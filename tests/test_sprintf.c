
#define USE_STB 1

#if USE_STB
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
#include <stdio.h>   // for printf
#include <string.h>  // for strcmp, strncmp, strlen

#if _MSC_VER && _MSC_VER <= 1600 
typedef int intmax_t;
typedef ptrdiff_t ssize_t;
#else
#include <stdint.h>  // for intmax_t, ssize_t
#endif

// stbsp_sprintf
#define CHECK_END(str) \
   if (strcmp(buf, str) != 0 || (unsigned) ret != strlen(str)) { \
      printf("< '%s'\n> '%s'\n", str, buf); \
      assert(!"Fail"); \
   }

#define CHECK9(str, v1, v2, v3, v4, v5, v6, v7, v8, v9) { int ret = SPRINTF(buf, v1, v2, v3, v4, v5, v6, v7, v8, v9); CHECK_END(str); }
#define CHECK8(str, v1, v2, v3, v4, v5, v6, v7, v8    ) { int ret = SPRINTF(buf, v1, v2, v3, v4, v5, v6, v7, v8    ); CHECK_END(str); }
#define CHECK7(str, v1, v2, v3, v4, v5, v6, v7        ) { int ret = SPRINTF(buf, v1, v2, v3, v4, v5, v6, v7        ); CHECK_END(str); }
#define CHECK6(str, v1, v2, v3, v4, v5, v6            ) { int ret = SPRINTF(buf, v1, v2, v3, v4, v5, v6            ); CHECK_END(str); }
#define CHECK5(str, v1, v2, v3, v4, v5                ) { int ret = SPRINTF(buf, v1, v2, v3, v4, v5                ); CHECK_END(str); }
#define CHECK4(str, v1, v2, v3, v4                    ) { int ret = SPRINTF(buf, v1, v2, v3, v4                    ); CHECK_END(str); }
#define CHECK3(str, v1, v2, v3                        ) { int ret = SPRINTF(buf, v1, v2, v3                        ); CHECK_END(str); }
#define CHECK2(str, v1, v2                            ) { int ret = SPRINTF(buf, v1, v2                            ); CHECK_END(str); }
#define CHECK1(str, v1                                ) { int ret = SPRINTF(buf, v1                                ); CHECK_END(str); }

#ifdef TEST_SPRINTF
int main()
{
   char buf[1024];
   int n = 0;
   const double pow_2_75 = 37778931862957161709568.0;
   const double pow_2_85 = 38685626227668133590597632.0;

   // integers
   CHECK4("a b     1", "%c %s     %d", 'a', "b", 1);
   CHECK2("abc     ", "%-8.3s", "abcdefgh");
   CHECK2("+5", "%+2d", 5);
   CHECK2("  6", "% 3i", 6);
   CHECK2("-7  ", "%-4d", -7);
   CHECK2("+0", "%+d", 0);
   CHECK3("     00003:     00004", "%10.5d:%10.5d", 3, 4);
   CHECK2("-100006789", "%d", -100006789);
   CHECK3("20 0020", "%u %04u", 20u, 20u);
   CHECK4("12 1e 3C", "%o %x %X", 10u, 30u, 60u);
   CHECK4(" 12 1e 3C ", "%3o %2x %-3X", 10u, 30u, 60u);
   CHECK4("012 0x1e 0X3C", "%#o %#x %#X", 10u, 30u, 60u);
   CHECK2("", "%.0x", 0);
#if USE_STB
   CHECK2("0", "%.0d", 0);  // stb_sprintf gives "0"
#else
   CHECK2("",  "%.0d", 0);  // glibc gives "" as specified by C99(?)
#endif
   CHECK3("33 555", "%hi %ld", (short)33, 555l);
#if !defined(_MSC_VER) || _MSC_VER >= 1600
   CHECK2("9888777666", "%llu", 9888777666llu);
#endif
   CHECK4("-1 2 -3", "%ji %zi %ti", (intmax_t)-1, (ssize_t)2, (ptrdiff_t)-3);

   // floating-point numbers
   CHECK2("-3.000000", "%f", -3.0);
   CHECK2("-8.8888888800", "%.10f", -8.88888888);
   CHECK2("880.0888888800", "%.10f", 880.08888888);
   CHECK2("4.1", "%.1f", 4.1);
   CHECK2(" 0", "% .0f", 0.1);
   CHECK2("0.00", "%.2f", 1e-4);
   CHECK2("-5.20", "%+4.2f", -5.2);
   CHECK2("0.0       ", "%-10.1f", 0.);
   CHECK2("-0.000000", "%f", -0.);
   CHECK2("0.000001", "%f", 9.09834e-07);
#if USE_STB  // rounding differences
   CHECK2("38685626227668133600000000.0", "%.1f", pow_2_85);
   CHECK2("0.000000499999999999999978", "%.24f", 5e-7);
#else
   CHECK2("38685626227668133590597632.0", "%.1f", pow_2_85); // exact
   CHECK2("0.000000499999999999999977", "%.24f", 5e-7);
#endif
   CHECK2("0.000000000000000020000000", "%.24f", 2e-17);
   CHECK3("0.0000000100 100000000", "%.10f %.0f", 1e-8, 1e+8);
   CHECK2("100056789.0", "%.1f", 100056789.0);
   CHECK4(" 1.23 %", "%*.*f %%", 5, 2, 1.23);
   CHECK2("-3.000000e+00", "%e", -3.0);
   CHECK2("4.1E+00", "%.1E", 4.1);
   CHECK2("-5.20e+00", "%+4.2e", -5.2);
   CHECK3("+0.3 -3", "%+g %+g", 0.3, -3.0);
   CHECK2("4", "%.1G", 4.1);
   CHECK2("-5.2", "%+4.2g", -5.2);
   CHECK2("3e-300", "%g", 3e-300);
   CHECK2("1", "%.0g", 1.2);
   CHECK3(" 3.7 3.71", "% .3g %.3g", 3.704, 3.706);
   CHECK3("2e-315:1e+308", "%g:%g", 2e-315, 1e+308);

#if __STDC_VERSION__ >= 199901L
#if USE_STB
   CHECK4("Inf Inf NaN", "%g %G %f", INFINITY, INFINITY, NAN);
   CHECK2("N", "%.1g", NAN);
#else
   CHECK4("inf INF nan", "%g %G %f", INFINITY, INFINITY, NAN);
   CHECK2("nan", "%.1g", NAN);
#endif
#endif

   // %n
   CHECK3("aaa ", "%.3s %n", "aaaaaaaaaaaaa", &n);
   assert(n == 4);

#if __STDC_VERSION__ >= 199901L
   // hex floats
   CHECK2("0x1.fedcbap+98", "%a", 0x1.fedcbap+98);
   CHECK2("0x1.999999999999a0p-4", "%.14a", 0.1);
   CHECK2("0x1.0p-1022", "%.1a", 0x1.ffp-1023);
#if USE_STB  // difference in default precision and x vs X for %A
   CHECK2("0x1.009117p-1022", "%a", 2.23e-308);
   CHECK2("-0x1.AB0P-5", "%.3A", -0x1.abp-5);
#else
   CHECK2("0x1.0091177587f83p-1022", "%a", 2.23e-308);
   CHECK2("-0X1.AB0P-5", "%.3A", -0X1.abp-5);
#endif
#endif

   // %p
#if USE_STB
   CHECK2("0000000000000000", "%p", (void*) NULL);
#else
   CHECK2("(nil)", "%p", (void*) NULL);
#endif

   // snprintf
   assert(SNPRINTF(buf, 100, " %s     %d",  "b", 123) == 10);
   assert(strcmp(buf, " b     123") == 0);
   assert(SNPRINTF(buf, 100, "%f", pow_2_75) == 30);
   assert(strncmp(buf, "37778931862957161709568.000000", 17) == 0);
   n = SNPRINTF(buf, 10, "number %f", 123.456789);
   assert(strcmp(buf, "number 12") == 0);
   assert(n == 17);  // written vs would-be written bytes
   n = SNPRINTF(buf, 0, "7 chars");
   assert(n == 7);
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
   CHECK2("1,200,000", "%'d", 1200000);
   CHECK2("-100,006,789", "%'d", -100006789);
#if !defined(_MSC_VER) || _MSC_VER >= 1600
   CHECK2("9,888,777,666", "%'lld", 9888777666ll);
#endif
   CHECK2("200,000,000.000000", "%'18f", 2e8);
   CHECK2("100,056,789", "%'.0f", 100056789.0);
   CHECK2("100,056,789.0", "%'.1f", 100056789.0);
#if USE_STB  // difference in leading zeros
   CHECK2("000,001,200,000", "%'015d", 1200000);
#else
   CHECK2("0000001,200,000", "%'015d", 1200000);
#endif

   // things not supported by glibc
#if USE_STB
   CHECK2("null", "%s", (char*) NULL);
   CHECK2("123,4abc:", "%'x:", 0x1234ABC);
   CHECK2("100000000", "%b", 256);
   CHECK3("0b10 0B11", "%#b %#B", 2, 3);
#if !defined(_MSC_VER) || _MSC_VER >= 1600
   CHECK4("2 3 4", "%I64d %I32d %Id", 2ll, 3, 4ll);
#endif
   CHECK3("1k 2.54 M", "%$_d %$.2d", 1000, 2536000);
   CHECK3("2.42 Mi 2.4 M", "%$$.2d %$$$d", 2536000, 2536000);

   // different separators
   stbsp_set_separators(' ', ',');
   CHECK2("12 345,678900", "%'f", 12345.6789);
#endif

   return 0;
}
#endif
