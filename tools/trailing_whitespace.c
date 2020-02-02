#define STB_DEFINE
#include "stb.h"

int main(int argc, char **argv)
{
   int i;
   for (i=1; i < argc; ++i) {
      int len;
      FILE *f;
      char *s = stb_file(argv[i], &len);
      char *end, *src, *dest;
      if (s == NULL) {
         printf("Couldn't read file '%s'.\n", argv[i]);
         continue; 
      }
      end = s + len;
      src = dest = s;
      while (src < end) {
         char *start=0;
         while (src < end && *src != '\n' && *src != '\r')
            *dest++ = *src++;
         while (dest-1 > s && (dest[-1] == ' ' || dest[-1] == '\t'))
            --dest;
         while (src < end && (*src == '\n' || *src == '\r'))
            *dest++ = *src++;
      }
      f = fopen(argv[i], "wb");
      fwrite(s, 1, dest-s, f);
      fclose(f);
   }
    return 0;
}
