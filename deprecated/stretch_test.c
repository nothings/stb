// check that stb_truetype compiles with no stb_rect_pack.h
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <assert.h>

int main(int arg, char **argv)
{
   int i;
   int *arr = NULL;

   for (i=0; i < 1000000; ++i)
      arrput(arr, i);

   assert(arrlen(arr) == 1000000);
   for (i=0; i < 1000000; ++i)
      assert(arr[i] == i);

   arrfree(arr);
   arr = NULL;

   for (i=0; i < 1000; ++i)
      arrput(arr, 1000);
   assert(arrlen(arr) == 1000000);

   return 0;
}