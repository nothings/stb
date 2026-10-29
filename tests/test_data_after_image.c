#include <stddef.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static const unsigned char test_data[] = {
   0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
   0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
   0x08, 0x02, 0x00, 0x00, 0x00, 0xfd, 0xd4, 0x9a, 0x73, 0x00, 0x00, 0x00,
   0x16, 0x49, 0x44, 0x41, 0x54, 0x08, 0xd7, 0x63, 0x6c, 0x16, 0x3d, 0xc4,
   0xc0, 0xc0, 0xc0, 0xc4, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x10,
   0x23, 0x01, 0x5e, 0xe1, 0x17, 0x17, 0x19, 0x00, 0x00, 0x00, 0x00, 0x49,
   0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82,
   'P', 'o', 's', 't', 'P', 'N', 'G', 'D', 'a', 't', 'a', '!'
};

typedef struct {
   const unsigned char* ptr;
   const unsigned char* begin;
   const unsigned char* end;
} my_ioctx;

static int my_read(void *user, char *data, int size)
{
   my_ioctx *c = (my_ioctx *)user;
   ptrdiff_t max_size = c->end - c->ptr;
   if (size > max_size) size = (int)max_size;
   memcpy(data, c->ptr, size);
   c->ptr += size;
   return size;
}

static void my_skip(void *user, int n)
{
   my_ioctx *c = (my_ioctx *)user;
   if (n >= 0) {
      ptrdiff_t max_dist = c->end - c->ptr;
      c->ptr += (n < max_dist) ? n : max_dist;
   } else {
      ptrdiff_t min_dist = c->begin - c->ptr;
      c->ptr += (n > min_dist) ? n : min_dist;
   }
}

static int my_eof(void *user)
{
   my_ioctx *c = (my_ioctx *)user;
   return c->ptr == c->end;
}

int main()
{
   my_ioctx ctx;
   stbi_io_callbacks ioc = { my_read, my_skip, my_eof };
   int x,y,n;
   stbi_uc *data;

   ctx.ptr = ctx.begin = test_data;
   ctx.end = test_data + sizeof(test_data);

   data = stbi_load_from_callbacks(&ioc, &ctx, &x, &y, &n, 4);
   if (!data) {
      printf("image failed to load: %s\n", stbi_failure_reason());
      return 1;
   }

   printf("%dx%d, ncomp=%d\n", x, y, n);
   printf("read pointer is %d bytes from end\n", (int)(ctx.end - ctx.ptr));

   if (ctx.end - ctx.ptr != 12 || memcmp(ctx.ptr, "PostPNGData!", 12) != 0) {
      printf("that's not where it should be!\n");
      return 1;
   }

   stbi_image_free(data);
   return 0;
}
