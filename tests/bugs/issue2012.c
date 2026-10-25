#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
/* zlib.compress(b"hello hello hello hello") - 16 bytes, inflates to 23 */
static const unsigned char z[16] = {120,156,203,72,205,201,201,87,200,64,39,1,104,3,8,177};
/* Call stbi_zlib_decode_malloc_guesssize() with the initial_size given as
   argv[1], then print the result: whether it returned a buffer, and the
   decoded length reported in outlen. */
int main(int argc, char **argv){
   int initial = argc > 1 ? atoi(argv[1]) : 0;
   int outlen = -1;
   char *out = stbi_zlib_decode_malloc_guesssize((const char *)z, (int)sizeof z, initial, &outlen);
   printf("initial_size=%d -> %s, outlen=%d\n", initial, out ? "ok" : "NULL", outlen);
   free(out);
   return 0;
}
