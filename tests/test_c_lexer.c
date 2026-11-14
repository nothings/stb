#include "stb_c_lexer.h"

#define STB_C_LEX_C_DECIMAL_INTS    Y   //  "0|[1-9][0-9]*"                        CLEX_intlit
#define STB_C_LEX_C_HEX_INTS        Y   //  "0x[0-9a-fA-F]+"                       CLEX_intlit
#define STB_C_LEX_C_OCTAL_INTS      Y   //  "[0-7]+"                               CLEX_intlit
#define STB_C_LEX_C_DECIMAL_FLOATS  Y   //  "[0-9]*(.[0-9]*([eE][-+]?[0-9]+)?)     CLEX_floatlit
#define STB_C_LEX_C99_HEX_FLOATS    Y   //  "0x{hex}+(.{hex}*)?[pP][-+]?{hex}+     CLEX_floatlit
#define STB_C_LEX_C_IDENTIFIERS     Y   //  "[_a-zA-Z][_a-zA-Z0-9]*"               CLEX_id
#define STB_C_LEX_C_DQ_STRINGS      Y   //  double-quote-delimited strings with escapes  CLEX_dqstring
#define STB_C_LEX_C_SQ_STRINGS      N   //  single-quote-delimited strings with escapes  CLEX_ssstring
#define STB_C_LEX_C_CHARS           Y   //  single-quote-delimited character with escape CLEX_charlits
#define STB_C_LEX_C_COMMENTS        Y   //  "/* comment */"
#define STB_C_LEX_CPP_COMMENTS      Y   //  "// comment to end of line\n"
#define STB_C_LEX_C_COMPARISONS     Y   //  "==" CLEX_eq  "!=" CLEX_noteq   "<=" CLEX_lesseq  ">=" CLEX_greatereq
#define STB_C_LEX_C_LOGICAL         Y   //  "&&"  CLEX_andand   "||"  CLEX_oror
#define STB_C_LEX_C_SHIFTS          Y   //  "<<"  CLEX_shl      ">>"  CLEX_shr
#define STB_C_LEX_C_INCREMENTS      Y   //  "++"  CLEX_plusplus "--"  CLEX_minusminus
#define STB_C_LEX_C_ARROW           Y   //  "->"  CLEX_arrow
#define STB_C_LEX_EQUAL_ARROW       N   //  "=>"  CLEX_eqarrow
#define STB_C_LEX_C_BITWISEEQ       Y   //  "&="  CLEX_andeq    "|="  CLEX_oreq     "^="  CLEX_xoreq
#define STB_C_LEX_C_ARITHEQ         Y   //  "+="  CLEX_pluseq   "-="  CLEX_minuseq
                                        //  "*="  CLEX_muleq    "/="  CLEX_diveq    "%=" CLEX_modeq
                                        //  if both STB_C_LEX_C_SHIFTS & STB_C_LEX_C_ARITHEQ:
                                        //                      "<<=" CLEX_shleq    ">>=" CLEX_shreq

#define STB_C_LEX_PARSE_SUFFIXES    Y   // letters after numbers are parsed as part of those numbers, and must be in suffix list below
#define STB_C_LEX_DECIMAL_SUFFIXES  "uUlL"  // decimal integer suffixes e.g. "uUlL" -- these are returned as-is in string storage
#define STB_C_LEX_HEX_SUFFIXES      "uUlL"  // e.g. "uUlL"
#define STB_C_LEX_OCTAL_SUFFIXES    "uUlL"  // e.g. "uUlL"
#define STB_C_LEX_FLOAT_SUFFIXES    ""  //

#define STB_C_LEX_0_IS_EOF             Y  // if Y, ends parsing at '\0'; if N, returns '\0' as token
#define STB_C_LEX_INTEGERS_AS_DOUBLES  N  // parses integers as doubles so they can be larger than 'int', but only if STB_C_LEX_USE_STDLIB==N
#define STB_C_LEX_MULTILINE_DSTRINGS   N  // allow newlines in double-quoted strings // @TODO These two don't currently do anything. See
                                          //                                                  the Status section at the start of the file.
#define STB_C_LEX_MULTILINE_SSTRINGS   N  // allow newlines in single-quoted strings // @TODO See comment above
#define STB_C_LEX_USE_STDLIB           N  // use strtod,strtol for parsing #s; otherwise inaccurate hack
#define STB_C_LEX_DOLLAR_IDENTIFIER    Y  // allow $ as an identifier character
#define STB_C_LEX_FLOAT_NO_DECIMAL     Y  // allow floats that have no decimal point if they have an exponent

#define STB_C_LEX_DISCARD_PREPROCESSOR    Y   // discard C-preprocessor directives (e.g. after prepocess
                                              // still have #line, #pragma, etc)

#define STB_C_LEX_OCTAL_CHARS         Y // allow octal chars in strings

#define STB_C_LEX_HEX_CHARS           Y // allow hex chars in strings

//#define STB_C_LEX_ISWHITE(str)    ... // return length in bytes of whitespace characters if first char is whitespace

#define STB_C_LEXER_DEFINITIONS         // This line prevents the header file from replacing your definitions

#define STB_C_LEXER_IMPLEMENTATION

#include "stb_c_lexer.h"

#include "stb_ds.h"


#ifdef C_LEXER_TEST

typedef struct
{
   int id;
   double realval;
   unsigned int intval;
   char *str;
   char *where1, *where2;
} token;

token *parse(stb_lexer *lexer)
{
   token *p = 0;
   for(;;) {
      int result = stb_c_lexer_get_token(lexer);
      token t;
      if (result == 0)
         return p;

      t.id = lexer->token;
      t.intval = 0;
      t.realval = 0;
      t.str = 0;
      t.where1 = lexer->where_firstchar;
      t.where2 = lexer->where_lastchar;

      switch (lexer->token) {
         case CLEX_id        :
         case CLEX_dqstring  :
         case CLEX_sqstring  :
            t.str = strdup(lexer->string);
            break;
         case CLEX_intlit    :
         case CLEX_charlit   :
            t.intval = lexer->int_number;
            break;
         case CLEX_floatlit  :
            t.realval = lexer->real_number;
            break;
         default:
            break;
      }

      arrpush(p, t);
      if (t.id == CLEX_parse_error)
         return p;
   }
}

#include <stdio.h>

static int test_intlits()
{
   static const char test_text[] =
      "0x7fffffff 017777777777 2147483647\n" // INT32_MAX
      "0x80000000 020000000000 2147483648\n" // INT32_MAX+1
      "0x2540be400 0112402762000 10000000000\n" // 10 billion
      "0x7fffffffffffffff 0777777777777777777777 9223372036854775807\n" // INT64_MAX
      "0x8000000000000000 01000000000000000000000 9223372036854775808\n"; // INT64_MAX + 1

   char string_store[256];
   stb_lexer lexer;
   int i, tok;

   stb_c_lexer_init(&lexer, test_text, test_text + sizeof(test_text) - 1, string_store, sizeof(string_store));

   for (i=0; i < 15; ++i) {
      if (!stb_c_lexer_get_token(&lexer) || lexer.token != CLEX_intlit)
         return 0;

      printf("intlit: 0x%lx\n", lexer.int_number);
   }

   return 1;
}

int main(int argc, char **argv)
{
   int i,j;
   char *buffer = malloc(1<<20), *zbuf;
   char *strings = malloc(1<<16);
   size_t len = fread(buffer, 1, 1<<20, fopen("tests/test_c_lexer.txt", "rb"));
   buffer[len] = 0;
   zbuf = malloc(len+1);
   memcpy(zbuf, buffer, len);
   test_intlits();
   for (i=len; i >= 0; --i) {
      stb_lexer lexer;
      token *t1, *t2;
      printf("%d\n", i);
      zbuf[i] = 0;
      stb_c_lexer_init(&lexer, buffer, buffer+i, strings, 1 << 16);
      t1 = parse(&lexer);
      stb_c_lexer_init(&lexer, zbuf, 0, strings, 1 << 16);
      t2 = parse(&lexer);
      for (j=0; j < arrlen(t1) && j < arrlen(t2); ++j) {
         if (t1[j].id != t2[j].id) { printf("Length %d: Mismatched token #%d: %d vs %d", i, j, t1[j].id, t2[j].id); goto error; }
         switch (t1[j].id) {
            case CLEX_id        :
            case CLEX_dqstring  :
            case CLEX_sqstring  :
               if (0 != strcmp(t1[j].str, t2[j].str)) { printf("Length %d: Mismatched string '%s' vs '%s", i, t1[j].str, t2[j].str); goto error; }
               break;
            case CLEX_intlit    :
            case CLEX_charlit   :
               if (t1[j].intval != t2[j].intval) { printf("Length %d: Mismatched int %d vs %d (%xd vs %xd)", i, t1[j].intval, t2[j].intval, t1[j].intval, t2[j].intval); goto error; }
               break;
            case CLEX_floatlit  :
               if (t1[j].realval != t2[j].realval) { printf("Length %d: Mismatched float %f vs %f", i, t1[j].realval, t2[j].realval); goto error; }
               break;
         }
      }
      if (j < arrlen(t1)) { printf("Length %d: More tokens in explicit-length stream; first unmatched token is %d. Zero-terminated stream ends: ", i, t1[j].id); goto error; }
      if (j < arrlen(t2)) { printf("Length %d: More tokens in zero-terminated stream; first unmatched token is %d. ", i, t2[j].id); goto error; }
      continue;
     error:
      if (j < arrlen(t2)) {
         stb_lex_location loc1,loc2;
         stb_c_lexer_get_location(&lexer, t2[j].where1, &loc1);
         stb_c_lexer_get_location(&lexer, t2[j].where2, &loc2);
         printf(". Line %d, offset %d..%d\n", loc1.line_number, loc1.line_offset, loc2.line_offset);
      }
      if (len > 50)
         printf("\n%s\n", zbuf+len-50);
      else
         printf("\n%s\n", zbuf);
      len=len;
      break;
   }
   return 0;
}
#endif
