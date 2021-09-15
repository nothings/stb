#ifdef DS_PERF
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS


//#define STBDS_INTERNAL_SMALL_BUCKET    // make 64-bit bucket fit both keys and hash bits
//#define STBDS_SIPHASH_2_4     // performance test 1_3 against 2_4
//#define STBDS_INTERNAL_BUCKET_START    // don't bother offseting differently within bucket for different hash values
//#define STBDS_FLUSH_CACHE  (1u<<20) // do this much memory traffic to flush the cache between some benchmarking measurements

#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define STB_DEFINE
#define STB_NO_REGISTRY
#include "../stb.h"
#endif

#ifdef DS_TEST
#define STBDS_UNIT_TESTS
#define STBDS_SMALL_BUCKET
#endif

#ifdef DS_STATS
#define STBDS_STATISTICS
#endif

#ifndef DS_PERF
#define STBDS_ASSERT assert
#include <assert.h>
#endif

#define STB_DS_IMPLEMENTATION
#include "../stb_ds.h"

size_t churn_inserts, churn_deletes;

void churn(int a, int b, int count)
{
  struct { int key,value; } *map=NULL;
  int i,j,n,k;
  for (i=0; i < a; ++i)
    hmput(map,i,i+1);
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      hmput(map,i,i+1);
    }
    assert(hmlen(map) == b);
    for (j=a; j < b; ++j) {
      k=i-j-1;
      k = hmdel(map,k);
      assert(k != 0);
    }
    assert(hmlen(map) == a);
  }
  hmfree(map);
  churn_inserts = i;
  churn_deletes = (b-a) * n;
}

#ifdef DS_TEST
#include <stdio.h>
int main(int argc, char **argv)
{
  char *temp=NULL;
  stbds_unit_tests();
  arrins(temp, 0, 'a');
  arrins(temp, arrlen(temp), 'b');
  churn(0,100,1);
  churn(3,7,50000);
  churn(3,15,50000);
  churn(16, 48, 25000);
  churn(10, 15, 25000);
  churn(200,500, 5000);
  churn(2000,5000, 500);
  churn(20000,50000, 50);
  printf("Ok!");
  return 0;
}
#endif

#ifdef DS_STATS
#define MAX(a,b) ((a) > (b) ? (a) : (b))
size_t max_hit_probes, max_miss_probes, total_put_probes, total_miss_probes, churn_misses;
void churn_stats(int a, int b, int count)
{
  struct { int key,value; } *map=NULL;
  int i,j,n,k;
  churn_misses = 0;
  for (i=0; i < a; ++i) {
    hmput(map,i,i+1);
    max_hit_probes = MAX(max_hit_probes, stbds_hash_probes);
    total_put_probes += stbds_hash_probes;
    stbds_hash_probes = 0;
  }
    
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      hmput(map,i,i+1);
      max_hit_probes = MAX(max_hit_probes, stbds_hash_probes);
      total_put_probes += stbds_hash_probes;
      stbds_hash_probes = 0;
    }
    for (j=0; j < (b-a)*10; ++j) {
      k=i+j;
      (void) hmgeti(map,k); // miss
      max_miss_probes = MAX(max_miss_probes, stbds_hash_probes);
      total_miss_probes += stbds_hash_probes;
      stbds_hash_probes = 0;
      ++churn_misses;
    }
    assert(hmlen(map) == b);
    for (j=a; j < b; ++j) {
      k=i-j-1;
      k = hmdel(map,k);
      stbds_hash_probes = 0;
      assert(k);
    }
    assert(hmlen(map) == a);
  }
  hmfree(map);
  churn_inserts = i;
  churn_deletes = (b-a) * n;
}

void reset_stats(void)
{
  stbds_array_grow=0, 
  stbds_hash_grow=0;
  stbds_hash_shrink=0;
  stbds_hash_rebuild=0;
  stbds_hash_probes=0;
  stbds_hash_alloc=0;
  stbds_rehash_probes=0;
  stbds_rehash_items=0;
  max_hit_probes = 0;
  max_miss_probes = 0;
  total_put_probes = 0;
  total_miss_probes = 0;
}

void print_churn_probe_stats(char *str)
{
  printf("Probes: %3d max hit, %3d max miss, %4.2f avg hit, %4.2f avg miss: %s\n",
    (int) max_hit_probes, (int) max_miss_probes, (float) total_put_probes / churn_inserts, (float) total_miss_probes / churn_misses, str);
  reset_stats();
}

int main(int arg, char **argv)
{
  churn_stats(0,500000,1); print_churn_probe_stats("Inserting 500000 items");
  churn_stats(0,500000,1); print_churn_probe_stats("Inserting 500000 items");
  churn_stats(0,500000,1); print_churn_probe_stats("Inserting 500000 items");
  churn_stats(0,500000,1); print_churn_probe_stats("Inserting 500000 items");
  churn_stats(49000,50000,500); print_churn_probe_stats("Deleting/Inserting 500000 items");
  churn_stats(49000,50000,500); print_churn_probe_stats("Deleting/Inserting 500000 items");
  churn_stats(49000,50000,500); print_churn_probe_stats("Deleting/Inserting 500000 items");
  churn_stats(49000,50000,500); print_churn_probe_stats("Deleting/Inserting 500000 items");
  return 0;
}
#endif


#ifdef DS_PERF
//char *strdup(const char *foo) { return 0; }
//int stricmp(const char *a, const char *b) { return 0; }
//int strnicmp(const char *a, const char *b, size_t n) { return 0; }

unsigned __int64 t0, xsum, mn,mx,count;
void begin(void)
{
  LARGE_INTEGER m;
  QueryPerformanceCounter(&m);
  t0 = m.QuadPart;
  xsum = 0;
  count = 0;
  mx = 0;
  mn = ~(unsigned __int64) 0;
}

void measure(void)
{
  unsigned __int64 t1, t;
  LARGE_INTEGER m;
  QueryPerformanceCounter(&m);
  t1 = m.QuadPart;
  t = t1-t0;
  if (t1 < t0)
    printf("ALERT: QueryPerformanceCounter was unordered!\n");
  if (t < mn) mn = t;
  if (t > mx) mx = t;
  xsum += t;
  ++count;
  t0 = t1;
}

void dont_measure(void)
{
  LARGE_INTEGER m;
  QueryPerformanceCounter(&m);
  t0 = m.QuadPart;
}

double timer;
double end(void)
{
  LARGE_INTEGER m;
  QueryPerformanceFrequency(&m);

  if (count > 3) {
    // discard the highest and lowest
    xsum -= mn;
    xsum -= mx;
    count -= 2;
  }
  timer = (double) (xsum) / count / m.QuadPart * 1000;
  return timer;
}

void build(int a, int b, int count, int step)
{
  struct { int key,value; } *map=NULL;
  int i,n;
  for (i=0; i < a; ++i) {
    n = i*step;
    hmput(map,n,i+1);
  }
  measure();
  churn_inserts = i;
  hmfree(map);
  dont_measure();
}

#ifdef STB__INCLUDE_STB_H
void build_stb(int a, int b, int count, int step)
{
  stb_idict *d = stb_idict_new_size(8);
  int i;
  for (i=0; i < a; ++i)
    stb_idict_add(d, i*step, i+1);
  measure();
  churn_inserts = i;
  stb_idict_destroy(d);
  dont_measure();
}

void multibuild_stb(int a, int b, int count, int step, int tables)
{
  stb_idict *d[50000];
  int i,q;
  for (q=0; q < tables; ++q)
    d[q] = stb_idict_new_size(8);
  dont_measure();
  for (i=0; i < a; ++i)
    for (q=0; q < tables; ++q)
      stb_idict_add(d[q], i*step+q*771, i+1);
  measure();
  churn_inserts = i;
  for (q=0; q < tables; ++q)
    stb_idict_destroy(d[q]);
  dont_measure();
}

int multisearch_stb(int a, int start, int end, int step, int tables)
{
  stb_idict *d[50000];
  int i,q,total=0,v;
  for (q=0; q < tables; ++q)
    d[q] = stb_idict_new_size(8);
  for (q=0; q < tables; ++q)
    for (i=0; i < a; ++i)
      stb_idict_add(d[q], i*step+q*771, i+1);
  dont_measure();
  for (i=start; i < end; ++i)
    for (q=0; q < tables; ++q)
      if (stb_idict_get_flag(d[q], i*step+q*771, &v))
        total += v;
  measure();
  churn_inserts = i;
  for (q=0; q < tables; ++q)
    stb_idict_destroy(d[q]);
  dont_measure();
  return total;
}
#endif

int multisearch(int a, int start, int end, int step, int tables)
{
  struct { int key,value; } *hash[50000];
  int i,q,total=0;
  for (q=0; q < tables; ++q)
    hash[q] = NULL;
  for (q=0; q < tables; ++q)
    for (i=0; i < a; ++i)
      hmput(hash[q], i*step+q*771, i+1);
  dont_measure();
  for (i=start; i < end; ++i)
    for (q=0; q < tables; ++q)
      total += hmget(hash[q], i*step+q*771);
  measure();
  churn_inserts = i;
  for (q=0; q < tables; ++q)
    hmfree(hash[q]);
  dont_measure();
  return total;
}

void churn_skip(unsigned int a, unsigned int b, int count)
{
  struct { unsigned int key,value; } *map=NULL;
  unsigned int i,j,n,k;
  for (i=0; i < a; ++i)
    hmput(map,i,i+1);
  dont_measure();
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      hmput(map,i,i+1);
    }
    assert(hmlen(map) == b);
    for (j=a; j < b; ++j) {
      k=i-j-1;
      k = hmdel(map,k);
      assert(k != 0);
    }
    assert(hmlen(map) == a);
  }
  measure();
  churn_inserts = i;
  churn_deletes = (b-a) * n;
  hmfree(map);
  dont_measure();
}

typedef struct { int n[8]; } str32;
void churn32(int a, int b, int count, int include_startup)
{
  struct { str32 key; int value; } *map=NULL;
  int i,j,n;
  str32 key = { 0 };
  for (i=0; i < a; ++i) {
    key.n[0] = i;
    hmput(map,key,i+1);
  }
  if (!include_startup)
    dont_measure();
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      key.n[0] = i;
      hmput(map,key,i+1);
    }
    assert(hmlen(map) == b);
    for (j=a; j < b; ++j) {
      key.n[0] = i-j-1;
      hmdel(map,key);
    }
    assert(hmlen(map) == a);
  }
  measure();
  hmfree(map);
  churn_inserts = i;
  churn_deletes = (b-a) * n;
  dont_measure();
}

typedef struct { int n[32]; } str256;
void churn256(int a, int b, int count, int include_startup)
{
  struct { str256 key; int value; } *map=NULL;
  int i,j,n;
  str256 key = { 0 };
  for (i=0; i < a; ++i) {
    key.n[0] = i;
    hmput(map,key,i+1);
  }
  if (!include_startup)
    dont_measure();
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      key.n[0] = i;
      hmput(map,key,i+1);
    }
    assert(hmlen(map) == b);
    for (j=a; j < b; ++j) {
      key.n[0] = i-j-1;
      hmdel(map,key);
    }
    assert(hmlen(map) == a);
  }
  measure();
  hmfree(map);
  churn_inserts = i;
  churn_deletes = (b-a) * n;
  dont_measure();
}

void churn8(int a, int b, int count, int include_startup)
{
  struct { size_t key,value; } *map=NULL;
  int i,j,n,k;
  for (i=0; i < a; ++i)
    hmput(map,i,i+1);
  if (!include_startup)
    dont_measure();
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      hmput(map,i,i+1);
    }
    assert(hmlen(map) == b);
    for (j=a; j < b; ++j) {
      k=i-j-1;
      k = hmdel(map,k);
      assert(k != 0);
    }
    assert(hmlen(map) == a);
  }
  measure();
  hmfree(map);
  churn_inserts = i;
  churn_deletes = (b-a) * n;
  dont_measure();
}

void multichurn4(int a, int b, int count, int include_startup, int tables)
{
  struct { int key,value; } *map[50000];
  int i,j,n,k,q;
  for (q=0; q < tables; ++q)
    map[q] = NULL;
  dont_measure();

  for (i=0; i < a; ++i)
    for (q=0; q < tables; ++q)
      hmput(map[q],i,i+1);
  if (!include_startup)
    dont_measure();
  for (n=0; n < count; ++n) {
    for (j=a; j < b; ++j,++i) {
      for (q=0; q < tables; ++q)
        hmput(map[q],i,i+1);
    }
    assert(hmlen(map[0]) == b);
    for (j=a; j < b; ++j) {
      k=i-j-1;
      for (q=0; q < tables; ++q)
        k = hmdel(map[q],k);
      assert(k != 0);
    }
    assert(hmlen(map[0]) == a);
  }
  measure();
  for (q=0; q < tables; ++q)
    hmfree(map[q]);
  churn_inserts = i * tables;
  churn_deletes = (b-a) * n * tables;
  dont_measure();
}

struct {
  unsigned __int64 start;
  unsigned __int64 end;
  int    table_size;
} mstats[32][4000];

const int first_step = 64;
const int last_step = 384-48; // 32M

void measure_build4(int step_log2)
{
  double length;
  int i,j,k=0;
  int step = 1 << step_log2;
  unsigned __int64 t0,t1;
  struct { int key,value; } *map=NULL;
  double rdtsc_scale;
  begin();
  t0 = __rdtsc();

  mstats[0][0].start = __rdtsc();
  for (i=0; i < 256; ++i) {
    hmput(map,k,k+1);
    k += step;
  }
  mstats[0][first_step-1].end = __rdtsc();
  mstats[0][first_step-1].table_size = k >> step_log2;
  for (j=first_step; j < last_step; ++j) {
    for (i=0; i < (1<<(j>>4)); ++i) {
      hmput(map, k,k+1);
      k += step;
    }
    mstats[0][j].end = __rdtsc();
    mstats[0][j].table_size = k >> step_log2;
  }
  t1 = __rdtsc();
  measure();
  hmfree(map);
  length = end();
  rdtsc_scale = length / (t1-t0) * 1000;

  for (j=1; j < last_step; ++j)
    mstats[0][j].start = mstats[0][0].start;
  for (j=first_step-1; j < last_step; ++j) {
    printf("%12.4f,%12d,%12d,0,0,0\n", (mstats[0][j].end - mstats[0][j].start) * rdtsc_scale, mstats[0][j].table_size, mstats[0][j].table_size);
  }
}

#ifdef STBDS_FLUSH_CACHE
static int cache_index;
char dummy[8][STBDS_FLUSH_CACHE];

int flush_cache(void)
{
  memmove(dummy[cache_index],dummy[cache_index]+1, sizeof(dummy[cache_index])-1);
  cache_index = (cache_index+1)%8;
  return dummy[cache_index][0];
}
#else
int flush_cache(void) { return 0; }
#endif

int measure_average_lookup4(int step_log2)
{
  int total;
  double length;
  int i,j,k=0,q;
  int step = 1 << step_log2;
  unsigned __int64 t0,t1;
  struct { int key,value; } *map=NULL;
  double rdtsc_scale;
  begin();
  t0 = __rdtsc();

  for (i=0; i < 128; ++i) {
    hmput(map,k,k+1);
    k += step;
  }
  for (j=first_step; j <= last_step; ++j) {
    total += flush_cache();
    mstats[0][j].start = __rdtsc();
    for (q=i=0; i < 50000; ++i) {
       total += hmget(map, q); // hit
       if (++q == k) q = 0;
    }
    mstats[0][j].end = __rdtsc();
    mstats[0][j].table_size = k;
    total += flush_cache();
    mstats[1][j].start = __rdtsc();
    for (i=0; i < 50000; ++i) {
       total += hmget(map, i+k); // miss
    }
    mstats[1][j].end = __rdtsc();
    mstats[1][j].table_size = k;

    // expand table
    for (i=0; i < (1<<(j>>4)); ++i) {
      hmput(map, k,k+1);
      k += step;
    }
  }

  t1 = __rdtsc();
  measure();
  hmfree(map);
  length = end();
  rdtsc_scale = length / (t1-t0) * 1000;

  for (j=first_step; j <= last_step; ++j) {
    // time,table_size,numins,numhit,nummiss,numperflush
    printf("%12.4f,%12d,0,50000,0,0\n", (mstats[0][j].end - mstats[0][j].start) * rdtsc_scale, mstats[0][j].table_size);
  }
  for (j=first_step; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,0,50000,0\n", (mstats[1][j].end - mstats[1][j].start) * rdtsc_scale, mstats[1][j].table_size);
  }
  return total;
}

int measure_worst_lookup4_a(int step_log2)
{
  int total;
  double length;
  int i,j,k=0,q,worst_q,n,z,attempts;
  int step = 1 << step_log2;
  unsigned __int64 t0,t1;
  unsigned __int64 m0,m1,worst;
  struct { int key,value; } *map=NULL;
  double rdtsc_scale;
  begin();
  t0 = __rdtsc();

  memset(mstats, 0, sizeof(mstats));
  for (j=first_step; j <= last_step; ++j)
    mstats[0][j].end = mstats[1][j].end = ~(unsigned __int64) 0;

  for(attempts=0; attempts < 2; ++attempts) {
    k = 0;
    stbds_rand_seed(0); // force us to get the same table every time
    for (i=0; i < 128; ++i) {
      hmput(map,k,k+1);
      k += step;
    }
    for (j=first_step; j <= last_step; ++j) {
      unsigned __int64 times[32];

      // find the worst hit time
      for (z=0; z < 2; ++z) { // try the bisectioning measurement 4 times
        worst = 0;
        for (n=0; n < 10; ++n) { // test 400 keys total
          // find the worst time to hit 20 keys
          q=0;
          worst_q = 0;
          total += flush_cache();
          m0 = __rdtsc();
          for (i=0; i < 20; ++i) {
            total += hmget(map, q); // hit
            if (++q == k) q = 0;
          }
          m1 = __rdtsc();
          // for each n, check if this is the worst lookup we've seen
          if (m1 - m0 > worst) {
            worst = m1-m0;
            worst_q = q - i;
            if (worst_q < 0) q += k;
          }
        }
        // after 400 keys, take the worst 20 keys, and try each one
        worst = 0;
        q = worst_q;
        for (i=0; i < 20; ++i) {
          total += flush_cache();
          m0 = __rdtsc();
          total += hmget(map, q); // hit
          m1 = __rdtsc();
          if (m1 - m0 > worst)
            worst = m1-m0;
          if (++q == k) q = 0;
        }
        times[z] = worst;
      }
      // find the worst time in the bunch
      worst = 0;
      for (i=0; i < z; ++i)
        if (times[i] > worst)
          worst = times[i];
      // take the best of 'attempts', to discard outliers
      if (worst < mstats[0][j].end)
        mstats[0][j].end = worst;
      mstats[0][j].start = 0;
      mstats[0][j].table_size = k >> step_log2;

      // find the worst miss time
      for (z=0; z < 8; ++z) { // try the bisectioning measurement 8 times
        worst = 0;
        for (n=0; n < 20; ++n) { // test 400 keys total
          // find the worst time to hit 20 keys
          q=k;
          worst_q = 0;
          total += flush_cache();
          m0 = __rdtsc();
          for (i=0; i < 20; ++i) {
            total += hmget(map, q); // hit
          }
          m1 = __rdtsc();
          // for each n, check if this is the worst lookup we've seen
          if (m1 - m0 > worst) {
            worst = m1-m0;
            worst_q = q - i;
          }
        }
        // after 400 keys, take the worst 20 keys, and try each one
        worst = 0;
        q = worst_q;
        for (i=0; i < 20; ++i) {
          total += flush_cache();
          m0 = __rdtsc();
          total += hmget(map, q); // hit
          m1 = __rdtsc();
          if (m1 - m0 > worst)
            worst = m1-m0;
        }
        times[z] = worst;
      }
      // find the worst time in the bunch
      worst = 0;
      for (i=0; i < z; ++i)
        if (times[i] > worst)
          worst = times[i];
      if (worst < mstats[1][j].end)
        mstats[1][j].end = worst;
      mstats[1][j].start = 0;
      mstats[1][j].table_size = k >> step_log2;

      // expand table
      for (i=0; i < (1<<(j>>4)); ++i) {
        hmput(map, k,k+1);
        k += step;
      }
    }
    hmfree(map);
  }

  t1 = __rdtsc();
  measure();
  length = end();
  rdtsc_scale = length / (t1-t0) * 1000;

  for (j=first_step; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,1,0,1\n", (mstats[0][j].end - mstats[0][j].start) * rdtsc_scale, mstats[0][j].table_size);
  }
  for (j=first_step; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,0,1,1\n", (mstats[1][j].end - mstats[1][j].start) * rdtsc_scale, mstats[1][j].table_size);
  }
  return total;
}

int measure_worst_lookup4_b(int step_log2)
{
  int total;
  double length;
  int i,j,k=0,q,worst_q,n,z,attempts;
  int step = 1 << step_log2;
  unsigned __int64 t0,t1;
  unsigned __int64 m0,m1,worst;
  struct { int key,value; } *map=NULL;
  double rdtsc_scale;
  begin();
  t0 = __rdtsc();

  memset(mstats, 0, sizeof(mstats));
  for (j=first_step; j <= last_step; ++j)
    mstats[0][j].end = mstats[1][j].end = ~(unsigned __int64) 0;

  k = 0;
  stbds_rand_seed(0); // force us to get the same table every time
  for (i=0; i < 128; ++i) {
    hmput(map,k,k+1);
    k += step;
  }
  for (j=first_step; j <= last_step; ++j) {
    unsigned __int64 times[32];

    // find the worst hit time
    for (z=0; z < 8; ++z) { // try this 8 times
      worst = 0;
      q=0;
      for (i=0; i < 5000; ++i) {
        total += hmget(map, q);
        m0 = __rdtsc();
        total += hmget(map, q);
        m1 = __rdtsc();
        if (m1 - m0 > worst) {
          worst = m1-m0;
          worst_q = q - i;
        }
        if (++q == k) q = 0;
      }
      // now retry with the worst one, but find the shortest time for it
      worst = ~(unsigned __int64) 0;
      for (i=0; i < 4; ++i) {
        total += flush_cache();
        m0 = __rdtsc();
        total += hmget(map,worst_q);
        m1 = __rdtsc();
        if (m1-m0 < worst)
          worst = m1-m0;
      }
      times[z] = worst;
    }

    // find the worst of those
    worst = 0;
    for (i=0; i < z; ++i)
      if (times[i] > worst)
        worst = times[i];
    mstats[0][j].start = 0;
    mstats[0][j].end = worst;
    mstats[0][j].table_size = k;

    // find the worst miss time
    for (z=0; z < 8; ++z) { // try this 8 times
      worst = 0;
      q=k;
      for (i=0; i < 5000; ++i) {
        total += hmget(map, q);
        m0 = __rdtsc();
        total += hmget(map, q);
        m1 = __rdtsc();
        if (m1 - m0 > worst) {
          worst = m1-m0;
          worst_q = q - i;
        }
        //printf("%6llu ", m1-m0);
      }
      // now retry with the worst one, but find the shortest time for it
      worst = ~(unsigned __int64) 0;
      for (i=0; i < 4; ++i) {
        total += flush_cache();
        m0 = __rdtsc();
        total += hmget(map,worst_q);
        m1 = __rdtsc();
        if (m1-m0 < worst)
          worst = m1-m0;
      }
      times[z] = worst;
    }

    // find the worst of those
    worst = 0;
    for (i=0; i < z; ++i)
      if (times[i] > worst)
        worst = times[i];
    mstats[1][j].start = 0;
    mstats[1][j].end = worst;
    mstats[1][j].table_size = k;

    // expand table
    for (i=0; i < (1<<(j>>4)); ++i) {
      hmput(map, k,k+1);
      k += step;
    }
  }
  hmfree(map);

  t1 = __rdtsc();
  measure();
  length = end();
  rdtsc_scale = length / (t1-t0) * 1000;

  for (j=first_step+1; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,1,0,1\n", (mstats[0][j].end - mstats[0][j].start) * rdtsc_scale, mstats[0][j].table_size);
  }
  for (j=first_step+1; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,0,1,1\n", (mstats[1][j].end - mstats[1][j].start) * rdtsc_scale, mstats[1][j].table_size);
  }
  return total;
}

int measure_uncached_lookup4(int step_log2)
{
  int total;
  double length;
  int i,j,k=0,q;
  int step = 1 << step_log2;
  unsigned __int64 t0,t1;
  struct { int key,value; } *map=NULL;
  double rdtsc_scale;
  begin();
  t0 = __rdtsc();

  map = NULL;
  for (i=0; i < 128; ++i) {
    hmput(map,k,k+1);
    k += step;
  }
  for (j=first_step; j <= last_step; ++j) {
    mstats[0][j].start = __rdtsc();
    mstats[0][j].end = 0;
    for (q=i=0; i < 512; ++i) {
      if ((i & 3) == 0) {
        mstats[0][j].end += __rdtsc();
        total += flush_cache();
        mstats[0][j].start += __rdtsc();
      }
      total += hmget(map, q); // hit
      if (++q == k) q = 0;
    }
    mstats[0][j].end += __rdtsc();
    mstats[0][j].table_size = k;
    total += flush_cache();
    mstats[1][j].end = 0;
    mstats[1][j].start = __rdtsc();
    for (i=0; i < 512; ++i) {
      if ((i & 3) == 0) {
        mstats[1][j].end += __rdtsc();
        total += flush_cache();
        mstats[1][j].start += __rdtsc();
      }
      total += hmget(map, i+k); // miss
    }
    mstats[1][j].end += __rdtsc();
    mstats[1][j].table_size = k;

    // expand table
    for (i=0; i < (1<<(j>>4)); ++i) {
      hmput(map, k,k+1);
      k += step;
    }
  }
  hmfree(map);

  t1 = __rdtsc();
  measure();
  length = end();
  rdtsc_scale = length / (t1-t0) * 1000;

  for (j=first_step; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,512,0,4\n", (mstats[0][j].end - mstats[0][j].start) * rdtsc_scale, mstats[0][j].table_size);
  }
  for (j=first_step; j <= last_step; ++j) {
    printf("%12.4f,%12d,0,0,512,4\n", (mstats[1][j].end - mstats[1][j].start) * rdtsc_scale, mstats[1][j].table_size);
  }
  return total;
}




int main(int arg, char **argv)
{
  int n,s,w;
  double worst = 0;

  printf("# size_t=%d,", (int) sizeof(size_t));

// number of cache-lines
#ifdef STBDS_SMALL_BUCKET
  printf("cacheline=%d,", 1);
#else
  printf("cacheline=%d,", sizeof(size_t)==8 ? 2 : 1);
#endif
#ifdef STBDS_FLUSH_CACHE
  printf("%d,", (int) stbds_log2(STBDS_FLUSH_CACHE));
#else
  printf("0,");
#endif
#ifdef STBDS_BUCKET_START    // don't bother offseting differently within bucket for different hash values
  printf("STBDS_BUCKET_START,");
#else
  printf(",");
#endif
#ifdef STBDS_SIPHASH_2_4
  printf("STBDS_SIPHASH_2_4,");
#else
  printf(",");
#endif
  printf("\n");

  measure_worst_lookup4_b(0);
  //measure_worst_lookup4_a(0);
  measure_average_lookup4(0);
  measure_uncached_lookup4(0);
  measure_build4(0);
  return 0;

#if 0
  begin(); for (n=0; n < 2000; ++n) { build_stb(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table\n", timer);
  begin(); for (n=0; n <  500; ++n) { build_stb(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table\n", timer);
  begin(); for (n=0; n <  100; ++n) { build_stb(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table\n", timer);
  begin(); for (n=0; n <   10; ++n) { build_stb(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table\n", timer);
  begin(); for (n=0; n <    5; ++n) { build_stb(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table\n", timer);
#endif

#if 0
  begin(); for (n=0; n < 2000; ++n) { churn32(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table w/ 32-byte key\n", timer);
  begin(); for (n=0; n <  500; ++n) { churn32(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table w/ 32-byte key\n", timer);
  begin(); for (n=0; n <  100; ++n) { churn32(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table w/ 32-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { churn32(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table w/ 32-byte key\n", timer);
  begin(); for (n=0; n <    5; ++n) { churn32(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table w/ 32-byte key\n", timer);

  begin(); for (n=0; n < 2000; ++n) { churn256(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table w/ 256-byte key\n", timer);
  begin(); for (n=0; n <  500; ++n) { churn256(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table w/ 256-byte key\n", timer);
  begin(); for (n=0; n <  100; ++n) { churn256(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table w/ 256-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { churn256(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table w/ 256-byte key\n", timer);
  begin(); for (n=0; n <    5; ++n) { churn256(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table w/ 256-byte key\n", timer);
#endif

  begin(); for (n=0; n <   20; ++n) { multisearch_stb(2000,0,2000,1,1000);    } end(); printf("  // %7.2fms : 2,000,000 hits on 1,000   2K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { multisearch_stb(20000,0,2000,1,1000);   } end(); printf("  // %7.2fms : 2,000,000 hits on 1,000  20K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    6; ++n) { multisearch_stb(200000,0,2000,1,1000);  } end(); printf("  // %7.2fms : 2,000,000 hits on 1,000 200K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multisearch_stb(2000000,0,20000,1,100); } end(); printf("  // %7.2fms : 2,000,000 hits on   100   2M table w/ 4-byte key\n", timer);

  begin(); for (n=0; n <   20; ++n) { multisearch    (2000,0,2000,1,1000);    } end(); printf("  // %7.2fms : 2,000,000 hits on 1,000   2K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { multisearch    (20000,0,2000,1,1000);   } end(); printf("  // %7.2fms : 2,000,000 hits on 1,000  20K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    6; ++n) { multisearch    (200000,0,2000,1,1000);  } end(); printf("  // %7.2fms : 2,000,000 hits on 1,000 200K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multisearch    (2000000,0,20000,1,100); } end(); printf("  // %7.2fms : 2,000,000 hits on   100   2M table w/ 4-byte key\n", timer);


#if 1
  begin(); for (n=0; n <    2; ++n) { multibuild_stb(2000,0,0,1,10000); } end(); printf("  // %7.2fms : 20,000,000 inserts creating 10,000   2K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multibuild_stb(20000,0,0,1,1000); } end(); printf("  // %7.2fms : 20,000,000 inserts creating  1,000  20K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multibuild_stb(200000,0,0,1,100); } end(); printf("  // %7.2fms : 20,000,000 inserts creating    100 200K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multibuild_stb(2000000,0,0,1,10); } end(); printf("  // %7.2fms : 20,000,000 inserts creating     10   2M table w/ 4-byte key\n", timer);

  begin(); for (n=0; n <    2; ++n) { multichurn4(2000,0,0,1,10000); } end(); printf("  // %7.2fms : 20,000,000 inserts creating 10,000   2K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multichurn4(20000,0,0,1,1000); } end(); printf("  // %7.2fms : 20,000,000 inserts creating  1,000  20K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multichurn4(200000,0,0,1,100); } end(); printf("  // %7.2fms : 20,000,000 inserts creating    100 200K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    2; ++n) { multichurn4(2000000,0,0,1,10); } end(); printf("  // %7.2fms : 20,000,000 inserts creating     10   2M table w/ 4-byte key\n", timer);
#endif

  begin(); for (n=0; n < 2000; ++n) { build(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <  500; ++n) { build(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <  100; ++n) { build(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { build(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    5; ++n) { build(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table w/ 4-byte key\n", timer);

  begin(); for (n=0; n < 2000; ++n) { churn8(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <  500; ++n) { churn8(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <  100; ++n) { churn8(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { churn8(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <    5; ++n) { churn8(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table w/ 8-byte key\n", timer);

  begin(); for (n=0; n <   60; ++n) { churn_skip(2000,2100,5000);            } end(); printf("  // %7.2fms : 500,000 inserts & deletes in 2K table\n", timer);
  begin(); for (n=0; n <   30; ++n) { churn_skip(20000,21000,500);           } end(); printf("  // %7.2fms : 500,000 inserts & deletes in 20K table\n", timer);
  begin(); for (n=0; n <   15; ++n) { churn_skip(200000,201000,500);         } end(); printf("  // %7.2fms : 500,000 inserts & deletes in 200K table\n", timer);
  begin(); for (n=0; n <    8; ++n) { churn_skip(2000000,2001000,500);       } end(); printf("  // %7.2fms : 500,000 inserts & deletes in 2M table\n", timer);
  begin(); for (n=0; n <    5; ++n) { churn_skip(20000000,20001000,500);     } end(); printf("  // %7.2fms : 500,000 inserts & deletes in 20M table\n", timer);
  begin(); for (n=0; n <    1; ++n) { churn_skip(200000000u,200001000u,500); } end(); printf("  // %7.2fms : 500,000 inserts & deletes in 200M table\n", timer);
  // even though the above measures a roughly fixed amount of work, we still have to build the table n times, hence the fewer measurements each time

  begin(); for (n=0; n <   60; ++n) { churn_skip(1000,3000,250);             } end(); printf("  // %7.2fms :    500,000 inserts & deletes in 2K table\n", timer);
  begin(); for (n=0; n <   15; ++n) { churn_skip(10000,30000,25);            } end(); printf("  // %7.2fms :    500,000 inserts & deletes in 20K table\n", timer);
  begin(); for (n=0; n <    7; ++n) { churn_skip(100000,300000,10);          } end(); printf("  // %7.2fms :  2,000,000 inserts & deletes in 200K table\n", timer);
  begin(); for (n=0; n <    2; ++n) { churn_skip(1000000,3000000,10);        } end(); printf("  // %7.2fms : 20,000,000 inserts & deletes in 2M table\n", timer);

  // search for bad intervals.. in practice this just seems to measure execution variance
  for (s = 2; s < 64; ++s) {
    begin(); for (n=0; n < 50; ++n) { build(200000,0,0,s); } end();
    if (timer > worst) {
      worst = timer;
      w = s;
    }
  }
  for (; s <= 1024; s *= 2) {
    begin(); for (n=0; n < 50; ++n) { build(200000,0,0,s); } end();
    if (timer > worst) {
      worst = timer;
      w = s;
    }
  }
  printf("  // %7.2fms(%d)   : Worst time from inserting 200,000 items with spacing %d.\n", worst, w, w);

  return 0;
}
#endif
