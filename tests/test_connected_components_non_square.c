#include <assert.h>
#include <stdlib.h>

#ifndef STBCC_GRID_COUNT_X_LOG2
#define STBCC_GRID_COUNT_X_LOG2 4
#endif
#ifndef STBCC_GRID_COUNT_Y_LOG2
#define STBCC_GRID_COUNT_Y_LOG2 3
#endif
#ifndef STBCC_CLUSTER_SIZE_X_LOG2
#define STBCC_CLUSTER_SIZE_X_LOG2 3
#endif
#ifndef STBCC_CLUSTER_SIZE_Y_LOG2
#define STBCC_CLUSTER_SIZE_Y_LOG2 2
#endif
#define STB_CONNECTED_COMPONENTS_IMPLEMENTATION
#include "../stb_connected_components.h"

static unsigned int test_random_state = 0x12345678;

static unsigned int test_random(void)
{
   test_random_state = test_random_state * 1664525u + 1013904223u;
   return test_random_state;
}

static void reference_components(const unsigned char *map, int *component)
{
   int queue[(1 << STBCC_GRID_COUNT_X_LOG2) * (1 << STBCC_GRID_COUNT_Y_LOG2)];
   int width = 1 << STBCC_GRID_COUNT_X_LOG2;
   int height = 1 << STBCC_GRID_COUNT_Y_LOG2;
   int i, j, x, y, head, tail, nx, ny, index, component_id;

   for (i = 0; i < width * height; ++i)
      component[i] = -1;

   component_id = 0;
   for (y = 0; y < height; ++y) {
      for (x = 0; x < width; ++x) {
         index = y * width + x;
         if (map[index] != 0 || component[index] >= 0)
            continue;

         head = 0;
         tail = 0;
         queue[tail++] = index;
         component[index] = component_id;
         while (head < tail) {
            index = queue[head++];
            nx = index % width;
            ny = index / width;
            for (j = 0; j < 4; ++j) {
               int dx = (j == 0) - (j == 1);
               int dy = (j == 2) - (j == 3);
               int neighbor;
               if (nx + dx < 0 || nx + dx >= width || ny + dy < 0 || ny + dy >= height)
                  continue;
               neighbor = (ny + dy) * width + nx + dx;
               if (map[neighbor] == 0 && component[neighbor] < 0) {
                  component[neighbor] = component_id;
                  queue[tail++] = neighbor;
               }
            }
         }
         ++component_id;
      }
   }
}

static void compare_components(stbcc_grid *grid, const unsigned char *map, int *component)
{
   int width = 1 << STBCC_GRID_COUNT_X_LOG2;
   int height = 1 << STBCC_GRID_COUNT_Y_LOG2;
   int x1, y1, x2, y2, index1, index2, expected;

   reference_components(map, component);
   for (y1 = 0; y1 < height; ++y1) {
      for (x1 = 0; x1 < width; ++x1) {
         index1 = y1 * width + x1;
         for (y2 = 0; y2 < height; ++y2) {
            for (x2 = 0; x2 < width; ++x2) {
               index2 = y2 * width + x2;
               expected = component[index1] >= 0 && component[index1] == component[index2];
               assert(stbcc_query_grid_node_connection(grid, x1, y1, x2, y2) == expected);
            }
         }
      }
   }
}

int main(void)
{
   int width = 1 << STBCC_GRID_COUNT_X_LOG2;
   int height = 1 << STBCC_GRID_COUNT_Y_LOG2;
   unsigned char map[(1 << STBCC_GRID_COUNT_X_LOG2) * (1 << STBCC_GRID_COUNT_Y_LOG2)];
   int component[(1 << STBCC_GRID_COUNT_X_LOG2) * (1 << STBCC_GRID_COUNT_Y_LOG2)];
   stbcc_grid *grid;
   int i, update_index;

   grid = (stbcc_grid *) malloc(stbcc_grid_sizeof());
   assert(grid != NULL);

   for (i = 0; i < 32; ++i) {
      int j;
      for (j = 0; j < width * height; ++j)
         map[j] = (test_random() & 3) ? 255 : 0;
      map[0] = 0;

      stbcc_init_grid(grid, map, width, height);
      compare_components(grid, map, component);

      for (j = 0; j < 16; ++j) {
         update_index = test_random() % (width * height);
         map[update_index] = map[update_index] ? 0 : 255;
         stbcc_update_grid(grid, update_index % width, update_index / width, map[update_index] != 0);
         compare_components(grid, map, component);
      }
   }

   free(grid);
   return 0;
}
