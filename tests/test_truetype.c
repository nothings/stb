#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <stdio.h>

char ttf_buffer[1<<25];
unsigned char output[512*100];

#ifdef TT_TEST

void debug(void)
{
   stbtt_fontinfo font;
   fread(ttf_buffer, 1, 1<<25, fopen("c:/x/lm/LiberationMono-Regular.ttf", "rb"));
   stbtt_InitFont(&font, ttf_buffer, 0);

   stbtt_MakeGlyphBitmap(&font, output, 6, 9, 512, 5.172414E-03f, 5.172414E-03f, 54);
}

int main(int argc, char **argv)
{
   stbtt_fontinfo font;
   unsigned char *bitmap;
   int w,h,i,j,c = (argc > 1 ? atoi(argv[1]) : 34807), s = (argc > 2 ? atoi(argv[2]) : 32);

   debug();

   fread(ttf_buffer, 1, 1<<25, fopen(argc > 3 ? argv[3] : "c:/windows/fonts/mingliu.ttc", "rb"));

   stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer,0));
   bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, (float)s), c, &w, &h, 0,0);

   for (j=0; j < h; ++j) {
      for (i=0; i < w; ++i)
         putchar(" .:ioVM@"[bitmap[j*w+i]>>5]);
      putchar('\n');
   }
   return 0;
}
#endif
