#include "stb_voxel_render.h"

#define STB_GLEXT_DECLARE "glext_list.h"
#include "stb_gl.h"
#include "stb_image.h"
#include "stb_glprog.h"

#include "caveview.h"
#include "cave_parse.h"
#include "stb.h"
#include "sdl.h"
#include "sdl_thread.h"
#include <math.h>

//#define SHORTVIEW


// renderer maintains GL meshes, draws them
stbvox_mesh_maker g_mesh_maker;

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

extern SDL_mutex * chunk_cache_mutex;
extern SDL_mutex * chunk_get_mutex;


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
   int i;
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
}

// 32..-32, 32..-32, !FILL_TERRAIN, !FANCY_LEAVES on 'mcrealm' data set

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
void world_init(void)
{
   int a,b,x,y;

   Uint64 start_time, end_time;
   #ifdef NDEBUG
   int range = 32;
   #else
   int range = 12;
   #endif

   start_time = SDL_GetPerformanceCounter();
   for (x=-range; x <= range; x += 16)
      for (y=-range; y <= range; y += 16)
         for (b=y; b < y+16 && b <= range; b += 2)
            for (a=x; a < x+16 && a <= range; a += 2)
               while (!request_chunk(a, b)) { // if request fails, all threads are busy
                  update_meshes_from_render_thread();
                  SDL_Delay(1);
               }

   // we can't reset the cache until all the workers are done,
   // so wait for that (this is only needed if we want to time
   // when the build finishes, or when we want to reset the
   // cache size)
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

   // don't waste lots of storage on chunk caches once it's finished starting-up;
   // this was only needed to be this large because we worked in large blocks
   // to maximize sharing
   reset_cache_size(32);
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