// the eight wide (AVX) copy of the timing body, x86 only (see dotimings_impl.c). STBIR_AVX turns the header's AVX path
//   on without a compiler switch. cl compiles AVX intrinsics regardless of /arch; gcc and clang need the ISA enabled for
//   this file, which the target pragma does (build switches are per target in cdep, so the file must do it itself).
#if ( defined( _M_X64 ) || defined( _M_IX86 ) || defined( __x86_64__ ) || defined( __i386__ ) ) && !defined( _M_ARM64EC )
#if defined( __GNUC__ ) && !defined( __AVX__ )
  #if defined( __clang__ )
    #pragma clang attribute push( __attribute__(( target( "avx" ) )), apply_to = function )
  #else
    #pragma GCC target( "avx" )
  #endif
#endif
#define DT_SUFFIX avx
#define STBIR_AVX
#include "dotimings_impl.c"
#ifndef STBIR_SIMD8
#error the AVX copy did not get the header's AVX path
#endif
#if defined( __clang__ ) && !defined( __AVX__ )
  #pragma clang attribute pop
#endif
#endif
