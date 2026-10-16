// dotimings_impl.c - the timing body of dotimings, compiled once per SIMD level (dotimings_scalar.c / _simd4.c /
//   _avx.c / _avx512.c include this with the right switches) and linked into the one dotimings.exe. Each copy includes
//   the header's implementation for its level and exports DT_FN( dt_time_set ): time every cell of a set, both orders.
//
//   DT_SUFFIX must be defined by the includer (scalar, sse2, avx, avx512, neon); only the exported names carry it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DT_SUFFIX
#error include this from dotimings_scalar.c / dotimings_simd4.c / dotimings_avx.c / dotimings_avx512.c
#endif
#define DT_CAT2( a, b ) a##_##b
#define DT_CAT( a, b ) DT_CAT2( a, b )
#define DT_FN( name ) DT_CAT( name, DT_SUFFIX )

#ifdef _MSC_VER
#pragma warning(disable:4127)
#endif

#define STBIR_PROFILE
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include "stb_image_resize2.h"

#include "dotimings.h"

// 0 scalar, 1 four wide (SSE2 / NEON), 2 eight wide (AVX), 3 sixteen wide (AVX-512) - what this copy was actually built as
int DT_FN( dt_simd_level )( void )
{
  #if defined( STBIR_SIMD16 )
  return 3;
  #elif defined( STBIR_SIMD8 )
  return 2;
  #elif defined( STBIR_SIMD )
  return 1;
  #else
  return 0;
  #endif
}

// one order of the resize, built once with that order forced (2 vertical first, 1 horizontal first)
static void build( STBIR_RESIZE * resize, void * o, int ox, int oy, int op, void * i, int ix, int iy, int ip, int buf, int type, int edg, int flt, int order )
{
  stbir_resize_init( resize, i, ix, iy, ip, o, ox, oy, op, buf, type );
  stbir_set_edgemodes( resize, edg, edg );
  stbir_set_filters( resize, flt, flt );
  stbir__force_vertical_first = order;   // this copy's static, read when the samplers are built
  if ( !stbir_build_samplers_with_splits( resize, 1 ) )
  {
    printf( "build failed (%dx%d to %dx%d)!\n", ix, iy, ox, oy );
    exit( 1 );
  }
}

// one run: the sampling zones' clocks (the vertical + horizontal passes only - decode and encode are the same for both orders)
static stbir_int64 run( STBIR_RESIZE * resize )
{
  STBIR_PROFILE_INFO profile;

  memset( &profile, 0, sizeof( profile ) );
  if ( !stbir_resize_extended( resize ) )
  {
    printf( "resize failed!\n" );
    exit( 1 );
  }
  stbir_resize_extended_profile_info( &profile, resize );

  return profile.clocks[1] + profile.clocks[2];
}

// times both orders of one resize. the orders alternate (V, H, V, H ...) to reduce clock drift between them; each stops
//   after 16 runs without improving its minimum. *VF / *HF come in as the previous minima (0 = none) and leave as the new.
static void time_cell( void * o, int ox, int oy, int op, void * i, int ix, int iy, int ip, int buf, int type, int edg, int flt, stbir_int64 * VF, stbir_int64 * HF )
{
  STBIR_RESIZE rv, rh;
  stbir_int64 bestV = ( *VF > 0 ) ? *VF : 0x7fffffffffffffffLL;
  stbir_int64 bestH = ( *HF > 0 ) ? *HF : 0x7fffffffffffffffLL;
  int sinceV = 0, sinceH = 0;   // runs since each order's best last improved

  build( &rv, o, ox, oy, op, i, ix, iy, ip, buf, type, edg, flt, 2 );
  build( &rh, o, ox, oy, op, i, ix, iy, ip, buf, type, edg, flt, 1 );

  while ( ( sinceV < 16 ) || ( sinceH < 16 ) )
  {
    if ( sinceV < 16 )
    {
      stbir_int64 v = run( &rv );
      if ( v < bestV )
      {
        bestV = v;
        sinceV = 0;
      }
      else
      {
        sinceV++;
      }
    }
    if ( sinceH < 16 )
    {
      stbir_int64 h = run( &rh );
      if ( h < bestH )
      {
        bestH = h;
        sinceH = 0;
      }
      else
      {
        sinceH++;
      }
    }
  }

  stbir_free_samplers( &rv );
  stbir_free_samplers( &rh );
  *VF = bestV;
  *HF = bestH;
}

// estimated work of a cell, pixels in + out times channels - so the progress bar moves evenly, not per cell
static double cell_work( dt_set const * set, int ir, int ty, int hh, int ww )
{
  return ( (double) set->sizes[ir] * set->sizes[ir] + (double) set->ox[ir][ww] * set->oy[ir][hh] ) * dt_effective[ty];
}

// times one set into out_timings (2 ints per cell: vertical first cycles, horizontal first cycles; cells ordered
//   input size, channel type, oy, ox). progress( in_w, htaps, in_h, vtaps, out_w, out_h, done, total ) is called per cell.
//   with dt_update the cells arrive holding a previous run's values, which become each cell's starting minimum (so a
//   run can only improve them).
void DT_FN( dt_time_set )( dt_set const * set, unsigned char * input, unsigned char * output, int * out_timings, dt_progress_func * progress )
{
  stbir__radius_callback_new * radius = stbir__builtin_radii[ set->filter ];
  stbir__support_callback_new * support = stbir__builtin_supports[ set->filter ];
  stbir__scale_info sx, sy;   // (just enough of one for the tap count the progress display shows)
  double total = 0, done = 0;
  int * ts = out_timings;
  int ir, ty, hh, ww;

  memset( &sx, 0, sizeof( sx ) );
  memset( &sy, 0, sizeof( sy ) );

  for( ir = 0 ; ir < set->insizes ; ir++ )
  {
    for( ty = 0 ; ty < DT_TYPES ; ty++ )
    {
      for( hh = 0 ; hh < set->dimy ; hh++ )
      {
        for( ww = 0 ; ww < set->dimx ; ww++ )
        {
          total += cell_work( set, ir, ty, hh, ww );
        }
      }
    }
  }

  for( ir = 0 ; ir < set->insizes ; ir++ )
  {
    int ix = set->sizes[ir], iy = set->sizes[ir];
    for( ty = 0 ; ty < DT_TYPES ; ty++ )
    {
      for( hh = 0 ; hh < set->dimy ; hh++ )
      {
        int h = set->oy[ir][hh];
        for( ww = 0 ; ww < set->dimx ; ww++ )
        {
          int w = set->ox[ir][ww];
          stbir_int64 VF = dt_update ? ts[0] : 0, HF = dt_update ? ts[1] : 0;   // the previous run's bests, or none

          sx.scale = (stbir_real) w / (stbir_real) ix;
          sx.inv_scale = (stbir_real) ix / (stbir_real) w;
          sy.scale = (stbir_real) h / (stbir_real) iy;
          sy.inv_scale = (stbir_real) iy / (stbir_real) h;
          progress( ix, stbir__get_filter_pixel_width( radius, support, 0, &sx, 0 ), iy, stbir__get_filter_pixel_width( radius, support, 0, &sy, 0 ), w, h, done, total );

          time_cell( output, w, h, w * 4, input, ix, iy, ix * 4, dt_types[ty], STBIR_TYPE_UINT8, set->edge, set->filter, &VF, &HF );

          ts[0] = (int) VF;
          ts[1] = (int) HF;
          ts += 2;
          done += cell_work( set, ir, ty, hh, ww );
          dt_after_cell();
        }
      }
    }
  }
  progress( 0, 0, 0, 0, 0, 0, total, total );
}

// the profile clock, so the driver can convert cycles to time
long long DT_FN( dt_clock )( void )
{
  return (long long) STBIR_PROFILE_FUNC();
}
