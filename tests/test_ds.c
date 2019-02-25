#include <stdio.h>

#ifdef DS_TEST
#define STBDS_UNIT_TESTS
#endif

#ifdef DS_STATS
#define STBDS_STATISTICS
#endif

#ifndef DS_PERF
#define STBDS_ASSERT assert
#include <assert.h>
#endif

//#define STBDS_SIPHASH_2_4
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
  stbds_unit_tests();
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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define STB_DEFINE
#define STB_NO_REGISTRY
//#include "../stb.h"


size_t t0, sum, mn,mx,count;
void begin(void)
{
  size_t t0;
  LARGE_INTEGER m;
  QueryPerformanceCounter(&m);
  t0 = m.QuadPart;
  sum = 0;
  count = 0;
  mx = 0;
  mn = ~(size_t) 0;
}

void measure(void)
{
  size_t t1, t;
  LARGE_INTEGER m;
  QueryPerformanceCounter(&m);
  t1 = m.QuadPart;
  t = t1-t0;
  if (t1 < t0)
    printf("ALERT: QueryPerformanceCounter was unordered!\n");
  if (t < mn) mn = t;
  if (t > mx) mx = t;
  sum += t;
  ++count;
  t0 = t1;
}

void dont_measure(void)
{
  size_t t1, t;
  LARGE_INTEGER m;
  QueryPerformanceCounter(&m);
  t0 = m.QuadPart;
}

double timer;
void end(void)
{
  LARGE_INTEGER m;
  QueryPerformanceFrequency(&m);

  if (count > 3) {
    // discard the highest and lowest
    sum -= mn;
    sum -= mx;
    count -= 2;
  }
  timer = (double) (sum) / count / m.QuadPart * 1000;
}

void build(int a, int b, int count, int step)
{
  struct { int key,value; } *map=NULL;
  int i,j,n,k;
  for (i=0; i < a; ++i)
    hmput(map,i*step,i+1);
  measure();
  churn_inserts = i;
  hmfree(map);
  dont_measure();
}

#ifdef STB__INCLUDE_STB_H
void build_stb(int a, int b, int count, int step)
{
  stb_idict *d = stb_idict_new_size(8);
  struct { int key,value; } *map=NULL;
  int i,j,n,k;
  for (i=0; i < a; ++i)
    stb_idict_add(d, i*step, i+1);
  measure();
  churn_inserts = i;
  stb_idict_destroy(d);
  dont_measure();
}
#endif

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


int main(int arg, char **argv)
{
  int n,s,w;
  double worst = 0;

#if 0
  begin(); for (n=0; n < 2000; ++n) { build_stb(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table\n", timer);
  begin(); for (n=0; n <  500; ++n) { build_stb(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table\n", timer);
  begin(); for (n=0; n <  100; ++n) { build_stb(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table\n", timer);
  begin(); for (n=0; n <   10; ++n) { build_stb(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table\n", timer);
  begin(); for (n=0; n <    5; ++n) { build_stb(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table\n", timer);
#endif

  begin(); for (n=0; n < 2000; ++n) { churn8(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <  500; ++n) { churn8(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <  100; ++n) { churn8(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { churn8(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table w/ 8-byte key\n", timer);
  begin(); for (n=0; n <    5; ++n) { churn8(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table w/ 8-byte key\n", timer);

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

  begin(); for (n=0; n < 2000; ++n) { build(2000,0,0,1);          } end(); printf("  // %7.2fms :      2,000 inserts creating 2K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <  500; ++n) { build(20000,0,0,1);         } end(); printf("  // %7.2fms :     20,000 inserts creating 20K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <  100; ++n) { build(200000,0,0,1);        } end(); printf("  // %7.2fms :    200,000 inserts creating 200K table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <   10; ++n) { build(2000000,0,0,1);       } end(); printf("  // %7.2fms :  2,000,000 inserts creating 2M table w/ 4-byte key\n", timer);
  begin(); for (n=0; n <    5; ++n) { build(20000000,0,0,1);      } end(); printf("  // %7.2fms : 20,000,000 inserts creating 20M table w/ 4-byte key\n", timer);

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
