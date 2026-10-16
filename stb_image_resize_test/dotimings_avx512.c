// the sixteen wide (AVX-512) copy of the timing body, x86 only (see dotimings_impl.c). STBIR_AVX512 turns the header's
//   AVX-512 path on without a compiler switch; gcc and clang need the ISA enabled for this file, which the target pragma
//   does (build switches are per target in cdep, so the file must do it itself).
#if ( defined( _M_X64 ) || defined( _M_IX86 ) || defined( __x86_64__ ) || defined( __i386__ ) ) && !defined( _M_ARM64EC )
#if defined( __GNUC__ ) && !defined( __AVX512F__ )
  #if defined( __clang__ )
    #pragma clang attribute push( __attribute__(( target( "avx512f,avx512bw,avx512vl,avx2,f16c" ) )), apply_to = function )
  #else
    #pragma GCC target( "avx512f,avx512bw,avx512vl,avx2,f16c" )
  #endif
#endif
#define DT_SUFFIX avx512
#define STBIR_AVX512
#include "dotimings_impl.c"
#ifndef STBIR_SIMD16
#error the AVX-512 copy did not get the header's AVX-512 path
#endif
#if defined( __clang__ ) && !defined( __AVX512F__ )
  #pragma clang attribute pop
#endif
#endif
