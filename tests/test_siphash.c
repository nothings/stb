#include <stdio.h>

#define STB_DS_IMPLEMENTATION
#define STBDS_SIPHASH_2_4
#define STBDS_TEST_SIPHASH_2_4
#include "../stb_ds.h"

int main(int argc, char **argv)
{
  unsigned char mem[64];
  int i,j;
  for (i=0; i < 64; ++i) mem[i] = i;
  for (i=0; i < 64; ++i) {
    size_t hash = stbds_hash_bytes(mem, i, 0);
    printf("  { ");
    for (j=0; j < 8; ++j)
      printf("0x%02x, ", (unsigned char) ((hash >> (j*8)) & 255));
    printf(" },\n");
  }
  return 0;
}