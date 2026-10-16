// the scalar copy of the timing body (see dotimings_impl.c). the compilers auto-vectorize some of the header's plain
//   loops at -O2, which would make "scalar" partly SIMD - turned off for this file (gcc here; clang and cl have no file
//   level pragma, so the build files pass -fno-vectorize -fno-slp-vectorize / -d2Qvec- for this file).
#if defined( __GNUC__ ) && !defined( __clang__ )
#pragma GCC optimize( "no-tree-vectorize", "no-tree-slp-vectorize" )
#endif
#define DT_SUFFIX scalar
#define STBIR_NO_SIMD
#include "dotimings_impl.c"
#ifdef STBIR_SIMD
#error the scalar copy got SIMD switches
#endif
