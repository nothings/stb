#ifdef TEST_VORBIS
#include <stdio.h>
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"
#include <stdlib.h>
#include "stb.h"

int main(int argc, char **argv)
{
   char **filenames = NULL;
   int chan, samplerate;
   short *output;
   int samples, i;
   FILE *f;

   if (argc < 2)
       return 1;

   f = fopen(argv[1], "rb");
   if (f) {
      fclose(f);
      stb_arr_push(filenames, argv[1]);
   } else {
      filenames = stb_readdir_recursive(argv[1], "*.ogg");
   }
   if (stb_arr_len(filenames) == 0)
      printf("No files.\n");
   else
      for (i=0; i < stb_arr_len(filenames); ++i) {
         output = NULL;
         printf("%s: ", filenames[i]);
         samples = stb_vorbis_decode_filename(filenames[i], &chan, &samplerate, &output);
         if (samples < 0)
            printf("=== ERROR ===: %d\n", -samples);
         if (output) {
            printf("chan=%d samplerate=%d\n", chan, samplerate);
            if (stb_arr_len(filenames) == 1) {
               f = fopen("decoded.raw", "wb");
               if (f) {
                  fwrite(output, chan * sizeof(short), samples, f);
                  fclose(f);
               }
               free(output);
            }
         }
   }
   return 0;
}
#endif
