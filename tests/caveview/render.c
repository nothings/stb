// @TODO
//   Thread usage is probably pretty terrible; need to make a
//   separate queue of needed chunks, instead of just generating
//   one request per thread per frame. (If it takes 1.5 frames
//   to build mesh, thread is idle for 0.5 frames.) Could achieve
//   similar effect by just bumping number of threads, but this
//   might slow down main thread.

// Q: How accurate is this as a Minecraft viewer?
//
// A: Not very. Many Minecraft blocks are not handled correctly:
//
//      No signs, doors, redstone, rails, carpets, or other "flat" blocks
//      Only one wood type
//      Colored glass becomes regular glass
//      Glass panes become glass blocks
//      Stairs are turned into ramps
//      Upper slabs turn into lower slabs
//      Water level is incorrect
//      No biome coloration
//      Cactus is not shrunk, shows holes
//      Chests are not shrunk
//      Chests, pumpkins, etc. are not rotated properly
//      Torches do not attach to walls
//      Incorrect textures for blocks that postdate terrain.png
//      Transparent textures have black fringes due to non-premultiplied-alpha
//      If a 32x32x256 "quad-chunk" needs more than 300K quads, isn't handled
//      Only blocks at y=1..255 are shown (not y=0)
//
//    Some of these are due to engine limitations, and some of
//    these are because I didn't make the effort since my
//    goal was to make a demo for stb_voxel_render.h, not
//    to make a proper Minecraft viewer.
//
//
// Q: Could this be turned into a proper Minecraft viewer?
//
// A: Yes and no. Yes, you could do it, but no, it wouldn't
//    really resemble this code that much anymore.
//
//    You could certainly use this engine to
//    render the parts of Minecraft it works for, but many
//    of the things it doesn't handle it can't handle at all
//    (stairs, water, fences, carpets, etc) because it uses
//    low-precision coordinates to store voxel data.
//
//    You would have to render all of the stuff it doesn't
//    handle through another rendering path. In a game (not
//    a viewer) you would need such a path for movable entities
//    like doors and carts anyway, so possibly handling other
//    things that way wouldn't be so bad.
//
//    Rails, ladders, and redstone lines could be implemented by
//    using tex2 to overlay those effects, but you can't rotate
//    tex1 and tex2 independently, so you'd have to have a
//    separate texture for each orientation of rail, etc, and
//    you'd need special rendering for rail up/down sections.
//
//    You can use the face-color effect to do biome coloration,
//    but the change won't be smooth the way it is in Minecraft.
//
//
// Q: Why isn't building the mesh data faster?
//
// A: Partly because converting from minecraft data is expensive.
//
//    Here is the approximate breakdown of an older version
//    of this executable and lib that did the building single-threaded,
//    and was a bit slower at building mesh data.
//
//    25%   loading & parsing minecraft files (4/5ths of this is zlib)
//    18%   converting from minecraft blockids & lighting to stb blockids & lighting
//    10%   reordering from data[z][y][x] (minecraft-style) to data[y][x][z] (stb-style)
//    40%   building mesh data
//     7%   uploading mesh data to OpenGL
//
//    I did do significant optimizations after the above, so the
//    final breakdown is different, but it should give you some
//    sense of the costs.


#define STB_VOXEL_RENDER_IMPLEMENTATION
#define STBVOX_ROTATION_IN_LIGHTING
#include "stb_voxel_render.h"

#define STB_GLEXT_DECLARE "glext_list.h"
#include "stb_gl.h"
#include "stb_image.h"
#include "stb_glprog.h"

#include "cave_parse.h"
#include "stb.h"
#include "sdl.h"
#include "sdl_thread.h"
#include <math.h>

extern void ods(char *fmt, ...);

#define FANCY_LEAVES  // nearly 2x the triangles when enabled (if underground is filled)
#define FAST_CHUNK
#define IN_PLACE

//#define SHORTVIEW

#define SKIP_TERRAIN   0 // must be a multiple of 16; doesn't build some underground stuff

GLuint main_prog;
GLint uniform_locations[64];

//#define MAX_QUADS_PER_DRAW        (65536 / 4) // assuming 16-bit indices, 4 verts per quad
//#define FIXED_INDEX_BUFFER_SIZE   (MAX_QUADS_PER_DRAW * 6 * 2)  // 16*1024 * 12 == ~192KB

// while uploading texture data, this holds our each texture
#define TEX_SIZE  64
uint32 texture[TEX_SIZE][TEX_SIZE];

GLuint voxel_tex[2];

enum
{
   C_empty,
   C_solid,
   C_trans,
   C_cross,
   C_water,
   C_slab,
   C_stair,
   C_force,
};

unsigned char geom_map[] =
{
   STBVOX_GEOM_empty,
   STBVOX_GEOM_solid,
   STBVOX_GEOM_transp,
   STBVOX_GEOM_crossed_pair,
   STBVOX_GEOM_solid,
   STBVOX_GEOM_slab_lower,
   STBVOX_GEOM_floor_slope_north_is_top,
   STBVOX_GEOM_force,
};

unsigned char minecraft_info[256][7] =
{
   { C_empty, 0,0,0,0,0,0 },
   { C_solid, 1,1,1,1,1,1 },
   { C_solid, 3,3,3,3,40,2 },
   { C_solid, 2,2,2,2,2,2 },
   { C_solid, 16,16,16,16,16,16 },
   { C_solid, 4,4,4,4,4,4 },
   { C_cross, 15,15,15,15 },
   { C_solid, 17,17,17,17,17,17 },

   // 8
   { C_water, 223,223,223,223,223,223 },
   { C_water, 223,223,223,223,223,223 },
   { C_solid, 255,255,255,255,255,255 },
   { C_solid, 255,255,255,255,255,255 },
   { C_solid, 18,18,18,18,18,18 },
   { C_solid, 19,19,19,19,19,19 },
   { C_solid, 32,32,32,32,32,32 },
   { C_solid, 33,33,33,33,33,33 },

   // 16
   { C_solid, 34,34,34,34,34,34 },
   { C_solid, 20,20,20,20,21,21 },
#ifdef FANCY_LEAVES
   { C_force, 52,52,52,52,52,52 }, // leaves
#else
   { C_solid, 53,53,53,53,53,53 }, // leaves
#endif
   { C_solid, 24,24,24,24,24,24 },
   { C_trans, 49,49,49,49,49,49 }, // glass
   { C_solid, 160,160,160,160,160,160 },
   { C_solid, 144,144,144,144,144,144 },
   { C_solid, 46,45,45,45,62,62 },

   // 24
   { C_solid, 192,192,192,192, 176,176 },
   { C_solid, 74,74,74,74,74,74 },
   { C_empty }, // bed
   { C_empty }, // powered rail
   { C_empty }, // detector rail
   { C_solid, 106,108,109,108,108,108 },
   { C_empty }, // cobweb=11
   { C_cross, 39,39,39,39 },

   // 32
   { C_cross, 55,55,55,55,0,0 },
   { C_solid, 107,108,109,108,108,108 },
   { C_empty }, // piston head
   { C_solid, 64,64,64,64,64,64 }, // various colors
   { C_empty }, // unused
   { C_cross, 13,13,13,13,0,0 },
   { C_cross, 12,12,12,12,0,0 },
   { C_cross, 29,29,29,29,0,0 },

   // 40
   { C_cross, 28,28,28,28,0,0 },
   { C_solid, 23,23,23,23,23,23 },
   { C_solid, 22,22,22,22,22,22 },
   { C_solid, 5,5,5,5,6,6, },
   { C_slab , 5,5,5,5,6,6, },
   { C_solid, 7,7,7,7,7,7, },
   { C_solid, 8,8,8,8,9,10 },
   { C_solid, 35,35,35,35,4,4, },

   // 48
   { C_solid, 36,36,36,36,36,36 },
   { C_solid, 37,37,37,37,37,37 },
   { C_cross, 80,80,80,80,80,80 }, // torch
   { C_empty }, // fire
   { C_trans, 65,65,65,65,65,65 },
   { C_stair, 4,4,4,4,4,4 },
   { C_solid, 27,26,26,26,25,25 },
   { C_empty }, // redstone

   // 56
   { C_solid, 50,50,50,50,50,50 },
   { C_solid, 26,26,26,26,26,26 },
   { C_solid, 60,59,59,59,43,43 },
   { C_cross, 95,95,95,95 },
   { C_solid, 2,2,2,2,86,2 },
   { C_solid, 44,45,45,45,62,62 },
   { C_solid, 61,45,45,45,62,62 },
   { C_empty }, // sign

   // 64
   { C_empty }, // door
   { C_empty }, // ladder
   { C_empty }, // rail
   { C_stair, 16,16,16,16,16,16 }, // cobblestone stairs
   { C_empty }, // sign
   { C_empty }, // lever
   { C_empty }, // stone pressure plate
   { C_empty }, // iron door

   // 72
   { C_empty }, // wooden pressure
   { C_solid, 51,51,51,51,51,51 },
   { C_solid, 51,51,51,51,51,51 },
   { C_empty },
   { C_empty },
   { C_empty },
   { C_empty }, // snow on block below, do as half slab?
   { C_solid, 67,67,67,67,67,67 },

   // 80
   { C_solid, 66,66,66,66,66,66 },
   { C_solid, 70,70,70,70,69,71 },
   { C_solid, 72,72,72,72,72,72 },
   { C_cross, 73,73,73,73,73,73 },
   { C_solid, 74,74,74,74,75,74 },
   { C_empty }, // fence
   { C_solid,119,118,118,118,102,102 },
   { C_solid,103,103,103,103,103,103 },

   // 88
   { C_solid, 104,104,104,104,104,104 },
   { C_solid, 105,105,105,105,105,105 },
   { C_solid, 167,167,167,167,167,167 },
   { C_solid, 120,118,118,118,102,102 },
   { C_empty }, // cake
   { C_empty }, // repeater
   { C_empty }, // repeater
   { C_solid, 49,49,49,49,49,49 }, // colored glass

   // 96
   { C_empty },
   { C_empty },
   { C_solid, 54,54,54,54,54,54 },
   { C_solid, 125,125,125,125,125,125 },
   { C_solid, 124,124,124,124,124,124 },
   { C_empty }, // bars
   { C_trans, 49,49,49,49,49,49 }, // glass pane
   { C_solid, 136,136,136,136,137,137 }, // melon

   // 104
   { C_empty }, // pumpkin stem
   { C_empty }, // melon stem
   { C_empty }, // vines
   { C_empty }, // gate
   { C_stair, 7,7,7,7,7,7, }, // brick stairs
   { C_stair, 54,54,54,54,54,54 }, // stone brick stairs
   { C_empty }, // mycelium
   { C_empty }, // lily pad

   // 112
   { C_solid, 224,224,224,224,224,224 },
   { C_empty }, // nether brick fence
   { C_stair, 224,224,224,224,224,224 }, // nether brick stairs
   { C_empty }, // nether wart
   { C_solid, 182,182,182,182,166,183 },
   { C_empty }, // brewing stand
   { C_empty }, // cauldron
   { C_empty }, // end portal

   // 120
   { C_solid, 159,159,159,159,158,158 },
   { C_solid, 175,175,175,175,175,175 },
   { C_empty }, // dragon egg
   { C_solid, 211,211,211,211,211,211 },
   { C_solid, 212,212,212,212,212,212 },
   { C_solid, 4,4,4,4,4,4, }, // wood double-slab
   { C_slab , 4,4,4,4,4,4, }, // wood slab
   { C_empty }, // cocoa

   // 128
   { C_solid, 192,192,192,192,176,176 }, // sandstone stairs
   { C_solid, 32,32,32,32,32,32 }, // emerald ore
   { C_empty }, // ender chest
   { C_empty },
   { C_empty },
   { C_solid, 23,23,23,23,23,23 }, // emerald block
   { C_solid, 198,198,198,198,198,198 }, // spruce stairs
   { C_solid, 214,214,214,214,214,214 }, // birch stairs

   // 136
   { C_stair, 199,199,199,199,199,199 }, // jungle stairs
   { C_empty }, // command block
   { C_empty }, // beacon
   { C_slab, 16,16,16,16,16,16 }, // cobblestone wall
   { C_empty }, // flower pot
   { C_empty }, // carrot
   { C_empty }, // potatoes
   { C_empty }, // wooden button

   // 144
   { C_empty }, // mob head
   { C_empty }, // anvil
   { C_solid, 27,26,26,26,25,25 }, // trapped chest
   { C_empty }, // weighted pressure plate light
   { C_empty }, // weighted pressure plat eheavy
   { C_empty }, // comparator inactive
   { C_empty }, // comparator active
   { C_empty }, // daylight sensor

   // 152
   { C_solid, 135,135,135,135,135,135 }, // redstone block
   { C_solid, 0,0,0,0,0,0, }, // nether quartz ore
   { C_empty }, // hopper
   { C_solid, 22,22,22,22,22,22 }, // quartz block
   { C_stair, 22,22,22,22,22,22 }, // quartz stairs
   { C_empty }, // activator rail
   { C_solid, 46,45,45,45,62,62 }, // dropper
   { C_solid, 72,72,72,72,72,72 }, // stained clay

   // 160
   { C_trans, 49,49,49,49,49,49 }, // stained glass pane
   #ifdef FANCY_LEAVES
   { C_force, 52,52,52,52,52,52 }, // leaves
   #else
   { C_solid, 53,53,53,53,53,53 }, // acacia leaves
   #endif
   { C_solid, 20,20,20,20,21,21 }, // acacia tree
   { C_solid, 199,199,199,199,199,199 }, // acacia wood stairs
   { C_solid, 198,198,198,198,198,198 }, // dark oak stairs
   { C_solid, 146,146,146,146,146,146 }, // slime block

   { C_solid, 176,176,176,176,176,176 }, // red sandstone
   { C_solid, 176,176,176,176,176,176 }, // red sandstone

   // 168
   { C_empty },
   { C_empty },
   { C_empty },
   { C_empty },
   { C_solid, 72,72,72,72,72,72 }, // hardened clay
   { C_empty },
   { C_empty },
   { C_empty },

   // 176
   { C_empty },
   { C_empty },
   { C_solid, 176,176,176,176,176,176 }, // red sandstone
};

unsigned char minecraft_tex1_for_blocktype[256][6];
unsigned char minecraft_trans_for_blocktype[256];
unsigned char effective_blocktype[256];
unsigned char effective_block_add[256];
unsigned char minecraft_color_for_blocktype[256][6];
unsigned char minecraft_geom_for_blocktype[256];

void scale_texture(unsigned char *src, int x, int y, int w, int h)
{
   int i,j,k;
   assert(w == 256 && h == 256);
   for (j=0; j < TEX_SIZE; ++j) {
      for (i=0; i < TEX_SIZE; ++i) {
         uint32 val=0;
         for (k=0; k < 4; ++k) {
            val >>= 8;
            val += src[ 4*(x+(i>>2)) + 4*w*(y+(j>>2)) + k]<<24;
         }
         texture[j][i] = val;
      }
   }
}

void build_base_texture(int n)
{
   int x,y;
   uint32 color = stb_rand() | 0xff808080;
   for (y=0; y<TEX_SIZE; ++y)
      for (x=0; x<TEX_SIZE; ++x) {
         texture[y][x] = color + (stb_rand()&0x1f1f1f);
      }
}

void build_overlay_texture(int n)
{
   int x,y;
   uint32 color = stb_rand();
   if (color & 16)
      color = 0xff000000;
   else
      color = 0xffffffff;
   for (y=0; y<TEX_SIZE; ++y)
      for (x=0; x<TEX_SIZE; ++x) {
         texture[y][x] = 0;
      }

   for (y=0; y < TEX_SIZE/8; ++y) {
      for (x=0; x < TEX_SIZE; ++x) {
         texture[y][x] = color;
         texture[TEX_SIZE-1-y][x] = color;
         texture[x][y] = color;
         texture[x][TEX_SIZE-1-y] = color;
      }
   }
}

#define BUILD_BUFFER_SIZE  (4*4*600000*4)
#define FACE_BUFFER_SIZE   (  4*600000*4)

uint8 build_buffer[BUILD_BUFFER_SIZE];
uint8 face_buffer[FACE_BUFFER_SIZE];

//GLuint vbuf, fbuf, fbuf_tex;
stbvox_mesh_maker g_mesh_maker;

//unsigned char tex1_for_blocktype[256][6];

//unsigned char blocktype[34][34][257];
//unsigned char lighting[34][34][257];

// a superchunk is 64x64x256, with the border blocks computed as well,
// which means we need 4x4 chunks plus 16 border chunks plus 4 corner chunks

#define SUPERCHUNK_X   4
#define SUPERCHUNK_Y   4

unsigned char remap_data[16][16];
unsigned char remap[256];
unsigned char rotate_data[4] = { 1,3,2,0 };

void convert_fastchunk_inplace(fast_chunk *fc)
{
   int i;
   int num_blocks=0, step=0;
   unsigned char rot[4096] = { 0 };
   #ifndef IN_PLACE
   unsigned char *storage;
   #endif

   for (i=0; i < 16; ++i)
      num_blocks += fc->blockdata[i] != NULL;

   #ifndef IN_PLACE
   storage = malloc(16*16*16*2 * num_blocks);
   #endif

   for (i=0; i < 16; ++i) {
      if (fc->blockdata[i]) {
         int o=0;
         unsigned char *bd,*dd,*lt,*sky;
         unsigned char *out, *outb;

         // this ordering allows us to determine which data we can safely overwrite for in-place processing
         bd = fc->blockdata[i];
         dd = fc->data[i];
         lt = fc->light[i];
         sky = fc->skylight[i];

         #ifdef IN_PLACE
         assert(dd < sky && sky < lt && lt < bd);
         out = bd;
         outb = dd;
         #else
         out = storage + 16*16*16*2*step;
         outb = out + 16*16*16;
         ++step;
         #endif

         for (o=0; o < 16*16*16/2; o += 1) {
            unsigned char v1,v2;
            unsigned char d = dd[o];
            v1 = bd[o*2+0];
            v2 = bd[o*2+1];

            if (remap[v1])
            {
               //unsigned char d = bd[o] & 15;
               v1 = remap_data[remap[v1]][d&15];
               rot[o] = rotate_data[d&3];
            } else
               v1 = effective_blocktype[v1];

            if (remap[v2])
            {
               //unsigned char d = bd[o] >> 4;
               v2 = remap_data[remap[v2]][d>>4];
               rot[o+1] = rotate_data[(d>>4)&3];
            } else
               v2 = effective_blocktype[v2];

            out[o*2+0] = v1;
            out[o*2+1] = v2;
         }

         // because this stores to data[], can't run at same time as above loop
         for (o=0; o < 16*16*16/2; ++o) {
            int bright;
            bright = (lt[o]&15)*12 + 15 + (sky[o]&15)*16;
            if (bright > 255) bright = 255;
            if (bright <  32) bright =  32;
            outb[o*2+0] = STBVOX_MAKE_LIGHTING((unsigned char) bright, rot[o]);

            bright = (lt[o]>>4)*12 + 15 + (sky[o]>>4)*16;
            if (bright > 255) bright = 255;
            if (bright <  32) bright =  32;
            outb[o*2+1] = STBVOX_MAKE_LIGHTING((unsigned char) bright, rot[o+1]);
         }

         #ifndef IN_PLACE
         fc->blockdata[i] = out;
         fc->data[i] = outb;
         #endif
      }
   }

   #ifndef IN_PLACE
   free(fc->pointer_to_free);
   fc->pointer_to_free = storage;
   #endif
}

void make_converted_fastchunk(fast_chunk *fc, int x, int y, int segment, uint8 *sv_blocktype, uint8 *sv_lighting)
{
   int z;
   assert(fc == NULL || (fc->refcount > 0 && fc->refcount < 64));
   if (fc == NULL || fc->blockdata[segment] == NULL) {
      for (z=0; z < 16; ++z) {
         sv_blocktype[z] = C_empty;
         sv_lighting[z] = 255;
      }
   } else {
      unsigned char *block = fc->blockdata[segment];
      unsigned char *data  = fc->data[segment];
      y = 15-y;
      for (z=0; z < 16; ++z) {
         sv_blocktype[z] = block[z*256 + y*16 + x];
         sv_lighting [z] = data [z*256 + y*16 + x];
      }
   }
}


#define CHUNK_CACHE   64
typedef struct
{
   int valid;
   int chunk_x, chunk_y;
   fast_chunk *fc;
} cached_converted_chunk;

cached_converted_chunk chunk_cache[CHUNK_CACHE][CHUNK_CACHE];
int cache_size = CHUNK_CACHE;

void reset_cache_size(int size)
{
   int i,j;
   for (j=size; j < cache_size; ++j) {
      for (i=size; i < cache_size; ++i) {
         cached_converted_chunk *ccc = &chunk_cache[j][i];
         if (ccc->valid) {
            if (ccc->fc) {
               free(ccc->fc->pointer_to_free);
               free(ccc->fc);
               ccc->fc = NULL;
            }
            ccc->valid = 0;
         }
      }
   }
   cache_size = size;
}

void deref_fastchunk(fast_chunk *fc)
{
   if (fc) {
      assert(fc->refcount > 0);
      --fc->refcount;
      if (fc->refcount == 0) {
         free(fc->pointer_to_free);
         free(fc);
      }
   }
}

SDL_mutex * chunk_cache_mutex;
SDL_mutex * chunk_get_mutex;

void lock_chunk_get_mutex(void)
{
   SDL_LockMutex(chunk_get_mutex);
}
void unlock_chunk_get_mutex(void)
{
   SDL_UnlockMutex(chunk_get_mutex);
}

fast_chunk *get_converted_fastchunk(int chunk_x, int chunk_y)
{
   int slot_x = (chunk_x & (cache_size-1));
   int slot_y = (chunk_y & (cache_size-1));
   fast_chunk *fc;
   cached_converted_chunk *ccc;
   SDL_LockMutex(chunk_cache_mutex);
   ccc = &chunk_cache[slot_y][slot_x];
   if (ccc->valid) {
      if (ccc->chunk_x == chunk_x && ccc->chunk_y == chunk_y) {
         fast_chunk *fc = ccc->fc;
         if (fc)
            ++fc->refcount;
         SDL_UnlockMutex(chunk_cache_mutex);
         return fc;
      }
      if (ccc->fc) {
         deref_fastchunk(ccc->fc);
         ccc->fc = NULL;
         ccc->valid = 0;
      }
   }
   SDL_UnlockMutex(chunk_cache_mutex);

   fc = get_decoded_fastchunk_uncached(chunk_x, -chunk_y);
   if (fc)
      convert_fastchunk_inplace(fc);

   SDL_LockMutex(chunk_cache_mutex);
   // another thread might have updated it, so before we overwrite it...
   if (ccc->fc) {
      deref_fastchunk(ccc->fc);
      ccc->fc = NULL;
   }

   if (fc)
      fc->refcount = 1; // 1 in the cache

   ccc->chunk_x = chunk_x;
   ccc->chunk_y = chunk_y;
   ccc->valid = 1;
   if (fc)
      ++fc->refcount;
   ccc->fc = fc;
   SDL_UnlockMutex(chunk_cache_mutex);
   return fc;
}

void make_map_segment_for_superchunk_preconvert(int chunk_x, int chunk_y, int segment, fast_chunk *fc_table[4][4], uint8 sv_blocktype[34][34][18], uint8 sv_lighting[34][34][18])
{
   int a,b;
   assert((chunk_x & 1) == 0);
   assert((chunk_y & 1) == 0);
   for (b=-1; b < 3; ++b) {
      for (a=-1; a < 3; ++a) {
         int xo = a*16+1;
         int yo = b*16+1;
         int x,y;
         fast_chunk *fc = fc_table[b+1][a+1];
         for (y=0; y < 16; ++y)
            for (x=0; x < 16; ++x)
               if (xo+x >= 0 && xo+x < 34 && yo+y >= 0 && yo+y < 34)
                  make_converted_fastchunk(fc,x,y, segment, sv_blocktype[xo+x][yo+y], sv_lighting[xo+x][yo+y]);
      }
   }
}

enum
{
   STATE_invalid,
   STATE_needed,
   STATE_requested,
   STATE_abandoned,
   STATE_valid,
};

// mesh is 32x32x255 ... this is hardcoded in that
// a mesh covers 2x2 minecraft chunks, no #defines for it
typedef struct
{
   int state;
   int chunk_x, chunk_y;
   int num_quads;
   float priority;
   int vbuf_size, fbuf_size;

   float transform[3][3];
   float bounds[2][3];

   GLuint vbuf;// vbuf_tex;
   GLuint fbuf, fbuf_tex;

} chunk_mesh;

// view radius of about 1024 = 2048 columns / 32 columns-per-mesh = 2^11 / 2^5 = 64x64
// so we need bigger than 64x64 so we can precache, which means we have to be
// non-power-of-two, or we have to be pretty huge
#define CACHED_MESH_NUM_X   128
#define CACHED_MESH_NUM_Y   128


chunk_mesh cached_chunk_mesh[CACHED_MESH_NUM_Y][CACHED_MESH_NUM_X];

void free_chunk(int slot_x, int slot_y)
{
   chunk_mesh *cm = &cached_chunk_mesh[slot_y][slot_x];
   if (cm->state == STATE_valid) {
      glDeleteTextures(1, &cm->fbuf_tex);
      glDeleteBuffersARB(1, &cm->vbuf);
      glDeleteBuffersARB(1, &cm->fbuf);
      cached_chunk_mesh[slot_y][slot_x].state = STATE_invalid;
   }
}

void upload_mesh(chunk_mesh *cm, uint8 *build_buffer, uint8 *face_buffer)
{
   glGenBuffersARB(1, &cm->vbuf);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, cm->vbuf);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, cm->num_quads*4*sizeof(uint32), build_buffer, GL_STATIC_DRAW_ARB);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

   glGenBuffersARB(1, &cm->fbuf);
   glBindBufferARB(GL_TEXTURE_BUFFER_ARB, cm->fbuf);
   glBufferDataARB(GL_TEXTURE_BUFFER_ARB, cm->num_quads*sizeof(uint32), face_buffer , GL_STATIC_DRAW_ARB);
   glBindBufferARB(GL_TEXTURE_BUFFER_ARB, 0);

   glGenTextures(1, &cm->fbuf_tex);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, cm->fbuf_tex);
   glTexBufferARB(GL_TEXTURE_BUFFER_ARB, GL_RGBA8UI, cm->fbuf);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, 0);
}

GLuint unitex[64], unibuf[64];
void make_texture_buffer_for_uniform(int uniform, int slot)
{
   GLenum type;
   stbvox_uniform_info *ui = stbvox_get_uniform_info(&g_mesh_maker, uniform);
   GLint uloc = stbgl_find_uniform(main_prog, ui->name);

   if (uniform == STBVOX_UNIFORM_color_table)
      ((float *)ui->default_value)[63*4+3] = 1.0f; // emissive

   glGenBuffersARB(1, &unibuf[uniform]);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, unibuf[uniform]);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, ui->array_length * ui->bytes_per_element, ui->default_value, GL_STATIC_DRAW_ARB);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

   glGenTextures(1, &unitex[uniform]);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, unitex[uniform]);
   switch (ui->type) {
      case STBVOX_UNIFORM_TYPE_vec2: type = GL_RG32F; break;
      case STBVOX_UNIFORM_TYPE_vec3: type = GL_RGB32F; break;
      case STBVOX_UNIFORM_TYPE_vec4: type = GL_RGBA32F; break;
      default: assert(0);
   }
   glTexBufferARB(GL_TEXTURE_BUFFER_ARB, type, unibuf[uniform]);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, 0);

   glActiveTextureARB(GL_TEXTURE0 + slot);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, unitex[uniform]);
   glActiveTextureARB(GL_TEXTURE0);

   stbglUseProgram(main_prog);
   stbglUniform1i(uloc, slot);
}


typedef struct
{
   int cx,cy;

   stbvox_mesh_maker mm;

   uint8 *build_buffer;
   uint8 *face_buffer;

   int num_quads;
   float transform[3][3];
   float bounds[2][3];

   uint8 sv_blocktype[34][34][18];
   uint8 sv_lighting [34][34][18];
} raw_mesh;


void build_chunk(int chunk_x, int chunk_y, fast_chunk *fc_table[4][4], raw_mesh *rm)
{
   int a,b,z;
   stbvox_input_description *map;

   assert((chunk_x & 1) == 0);
   assert((chunk_y & 1) == 0);

   rm->cx = chunk_x;
   rm->cy = chunk_y;

   stbvox_set_input_stride(&rm->mm, 34*18, 18);

   assert(rm->mm.input.geometry == NULL);

   map = stbvox_get_input_description(&rm->mm);
   map->block_tex1_face = minecraft_tex1_for_blocktype;
   map->block_color_face = minecraft_color_for_blocktype;
   map->block_geometry = minecraft_geom_for_blocktype;
   stbvox_config_set_z_precision(&rm->mm, 1);

   // we're going to build 4 meshes in parallel, each covering 2x2 chunks
   stbvox_reset_buffers(&rm->mm);
   stbvox_set_buffer(&rm->mm, 0, 0, rm->build_buffer, BUILD_BUFFER_SIZE);
   stbvox_set_buffer(&rm->mm, 0, 1, rm->face_buffer , FACE_BUFFER_SIZE);

   map->blocktype = &rm->sv_blocktype[1][1][1]; // this is (0,0,0), but we need to be able to query off the edges
   map->lighting = &rm->sv_lighting[1][1][1];

   // fill in the top two rows of the buffer
   for (a=0; a < 34; ++a) {
      for (b=0; b < 34; ++b) {
         rm->sv_blocktype[a][b][16] = 0;
         rm->sv_lighting [a][b][16] = 255;
         rm->sv_blocktype[a][b][17] = 0;
         rm->sv_lighting [a][b][17] = 255;
      }
   }

   for (z=256-16; z >= SKIP_TERRAIN; z -= 16)
   {
      int z0 = z;
      int z1 = z+16;
      if (z1 == 256) z1 = 255;

      make_map_segment_for_superchunk_preconvert(chunk_x, chunk_y, z >> 4, fc_table, rm->sv_blocktype, rm->sv_lighting);

      map->blocktype = &rm->sv_blocktype[1][1][1-z]; // specify location of 0,0,0 so that accessing z0..z1 gets right data
      map->lighting = &rm->sv_lighting[1][1][1-z];

      {
         int cx = chunk_x;
         int cy = chunk_y;
         int slot_x = (cx >> 1) & (CACHED_MESH_NUM_X-1);
         int slot_y = (cy >> 1) & (CACHED_MESH_NUM_Y-1);
         chunk_mesh *cm;
         cm = &cached_chunk_mesh[slot_y][slot_x];

         stbvox_set_input_range(&rm->mm, 0,0,z0, 32,32,z1);
         stbvox_set_default_mesh(&rm->mm, 0);
         stbvox_make_mesh(&rm->mm);
      }

      // copy the bottom two rows of data up to the top
      for (a=0; a < 34; ++a) {
         for (b=0; b < 34; ++b) {
            rm->sv_blocktype[a][b][16] = rm->sv_blocktype[a][b][0];
            rm->sv_blocktype[a][b][17] = rm->sv_blocktype[a][b][1];
            rm->sv_lighting [a][b][16] = rm->sv_lighting [a][b][0];
            rm->sv_lighting [a][b][17] = rm->sv_lighting [a][b][1];
         }
      }
   }

   stbvox_set_mesh_coordinates(&rm->mm, chunk_x*16, chunk_y*16, 0);
   stbvox_get_transform(&rm->mm, rm->transform);

   stbvox_set_input_range(&rm->mm, 0,0,0, 32,32,255);
   stbvox_get_bounds(&rm->mm, rm->bounds);

   rm->num_quads = stbvox_get_quad_count(&rm->mm, 0);
}

static void upload_mesh_data(raw_mesh *rm)
{
   int cx = rm->cx;
   int cy = rm->cy;
   int slot_x = (cx >> 1) & (CACHED_MESH_NUM_X-1);
   int slot_y = (cy >> 1) & (CACHED_MESH_NUM_Y-1);
   chunk_mesh *cm;

   free_chunk(slot_x, slot_y);

   cm = &cached_chunk_mesh[slot_y][slot_x];
   cm->num_quads = rm->num_quads;

   upload_mesh(cm, rm->build_buffer, rm->face_buffer);
   cm->vbuf_size = rm->num_quads*4*sizeof(uint32);
   cm->fbuf_size = rm->num_quads*sizeof(uint32);
   cm->priority = 100000;
   cm->chunk_x = cx;
   cm->chunk_y = cy;

   memcpy(cm->bounds, rm->bounds, sizeof(cm->bounds));
   memcpy(cm->transform, rm->transform, sizeof(cm->transform));

   // write barrier here
   cm->state = STATE_valid;
}

GLint uniform_loc[16];
float table3[128][3];
GLint tablei[2];

void setup_uniforms(float pos[3])
{
   int i,j;
   for (i=0; i < STBVOX_UNIFORM__count; ++i) {
      stbvox_uniform_info *ui = stbvox_get_uniform_info(&g_mesh_maker, i);
      uniform_loc[i] = -1;

      if (i == STBVOX_UNIFORM_texscale || i == STBVOX_UNIFORM_texgen || i == STBVOX_UNIFORM_color_table)
         continue;

      if (ui) {
         void *data = ui->default_value;
         uniform_loc[i] = stbgl_find_uniform(main_prog, ui->name);
         switch (i) {
            case STBVOX_UNIFORM_face_data:
               tablei[0] = 2;
               data = tablei;
               break;

            case STBVOX_UNIFORM_tex_array:
               glActiveTextureARB(GL_TEXTURE0_ARB);
               glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, voxel_tex[0]);
               glActiveTextureARB(GL_TEXTURE1_ARB);
               glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, voxel_tex[1]);
               glActiveTextureARB(GL_TEXTURE0_ARB);
               tablei[0] = 0;
               tablei[1] = 1;
               data = tablei;
               break;

            case STBVOX_UNIFORM_color_table:
               data = ui->default_value;
               ((float *)data)[63*4+3] = 1.0f; // emissive
               break;

            case STBVOX_UNIFORM_camera_pos:
               data = table3[0];
               table3[0][0] = pos[0];
               table3[0][1] = pos[1];
               table3[0][2] = pos[2];
               break;

            case STBVOX_UNIFORM_ambient: {
               float amb[3][3];

               // ambient direction is sky-colored upwards
               // "ambient" lighting is from above
               table3[0][0] =  0.3f;
               table3[0][1] = -0.5f;
               table3[0][2] =  0.9f;

               amb[1][0] = 0.3f; amb[1][1] = 0.3f; amb[1][2] = 0.3f; // dark-grey
               amb[2][0] = 1.0; amb[2][1] = 1.0; amb[2][2] = 1.0; // white

               // convert so (table[1]*dot+table[2]) gives
               // above interpolation
               //     lerp((dot+1)/2, amb[1], amb[2])
               //     amb[1] + (amb[2] - amb[1]) * (dot+1)/2
               //     amb[1] + (amb[2] - amb[1]) * dot/2 + (amb[2]-amb[1])/2

               for (j=0; j < 3; ++j) {
                  table3[1][j] = (amb[2][j] - amb[1][j])/2;
                  table3[2][j] = (amb[1][j] + amb[2][j])/2;
               }

               // fog color
               table3[3][0] = 0.6f, table3[3][1] = 0.7f, table3[3][2] = 0.9f;
               // fog distance
               //table3[3][3] = 1200;

               data = table3;
               break;
            }
         }

         switch (ui->type) {
            case STBVOX_UNIFORM_TYPE_sampler: stbglUniform1iv(uniform_loc[i], ui->array_length, data); break;
            case STBVOX_UNIFORM_TYPE_vec2:    stbglUniform2fv(uniform_loc[i], ui->array_length, data); break;
            case STBVOX_UNIFORM_TYPE_vec3:    stbglUniform3fv(uniform_loc[i], ui->array_length, data); break;
            case STBVOX_UNIFORM_TYPE_vec4:    stbglUniform4fv(uniform_loc[i], ui->array_length, data); break;
         }
      }
   }
}

int next_blocktype = 255;

unsigned char mc_rot[4] = { 1,3,2,0 };

// create blocktypes with rotation baked into type
void build_stair_rotations(int blocktype, unsigned char *map)
{
   int i,j,k;
   for (j=0; j < 2; ++j) {
      int geom = j ? STBVOX_GEOM_ceil_slope_north_is_bottom : STBVOX_GEOM_floor_slope_north_is_top;
      for (i=0; i < 4; ++i) {
         if (i == 0 && j == 0) {
            map[j*4+i+8] = map[j*4+i] = blocktype;
            minecraft_geom_for_blocktype[blocktype] = (unsigned char) STBVOX_MAKE_GEOMETRY(geom, mc_rot[i], 0);
         } else {
            map[j*4+i+8] = map[j*4+i] = next_blocktype;

            for (k=0; k < 6; ++k) {
               minecraft_color_for_blocktype[next_blocktype][k] = minecraft_color_for_blocktype[blocktype][k];
               minecraft_tex1_for_blocktype [next_blocktype][k] = minecraft_tex1_for_blocktype [blocktype][k];
            }
            minecraft_geom_for_blocktype[next_blocktype] = (unsigned char) STBVOX_MAKE_GEOMETRY(geom, mc_rot[i], 0);
            --next_blocktype;
         }
      }
   }
}

void build_wool_variations(int bt, unsigned char *map)
{
   int i,k;
   unsigned char tex[16] = { 64, 210, 194, 178,  162, 146, 130, 114,  225, 209, 193, 177,  161, 145, 129, 113 };
   for (i=0; i < 16; ++i) {
      if (i == 0)
         map[i] = bt;
      else {
         map[i] = next_blocktype;
         for (k=0; k < 6; ++k) {
            minecraft_tex1_for_blocktype[next_blocktype][k] = tex[i];
            minecraft_color_for_blocktype[next_blocktype][k] = 0;
         }
         minecraft_geom_for_blocktype[next_blocktype] = minecraft_geom_for_blocktype[bt];
         --next_blocktype;
      }
   }
}

#define MAX_MESH_WORKERS  8
#define MAX_CHUNK_LOAD_WORKERS 2

int num_mesh_workers;
int num_chunk_load_workers;

typedef struct
{
   int state;
   int request_cx;
   int request_cy;
   int padding[13];

   SDL_sem * request_received;

   SDL_sem * chunk_server_done_processing;
   int chunk_action;
   int chunk_request_x;
   int chunk_request_y;
   fast_chunk *chunks[4][4];

   int padding2[16];
   raw_mesh rm;
   int padding3[16];

   uint8 *build_buffer;
   uint8 *face_buffer ;
} mesh_worker;

mesh_worker mesh_data[MAX_MESH_WORKERS];
int num_meshes_started;

int request_chunk(int chunk_x, int chunk_y);
void update_meshes_from_render_thread(void);

enum
{
   WSTATE_idle,
   WSTATE_requested,
   WSTATE_running,
   WSTATE_mesh_ready,
};

void render_init(void)
{
   int i,a,b;
   char *binds[] = { "attr_vertex", "attr_face", NULL };
   char vertex[5000];
   int vertex_len;
   char fragment[5000];
   int fragment_len;
   int w,h;

   unsigned char *texdata = stbi_load("terrain.png", &w, &h, NULL, 4);

   stbvox_init_mesh_maker(&g_mesh_maker);
   stbvox_config_use_gl(&g_mesh_maker, 1, 1, 1);
   for (i=0; i < num_mesh_workers; ++i) {
      stbvox_init_mesh_maker(&mesh_data[i].rm.mm);
      stbvox_config_use_gl(&mesh_data[i].rm.mm, 1,1,1);
   }

   vertex_len = stbvox_get_vertex_shader(&g_mesh_maker, vertex, sizeof(vertex));
   fragment_len = stbvox_get_fragment_shader(&g_mesh_maker, fragment, sizeof(fragment));

   if (vertex_len < 0) {
      ods("Vertex shader was too long!\n");
      assert(0);
      exit(1);
   }
   if (fragment_len < 0) {
      ods("fragment shader was too long!\n");
      assert(0);
      exit(1);
   }
   ods("Shader lengths: %d %d\n", vertex_len, fragment_len);

   {
      char error_buffer[1024];
      char *main_vertex[] = { vertex, NULL };
      char *main_fragment[] = { fragment, NULL };
      main_prog = stbgl_create_program(main_vertex, main_fragment, binds, error_buffer, sizeof(error_buffer));
      if (main_prog == 0) {
         ods("Compile error for main shader: %s\n", error_buffer);
         assert(0);
         exit(1);
      }
      //stbgl_find_uniforms(main_prog, uniform_locations, uniforms, -1);
   }
   //init_index_buffer();

   make_texture_buffer_for_uniform(STBVOX_UNIFORM_texscale     , 3);
   make_texture_buffer_for_uniform(STBVOX_UNIFORM_texgen       , 4);
   make_texture_buffer_for_uniform(STBVOX_UNIFORM_color_table  , 5);

   glGenTextures(2, voxel_tex);

   glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, voxel_tex[0]);
   glTexImage3DEXT(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_RGBA,
                      TEX_SIZE,TEX_SIZE,256,
                      0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
   for (i=0; i < 256; ++i) {
      if (texdata)
         scale_texture(texdata, (i&15)*w/16, (h/16)*(i>>4), w,h);
      else
         build_base_texture(i);
      glTexSubImage3DEXT(GL_TEXTURE_2D_ARRAY_EXT, 0, 0,0,i, TEX_SIZE,TEX_SIZE,1, GL_RGBA, GL_UNSIGNED_BYTE, texture[0]);
   }
   glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

   glGenerateMipmapEXT(GL_TEXTURE_2D_ARRAY_EXT);

   glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, voxel_tex[1]);
   glTexImage3DEXT(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_RGBA,
                      TEX_SIZE,TEX_SIZE,128,
                      0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
   for (i=0; i < 128; ++i) {
      build_overlay_texture(i);
      glTexSubImage3DEXT(GL_TEXTURE_2D_ARRAY_EXT, 0, 0,0,i, TEX_SIZE,TEX_SIZE,1, GL_RGBA, GL_UNSIGNED_BYTE, texture[0]);
   }
   glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmapEXT(GL_TEXTURE_2D_ARRAY_EXT);

   for (i=0; i < 256; ++i) {
      memcpy(minecraft_tex1_for_blocktype[i], minecraft_info[i]+1, 6);
      minecraft_trans_for_blocktype[i] = (minecraft_info[i][0] != C_solid && minecraft_info[i][0] != C_water);
      effective_blocktype[i] = (minecraft_info[i][0] == C_empty ? 0 : i);
      minecraft_geom_for_blocktype[i] = geom_map[minecraft_info[i][0]];
   }
   //effective_blocktype[50] = 0; // delete torches

   for (i=0; i < 6*256; ++i) {
      if (minecraft_tex1_for_blocktype[0][i] == 40)
         minecraft_color_for_blocktype[0][i] = 38 | 64; // apply to tex1
      if (minecraft_tex1_for_blocktype[0][i] == 39)
         minecraft_color_for_blocktype[0][i] = 39 | 64; // apply to tex1
      if (minecraft_tex1_for_blocktype[0][i] == 105)
         minecraft_color_for_blocktype[0][i] = 63; // emissive
      if (minecraft_tex1_for_blocktype[0][i] == 212)
         minecraft_color_for_blocktype[0][i] = 63; // emissive
      if (minecraft_tex1_for_blocktype[0][i] == 80)
         minecraft_color_for_blocktype[0][i] = 63; // emissive
   }

   for (i=0; i < 6; ++i) {
      minecraft_color_for_blocktype[172][i] = 47 | 64; // apply to tex1
      minecraft_color_for_blocktype[178][i] = 47 | 64; // apply to tex1
      minecraft_color_for_blocktype[18][i] = 39 | 64; // green
      minecraft_color_for_blocktype[161][i] = 37 | 64; // green
      minecraft_color_for_blocktype[10][i] = 63; // emissive lava
      minecraft_color_for_blocktype[11][i] = 63; // emissive
   }

   remap[53] = 1;
   remap[67] = 2;
   remap[108] = 3;
   remap[109] = 4;
   remap[114] = 5;
   remap[136] = 6;
   remap[156] = 7;
   for (i=0; i < 256; ++i)
      if (remap[i])
         build_stair_rotations(i, remap_data[remap[i]]);
   remap[35]  = 8;
   build_wool_variations(35, remap_data[remap[35]]);

   for (i=0; i < 256; ++i) {
      if (remap[i])
         effective_block_add[i] = 0;
      else
         effective_block_add[i] = effective_blocktype[i];
   }

   //build_test_object();
   //build_chunk(0,0);
   {

      // 32..-32, 32..-32, !FILL_TERRAIN, !FANCY_LEAVES
      // 6.27s  - reblocked to do 16 z at a time instead of 256 (still using 66x66x258), 4 meshes in parallel
      // 5.96s  - reblocked to use FAST_CHUNK (no intermediate data structure)
      // 5.45s  - unknown change, or previous measurement was wrong

      // 6.12s  - use preconverted data, not in-place
      // 5.91s  - use preconverted, in-place
      // 5.34s  - preconvert, in-place, avoid dependency chain (suggested by ryg)
      // 5.34s  - preconvert, in-place, avoid dependency chain, use bit-table instead of byte-table
      // 5.50s  - preconvert, in-place, branchless

      // 6.42s  - non-preconvert, avoid dependency chain (not an error)
      // 5.40s  - non-preconvert, w/dependency chain (same as earlier)

      // 5.50s  - non-FAST_CHUNK, reblocked outer loop for better cache reuse
      // 4.73s  - FAST_CHUNK non-preconvert, reblocked outer loop
      // 4.25s  - preconvert, in-place, reblocked outer loop
      // 4.18s  - preconvert, in-place, unrolled again
      // 4.10s  - 34x34 1 mesh instead of 66x66 and 4 meshes (will make it easier to do multiple threads)

      // 4.83s  - building bitmasks but not using them (2 bits per block, one if empty, one if solid)

      // 5.16s  - using empty bitmasks to early out
      // 5.01s  - using solid & empty bitmasks to early out - "foo"
      // 4.64s  - empty bitmask only, test 8 at a time, then test geom
      // 4.72s  - empty bitmask only, 8 at a time, then test bits
      // 4.46s  - split bitmask building into three loops (each byte is separate)
      // 4.42s  - further optimize computing bitmask

      // 4.58s  - using solid & empty bitmasks to early out, same as "foo" but faster bitmask building
      // 4.12s  - using solid & empty bitmasks to efficiently test neighbors
      // 4.04s  - using 16-bit fetches (not endian-independent)

      // 4.30s  - current time with bitmasks disabled again (note was 4.10 earlier)
      // 3.95s  - bitmasks enabled again, no other changes
      // 4.00s  - current time with bitmasks disabled again, no other changes -- wide variation that is time dependent?
      //          (note that most of the numbers listed here are average of 3 values already)
      // 3.98s  - bitmasks enabled

      // Bitmasks removed from the code as not worth the complexity increase

      Uint64 start_time, end_time;
      #ifdef NDEBUG
      int range = 32;
      #else
      int range = 12;
      #endif
      start_time = SDL_GetPerformanceCounter();
      {
         #if 1
         int x,y;
         for (x=-range; x <= range; x += 16)
            for (y=-range; y <= range; y += 16)
               for (b=-range; b <= range; b += 2)
                  for (a=-range; a <= range; a += 2)
                     if (a >= x && a <= x+15 && b >= y && b <= y+15) {
                        #if 1
                        while (!request_chunk(a, b)) {
                           update_meshes_from_render_thread();
                           SDL_Delay(1);
                        }
                        #else
                        raw_mesh rm;
                        rm.cx = a;
                        rm.cy = b;
                        rm.build_buffer = build_buffer;
                        rm.face_buffer = face_buffer;
                        rm.mm = g_mesh_maker;
                        build_chunk(a,b, 0, &rm);
                        upload_mesh_data(&rm);
                        #endif
                     }
         #else
         for (b=-range; b <= range; b += 4)
            for (a=-range; a <= range; a += 4)
               build_chunk(a,b);
         #endif
      }

      // we can't reset the cache until all the workers are done
      for(;;) {
         int i;
         update_meshes_from_render_thread();
         for (i=0; i < num_mesh_workers; ++i)
            if (mesh_data[i].state != WSTATE_idle)
               break;
         if (i == num_mesh_workers)
            break;
         SDL_Delay(3);
      }

      end_time = SDL_GetPerformanceCounter();
      ods("Build time: %7.2fs\n", (end_time - start_time) / (float) SDL_GetPerformanceFrequency());

      // don't waste lots of storage once it's finished start-up
      reset_cache_size(32);
   }
}

int mesh_worker_handler(void *data)
{
   mesh_worker *mw = data;
   mw->face_buffer = malloc(FACE_BUFFER_SIZE);
   mw->build_buffer = malloc(BUILD_BUFFER_SIZE);

   // this loop only works because the compiler can't
   // tell that the SDL_calls don't access mw->state;
   // really we should barrier that stuff
   for(;;) {
      int i,j;
      int cx,cy;

      // wait for a chunk request
      SDL_SemWait(mw->request_received);

      // analyze the chunk request
      assert(mw->state == WSTATE_requested);
      cx = mw->request_cx;
      cy = mw->request_cy;

      // this is inaccurate as it can block while another thread has the cache locked
      mw->state = WSTATE_running;

      // get the chunks we need (this takes a lock and caches them)
      for (j=0; j < 4; ++j)
         for (i=0; i < 4; ++i)
            mw->chunks[j][i] = get_converted_fastchunk(cx-1 + i, cy-1 + j);

      // build the mesh based on the chunks
      mw->rm.build_buffer = mw->build_buffer;
      mw->rm.face_buffer = mw->face_buffer;
      build_chunk(cx, cy, mw->chunks, &mw->rm);
      mw->state = WSTATE_mesh_ready;
      // don't need to notify of this, because it gets polled

      // when done, free the chunks

      SDL_LockMutex(chunk_cache_mutex);
      for (j=0; j < 4; ++j)
         for (i=0; i < 4; ++i) {
            deref_fastchunk(mw->chunks[j][i]);
            mw->chunks[j][i] = NULL;
         }
      SDL_UnlockMutex(chunk_cache_mutex);
   }
   return 0;
}

int request_chunk(int chunk_x, int chunk_y)
{
   int i;
   for (i=0; i < num_mesh_workers; ++i) {
      mesh_worker *mw = &mesh_data[i];
      if (mw->state == WSTATE_idle) {
         mw->request_cx = chunk_x;
         mw->request_cy = chunk_y;
         mw->state = WSTATE_requested;
         SDL_SemPost(mw->request_received);
         ++num_meshes_started;
         return 1;
      }
   }
   return 0;
}

void prepare_threads(void)
{
   int i;
   int num_proc = SDL_GetCPUCount();

   if (num_proc > 6)
      num_mesh_workers = num_proc/2;
   else if (num_proc > 4)
      num_mesh_workers = 4;
   else 
      num_mesh_workers = num_proc-1;

   num_mesh_workers *= 2; // try to get better thread usage

   if (num_mesh_workers > MAX_MESH_WORKERS)
      num_mesh_workers = MAX_MESH_WORKERS;

   chunk_cache_mutex = SDL_CreateMutex();
   chunk_get_mutex   = SDL_CreateMutex();

   for (i=0; i < num_mesh_workers; ++i) {
      mesh_worker *data = &mesh_data[i];
      data->request_received = SDL_CreateSemaphore(0);
      data->chunk_server_done_processing = SDL_CreateSemaphore(0);
      SDL_CreateThread(mesh_worker_handler, "mesh worker", data);
   }
}


#if 0
   if (glBufferStorage) {
      glDeleteBuffersARB(1, &vb->vbuf);
      glGenBuffersARB(1, &vb->vbuf);

      glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->vbuf);
      glBufferStorage(GL_ARRAY_BUFFER_ARB, sizeof(build_buffer), build_buffer, 0);
      glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
   } else {
      glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb->vbuf);
      glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(build_buffer), build_buffer, GL_STATIC_DRAW_ARB);
      glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
   }
#endif


typedef struct
{
   float x,y,z,w;
} plane;

static plane frustum[6];

static void matd_mul(double out[4][4], double src1[4][4], double src2[4][4])
{
   int i,j,k;
   for (j=0; j < 4; ++j) {
      for (i=0; i < 4; ++i) {
         double t=0;
         for (k=0; k < 4; ++k)
            t += src1[k][i] * src2[j][k];
         out[i][j] = t;
      }
   }
}

static void compute_frustum(void)
{
   int i;
   GLdouble mv[4][4],proj[4][4], mvproj[4][4];
   glGetDoublev(GL_MODELVIEW_MATRIX , mv[0]);
   glGetDoublev(GL_PROJECTION_MATRIX, proj[0]);
   matd_mul(mvproj, proj, mv);
   for (i=0; i < 4; ++i) {
      (&frustum[0].x)[i] = (float) (mvproj[3][i] + mvproj[0][i]);
      (&frustum[1].x)[i] = (float) (mvproj[3][i] - mvproj[0][i]);
      (&frustum[2].x)[i] = (float) (mvproj[3][i] + mvproj[1][i]);
      (&frustum[3].x)[i] = (float) (mvproj[3][i] - mvproj[1][i]);
      (&frustum[4].x)[i] = (float) (mvproj[3][i] + mvproj[2][i]);
      (&frustum[5].x)[i] = (float) (mvproj[3][i] - mvproj[2][i]);
   }   
}

static int test_plane(plane *p, float x0, float y0, float z0, float x1, float y1, float z1)
{
   // return false if the box is entirely behind the plane
   float d=0;
   if (p->x > 0) d += x1*p->x; else d += x0*p->x;
   if (p->y > 0) d += y1*p->y; else d += y0*p->y;
   if (p->z > 0) d += z1*p->z; else d += z0*p->z;
   return d + p->w >= 0;
}

static int is_box_in_frustum(float *bmin, float *bmax)
{
   int i;
   for (i=0; i < 5; ++i)
      if (!test_plane(&frustum[i], bmin[0], bmin[1], bmin[2], bmax[0], bmax[1], bmax[2]))
         return 0;
   return 1;
}

#ifdef SHORTVIEW
int view_dist_in_chunks = 50;
#else
int view_dist_in_chunks = 80;
#endif

float compute_priority(int cx, int cy, float x, float y)
{
   float distx, disty, dist2;
   distx = (cx*16+8) - x;
   disty = (cy*16+8) - y;
   dist2 = distx*distx + disty*disty;
   return view_dist_in_chunks*view_dist_in_chunks * 16 * 16 - dist2;
}

int chunk_locations, chunks_considered, chunks_in_frustum;
int quads_considered, quads_rendered;
int chunk_storage_rendered, chunk_storage_considered, chunk_storage_total;
int update_frustum = 1;

#ifdef SHORTVIEW
int max_chunk_storage = 450 << 20;
int min_chunk_storage = 350 << 20;
#else
int max_chunk_storage = 900 << 20;
int min_chunk_storage = 800 << 20;
#endif

float min_priority = -500; // this really wants to be in unit space, not squared space

int num_meshes_uploaded;

void update_meshes_from_render_thread(void)
{
   int i;
   for (i=0; i < num_mesh_workers; ++i) {
      mesh_worker *mw = &mesh_data[i];
      if (mw->state == WSTATE_mesh_ready) {
         upload_mesh_data(&mw->rm);
         ++num_meshes_uploaded;
         mw->state = WSTATE_idle;
      }
   }
}

int num_threads_active;
float chunk_server_activity;

void render_caves(float campos[3])
{
   float x = campos[0], y = campos[1];
   int qchunk_x, qchunk_y;
   int cam_x, cam_y;
   int i,j, rad;

   compute_frustum();

   chunk_locations = chunks_considered = chunks_in_frustum = 0;
   quads_considered = quads_rendered = 0;
   chunk_storage_total = chunk_storage_considered = chunk_storage_rendered = 0;

   cam_x = (int) floor(x+0.5);
   cam_y = (int) floor(y+0.5);

   qchunk_x = (((int) floor(x)+16) >> 5) << 1;
   qchunk_y = (((int) floor(y)+16) >> 5) << 1;

   glEnable(GL_ALPHA_TEST);
   glAlphaFunc(GL_GREATER, 0.5);

   stbglUseProgram(main_prog);
   setup_uniforms(campos); // set uniforms to default values inefficiently
   glActiveTextureARB(GL_TEXTURE2_ARB);
   glEnableVertexAttribArrayARB(0);

   num_meshes_uploaded = 0;
   update_meshes_from_render_thread();

   // traverse all in-range chunks and analyze them
   for (j=-view_dist_in_chunks; j <= view_dist_in_chunks; j += 2) {
      for (i=-view_dist_in_chunks; i <= view_dist_in_chunks; i += 2) {
         float priority;
         int cx = qchunk_x + i;
         int cy = qchunk_y + j;

         priority = compute_priority(cx, cy, x, y);
         if (priority >= min_priority) {
            int slot_x = (cx>>1) & (CACHED_MESH_NUM_X-1);
            int slot_y = (cy>>1) & (CACHED_MESH_NUM_Y-1);
            chunk_mesh *cm = &cached_chunk_mesh[slot_y][slot_x];
            ++chunk_locations;
            if (cm->state == STATE_valid && priority >= 0) {
               // check if chunk pos actually matches
               if (cm->chunk_x != cx || cm->chunk_y != cy) {
                  // we have a stale chunk we need to recreate
                  free_chunk(slot_x, slot_y); // it probably will have already gotten freed, but just in case
               }
            }
            if (cm->state == STATE_invalid) {
               cm->chunk_x = cx;
               cm->chunk_y = cy;
               cm->state = STATE_needed;
            }
            cm->priority = priority;
         }
      }
   }

   // draw front-to-back
   for (rad = 0; rad <= view_dist_in_chunks; rad += 2) {
      for (j=-rad; j <= rad; j += 2) {
         // if j is +- rad, then iterate i through all values
         // if j isn't +-rad, then i should be only -rad & rad
         int step = 2;
         if (abs(j) != rad)
            step = 2*rad;
         for (i=-rad; i <= rad; i += step) {
            int cx = qchunk_x + i;
            int cy = qchunk_y + j;
            int slot_x = (cx>>1) & (CACHED_MESH_NUM_X-1);
            int slot_y = (cy>>1) & (CACHED_MESH_NUM_Y-1);
            chunk_mesh *cm = &cached_chunk_mesh[slot_y][slot_x];
            if (cm->state == STATE_valid && cm->priority >= 0) {
               ++chunks_considered;
               quads_considered += cm->num_quads;
               if (is_box_in_frustum(cm->bounds[0], cm->bounds[1])) {
                  ++chunks_in_frustum;

                  // @TODO if in range
                  stbglUniform3fv(uniform_loc[STBVOX_UNIFORM_transform], 3, cm->transform[0]);
                  glBindBufferARB(GL_ARRAY_BUFFER_ARB, cm->vbuf);
                  glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 4, (void*) 0);
                  glBindTexture(GL_TEXTURE_BUFFER_ARB, cm->fbuf_tex);
                  glDrawArrays(GL_QUADS, 0, cm->num_quads*4);
                  quads_rendered += cm->num_quads;

                  chunk_storage_rendered += cm->vbuf_size + cm->fbuf_size;
               }
               chunk_storage_considered += cm->vbuf_size + cm->fbuf_size;
            }
         }
      }
   }

   glDisableVertexAttribArrayARB(0);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
   glActiveTextureARB(GL_TEXTURE0_ARB);

   stbglUseProgram(0);
   num_meshes_started = 0;

   {
      #define MAX_QUEUE  8
      float highest_priority[MAX_QUEUE];
      int highest_i[MAX_QUEUE], highest_j[MAX_QUEUE];
      float lowest_priority = view_dist_in_chunks * view_dist_in_chunks * 16 * 16.0f;
      int lowest_i = -1, lowest_j = -1;

      for (i=0; i < MAX_QUEUE; ++i) {
         highest_priority[i] = min_priority;
         highest_i[i] = -1;
         highest_j[i] = -1;
      }

      for (j=0; j < CACHED_MESH_NUM_Y; ++j) {
         for (i=0; i < CACHED_MESH_NUM_X; ++i) {
            chunk_mesh *cm = &cached_chunk_mesh[j][i];
            if (cm->state == STATE_valid) {
               cm->priority = compute_priority(cm->chunk_x, cm->chunk_y, x, y);
               chunk_storage_total += cm->vbuf_size + cm->fbuf_size;
               if (cm->priority < lowest_priority) {
                  lowest_priority = cm->priority;
                  lowest_i = i;
                  lowest_j = j;
               }
            }
            if (cm->state == STATE_needed) {
               cm->priority = compute_priority(cm->chunk_x, cm->chunk_y, x, y);
               if (cm->priority < min_priority)
                  cm->state = STATE_invalid;
               else if (cm->priority > highest_priority[0]) {
                  int k;
                  highest_priority[0] = cm->priority;
                  highest_i[0] = i;
                  highest_j[0] = j;
                  // bubble this up to right place
                  for (k=0; k < MAX_QUEUE-1; ++k) {
                     if (highest_priority[k] > highest_priority[k+1]) {
                        highest_priority[k] = highest_priority[k+1];
                        highest_priority[k+1] = cm->priority;
                        highest_i[k] = highest_i[k+1];
                        highest_i[k+1] = i;
                        highest_j[k] = highest_j[k+1];
                        highest_j[k+1] = j;
                     } else {
                        break;
                     }
                  }
               }
            }
         }
      }


      // I couldn't find any straightforward logic that avoids
      // the hysteresis problem of continually creating & freeing
      // a block on the margin, so I just don't free a block until
      // it's out of range, but this doesn't actually correctly
      // handle when the cache is too small for the given range
      if (chunk_storage_total >= min_chunk_storage && lowest_i >= 0) {
         if (cached_chunk_mesh[lowest_j][lowest_i].priority < -1200) // -1000? 0?
            free_chunk(lowest_i, lowest_j);
      }

      if (chunk_storage_total < max_chunk_storage && highest_i[0] >= 0) {
         for (j=MAX_QUEUE-1; j >= 0; --j) {
            if (highest_j[0] >= 0) {
               chunk_mesh *cm = &cached_chunk_mesh[highest_j[j]][highest_i[j]];
               if (request_chunk(cm->chunk_x, cm->chunk_y)) {
                  cm->state = STATE_requested;
               } else {
                  // if we couldn't queue this one, skip the remainder
                  break;
               }
            }
         }
      }
   }

   update_meshes_from_render_thread();

   num_threads_active = 0;
   for (i=0; i < num_mesh_workers; ++i) {
      num_threads_active += (mesh_data[i].state == WSTATE_running);
   }
}

// Raw data for Q&A:
//
//   26% parsing & loading minecraft files (4/5ths of which is zlib decode)
//   39% building mesh from stb input format
//   18% converting from minecraft blocks to stb blocks
//    9% reordering from minecraft axis order to stb axis order
//    7% uploading vertex buffer to OpenGL
