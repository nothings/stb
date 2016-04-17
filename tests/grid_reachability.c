#define STB_CONNECTED_COMPONENTS_IMPLEMENTATION
#define STBCC_GRID_COUNT_X_LOG2  10
#define STBCC_GRID_COUNT_Y_LOG2  10
#include "stb_connected_components.h"

#ifdef GRID_TEST

#include <windows.h>
#include <stdio.h>
#include <direct.h>

//#define STB_DEFINE
#include "stb.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct
{
   uint16 x,y;
} point;

point leader[1024][1024];
uint32 color[1024][1024];

point find(int x, int y)
{
   point p,q;
   p = leader[y][x];
   if (p.x == x && p.y == y)
      return p;
   q = find(p.x, p.y);
   leader[y][x] = q;
   return q;
}

void onion(int x1, int y1, int x2, int y2)
{
   point p = find(x1,y1);
   point q = find(x2,y2);

   if (p.x == q.x && p.y == q.y)
      return;

   leader[p.y][p.x] = q;
}

void reference(uint8 *map, int w, int h)
{
   int i,j;

   for (j=0; j < h; ++j) {
      for (i=0; i < w; ++i) {
         leader[j][i].x = i;
         leader[j][i].y = j;
      }
   }
         
   for (j=1; j < h-1; ++j) {
      for (i=1; i < w-1; ++i) {
         if (map[j*w+i] == 255) {
            if (map[(j+1)*w+i] == 255) onion(i,j, i,j+1);
            if (map[(j)*w+i+1] == 255) onion(i,j, i+1,j);
         }
      }
   }

   for (j=0; j < h; ++j) {
      for (i=0; i < w; ++i) {
         uint32 c = 0xff000000;
         if (leader[j][i].x == i && leader[j][i].y == j) {
            if (map[j*w+i] == 255)
               c = stb_randLCG() | 0xff404040;
         }
         color[j][i] = c;
      }
   }

   for (j=0; j < h; ++j) {
      for (i=0; i < w; ++i) {
         if (leader[j][i].x != i || leader[j][i].y != j) {
            point p = find(i,j);
            color[j][i] = color[p.y][p.x];
         }
      }
   }
}

void write_map(stbcc_grid *g, int w, int h, char *filename)
{
   int i,j;
   for (j=0; j < h; ++j) {
      for (i=0; i < w; ++i) {
         unsigned int c;
         c = stbcc_get_unique_id(g,i,j);
         if (c == STBCC_NULL_UNIQUE_ID)
            c = 0xff000000;
         else
            c = (~c)^0x555555;
         color[j][i] = c;
      }
   }
   stbi_write_png(filename, w, h, 4, color, 0);
}

void test_connected(stbcc_grid *g)
{
   int n = stbcc_query_grid_node_connection(g, 512, 90, 512, 871);
   //printf("%d ", n);
}

static char *message;
LARGE_INTEGER start;

void start_timer(char *s)
{
   message = s;
   QueryPerformanceCounter(&start);
}

void end_timer(void)
{
   LARGE_INTEGER end, freq;
   double tm;

   QueryPerformanceCounter(&end);
   QueryPerformanceFrequency(&freq);

   tm = (end.QuadPart - start.QuadPart) / (double) freq.QuadPart;
   printf("%6.4lf ms: %s\n", tm * 1000, message);
}

int loc[5000][2];
int main(int argc, char **argv)
{
   stbcc_grid *g;

   int w,h, i,j,k=0, count=0, r;
   uint8 *map = stbi_load("data/map_03.png", &w, &h, 0, 1);

   assert(map);

   for (j=0; j < h; ++j)
      for (i=0; i < w; ++i)
         map[j*w+i] = ~map[j*w+i];

   for (i=0; i < w; ++i)
      for (j=0; j < h; ++j)
         //map[j*w+i] = (((i+1) ^ (j+1)) >> 1) & 1 ? 255 : 0;
         map[j*w+i] = stb_max(abs(i-w/2),abs(j-h/2)) & 1 ? 255 : 0;
         //map[j*w+i] = (((i ^ j) >> 5) ^ (i ^ j)) & 1 ? 255 : 0;
         //map[j*w+i] = stb_rand() & 1 ? 255 : 0;

   #if 1
   for (i=0; i < 100000; ++i)
      map[(stb_rand()%h)*w + stb_rand()%w] ^= 255;
   #endif
            
   stbi_write_png("tests/output/stbcc/reference.png", w, h, 1, map, 0);

   //reference(map, w, h);

   _mkdir("tests/output/stbcc");

   g = malloc(stbcc_grid_sizeof());
   printf("Size: %d\n", stbcc_grid_sizeof());

   start_timer("init");
   stbcc_init_grid(g, map, w, h);
   end_timer();
   write_map(g, w, h, "tests/output/stbcc/base.png");

   for (i=0; i < 5000;) {
      loc[i][0] = stb_rand() % w;
      loc[i][1] = stb_rand() % h;
      if (stbcc_query_grid_open(g, loc[i][0], loc[i][1]))
         ++i;
   }

   r = 0;
   start_timer("reachable");
   for (i=0; i < 2000; ++i) {
      for (j=0; j < 2000; ++j) {
         int x1 = loc[i][0], y1 = loc[i][1];
         int x2 = loc[2000+j][0], y2 = loc[2000+j][1];
         r += stbcc_query_grid_node_connection(g, x1,y1, x2,y2);
      }
   }
   end_timer();
   printf("%d reachable\n", r);

   printf("Cluster size: %d,%d\n", STBCC__CLUSTER_SIZE_X, STBCC__CLUSTER_SIZE_Y);

   #if 1
   for (j=0; j < 10; ++j) {
      for (i=0; i < 5000; ++i) {
         loc[i][0] = stb_rand() % w;
         loc[i][1] = stb_rand() % h;
      }
      start_timer("updating 2500");
      for (i=0; i < 2500; ++i) {
         if (stbcc_query_grid_open(g, loc[i][0], loc[i][1]))
            stbcc_update_grid(g, loc[i][0], loc[i][1], 1);
         else
            stbcc_update_grid(g, loc[i][0], loc[i][1], 0);
      }
      end_timer();
      write_map(g, w, h, stb_sprintf("tests/output/stbcc/update_random_%d.png", j*i));
   }
   #endif

   #if 0
   start_timer("removing");
   count = 0;
   for (i=0; i < 1800; ++i) {
      int x,y,a,b;
      x = stb_rand() % (w-32);
      y = stb_rand() % (h-32);
      
      if (i & 1) {
         for (a=0; a < 32; ++a)
            for (b=0; b < 1; ++b)
               if (stbcc_query_grid_open(g, x+a, y+b)) {
                  stbcc_update_grid(g, x+a, y+b, 1);
                  ++count;
               }
      } else {
         for (a=0; a < 1; ++a)
            for (b=0; b < 32; ++b)
               if (stbcc_query_grid_open(g, x+a, y+b)) {
                  stbcc_update_grid(g, x+a, y+b, 1);
                  ++count;
               }
      }

      //if (i % 100 == 0) write_map(g, w, h, stb_sprintf("tests/output/stbcc/open_random_%d.png", i+1));
   }
   end_timer();
   printf("Removed %d grid spaces\n", count);
   write_map(g, w, h, stb_sprintf("tests/output/stbcc/open_random_%d.png", i));


   r = 0;
   start_timer("reachable");
   for (i=0; i < 1000; ++i) {
      for (j=0; j < 1000; ++j) {
         int x1 = loc[i][0], y1 = loc[i][1];
         int x2 = loc[j][0], y2 = loc[j][1];
         r += stbcc_query_grid_node_connection(g, x1,y1, x2,y2);
      }
   }
   end_timer();
   printf("%d reachable\n", r);

   start_timer("adding");
   count = 0;
   for (i=0; i < 1800; ++i) {
      int x,y,a,b;
      x = stb_rand() % (w-32);
      y = stb_rand() % (h-32);

      if (i & 1) {
         for (a=0; a < 32; ++a)
            for (b=0; b < 1; ++b)
               if (!stbcc_query_grid_open(g, x+a, y+b)) {
                  stbcc_update_grid(g, x+a, y+b, 0);
                  ++count;
               }
      } else {
         for (a=0; a < 1; ++a)
            for (b=0; b < 32; ++b)
               if (!stbcc_query_grid_open(g, x+a, y+b)) {
                  stbcc_update_grid(g, x+a, y+b, 0);
                  ++count;
               }
      }

      //if (i % 100 == 0) write_map(g, w, h, stb_sprintf("tests/output/stbcc/close_random_%d.png", i+1));
   }
   end_timer();
   write_map(g, w, h, stb_sprintf("tests/output/stbcc/close_random_%d.png", i));
   printf("Added %d grid spaces\n", count);
   #endif


   #if 0  // for map_02.png
   start_timer("process");
   for (k=0; k < 20; ++k) {
      for (j=0; j < h; ++j) {
         int any=0;
         for (i=0; i < w; ++i) {
            if (map[j*w+i] > 10 && map[j*w+i] < 250) {
               //start_timer(stb_sprintf("open %d,%d", i,j));
               stbcc_update_grid(g, i, j, 0);
               test_connected(g);
               //end_timer();
               any = 1;
            }
         }
         if (any) write_map(g, w, h, stb_sprintf("tests/output/stbcc/open_row_%04d.png", j));
      }

      for (j=0; j < h; ++j) {
         int any=0;
         for (i=0; i < w; ++i) {
            if (map[j*w+i] > 10 && map[j*w+i] < 250) {
               //start_timer(stb_sprintf("close %d,%d", i,j));
               stbcc_update_grid(g, i, j, 1);
               test_connected(g);
               //end_timer();
               any = 1;
            }
         }
         if (any) write_map(g, w, h, stb_sprintf("tests/output/stbcc/close_row_%04d.png", j));
      }
   }
   end_timer();
   #endif

   return 0;
}
#endif
