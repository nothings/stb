// dotimings - times stb_image_resize2 with the vertical pass first and with the horizontal pass first, over a set of
//   resizes, at every SIMD level the machine supports (scalar, SSE2, AVX and AVX-512 on x86; scalar and NEON on arm), and
//   writes one .timings file for the machine. vf_train.c reads these to evaluate and fit the vertical-first predictor.
//
//   dotimings [-update] [-runcool] [-loop] [outfilename]
//     times the representative sets (below) and writes <cpu>.timings: every cell of every set, both orders forced, each
//     the minimum over runs until 16 in a row fail to improve it; the two orders' runs alternate to reduce clock drift
//     between them (see time_cell in dotimings_impl.c).
//     -update   read the file this run would write and start every cell's minimum at its value, so repeated runs can
//               only improve the file (the sets have to match: same levels, filters, sizes, channel types). the file
//               has no idea which header it was timed with: after a change to the resizer's kernels, delete it and
//               time from scratch, or the old minimums hide the change
//     -runcool  pause between cells - roughly as long as the cells took - so the cpu never runs hot for long (laptops
//               throttle)
//     -loop     run round after round until stopped; -update -runcool -loop left running converges a machine that
//               runs hot to its cool minimums
//   On Windows the process also keeps the machine from sleeping while it runs (SetThreadExecutionState); on the Mac run it
//   under caffeinate -i (do_mac_timings.bat does).
//
//   The timing body is dotimings_impl.c, compiled once per SIMD level (dotimings_scalar.c / _simd4.c / _avx.c / _avx512.c)
//   and linked in here; this file only drives it. Build with test.cdep (dotimings.mak) or dotimings.sh.
//
//   File format (VFT3):
//     32 int header: 'VFT3', cpu (1 x86, 2 arm), number of sets, number of channel types, types[5], effective channels[5],
//       reserved, total ms, total profile clocks (int64 at ints 16-17), the rest reserved
//     per set: simd level (0 scalar, 1 four wide, 2 eight wide, 3 sixteen wide), filter (stbir_filter), edge (stbir_edge), number of
//       input sizes, dimx, dimy, per input size: ix, iy, ox[dimx], oy[dimy], then for each input size, channel type,
//       oy, ox: vertical-first clocks, horizontal-first clocks

#ifndef _WIN32
#define _GNU_SOURCE   // sched_setaffinity
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stbir enums and types only (the implementation lives in the per level copies)
#include "stb_image_resize2.h"
#include "dotimings.h"

#ifdef _MSC_VER
  #include <windows.h>
  #include <mmsystem.h>
  #pragma comment( lib, "winmm.lib" )
  #pragma warning(disable:4127)
#else
  #include <time.h>
  #include <sys/resource.h>
  #ifndef __APPLE__
    #include <sched.h>
  #endif
  #ifdef __APPLE__
    #include <mach/mach.h>
    #include <mach/thread_policy.h>
    #include <pthread.h>
    #include <sys/qos.h>
  #endif
#endif

#define HEADER 32   // the file header, in ints (see the format above)

// the options
const int dt_types[ DT_TYPES ] = { STBIR_1CHANNEL, STBIR_2CHANNEL, STBIR_RGB, STBIR_4CHANNEL, STBIR_RGBA };
const int dt_effective[ DT_TYPES ] = { 1, 2, 3, 4, 7 };
int dt_update = 0;              // -update: the cells start at the previous file's values
static int dt_runcool = 0;      // -runcool: pause between cells
static int dt_loop = 0;         // -loop: round after round

//=============================================================================
// a millisecond wall clock (for progress, the cool-down pauses and the file's total) and a sleep

static int get_milliseconds( void )
{
  #ifdef _WIN32
  return (int) timeGetTime();   // 1 ms once timeBeginPeriod(1) is in effect (GetTickCount is ~16 ms)
  #else
  struct timespec ts;
  clock_gettime( CLOCK_MONOTONIC, &ts );
  return (int)( ts.tv_sec * 1000 + ts.tv_nsec / 1000000 );
  #endif
}

static void dt_sleep_ms( int ms )
{
  #ifdef _WIN32
  Sleep( ms );
  #else
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = ( ms % 1000 ) * 1000000L;
  nanosleep( &ts, 0 );
  #endif
}

//=============================================================================
// -runcool: after every cell, once the cells since the last pause add up to a quarter second of work, sleep about as
//   long as they took (a 50% duty cycle - the timings themselves are minimums, so the idle time costs nothing but
//   wall clock). the progress estimate includes the pauses, since it works from elapsed time.

static int cool_work_start = -1;

// after a pause the core is at its idle clock and takes a few (on some power plans tens of) milliseconds to ramp
//   back. a big cell's runs outlast that and its minimum ignores the slow first ones, but a 240x240 cell's whole run
//   block can fit inside the ramp - so spin for a moment before timing resumes (a dependent chain, real work)
static volatile unsigned int warm_sink;

static void dt_warm_up( int ms )
{
  int start = get_milliseconds();
  unsigned int x = 1;
  do
  {
    int i;
    for( i = 0 ; i < 100000 ; i++ )
    {
      x = x * 1664525u + 1013904223u;
    }
    warm_sink = x;
  } while ( get_milliseconds() - start < ms );
}

void dt_after_cell( void )
{
  int now, worked;

  if ( !dt_runcool )
  {
    return;
  }

  now = get_milliseconds();
  if ( cool_work_start < 0 )
  {
    cool_work_start = now;
    return;
  }

  worked = now - cool_work_start;
  if ( worked >= 250 )
  {
    dt_sleep_ms( worked );
    dt_warm_up( 25 );
    cool_work_start = get_milliseconds();
  }
}

//=============================================================================
// run above everything else on the box: the timings are minimums, so a competing process mostly costs time, but a
//   busy one (or, on Apple silicon, being scheduled onto an efficiency core) skews the ratio between the two orders too.
//   and stay on one core: a migration mid cell lands the two orders on different caches (or core types). the core is
//   the one we are already on, unless that is core 0 (where the interrupts land)

static void pin_to_core( void )
{
  #ifdef _WIN32
  {
    unsigned int core = GetCurrentProcessorNumber();
    SYSTEM_INFO si;
    GetSystemInfo( &si );
    if ( ( core == 0 ) && ( si.dwNumberOfProcessors > 1 ) )
    {
      core = 1;
    }
    if ( core < 64 )
    {
      if ( SetThreadAffinityMask( GetCurrentThread(), (DWORD_PTR) 1 << core ) )
      {
        printf( "pinned to core %u\n", core );
        return;
      }
    }
    printf( "could not pin to a core\n" );
  }
  #elif defined( __APPLE__ )
  printf( "not pinned (macOS has no thread affinity; the QoS class below keeps us on a performance core)\n" );
  #else
  {
    int core = sched_getcpu();
    cpu_set_t set;
    if ( core == 0 )
    {
      core = 1;
    }
    if ( ( core < 0 ) || ( core >= CPU_SETSIZE ) )   // sched_getcpu failed, or a core past the set's size
    {
      printf( "could not pin to a core\n" );
      return;
    }
    CPU_ZERO( &set );
    CPU_SET( core, &set );
    if ( sched_setaffinity( 0, sizeof( set ), &set ) == 0 )
    {
      printf( "pinned to core %d\n", core );
    }
    else
    {
      printf( "could not pin to a core\n" );
    }
  }
  #endif
}

static void raise_priority( void )
{
  pin_to_core();
  #ifdef _WIN32
  {
    int ok = SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS ) && SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST );
    printf( "priority: %s\n", ok ? "high (process), highest (thread)" : "could not raise" );
    // 1 ms timer resolution for the whole run: timeGetTime reads to the millisecond and Sleep() wakes on time (the
    //   default 15.6 ms tick would round both up). undone by the process exiting.
    timeBeginPeriod( 1 );
    // and don't let the machine idle-sleep in the middle of a run (this is a process-lifetime request, no power
    //   settings are changed - it ends when we exit)
    if ( SetThreadExecutionState( ES_CONTINUOUS | ES_SYSTEM_REQUIRED ) )
    {
      printf( "sleep: blocked while running\n" );
    }
  }
  #elif defined( __APPLE__ )
  {
    // the interactive QoS class first - it is what keeps the scheduler from parking us on an efficiency core, and it
    //   is refused (EPERM) once a Mach policy has been set on the thread. then Mach: leave the timeshare class (fixed
    //   priority) with the maximum importance. nice -20 on top, which only sticks as root.
    thread_extended_policy_data_t ext = { 0 };            // timeshare = 0: fixed priority
    thread_precedence_policy_data_t prec = { 63 };        // importance, the maximum for user threads
    mach_port_t self = pthread_mach_thread_np( pthread_self() );
    int q = pthread_set_qos_class_self_np( QOS_CLASS_USER_INTERACTIVE, 0 );
    kern_return_t k1 = thread_policy_set( self, THREAD_EXTENDED_POLICY, (thread_policy_t) &ext, THREAD_EXTENDED_POLICY_COUNT );
    kern_return_t k2 = thread_policy_set( self, THREAD_PRECEDENCE_POLICY, (thread_policy_t) &prec, THREAD_PRECEDENCE_POLICY_COUNT );
    int n = setpriority( PRIO_PROCESS, 0, -20 );
    printf( "priority: qos interactive %s, mach fixed %s, precedence %s, nice -20 %s\n", ( q == 0 ) ? "ok" : "failed", ( k1 == KERN_SUCCESS ) ? "ok" : "failed", ( k2 == KERN_SUCCESS ) ? "ok" : "failed", ( n == 0 ) ? "ok" : "needs root" );
  }
  #else
  {
    int n = setpriority( PRIO_PROCESS, 0, -20 );
    printf( "priority: nice -20 %s\n", ( n == 0 ) ? "ok" : "needs root (running at normal priority)" );
  }
  #endif
}

//=============================================================================
// a one line sanity check of the core we ended up on: a dependent add / xor chain takes two cycles per iteration on
//   the cores we have timed, so iterations per second x 2 estimates the clock we are actually getting. On Apple silicon
//   it tells a performance core (~3.2 GHz on an M1) from an efficiency core (~2.0), which no API will. Best of three,
//   so the clock has ramped.

static double now_seconds( void )
{
  #ifdef _WIN32
  LARGE_INTEGER t, f;
  QueryPerformanceCounter( &t );
  QueryPerformanceFrequency( &f );
  return (double) t.QuadPart / (double) f.QuadPart;
  #else
  struct timespec ts;
  clock_gettime( CLOCK_MONOTONIC, &ts );
  return (double) ts.tv_sec + ts.tv_nsec * 1e-9;
  #endif
}

static volatile unsigned long long calibration_sink;

static void print_calibration( void )
{
  double best = 0;
  int pass;
  for( pass = 0 ; pass < 3 ; pass++ )
  {
    unsigned long long x = 0x9E3779B97F4A7C15ULL, y = 12345, i, n = 400 * 1000 * 1000;
    double t0 = now_seconds(), t1, ghz;
    for( i = 0 ; i < n ; i++ )   // two dependent single cycle ops
    {
      x += y;
      y ^= x;
    }
    t1 = now_seconds();
    calibration_sink = x + y;
    ghz = ( (double) n * 2.0 ) / ( t1 - t0 ) * 1e-9;
    if ( ghz > best )
    {
      best = ghz;
    }
  }
  printf( "core clock: ~%.2f GHz equivalent (dependent add chain, best of 3)\n", best );
}

//=============================================================================
// the cpu: name for the file, and which SIMD levels it can run

#ifdef DT_X86
  #ifdef _MSC_VER
    #include <intrin.h>
    static void dt_cpuid( unsigned int leaf, unsigned int r[4] )
    {
      __cpuidex( (int*) r, (int) leaf, 0 );
    }
    static unsigned long long dt_xgetbv( void )
    {
      return _xgetbv( 0 );
    }
  #else
    #include <cpuid.h>
    static void dt_cpuid( unsigned int leaf, unsigned int r[4] )
    {
      __cpuid_count( leaf, 0, r[0], r[1], r[2], r[3] );
    }
    static unsigned long long dt_xgetbv( void )
    {
      unsigned int a, d;
      __asm__ volatile( "xgetbv" : "=a"(a), "=d"(d) : "c"(0) );
      return ( (unsigned long long) d << 32 ) | a;
    }
  #endif

static int cpu_has_avx( void )
{
  unsigned int r[4];
  dt_cpuid( 1, r );
  if ( !( r[2] & ( 1u << 27 ) ) || !( r[2] & ( 1u << 28 ) ) )   // OSXSAVE, AVX
  {
    return 0;
  }
  return ( dt_xgetbv() & 6 ) == 6;                                // OS saves the YMM state
}

// what the header's AVX-512 path needs: F, BW and VL, and the OS saving the opmask and ZMM state too
static int cpu_has_avx512( void )
{
  unsigned int r[4];
  if ( !cpu_has_avx() )
  {
    return 0;
  }
  if ( ( dt_xgetbv() & 0xe6 ) != 0xe6 )
  {
    return 0;
  }
  dt_cpuid( 7, r );
  return ( ( r[1] & ( 1u << 16 ) ) != 0 ) && ( ( r[1] & ( 1u << 30 ) ) != 0 ) && ( ( r[1] & ( 1u << 31 ) ) != 0 );
}
#elif defined( _WIN32 )
  // Windows on ARM: no cpuid; the name is in the registry
#else
  #include <sys/utsname.h>
  #ifdef __APPLE__
    #include <sys/sysctl.h>
  #endif
#endif

// the cpu name, squeezed to letters and digits: cpuid brand string on x86, the registry on Windows on ARM, /proc/cpuinfo
//   or sysctl elsewhere, plus the architecture on arm so 32 and 64 bit runs on one board get different names
static void get_cpu_name( char * out, int out_size )
{
  char brand[ 128 ] = "cpu";
  int i, n;

  #ifdef DT_X86
  {
    unsigned int r[4];
    dt_cpuid( 0x80000000, r );
    if ( r[0] >= 0x80000004 )
    {
      for( i = 0 ; i < 3 ; i++ )
      {
        dt_cpuid( 0x80000002 + i, r );
        memcpy( brand + i * 16, r, 16 );
      }
      brand[ 48 ] = 0;
    }
  }
  #elif defined( _WIN32 )
  {
    DWORD len = sizeof( brand ) - 8;
    if ( RegGetValueA( HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString", RRF_RT_REG_SZ, 0, brand, &len ) != ERROR_SUCCESS )
    {
      strcpy( brand, "WindowsArm" );
    }
    strcat( brand, " arm64" );
  }
  #elif defined( __APPLE__ )
  {
    struct utsname un;
    size_t len = 100;
    if ( sysctlbyname( "machdep.cpu.brand_string", brand, &len, 0, 0 ) != 0 )
    {
      strcpy( brand, "AppleSilicon" );
    }
    brand[ 100 ] = 0;
    if ( uname( &un ) == 0 )
    {
      size_t l = strlen( brand );
      snprintf( brand + l, sizeof( brand ) - l, " %.20s", un.machine );
    }
  }
  #else
  {
    struct utsname un;
    FILE * f = fopen( "/proc/cpuinfo", "rt" );
    char line[ 256 ], model[ 100 ] = "", hw[ 100 ] = "", impl[ 16 ] = "", part[ 16 ] = "";
    if ( f )
    {
      while ( fgets( line, sizeof( line ), f ) )
      {
        char * colon = strchr( line, ':' ), * v, * e;
        if ( !colon )
        {
          continue;
        }
        v = colon + 1;
        while ( ( *v == ' ' ) || ( *v == '\t' ) )
        {
          v++;
        }
        e = v + strlen( v );
        while ( ( e > v ) && ( ( e[-1] == '\n' ) || ( e[-1] == '\r' ) || ( e[-1] == ' ' ) ) )
        {
          *--e = 0;
        }
        if ( !model[0] && !strncmp( line, "model name", 10 ) )
        {
          strncpy( model, v, 99 );
        }
        else if ( !hw[0] && ( !strncmp( line, "Hardware", 8 ) || !strncmp( line, "Processor", 9 ) ) )
        {
          strncpy( hw, v, 99 );
        }
        else if ( !impl[0] && !strncmp( line, "CPU implementer", 15 ) )
        {
          strncpy( impl, v, 15 );
        }
        else if ( !part[0] && !strncmp( line, "CPU part", 8 ) )
        {
          strncpy( part, v, 15 );
        }
      }
      fclose( f );
    }
    if ( model[0] )
    {
      strcpy( brand, model );
    }
    else if ( hw[0] )
    {
      strcpy( brand, hw );
    }
    else if ( impl[0] )
    {
      sprintf( brand, "arm %s %s", impl, part );
    }
    if ( uname( &un ) == 0 )
    {
      size_t l = strlen( brand );
      snprintf( brand + l, sizeof( brand ) - l, " %.20s", un.machine );
    }
  }
  #endif

  n = 0;
  for( i = 0 ; brand[i] && ( n < out_size - 1 ) ; i++ )
  {
    if ( ( ( brand[i] >= '0' ) && ( brand[i] <= '9' ) ) || ( ( brand[i] >= 'A' ) && ( brand[i] <= 'Z' ) ) || ( ( brand[i] >= 'a' ) && ( brand[i] <= 'z' ) ) )
    {
      out[ n++ ] = brand[i];
    }
  }
  out[ n ] = 0;
  if ( n == 0 )
  {
    strcpy( out, "cpu" );
  }
}

//=============================================================================
// the representative sets: the decision depends on the tap count per axis, whether the horizontal is an integer factor
//   (period 1 kernels) and the row / column counts, so one scale per tap count stands in for a full grid. Mitchell:
//   4 taps on every upsample (2.5 and 1.37 - few on purpose, every factor is also the other axis's partner), then one
//   downsample factor per tap count from 5 (1/1.25) to 32 (1/8), the round ones (1/2, 1/3, 1/4) being the period 1
//   kernels. Triangle and box cover 2 and 3 taps (and 1:1). Three input sizes: 240 (cache resident), 480, 960. All
//   timed with CLAMP - WRAP only adds the filter's margins to the input, which the cost model inflates the size by.

static const double rep_factors[22] = { 2.5, 1.37, 1/1.25, 1/1.5, 1/1.6, 1/2.0, 1/2.2, 1/2.5, 1/2.7, 1/3.0, 1/3.2, 1/3.45, 1/3.7, 1/4.0, 1/4.2, 1/4.4, 1/5.0, 1/5.3, 1/6.0, 1/6.4, 1/6.9, 1/8.0 };
static const double tri_factors[6] = { 2, 1.37, 1, 1/1.25, 1/1.37, 1/1.5 };          // 2 taps up and at 1:1, 3 at 1/1.25-1/1.5
static const double box_factors[7] = { 2, 1.37, 1, 1/1.37, 1/1.5, 1/2.0, 1/3.0 };    // 2 taps up and at 1:1, 3 at 1/1.37-1/2, 4 at 1/3
static const int rep_sizes[3] = { 240, 480, 960 };

typedef struct rep_desc
{
  double const * factors;
  int count;
  int filter;
  char const * name;
} rep_desc;

#define REPSETS 3
static const rep_desc rep_sets[ REPSETS ] =
{
  { rep_factors, 22, STBIR_FILTER_MITCHELL, "Mitchell" },   // 4..32 taps, one factor per tap count
  { tri_factors,  6, STBIR_FILTER_TRIANGLE, "Triangle" },   // 2..3
  { box_factors,  7, STBIR_FILTER_BOX,      "Box"      },   // 2..4
};

static void make_rep_set( dt_set * set, rep_desc const * d )
{
  int ir, i;

  memset( set, 0, sizeof( *set ) );
  set->filter = d->filter;
  set->edge = STBIR_EDGE_CLAMP;
  set->insizes = 3;
  set->dimx = set->dimy = d->count;
  set->name = d->name;
  for( ir = 0 ; ir < 3 ; ir++ )
  {
    set->sizes[ir] = rep_sizes[ir];
    for( i = 0 ; i < d->count ; i++ )
    {
      set->ox[ir][i] = set->oy[ir][i] = (int)( rep_sizes[ir] * d->factors[i] + 0.5 );
    }
  }
}

//=============================================================================
// progress: the resize being timed as in_width(horizontal taps) x in_height(vertical taps) to out_width x out_height,
//   and a 32 wide bar (by estimated work, so it moves evenly), redrawn in place when either changes

#define BAR_WIDTH 32
static int prog_shown = -1;
static stbir_int64 prog_shown_key = -1;
static int prog_ms;

static void progress( int in_width, int htaps, int in_height, int vtaps, int out_width, int out_height, double done, double total )
{
  int fill = (int)( ( done * BAR_WIDTH ) / total );
  stbir_int64 key = ( ( (stbir_int64) htaps * 1000 + vtaps ) * 8192 + out_width ) * 8192 + out_height;   // the taps and the output size, as one value
  int b;

  if ( ( fill == prog_shown ) && ( key == prog_shown_key ) )
  {
    return;
  }
  prog_shown = fill;
  prog_shown_key = key;

  if ( done < total )
  {
    printf( "\r%4d(%2d) x %4d(%2d) to %4d x %-4d [", in_width, htaps, in_height, vtaps, out_width, out_height );
  }
  else
  {
    printf( "\r%-35s [", "done" );
  }
  for( b = 0 ; b < BAR_WIDTH ; b++ )
  {
    putchar( ( b < fill ) ? '.' : ' ' );
  }
  printf( "]" );

  if ( done >= total )
  {
    printf( " %d s          \n", ( get_milliseconds() - prog_ms ) / 1000 );
  }
  else if ( done > 0 )
  {
    // time left, from the work done so far at the elapsed rate
    double elapsed = ( get_milliseconds() - prog_ms ) / 1000.0;
    printf( " %4d s left", (int)( elapsed * ( total - done ) / done + 0.5 ) );
  }
  fflush( stdout );
}

//=============================================================================
// -update: the previous run's file, walked set by set alongside the sets we time. the sets are laid out in the same
//   order (levels outer, sets inner), so each is matched against the next one in the file: same level, filter, edge
//   and geometry - then its cells seed the new set's minimums. a mismatch stops the seeding (the rest time from scratch).

static int * prior_buf = 0, * prior_next = 0, * prior_end = 0;
static int prior_sets_left = 0;       // sets still to be matched (0 = no prior, or given up)
static int prior_ms = 0;              // the previous file's total run time and profile clocks: this run's are added on, so the
static stbir_int64 prior_clocks = 0;  //   file's totals stay the effort spent on it (both are wall time, so their ratio - the
                                      //   clock calibration vf_train uses - is unaffected, with or without -runcool's pauses)

static void prior_load( char const * filename )
{
  FILE * f = fopen( filename, "rb" );
  long size;

  if ( prior_buf )
  {
    free( prior_buf );
    prior_buf = 0;
  }
  prior_sets_left = 0;
  prior_ms = 0;
  prior_clocks = 0;

  if ( !f )
  {
    printf( "-update: no %s yet, timing from scratch\n", filename );
    return;
  }

  fseek( f, 0, SEEK_END );
  size = ftell( f );
  fseek( f, 0, SEEK_SET );
  prior_buf = (int*) malloc( size + 4 );
  if ( ( fread( prior_buf, 1, size, f ) != (size_t) size ) || ( size < HEADER * (int) sizeof( int ) ) || ( prior_buf[0] != ( ( 'V' << 24 ) | ( 'F' << 16 ) | ( 'T' << 8 ) | '3' ) ) )
  {
    printf( "-update: %s isn't a VFT3 timing file, timing from scratch\n", filename );
    free( prior_buf );
    prior_buf = 0;
  }
  else if ( ( prior_buf[3] != DT_TYPES ) || memcmp( prior_buf + 4, dt_types, sizeof( dt_types ) ) || memcmp( prior_buf + 9, dt_effective, sizeof( dt_effective ) ) )
  {
    printf( "-update: %s was timed with different channel types, timing from scratch\n", filename );
    free( prior_buf );
    prior_buf = 0;
  }
  else
  {
    prior_sets_left = prior_buf[2];
    prior_next = prior_buf + HEADER;
    prior_end = prior_buf + size / sizeof( int );
    prior_ms = prior_buf[15];
    prior_clocks = ( (stbir_int64*)( prior_buf + 16 ) )[0];
    printf( "-update: starting from %s (%d sets, %d min of timing so far)\n", filename, prior_sets_left, prior_ms / 60000 );
  }
  fclose( f );
}

// seeds a set's cells (right after its geometry) from the next prior set if it is the same set; returns 1 if it did
static int prior_seed( int const * header, int header_ints, int * cells, int num_cells )
{
  int * s = prior_next;

  if ( ( prior_sets_left <= 0 ) || ( s + header_ints + 2 * num_cells > prior_end ) )
  {
    return 0;
  }
  if ( memcmp( s, header, header_ints * sizeof( int ) ) != 0 )
  {
    printf( "  (-update: the previous file's sets don't match from here on - timing from scratch)\n" );
    prior_sets_left = 0;   // stop trying
    return 0;
  }

  memcpy( cells, s + header_ints, 2 * num_cells * sizeof( int ) );
  prior_next = s + header_ints + 2 * num_cells;
  prior_sets_left--;
  return 1;
}

//=============================================================================
// the output file

static int * file_buf = 0;
static int file_ints = 0, file_cap = 0;

static int * file_reserve( int ints )
{
  if ( file_ints + ints > file_cap )
  {
    file_cap = ( file_ints + ints ) * 2 + 4096;
    file_buf = (int*) realloc( file_buf, sizeof( int ) * file_cap );
  }
  file_ints += ints;
  return file_buf + file_ints - ints;
}

typedef void time_set_func( dt_set const * set, unsigned char * input, unsigned char * output, int * out_timings, dt_progress_func * progress );

// appends one set timed at one SIMD level to the file buffer
static void time_and_store( dt_set const * set, int simd_level, time_set_func * time_set, unsigned char * input, unsigned char * output )
{
  int cells = set->dimx * set->dimy * set->insizes * DT_TYPES;
  int header_ints = 6 + set->insizes * ( 2 + set->dimx + set->dimy );
  int * header = file_reserve( header_ints + 2 * cells );
  int * p = header;
  int ir, i, seeded = 0;

  *p++ = simd_level;
  *p++ = set->filter;
  *p++ = set->edge;
  *p++ = set->insizes;
  *p++ = set->dimx;
  *p++ = set->dimy;
  for( ir = 0 ; ir < set->insizes ; ir++ )
  {
    *p++ = set->sizes[ir];
    *p++ = set->sizes[ir];
    for( i = 0 ; i < set->dimx ; i++ )
    {
      *p++ = set->ox[ir][i];
    }
    for( i = 0 ; i < set->dimy ; i++ )
    {
      *p++ = set->oy[ir][i];
    }
  }

  memset( p, 0, 2 * cells * sizeof( int ) );
  if ( dt_update )
  {
    seeded = prior_seed( header, header_ints, p, cells );
  }

  printf( "  %s:%s\n", set->name, seeded ? "  (improving the previous run)" : "" );
  prog_shown = -1;
  prog_shown_key = -1;
  prog_ms = get_milliseconds();
  cool_work_start = -1;
  time_set( set, input, output, p, progress );
}

// written to a temp file beside it first, then swapped in, so a failed write (disk full, a kill) can't leave a
//   truncated file where the hours of timings were
static int file_write( const char * filename, void * buffer, size_t size )
{
  char tempname[ 300 ];
  FILE * f;
  int ok;

  if ( strlen( filename ) + 5 > sizeof( tempname ) )
  {
    return 0;
  }
  sprintf( tempname, "%s.tmp", filename );
  f = fopen( tempname, "wb" );
  if ( f == 0 )
  {
    return 0;
  }
  ok = ( fwrite( buffer, 1, size, f ) == size );
  ok = ( fclose( f ) == 0 ) && ok;
  if ( !ok )
  {
    remove( tempname );
    return 0;
  }
  #ifdef _WIN32
  return MoveFileExA( tempname, filename, MOVEFILE_REPLACE_EXISTING ) != 0;   // (C's rename won't replace on Windows)
  #else
  return rename( tempname, filename ) == 0;
  #endif
}

//=============================================================================

typedef struct dt_level
{
  int level;
  char const * name;
  time_set_func * time_set;
  long long ( *clock )( void );
} dt_level;

static void add_level( dt_level * levels, int * numlevels, int level, char const * name, time_set_func * time_set, long long ( *clock )( void ) )
{
  levels[ *numlevels ].level = level;
  levels[ *numlevels ].name = name;
  levels[ *numlevels ].time_set = time_set;
  levels[ *numlevels ].clock = clock;
  ( *numlevels )++;
}

int main( int argc, char ** argv )
{
  static dt_set sets[ 8 ];
  dt_level levels[4];
  unsigned char * input, * output;
  int numsets = 0, numlevels = 0, s, l;
  int totalms, round;
  stbir_int64 totalclocks;
  char outname[ 256 ];

  outname[0] = 0;
  for( s = 1 ; s < argc ; s++ )
  {
    if ( !strcmp( argv[s], "-update" ) )
    {
      dt_update = 1;
    }
    else if ( !strcmp( argv[s], "-runcool" ) )
    {
      dt_runcool = 1;
    }
    else if ( !strcmp( argv[s], "-loop" ) )
    {
      dt_loop = 1;
    }
    else if ( ( argv[s][0] != '-' ) && !outname[0] )
    {
      strncpy( outname, argv[s], sizeof( outname ) - 1 );
      outname[ sizeof( outname ) - 1 ] = 0;
    }
    else
    {
      printf( "command: dotimings [-update] [-runcool] [-loop] [outfilename]\n" );
      printf( "         times the representative sets (mitchell / triangle / box, clamp) at every SIMD level this cpu supports and\n" );
      printf( "         writes <cpu>.timings (or outfilename) in the current directory.\n" );
      printf( "         -update:  start from the file this run would write - every cell's minimum begins at the previous value, so\n" );
      printf( "                   repeated runs only ever improve it\n" );
      printf( "         -runcool: pause between cells about as long as they took, so the cpu stays cool (laptops throttle)\n" );
      printf( "         -loop:    run again and again until stopped (ctrl-c) - with -update, each round improves the file\n" );
      return 1;
    }
  }
  if ( dt_loop && !dt_update )
  {
    printf( "(-loop without -update: each round overwrites the file with just its own results)\n" );
  }

  raise_priority();
  print_calibration();

  for( s = 0 ; s < REPSETS ; s++ )
  {
    make_rep_set( sets + numsets++, rep_sets + s );
  }

  // the SIMD levels this cpu can run
  add_level( levels, &numlevels, 0, "scalar", dt_time_set_scalar, dt_clock_scalar );
  #ifdef DT_X86
  add_level( levels, &numlevels, 1, "SSE2", dt_time_set_sse2, dt_clock_sse2 );
  if ( cpu_has_avx() )
  {
    add_level( levels, &numlevels, 2, "AVX", dt_time_set_avx, dt_clock_avx );
  }
  else
  {
    printf( "(no AVX on this cpu - not timed)\n" );
  }
  if ( cpu_has_avx512() )
  {
    add_level( levels, &numlevels, 3, "AVX512", dt_time_set_avx512, dt_clock_avx512 );
  }
  else
  {
    printf( "(no AVX-512 on this cpu - not timed)\n" );
  }
  #else
  add_level( levels, &numlevels, 1, "NEON", dt_time_set_neon, dt_clock_neon );
  #endif

  // sanity: each copy was built as the level it is used as
  #ifdef DT_X86
  if ( ( dt_simd_level_scalar() != 0 ) || ( dt_simd_level_sse2() != 1 ) || ( cpu_has_avx() && ( dt_simd_level_avx() != 2 ) ) || ( cpu_has_avx512() && ( dt_simd_level_avx512() != 3 ) ) )
  #else
  if ( ( dt_simd_level_scalar() != 0 ) || ( dt_simd_level_neon() != 1 ) )
  #endif
  {
    printf( "build problem: a SIMD level copy of dotimings_impl.c was not built at its level\n" );
    return 1;
  }

  input = (unsigned char*) malloc( 4 * 1200 * 1200 );
  memset( input, 0x80, 4 * 1200 * 1200 );
  output = (unsigned char*) malloc( 4 * 10000 * 10000ULL );

  if ( !outname[0] )
  {
    char cpu[ 128 ];
    get_cpu_name( cpu, sizeof( cpu ) );
    sprintf( outname, "%s.timings", cpu );
  }
  printf( "timing to %s\n", outname );

  for( round = 1 ; ; round++ )
  {
    int * file;

    if ( dt_loop )
    {
      printf( "\n=== round %d\n", round );
    }
    if ( dt_update )
    {
      prior_load( outname );
    }

    file_ints = 0;            // a fresh file per round (the buffer is reused)
    file_reserve( HEADER );   // filled in at the end
    totalms = get_milliseconds();
    totalclocks = levels[0].clock();

    for( l = 0 ; l < numlevels ; l++ )
    {
      printf( "timing %s\n", levels[l].name );
      for( s = 0 ; s < numsets ; s++ )
      {
        time_and_store( sets + s, levels[l].level, levels[l].time_set, input, output );
      }
    }

    totalms = get_milliseconds() - totalms;
    totalclocks = levels[0].clock() - totalclocks;

    file = file_buf;
    file[0] = ( 'V' << 24 ) | ( 'F' << 16 ) | ( 'T' << 8 ) | '3';   // == 'VFT3' as vf_train reads it
    #ifdef DT_X86
    file[1] = 1;
    #else
    file[1] = 2;
    #endif
    file[2] = numsets * numlevels;
    file[3] = DT_TYPES;
    for( s = 0 ; s < DT_TYPES ; s++ )
    {
      file[ 4 + s ] = dt_types[s];
      file[ 9 + s ] = dt_effective[s];
    }
    file[14] = 0;                                                   // reserved (keeps the int64 below 8 byte aligned)
    file[15] = totalms + prior_ms;                                  // the effort spent on the file, across -update rounds
    ( (stbir_int64*)( file + 16 ) )[0] = totalclocks + prior_clocks;   // 16,17 (same wall time in profile clocks: the calibration)
    // 18..31 reserved

    if ( !file_write( outname, file_buf, sizeof( int ) * file_ints ) )
    {
      printf( "Error writing file: %s\n", outname );
      return 1;
    }
    printf( "Successfully wrote timing file: %s (%d s)\n", outname, totalms / 1000 );

    if ( !dt_loop )
    {
      break;
    }
  }

  return 0;
}
