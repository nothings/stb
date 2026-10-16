// vf_train - evaluates and fits the vertical-first / horizontal-first predictor of stb_image_resize2 from dotimings'
//   .timings files (see vf_common.h for the reader and the cost model). Portable (no GUI); vf_view is the visualizer.
#include "vf_common.h"

// the same ( file, SIMD level ) group? the fits and the weighted totals are per group
static int same_group( int a, int b )
{
  return ( strcmp( fi[a].filename, fi[b].filename ) == 0 ) && ( fi[a].simd == fi[b].simd );
}

// is this the first set of its group?
static int first_of_group( int i )
{
  int j;
  for( j = 0 ; j < i ; j++ )
  {
    if ( same_group( i, j ) )
    {
      return 0;
    }
  }
  return 1;
}

//=============================================================================
// eval: how much time the header's predictor loses against the best order per cell, per set and per channel count

typedef struct model_stats
{
  double best_ms, lost_ms;   // per file [findex], plus per channel [5] in the second set
  double best_w, lost_w;     // the same, each cell weighted by cell_weight (for the normalized weighted total)
  int cells, wrong;
} model_stats;

static model_stats file_stats[VF_MAX_SETS], chan_stats[5];

static void eval_cell( int findex, int chanind, int ix, int iy, int ox, int oy, int VF, int HF, void * user )
{
  double scale = fi[findex].scale_time;   // clocks -> ms
  int best = ( VF < HF ) ? VF : HF;
  int v = vert_first( chanind, ox, oy, ix, iy, fi[findex].filter, fi[findex].edge );
  double lost = ( ( v ? VF : HF ) - best ) * scale;
  double w = cell_weight( ox, oy, ix, iy );
  model_stats * s[2];
  int i;
  (void) user;

  s[0] = &file_stats[findex];
  s[1] = &chan_stats[chanind];
  for( i = 0 ; i < 2 ; i++ )
  {
    s[i]->cells++;
    s[i]->best_ms += best * scale;
    s[i]->lost_ms += lost;
    s[i]->wrong += ( lost > 0 );
    s[i]->best_w += best * scale * w;
    s[i]->lost_w += lost * w;
  }
}

static void print_model_stats( char const * name, model_stats const * s )
{
  printf( "  %-52s %6d cells  best %9.1f ms | wrong %5d (%4.1f%%)  lost %8.1f ms (%5.2f%%)\n",
    name, s->cells, s->best_ms, s->wrong, 100.0 * s->wrong / s->cells, s->lost_ms, 100.0 * s->lost_ms / s->best_ms );
}

static void eval( void )
{
  model_stats total = {0};
  double w_lost = 0, w_sum = 0;
  char buf[128];
  int i, j;

  memset( file_stats, 0, sizeof( file_stats ) );
  memset( chan_stats, 0, sizeof( chan_stats ) );
  for_each_cell( eval_cell, 0 );

  printf( "time lost against the best order per cell (ms are the file's own clock):\n" );
  for( i = 0 ; i < numfileinfo ; i++ )
  {
    sprintf( buf, "%.40s %s", short_name( fi[i].filename ), fi[i].setname );
    print_model_stats( buf, &file_stats[i] );
    total.cells += file_stats[i].cells;
    total.best_ms += file_stats[i].best_ms;
    total.wrong += file_stats[i].wrong;
    total.lost_ms += file_stats[i].lost_ms;
  }
  printf( "\n" );
  for( i = 0 ; i < fi[0].numtypes ; i++ )
  {
    sprintf( buf, "%d channels (all files)", fi[0].effective[i] );
    print_model_stats( buf, &chan_stats[i] );
  }
  printf( "\n" );
  print_model_stats( "TOTAL", &total );

  // the measure fit optimizes: per group, the loss as a fraction of the group's best time, weighted
  for( i = 0 ; i < numfileinfo ; i++ )
  {
    double best = 0, lost = 0;
    if ( !first_of_group( i ) )
    {
      continue;
    }
    for( j = i ; j < numfileinfo ; j++ )
    {
      if ( same_group( i, j ) )
      {
        best += file_stats[j].best_w;
        lost += file_stats[j].lost_w;
      }
    }
    if ( best > 0 )
    {
      w_lost += simd_weight( fi[i].simd ) * lost / best;
      w_sum += simd_weight( fi[i].simd );
    }
  }
  if ( w_sum > 0 )
  {
    printf( "\n  normalized per (file, SIMD level), weighted scalar 1.0 / SIMD4 2.0 / SIMD8 0.8 / SIMD16 0.5 and by scale (0.5x..2x double, below 1/8 half): %.3f%%\n", 100.0 * w_lost / w_sum );
  }
}

//=============================================================================
// worst: per set, the cells where the predictor loses the most time

#define WORST_N 6

typedef struct worst_cell
{
  double lost_ms, pct;
  int ch, ix, iy, ox, oy, taps_h, taps_v, picked_v;
  int VF, HF;   // microseconds
} worst_cell;

typedef struct worst_set
{
  worst_cell list[WORST_N];
  double total;
} worst_set;

static worst_set worst[VF_MAX_SETS];

static void worst_insert( worst_cell * list, worst_cell const * c )
{
  int i, j;
  for( i = 0 ; i < WORST_N ; i++ )
  {
    if ( c->lost_ms > list[i].lost_ms )
    {
      for( j = WORST_N - 1 ; j > i ; j-- )
      {
        list[j] = list[j-1];
      }
      list[i] = *c;
      return;
    }
  }
}

static void worst_cell_cb( int findex, int chanind, int ix, int iy, int ox, int oy, int VF, int HF, void * user )
{
  cell_geom g;
  double scale = fi[findex].scale_time;
  int best = ( VF < HF ) ? VF : HF;
  int v = vert_first( chanind, ox, oy, ix, iy, fi[findex].filter, fi[findex].edge );
  worst_cell c;
  (void) user;

  cell_geometry( &g, ox, oy, ix, iy, fi[findex].filter, fi[findex].edge );
  c.ch = fi[findex].effective[chanind];
  c.ix = ix;
  c.iy = iy;
  c.ox = ox;
  c.oy = oy;
  c.taps_h = g.taps_h;
  c.taps_v = g.taps_v;
  c.VF = (int)( VF * scale * 1000 );
  c.HF = (int)( HF * scale * 1000 );
  c.picked_v = v;
  c.lost_ms = ( ( v ? VF : HF ) - best ) * scale;
  c.pct = 100.0 * ( ( v ? VF : HF ) - best ) / (double) best;

  worst[findex].total += c.lost_ms;
  if ( c.lost_ms > 0 )
  {
    worst_insert( worst[findex].list, &c );
  }
}

static void worst_mode( void )
{
  int i, j;

  memset( worst, 0, sizeof( worst ) );
  for_each_cell( worst_cell_cb, 0 );

  for( i = 0 ; i < numfileinfo ; i++ )
  {
    printf( "\n%s  %s  (%.1f ms lost in this set)\n", short_name( fi[i].filename ), fi[i].setname, worst[i].total );
    for( j = 0 ; ( j < WORST_N ) && ( worst[i].list[j].lost_ms > 0 ) ; j++ )
    {
      worst_cell const * c = worst[i].list + j;
      printf( "  %dch %4dx%-4d -> %4dx%-4d  taps %2dx%-2d  picked %s: v %.2f ms  h %.2f ms  lost %.2f ms (%.0f%%)\n",
        c->ch, c->ix, c->iy, c->ox, c->oy, c->taps_h, c->taps_v, c->picked_v ? "v" : "h", c->VF / 1000.0, c->HF / 1000.0, c->lost_ms, c->pct );
    }
  }
}

//=============================================================================
// fit: fit the R tables to the timings. A cell only depends on R[chan][bucket][period1], so each table entry is a
//   one dimensional search over its own cells: pick the R with the least time lost.
//
//   A cell's loss is a fraction of the total best time of its group - the sets from one file at one SIMD level - so a
//   slow scalar millisecond is not worth 3-5 AVX ones and a slow machine does not outweigh a fast one. The groups are
//   then weighted by simd_weight. group_weight[findex] = level weight / ( that group's total best ms ).

static double group_weight[VF_MAX_SETS];

static void group_best_cell( int findex, int chanind, int ix, int iy, int ox, int oy, int VF, int HF, void * user )
{
  double * best = (double*) user;
  (void) chanind;
  best[findex] += ( ( VF < HF ) ? VF : HF ) * fi[findex].scale_time * cell_weight( ox, oy, ix, iy );
}

static void compute_group_weights( void )
{
  static double best[VF_MAX_SETS];
  int i, j;

  memset( best, 0, sizeof( best ) );
  for_each_cell( group_best_cell, best );

  for( i = 0 ; i < numfileinfo ; i++ )
  {
    double group = 0;
    for( j = 0 ; j < numfileinfo ; j++ )
    {
      if ( same_group( i, j ) )
      {
        group += best[j];
      }
    }
    group_weight[i] = ( group > 0 ) ? simd_weight( fi[i].simd ) / group : 0;
  }
}

#define FIT_STEPS 400

static double fit_lost[5][9][2][FIT_STEPS];   // [chan][bucket][period1][R step] loss (a fraction of the group's time)
static double fit_cur_lost[5][9][2];
static int fit_cells[5][9][2];

// the R values tried: 0.5 .. 20, log spaced
static double fit_R( int step )
{
  return 0.5 * pow( 40.0, (double) step / (double)( FIT_STEPS - 1 ) );
}

static void fit_cell( int findex, int chanind, int ix, int iy, int ox, int oy, int VF, int HF, void * user )
{
  cell_geom g;
  int best = ( VF < HF ) ? VF : HF, step;
  double scale = fi[findex].scale_time * group_weight[findex] * cell_weight( ox, oy, ix, iy );
  double lost_if_v = ( VF - best ) * scale, lost_if_h = ( HF - best ) * scale;
  (void) user;

  cell_geometry( &g, ox, oy, ix, iy, fi[findex].filter, fi[findex].edge );
  fit_cells[chanind][g.bucket][g.period1]++;
  fit_cur_lost[chanind][g.bucket][g.period1] += cost_model_vfirst( &g, current_R( &g, chanind ) ) ? lost_if_v : lost_if_h;
  for( step = 0 ; step < FIT_STEPS ; step++ )
  {
    fit_lost[chanind][g.bucket][g.period1][step] += cost_model_vfirst( &g, fit_R( step ) ) ? lost_if_v : lost_if_h;
  }
}

static void print_table( char const * name, double fitted[5][9][2], int p1 )
{
  int c, b;
  printf( "static float %s[5][9] =\n{\n", name );
  for( c = 0 ; c < 5 ; c++ )
  {
    printf( "  {" );
    for( b = 0 ; b < 9 ; b++ )
    {
      printf( " %6.3ff%s", fitted[c][b][p1], ( b < 8 ) ? "," : "" );
    }
    printf( " },\n" );
  }
  printf( "};\n" );
}

static void fit( void )
{
  double fitted[5][9][2];
  double total_cur = 0, total_fit = 0, weight_sum = 0;
  int groups = 0;
  int c, b, p1, i;

  memset( fit_lost, 0, sizeof( fit_lost ) );
  memset( fit_cur_lost, 0, sizeof( fit_cur_lost ) );
  memset( fit_cells, 0, sizeof( fit_cells ) );
  compute_group_weights();
  for( i = 0 ; i < numfileinfo ; i++ )
  {
    if ( first_of_group( i ) )
    {
      groups++;
      weight_sum += simd_weight( fi[i].simd );
    }
  }
  for_each_cell( fit_cell, 0 );

  printf( "losses are fractions of each (file, SIMD level) group's best time, weighted scalar 1.0 / SIMD4 2.0 / SIMD8 0.8 / SIMD16 0.5 and by scale\n  (both axes 0.5x..2x double, an axis below 1/8 half), over %d groups\n", groups );
  printf( "per table entry: cells, loss with the current R, with the fitted R\n" );
  for( p1 = 0 ; p1 < 2 ; p1++ )
  {
    printf( "\n%s\n", p1 ? "period 1 (integer horizontal downsample)" : "general" );
    for( c = 0 ; c < 5 ; c++ )
    {
      for( b = 0 ; b < 9 ; b++ )
      {
        double cur = ( p1 ? stbir__horizontal_cost_period1 : stbir__horizontal_cost )[c][b];
        double best_lost = 1e300, best_dist = 1e300;
        int step, best_step = 0;

        for( step = 0 ; step < FIT_STEPS ; step++ )
        {
          if ( fit_lost[c][b][p1][step] < best_lost )
          {
            best_lost = fit_lost[c][b][p1][step];
          }
        }

        // several R values usually tie (the bucket's cells don't separate them): keep the one nearest the current
        //   table value, so an entry the data doesn't constrain isn't moved further than it has to be
        for( step = 0 ; step < FIT_STEPS ; step++ )
        {
          if ( fit_lost[c][b][p1][step] <= best_lost + 1e-12 )
          {
            double dist = fabs( log( fit_R( step ) ) - log( cur ) );
            if ( dist < best_dist )
            {
              best_dist = dist;
              best_step = step;
            }
          }
        }

        fitted[c][b][p1] = fit_cells[c][b][p1] ? fit_R( best_step ) : cur;   // nothing measured - keep the current value
        total_cur += fit_cur_lost[c][b][p1];
        if ( fit_cells[c][b][p1] )
        {
          total_fit += best_lost;
          printf( "  ch %d bucket %d: %6d cells  current R %6.3f lost %7.3f%%   fitted R %6.3f lost %7.3f%%\n",
            fi[0].effective[c], b, fit_cells[c][b][p1], cur, 100.0 * fit_cur_lost[c][b][p1], fitted[c][b][p1], 100.0 * best_lost );
        }
      }
    }
  }
  printf( "\ntotal loss: current tables %.3f%%, fitted %.3f%%  (weighted average over the groups, 0%% = always the faster order)\n", 100.0 * total_cur / weight_sum, 100.0 * total_fit / weight_sum );

  printf( "\n// fitted to the sampling zone timings of test/vfirst/timings (vf_train fit)\n" );
  print_table( "stbir__horizontal_cost", fitted, 0 );
  print_table( "stbir__horizontal_cost_period1", fitted, 1 );
}

//=============================================================================

static void info( void )
{
  int findex;
  for( findex = 0 ; findex < numfileinfo ; findex++ )
  {
    fileinfo const * f = fi + findex;
    int i, h, m, s;

    if ( findex )
    {
      printf( "\n" );
    }
    printf( "Timing file: %s   set: %s\n", f->filename, f->setname );
    h = f->milliseconds / 3600000;
    m = ( f->milliseconds - h * 3600000 ) / 60000;
    s = ( f->milliseconds - h * 3600000 - m * 60000 ) / 1000;
    printf( "cpu type %d, whole run %dh %dm %ds, %.0f clocks/sec\n", f->cpu, h, m, s, 1000.0 / f->scale_time );
    printf( "%d x %d output sizes per input size; input sizes: ", f->dimensionx, f->dimensiony );
    for( i = 0 ; i < f->numinputrects ; i++ )
    {
      printf( "%dx%d ", f->inputrects[i*2], f->inputrects[i*2+1] );
    }
    printf( "\noutput widths (first input): " );
    for( i = 0 ; i < f->dimensionx ; i++ )
    {
      printf( "%d ", OX( *f, 0, i ) );
    }
    printf( "\noutput heights (first input): " );
    for( i = 0 ; i < f->dimensiony ; i++ )
    {
      printf( "%d ", OY( *f, 0, i ) );
    }
    printf( "\nchannel counts: " );
    for( i = 0 ; i < f->numtypes ; i++ )
    {
      printf( "%d ", f->effective[i] );
    }
    printf( "\n" );
  }
}

int main( int argc, char ** argv )
{
  if ( argc < 3 )
  {
   err:
    printf( "vf_train info  [timing files...]  - what is in each file\n" );
    printf( "vf_train eval  [timing files...]  - time lost by the header's predictor against the best order, per set and channel count\n" );
    printf( "vf_train fit   [timing files...]  - fit the predictor's R tables to the timings, print them as C for the header\n" );
    printf( "vf_train worst [timing files...]  - per set, the cells where the predictor loses the most\n" );
    printf( "(vf_view shows the right / wrong picture of a file)\n" );
    return 1;
  }

  load_files( argv + 2, argc - 2 );

  if ( !strcmp( argv[1], "info" ) )
  {
    info();
  }
  else if ( !strcmp( argv[1], "eval" ) )
  {
    eval();
  }
  else if ( !strcmp( argv[1], "fit" ) )
  {
    fit();
  }
  else if ( !strcmp( argv[1], "worst" ) )
  {
    worst_mode();
  }
  else
  {
    goto err;
  }

  print_ignored();
  return 0;
}
