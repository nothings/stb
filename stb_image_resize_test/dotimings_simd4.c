// the four wide copy of the timing body: SSE2 on x86 (suffix sse2), NEON on arm (suffix neon) - see dotimings_impl.c
#if ( defined( _M_X64 ) || defined( _M_IX86 ) || defined( __x86_64__ ) || defined( __i386__ ) ) && !defined( _M_ARM64EC )
#define DT_SUFFIX sse2
#else
#define DT_SUFFIX neon
#endif
#include "dotimings_impl.c"
#ifndef STBIR_SIMD
#error the four wide copy was built without SIMD
#endif
#ifdef STBIR_SIMD8
#error the four wide copy got the AVX switches - per file switches leaked
#endif
