/* stb_gif - v0.50 - public domain gif loader - http://nothings.org/stb
                                  no warranty implied; use at your own risk

   Do this:
      #define STBGIF_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   // i.e. it should look like this:
   #include ...
   #include ...
   #include ...
   #define STBGIF_IMPLEMENTATION
   #include "stb_gif.h"

   You can #define STBGIF_ASSERT(x) before the #include to avoid using assert.h.
   And #define STBGIF_MALLOC, STBGIF_REALLOC, and STBGIF_FREE to avoid using malloc,realloc,free

   QUICK NOTES:
      Primarily of interest to game developers and other people who can
          avoid problematic images and only need the trivial interface

      - *comp always reports as 4-channel
      - decode from memory or through FILE (define STBGIF_NO_STDIO to remove code)
      - decode from arbitrary I/O callbacks

   Full documentation under "DOCUMENTATION" below.

LICENSE

  See end of file for license information.

RECENT REVISION HISTORY:

      0.50  (2020-09-03) 
              first released version; created from stb_image.h v2.26

   See end of file for full revision history.


=============================    Contributors    =========================

Jean-Marc Lienher (gif)
github:urraka (animated gif)
Christopher Forseth (animated gif)
github:lokno (creation of stand-alone stb_gif header)

====================    stb_image v2.26 Contributors    ==================

 Image formats                          Extensions, features
    Sean Barrett (jpeg, png, bmp)          Jetro Lauha (stbi_info)
    Nicolas Schulz (hdr, psd)              Martin "SpartanJ" Golini (stbi_info)
    Jonathan Dummer (tga)                  James "moose2000" Brown (iPhone PNG)
    Jean-Marc Lienher (gif)                Ben "Disch" Wenger (io callbacks)
    Tom Seddon (pic)                       Omar Cornut (1/2/4-bit PNG)
    Thatcher Ulrich (psd)                  Nicolas Guillemot (vertical flip)
    Ken Miller (pgm, ppm)                  Richard Mitton (16-bit PSD)
    github:urraka (animated gif)           Junggon Kim (PNM comments)
    Christopher Forseth (animated gif)     Daniel Gibson (16-bit TGA)
                                           socks-the-fox (16-bit PNG)
                                           Jeremy Sawicki (handle all ImageNet JPGs)
 Optimizations & bugfixes                  Mikhail Morozov (1-bit BMP)
    Fabian "ryg" Giesen                    Anael Seghezzi (is-16-bit query)
    Arseny Kapoulkine
    John-Mark Allen
    Carmelo J Fdez-Aguera

 Bug & warning fixes
    Marc LeBlanc            David Woo          Guillaume George     Martins Mozeiko
    Christpher Lloyd        Jerry Jansson      Joseph Thomson       Blazej Dariusz Roszkowski
    Phil Jordan                                Dave Moore           Roy Eltham
    Hayaki Saito            Nathan Reed        Won Chun
    Luke Graham             Johan Duparc       Nick Verigakis       the Horde3D community
    Thomas Ruf              Ronny Chevalier                         github:rlyeh
    Janez Zemva             John Bartholomew   Michal Cichon        github:romigrou
    Jonathan Blow           Ken Hamada         Tero Hanninen        github:svdijk
                            Laurent Gomila     Cort Stratton        github:snagar
    Aruelien Pocheville     Sergio Gonzalez    Thibault Reuille     github:Zelex
    Cass Everitt            Ryamond Barbiero                        github:grim210
    Paul Du Bois            Engin Manap        Aldo Culquicondor    github:sammyhw
    Philipp Wiesemann       Dale Weiler        Oriol Ferrer Mesia   github:phprus
    Josh Tobin                                 Matthew Gregan       github:poppolopoppo
    Julian Raschke          Gregory Mullen     Christian Floisand   github:darealshinji
    Baldur Karlsson         Kevin Schmidt      JR Smith             github:Michaelangel007
                            Brad Weinberger    Matvey Cherevko      [reserved]
    Luca Sas                Alexander Veselov  Zack Middleton       [reserved]
    Ryan C. Gordon          [reserved]                              [reserved]
                     DO NOT ADD YOUR NAME HERE

  To add your name to the credits, pick a random blank space in the middle and fill it.
  80% of merge conflicts on stb PRs are due to people adding their name at the end
  of the credits.
*/   

#ifndef STBGIF_INCLUDE_STB_H
#define STBGIF_INCLUDE_STB_H

// DOCUMENTATION
//
// Limitations:
//    - GIF always returns *comp=4
//
// Basic usage:
//    int x,y,z,comp,*delays;
//    unsigned char *data = stbgif_load(filename, &delays, &x, &y, &z, &comp, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, z = frames, delays = array of delay for each frame, comp = # components
//    // ... currently comp = 4
//    stbgif_image_free(data)

#ifndef STBGIF_NO_STDIO
#include <stdio.h>
#endif // STBGIF_NO_STDIO

#define STBGIF_VERSION 0.5

#include <stdlib.h>
typedef unsigned char stbgif_uc;

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STBGIFDEF
#ifdef STBGIF_STATIC
#define STBGIFDEF static
#else
#define STBGIFDEF extern
#endif
#endif

//////////////////////////////////////////////////////////////////////////////
//
// PRIMARY API 
//

//
// load image by filename, open file, callback, or memory buffer
//

typedef struct
{
   int      (*read)  (void *user,char *data,int size);   // fill 'data' with 'size' bytes.  return number of bytes actually read
   void     (*skip)  (void *user,int n);                 // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
   int      (*eof)   (void *user);                       // returns nonzero if we are at end of file/data
} stbgif_io_callbacks;

#ifdef _MSC_VER
typedef unsigned short stbgif__uint16;
typedef   signed short stbgif__int16;
typedef unsigned int   stbgif__uint32;
typedef   signed int   stbgif__int32;
#else
#include <stdint.h>
typedef uint16_t stbgif__uint16;
typedef int16_t  stbgif__int16;
typedef uint32_t stbgif__uint32;
typedef int32_t  stbgif__int32;
#endif

#ifdef _MSC_VER
#define STBGIF_NOTUSED(v)  (void)(v)
#else
#define STBGIF_NOTUSED(v)  (void)sizeof(v)
#endif

#if defined(STBGIF_MALLOC) && defined(STBGIF_FREE) && (defined(STBGIF_REALLOC) || defined(STBGIF_REALLOC_SIZED))
// ok
#elif !defined(STBGIF_MALLOC) && !defined(STBGIF_FREE) && !defined(STBGIF_REALLOC) && !defined(STBGIF_REALLOC_SIZED)
// ok
#else
#error "Must define all or none of STBGIF_MALLOC, STBGIF_FREE, and STBGIF_REALLOC (or STBGIF_REALLOC_SIZED)."
#endif

#ifndef STBGIF_MALLOC
#define STBGIF_MALLOC(sz)           malloc(sz)
#define STBGIF_REALLOC(p,newsz)     realloc(p,newsz)
#define STBGIF_FREE(p)              free(p)
#endif

#ifndef STBGIF_REALLOC_SIZED
#define STBGIF_REALLOC_SIZED(p,oldsz,newsz) STBGIF_REALLOC(p,newsz)
#endif

STBGIFDEF stbgif_uc *stbgif_load_from_memory(stbgif_uc const *buffer, int len, int **delays, int *x, int *y, int *z, int *comp, int req_comp);
STBGIFDEF stbgif_uc *stbgif_load_from_callbacks(stbgif_io_callbacks const *clbk, void *user, int** delays, int *x, int *y, int *z, int *comp, int req_comp);

#ifndef STBI_NO_STDIO
STBGIFDEF stbgif_uc *stbgif_load            (char const *filename, int** delays, int *x, int *y, int *z, int *channels_in_file, int desired_channels);
STBGIFDEF stbgif_uc *stbgif_load_from_file  (FILE *f, int** delays, int *x, int *y, int*z, int *channels_in_file, int desired_channels);
// for stbgif_load_from_file, file pointer is left pointing immediately after image
#endif

STBGIFDEF void stbgif_info_from_memory(stbgif_uc const *buffer, int len, int *x, int *y, int *comp);
STBGIFDEF int stbgif_info_from_callbacks(stbgif_io_callbacks const *c, void *user, int *x, int *y, int *comp);

#ifndef STBI_NO_STDIO
STBGIFDEF int      stbgif_info               (char const *filename,     int *x, int *y, int *comp);
STBGIFDEF int      stbgif_info_from_file     (FILE *f,                  int *x, int *y, int *comp);
#endif

#ifdef __cplusplus
}
#endif

//
//
////   end header file   /////////////////////////////////////////////////////
#endif // STBGIF_INCLUDE_STB_H

#ifdef STBGIF_IMPLEMENTATION

#include <limits.h>
#include <string.h>

#ifndef STBGIF_NO_STDIO
#include <stdio.h>
#endif

#ifndef STBGIF_ASSERT
#include <assert.h>
#define STBGIF_ASSERT(x) assert(x)
#endif

#ifdef __cplusplus
#define STBGIF_EXTERN extern "C"
#else
#define STBGIF_EXTERN extern
#endif

#ifndef _MSC_VER
   #ifdef __cplusplus
   #define stbgif_inline inline
   #else
   #define stbgif_inline
   #endif
#else
   #define stbgif_inline __forceinline
#endif

#ifndef STBGIF_MAX_DIMENSIONS
#define STBGIF_MAX_DIMENSIONS (1 << 24)
#endif

///////////////////////////////////////////////
//
//  stbgif__context struct and start_xxx functions

// stbgif__context structure is our basic context, so it
// contains all the IO context, plus some basic image information
typedef struct
{
   int img_n;

   stbgif_io_callbacks io;
   void *io_user_data;

   int read_from_callbacks;
   int buflen;
   stbgif_uc buffer_start[128];
   int callback_already_read;

   stbgif_uc *img_buffer, *img_buffer_end;
   stbgif_uc *img_buffer_original, *img_buffer_original_end;
} stbgif__context;

static void stbgif__refill_buffer(stbgif__context *s);

// initialize a memory-decode context
static void stbgif__start_mem(stbgif__context *s, stbgif_uc const *buffer, int len)
{
   s->io.read = NULL;
   s->read_from_callbacks = 0;
   s->callback_already_read = 0;
   s->img_buffer = s->img_buffer_original = (stbgif_uc *) buffer;
   s->img_buffer_end = s->img_buffer_original_end = (stbgif_uc *) buffer+len;
}

// initialize a callback-based context
static void stbgif__start_callbacks(stbgif__context *s, stbgif_io_callbacks *c, void *user)
{
   s->io = *c;
   s->io_user_data = user;
   s->buflen = sizeof(s->buffer_start);
   s->read_from_callbacks = 1;
   s->callback_already_read = 0;
   s->img_buffer = s->img_buffer_original = s->buffer_start;
   stbgif__refill_buffer(s);
   s->img_buffer_original_end = s->img_buffer_end;
}

#ifndef STBGIF_NO_STDIO

static int stbgif__stdio_read(void *user, char *data, int size)
{
   return (int) fread(data,1,size,(FILE*) user);
}

static void stbgif__stdio_skip(void *user, int n)
{
   int ch;
   fseek((FILE*) user, n, SEEK_CUR);
   ch = fgetc((FILE*) user);  /* have to read a byte to reset feof()'s flag */
   if (ch != EOF) {
      ungetc(ch, (FILE *) user);  /* push byte back onto stream if valid. */
   }
}

static int stbgif__stdio_eof(void *user)
{
   return feof((FILE*) user) || ferror((FILE *) user);
}

static stbgif_io_callbacks stbgif__stdio_callbacks =
{
   stbgif__stdio_read,
   stbgif__stdio_skip,
   stbgif__stdio_eof,
};

static void stbgif__start_file(stbgif__context *s, FILE *f)
{
   stbgif__start_callbacks(s, &stbgif__stdio_callbacks, (void *) f);
}

#endif // !STBGIF_NO_STDIO

static void stbgif__rewind(stbgif__context *s)
{
   // conceptually rewind SHOULD rewind to the beginning of the stream,
   // but we just rewind to the beginning of the initial buffer, because
   // we only use it after doing 'test', which only ever looks at at most 92 bytes
   s->img_buffer = s->img_buffer_original;
   s->img_buffer_end = s->img_buffer_original_end;
}

static int      stbgif_test(stbgif__context *s);
static void    *stbgif__load_first_layer(stbgif__context *s, int *x, int *y, int *comp, int req_comp);
static void    *stbgif__load_main(stbgif__context *s, int **delays, int *x, int *y, int *z, int *comp, int req_comp);
static int      stbgif__info(stbgif__context *s, int *x, int *y, int *comp);

const char *stbgif__g_failure_reason;

STBGIFDEF const char *stbgif_failure_reason(void)
{
   return stbgif__g_failure_reason;
}

#ifndef STBGIF_NO_FAILURE_STRINGS
static int stbgif__err(const char *str)
{
   stbgif__g_failure_reason = str;
   return 0;
}
#endif

static void *stbgif__malloc(size_t size)
{
    return STBGIF_MALLOC(size);
}

// stb_gif uses ints pervasively, including for offset calculations.
// therefore the largest decoded image size we can support with the
// current code, even on 64-bit targets, is INT_MAX. this is not a
// significant limitation for the intended use case.
//
// we do, however, need to make sure our size calculations don't
// overflow. hence a few helper functions for size calculations that
// multiply integers together, making sure that they're non-negative
// and no overflow occurs.

// return 1 if the sum is valid, 0 on overflow.
// negative terms are considered invalid.
static int stbgif__addsizes_valid(int a, int b)
{
   if (b < 0) return 0;
   // now 0 <= b <= INT_MAX, hence also
   // 0 <= INT_MAX - b <= INTMAX.
   // And "a + b <= INT_MAX" (which might overflow) is the
   // same as a <= INT_MAX - b (no overflow)
   return a <= INT_MAX - b;
}

// returns 1 if the product is valid, 0 on overflow.
// negative factors are considered invalid.
static int stbgif__mul2sizes_valid(int a, int b)
{
   if (a < 0 || b < 0) return 0;
   if (b == 0) return 1; // mul-by-0 is always safe
   // portable way to check for no overflows in a*b
   return a <= INT_MAX/b;
}

// returns 1 if "a*b*c + add" has no negative terms/factors and doesn't overflow
static int stbgif__mad3sizes_valid(int a, int b, int c, int add)
{
   return stbgif__mul2sizes_valid(a, b) && stbgif__mul2sizes_valid(a*b, c) &&
      stbgif__addsizes_valid(a*b*c, add);
}

static void *stbgif__malloc_mad3(int a, int b, int c, int add)
{
   if (!stbgif__mad3sizes_valid(a, b, c, add)) return NULL;
   return stbgif__malloc(a*b*c + add);
}

// stbgif__err - error
// stbgif__errpf - error returning pointer to float
// stbgif__errpuc - error returning pointer to unsigned char

#ifdef STBGIF_NO_FAILURE_STRINGS
   #define stbgif__err(x,y)  0
#elif defined(STBGIF_FAILURE_USERMSG)
   #define stbgif__err(x,y)  stbgif__err(y)
#else
   #define stbgif__err(x,y)  stbgif__err(x)
#endif

#define stbgif__errpf(x,y)   ((float *)(size_t) (stbgif__err(x,y)?NULL:NULL))
#define stbgif__errpuc(x,y)  ((unsigned char *)(size_t) (stbgif__err(x,y)?NULL:NULL))

STBGIFDEF void stbgif_image_free(void *retval_from_stbgif_load)
{
   STBGIF_FREE(retval_from_stbgif_load);
}

static int stbgif__vertically_flip_on_load_global = 0;

STBGIFDEF void stbgif_set_flip_vertically_on_load(int flag_true_if_should_flip)
{
   stbgif__vertically_flip_on_load_global = flag_true_if_should_flip;
}

#ifndef STBI_THREAD_LOCAL
#define stbgif__vertically_flip_on_load  stbgif__vertically_flip_on_load_global
#else
static STBI_THREAD_LOCAL int stbgif__vertically_flip_on_load_local, stbgif__vertically_flip_on_load_set;

STBGIFDEF void stbgif_set_flip_vertically_on_load_thread(int flag_true_if_should_flip)
{
   stbgif__vertically_flip_on_load_local = flag_true_if_should_flip;
   stbgif__vertically_flip_on_load_set = 1;
}

#define stbgif__vertically_flip_on_load  (stbgif__vertically_flip_on_load_set       \
                                         ? stbgif__vertically_flip_on_load_local  \
                                         : stbgif__vertically_flip_on_load_global)
#endif // STBI_THREAD_LOCAL

static void stbgif__skip(stbgif__context *s, int n)
{
   if (n == 0) return;  // already there!
   if (n < 0) {
      s->img_buffer = s->img_buffer_end;
      return;
   }
   if (s->io.read) {
      int blen = (int) (s->img_buffer_end - s->img_buffer);
      if (blen < n) {
         s->img_buffer = s->img_buffer_end;
         (s->io.skip)(s->io_user_data, n - blen);
         return;
      }
   }
   s->img_buffer += n;
}


static void stbgif__vertical_flip(void *image, int w, int h, int bytes_per_pixel)
{
   int row;
   size_t bytes_per_row = (size_t)w * bytes_per_pixel;
   stbgif_uc temp[2048];
   stbgif_uc *bytes = (stbgif_uc *)image;

   for (row = 0; row < (h>>1); row++) {
      stbgif_uc *row0 = bytes + row*bytes_per_row;
      stbgif_uc *row1 = bytes + (h - row - 1)*bytes_per_row;
      // swap row0 with row1
      size_t bytes_left = bytes_per_row;
      while (bytes_left) {
         size_t bytes_copy = (bytes_left < sizeof(temp)) ? bytes_left : sizeof(temp);
         memcpy(temp, row0, bytes_copy);
         memcpy(row0, row1, bytes_copy);
         memcpy(row1, temp, bytes_copy);
         row0 += bytes_copy;
         row1 += bytes_copy;
         bytes_left -= bytes_copy;
      }
   }
}

static void stbgif__vertical_flip_slices(void *image, int w, int h, int z, int bytes_per_pixel)
{
   int slice;
   int slice_size = w * h * bytes_per_pixel;

   stbgif_uc *bytes = (stbgif_uc *)image;
   for (slice = 0; slice < z; ++slice) {
      stbgif__vertical_flip(bytes, w, h, bytes_per_pixel);
      bytes += slice_size;
   }
}

#ifndef STBGIF_NO_STDIO

#if defined(_MSC_VER) && defined(STBGIF_WINDOWS_UTF8)
STBGIF_EXTERN __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int cp, unsigned long flags, const char *str, int cbmb, wchar_t *widestr, int cchwide);
STBGIF_EXTERN __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned int cp, unsigned long flags, const wchar_t *widestr, int cchwide, char *str, int cbmb, const char *defchar, int *used_default);
#endif

#if defined(_MSC_VER) && defined(STBGIF_WINDOWS_UTF8)
STBGIFDEF int stbgif_convert_wchar_to_utf8(char *buffer, size_t bufferlen, const wchar_t* input)
{
   return WideCharToMultiByte(65001 /* UTF8 */, 0, input, -1, buffer, (int) bufferlen, NULL, NULL);
}
#endif

static FILE *stbgif__fopen(char const *filename, char const *mode)
{
   FILE *f;
#if defined(_MSC_VER) && defined(STBGIF_WINDOWS_UTF8)
   wchar_t wMode[64];
   wchar_t wFilename[1024];
   if (0 == MultiByteToWideChar(65001 /* UTF8 */, 0, filename, -1, wFilename, sizeof(wFilename)))
      return 0;

   if (0 == MultiByteToWideChar(65001 /* UTF8 */, 0, mode, -1, wMode, sizeof(wMode)))
      return 0;

#if _MSC_VER >= 1400
   if (0 != _wfopen_s(&f, wFilename, wMode))
      f = 0;
#else
   f = _wfopen(wFilename, wMode);
#endif

#elif defined(_MSC_VER) && _MSC_VER >= 1400
   if (0 != fopen_s(&f, filename, mode))
      f=0;
#else
   f = fopen(filename, mode);
#endif
   return f;
}

STBGIFDEF stbgif_uc *stbgif_load(char const *filename, int **delays, int *x, int *y, int *z, int *comp, int req_comp)
{
   FILE *f = stbgif__fopen(filename, "rb");
   unsigned char *result;
   if (!f) return stbgif__errpuc("can't fopen", "Unable to open file");
   result = stbgif_load_from_file(f,delays,x,y,z,comp,req_comp);
   fclose(f);
   return result;
}

STBGIFDEF stbgif_uc *stbgif_load_from_file(FILE *f, int **delays, int *x, int *y, int *z, int *comp, int req_comp)
{
   void *result;
   stbgif__context s;
   stbgif__start_file(&s,f);

   if (stbgif_test(&s))
   {
      result = stbgif__load_main(&s,delays,x,y,z,comp,req_comp);
   }
   else
   {
      result = stbgif__errpuc("unknown image type", "Image is not GIF format, or corrupt");
   }

   if (result == NULL) return NULL;

   if (stbgif__vertically_flip_on_load) {
      stbgif__vertical_flip_slices( result, *x, *y, *z, *comp );
   }

   if (result) {
      // need to 'unget' all the characters in the IO buffer
      fseek(f, - (int) (s.img_buffer_end - s.img_buffer), SEEK_CUR);
   }
   return result;
}

#endif //!STBGIF_NO_STDIO

static void stbgif__refill_buffer(stbgif__context *s)
{
   int n = (s->io.read)(s->io_user_data,(char*)s->buffer_start,s->buflen);
   s->callback_already_read += (int) (s->img_buffer - s->img_buffer_original);
   if (n == 0) {
      // at end of file, treat same as if from memory, but need to handle case
      // where s->img_buffer isn't pointing to safe memory, e.g. 0-byte file
      s->read_from_callbacks = 0;
      s->img_buffer = s->buffer_start;
      s->img_buffer_end = s->buffer_start+1;
      *s->img_buffer = 0;
   } else {
      s->img_buffer = s->buffer_start;
      s->img_buffer_end = s->buffer_start + n;
   }
}

stbgif_inline static stbgif_uc stbgif__get8(stbgif__context *s)
{
   if (s->img_buffer < s->img_buffer_end)
      return *s->img_buffer++;
   if (s->read_from_callbacks) {
      stbgif__refill_buffer(s);
      return *s->img_buffer++;
   }
   return 0;
}

static int stbgif__get16le(stbgif__context *s)
{
   int z = stbgif__get8(s);
   return z + (stbgif__get8(s) << 8);
}

//////////////////////////////////////////////////////////////////////////////
//
//  generic converter from built-in img_n to req_comp
//    individual types do this automatically as much as possible (e.g. jpeg
//    does all cases internally since it needs to colorspace convert anyway,
//    and it never has alpha, so very few cases ). png can automatically
//    interleave an alpha=255 channel, but falls back to this for other cases
//
//  assume data buffer is malloced, so malloc a new one and free that one
//  only failure mode is malloc failing

static stbgif_uc stbgif__compute_y(int r, int g, int b)
{
   return (stbgif_uc) (((r*77) + (g*150) +  (29*b)) >> 8);
}

static unsigned char *stbgif__convert_format(unsigned char *data, int img_n, int req_comp, unsigned int x, unsigned int y)
{
   int i,j;
   unsigned char *good;

   if (req_comp == img_n) return data;
   STBGIF_ASSERT(req_comp >= 1 && req_comp <= 4);

   good = (unsigned char *) stbgif__malloc_mad3(req_comp, x, y, 0);
   if (good == NULL) {
      STBGIF_FREE(data);
      return stbgif__errpuc("outofmem", "Out of memory");
   }

   for (j=0; j < (int) y; ++j) {
      unsigned char *src  = data + j * x * img_n   ;
      unsigned char *dest = good + j * x * req_comp;

      #define STBGIF__COMBO(a,b)  ((a)*8+(b))
      #define STBGIF__CASE(a,b)   case STBGIF__COMBO(a,b): for(i=x-1; i >= 0; --i, src += a, dest += b)
      // convert source image with img_n components to one with req_comp components;
      // avoid switch per pixel, so use switch per scanline and massive macros
      switch (STBGIF__COMBO(img_n, req_comp)) {
         STBGIF__CASE(1,2) { dest[0]=src[0]; dest[1]=255;                                     } break;
         STBGIF__CASE(1,3) { dest[0]=dest[1]=dest[2]=src[0];                                  } break;
         STBGIF__CASE(1,4) { dest[0]=dest[1]=dest[2]=src[0]; dest[3]=255;                     } break;
         STBGIF__CASE(2,1) { dest[0]=src[0];                                                  } break;
         STBGIF__CASE(2,3) { dest[0]=dest[1]=dest[2]=src[0];                                  } break;
         STBGIF__CASE(2,4) { dest[0]=dest[1]=dest[2]=src[0]; dest[3]=src[1];                  } break;
         STBGIF__CASE(3,4) { dest[0]=src[0];dest[1]=src[1];dest[2]=src[2];dest[3]=255;        } break;
         STBGIF__CASE(3,1) { dest[0]=stbgif__compute_y(src[0],src[1],src[2]);                   } break;
         STBGIF__CASE(3,2) { dest[0]=stbgif__compute_y(src[0],src[1],src[2]); dest[1] = 255;    } break;
         STBGIF__CASE(4,1) { dest[0]=stbgif__compute_y(src[0],src[1],src[2]);                   } break;
         STBGIF__CASE(4,2) { dest[0]=stbgif__compute_y(src[0],src[1],src[2]); dest[1] = src[3]; } break;
         STBGIF__CASE(4,3) { dest[0]=src[0];dest[1]=src[1];dest[2]=src[2];                    } break;
         default: STBGIF_ASSERT(0); STBGIF_FREE(data); STBGIF_FREE(good); return stbgif__errpuc("unsupported", "Unsupported format conversion");
      }
      #undef STBGIF__CASE
   }

   STBGIF_FREE(data);
   return good;
}

typedef struct
{
   stbgif__int16 prefix;
   stbgif_uc first;
   stbgif_uc suffix;
} stbgif_lzw;

typedef struct
{
   int w,h;
   stbgif_uc *out;                 // output buffer (always 4 components)
   stbgif_uc *background;          // The current "background" as far as a gif is concerned
   stbgif_uc *history;
   int flags, bgindex, ratio, transparent, eflags;
   stbgif_uc  pal[256][4];
   stbgif_uc lpal[256][4];
   stbgif_lzw codes[8192];
   stbgif_uc *color_table;
   int parse, step;
   int lflags;
   int start_x, start_y;
   int max_x, max_y;
   int cur_x, cur_y;
   int line_size;
   int delay;
} stbgif_data;

#ifndef STBGIF_NO_STDIO
STBGIFDEF int stbgif_info_from_file(FILE *f, int *x, int *y, int *comp)
{
   int r;
   stbgif__context s;
   long pos = ftell(f);
   stbgif__start_file(&s, f);

   r = stbgif__info(&s, x, y, comp);
   if( r ) r = stbgif__err("unknown image type", "Image is not GIF format, or corrupt");

   fseek(f,pos,SEEK_SET);
   return r;
}

STBGIFDEF int stbgif_info(char const *filename, int *x, int *y, int *comp)
{
    FILE *f = stbgif__fopen(filename, "rb");
    int result;
    if (!f) return stbgif__err("can't fopen", "Unable to open file");
    result = stbgif_info_from_file(f, x, y, comp);
    fclose(f);
    return result;
}


#endif // !STBI_NO_STDIO

STBGIFDEF stbgif_uc *stbgif_load_from_memory(stbgif_uc const *buffer, int len, int **delays, int *x, int *y, int *z, int *comp, int req_comp)
{
   unsigned char *result;
   stbgif__context s;
   stbgif__start_mem(&s,buffer,len);

   result = (unsigned char*) stbgif__load_main(&s, delays, x, y, z, comp, req_comp);
   if (stbgif__vertically_flip_on_load) {
      stbgif__vertical_flip_slices( result, *x, *y, *z, *comp );
   }

   return result;
}

STBGIFDEF stbgif_uc *stbgif_load_from_callbacks(stbgif_io_callbacks const *clbk, void *user, int** delays, int *x, int *y, int *z, int *comp, int req_comp)
{
   void *result;
   stbgif__context s;
   stbgif__start_callbacks(&s, (stbgif_io_callbacks *) clbk, user);

   if (stbgif_test(&s))
   {
      result = stbgif__load_main(&s,delays,x,y,z,comp,req_comp);
   }
   else
   {
      result = stbgif__errpuc("unknown image type", "Image is not GIF format, or corrupt");
   }

   if (result == NULL) return NULL;

   if (stbgif__vertically_flip_on_load) {
      stbgif__vertical_flip_slices( result, *x, *y, *z, *comp );
   }

   return (unsigned char*)result;

}

STBGIFDEF void stbgif_info_from_memory(stbgif_uc const *buffer, int len, int *x, int *y, int *comp)
{
   stbgif__context s;
   stbgif__start_mem(&s,buffer,len);
   stbgif__info(&s, x, y, comp);
}

STBGIFDEF int stbgif_info_from_callbacks(stbgif_io_callbacks const *c, void *user, int *x, int *y, int *comp)
{
   int r;
   stbgif__context s;
   stbgif__start_callbacks(&s, (stbgif_io_callbacks *) c, user);

   r = stbgif__info(&s, x, y, comp);
   if( r ) r = stbgif__err("unknown image type", "Image is not GIF format, or corrupt");

   return r;
}

static int stbgif_test_raw(stbgif__context *s)
{
   int sz;
   if (stbgif__get8(s) != 'G' || stbgif__get8(s) != 'I' || stbgif__get8(s) != 'F' || stbgif__get8(s) != '8') return 0;
   sz = stbgif__get8(s);
   if (sz != '9' && sz != '7') return 0;
   if (stbgif__get8(s) != 'a') return 0;
   return 1;
}

static int stbgif_test(stbgif__context *s)
{
   int r = stbgif_test_raw(s);
   stbgif__rewind(s);
   return r;
}

static void stbgif_parse_colortable(stbgif__context *s, stbgif_uc pal[256][4], int num_entries, int transp)
{
   int i;
   for (i=0; i < num_entries; ++i) {
      pal[i][2] = stbgif__get8(s);
      pal[i][1] = stbgif__get8(s);
      pal[i][0] = stbgif__get8(s);
      pal[i][3] = transp == i ? 0 : 255;
   }
}

static int stbgif_header(stbgif__context *s, stbgif_data *g, int *comp, int is_info)
{
   stbgif_uc version;
   if (stbgif__get8(s) != 'G' || stbgif__get8(s) != 'I' || stbgif__get8(s) != 'F' || stbgif__get8(s) != '8')
      return stbgif__err("not GIF", "Corrupt GIF");

   version = stbgif__get8(s);
   if (version != '7' && version != '9')    return stbgif__err("not GIF", "Corrupt GIF");
   if (stbgif__get8(s) != 'a')              return stbgif__err("not GIF", "Corrupt GIF");

   stbgif__g_failure_reason = "";
   g->w = stbgif__get16le(s);
   g->h = stbgif__get16le(s);
   g->flags = stbgif__get8(s);
   g->bgindex = stbgif__get8(s);
   g->ratio = stbgif__get8(s);
   g->transparent = -1;

   if (g->w > STBGIF_MAX_DIMENSIONS) return stbgif__err("too large","Very large image (corrupt?)");
   if (g->h > STBGIF_MAX_DIMENSIONS) return stbgif__err("too large","Very large image (corrupt?)");

   if (comp != 0) *comp = 4;  // can't actually tell whether it's 3 or 4 until we parse the comments

   if (is_info) return 1;

   if (g->flags & 0x80)
      stbgif_parse_colortable(s,g->pal, 2 << (g->flags & 7), -1);

   return 1;
}

static int stbgif_info_raw(stbgif__context *s, int *x, int *y, int *comp)
{
   stbgif_data* g = (stbgif_data*) stbgif__malloc(sizeof(stbgif_data));
   if (!stbgif_header(s, g, comp, 1)) {
      STBGIF_FREE(g);
      stbgif__rewind( s );
      return 0;
   }
   if (x) *x = g->w;
   if (y) *y = g->h;
   STBGIF_FREE(g);
   return 1;
}

static void stbgif__out_code(stbgif_data *g, stbgif__uint16 code)
{
   stbgif_uc *p, *c;
   int idx;

   // recurse to decode the prefixes, since the linked-list is backwards,
   // and working backwards through an interleaved image would be nasty
   if (g->codes[code].prefix >= 0)
      stbgif__out_code(g, g->codes[code].prefix);

   if (g->cur_y >= g->max_y) return;

   idx = g->cur_x + g->cur_y;
   p = &g->out[idx];
   g->history[idx / 4] = 1;

   c = &g->color_table[g->codes[code].suffix * 4];
   if (c[3] > 128) { // don't render transparent pixels;
      p[0] = c[2];
      p[1] = c[1];
      p[2] = c[0];
      p[3] = c[3];
   }
   g->cur_x += 4;

   if (g->cur_x >= g->max_x) {
      g->cur_x = g->start_x;
      g->cur_y += g->step;

      while (g->cur_y >= g->max_y && g->parse > 0) {
         g->step = (1 << g->parse) * g->line_size;
         g->cur_y = g->start_y + (g->step >> 1);
         --g->parse;
      }
   }
}

static stbgif_uc *stbgif__process_raster(stbgif__context *s, stbgif_data *g)
{
   stbgif_uc lzw_cs;
   stbgif__int32 len, init_code;
   stbgif__uint32 first;
   stbgif__int32 codesize, codemask, avail, oldcode, bits, valid_bits, clear;
   stbgif_lzw *p;

   lzw_cs = stbgif__get8(s);
   if (lzw_cs > 12) return NULL;
   clear = 1 << lzw_cs;
   first = 1;
   codesize = lzw_cs + 1;
   codemask = (1 << codesize) - 1;
   bits = 0;
   valid_bits = 0;
   for (init_code = 0; init_code < clear; init_code++) {
      g->codes[init_code].prefix = -1;
      g->codes[init_code].first = (stbgif_uc) init_code;
      g->codes[init_code].suffix = (stbgif_uc) init_code;
   }

   // support no starting clear code
   avail = clear+2;
   oldcode = -1;

   len = 0;
   for(;;) {
      if (valid_bits < codesize) {
         if (len == 0) {
            len = stbgif__get8(s); // start new block
            if (len == 0)
               return g->out;
         }
         --len;
         bits |= (stbgif__int32) stbgif__get8(s) << valid_bits;
         valid_bits += 8;
      } else {
         stbgif__int32 code = bits & codemask;
         bits >>= codesize;
         valid_bits -= codesize;
         // @OPTIMIZE: is there some way we can accelerate the non-clear path?
         if (code == clear) {  // clear code
            codesize = lzw_cs + 1;
            codemask = (1 << codesize) - 1;
            avail = clear + 2;
            oldcode = -1;
            first = 0;
         } else if (code == clear + 1) { // end of stream code
            stbgif__skip(s, len);
            while ((len = stbgif__get8(s)) > 0)
               stbgif__skip(s,len);
            return g->out;
         } else if (code <= avail) {
            if (first) {
               return stbgif__errpuc("no clear code", "Corrupt GIF");
            }

            if (oldcode >= 0) {
               p = &g->codes[avail++];
               if (avail > 8192) {
                  return stbgif__errpuc("too many codes", "Corrupt GIF");
               }

               p->prefix = (stbgif__int16) oldcode;
               p->first = g->codes[oldcode].first;
               p->suffix = (code == avail) ? p->first : g->codes[code].first;
            } else if (code == avail)
               return stbgif__errpuc("illegal code in raster", "Corrupt GIF");

            stbgif__out_code(g, (stbgif__uint16) code);

            if ((avail & codemask) == 0 && avail <= 0x0FFF) {
               codesize++;
               codemask = (1 << codesize) - 1;
            }

            oldcode = code;
         } else {
            return stbgif__errpuc("illegal code in raster", "Corrupt GIF");
         }
      }
   }
}

// two back is the image from two frames ago, used for a very specific disposal format
static stbgif_uc *stbgif__load_next(stbgif__context *s, stbgif_data *g, int *comp, int req_comp, stbgif_uc *two_back)
{
   int dispose;
   int first_frame;
   int pi;
   int pcount;
   STBGIF_NOTUSED(req_comp);

   // on first frame, any non-written pixels get the background colour (non-transparent)
   first_frame = 0;
   if (g->out == 0) {
      if (!stbgif_header(s, g, comp,0)) return 0; // stbgif__g_failure_reason set by stbgif_data_header
      if (!stbgif__mad3sizes_valid(4, g->w, g->h, 0))
         return stbgif__errpuc("too large", "GIF image is too large");
      pcount = g->w * g->h;
      g->out = (stbgif_uc *) stbgif__malloc(4 * pcount);
      g->background = (stbgif_uc *) stbgif__malloc(4 * pcount);
      g->history = (stbgif_uc *) stbgif__malloc(pcount);
      if (!g->out || !g->background || !g->history)
         return stbgif__errpuc("outofmem", "Out of memory");

      // image is treated as "transparent" at the start - ie, nothing overwrites the current background;
      // background colour is only used for pixels that are not rendered first frame, after that "background"
      // color refers to the color that was there the previous frame.
      memset(g->out, 0x00, 4 * pcount);
      memset(g->background, 0x00, 4 * pcount); // state of the background (starts transparent)
      memset(g->history, 0x00, pcount);        // pixels that were affected previous frame
      first_frame = 1;
   } else {
      // second frame - how do we dispose of the previous one?
      dispose = (g->eflags & 0x1C) >> 2;
      pcount = g->w * g->h;

      if ((dispose == 3) && (two_back == 0)) {
         dispose = 2; // if I don't have an image to revert back to, default to the old background
      }

      if (dispose == 3) { // use previous graphic
         for (pi = 0; pi < pcount; ++pi) {
            if (g->history[pi]) {
               memcpy( &g->out[pi * 4], &two_back[pi * 4], 4 );
            }
         }
      } else if (dispose == 2) {
         // restore what was changed last frame to background before that frame;
         for (pi = 0; pi < pcount; ++pi) {
            if (g->history[pi]) {
               memcpy( &g->out[pi * 4], &g->background[pi * 4], 4 );
            }
         }
      } else {
         // This is a non-disposal case eithe way, so just
         // leave the pixels as is, and they will become the new background
         // 1: do not dispose
         // 0:  not specified.
      }

      // background is what out is after the undoing of the previous frame;
      memcpy( g->background, g->out, 4 * g->w * g->h );
   }

   // clear my history;
   memset( g->history, 0x00, g->w * g->h );        // pixels that were affected previous frame

   for (;;) {
      int tag = stbgif__get8(s);
      switch (tag) {
         case 0x2C: /* Image Descriptor */
         {
            stbgif__int32 x, y, w, h;
            stbgif_uc *o;

            x = stbgif__get16le(s);
            y = stbgif__get16le(s);
            w = stbgif__get16le(s);
            h = stbgif__get16le(s);
            if (((x + w) > (g->w)) || ((y + h) > (g->h)))
               return stbgif__errpuc("bad Image Descriptor", "Corrupt GIF");

            g->line_size = g->w * 4;
            g->start_x = x * 4;
            g->start_y = y * g->line_size;
            g->max_x   = g->start_x + w * 4;
            g->max_y   = g->start_y + h * g->line_size;
            g->cur_x   = g->start_x;
            g->cur_y   = g->start_y;

            // if the width of the specified rectangle is 0, that means
            // we may not see *any* pixels or the image is malformed;
            // to make sure this is caught, move the current y down to
            // max_y (which is what out_gif_code checks).
            if (w == 0)
               g->cur_y = g->max_y;

            g->lflags = stbgif__get8(s);

            if (g->lflags & 0x40) {
               g->step = 8 * g->line_size; // first interlaced spacing
               g->parse = 3;
            } else {
               g->step = g->line_size;
               g->parse = 0;
            }

            if (g->lflags & 0x80) {
               stbgif_parse_colortable(s,g->lpal, 2 << (g->lflags & 7), g->eflags & 0x01 ? g->transparent : -1);
               g->color_table = (stbgif_uc *) g->lpal;
            } else if (g->flags & 0x80) {
               g->color_table = (stbgif_uc *) g->pal;
            } else
               return stbgif__errpuc("missing color table", "Corrupt GIF");

            o = stbgif__process_raster(s, g);
            if (!o) return NULL;

            // if this was the first frame,
            pcount = g->w * g->h;
            if (first_frame && (g->bgindex > 0)) {
               // if first frame, any pixel not drawn to gets the background color
               for (pi = 0; pi < pcount; ++pi) {
                  if (g->history[pi] == 0) {
                     g->pal[g->bgindex][3] = 255; // just in case it was made transparent, undo that; It will be reset next frame if need be;
                     memcpy( &g->out[pi * 4], &g->pal[g->bgindex], 4 );
                  }
               }
            }

            return o;
         }

         case 0x21: // Comment Extension.
         {
            int len;
            int ext = stbgif__get8(s);
            if (ext == 0xF9) { // Graphic Control Extension.
               len = stbgif__get8(s);
               if (len == 4) {
                  g->eflags = stbgif__get8(s);
                  g->delay = 10 * stbgif__get16le(s); // delay - 1/100th of a second, saving as 1/1000ths.

                  // unset old transparent
                  if (g->transparent >= 0) {
                     g->pal[g->transparent][3] = 255;
                  }
                  if (g->eflags & 0x01) {
                     g->transparent = stbgif__get8(s);
                     if (g->transparent >= 0) {
                        g->pal[g->transparent][3] = 0;
                     }
                  } else {
                     // don't need transparent
                     stbgif__skip(s, 1);
                     g->transparent = -1;
                  }
               } else {
                  stbgif__skip(s, len);
                  break;
               }
            }
            while ((len = stbgif__get8(s)) != 0) {
               stbgif__skip(s, len);
            }
            break;
         }

         case 0x3B: // gif stream termination code
            return (stbgif_uc *) s; // using '1' causes warning on some compilers

         default:
            return stbgif__errpuc("unknown code", "Corrupt GIF");
      }
   }
}

static void *stbgif__load_main(stbgif__context *s, int **delays, int *x, int *y, int *z, int *comp, int req_comp)
{
   if (stbgif_test(s)) {
      int layers = 0;
      stbgif_uc *u = 0;
      stbgif_uc *out = 0;
      stbgif_uc *two_back = 0;
      stbgif_data g;
      int stride;
      int out_size = 0;
      int delays_size = 0;
      memset(&g, 0, sizeof(g));
      if (delays) {
         *delays = 0;
      }

      do {
         u = stbgif__load_next(s, &g, comp, req_comp, two_back);
         if (u == (stbgif_uc *) s) u = 0;  // end of animated gif marker

         if (u) {
            *x = g.w;
            *y = g.h;
            ++layers;
            stride = g.w * g.h * 4;

            if (out) {
               void *tmp = (stbgif_uc*) STBGIF_REALLOC_SIZED( out, out_size, layers * stride );
               if (NULL == tmp) {
                  STBGIF_FREE(g.out);
                  STBGIF_FREE(g.history);
                  STBGIF_FREE(g.background);
                  return stbgif__errpuc("outofmem", "Out of memory");
               }
               else {
                   out = (stbgif_uc*) tmp;
                   out_size = layers * stride;
               }

               if (delays) {
                  *delays = (int*) STBGIF_REALLOC_SIZED( *delays, delays_size, sizeof(int) * layers );
                  delays_size = layers * sizeof(int);
               }
            } else {
               out = (stbgif_uc*)stbgif__malloc( layers * stride );
               out_size = layers * stride;
               if (delays) {
                  *delays = (int*) stbgif__malloc( layers * sizeof(int) );
                  delays_size = layers * sizeof(int);
               }
            }
            memcpy( out + ((layers - 1) * stride), u, stride );
            if (layers >= 2) {
               two_back = out - 2 * stride;
            }

            if (delays) {
               (*delays)[layers - 1U] = g.delay;
            }
         }
      } while (u != 0);

      // free temp buffer;
      STBGIF_FREE(g.out);
      STBGIF_FREE(g.history);
      STBGIF_FREE(g.background);

      // do the final conversion after loading everything;
      if (req_comp && req_comp != 4)
         out = stbgif__convert_format(out, 4, req_comp, layers * g.w, g.h);

      *z = layers;
      return out;
   } else {
      return stbgif__errpuc("not GIF", "Image was not as a gif type.");
   }
}

// loads only the first frame
static void *stbgif__load_first_layer(stbgif__context *s, int *x, int *y, int *comp, int req_comp)
{
   stbgif_uc *u = 0;
   stbgif_data g;
   memset(&g, 0, sizeof(g));

   u = stbgif__load_next(s, &g, comp, req_comp, 0);
   if (u == (stbgif_uc *) s) u = 0;  // end of animated gif marker
   if (u) {
      *x = g.w;
      *y = g.h;

      // moved conversion to after successful load so that the same
      // can be done for multiple frames.
      if (req_comp && req_comp != 4)
         u = stbgif__convert_format(u, 4, req_comp, g.w, g.h);
   } else if (g.out) {
      // if there was an error and we allocated an image buffer, free it!
      STBGIF_FREE(g.out);
   }

   // free buffers needed for multiple frame loading;
   STBGIF_FREE(g.history);
   STBGIF_FREE(g.background);

   return u;
}

static int stbgif__info(stbgif__context *s, int *x, int *y, int *comp)
{
   return stbgif_info_raw(s,x,y,comp);
}

#endif // STBGIF_IMPLEMENTATION

/*
   revision history:
      0.50  (2020-09-03) 
              first released version; created from stb_image.h v2.26
*/

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
