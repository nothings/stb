#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main(int argc, char **argv)
{
   int w,h;
   unsigned char *data = stbi_load(argv[1], &w, &h, 0, 4);
   if (data)
      stbi_write_png("c:/x/result.png", w, h, 4, data, w*4);
   return 0;
}
