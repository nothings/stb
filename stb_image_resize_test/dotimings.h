// dotimings.h - shared between the dotimings driver and its per SIMD level copies of dotimings_impl.c
#ifndef DOTIMINGS_H
#define DOTIMINGS_H

#define DT_TYPES 5          // channel types timed: 1, 2, 3, 4 and 7 (RGBA with alpha weighting) effective channels
#define DT_MAXINSIZES 8
#define DT_MAXDIM 128

extern const int dt_types[ DT_TYPES ];       // stbir_pixel_layout per type
extern const int dt_effective[ DT_TYPES ];   // effective channel count per type
extern int dt_update;                        // 1 = out_timings arrive pre-filled with a previous run's cells (0 = none): start each cell's minimum there

// called by the timing body after every cell: with -runcool the driver sleeps here now and then so the cpu cools
void dt_after_cell( void );

// one timing set: a filter and edge mode, input sizes, and the output widths / heights per input size
typedef struct dt_set
{
  int filter, edge;
  int insizes;
  int sizes[ DT_MAXINSIZES ];
  int dimx, dimy;
  int ox[ DT_MAXINSIZES ][ DT_MAXDIM ], oy[ DT_MAXINSIZES ][ DT_MAXDIM ];
  char const * name;
} dt_set;

// done / total are estimated work (pixels x channels), not cell counts, so the bar moves evenly
typedef void dt_progress_func( int in_width, int htaps, int in_height, int vtaps, int out_width, int out_height, double done, double total );

// per SIMD level entry points (dotimings_impl.c compiled with DT_SUFFIX = scalar / sse2 / avx / avx512 / neon)
#define DT_LEVEL_FUNCS( suffix ) \
  int dt_simd_level_##suffix( void ); \
  void dt_time_set_##suffix( dt_set const * set, unsigned char * input, unsigned char * output, int * out_timings, dt_progress_func * progress ); \
  long long dt_clock_##suffix( void );

DT_LEVEL_FUNCS( scalar )
#if ( defined( _M_X64 ) || defined( _M_IX86 ) || defined( __x86_64__ ) || defined( __i386__ ) ) && !defined( _M_ARM64EC )
  #define DT_X86
  DT_LEVEL_FUNCS( sse2 )
  DT_LEVEL_FUNCS( avx )
  DT_LEVEL_FUNCS( avx512 )
#else
  DT_LEVEL_FUNCS( neon )
#endif

#endif
