
#define USE_STB 1

#if USE_STB
# include "stb_sprintf.h"
# define STB_SPRINTF_IMPLEMENTATION
# include "stb_sprintf.h"
# define SPRINTF stbsp_sprintf
# define SNPRINTF stbsp_snprintf
#else
# include <locale.h>
# define SPRINTF sprintf
# define SNPRINTF snprintf
#endif

#include <assert.h>
#include <math.h>    // for INFINITY, NAN
#include <stddef.h>  // for ptrdiff_t
#include <stdint.h>  // for intmax_t, ssize_t
#include <stdio.h>   // for printf
#include <string.h>  // for strcmp, strncmp, strlen

// stbsp_sprintf
#define CHECK(str, ...) { \
   int ret = SPRINTF(buf, __VA_ARGS__); \
   if (strcmp(buf, str) != 0 || ret != strlen(str)) { \
      printf("< '%s'\n> '%s'\n", str, buf); \
      assert(!"Fail"); \
   } \
}

int main()
{
   char buf[1024];
   int n = 0;
   const double pow_2_75 = 37778931862957161709568.0;
   const double pow_2_85 = 38685626227668133590597632.0;

   // integers
   CHECK("a b     1", "%c %s     %d", 'a', "b", 1);
   CHECK("abc     ", "%-8.3s", "abcdefgh");
   CHECK("+5", "%+2d", 5);
   CHECK("  6", "% 3i", 6);
   CHECK("-7  ", "%-4d", -7);
   CHECK("+0", "%+d", 0);
   CHECK("     00003:     00004", "%10.5d:%10.5d", 3, 4);
   CHECK("-100006789", "%d", -100006789);
   CHECK("20 0020", "%u %04u", 20u, 20u);
   CHECK("12 1e 3C", "%o %x %X", 10u, 30u, 60u);
   CHECK(" 12 1e 3C ", "%3o %2x %-3X", 10u, 30u, 60u);
   CHECK("012 0x1e 0X3C", "%#o %#x %#X", 10u, 30u, 60u);
   CHECK("", "%.0x", 0);
#if USE_STB
   CHECK("0", "%.0d", 0);  // stb_sprintf gives "0"
#else
   CHECK("",  "%.0d", 0);  // glibc gives "" as specified by C99(?)
#endif
   CHECK("33 555", "%hi %ld", (short)33, 555l);
   CHECK("9888777666", "%llu", 9888777666llu);
   CHECK("-1 2 -3", "%ji %zi %ti", (intmax_t)-1, (ssize_t)2, (ptrdiff_t)-3);

   // floating-point numbers
   CHECK("-3.000000", "%f", -3.0);
   CHECK("-8.8888888800", "%.10f", -8.88888888);
   CHECK("880.0888888800", "%.10f", 880.08888888);
   CHECK("4.1", "%.1f", 4.1);
   CHECK(" 0", "% .0f", 0.1);
   CHECK("0.00", "%.2f", 1e-4);
   CHECK("-5.20", "%+4.2f", -5.2);
   CHECK("0.0       ", "%-10.1f", 0.);
   CHECK("0.000001", "%f", 9.09834e-07);
#if USE_STB  // rounding differences
   CHECK("38685626227668133600000000.0", "%.1f", pow_2_85);
   CHECK("0.000000499999999999999978", "%.24f", 5e-7);
#else
   CHECK("38685626227668133590597632.0", "%.1f", pow_2_85); // exact
   CHECK("0.000000499999999999999977", "%.24f", 5e-7);
#endif
   CHECK("0.000000000000000020000000", "%.24f", 2e-17);
   CHECK("0.0000000100 100000000", "%.10f %.0f", 1e-8, 1e+8);
   CHECK("100056789.0", "%.1f", 100056789.0);
   CHECK(" 1.23 %", "%*.*f %%", 5, 2, 1.23);
   CHECK("-3.000000e+00", "%e", -3.0);
   CHECK("4.1E+00", "%.1E", 4.1);
   CHECK("-5.20e+00", "%+4.2e", -5.2);
   CHECK("+0.3 -3", "%+g %+g", 0.3, -3.0);
   CHECK("4", "%.1G", 4.1);
   CHECK("-5.2", "%+4.2g", -5.2);
   CHECK("3e-300", "%g", 3e-300);
   CHECK("1", "%.0g", 1.2);
   CHECK(" 3.7 3.71", "% .3g %.3g", 3.704, 3.706);
   CHECK("2e-315:1e+308", "%g:%g", 2e-315, 1e+308);

#if USE_STB
   CHECK("Inf Inf NaN", "%g %G %f", INFINITY, INFINITY, NAN);
   CHECK("N", "%.1g", NAN);
#else
   CHECK("inf INF nan", "%g %G %f", INFINITY, INFINITY, NAN);
   CHECK("nan", "%.1g", NAN);
#endif

   // %n
   CHECK("aaa ", "%.3s %n", "aaaaaaaaaaaaa", &n);
   assert(n == 4);

   // hex floats
   CHECK("0x1.fedcbap+98", "%a", 0x1.fedcbap+98);
   CHECK("0x1.999999999999a0p-4", "%.14a", 0.1);
   CHECK("0x1.0p-1022", "%.1a", 0x1.ffp-1023);
#if USE_STB  // difference in default precision and x vs X for %A
   CHECK("0x1.009117p-1022", "%a", 2.23e-308);
   CHECK("-0x1.AB0P-5", "%.3A", -0x1.abp-5);
#else
   CHECK("0x1.0091177587f83p-1022", "%a", 2.23e-308);
   CHECK("-0X1.AB0P-5", "%.3A", -0X1.abp-5);
#endif

   // %p
#if USE_STB
   CHECK("0000000000000000", "%p", (void*) NULL);
#else
   CHECK("(nil)", "%p", (void*) NULL);
#endif

   // snprintf
   assert(SNPRINTF(buf, 100, " %s     %d",  "b", 123) == 10);
   assert(strcmp(buf, " b     123") == 0);
   assert(SNPRINTF(buf, 100, "%f", pow_2_75) == 30);
   assert(strncmp(buf, "37778931862957161709568.000000", 17) == 0);
   n = SNPRINTF(buf, 10, "number %f", 123.456789);
   assert(strcmp(buf, "number 12") == 0);
   assert(n == (USE_STB ? 9 : 17));  // written vs would-be written bytes
   n = SNPRINTF(buf, 0, "7 chars");
   assert(n == (USE_STB ? 0 : 7));
   // stb_sprintf uses internal buffer of 512 chars - test longer string
   assert(SPRINTF(buf, "%d  %600s", 3, "abc") == 603);
   assert(strlen(buf) == 603);
   SNPRINTF(buf, 550, "%d  %600s", 3, "abc");
   assert(strlen(buf) == 549);
   assert(SNPRINTF(buf, 600, "%510s     %c", "a", 'b') == 516);

   // length check
   assert(SNPRINTF(NULL, 0, " %s     %d",  "b", 123) == 10);

   // ' modifier. Non-standard, but supported by glibc.
#if !USE_STB
   setlocale(LC_NUMERIC, "");  // C locale does not group digits
#endif
   CHECK("1,200,000", "%'d", 1200000);
   CHECK("-100,006,789", "%'d", -100006789);
   CHECK("9,888,777,666", "%'lld", 9888777666ll);
   CHECK("200,000,000.000000", "%'18f", 2e8);
   CHECK("100,056,789", "%'.0f", 100056789.0);
   CHECK("100,056,789.0", "%'.1f", 100056789.0);
#if USE_STB  // difference in leading zeros
   CHECK("000,001,200,000", "%'015d", 1200000);
#else
   CHECK("0000001,200,000", "%'015d", 1200000);
#endif

   // things not supported by glibc
#if USE_STB
   CHECK("null", "%s", (char*) NULL);
   CHECK("123,4abc:", "%'x:", 0x1234ABC);
   CHECK("100000000", "%b", 256);
   CHECK("0b10 0B11", "%#b %#B", 2, 3);
   CHECK("2 3 4", "%I64d %I32d %Id", 2ll, 3, 4ll);
   CHECK("1k 2.54 M", "%$_d %$.2d", 1000, 2536000);
   CHECK("2.42 Mi 2.4 M", "%$$.2d %$$$d", 2536000, 2536000);

   // different separators
   stbsp_set_separators(' ', ',');
   CHECK("12 345,678900", "%'f", 12345.6789);
#endif

   return 0;
}
