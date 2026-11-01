#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// ---- memory allocation with limit to memory allocations

// reallocs and frees don't restore the byte count. this is
// no attempt at accurate memory tracking, just a quick way
// to limit fuzzer instances consuming huge amounts of mem.

// we also add a global alloc count limit after which every
// subsequent malloc fails no matter the size. this allows the
// fuzzer to systematically exercise all out-of-memory paths.

#define MEM_LIMIT (64<<20) // 64MB

size_t g_alloc_count_limit;
size_t g_alloc_bytes_remaining;

static int fuzz_alloc_check(size_t sz)
{
   if (!g_alloc_count_limit || sz > g_alloc_bytes_remaining) {
      return 0;
   }

   --g_alloc_count_limit;
   g_alloc_bytes_remaining -= sz;
   return 1;
}

static void *fuzz_malloc(size_t sz)
{
   return fuzz_alloc_check(sz) ? malloc(sz) : NULL;
}

static void *fuzz_realloc(void *ptr, size_t newsz)
{
   if (fuzz_alloc_check(newsz)) {
      return realloc(ptr, newsz);
   } else {
      // failing realloc returns NULL but leaves the old block alone
      return NULL;
   }
}

static void fuzz_free(void *ptr)
{
   free(ptr);
}

// this is a bit gross, but it'll do for now
#define malloc(sz) fuzz_malloc(sz)
#define free(p) fuzz_free(p)
#define realloc(p,sz) fuzz_realloc(p,sz)

// ---- fuzzer control

#define CONTROL_MAGIC 217 // just a byte value that's not super common

// Append data to the input data that controls what code paths
// get exercised.
//
// Right now we only use an allocation limit to help us exercise
// out-of-memory cases.
typedef struct
{
   uint8_t magic; // set to CONTROL_MAGIC to enable fuzz control

   // allocation limit: we use a malloc/realloc wrapper that fails
   // every allocation past a certain count. This lets the fuzzer
   // easily and systematically exercise out-of-memory paths.
   // 255 = unlimited (we assume that 254 is enough to get coverage
   // of all failure paths)
   uint8_t alloc_limit;
} fuzz_control_footer;

#include "stb_vorbis.c"

#undef malloc
#undef realloc
#undef free

#ifdef __cplusplus
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);
#endif

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
   int chans, sample_rate;
   int result;
   short *output = NULL;

   // reset global control parameters to default
   g_alloc_count_limit = ~(size_t) 0;
   g_alloc_bytes_remaining = MEM_LIMIT;

   // if we have the bytes for a fuzz control footer, try to parse it
   if (size >= sizeof(fuzz_control_footer)) {
      const fuzz_control_footer *f = (const fuzz_control_footer *)(data + size - sizeof(fuzz_control_footer));
      if (f->magic == CONTROL_MAGIC) {
         if (f->alloc_limit != 255) {
            g_alloc_count_limit = f->alloc_limit;
         }

         size -= sizeof(*f);
      }
   }

   result = stb_vorbis_decode_memory(data, (int)size, &chans, &sample_rate, &output);
   free(output);

   return 0;
}

