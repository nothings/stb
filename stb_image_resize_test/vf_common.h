// vf_common.h - shared by vf_train (evaluate / fit the vertical-first predictor) and vf_view (visualize it): the .timings
//   file reader, the header's cost model with its R table as a parameter, cell geometry and a walker over every timed
//   cell. One translation unit per tool: this includes the header's implementation.
#ifndef VF_COMMON_H
#define VF_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _MSC_VER
typedef __int64 vf_int64;
#pragma warning(disable:4127)
#else
typedef long long vf_int64;
#endif

#define STBIR_PROFILE
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include "stb_image_resize2.h"

#ifdef _WIN32
#include <windows.h>   // FindFirstFile for the wildcards (and vf_view's window)
#endif

static char * vf_strdup( char const * s )
{
  size_t n = strlen( s ) + 1;
  char * d = (char*) malloc( n );
  memcpy( d, s, n );
  return d;
}

// the whole file, with its size in the first int
static int * file_read( char const * filename )
{
  size_t s;
  int * m;
  FILE * f = fopen( filename, "rb" );
  if ( f == 0 )
  {
    return 0;
  }

  fseek( f, 0, SEEK_END );
  s = ftell( f );
  fseek( f, 0, SEEK_SET );
  m = (int*) malloc( s + 4 );
  m[0] = (int) s;
  fread( m + 1, 1, s, f );
  fclose( f );

  return m;
}

// one timed set (a filter and edge mode at one SIMD level) of one .timings file
typedef struct fileinfo
{
  int * timings;           // [input rect][channel type][height][width] pairs of ( vertical first, horizontal first ) clocks
  int timing_count;
  int dimensionx, dimensiony;
  int numtypes;
  int * types;
  int * effective;
  int cpu;
  int simd;                // 0 scalar, 1 four wide (SSE2 / NEON), 2 eight wide (AVX), 3 sixteen wide (AVX-512)
  int numinputrects;
  int * inputrects;
  int * ox;                // [numinputrects][dimensionx] output widths, [numinputrects][dimensiony] heights
  int * oy;
  int filter;              // stbir_filter the set was timed with
  int edge;                // stbir_edge, both axes
  char const * setname;    // e.g. "MitchellClamp SIMD4"
  int milliseconds;
  vf_int64 cycles;
  double scale_time;       // ms per profile clock
  int bitmapx, bitmapy;    // where vf_view draws this set
  char const * filename;
  unsigned char * ignored; // per cell (same order as timings): 1 = left out of the fits and the loss totals (see flag_outliers)
  int ignored_count;
} fileinfo;

#define VF_MAX_SETS 256   // (the per set arrays in vf_train are sized to match)
static int numfileinfo;
static fileinfo fi[VF_MAX_SETS];

// output width / height of grid cell ( ww, hh ) for input rect ir of file f
#define OX( f, ir, ww ) ( (f).ox[ (ir) * (f).dimensionx + (ww) ] )
#define OY( f, ir, hh ) ( (f).oy[ (ir) * (f).dimensiony + (hh) ] )

static char const * set_name( int filter, int edge )
{
  static char const * filters[] = { "Default", "Box", "Triangle", "Cubic", "CatmullRom", "Mitchell", "Point", "MitchellQ", "MitchellS", "MitchellNS", "MitchellNT", "Lanczos4", "Lanczos5", "Muratori6", "Other" };
  static char const * edges[] = { "Clamp", "Reflect", "Wrap", "Zero" };
  static char buf[64];
  sprintf( buf, "%s%s", filters[ ( filter >= 0 && filter < 14 ) ? filter : 14 ], edges[ ( edge >= 0 && edge < 4 ) ? edge : 0 ] );
  return buf;
}

// loads a timing file (VFT3, written by dotimings) into fi[index...]: any number of sets, each with its own SIMD level,
//   filter, edge mode and geometry - every set becomes its own fileinfo entry. returns the number of entries added, 0 on
//   error (not a VFT3 file, truncated - a run that was killed mid write - or more sets than fit)
static int use_timing_file( char const * filename, int index )
{
  int * base = file_read( filename );
  int * file = base;
  int * end;
  int version;

  if ( base == 0 )
  {
    return 0;
  }
  end = base + 1 + base[0] / (int) sizeof( int );   // one past the last whole int in the file
  if ( end - base < 1 + 32 )
  {
    return 0;
  }

  ++file;   // the file size
  version = *file++;

  if ( version == 'VFT3' )
  {
    // 'VFT3', cpu, numsets, numtypes, types[numtypes], effective[numtypes], reserved, ms, clocks (vf_int64 at 16-17)
    int cpu = *file++, numsets = *file++, numtypes = *file++;
    int * types = file;
    int * effective;
    int ms = base[ 1 + 15 ];
    vf_int64 cycles = ( (vf_int64*)( base + 1 + 16 ) )[0];
    int s;

    if ( ( numtypes < 1 ) || ( numtypes > 5 ) || ( numsets < 1 ) || ( index + numsets > VF_MAX_SETS ) )
    {
      printf( "%s: %d sets of %d channel types (%d sets fit in all)\n", filename, numsets, numtypes, VF_MAX_SETS );
      return 0;
    }
    file += numtypes;
    effective = file;
    file = base + 1 + 32;

    for( s = 0 ; s < numsets ; s++ )
    {
      fileinfo * f = fi + index + s;
      char buf[ 96 ];
      int ir, i;

      if ( end - file < 6 )
      {
        return 0;
      }
      memset( f, 0, sizeof( *f ) );
      f->cpu = cpu;
      f->numtypes = numtypes;
      f->types = types;
      f->effective = effective;
      f->milliseconds = ms;
      f->cycles = cycles;
      f->scale_time = (double) ms / (double) cycles;
      f->simd = *file++;
      f->filter = *file++;
      f->edge = *file++;
      f->numinputrects = *file++;
      f->dimensionx = *file++;
      f->dimensiony = *file++;
      if ( ( f->numinputrects < 1 ) || ( f->dimensionx < 1 ) || ( f->dimensiony < 1 ) || ( f->dimensionx > 4096 ) || ( f->dimensiony > 4096 ) ||
           ( end - file < (vf_int64) f->numinputrects * ( 2 + f->dimensionx + f->dimensiony + 2 * numtypes * f->dimensionx * f->dimensiony ) ) )
      {
        return 0;   // nonsense geometry, or the file ends inside this set
      }
      f->inputrects = (int*) malloc( sizeof( int ) * f->numinputrects * 2 );
      f->ox = (int*) malloc( sizeof( int ) * f->numinputrects * f->dimensionx );
      f->oy = (int*) malloc( sizeof( int ) * f->numinputrects * f->dimensiony );
      for( ir = 0 ; ir < f->numinputrects ; ir++ )
      {
        f->inputrects[ ir * 2 ] = *file++;
        f->inputrects[ ir * 2 + 1 ] = *file++;
        for( i = 0 ; i < f->dimensionx ; i++ )
        {
          f->ox[ ir * f->dimensionx + i ] = *file++;
        }
        for( i = 0 ; i < f->dimensiony ; i++ )
        {
          f->oy[ ir * f->dimensiony + i ] = *file++;
        }
      }
      f->filename = filename;
      sprintf( buf, "%s %s", set_name( f->filter, f->edge ), ( f->simd == 3 ) ? "AVX512" : ( f->simd == 2 ) ? "AVX" : ( f->simd == 1 ) ? "SIMD4" : "Scalar" );
      f->setname = vf_strdup( buf );
      f->timings = file;
      f->timing_count = f->dimensionx * f->dimensiony * f->numinputrects * f->numtypes;
      f->ignored = (unsigned char*) calloc( f->timing_count, 1 );
      f->ignored_count = 0;
      file += 2 * f->timing_count;
    }
    return numsets;
  }

  return 0;
}

static void load_one_file( char const * filename )
{
  int added = use_timing_file( filename, numfileinfo );
  if ( !added )
  {
    printf( "Bad timing file %s\n", filename );
    exit( 2 );
  }
  numfileinfo += added;
}

static void flag_outliers( fileinfo * f );   // below, after the cost model it uses

// the timing files on the command line - wildcards expanded here on Windows (the shell does it elsewhere), keeping
//   the argument's directory in front of each match
static void load_files( char ** args, int count )
{
  int i;

  if ( count == 0 )
  {
    printf( "No timing files listed!" );
    exit( 3 );
  }

  numfileinfo = 0;
  for( i = 0 ; i < count ; i++ )
  {
    #ifdef _WIN32
    if ( strchr( args[i], '*' ) || strchr( args[i], '?' ) )
    {
      WIN32_FIND_DATAA fd;
      HANDLE h = FindFirstFileA( args[i], &fd );
      char const * slash = strrchr( args[i], '\\' ), * fslash = strrchr( args[i], '/' );
      int dirlen = 0, found = 0;
      if ( fslash && ( !slash || ( fslash > slash ) ) )   // the later of the two separators (either may be absent)
      {
        slash = fslash;
      }
      if ( slash )
      {
        dirlen = (int)( slash - args[i] ) + 1;
      }
      if ( h != INVALID_HANDLE_VALUE )
      {
        do
        {
          if ( !( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
          {
            char * path = (char*) malloc( dirlen + strlen( fd.cFileName ) + 1 );
            memcpy( path, args[i], dirlen );
            strcpy( path + dirlen, fd.cFileName );
            load_one_file( path );
            found = 1;
          }
        } while ( FindNextFileA( h, &fd ) );
        FindClose( h );
      }
      if ( !found )
      {
        printf( "No timing files match %s\n", args[i] );
        exit( 2 );
      }
      continue;
    }
    #endif
    load_one_file( args[i] );
  }

  for( i = 0 ; i < numfileinfo ; i++ )
  {
    flag_outliers( fi + i );
  }
}

//=============================================================================
// the header's cost model, with the R table entry as a parameter so the fit can try values

typedef struct cell_geom
{
  int taps_h, taps_v, bucket, period1;
  double inv_h, inv_v;   // input / output per axis, with WRAP's margins added to the input (what the header's model uses)
} cell_geom;

static void cell_geometry( cell_geom * g, int ox, int oy, int ix, int iy, int filter, int edge )
{
  stbir__radius_callback_new * radius = stbir__builtin_radii[ filter ];
  stbir__support_callback_new * support = stbir__builtin_supports[ filter ];
  stbir__scale_info s_h, s_v;   // (just the scales - enough for the tap counts)

  memset( &s_h, 0, sizeof( s_h ) );
  memset( &s_v, 0, sizeof( s_v ) );
  s_h.scale = (stbir_real) ox / (stbir_real) ix;
  s_h.inv_scale = (stbir_real) ix / (stbir_real) ox;
  s_v.scale = (stbir_real) oy / (stbir_real) iy;
  s_v.inv_scale = (stbir_real) iy / (stbir_real) oy;

  g->taps_h = stbir__get_filter_pixel_width( radius, support, 0, &s_h, 0 );
  g->taps_v = stbir__get_filter_pixel_width( radius, support, 0, &s_v, 0 );
  g->bucket = stbir__horizontal_cost_bucket( g->taps_h );
  g->period1 = ( ox <= ix ) && ( ( ix % ox ) == 0 );   // integer horizontal downsample (or 1:1): the period 1 kernels
  g->inv_h = (double)( ix + ( ( edge == STBIR_EDGE_WRAP ) ? g->taps_h : 0 ) ) / (double) ox;
  g->inv_v = (double)( iy + ( ( edge == STBIR_EDGE_WRAP ) ? g->taps_v : 0 ) ) / (double) oy;
}

// vertical first? for a cell, with ratio R = horizontal cost / vertical cost per byte (the header's formula)
static int cost_model_vfirst( cell_geom const * g, double R )
{
  double v_cost = (double)( g->taps_v + 1 ) * g->inv_h + ( g->inv_h + 1.0 ) * R;
  double h_cost = g->inv_v * ( g->inv_h + 1.0 ) * R + (double)( g->taps_v + 1 );
  return v_cost <= h_cost;
}

// the header's current table entry for a cell
static double current_R( cell_geom const * g, int chanind )
{
  return ( g->period1 ? stbir__horizontal_cost_period1 : stbir__horizontal_cost )[ chanind ][ g->bucket ];
}

// the header's decision for a cell
static int vert_first( int chanind, int ox, int oy, int ix, int iy, int filter, int edge )
{
  cell_geom g;
  cell_geometry( &g, ox, oy, ix, iy, filter, edge );
  return cost_model_vfirst( &g, current_R( &g, chanind ) );
}

//=============================================================================
// outliers: a cell whose two orders were not measured alike (a throttling episode or an interruption during one of
//   them) has a V/H ratio out of line with the cells around it. The heuristic: each cell's residual - measured ln(V/H)
//   minus the model's - is compared with the median residual of its neighbors in the output size grid, on the
//   assumption that the model's error changes slowly between neighbors while a bad measurement doesn't. Cells out of
//   line are left out of the fits and the loss totals, and reported per file (a machine that needs more -update
//   rounds shows up there). A cell that is uniformly slow - both orders inflated alike - keeps its ratio and stays in.

#define OUTLIER_NEIGHBOR_RATIO 1.5    // a residual beyond ln(this) from the neighbors' median is out of line
#define OUTLIER_ABSOLUTE_RATIO 6.0    // no resize is this lopsided between the orders on any machine we have seen

static double median_of( double * v, int n )
{
  int i, j;
  for( i = 1 ; i < n ; i++ )
  {
    double t = v[i];
    for( j = i ; ( j > 0 ) && ( v[j-1] > t ) ; j-- )
    {
      v[j] = v[j-1];
    }
    v[j] = t;
  }
  return ( n & 1 ) ? v[ n / 2 ] : 0.5 * ( v[ n / 2 - 1 ] + v[ n / 2 ] );
}

static void flag_outliers( fileinfo * f )
{
  int dx = f->dimensionx, dy = f->dimensiony;
  int grid, ncells = dx * dy;
  double * lr = (double*) malloc( sizeof( double ) * ncells );
  double limit = log( OUTLIER_NEIGHBOR_RATIO ), absolute = log( OUTLIER_ABSOLUTE_RATIO );

  for( grid = 0 ; grid < f->numinputrects * f->numtypes ; grid++ )   // one output size grid per ( input size, channel type )
  {
    int ir = grid / f->numtypes, chanind = grid % f->numtypes;
    int ix = f->inputrects[ ir * 2 ], iy = f->inputrects[ ir * 2 + 1 ];
    int * ts = f->timings + 2 * grid * ncells;
    unsigned char * ig = f->ignored + grid * ncells;
    int c, hh, ww;

    // the residuals: measured ln(V/H) minus the cost model's ln(v_cost/h_cost) (1e9 = unusable cell)
    for( hh = 0 ; hh < dy ; hh++ )
    {
      for( ww = 0 ; ww < dx ; ww++ )
      {
        cell_geom g;
        double R, v_cost, h_cost;
        c = hh * dx + ww;
        if ( ( ts[2*c] <= 0 ) || ( ts[2*c+1] <= 0 ) )
        {
          lr[c] = 1e9;
          continue;
        }
        cell_geometry( &g, OX( *f, ir, ww ), OY( *f, ir, hh ), ix, iy, f->filter, f->edge );
        R = current_R( &g, chanind );
        v_cost = (double)( g.taps_v + 1 ) * g.inv_h + ( g.inv_h + 1.0 ) * R;
        h_cost = g.inv_v * ( g.inv_h + 1.0 ) * R + (double)( g.taps_v + 1 );
        lr[c] = log( (double) ts[2*c] / (double) ts[2*c+1] ) - log( v_cost / h_cost );
      }
    }

    for( hh = 0 ; hh < dy ; hh++ )
    {
      for( ww = 0 ; ww < dx ; ww++ )
      {
        int n = 0, dh, dw;
        double nb[8];
        c = hh * dx + ww;
        if ( lr[c] > 1e8 )
        {
          ig[c] = 1;
          continue;
        }
        if ( fabs( log( (double) ts[2*c] / (double) ts[2*c+1] ) ) > absolute )
        {
          ig[c] = 1;
          continue;
        }
        for( dh = -1 ; dh <= 1 ; dh++ )
        {
          for( dw = -1 ; dw <= 1 ; dw++ )
          {
            int h2 = hh + dh, w2 = ww + dw;
            if ( ( dh || dw ) && ( h2 >= 0 ) && ( h2 < dy ) && ( w2 >= 0 ) && ( w2 < dx ) && ( lr[ h2 * dx + w2 ] < 1e8 ) )
            {
              nb[ n++ ] = lr[ h2 * dx + w2 ];
            }
          }
        }
        if ( ( n >= 3 ) && ( fabs( lr[c] - median_of( nb, n ) ) > limit ) )
        {
          ig[c] = 1;
        }
      }
    }

    for( c = 0 ; c < ncells ; c++ )
    {
      f->ignored_count += ig[c];
    }
  }
  free( lr );
}

// the file name without its directory
static char const * short_name( char const * filename )
{
  char const * n = strrchr( filename, '\\' );
  if ( !n )
  {
    n = strrchr( filename, '/' );
  }
  return n ? n + 1 : filename;
}

// the ignored cells per file (cpu) and per set - lots of them means the machine needs more -update -runcool rounds
static void print_ignored( void )
{
  int i, j, any = 0;
  for( i = 0 ; i < numfileinfo ; i++ )
  {
    int total = 0, cells = 0, first = 1;
    for( j = 0 ; j < i ; j++ )
    {
      if ( strcmp( fi[i].filename, fi[j].filename ) == 0 )
      {
        first = 0;
      }
    }
    if ( !first )
    {
      continue;
    }
    for( j = i ; j < numfileinfo ; j++ )
    {
      if ( strcmp( fi[i].filename, fi[j].filename ) == 0 )
      {
        total += fi[j].ignored_count;
        cells += fi[j].timing_count;
      }
    }
    if ( !any )
    {
      printf( "\ncells left out as outliers (a V/H ratio out of line with its neighbors, or beyond %g:1):\n", OUTLIER_ABSOLUTE_RATIO );
      any = 1;
    }
    printf( "  %-48s %5d of %6d (%4.1f%%)", short_name( fi[i].filename ), total, cells, 100.0 * total / cells );
    for( j = i ; j < numfileinfo ; j++ )
    {
      if ( ( strcmp( fi[i].filename, fi[j].filename ) == 0 ) && fi[j].ignored_count )
      {
        printf( "  %s %d", fi[j].setname, fi[j].ignored_count );
      }
    }
    printf( "\n" );
  }
}

// how much each SIMD level counts in the fits and the weighted totals: SIMD4 (SSE2 / NEON) is what most users run,
//   scalar the fallback, SIMD8 (AVX) less common, SIMD16 (AVX-512) a quarter of SIMD4
static double simd_weight( int simd )
{
  return ( simd == 1 ) ? 2.0 : ( simd == 2 ) ? 0.8 : ( simd == 3 ) ? 0.5 : 1.0;
}

// and how much a resize counts by its scale: the everyday range (both axes within 0.5x .. 2x) double, tiny reductions
//   (an axis below 1/8) half, everything else 1
static double cell_weight( int ox, int oy, int ix, int iy )
{
  double sx = (double) ox / (double) ix, sy = (double) oy / (double) iy;
  double lo = ( sx < sy ) ? sx : sy, hi = ( sx < sy ) ? sy : sx;
  if ( ( lo >= 0.5 ) && ( hi <= 2.0 ) )
  {
    return 2.0;
  }
  if ( lo < 0.125 )
  {
    return 0.5;
  }
  return 1.0;
}

// walk every cell of every file that isn't an outlier: callback( file index, channel index, ix, iy, ox, oy, VF, HF, user )
typedef void cell_callback( int findex, int chanind, int ix, int iy, int ox, int oy, int VF, int HF, void * user );

static void for_each_cell( cell_callback * cb, void * user )
{
  int findex;
  for( findex = 0 ; findex < numfileinfo ; findex++ )
  {
    int * ts = fi[findex].timings;
    unsigned char const * ig = fi[findex].ignored;
    int ir;
    for( ir = 0 ; ir < fi[findex].numinputrects ; ir++ )
    {
      int ix = fi[findex].inputrects[ir*2], iy = fi[findex].inputrects[ir*2+1];
      int chanind;
      for( chanind = 0 ; chanind < fi[findex].numtypes ; chanind++ )
      {
        int hh, ww;
        for( hh = 0 ; hh < fi[findex].dimensiony ; hh++ )
        {
          for( ww = 0 ; ww < fi[findex].dimensionx ; ww++ )
          {
            if ( !*ig )
            {
              cb( findex, chanind, ix, iy, OX( fi[findex], ir, ww ), OY( fi[findex], ir, hh ), ts[0], ts[1], user );
            }
            ts += 2;
            ig++;
          }
        }
      }
    }
  }
}

#endif
