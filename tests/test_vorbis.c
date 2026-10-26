#include <stdio.h>
#include "stb_vorbis.c"

int main(int argc, char **argv)
{
   int chan, samplerate;
   short *output;
   int samples;
   FILE *f;

   if (argc < 2)
       return 1;

   samples = stb_vorbis_decode_filename(argv[1], &chan, &samplerate, &output);
   if (output) {
      printf("chan=%d samplerate=%d\n", chan, samplerate);
      f = fopen("decoded.raw", "wb");
      if (f) {
         fwrite(output, chan * sizeof(short), samples, f);
         fclose(f);
      }
      free(output);
   }
   return 0;
}
