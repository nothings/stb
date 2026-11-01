#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

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

#define STBI_MALLOC(sz) fuzz_malloc(sz)
#define STBI_REALLOC(p,sz) fuzz_realloc(p,sz)
#define STBI_FREE(p) fuzz_free(p)

// ---- IO callbacks

// This is still just reading from memory, but it exercises the
// callback IO paths.

typedef struct
{
   const unsigned char* ptr;
   const unsigned char* begin;
   const unsigned char* end;
} fuzz_ioctx;

static int fuzz_read(void *user, char *data, int size)
{
   fuzz_ioctx *c = (fuzz_ioctx *)user;
   ptrdiff_t max_size = c->end - c->ptr;
   if (size > max_size) size = (int)max_size;
   memcpy(data, c->ptr, size);
   c->ptr += size;
   return size;
}

static void fuzz_skip(void *user, int n)
{
   fuzz_ioctx *c = (fuzz_ioctx *)user;
   if (n >= 0) {
      ptrdiff_t max_dist = c->end - c->ptr;
      c->ptr += (n < max_dist) ? n : max_dist;
   } else {
      ptrdiff_t min_dist = c->begin - c->ptr;
      c->ptr += (n > min_dist) ? n : min_dist;
   }
}

static int fuzz_eof(void *user)
{
   fuzz_ioctx *c = (fuzz_ioctx *)user;
   return c->ptr == c->end;
}

// ---- fuzzer control

enum
{
   LOAD_MODE_8bit = 0, // stbi_load*
   LOAD_MODE_16bit, // stbi_load_16*
   LOAD_MODE_float, // stbi_loadf*
   LOAD_MODE_anim_gif, // stbi_load_gif_from_memory
};

#define CONTROL_MAGIC 217 // just a byte value that's not super common

// Append data to the image file that controls what code paths
// get exercised. This lets us get better API coverage using a
// regular fuzzing setup; by making these controls part of the
// input, they are naturally exercised alongside everything else.
// We add them as a footer because the formats stb_image reads
// use headers for identification and ignore bytes past the end.
// Doing it this way means regular image files are valid input.
typedef struct
{
   uint8_t magic; // set to CONTROL_MAGIC to enable fuzz control

   // allocation limit: we use a malloc/realloc wrapper that fails
   // every allocation past a certain count. This lets the fuzzer
   // easily and systematically exercise out-of-memory paths.
   // 255 = unlimited (we assume that 254 is enough to get coverage
   // of all failure paths)
   uint8_t alloc_limit;

   // load mode
   uint8_t load_mode : 2; // LOAD_MODE_*

   // requested component count-1
   uint8_t req_comp_minus1 : 2;

   // if 1, load via callbacks (else use _memory variants)
   uint8_t use_callbacks : 1;
} fuzz_control_footer;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef __cplusplus
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);
#endif

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
   stbi_io_callbacks callbacks = { fuzz_read, fuzz_skip, fuzz_eof };
   fuzz_ioctx ctx;

   int w, h, nch, nimg = 0;
   int *delays = NULL;
   void *img = NULL;

   // control parameters
   int load_mode = LOAD_MODE_8bit;
   int req_comp = 4;
   int use_callbacks = 0;

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
         load_mode = f->load_mode;
         req_comp = f->req_comp_minus1 + 1;
         use_callbacks = f->use_callbacks;
      }
   }

   // init io context to point at data
   ctx.begin = data;
   ctx.end = data + size;

   // check all kinds of info
   // this is both as a sanity check for image sizes and to exercise those funcs
   if (!use_callbacks) {
      if (!stbi_info_from_memory(data, size, &w, &h, &nch)) {
         return 0;
      }

      (void)stbi_is_hdr_from_memory(data, size);
      (void)stbi_is_16_bit_from_memory(data, size);
   } else {
      ctx.ptr = ctx.begin;
      if (!stbi_info_from_callbacks(&callbacks, &ctx, &w, &h, &nch)) {
         return 0;
      }

      ctx.ptr = ctx.begin;
      (void)stbi_is_hdr_from_callbacks(&callbacks, &ctx);
      ctx.ptr = ctx.begin;
      (void)stbi_is_16_bit_from_callbacks(&callbacks, &ctx);
   }

   // don't even try if we would likely exceed our memory limit
   // (this is assuming req_comp=4, but it's not _that_ precise)
   if (w && h > (MEM_LIMIT / 4) / w)
      return 0;

   ctx.ptr = ctx.begin;

   switch (load_mode) {
   case LOAD_MODE_8bit:
      if (!use_callbacks) {
         img = stbi_load_from_memory(data, size, &w, &h, &nch, req_comp);
      } else {
         img = stbi_load_from_callbacks(&callbacks, &ctx, &w, &h, &nch, req_comp);
      }
      break;

   case LOAD_MODE_16bit:
      if (!use_callbacks) {
         img = stbi_load_16_from_memory(data, size, &w, &h, &nch, req_comp);
      } else {
         img = stbi_load_16_from_callbacks(&callbacks, &ctx, &w, &h, &nch, req_comp);
      }
      break;

   case LOAD_MODE_float:
      if (!use_callbacks) {
         img = stbi_loadf_from_memory(data, size, &w, &h, &nch, req_comp);
      } else {
         img = stbi_loadf_from_callbacks(&callbacks, &ctx, &w, &h, &nch, req_comp);
      }
      break;

   case LOAD_MODE_anim_gif:
   #ifndef STBI_NO_GIF
      // no callback variant exists
      img = stbi_load_gif_from_memory(data, size, &delays, &w, &h, &nimg, &nch, req_comp);
   #else
      img = NULL;
   #endif
      break;
   }

   stbi_image_free(img);
   free(delays);

   return 0;
}

