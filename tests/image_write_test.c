#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// using an 'F' since it has no rotational symmetries, and 6x5
// because it's a small, atypical size likely to trigger edge cases.
//
// conveniently, it's also small enough to fully fit inside a typical
// directory listing thumbnail, which simplifies checking at a glance.
static const char img6x5_template[] =
   ".****."
   ".*...."
   ".***.."
   ".*...."
   ".*....";

int main(int argc, char **argv)
{
   // make a RGB version of the template image
   // use red on blue to detect R<->B swaps
   unsigned char img6x5_rgb[6*5*3];
   float img6x5_rgbf[6*5*3];
   int i;

   for (i = 0; i < 6*5; i++) {
      int on = img6x5_template[i] == '*';
      img6x5_rgb[i*3 + 0] = on ? 255 : 0;
      img6x5_rgb[i*3 + 1] = 0;
      img6x5_rgb[i*3 + 2] = on ? 0 : 255;

      img6x5_rgbf[i*3 + 0] = on ? 1.0f : 0.0f;
      img6x5_rgbf[i*3 + 1] = 0.0f;
      img6x5_rgbf[i*3 + 2] = on ? 0.0f : 1.0f;
   }

   stbi_write_png("wr6x5_regular.png", 6, 5, 3, img6x5_rgb, 6*3);
   stbi_write_bmp("wr6x5_regular.bmp", 6, 5, 3, img6x5_rgb);
   stbi_write_tga("wr6x5_regular.tga", 6, 5, 3, img6x5_rgb);
   stbi_write_jpg("wr6x5_regular.jpg", 6, 5, 3, img6x5_rgb, 95);
   stbi_write_hdr("wr6x5_regular.hdr", 6, 5, 3, img6x5_rgbf);

   stbi_flip_vertically_on_write(1);

   stbi_write_png("wr6x5_flip.png", 6, 5, 3, img6x5_rgb, 6*3);
   stbi_write_bmp("wr6x5_flip.bmp", 6, 5, 3, img6x5_rgb);
   stbi_write_tga("wr6x5_flip.tga", 6, 5, 3, img6x5_rgb);
   stbi_write_jpg("wr6x5_flip.jpg", 6, 5, 3, img6x5_rgb, 95);
   stbi_write_hdr("wr6x5_flip.hdr", 6, 5, 3, img6x5_rgbf);

   return 0;
}
