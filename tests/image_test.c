#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_DEFINE
#include "stb.h"

int main(int argc, char **argv)
{
   int w,h;
   if (argc > 1) {
      int i;
      for (i=1; i < argc; ++i) {
         unsigned char *data;
         int n;
         printf("%s\n", argv[i]);
         data = stbi_load(argv[i], &w, &h, &n, 4); if (data) free(data); else printf("Failed &n\n");
         data = stbi_load(argv[i], &w, &h,  0, 1); if (data) free(data); else printf("Failed 1\n");
         data = stbi_load(argv[i], &w, &h,  0, 2); if (data) free(data); else printf("Failed 2\n");
         data = stbi_load(argv[i], &w, &h,  0, 3); if (data) free(data); else printf("Failed 3\n");
         data = stbi_load(argv[i], &w, &h,  0, 4);
         assert(data);
         if (data) {
            char fname[512];
            stb_splitpath(fname, argv[i], STB_FILE);
            stbi_write_png(stb_sprintf("output/%s.png", fname), w, h, 4, data, w*4);
            free(data);
         } else
            printf("FAILED 4\n");
      }
   } else {
      int i;
      char **files = stb_readdir_files("images");
      for (i=0; i < stb_arr_len(files); ++i) {
         int n;
         unsigned char *data;
         printf("%s\n", files[i]);
         data = stbi_load(files[i], &w, &h, &n, 4); if (data) free(data); else printf("Failed &n\n");
         data = stbi_load(files[i], &w, &h,  0, 1); if (data) free(data); else printf("Failed 1\n");
         data = stbi_load(files[i], &w, &h,  0, 2); if (data) free(data); else printf("Failed 2\n");
         data = stbi_load(files[i], &w, &h,  0, 3); if (data) free(data); else printf("Failed 3\n");
         data = stbi_load(files[i], &w, &h,  0, 4);
         if (data) {
            char fname[512];
            stb_splitpath(fname, files[i], STB_FILE);
            stbi_write_png(stb_sprintf("output/%s.png", fname), w, h, 4, data, w*4);
            free(data);
         } else
            printf("FAILED\n");
      }
   }
   return 0;
}
