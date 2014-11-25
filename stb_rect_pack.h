// stb_rect_pack.h - v0.01 - public domain - rectangle packing
//
// Useful for e.g. packing rectangular textures into an atlas.
//
// By Sean Barrett and Ryan Gordon
//
// This library currently uses the Skyline Bottom-Left algorithm.
//
// Please note: better rectangle packers are welcome! Please
// implement them to the same API, but with a different init
// function. Contact me for details of how to set up the
// heuristic enums and suchlike (as the code currently isn't
// designed to do that correctly internally).
//

#ifndef STB_INCLUDE_STB_RECT_PACK_H
#define STB_INCLUDE_STB_RECT_PACK_H

#ifdef STBRP_STATIC
#define STBRP_DEF static
#else
#define STBRP_DEF extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stbrp_context stbrp_context;
typedef struct stbrp_node    stbrp_node;
typedef struct stbrp_rect    stbrp_rect;

enum
{
   STBRP_HEURISTIC_Skyline_default=0,
   STBRP_HEURISTIC_Skyline_BL_sortHeight = STBRP_HEURISTIC_Skyline_default,
   STBRP_HEURISTIC_Skyline_BF_sortHeight,
};

STBRP_DEF void stbrp_init_packer  (stbrp_context *context, int width, int height, stbrp_node *nodes, int num_nodes);
STBRP_DEF void stbrp_allow_oom    (stbrp_context *context, int allow_out_of_mem);
STBRP_DEF void stbrp_set_heuristic(stbrp_context *context, int heuristic);
STBRP_DEF void stbrp_pack_rects   (stbrp_context *context, stbrp_rect *rects, int num_rects);

struct stbrp_rect
{
   // reserved for your use:
   int            id;

   // input:
   unsigned short w, h;

   // output:
   unsigned short x, y;
   int            was_packed;  // non-zero if valid packing
}; // 16 bytes, nominally

// the details of the following structures don't matter to you, but they must
// be visible so you can manage the memory allocations for them
struct stbrp_node
{
   unsigned short x,y;
   stbrp_node *next;
};

struct stbrp_context
{
   int width;
   int height;
   int align;
   int init_mode;
   int heuristic;
   int num_nodes;
   stbrp_node *active_head;
   stbrp_node *free_head;
   stbrp_node extra[2]; // we allocate two extra nodes so user only needs to create 'width' for correctness, not width+1
};

#ifdef __cplusplus
}
#endif

#endif



#ifdef STB_RECT_PACK_IMPLEMENTATION
#include <stdlib.h>

enum
{
   STBRP__INIT_skyline = 1,
};

STBRP_DEF void stbrp_set_heuristic(stbrp_context *context, int heuristic)
{
   switch (context->init_mode) {
      case STBRP__INIT_skyline:
         assert(heuristic == STBRP_HEURISTIC_Skyline_BL_sortHeight || heuristic == STBRP_HEURISTIC_Skyline_BF_sortHeight);
         break;
      default:
         assert(0);
   }
}

STBRP_DEF void stbrp_allow_oom(stbrp_context *context, int allow_out_of_mem)
{
   if (allow_out_of_mem)
      // if it's ok to run out of memory, then don't bother aligning them;
      // this gives better packing, but may fail due to OOM (even though
      // the rectangles easily fit). @TODO a smarter approach would be to only
      // quantize once we've hit OOM, then we could get rid of this parameter.
      context->align = 1;
   else {
      // if it's not ok to run out of memory, then quantize the widths
      // so that num_nodes is always enough nodes.
      //
      // I.e. num_nodes * align >= width
      //                  align >= width / num_nodes
      //                  align = ceil(width/num_nodes)

      context->align = (context->width + context->num_nodes-1) / context->num_nodes;
   }
}

STBRP_DEF void stbrp_init_packer(stbrp_context *context, int width, int height, stbrp_node *nodes, int num_nodes)
{
   int i;
   for (i=0; i < num_nodes-1; ++i)
      nodes[i].next = &nodes[i+1];
   nodes[i].next = NULL;
   context->init_mode = STBRP__INIT_skyline;
   context->heuristic = STBRP_HEURISTIC_Skyline_default;
   context->free_head = &nodes[0];
   context->active_head = &context->extra[0];
   context->width = width;
   context->num_nodes = num_nodes;
   stbrp_allow_oom(context, 0);

   // node 0 is the full width, node 1 is the sentinel (lets us not store width explicitly)
   context->extra[0].x = 0;
   context->extra[0].y = 0;
   context->extra[0].next = &context->extra[1];
   context->extra[1].x = width;
   context->extra[1].y = 65535;
   context->extra[2].next = NULL;
}

// find minimum y position if it starts at x1
static int stbrp__skyline_find_min_y(stbrp_context *c, stbrp_node *first, int x0, int width, int *pwaste)
{
   stbrp_node *node = first;
   int x1 = x0 + width;
   int min_y, visited_width, waste_area;
   assert(first->x <= x0);

   #if 0
   // skip in case we're past the node
   while (node->next->x <= x0)
      ++node;
   #else
   assert(node->next->x > x0); // we ended up handling this in the caller for efficiency
   #endif

   assert(node->x <= x0);

   min_y = 0;
   waste_area = 0;
   visited_width = 0;
   while (node->x <= x1) {
      if (node->y > min_y) {
         // raise min_y higher.
         // we've accounted for all waste up to min_y,
         // but we'll now ad more waste for everything we've visted
         waste_area += visited_width * (node->y - min_y);
         min_y = node->y;
      } else {
         // add waste area
         int under_width = node->next->x - node->x;
         if (under_width + visited_width > width)
            under_width = width - visited_width;
         waste_area += under_width * (min_y - node->y);
      }
      visited_width += node->next->x - node->x; // adds too much the last time, but that's never used
      node = node->next;
   }

   *pwaste = waste_area;
   return min_y;
}

typedef struct
{
   int x,y;
   stbrp_node **prev_link;
} stbrp__findresult;

#define STBRP__HUGE_Y  (1<<30)

static stbrp__findresult stbrp__skyline_find_best_pos(stbrp_context *c, int width, int height)
{
   int best_waste = (1<<30), best_x, best_y = STBRP__HUGE_Y;
   stbrp__findresult fr;
   stbrp_node **prev, *node, *tail, **best = NULL;

   // align to multiple of c->align
   width = (width + c->align - 1);
   width -= width % c->align;
   assert(width % c->align == 0);

   node = c->active_head;
   prev = &c->active_head;
   while (node->x + width < c->width) {
      int y,waste;
      y = stbrp__skyline_find_min_y(c, node, node->x, width, &waste);
      if (c->heuristic == STBRP_HEURISTIC_Skyline_BL_sortHeight) { // actually just want to test BL
         // bottom left
         if (y < best_y) {
            best_y = y;
            best = prev;
         }
      } else {
         // best-fit
         if (waste < best_waste) {
            // can only use it if it first vertically
            if (y + height <= c->height) {
               best_y = y;
               best_waste = waste;
               best = prev;
            }
         }
      }
      prev = &node->next;
      node = node->next;
   }

   best_x = (best == NULL) ? 0 : (*best)->x;

   // if doing best-fit (BF), we also have to try aligning right edge to each node position
   //
   // e.g, if fitting
   //
   //     ____________________
   //    |____________________|
   //
   //            into
   //
   //   |                         |
   //   |             ____________|
   //   |____________|
   //
   // then right-aligned reduces waste, but bottom-left BL is always chooses left-aligned
   //
   // This makes BF take about 2x the time

   if (c->heuristic == STBRP_HEURISTIC_Skyline_BF_sortHeight) {
      tail = c->active_head;
      node = c->active_head;
      prev = &c->active_head;
      // find first node that's admissible
      while (tail->x < width)
         tail = tail->next;
      while (tail->x <= c->width) {
         int xpos = tail->x - width;
         int y,waste;
         assert(xpos >= 0);
         // find the left position that matches this
         while (node->next->x <= xpos) {
            prev = &node;
            node = node->next;
         }
         assert(node->next->x > xpos && node->x <= xpos);
         y = stbrp__skyline_find_min_y(c, node, xpos, width, &waste);
         if (waste <= best_waste && y + height < c->height) {
            if (waste < best_waste || y < best_y || (y==best_y && xpos < best_x)) {
               best_x = xpos;
               best_y = y;
               best_waste = waste;
               best = prev;
            }
         }
         tail = tail->next;
      }         
   }

   fr.prev_link = prev;
   fr.x = best_x;
   fr.y = best_y;
   return fr;
}

static stbrp__findresult stbrp__skyline_pack_rectangle(stbrp_context *context, int width, int height)
{
   // find best position according to heuristic
   stbrp__findresult res = stbrp__skyline_find_best_pos(context, width, height);
   stbrp_node *node, *cur;

   // bail if:
   //    1. it failed
   //    2. the best node doesn't fit (we don't always check this)
   //    3. we're out of memory
   if (res.prev_link == NULL || res.y + height > context->height || context->free_head == NULL) {
      res.prev_link = NULL;
      return res;
   }

   // on success, create new node
   node = context->free_head;
   node->x = res.x;
   node->y = res.y + height;

   context->free_head = node->next;

   // insert the new node into the right starting point, and
   // let 'cur' point to the remaining nodes needing to be
   // stiched back in

   cur = *res.prev_link;
   if (cur->x < res.x) {
      // preserve the existing one, so start testing with the next one
      stbrp_node *next = cur->next;
      cur->next = node;
      cur = next;
   } else {
      *res.prev_link = node;
   }

   // from here, traverse cur and free nodes, until we get to one
   // that shouldn't be freed
   while (cur->next->x <= res.x + width) {
      stbrp_node *next = cur->next;
      // move the current node to the free list
      cur->next = context->free_head;
      context->free_head = cur->next;
      cur = next;
   }

   // stich the list back in
   node->next = cur;

   if (cur->x < res.x + width)
      cur->x = res.x+width;

#ifdef _DEBUG
   cur = context->active_head;
   while (cur->x < context->width) {
      assert(cur->x < cur->next->x);
      cur = cur->next;
   }
   assert(cur->next == NULL);
#endif

   return res;
}

static int rect_height_compare(const void *a, const void *b)
{
   stbrp_rect *p = (stbrp_rect *) a;
   stbrp_rect *q = (stbrp_rect *) b;
   if (p->h > q->h)
      return -1;
   if (p->h < q->h)
      return  1;
   return (p->w > q->w) ? -1 : (p->w < q->w);
}

static int rect_original_order(const void *a, const void *b)
{
   stbrp_rect *p = (stbrp_rect *) a;
   stbrp_rect *q = (stbrp_rect *) b;
   return (p->was_packed < q->was_packed) ? -1 : (p->was_packed > q->was_packed);
}

STBRP_DEF void stbrp_pack_rects(stbrp_context *context, stbrp_rect *rects, int num_rects)
{
   int i;

   // we use the 'was_packed' field internally to allow sorting/unsorting
   for (i=0; i < num_rects; ++i)
      rects[i].was_packed = i;

   // sort according to heuristic
   qsort(rects, num_rects, sizeof(rects[0]), rect_height_compare);

   for (i=0; i < num_rects; ++i) {
      stbrp__findresult fr = stbrp__skyline_pack_rectangle(context, rects[i].w, rects[i].h);
      if (fr.prev_link) {
         rects[i].x = (unsigned short) fr.x;
         rects[i].y = (unsigned short) fr.y;
      } else {
         rects[i].x = rects[i].y = 0xffff;
      }
   }

   // unsort
   qsort(rects, num_rects, sizeof(rects[0]), rect_original_order);

   // set was_packed flags
   for (i=0; i < num_rects; ++i)
      rects[i].was_packed = !(rects[i].x == 0xffff && rects[i].y == 0xffff);
}
#endif
