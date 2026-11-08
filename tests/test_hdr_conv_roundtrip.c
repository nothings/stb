#include <stdint.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char **argv)
{
   float explut[256];
   float linear[3];
   uint8_t in_rgbe[4];
   uint8_t out_rgbe[4];
   uint32_t x;

   // This test verifies that RGBE -> float -> RGBE conversions between stb_image and stb_image_write round-trip correctly

   stbi__hdr_makelut(explut, 3);

   // smallest RGBE exponent that doesn't have values that snap to 0 is 23:
   //   0x80 * 2^(23 - (128 + 8)) = 2^(23 + 7 - 128 - 8) = 2^(-106)
   // HDR cutoff for "emit black" is 'traditionally' at 1e-32 ~= 1.62 * 2^(-107)
   x = (23 << 24) - 1u;
   do
   {
      ++x; // wraps around to 0 on overflow

      // need to value at least one value with bit 7 set for it to be a legal encoding
      if ((x & 0x808080u) == 0)
         continue;

      in_rgbe[0] = (uint8_t) (x & 0xff);
      in_rgbe[1] = (uint8_t) ((x >> 8) & 0xff);
      in_rgbe[2] = (uint8_t) ((x >> 16) & 0xff);
      in_rgbe[3] = (uint8_t) (x >> 24);
      stbi__hdr_convert(linear, in_rgbe, 3, explut);
      stbiw__linear_to_rgbe(out_rgbe, linear, 3);

      if (memcmp(in_rgbe, out_rgbe, 4) != 0) {
         printf("failure to round-trip r=0x%02x g=0x%02x b=0x%02x e=0x%02x\n", in_rgbe[0], in_rgbe[1], in_rgbe[2], in_rgbe[3]);
         printf("linear r=%g g=%g b=%g\n", linear[0], linear[1], linear[2]);
         printf("got back r=0x%02x g=0x%02x b=0x%02x e=0x%02x\n", out_rgbe[0], out_rgbe[1], out_rgbe[2], out_rgbe[3]);
         return 1;
      }
   } while (x != 0u);

   printf("all OK!\n");
   return 0;
}
