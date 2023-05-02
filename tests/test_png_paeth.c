#include <stdio.h>
#include <stdlib.h>

// Reference Paeth filter as per PNG spec
static int ref_paeth(int a, int b, int c)
{
   int p = a + b - c;
   int pa = abs(p-a);
   int pb = abs(p-b);
   int pc = abs(p-c);
   if (pa <= pb && pa <= pc) return a;
   if (pb <= pc) return b;
   return c;
}

// Optimized Paeth filter
static int opt_paeth(int a, int b, int c)
{
   int thresh = c*3 - (a + b);
   int lo = a < b ? a : b;
   int hi = a < b ? b : a;
   int t0 = (hi <= thresh) ? lo : c;
   int t1 = (thresh <= lo) ? hi : t0;
   return t1;
}

int main()
{
   // Exhaustively test the functions match for all byte inputs a, b,c in [0,255]
   for (int i = 0; i < (1 << 24); ++i) {
      int a = i & 0xff;
      int b = (i >> 8) & 0xff;
      int c = (i >> 16) & 0xff;

      int ref = ref_paeth(a, b, c);
      int opt = opt_paeth(a, b, c);
      if (ref != opt) {
         fprintf(stderr, "mismatch at a=%3d b=%3d c=%3d: ref=%3d opt=%3d\n", a, b, c, ref, opt);
         return 1;
      }
   }

   printf("all ok!\n");
   return 0;
}

// vim:sw=3:sts=3:et
