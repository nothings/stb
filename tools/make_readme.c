#define STB_DEFINE
#include "../stb.h"

int main(int argc, char  **argv)
{
   int i;
   int hlen, flen, listlen;
   char *header = stb_file("README.header.md", &hlen);
   char *footer = stb_file("README.footer.md", &flen);
   char **list  = stb_stringfile("README.list", &listlen);

   FILE *f = fopen("../README.md", "wb");
   fwrite(header, 1, hlen, f);

   for (i=0; i < listlen; ++i) {
      int num,j;
      char **tokens = stb_tokens_stripwhite(list[i], "|", &num);
      FILE *g = fopen(stb_sprintf("../%s", tokens[0]), "rb");
      char buffer[256], *s1, *s2;
      fread(buffer, 1, 256, g);
      fclose(g);
      buffer[255] = 0;
      s1 = strchr(buffer, '-');
      if (!s1) stb_fatal("Couldn't find '-' before version number in %s", tokens[0]);
      s2 = strchr(s1+2, '-');
      if (!s2) stb_fatal("Couldn't find '-' after version number in %s", tokens[0]);
      *s2 = 0;
      s1 += 1;
      s1 = stb_trimwhite(s1);
      if (*s1 == 'v') ++s1;
      fprintf(f, "**%s** | %s", tokens[0], s1);
      s1 = stb_trimwhite(tokens[1]);
      s2 = stb_dupreplace(s1, " ", "&nbsp;");
      fprintf(f, " | %s", s2);
      free(s2);
      for (j=2; j < num; ++j)
         fprintf(f, " | %s", tokens[j]);
      fprintf(f, "\n");
   }

   fwrite(footer, 1, flen, f);
   fclose(f);

   return 0;
}