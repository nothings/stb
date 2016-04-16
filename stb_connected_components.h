// stb_connected_components - v0.91 - public domain connected components on grids
//                                                 http://github.com/nothings/stb
//
// Finds connected components on 2D grids for testing reachability between
// two points, with fast updates when changing reachability (e.g. on one machine
// it was typically 0.2ms w/ 1024x1024 grid). Each grid square must be "open" or
// "closed" (traversable or untraversable), and grid squares are only connected
// to their orthogonal neighbors, not diagonally. 
//
// In one source file, create the implementation by doing something like this:
//
//   #define STBCC_GRID_COUNT_X_LOG2    10
//   #define STBCC_GRID_COUNT_Y_LOG2    10
//   #define STB_CONNECTED_COMPONENTS_IMPLEMENTATION
//   #include "stb_connected_components.h"
//
// The above creates an implementation that can run on maps up to 1024x1024.
// Map sizes must be a multiple of 32 on each axis.
// 
// LICENSE
// 
// This software is dual-licensed to the public domain and under the following
// license: you are granted a perpetual, irrevocable license to copy, modify,
// publish, and distribute this file as you see fit.
//
//
// CHANGELOG
//
//    0.92  (2016-04-16)  Compute sqrt(N) cluster size by default
//    0.91  (2016-04-15)  Initial release
//
// TODO:
//    - better API documentation
//    - more comments
//    - try re-integrating naive algorithm & compare performance
//    - more optimized batching (current approach still recomputes local clumps many times)
//    - function for setting a grid of squares at once (just use batching)
//    - shrink data by storing only, say, 2X max exits
//      (instead of max exits per clump), and repack cluster
//      if it runs out (possibly by just rebuilding from scratch,
//      could even use dirty-cluster data structure)
//      should reduce 1Kx1K from ~66MB to ~8MB
//
//  ALGORITHM
//
//      The NxN grid map is split into sqrt(N) x sqrt(N) blocks called
//     "clusters". Each cluster independently computes a set of connected
//      components within that cluster (ignoring all connectivity out of
//      that cluster) using a union-find disjoint set forest. This produces a bunch
//      of locally connected components called "clumps". Each clump is (a) connected
//      within its cluster, (b) does not directly connect to any other clumps in the
//      cluster (though it may connect to them by paths that lead outside the cluster,
//      but those are ignored at this step), and (c) maintains an adjacency list of
//      all clumps in adjacent clusters that it _is_ connected to. Then a second
//      union-find disjoint set forest is used to compute connected clumps
//      globally, across the whole map. Reachability is then computed by
//      finding which clump each input point belongs to, and checking whether
//      those clumps are in the same "global" connected component.
//
//      The above data structure can be updated efficiently; on a change
//      of a single grid square on the map, only one cluster changes its
//      purely-local state, so only one cluster needs its clumps fully
//      recomputed. Clumps in adjacent clusters need their adjacency lists
//      updated: first to remove all references to the old clumps in the
//      rebuilt cluster, then to add new references to the new clumps. Both
//      of these operations can use the existing "find which clump each input
//      point belongs to" query to compute that adjacency information rapidly.
//      In one 1024x1024 test on a specific machine, a one-tile update was
//      about 250 times faster than a full disjoint-set-forest on the full map.

#ifndef INCLUDE_STB_CONNECTED_COMPONENTS_H
#define INCLUDE_STB_CONNECTED_COMPONENTS_H

#include <stdlib.h>
#include <assert.h>

typedef struct st_stbcc_grid stbcc_grid;

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////////////////
//
//  initialization
//

// you allocate the grid data structure to this size (note that it will be very big!!!)
extern size_t stbcc_grid_sizeof(void);

// initialize the grid, value of map[] is 0 = traversable, non-0 is solid
extern void stbcc_init_grid(stbcc_grid *g, unsigned char *map, int w, int h);


//////////////////////////////////////////////////////////////////////////////////////////
//
//  main functionality
//

// update a grid square state, 0 = traversable, non-0 is solid
// i can add a batch-update if it's needed
extern void stbcc_update_grid(stbcc_grid *g, int x, int y, int solid);

// query if two grid squares are reachable from each other
extern int stbcc_query_grid_node_connection(stbcc_grid *g, int x1, int y1, int x2, int y2);


//////////////////////////////////////////////////////////////////////////////////////////
//
//  bonus functions
//

// wrap multiple stbcc_update_grid calls in these function to compute
// multiple updates more efficiently; cannot make queries inside batch
extern void stbcc_update_batch_begin(stbcc_grid *g);
extern void stbcc_update_batch_end(stbcc_grid *g);

// query the grid data structure for whether a given square is open or not
extern int stbcc_query_grid_open(stbcc_grid *g, int x, int y);

// get a unique id for the connected component this is in; it's not necessarily
// small, you'll need a hash table or something to remap it (or just use
extern unsigned int stbcc_get_unique_id(stbcc_grid *g, int x, int y);
#define STBCC_NULL_UNIQUE_ID 0xffffffff // returned for closed map squares

#ifdef __cplusplus
}
#endif

#endif // INCLUDE_STB_CONNECTED_COMPONENTS_H

#ifdef STB_CONNECTED_COMPONENTS_IMPLEMENTATION

#if !defined(STBCC_GRID_COUNT_X_LOG2) || !defined(STBCC_GRID_COUNT_Y_LOG2)
   #error "You must define STBCC_GRID_COUNT_X_LOG2 and STBCC_GRID_COUNT_Y_LOG2 to define the max grid supported."
#endif

#define STBCC__GRID_COUNT_X (1 << STBCC_GRID_COUNT_X_LOG2)
#define STBCC__GRID_COUNT_Y (1 << STBCC_GRID_COUNT_Y_LOG2)

#define STBCC__MAP_STRIDE   (1 << (STBCC_GRID_COUNT_X_LOG2-3))

#ifndef STBCC_CLUSTER_SIZE_X_LOG2
   #define STBCC_CLUSTER_SIZE_X_LOG2   (STBCC_GRID_COUNT_X_LOG2/2) // log2(sqrt(2^N)) = 1/2 * log2(2^N)) = 1/2 * N
   #if STBCC_CLUSTER_SIZE_X_LOG2 > 6
   #undef STBCC_CLUSTER_SIZE_X_LOG2
   #define STBCC_CLUSTER_SIZE_X_LOG2 6
   #endif
#endif

#ifndef STBCC_CLUSTER_SIZE_Y_LOG2
   #define STBCC_CLUSTER_SIZE_Y_LOG2   (STBCC_GRID_COUNT_Y_LOG2/2)
   #if STBCC_CLUSTER_SIZE_Y_LOG2 > 6
   #undef STBCC_CLUSTER_SIZE_Y_LOG2
   #define STBCC_CLUSTER_SIZE_Y_LOG2 6
   #endif
#endif

#define STBCC__CLUSTER_SIZE_X   (1 << STBCC_CLUSTER_SIZE_X_LOG2)
#define STBCC__CLUSTER_SIZE_Y   (1 << STBCC_CLUSTER_SIZE_Y_LOG2)

#define STBCC__CLUSTER_COUNT_X_LOG2   (STBCC_GRID_COUNT_X_LOG2 - STBCC_CLUSTER_SIZE_X_LOG2)
#define STBCC__CLUSTER_COUNT_Y_LOG2   (STBCC_GRID_COUNT_Y_LOG2 - STBCC_CLUSTER_SIZE_Y_LOG2)

#define STBCC__CLUSTER_COUNT_X  (1 << STBCC__CLUSTER_COUNT_X_LOG2)
#define STBCC__CLUSTER_COUNT_Y  (1 << STBCC__CLUSTER_COUNT_Y_LOG2)

#if STBCC__CLUSTER_SIZE_X >= STBCC__GRID_COUNT_X || STBCC__CLUSTER_SIZE_Y >= STBCC__GRID_COUNT_Y
   #error "STBCC_CLUSTER_SIZE_X/Y_LOG2 must be smaller than STBCC_GRID_COUNT_X/Y_LOG2"
#endif

// worst case # of clumps per cluster
#define STBCC__MAX_CLUMPS_PER_CLUSTER_LOG2   (STBCC_CLUSTER_SIZE_X_LOG2 + STBCC_CLUSTER_SIZE_Y_LOG2-1)
#define STBCC__MAX_CLUMPS_PER_CLUSTER        (1 << STBCC__MAX_CLUMPS_PER_CLUSTER_LOG2)
#define STBCC__MAX_CLUMPS                    (STBCC__MAX_CLUMPS_PER_CLUSTER * STBCC__CLUSTER_COUNT_X * STBCC__CLUSTER_COUNT_Y)
#define STBCC__NULL_CLUMPID                  STBCC__MAX_CLUMPS_PER_CLUSTER

#define STBCC__CLUSTER_X_FOR_COORD_X(x)  ((x) >> STBCC_CLUSTER_SIZE_X_LOG2)
#define STBCC__CLUSTER_Y_FOR_COORD_Y(y)  ((y) >> STBCC_CLUSTER_SIZE_Y_LOG2)

#define STBCC__MAP_BYTE_MASK(x,y)       (1 << ((x) & 7))
#define STBCC__MAP_BYTE(g,x,y)          ((g)->map[y][(x) >> 3])
#define STBCC__MAP_OPEN(g,x,y)          (STBCC__MAP_BYTE(g,x,y) & STBCC__MAP_BYTE_MASK(x,y))

typedef unsigned short stbcc__clumpid;
typedef unsigned char stbcc__verify_max_clumps[STBCC__MAX_CLUMPS_PER_CLUSTER < (1 << (8*sizeof(stbcc__clumpid))) ? 1 : -1];

#define STBCC__MAX_EXITS_PER_CLUMP    (STBCC__CLUSTER_SIZE_X + STBCC__CLUSTER_SIZE_Y)   // 64
// 2^19 * 2^6 => 2^25 exits => 2^26  => 64MB for 1024x1024

typedef unsigned char stbcc__verify_max_exits[STBCC__MAX_EXITS_PER_CLUMP <= 256];

typedef struct
{
   unsigned short clump_index:12;
     signed short cluster_dx:2;
     signed short cluster_dy:2;
} stbcc__relative_clumpid;

typedef union
{
   struct {
      unsigned int clump_index:12;
      unsigned int cluster_x:10;
      unsigned int cluster_y:10;
   } f;
   unsigned int c;
} stbcc__global_clumpid;

// rebuilt cluster 3,4

// what changes in cluster 2,4

typedef struct
{
   stbcc__global_clumpid global_label;
   unsigned short num_adjacent;
   stbcc__relative_clumpid adjacent_clumps[STBCC__MAX_EXITS_PER_CLUMP];
} stbcc__clump;

typedef struct
{
   unsigned int num_clumps;
   stbcc__clump clump[STBCC__MAX_CLUMPS_PER_CLUSTER];
} stbcc__cluster;

struct st_stbcc_grid
{
   int w,h,cw,ch;
   int in_batched_update;
   //unsigned char cluster_dirty[STBCC__CLUSTER_COUNT_Y][STBCC__CLUSTER_COUNT_X]; // could bitpack, but: 1K x 1K => 1KB
   unsigned char map[STBCC__GRID_COUNT_Y][STBCC__MAP_STRIDE]; // 1K x 1K => 1K x 128 => 128KB
   stbcc__clumpid clump_for_node[STBCC__GRID_COUNT_Y][STBCC__GRID_COUNT_X];  // 1K x 1K x 2 = 2MB
   stbcc__cluster cluster[STBCC__CLUSTER_COUNT_Y][STBCC__CLUSTER_COUNT_X]; //  1K x 1K x 0.5 x 64 x 2 = 64MB
};

int stbcc_query_grid_node_connection(stbcc_grid *g, int x1, int y1, int x2, int y2)
{
   stbcc__global_clumpid label1, label2;
   stbcc__clumpid c1 = g->clump_for_node[y1][x1];
   stbcc__clumpid c2 = g->clump_for_node[y2][x2];
   int cx1 = STBCC__CLUSTER_X_FOR_COORD_X(x1);
   int cy1 = STBCC__CLUSTER_Y_FOR_COORD_Y(y1);
   int cx2 = STBCC__CLUSTER_X_FOR_COORD_X(x2);
   int cy2 = STBCC__CLUSTER_Y_FOR_COORD_Y(y2);
   assert(!g->in_batched_update);
   if (c1 == STBCC__NULL_CLUMPID || c2 == STBCC__NULL_CLUMPID)
      return 0;
   label1 = g->cluster[cy1][cx1].clump[c1].global_label;
   label2 = g->cluster[cy2][cx2].clump[c2].global_label;
   if (label1.c == label2.c)
      return 1;
   return 0;
}

int stbcc_query_grid_open(stbcc_grid *g, int x, int y)
{
   return STBCC__MAP_OPEN(g, x, y) != 0;
}

unsigned int stbcc_get_unique_id(stbcc_grid *g, int x, int y)
{
   stbcc__clumpid c = g->clump_for_node[y][x];
   int cx = STBCC__CLUSTER_X_FOR_COORD_X(x);
   int cy = STBCC__CLUSTER_Y_FOR_COORD_Y(y);
   assert(!g->in_batched_update);
   if (c == STBCC__NULL_CLUMPID) return STBCC_NULL_UNIQUE_ID;
   return g->cluster[cy][cx].clump[c].global_label.c;
}

typedef struct
{
   unsigned char x,y;
} stbcc__tinypoint;

typedef struct
{
   stbcc__tinypoint parent[STBCC__CLUSTER_SIZE_Y][STBCC__CLUSTER_SIZE_X]; // 32x32 => 2KB
   stbcc__clumpid   label[STBCC__CLUSTER_SIZE_Y][STBCC__CLUSTER_SIZE_X];
} stbcc__cluster_build_info;

static void stbcc__build_clumps_for_cluster(stbcc_grid *g, int cx, int cy);
static void stbcc__remove_connections_to_adjacent_cluster(stbcc_grid *g, int cx, int cy, int dx, int dy);
static void stbcc__add_connections_to_adjacent_cluster(stbcc_grid *g, int cx, int cy, int dx, int dy);

static stbcc__global_clumpid stbcc__clump_find(stbcc_grid *g, stbcc__global_clumpid n)
{
   stbcc__global_clumpid q;
   stbcc__clump *c = &g->cluster[n.f.cluster_y][n.f.cluster_x].clump[n.f.clump_index];

   if (c->global_label.c == n.c)
      return n;

   q = stbcc__clump_find(g, c->global_label);
   c->global_label = q;
   return q;
}

typedef struct
{
   unsigned int cluster_x;
   unsigned int cluster_y;
   unsigned int clump_index;
} stbcc__unpacked_clumpid;

// @OPTIMIZE: pass in these parameters unpacked, not packed
static void stbcc__clump_union(stbcc_grid *g, stbcc__unpacked_clumpid m, int x, int y, int idx)
{
   stbcc__clump *mc = &g->cluster[m.cluster_y][m.cluster_x].clump[m.clump_index];
   stbcc__clump *nc = &g->cluster[y][x].clump[idx];
   stbcc__global_clumpid mp = stbcc__clump_find(g, mc->global_label);
   stbcc__global_clumpid np = stbcc__clump_find(g, nc->global_label);

   if (mp.c == np.c)
      return;

   g->cluster[mp.f.cluster_y][mp.f.cluster_x].clump[mp.f.clump_index].global_label = np;
}

static void stbcc__build_connected_components_for_clumps(stbcc_grid *g)
{
   int i,j,k,h;

   for (j=0; j < STBCC__CLUSTER_COUNT_Y; ++j) {
      for (i=0; i < STBCC__CLUSTER_COUNT_X; ++i) {
         stbcc__cluster *cluster = &g->cluster[j][i];
         for (k=0; k < (int) cluster->num_clumps; ++k) {
            stbcc__global_clumpid m;
            m.f.clump_index = k;
            m.f.cluster_x = i;
            m.f.cluster_y = j;
            assert((int) m.f.clump_index == k && (int) m.f.cluster_x == i && (int) m.f.cluster_y == j);
            cluster->clump[k].global_label = m;
         }
      }
   }

   for (j=0; j < STBCC__CLUSTER_COUNT_Y; ++j) {
      for (i=0; i < STBCC__CLUSTER_COUNT_X; ++i) {
         stbcc__cluster *cluster = &g->cluster[j][i];
         for (k=0; k < (int) cluster->num_clumps; ++k) {
            stbcc__clump *clump = &cluster->clump[k];
            stbcc__unpacked_clumpid m;
            m.clump_index = k;
            m.cluster_x = i;
            m.cluster_y = j;
            for (h=0; h < clump->num_adjacent; ++h) {
               unsigned int clump_index = clump->adjacent_clumps[h].clump_index;
               unsigned int x = clump->adjacent_clumps[h].cluster_dx + i;
               unsigned int y = clump->adjacent_clumps[h].cluster_dy + j;
               stbcc__clump_union(g, m, x, y, clump_index);
            }
         }
      }
   }

   for (j=0; j < STBCC__CLUSTER_COUNT_Y; ++j) {
      for (i=0; i < STBCC__CLUSTER_COUNT_X; ++i) {
         stbcc__cluster *cluster = &g->cluster[j][i];
         for (k=0; k < (int) cluster->num_clumps; ++k) {
            stbcc__global_clumpid m;
            m.f.clump_index = k;
            m.f.cluster_x = i;
            m.f.cluster_y = j;
            stbcc__clump_find(g, m);
         }
      }
   }
}

void stbcc_update_grid(stbcc_grid *g, int x, int y, int solid)
{
   int cx,cy;

   if (!solid) {
      if (STBCC__MAP_OPEN(g,x,y))
         return;
   } else {
      if (!STBCC__MAP_OPEN(g,x,y))
         return;
   }

   cx = STBCC__CLUSTER_X_FOR_COORD_X(x);
   cy = STBCC__CLUSTER_Y_FOR_COORD_Y(y);

   stbcc__remove_connections_to_adjacent_cluster(g, cx-1, cy,  1, 0);
   stbcc__remove_connections_to_adjacent_cluster(g, cx+1, cy, -1, 0);
   stbcc__remove_connections_to_adjacent_cluster(g, cx, cy-1,  0, 1);
   stbcc__remove_connections_to_adjacent_cluster(g, cx, cy+1,  0,-1);

   if (!solid)
      STBCC__MAP_BYTE(g,x,y) |= STBCC__MAP_BYTE_MASK(x,y);
   else
      STBCC__MAP_BYTE(g,x,y) &= ~STBCC__MAP_BYTE_MASK(x,y);

   stbcc__build_clumps_for_cluster(g, cx, cy);

   stbcc__add_connections_to_adjacent_cluster(g, cx, cy, -1, 0);
   stbcc__add_connections_to_adjacent_cluster(g, cx, cy,  1, 0);
   stbcc__add_connections_to_adjacent_cluster(g, cx, cy,  0,-1);
   stbcc__add_connections_to_adjacent_cluster(g, cx, cy,  0, 1);

   stbcc__add_connections_to_adjacent_cluster(g, cx-1, cy,  1, 0);
   stbcc__add_connections_to_adjacent_cluster(g, cx+1, cy, -1, 0);
   stbcc__add_connections_to_adjacent_cluster(g, cx, cy-1,  0, 1);
   stbcc__add_connections_to_adjacent_cluster(g, cx, cy+1,  0,-1);

   if (!g->in_batched_update)
      stbcc__build_connected_components_for_clumps(g);
   #if 0
   else
      g->cluster_dirty[cy][cx] = 1;
   #endif
}

void stbcc_update_batch_begin(stbcc_grid *g)
{
   assert(!g->in_batched_update);
   g->in_batched_update = 1;
}

void stbcc_update_batch_end(stbcc_grid *g)
{
   assert(g->in_batched_update);
   g->in_batched_update =  0;
   stbcc__build_connected_components_for_clumps(g); // @OPTIMIZE: only do this if update was non-empty
}

size_t stbcc_grid_sizeof(void)
{
   return sizeof(stbcc_grid);
}

void stbcc_init_grid(stbcc_grid *g, unsigned char *map, int w, int h)
{
   int i,j,k;
   assert(w % STBCC__CLUSTER_SIZE_X == 0);
   assert(h % STBCC__CLUSTER_SIZE_Y == 0);
   assert(w % 8 == 0);

   g->w = w;
   g->h = h;
   g->cw = w >> STBCC_CLUSTER_SIZE_X_LOG2;
   g->ch = h >> STBCC_CLUSTER_SIZE_Y_LOG2;
   g->in_batched_update = 0;

   #if 0
   for (j=0; j < STBCC__CLUSTER_COUNT_Y; ++j)
      for (i=0; i < STBCC__CLUSTER_COUNT_X; ++i) 
         g->cluster_dirty[j][i] = 0;
   #endif

   for (j=0; j < h; ++j) {
      for (i=0; i < w; i += 8) {
         unsigned char c = 0;
         for (k=0; k < 8; ++k)
            if (map[j*w + (i+k)] == 0)
               c |= (1 << k);
         g->map[j][i>>3] = c;
      }
   }

   for (j=0; j < g->ch; ++j)
      for (i=0; i < g->cw; ++i)
         stbcc__build_clumps_for_cluster(g, i, j);

   for (j=0; j < g->ch; ++j) {
      for (i=0; i < g->cw; ++i) {
         stbcc__add_connections_to_adjacent_cluster(g, i, j, -1, 0);
         stbcc__add_connections_to_adjacent_cluster(g, i, j,  1, 0);
         stbcc__add_connections_to_adjacent_cluster(g, i, j,  0,-1);
         stbcc__add_connections_to_adjacent_cluster(g, i, j,  0, 1);
      }
   }

   stbcc__build_connected_components_for_clumps(g);

   for (j=0; j < g->h; ++j)
      for (i=0; i < g->w; ++i)
         assert(g->clump_for_node[j][i] <= STBCC__NULL_CLUMPID);
}


static void stbcc__add_clump_connection(stbcc_grid *g, int x1, int y1, int x2, int y2)
{
   stbcc__clump *clump;

   int cx1 = STBCC__CLUSTER_X_FOR_COORD_X(x1);
   int cy1 = STBCC__CLUSTER_Y_FOR_COORD_Y(y1);
   int cx2 = STBCC__CLUSTER_X_FOR_COORD_X(x2);
   int cy2 = STBCC__CLUSTER_Y_FOR_COORD_Y(y2);

   stbcc__clumpid c1 = g->clump_for_node[y1][x1];
   stbcc__clumpid c2 = g->clump_for_node[y2][x2];

   stbcc__relative_clumpid rc;

   assert(cx1 != cx2 || cy1 != cy2);
   assert(abs(cx1-cx2) + abs(cy1-cy2) == 1);

   // add connection to c2 in c1

   rc.clump_index = c2;
   rc.cluster_dx = x2-x1;
   rc.cluster_dy = y2-y1;

   clump = &g->cluster[cy1][cx1].clump[c1];
   assert(clump->num_adjacent < STBCC__MAX_EXITS_PER_CLUMP);
   clump->adjacent_clumps[clump->num_adjacent++] = rc;
}

static void stbcc__remove_clump_connection(stbcc_grid *g, int x1, int y1, int x2, int y2)
{
   stbcc__clump *clump;
   int i;

   int cx1 = STBCC__CLUSTER_X_FOR_COORD_X(x1);
   int cy1 = STBCC__CLUSTER_Y_FOR_COORD_Y(y1);
   int cx2 = STBCC__CLUSTER_X_FOR_COORD_X(x2);
   int cy2 = STBCC__CLUSTER_Y_FOR_COORD_Y(y2);

   stbcc__clumpid c1 = g->clump_for_node[y1][x1];
   stbcc__clumpid c2 = g->clump_for_node[y2][x2];

   stbcc__relative_clumpid rc;

   assert(cx1 != cx2 || cy1 != cy2);
   assert(abs(cx1-cx2) + abs(cy1-cy2) == 1);

   // add connection to c2 in c1

   rc.clump_index = c2;
   rc.cluster_dx = x2-x1;
   rc.cluster_dy = y2-y1;

   clump = &g->cluster[cy1][cx1].clump[c1];

   for (i=0; i < clump->num_adjacent; ++i)
      if (rc.clump_index == clump->adjacent_clumps[i].clump_index &&
          rc.cluster_dx  == clump->adjacent_clumps[i].cluster_dx  &&
          rc.cluster_dy  == clump->adjacent_clumps[i].cluster_dy) 
         break;

   if (i < clump->num_adjacent)
      clump->adjacent_clumps[i] = clump->adjacent_clumps[--clump->num_adjacent];
   else
      assert(0);
}

static void stbcc__add_connections_to_adjacent_cluster(stbcc_grid *g, int cx, int cy, int dx, int dy)
{
   unsigned char connected[STBCC__MAX_CLUMPS_PER_CLUSTER/8] = { 0 };
   int x = cx * STBCC__CLUSTER_SIZE_X;
   int y = cy * STBCC__CLUSTER_SIZE_Y;
   int step_x, step_y=0, i, j, k, n;

   if (cx < 0 || cx >= g->cw || cy < 0 || cy >= g->ch)
      return;

   if (cx+dx < 0 || cx+dx >= g->cw || cy+dy < 0 || cy+dy >= g->ch)
      return;

   assert(abs(dx) + abs(dy) == 1);

   if (dx == 1) {
      i = STBCC__CLUSTER_SIZE_X-1;
      j = 0;
      step_x = 0;
      step_y = 1;
      n = STBCC__CLUSTER_SIZE_Y;
   } else if (dx == -1) {
      i = 0;
      j = 0;
      step_x = 0;
      step_y = 1;  
      n = STBCC__CLUSTER_SIZE_Y;
   } else if (dy == -1) {
      i = 0;
      j = 0;
      step_x = 1;
      step_y = 0;
      n = STBCC__CLUSTER_SIZE_X;
   } else if (dy == 1) {
      i = 0;
      j = STBCC__CLUSTER_SIZE_Y-1;
      step_x = 1;
      step_y = 0;
      n = STBCC__CLUSTER_SIZE_X;
   } else {
      assert(0);
   }

   for (k=0; k < n; ++k) {
      if (STBCC__MAP_OPEN(g, x+i, y+j) && STBCC__MAP_OPEN(g, x+i+dx, y+j+dy)) {
         stbcc__clumpid c = g->clump_for_node[y+j+dy][x+i+dx];
         if (0 == (connected[c>>3] & (1 << (c & 7)))) {
            connected[c>>3] |= 1 << (c & 7);
            stbcc__add_clump_connection(g, x+i, y+j, x+i+dx, y+j+dy);
         }
      }
      i += step_x;
      j += step_y;
   }
}

static void stbcc__remove_connections_to_adjacent_cluster(stbcc_grid *g, int cx, int cy, int dx, int dy)
{
   unsigned char disconnected[STBCC__MAX_CLUMPS_PER_CLUSTER/8] = { 0 };
   int x = cx * STBCC__CLUSTER_SIZE_X;
   int y = cy * STBCC__CLUSTER_SIZE_Y;
   int step_x, step_y=0, i, j, k, n;

   if (cx < 0 || cx >= g->cw || cy < 0 || cy >= g->ch)
      return;

   if (cx+dx < 0 || cx+dx >= g->cw || cy+dy < 0 || cy+dy >= g->ch)
      return;

   assert(abs(dx) + abs(dy) == 1);

   if (dx == 1) {
      i = STBCC__CLUSTER_SIZE_X-1;
      j = 0;
      step_x = 0;
      step_y = 1;
      n = STBCC__CLUSTER_SIZE_Y;
   } else if (dx == -1) {
      i = 0;
      j = 0;
      step_x = 0;
      step_y = 1;  
      n = STBCC__CLUSTER_SIZE_Y;
   } else if (dy == -1) {
      i = 0;
      j = 0;
      step_x = 1;
      step_y = 0;
      n = STBCC__CLUSTER_SIZE_X;
   } else if (dy == 1) {
      i = 0;
      j = STBCC__CLUSTER_SIZE_Y-1;
      step_x = 1;
      step_y = 0;
      n = STBCC__CLUSTER_SIZE_X;
   } else {
      assert(0);
   }

   for (k=0; k < n; ++k) {
      if (STBCC__MAP_OPEN(g, x+i, y+j) && STBCC__MAP_OPEN(g, x+i+dx, y+j+dy)) {
         stbcc__clumpid c = g->clump_for_node[y+j+dy][x+i+dx];
         if (0 == (disconnected[c>>3] & (1 << (c & 7)))) {
            disconnected[c>>3] |= 1 << (c & 7);
            stbcc__remove_clump_connection(g, x+i, y+j, x+i+dx, y+j+dy);
         }
      }
      i += step_x;
      j += step_y;
   }
}

static stbcc__tinypoint stbcc__incluster_find(stbcc__cluster_build_info *cbi, int x, int y)
{
   stbcc__tinypoint p,q;
   p = cbi->parent[y][x];
   if (p.x == x && p.y == y)
      return p;
   q = stbcc__incluster_find(cbi, p.x, p.y);
   cbi->parent[y][x] = q;
   return q;
}

static void stbcc__incluster_union(stbcc__cluster_build_info *cbi, int x1, int y1, int x2, int y2)
{
   stbcc__tinypoint p = stbcc__incluster_find(cbi, x1,y1);
   stbcc__tinypoint q = stbcc__incluster_find(cbi, x2,y2);

   if (p.x == q.x && p.y == q.y)
      return;

   cbi->parent[p.y][p.x] = q;
}

static void stbcc__build_clumps_for_cluster(stbcc_grid *g, int cx, int cy)
{
   stbcc__cluster *c;
   stbcc__cluster_build_info cbi;
   int label=0;
   int i,j;
   int x = cx * STBCC__CLUSTER_SIZE_X;
   int y = cy * STBCC__CLUSTER_SIZE_Y;

   // set initial disjoint set forest state
   for (j=0; j < STBCC__CLUSTER_SIZE_Y; ++j) {
      for (i=0; i < STBCC__CLUSTER_SIZE_X; ++i) {
         cbi.parent[j][i].x = i;
         cbi.parent[j][i].y = j;
      }
   }

   // join all sets that are connected
   for (j=0; j < STBCC__CLUSTER_SIZE_Y; ++j) {
      // check down only if not on bottom row
      if (j < STBCC__CLUSTER_SIZE_Y-1)
         for (i=0; i < STBCC__CLUSTER_SIZE_X; ++i)
            if (STBCC__MAP_OPEN(g,x+i,y+j) && STBCC__MAP_OPEN(g,x+i  ,y+j+1))
               stbcc__incluster_union(&cbi, i,j, i,j+1);
      // check right for everything but rightmost column
      for (i=0; i < STBCC__CLUSTER_SIZE_X-1; ++i)
         if (STBCC__MAP_OPEN(g,x+i,y+j) && STBCC__MAP_OPEN(g,x+i+1,y+j  ))
            stbcc__incluster_union(&cbi, i,j, i+1,j);
   }

   // label all non-empty leaders
   for (j=0; j < STBCC__CLUSTER_SIZE_Y; ++j) {
      for (i=0; i < STBCC__CLUSTER_SIZE_X; ++i) {
         stbcc__tinypoint p = cbi.parent[j][i];
         if (p.x == i && p.y == j)
            if (STBCC__MAP_OPEN(g,x+i,y+j))
               cbi.label[j][i] = label++;
            else
               cbi.label[j][i] = STBCC__NULL_CLUMPID;
      }
   }

   // label all other nodes
   for (j=0; j < STBCC__CLUSTER_SIZE_Y; ++j) {
      for (i=0; i < STBCC__CLUSTER_SIZE_X; ++i) {
         stbcc__tinypoint p = stbcc__incluster_find(&cbi, i,j);
         if (p.x != i || p.y != j) {
            if (STBCC__MAP_OPEN(g,x+i,y+j))
               cbi.label[j][i] = cbi.label[p.y][p.x];
         }
      }
   }

   c = &g->cluster[cy][cx];
   c->num_clumps = label;
   for (i=0; i < label; ++i)
      c->clump[i].num_adjacent = 0;

   for (j=0; j < STBCC__CLUSTER_SIZE_Y; ++j)
      for (i=0; i < STBCC__CLUSTER_SIZE_X; ++i) {
         g->clump_for_node[y+j][x+i] = cbi.label[j][i]; // @OPTIMIZE: remove cbi.label entirely
         assert(g->clump_for_node[y+j][x+i] <= STBCC__NULL_CLUMPID);
      }
}

#endif // STB_CONNECTED_COMPONENTS_IMPLEMENTATION
