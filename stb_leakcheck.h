// stb_leakcheck.h - v0.4 - quick & dirty malloc leak-checking - public domain
// LICENSE
//
//   See end of file.

#ifdef STB_LEAKCHECK_IMPLEMENTATION
#undef STB_LEAKCHECK_IMPLEMENTATION // don't implement more than once

// if we've already included leakcheck before, undefine the macros
#ifdef malloc
#undef malloc
#undef free
#undef realloc
#endif

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
typedef struct malloc_info stb_leakcheck_malloc_info;

struct malloc_info
{
   const char *file;
   int line;
   size_t size;
   stb_leakcheck_malloc_info *next,*prev;
};

static stb_leakcheck_malloc_info *mi_head;

void *stb_leakcheck_malloc(size_t sz, const char *file, int line)
{
   stb_leakcheck_malloc_info *mi = (stb_leakcheck_malloc_info *) malloc(sz + sizeof(*mi));
   if (mi == NULL) return mi;
   mi->file = file;
   mi->line = line;
   mi->next = mi_head;
   if (mi_head)
      mi->next->prev = mi;
   mi->prev = NULL;
   mi->size = (int) sz;
   mi_head = mi;
   return mi+1;
}

void stb_leakcheck_free(void *ptr)
{
   if (ptr != NULL) {
      stb_leakcheck_malloc_info *mi = (stb_leakcheck_malloc_info *) ptr - 1;
      mi->size = ~mi->size;
      #ifndef STB_LEAKCHECK_SHOWALL
      if (mi->prev == NULL) {
         assert(mi_head == mi);
         mi_head = mi->next;
      } else
         mi->prev->next = mi->next;
      if (mi->next)
         mi->next->prev = mi->prev;
      #endif
      free(mi);
   }
}

void *stb_leakcheck_realloc(void *ptr, size_t sz, const char *file, int line)
{
   if (ptr == NULL) {
      return stb_leakcheck_malloc(sz, file, line);
   } else if (sz == 0) {
      stb_leakcheck_free(ptr);
      return NULL;
   } else {
      stb_leakcheck_malloc_info *mi = (stb_leakcheck_malloc_info *) ptr - 1;
      if (sz <= mi->size)
         return ptr;
      else {
         #ifdef STB_LEAKCHECK_REALLOC_PRESERVE_MALLOC_FILELINE
         void *q = stb_leakcheck_malloc(sz, mi->file, mi->line);
         #else
         void *q = stb_leakcheck_malloc(sz, file, line);
         #endif
         if (q) {
            memcpy(q, ptr, mi->size);
            stb_leakcheck_free(ptr);
         }
         return q;
      }
   }
}

static void stblkck_internal_print(const char *reason, const char *file,  int line, size_t size, void *ptr)
{
#if (defined(_MSC_VER) && _MSC_VER < 1900) /* 1900=VS 2015 */ || defined(__MINGW32__)
   // Compilers that use the old MS C runtime library don't have %zd
   // and the older ones don't even have %lld either... however, the old compilers
   // without "long long" don't support 64-bit targets either, so here's the
   // compromise:
   #if defined(_MSC_VER) && _MSC_VER < 1400 // before VS 2005
      printf("%-6s: %s (%4d): %8d bytes at %p\n", reason, file, line, (int)size, ptr);
   #else
      printf("%-6s: %s (%4d): %8lld bytes at %p\n", reason, file, line, (long long)size, ptr);
   #endif
#else
   // Assume we have %zd on other targets.
   printf("%-6s: %s (%4d): %zd bytes at %p\n", reason, file, line, size, ptr);
#endif
}

void stb_leakcheck_dumpmem(void)
{
   stb_leakcheck_malloc_info *mi = mi_head;
   while (mi) {
      if ((ptrdiff_t) mi->size >= 0)
         stblkck_internal_print("LEAKED", mi->file, mi->line, mi->size, mi+1);
         printf("LEAKED: %s (%4d): %8d bytes at %p\n", mi->file, mi->line, (int) mi->size, mi+1);
      mi = mi->next;
   }
   #ifdef STB_LEAKCHECK_SHOWALL
   mi = mi_head;
   while (mi) {
      if ((ptrdiff_t) mi->size < 0)
         stblkck_internal_print("FREED", mi->file, mi->line, ~mi->size, mi+1);
         printf("FREED : %s (%4d): %8d bytes at %p\n", mi->file, mi->line, (int) ~mi->size, mi+1);
      mi = mi->next;
   }
   #endif
}
#endif // STB_LEAKCHECK_IMPLEMENTATION

#ifndef INCLUDE_STB_LEAKCHECK_H
#define INCLUDE_STB_LEAKCHECK_H

#define malloc(sz)    stb_leakcheck_malloc(sz, __FILE__, __LINE__)
#define free(p)       stb_leakcheck_free(p)
#define realloc(p,sz) stb_leakcheck_realloc(p,sz, __FILE__, __LINE__)

extern void * stb_leakcheck_malloc(size_t sz, const char *file, int line);
extern void * stb_leakcheck_realloc(void *ptr, size_t sz, const char *file, int line);
extern void   stb_leakcheck_free(void *ptr);
extern void   stb_leakcheck_dumpmem(void);

#endif // INCLUDE_STB_LEAKCHECK_H


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
