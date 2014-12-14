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
      char **files = stb_readdir_files("pngsuite/part1");
      for (i=0; i < stb_arr_len(files); ++i) {
         int n;
         char **failed = NULL;
         unsigned char *data;
         //printf("%s\n", files[i]);
         data = stbi_load(files[i], &w, &h, &n, 0); if (data) free(data); else stb_arr_push(failed, "&n");
         data = stbi_load(files[i], &w, &h,  0, 1); if (data) free(data); else stb_arr_push(failed, "1");
         data = stbi_load(files[i], &w, &h,  0, 2); if (data) free(data); else stb_arr_push(failed, "2");
         data = stbi_load(files[i], &w, &h,  0, 3); if (data) free(data); else stb_arr_push(failed, "3");
         data = stbi_load(files[i], &w, &h,  0, 4); if (data)           ; else stb_arr_push(failed, "4");
         if (data) {
            char fname[512];
            stb_splitpath(fname, files[i], STB_FILE);
            stbi_write_png(stb_sprintf("output/%s.png", fname), w, h, 4, data, w*4);
            free(data);
         }
         if (failed) {
            int j;
            printf("FAILED: ");
            for (j=0; j < stb_arr_len(failed); ++j)
               printf("%s ", failed[j]);
            printf(" -- %s\n", files[i]);
         }
      }
      printf("Tested %d files\n", i);
   }
   return 0;
}
