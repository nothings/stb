// stb_dxt.h - v1.10 - DXT1/DXT5 compressor - public domain
// original by fabian "ryg" giesen - ported to C by stb
// use '#define STB_DXT_IMPLEMENTATION' before including to create the implementation
//
// USAGE:
//   call stb_compress_dxt_block() for every block (you must pad)
//     source should be a 4x4 block of RGBA data in row-major order;
//     Alpha channel is not stored if you specify alpha=0 (but you
//     must supply some constant alpha in the alpha channel).
//     You can turn on dithering and "high quality" using mode.
//
// version history:
//   v1.10  - (i.c) various small quality improvements
//   v1.09  - (stb) update documentation re: surprising alpha channel requirement
//   v1.08  - (stb) fix bug in dxt-with-alpha block
//   v1.07  - (stb) bc4; allow not using libc; add STB_DXT_STATIC
//   v1.06  - (stb) fix to known-broken 1.05
//   v1.05  - (stb) support bc5/3dc (Arvids Kokins), use extern "C" in C++ (Pavel Krajcevski)
//   v1.04  - (ryg) default to no rounding bias for lerped colors (as per S3TC/DX10 spec);
//            single color match fix (allow for inexact color interpolation);
//            optimal DXT5 index finder; "high quality" mode that runs multiple refinement steps.
//   v1.03  - (stb) endianness support
//   v1.02  - (stb) fix alpha encoding bug
//   v1.01  - (stb) fix bug converting to RGB that messed up quality, thanks ryg & cbloom
//   v1.00  - (stb) first release
//
// contributors:
//   Rich Geldreich (more accurate index selection)
//   Kevin Schmidt (#defines for "freestanding" compilation)
//   github:ppiastucki (BC4 support)
//   Ignacio Castano - improve DXT endpoint quantization
//   Alan Hickman - static table initialization
//
// LICENSE
//
//   See end of file for license information.

#ifndef STB_INCLUDE_STB_DXT_H
#define STB_INCLUDE_STB_DXT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_DXT_STATIC
#define STBDDEF static
#else
#define STBDDEF extern
#endif

// compression mode (bitflags)
#define STB_DXT_NORMAL    0
#define STB_DXT_DITHER    1   // use dithering. dubious win. never use for normal maps and the like!
#define STB_DXT_HIGHQUAL  2   // high quality mode, does two refinement steps instead of 1. ~30-40% slower.

STBDDEF void stb_compress_dxt_block(unsigned char *dest, const unsigned char *src_rgba_four_bytes_per_pixel, int alpha, int mode);
STBDDEF void stb_compress_bc4_block(unsigned char *dest, const unsigned char *src_r_one_byte_per_pixel);
STBDDEF void stb_compress_bc5_block(unsigned char *dest, const unsigned char *src_rg_two_byte_per_pixel);

#define STB_COMPRESS_DXT_BLOCK

#ifdef __cplusplus
}
#endif
#endif // STB_INCLUDE_STB_DXT_H

#ifdef STB_DXT_IMPLEMENTATION

// configuration options for DXT encoder. set them in the project/makefile or just define
// them at the top.

// STB_DXT_USE_ROUNDING_BIAS
//     use a rounding bias during color interpolation. this is closer to what "ideal"
//     interpolation would do but doesn't match the S3TC/DX10 spec. old versions (pre-1.03)
//     implicitly had this turned on.
//
//     in case you're targeting a specific type of hardware (e.g. console programmers):
//     NVidia and Intel GPUs (as of 2010) as well as DX9 ref use DXT decoders that are closer
//     to STB_DXT_USE_ROUNDING_BIAS. AMD/ATI, S3 and DX10 ref are closer to rounding with no bias.
//     you also see "(a*5 + b*3) / 8" on some old GPU designs.
// #define STB_DXT_USE_ROUNDING_BIAS

#include <stdlib.h>

#if !defined(STBI_FABS)
#include <math.h>
#endif

#ifndef STBD_FABS
#define STBD_FABS(x)          fabs(x)
#endif

#ifndef STBD_MEMSET
#include <string.h>
#define STBD_MEMSET           memset
#endif

static const unsigned char stb__QuantRBTab[256 + 16] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   8,   8,   8,
     8,   8,   8,   8,   8,  16,  16,  16,  16,  16,  16,  16,  16,  24,  24,  24,
    24,  24,  24,  24,  24,  33,  33,  33,  33,  33,  33,  33,  33,  33,  41,  41,
    41,  41,  41,  41,  41,  41,  49,  49,  49,  49,  49,  49,  49,  49,  57,  57,
    57,  57,  57,  57,  57,  57,  66,  66,  66,  66,  66,  66,  66,  66,  74,  74,
    74,  74,  74,  74,  74,  74,  74,  82,  82,  82,  82,  82,  82,  82,  82,  90,
    90,  90,  90,  90,  90,  90,  90,  99,  99,  99,  99,  99,  99,  99,  99, 107,
   107, 107, 107, 107, 107, 107, 107, 107, 115, 115, 115, 115, 115, 115, 115, 115,
   123, 123, 123, 123, 123, 123, 123, 123, 132, 132, 132, 132, 132, 132, 132, 132,
   140, 140, 140, 140, 140, 140, 140, 140, 148, 148, 148, 148, 148, 148, 148, 148,
   148, 156, 156, 156, 156, 156, 156, 156, 156, 165, 165, 165, 165, 165, 165, 165,
   165, 173, 173, 173, 173, 173, 173, 173, 173, 181, 181, 181, 181, 181, 181, 181,
   181, 181, 189, 189, 189, 189, 189, 189, 189, 189, 198, 198, 198, 198, 198, 198,
   198, 198, 206, 206, 206, 206, 206, 206, 206, 206, 214, 214, 214, 214, 214, 214,
   214, 214, 222, 222, 222, 222, 222, 222, 222, 222, 222, 231, 231, 231, 231, 231,
   231, 231, 231, 239, 239, 239, 239, 239, 239, 239, 239, 247, 247, 247, 247, 247,
   247, 247, 247, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};
static const unsigned char stb__QuantGTab[256 + 16] = {
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   4,   4,   4,   8,
     8,   8,   8,  12,  12,  12,  12,  16,  16,  16,  16,  20,  20,  20,  20,  24,
    24,  24,  24,  28,  28,  28,  28,  32,  32,  32,  32,  36,  36,  36,  36,  40,
    40,  40,  40,  44,  44,  44,  44,  48,  48,  48,  48,  52,  52,  52,  52,  56,
    56,  56,  56,  60,  60,  60,  60,  65,  65,  65,  65,  69,  69,  69,  69,  73,
    73,  73,  73,  77,  77,  77,  77,  81,  81,  81,  81,  85,  85,  85,  85,  85,
    89,  89,  89,  89,  93,  93,  93,  93,  97,  97,  97,  97, 101, 101, 101, 101,
   105, 105, 105, 105, 109, 109, 109, 109, 113, 113, 113, 113, 117, 117, 117, 117,
   121, 121, 121, 121, 125, 125, 125, 125, 130, 130, 130, 130, 134, 134, 134, 134,
   138, 138, 138, 138, 142, 142, 142, 142, 146, 146, 146, 146, 150, 150, 150, 150,
   154, 154, 154, 154, 158, 158, 158, 158, 162, 162, 162, 162, 166, 166, 166, 166,
   170, 170, 170, 170, 170, 174, 174, 174, 174, 178, 178, 178, 178, 182, 182, 182,
   182, 186, 186, 186, 186, 190, 190, 190, 190, 195, 195, 195, 195, 199, 199, 199,
   199, 203, 203, 203, 203, 207, 207, 207, 207, 211, 211, 211, 211, 215, 215, 215,
   215, 219, 219, 219, 219, 223, 223, 223, 223, 227, 227, 227, 227, 231, 231, 231,
   231, 235, 235, 235, 235, 239, 239, 239, 239, 243, 243, 243, 243, 247, 247, 247,
   247, 251, 251, 251, 251, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};
static const unsigned char stb__OMatch5[256][2] = {
   {  0,  0 }, {  0,  0 }, {  0,  1 }, {  0,  1 }, {  1,  0 }, {  1,  0 }, {  1,  0 }, {  1,  1 },
   {  1,  1 }, {  2,  0 }, {  2,  0 }, {  0,  4 }, {  2,  1 }, {  2,  1 }, {  2,  1 }, {  3,  0 },
   {  3,  0 }, {  3,  0 }, {  3,  1 }, {  1,  5 }, {  3,  2 }, {  3,  2 }, {  4,  0 }, {  4,  0 },
   {  4,  1 }, {  4,  1 }, {  4,  2 }, {  4,  2 }, {  4,  2 }, {  3,  5 }, {  5,  1 }, {  5,  1 },
   {  5,  2 }, {  4,  4 }, {  5,  3 }, {  5,  3 }, {  5,  3 }, {  6,  2 }, {  6,  2 }, {  6,  2 },
   {  6,  3 }, {  5,  5 }, {  6,  4 }, {  6,  4 }, {  4,  8 }, {  7,  3 }, {  7,  3 }, {  7,  3 },
   {  7,  4 }, {  7,  4 }, {  7,  4 }, {  7,  5 }, {  5,  9 }, {  7,  6 }, {  7,  6 }, {  8,  4 },
   {  8,  4 }, {  8,  5 }, {  8,  5 }, {  8,  6 }, {  8,  6 }, {  8,  6 }, {  7,  9 }, {  9,  5 },
   {  9,  5 }, {  9,  6 }, {  8,  8 }, {  9,  7 }, {  9,  7 }, {  9,  7 }, { 10,  6 }, { 10,  6 },
   { 10,  6 }, { 10,  7 }, {  9,  9 }, { 10,  8 }, { 10,  8 }, {  8, 12 }, { 11,  7 }, { 11,  7 },
   { 11,  7 }, { 11,  8 }, { 11,  8 }, { 11,  8 }, { 11,  9 }, {  9, 13 }, { 11, 10 }, { 11, 10 },
   { 12,  8 }, { 12,  8 }, { 12,  9 }, { 12,  9 }, { 12, 10 }, { 12, 10 }, { 12, 10 }, { 11, 13 },
   { 13,  9 }, { 13,  9 }, { 13, 10 }, { 12, 12 }, { 13, 11 }, { 13, 11 }, { 13, 11 }, { 14, 10 },
   { 14, 10 }, { 14, 10 }, { 14, 11 }, { 13, 13 }, { 14, 12 }, { 14, 12 }, { 12, 16 }, { 15, 11 },
   { 15, 11 }, { 15, 11 }, { 15, 12 }, { 15, 12 }, { 15, 12 }, { 15, 13 }, { 13, 17 }, { 15, 14 },
   { 15, 14 }, { 16, 12 }, { 16, 12 }, { 16, 13 }, { 16, 13 }, { 16, 14 }, { 16, 14 }, { 16, 14 },
   { 15, 17 }, { 17, 13 }, { 17, 13 }, { 17, 14 }, { 16, 16 }, { 17, 15 }, { 17, 15 }, { 17, 15 },
   { 18, 14 }, { 18, 14 }, { 18, 14 }, { 18, 15 }, { 17, 17 }, { 18, 16 }, { 18, 16 }, { 16, 20 },
   { 19, 15 }, { 19, 15 }, { 19, 15 }, { 19, 16 }, { 19, 16 }, { 19, 16 }, { 19, 17 }, { 17, 21 },
   { 19, 18 }, { 19, 18 }, { 20, 16 }, { 20, 16 }, { 20, 17 }, { 20, 17 }, { 20, 18 }, { 20, 18 },
   { 20, 18 }, { 19, 21 }, { 21, 17 }, { 21, 17 }, { 21, 18 }, { 20, 20 }, { 21, 19 }, { 21, 19 },
   { 21, 19 }, { 22, 18 }, { 22, 18 }, { 22, 18 }, { 22, 19 }, { 21, 21 }, { 22, 20 }, { 22, 20 },
   { 20, 24 }, { 23, 19 }, { 23, 19 }, { 23, 19 }, { 23, 20 }, { 23, 20 }, { 23, 20 }, { 23, 21 },
   { 21, 25 }, { 23, 22 }, { 23, 22 }, { 24, 20 }, { 24, 20 }, { 24, 21 }, { 24, 21 }, { 24, 22 },
   { 24, 22 }, { 24, 22 }, { 23, 25 }, { 25, 21 }, { 25, 21 }, { 25, 22 }, { 24, 24 }, { 25, 23 },
   { 25, 23 }, { 25, 23 }, { 26, 22 }, { 26, 22 }, { 26, 22 }, { 26, 23 }, { 25, 25 }, { 26, 24 },
   { 26, 24 }, { 24, 28 }, { 27, 23 }, { 27, 23 }, { 27, 23 }, { 27, 24 }, { 27, 24 }, { 27, 24 },
   { 27, 25 }, { 25, 29 }, { 27, 26 }, { 27, 26 }, { 28, 24 }, { 28, 24 }, { 28, 25 }, { 28, 25 },
   { 28, 26 }, { 28, 26 }, { 28, 26 }, { 27, 29 }, { 29, 25 }, { 29, 25 }, { 29, 26 }, { 28, 28 },
   { 29, 27 }, { 29, 27 }, { 29, 27 }, { 30, 26 }, { 30, 26 }, { 30, 26 }, { 30, 27 }, { 29, 29 },
   { 30, 28 }, { 30, 28 }, { 30, 28 }, { 31, 27 }, { 31, 27 }, { 31, 27 }, { 31, 28 }, { 31, 28 },
   { 31, 28 }, { 31, 29 }, { 31, 29 }, { 31, 30 }, { 31, 30 }, { 31, 30 }, { 31, 31 }, { 31, 31 },
};
static const unsigned char stb__OMatch6[256][2] = {
   {  0,  0 }, {  0,  1 }, {  1,  0 }, {  1,  0 }, {  1,  1 }, {  2,  0 }, {  2,  1 }, {  3,  0 },
   {  3,  0 }, {  3,  1 }, {  4,  0 }, {  4,  0 }, {  4,  1 }, {  5,  0 }, {  5,  1 }, {  6,  0 },
   {  6,  0 }, {  6,  1 }, {  7,  0 }, {  7,  0 }, {  7,  1 }, {  8,  0 }, {  8,  1 }, {  8,  1 },
   {  8,  2 }, {  9,  1 }, {  9,  2 }, {  9,  2 }, {  9,  3 }, { 10,  2 }, { 10,  3 }, { 10,  3 },
   { 10,  4 }, { 11,  3 }, { 11,  4 }, { 11,  4 }, { 11,  5 }, { 12,  4 }, { 12,  5 }, { 12,  5 },
   { 12,  6 }, { 13,  5 }, { 13,  6 }, {  8, 16 }, { 13,  7 }, { 14,  6 }, { 14,  7 }, {  9, 17 },
   { 14,  8 }, { 15,  7 }, { 15,  8 }, { 11, 16 }, { 15,  9 }, { 15, 10 }, { 16,  8 }, { 16,  9 },
   { 16, 10 }, { 15, 13 }, { 17,  9 }, { 17, 10 }, { 17, 11 }, { 15, 16 }, { 18, 10 }, { 18, 11 },
   { 18, 12 }, { 16, 16 }, { 19, 11 }, { 19, 12 }, { 19, 13 }, { 17, 17 }, { 20, 12 }, { 20, 13 },
   { 20, 14 }, { 19, 16 }, { 21, 13 }, { 21, 14 }, { 21, 15 }, { 20, 17 }, { 22, 14 }, { 22, 15 },
   { 25, 10 }, { 22, 16 }, { 23, 15 }, { 23, 16 }, { 26, 11 }, { 23, 17 }, { 24, 16 }, { 24, 17 },
   { 27, 12 }, { 24, 18 }, { 25, 17 }, { 25, 18 }, { 28, 13 }, { 25, 19 }, { 26, 18 }, { 26, 19 },
   { 29, 14 }, { 26, 20 }, { 27, 19 }, { 27, 20 }, { 30, 15 }, { 27, 21 }, { 28, 20 }, { 28, 21 },
   { 28, 21 }, { 28, 22 }, { 29, 21 }, { 29, 22 }, { 24, 32 }, { 29, 23 }, { 30, 22 }, { 30, 23 },
   { 25, 33 }, { 30, 24 }, { 31, 23 }, { 31, 24 }, { 27, 32 }, { 31, 25 }, { 31, 26 }, { 32, 24 },
   { 32, 25 }, { 32, 26 }, { 31, 29 }, { 33, 25 }, { 33, 26 }, { 33, 27 }, { 31, 32 }, { 34, 26 },
   { 34, 27 }, { 34, 28 }, { 32, 32 }, { 35, 27 }, { 35, 28 }, { 35, 29 }, { 33, 33 }, { 36, 28 },
   { 36, 29 }, { 36, 30 }, { 35, 32 }, { 37, 29 }, { 37, 30 }, { 37, 31 }, { 36, 33 }, { 38, 30 },
   { 38, 31 }, { 41, 26 }, { 38, 32 }, { 39, 31 }, { 39, 32 }, { 42, 27 }, { 39, 33 }, { 40, 32 },
   { 40, 33 }, { 43, 28 }, { 40, 34 }, { 41, 33 }, { 41, 34 }, { 44, 29 }, { 41, 35 }, { 42, 34 },
   { 42, 35 }, { 45, 30 }, { 42, 36 }, { 43, 35 }, { 43, 36 }, { 46, 31 }, { 43, 37 }, { 44, 36 },
   { 44, 37 }, { 44, 37 }, { 44, 38 }, { 45, 37 }, { 45, 38 }, { 40, 48 }, { 45, 39 }, { 46, 38 },
   { 46, 39 }, { 41, 49 }, { 46, 40 }, { 47, 39 }, { 47, 40 }, { 43, 48 }, { 47, 41 }, { 47, 42 },
   { 48, 40 }, { 48, 41 }, { 48, 42 }, { 47, 45 }, { 49, 41 }, { 49, 42 }, { 49, 43 }, { 47, 48 },
   { 50, 42 }, { 50, 43 }, { 50, 44 }, { 48, 48 }, { 51, 43 }, { 51, 44 }, { 51, 45 }, { 49, 49 },
   { 52, 44 }, { 52, 45 }, { 52, 46 }, { 51, 48 }, { 53, 45 }, { 53, 46 }, { 53, 47 }, { 52, 49 },
   { 54, 46 }, { 54, 47 }, { 57, 42 }, { 54, 48 }, { 55, 47 }, { 55, 48 }, { 58, 43 }, { 55, 49 },
   { 56, 48 }, { 56, 49 }, { 59, 44 }, { 56, 50 }, { 57, 49 }, { 57, 50 }, { 60, 45 }, { 57, 51 },
   { 58, 50 }, { 58, 51 }, { 61, 46 }, { 58, 52 }, { 59, 51 }, { 59, 52 }, { 62, 47 }, { 59, 53 },
   { 60, 52 }, { 60, 53 }, { 60, 53 }, { 60, 54 }, { 61, 53 }, { 61, 54 }, { 61, 54 }, { 61, 55 },
   { 62, 54 }, { 62, 55 }, { 62, 55 }, { 62, 56 }, { 63, 55 }, { 63, 56 }, { 63, 56 }, { 63, 57 },
   { 63, 58 }, { 63, 59 }, { 63, 59 }, { 63, 60 }, { 63, 61 }, { 63, 62 }, { 63, 62 }, { 63, 63 },
};

static int stb__Mul8Bit(int a, int b)
{
  int t = a*b + 128;
  return (t + (t >> 8)) >> 8;
}

static void stb__From16Bit(unsigned char *out, unsigned short v)
{
   int rv = (v & 0xf800) >> 11;
   int gv = (v & 0x07e0) >>  5;
   int bv = (v & 0x001f) >>  0;

   // expand to 8 bits via bit replication
   out[0] = (rv * 33) >> 2;
   out[1] = (gv * 65) >> 4;
   out[2] = (bv * 33) >> 2;
   out[3] = 0;
}

static unsigned short stb__As16Bit(int r, int g, int b)
{
   return (unsigned short)((stb__Mul8Bit(r,31) << 11) + (stb__Mul8Bit(g,63) << 5) + stb__Mul8Bit(b,31));
}

// linear interpolation at 1/3 point between a and b, using desired rounding type
static int stb__Lerp13(int a, int b)
{
#ifdef STB_DXT_USE_ROUNDING_BIAS
   // with rounding bias
   return a + stb__Mul8Bit(b-a, 0x55);
#else
   // without rounding bias
   // replace "/ 3" by "* 0xaaab) >> 17" if your compiler sucks or you really need every ounce of speed.
   return (2*a + b) / 3;
#endif
}

// lerp RGB color
static void stb__Lerp13RGB(unsigned char *out, unsigned char *p1, unsigned char *p2)
{
   out[0] = (unsigned char)stb__Lerp13(p1[0], p2[0]);
   out[1] = (unsigned char)stb__Lerp13(p1[1], p2[1]);
   out[2] = (unsigned char)stb__Lerp13(p1[2], p2[2]);
}

/****************************************************************************/

static void stb__EvalColors(unsigned char *color,unsigned short c0,unsigned short c1)
{
   stb__From16Bit(color+ 0, c0);
   stb__From16Bit(color+ 4, c1);
   stb__Lerp13RGB(color+ 8, color+0, color+4);
   stb__Lerp13RGB(color+12, color+4, color+0);
}

// Block dithering function. Simply dithers a block to 565 RGB.
// (Floyd-Steinberg)
static void stb__DitherBlock(unsigned char *dest, unsigned char *block)
{
  int err[8],*ep1 = err,*ep2 = err+4, *et;
  int ch,y;

  // process channels separately
  for (ch=0; ch<3; ++ch) {
      unsigned char *bp = block+ch, *dp = dest+ch;
      const unsigned char *quant = (ch == 1) ? stb__QuantGTab+8 : stb__QuantRBTab+8;
      STBD_MEMSET(err, 0, sizeof(err));
      for(y=0; y<4; ++y) {
         dp[ 0] = quant[bp[ 0] + ((3*ep2[1] + 5*ep2[0]) >> 4)];
         ep1[0] = bp[ 0] - dp[ 0];
         dp[ 4] = quant[bp[ 4] + ((7*ep1[0] + 3*ep2[2] + 5*ep2[1] + ep2[0]) >> 4)];
         ep1[1] = bp[ 4] - dp[ 4];
         dp[ 8] = quant[bp[ 8] + ((7*ep1[1] + 3*ep2[3] + 5*ep2[2] + ep2[1]) >> 4)];
         ep1[2] = bp[ 8] - dp[ 8];
         dp[12] = quant[bp[12] + ((7*ep1[2] + 5*ep2[3] + ep2[2]) >> 4)];
         ep1[3] = bp[12] - dp[12];
         bp += 16;
         dp += 16;
         et = ep1, ep1 = ep2, ep2 = et; // swap
      }
   }
}

// The color matching function
static unsigned int stb__MatchColorsBlock(unsigned char *block, unsigned char *color,int dither)
{
   unsigned int mask = 0;
   int dirr = color[0*4+0] - color[1*4+0];
   int dirg = color[0*4+1] - color[1*4+1];
   int dirb = color[0*4+2] - color[1*4+2];
   int dots[16];
   int stops[4];
   int i;
   int c0Point, halfPoint, c3Point;

   for(i=0;i<16;i++)
      dots[i] = block[i*4+0]*dirr + block[i*4+1]*dirg + block[i*4+2]*dirb;

   for(i=0;i<4;i++)
      stops[i] = color[i*4+0]*dirr + color[i*4+1]*dirg + color[i*4+2]*dirb;

   // think of the colors as arranged on a line; project point onto that line, then choose
   // next color out of available ones. we compute the crossover points for "best color in top
   // half"/"best in bottom half" and then the same inside that subinterval.
   //
   // relying on this 1d approximation isn't always optimal in terms of euclidean distance,
   // but it's very close and a lot faster.
   // http://cbloomrants.blogspot.com/2008/12/12-08-08-dxtc-summary.html

   c0Point   = (stops[1] + stops[3]);
   halfPoint = (stops[3] + stops[2]);
   c3Point   = (stops[2] + stops[0]);

   if(!dither) {
      // the version without dithering is straightforward
      for (i=15;i>=0;i--) {
         int dot = dots[i]*2;
         mask <<= 2;

         if(dot < halfPoint)
           mask |= (dot < c0Point) ? 1 : 3;
         else
           mask |= (dot < c3Point) ? 2 : 0;
      }
  } else {
      // with floyd-steinberg dithering
      int err[8],*ep1 = err,*ep2 = err+4;
      int *dp = dots, y;

      c0Point   <<= 3;
      halfPoint <<= 3;
      c3Point   <<= 3;
      for(i=0;i<8;i++)
         err[i] = 0;

      for(y=0;y<4;y++)
      {
         int dot,lmask,step;

         dot = (dp[0] << 4) + (3*ep2[1] + 5*ep2[0]);
         if(dot < halfPoint)
           step = (dot < c0Point) ? 1 : 3;
         else
           step = (dot < c3Point) ? 2 : 0;
         ep1[0] = dp[0] - stops[step];
         lmask = step;

         dot = (dp[1] << 4) + (7*ep1[0] + 3*ep2[2] + 5*ep2[1] + ep2[0]);
         if(dot < halfPoint)
           step = (dot < c0Point) ? 1 : 3;
         else
           step = (dot < c3Point) ? 2 : 0;
         ep1[1] = dp[1] - stops[step];
         lmask |= step<<2;

         dot = (dp[2] << 4) + (7*ep1[1] + 3*ep2[3] + 5*ep2[2] + ep2[1]);
         if(dot < halfPoint)
           step = (dot < c0Point) ? 1 : 3;
         else
           step = (dot < c3Point) ? 2 : 0;
         ep1[2] = dp[2] - stops[step];
         lmask |= step<<4;

         dot = (dp[3] << 4) + (7*ep1[2] + 5*ep2[3] + ep2[2]);
         if(dot < halfPoint)
           step = (dot < c0Point) ? 1 : 3;
         else
           step = (dot < c3Point) ? 2 : 0;
         ep1[3] = dp[3] - stops[step];
         lmask |= step<<6;

         dp += 4;
         mask |= lmask << (y*8);
         { int *et = ep1; ep1 = ep2; ep2 = et; } // swap
      }
   }

   return mask;
}

// The color optimization function. (Clever code, part 1)
static void stb__OptimizeColorsBlock(unsigned char *block, unsigned short *pmax16, unsigned short *pmin16)
{
  int mind,maxd;
  unsigned char *minp, *maxp;
  double magn;
  int v_r,v_g,v_b;
  static const int nIterPower = 4;
  float covf[6],vfr,vfg,vfb;

  // determine color distribution
  int cov[6];
  int mu[3],min[3],max[3];
  int ch,i,iter;

  for(ch=0;ch<3;ch++)
  {
    const unsigned char *bp = ((const unsigned char *) block) + ch;
    int muv,minv,maxv;

    muv = minv = maxv = bp[0];
    for(i=4;i<64;i+=4)
    {
      muv += bp[i];
      if (bp[i] < minv) minv = bp[i];
      else if (bp[i] > maxv) maxv = bp[i];
    }

    mu[ch] = (muv + 8) >> 4;
    min[ch] = minv;
    max[ch] = maxv;
  }

  // determine covariance matrix
  for (i=0;i<6;i++)
     cov[i] = 0;

  for (i=0;i<16;i++)
  {
    int r = block[i*4+0] - mu[0];
    int g = block[i*4+1] - mu[1];
    int b = block[i*4+2] - mu[2];

    cov[0] += r*r;
    cov[1] += r*g;
    cov[2] += r*b;
    cov[3] += g*g;
    cov[4] += g*b;
    cov[5] += b*b;
  }

  // convert covariance matrix to float, find principal axis via power iter
  for(i=0;i<6;i++)
    covf[i] = cov[i] / 255.0f;

  vfr = (float) (max[0] - min[0]);
  vfg = (float) (max[1] - min[1]);
  vfb = (float) (max[2] - min[2]);

  for(iter=0;iter<nIterPower;iter++)
  {
    float r = vfr*covf[0] + vfg*covf[1] + vfb*covf[2];
    float g = vfr*covf[1] + vfg*covf[3] + vfb*covf[4];
    float b = vfr*covf[2] + vfg*covf[4] + vfb*covf[5];

    vfr = r;
    vfg = g;
    vfb = b;
  }

  magn = STBD_FABS(vfr);
  if (STBD_FABS(vfg) > magn) magn = STBD_FABS(vfg);
  if (STBD_FABS(vfb) > magn) magn = STBD_FABS(vfb);

   if(magn < 4.0f) { // too small, default to luminance
      v_r = 299; // JPEG YCbCr luma coefs, scaled by 1000.
      v_g = 587;
      v_b = 114;
   } else {
      magn = 512.0 / magn;
      v_r = (int) (vfr * magn);
      v_g = (int) (vfg * magn);
      v_b = (int) (vfb * magn);
   }

   minp = maxp = block;
   mind = maxd = block[0]*v_r + block[1]*v_g + block[2]*v_b;
   // Pick colors at extreme points
   for(i=1;i<16;i++)
   {
      int dot = block[i*4+0]*v_r + block[i*4+1]*v_g + block[i*4+2]*v_b;

      if (dot < mind) {
         mind = dot;
         minp = block+i*4;
      }

      if (dot > maxd) {
         maxd = dot;
         maxp = block+i*4;
      }
   }

   *pmax16 = stb__As16Bit(maxp[0],maxp[1],maxp[2]);
   *pmin16 = stb__As16Bit(minp[0],minp[1],minp[2]);
}

static const float stb__midpoints5[32] = {
   0.015686f, 0.047059f, 0.078431f, 0.111765f, 0.145098f, 0.176471f, 0.207843f, 0.241176f, 0.274510f, 0.305882f, 0.337255f, 0.370588f, 0.403922f, 0.435294f, 0.466667f, 0.5f,
   0.533333f, 0.564706f, 0.596078f, 0.629412f, 0.662745f, 0.694118f, 0.725490f, 0.758824f, 0.792157f, 0.823529f, 0.854902f, 0.888235f, 0.921569f, 0.952941f, 0.984314f, 1.0f
};

static const float stb__midpoints6[64] = {
   0.007843f, 0.023529f, 0.039216f, 0.054902f, 0.070588f, 0.086275f, 0.101961f, 0.117647f, 0.133333f, 0.149020f, 0.164706f, 0.180392f, 0.196078f, 0.211765f, 0.227451f, 0.245098f,
   0.262745f, 0.278431f, 0.294118f, 0.309804f, 0.325490f, 0.341176f, 0.356863f, 0.372549f, 0.388235f, 0.403922f, 0.419608f, 0.435294f, 0.450980f, 0.466667f, 0.482353f, 0.500000f,
   0.517647f, 0.533333f, 0.549020f, 0.564706f, 0.580392f, 0.596078f, 0.611765f, 0.627451f, 0.643137f, 0.658824f, 0.674510f, 0.690196f, 0.705882f, 0.721569f, 0.737255f, 0.754902f,
   0.772549f, 0.788235f, 0.803922f, 0.819608f, 0.835294f, 0.850980f, 0.866667f, 0.882353f, 0.898039f, 0.913725f, 0.929412f, 0.945098f, 0.960784f, 0.976471f, 0.992157f, 1.0f
};

static unsigned short stb__Quantize5(float x)
{
   unsigned short q;
   x = x < 0 ? 0 : x > 1 ? 1 : x;  // saturate
   q = (unsigned short)(x * 31);
   q += (x > stb__midpoints5[q]);
   return q;
}

static unsigned short stb__Quantize6(float x)
{
   unsigned short q;
   x = x < 0 ? 0 : x > 1 ? 1 : x;  // saturate
   q = (unsigned short)(x * 63);
   q += (x > stb__midpoints6[q]);
   return q;
}

// The refinement function. (Clever code, part 2)
// Tries to optimize colors to suit block contents better.
// (By solving a least squares system via normal equations+Cramer's rule)
static int stb__RefineBlock(unsigned char *block, unsigned short *pmax16, unsigned short *pmin16, unsigned int mask)
{
   static const int w1Tab[4] = { 3,0,2,1 };
   static const int prods[4] = { 0x090000,0x000900,0x040102,0x010402 };
   // ^some magic to save a lot of multiplies in the accumulating loop...
   // (precomputed products of weights for least squares system, accumulated inside one 32-bit register)

   float f;
   unsigned short oldMin, oldMax, min16, max16;
   int i, akku = 0, xx,xy,yy;
   int At1_r,At1_g,At1_b;
   int At2_r,At2_g,At2_b;
   unsigned int cm = mask;

   oldMin = *pmin16;
   oldMax = *pmax16;

   if((mask ^ (mask<<2)) < 4) // all pixels have the same index?
   {
      // yes, linear system would be singular; solve using optimal
      // single-color match on average color
      int r = 8, g = 8, b = 8;
      for (i=0;i<16;++i) {
         r += block[i*4+0];
         g += block[i*4+1];
         b += block[i*4+2];
      }

      r >>= 4; g >>= 4; b >>= 4;

      max16 = (stb__OMatch5[r][0]<<11) | (stb__OMatch6[g][0]<<5) | stb__OMatch5[b][0];
      min16 = (stb__OMatch5[r][1]<<11) | (stb__OMatch6[g][1]<<5) | stb__OMatch5[b][1];
   } else {
      At1_r = At1_g = At1_b = 0;
      At2_r = At2_g = At2_b = 0;
      for (i=0;i<16;++i,cm>>=2) {
         int step = cm&3;
         int w1 = w1Tab[step];
         int r = block[i*4+0];
         int g = block[i*4+1];
         int b = block[i*4+2];

         akku    += prods[step];
         At1_r   += w1*r;
         At1_g   += w1*g;
         At1_b   += w1*b;
         At2_r   += r;
         At2_g   += g;
         At2_b   += b;
      }

      At2_r = 3*At2_r - At1_r;
      At2_g = 3*At2_g - At1_g;
      At2_b = 3*At2_b - At1_b;

      // extract solutions and decide solvability
      xx = akku >> 16;
      yy = (akku >> 8) & 0xff;
      xy = (akku >> 0) & 0xff;

      f = 3.0f / 255.0f / (xx*yy - xy*xy);

      max16 =  stb__Quantize5((At1_r*yy - At2_r * xy) * f) << 11;
      max16 |= stb__Quantize6((At1_g*yy - At2_g * xy) * f) << 5;
      max16 |= stb__Quantize5((At1_b*yy - At2_b * xy) * f) << 0;

      min16 =  stb__Quantize5((At2_r*xx - At1_r * xy) * f) << 11;
      min16 |= stb__Quantize6((At2_g*xx - At1_g * xy) * f) << 5;
      min16 |= stb__Quantize5((At2_b*xx - At1_b * xy) * f) << 0;
   }

   *pmin16 = min16;
   *pmax16 = max16;
   return oldMin != min16 || oldMax != max16;
}

// Color block compression
static void stb__CompressColorBlock(unsigned char *dest, unsigned char *block, int mode)
{
   unsigned int mask;
   int i;
   int dither;
   int refinecount;
   unsigned short max16, min16;
   unsigned char dblock[16*4],color[4*4];

   dither = mode & STB_DXT_DITHER;
   refinecount = (mode & STB_DXT_HIGHQUAL) ? 2 : 1;

   // check if block is constant
   for (i=1;i<16;i++)
      if (((unsigned int *) block)[i] != ((unsigned int *) block)[0])
         break;

   if(i == 16) { // constant color
      int r = block[0], g = block[1], b = block[2];
      mask  = 0xaaaaaaaa;
      max16 = (stb__OMatch5[r][0]<<11) | (stb__OMatch6[g][0]<<5) | stb__OMatch5[b][0];
      min16 = (stb__OMatch5[r][1]<<11) | (stb__OMatch6[g][1]<<5) | stb__OMatch5[b][1];
   } else {
      // first step: compute dithered version for PCA if desired
      if(dither)
         stb__DitherBlock(dblock,block);

      // second step: pca+map along principal axis
      stb__OptimizeColorsBlock(dither ? dblock : block,&max16,&min16);
      if (max16 != min16) {
         stb__EvalColors(color,max16,min16);
         mask = stb__MatchColorsBlock(block,color,dither);
      } else
         mask = 0;

      // third step: refine (multiple times if requested)
      for (i=0;i<refinecount;i++) {
         unsigned int lastmask = mask;

         if (stb__RefineBlock(dither ? dblock : block,&max16,&min16,mask)) {
            if (max16 != min16) {
               stb__EvalColors(color,max16,min16);
               mask = stb__MatchColorsBlock(block,color,dither);
            } else {
               mask = 0;
               break;
            }
         }

         if(mask == lastmask)
            break;
      }
  }

  // write the color block
  if(max16 < min16)
  {
     unsigned short t = min16;
     min16 = max16;
     max16 = t;
     mask ^= 0x55555555;
  }

  dest[0] = (unsigned char) (max16);
  dest[1] = (unsigned char) (max16 >> 8);
  dest[2] = (unsigned char) (min16);
  dest[3] = (unsigned char) (min16 >> 8);
  dest[4] = (unsigned char) (mask);
  dest[5] = (unsigned char) (mask >> 8);
  dest[6] = (unsigned char) (mask >> 16);
  dest[7] = (unsigned char) (mask >> 24);
}

// Alpha block compression (this is easy for a change)
static void stb__CompressAlphaBlock(unsigned char *dest,unsigned char *src, int stride)
{
   int i,dist,bias,dist4,dist2,bits,mask;

   // find min/max color
   int mn,mx;
   mn = mx = src[0];

   for (i=1;i<16;i++)
   {
      if (src[i*stride] < mn) mn = src[i*stride];
      else if (src[i*stride] > mx) mx = src[i*stride];
   }

   // encode them
   dest[0] = (unsigned char)mx;
   dest[1] = (unsigned char)mn;
   dest += 2;

   // determine bias and emit color indices
   // given the choice of mx/mn, these indices are optimal:
   // http://fgiesen.wordpress.com/2009/12/15/dxt5-alpha-block-index-determination/
   dist = mx-mn;
   dist4 = dist*4;
   dist2 = dist*2;
   bias = (dist < 8) ? (dist - 1) : (dist/2 + 2);
   bias -= mn * 7;
   bits = 0,mask=0;

   for (i=0;i<16;i++) {
      int a = src[i*stride]*7 + bias;
      int ind,t;

      // select index. this is a "linear scale" lerp factor between 0 (val=min) and 7 (val=max).
      t = (a >= dist4) ? -1 : 0; ind =  t & 4; a -= dist4 & t;
      t = (a >= dist2) ? -1 : 0; ind += t & 2; a -= dist2 & t;
      ind += (a >= dist);

      // turn linear scale into DXT index (0/1 are extremal pts)
      ind = -ind & 7;
      ind ^= (2 > ind);

      // write index
      mask |= ind << bits;
      if((bits += 3) >= 8) {
         *dest++ = (unsigned char)mask;
         mask >>= 8;
         bits -= 8;
      }
   }
}

void stb_compress_dxt_block(unsigned char *dest, const unsigned char *src, int alpha, int mode)
{
   unsigned char data[16][4];
   if (alpha) {
      int i;
      stb__CompressAlphaBlock(dest,(unsigned char*) src+3, 4);
      dest += 8;
      // make a new copy of the data in which alpha is opaque,
      // because code uses a fast test for color constancy
      memcpy(data, src, 4*16);
      for (i=0; i < 16; ++i)
         data[i][3] = 255;
      src = &data[0][0];
   }

   stb__CompressColorBlock(dest,(unsigned char*) src,mode);
}

void stb_compress_bc4_block(unsigned char *dest, const unsigned char *src)
{
   stb__CompressAlphaBlock(dest,(unsigned char*) src, 1);
}

void stb_compress_bc5_block(unsigned char *dest, const unsigned char *src)
{
   stb__CompressAlphaBlock(dest,(unsigned char*) src,2);
   stb__CompressAlphaBlock(dest + 8,(unsigned char*) src+1,2);
}
#endif // STB_DXT_IMPLEMENTATION

// Compile with STB_DXT_IMPLEMENTATION and STB_DXT_GENERATE_TABLES
// defined to generate the tables above.
#ifdef STB_DXT_GENERATE_TABLES
#include <stdio.h>

int main()
{
   int i, j;
   const char *quant_names[] = { "stb__QuantRBTab", "stb__QuantGTab" };
   const char *omatch_names[] = { "stb__OMatch5", "stb__OMatch6" };
   int dequant_mults[2] = { 33*4, 65 }; // .4 fixed-point dequant multipliers

   // quant tables (for dither)
   for (i=0; i < 2; ++i) {
      int quant_mult = i ? 63 : 31;
      printf("static const unsigned char %s[256 + 16] = {\n", quant_names[i]);
      for (int j = 0; j < 256 + 16; ++j) {
         int v = j - 8;
         int q, dq;

         v = (v < 0) ? 0 : (v > 255) ? 255 : v; // clamp
         q = stb__Mul8Bit(v, quant_mult); // quantize
         dq = (q * dequant_mults[i]) >> 4; // dequantize

         if ((j % 16) == 0) printf("  "); // 2 spaces, third is done below
         printf(" %3d,", dq);
         if ((j % 16) == 15) printf("\n");
      }
      printf("};\n");
   }

   // optimal endpoint tables
   for (i = 0; i < 2; ++i) {
      int dequant = dequant_mults[i];
      int size = i ? 64 : 32;
      printf("static const unsigned char %s[256][2] = {\n", omatch_names[i]);
      for (int j = 0; j < 256; ++j) {
         int mn, mx;
         int best_mn = 0, best_mx = 0;
         int best_err = 256;
         for (mn=0;mn<size;mn++) {
            for (mx=0;mx<size;mx++) {
               int mine = (mn * dequant) >> 4;
               int maxe = (mx * dequant) >> 4;
               int err = abs(stb__Lerp13(maxe, mine) - j);

               // DX10 spec says that interpolation must be within 3% of "correct" result,
               // add this as error term. Normally we'd expect a random distribution of
               // +-1.5% error, but nowhere in the spec does it say that the error has to be
               // unbiased - better safe than sorry.
               err += abs(maxe - mine) * 3 / 100;

               if(err < best_err) {
                  best_mn = mn;
                  best_mx = mx;
                  best_err = err;
               }
            }
         }
         if ((j % 8) == 0) printf("  "); // 2 spaces, third is done below
         printf(" { %2d, %2d },", best_mx, best_mn);
         if ((j % 8) == 7) printf("\n");
      }
      printf("};\n");
   }

   return 0;
}
#endif

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
