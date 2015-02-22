#include <windows.h>
#include "game.h"
#include "stb.h"

#include "sdl.h"
#include "SDL_opengl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_GL_IMPLEMENTATION
#include "stb_gl.h"

#define STB_GLPROG_IMPLEMENTATION
#define STB_GLPROG_ARB_DEFINE_EXTENSIONS
#include "stb_glprog.h"

#include "stb_easy_font.h"

char *game_name = "caveview";

// assume only a single texture with all sprites
float texture_s_scale;
float texture_t_scale;
GLuint interface_tex, logo_tex;

extern int screen_x, screen_y; // main.c

int tex_w, tex_h;
void *tex_data;

GLuint load_texture(char *filename, int keep)
{
   GLuint tex;
   tex_data = stbi_load(filename, &tex_w, &tex_h, NULL, 4);
   if (tex_data == NULL) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                               game_name,
                               "Couldn't open image file.",
                               NULL);
      exit(1);
   }

   glGenTextures(1, &tex);
   glBindTexture(GL_TEXTURE_2D, tex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   if (!keep) {
      free(tex_data);
      tex_data = NULL;
   }

   return tex;
}

static void init_graphics(void)
{
   //logo_tex = load_texture("sss_logo.png",0);
   //interface_tex = load_texture("game_art.png",1);
   texture_s_scale = 1.0f / tex_w;
   texture_t_scale = 1.0f / tex_h;
}

void print_string(float x, float y, char *text, float r, float g, float b)
{
   static char buffer[99999];
   int num_quads;
   
   num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

   glColor3f(r,g,b);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, 16, buffer);
   glDrawArrays(GL_QUADS, 0, num_quads*4);
   glDisableClientState(GL_VERTEX_ARRAY);
}

float text_color[3];
float pos_x = 10;
float pos_y = 10;

void print(char *text, ...)
{
   char buffer[999];
   va_list va;
   va_start(va, text);
   vsprintf(buffer, text, va);
   va_end(va);
   print_string(pos_x, pos_y, buffer, text_color[0], text_color[1], text_color[2]);
   pos_y += 10;
}

// mouse offsetting 'pixel to virtual'
float xs_p2v, ys_p2v;// xoff_p2v, yoff_p2v;

// viewport offseting 'virtual to pixel'
float xs_v2p, ys_v2p, xoff_v2p, yoff_v2p;

float camang[3], camloc[3] = { 0,0,75 };
float player_zoom = 1.0;
int third_person;
float rotate_view = 0.0;

#define REVERSE_DEPTH


void init_game(void)
{
   init_graphics();
}

void render_caves(float pos[3]);

void camera_to_worldspace(float world[3], float cam_x, float cam_y, float cam_z)
{
   float vec[3] = { cam_x, cam_y, cam_z };
   float t[3];
   float s,c;
   s = sin(camang[0]*3.141592/180);
   c = cos(camang[0]*3.141592/180);

   t[0] = vec[0];
   t[1] = c*vec[1] - s*vec[2];
   t[2] = s*vec[1] + c*vec[2];

   s = sin(camang[2]*3.141592/180);
   c = cos(camang[2]*3.141592/180);
   world[0] = c*t[0] - s*t[1];
   world[1] = s*t[0] + c*t[1];
   world[2] = t[2];
}

// camera worldspace velocity
float cam_vel[3];

int controls;

#define MAX_VEL  150      // blocks per second
#define ACCEL      6
#define DECEL      3

#define STATIC_FRICTION   DECEL
#define EFFECTIVE_ACCEL   (ACCEL+DECEL)

// dynamic friction:
//
//    if going at MAX_VEL, ACCEL and friction must cancel
//    EFFECTIVE_ACCEL = DECEL + DYNAMIC_FRIC*MAX_VEL
#define DYNAMIC_FRICTION  (ACCEL/(float)MAX_VEL)

float view_x_vel = 0;
float view_z_vel = 0;
float pending_view_x;
float pending_view_z;
float pending_view_x;
float pending_view_z;

void process_tick_raw(float dt)
{
   int i;
   float thrust[3] = { 0,0,0 };
   float world_thrust[3];

   // choose direction to apply thrust

   thrust[0] = (controls &  3)== 1 ? EFFECTIVE_ACCEL : (controls &  3)== 2 ? -EFFECTIVE_ACCEL : 0;
   thrust[1] = (controls & 12)== 4 ? EFFECTIVE_ACCEL : (controls & 12)== 8 ? -EFFECTIVE_ACCEL : 0;
   thrust[2] = (controls & 48)==16 ? EFFECTIVE_ACCEL : (controls & 48)==32 ? -EFFECTIVE_ACCEL : 0;

   // @TODO clamp thrust[0] & thrust[1] vector length to EFFECTIVE_ACCEL

   camera_to_worldspace(world_thrust, thrust[0], thrust[1], 0);
   world_thrust[2] += thrust[2];

   for (i=0; i < 3; ++i) {
      float acc = world_thrust[i];
      cam_vel[i] += acc*dt;
   }

   if (cam_vel[0] || cam_vel[1] || cam_vel[2])
   {
      float vel = sqrt(cam_vel[0]*cam_vel[0] + cam_vel[1]*cam_vel[1] + cam_vel[2]*cam_vel[2]);
      float newvel = vel;
      float dec = STATIC_FRICTION + DYNAMIC_FRICTION*vel;
      newvel = vel - dec*dt;
      if (newvel < 0)
         newvel = 0;
      cam_vel[0] *= newvel/vel;
      cam_vel[1] *= newvel/vel;
      cam_vel[2] *= newvel/vel;
   }

   camloc[0] += cam_vel[0] * dt;
   camloc[1] += cam_vel[1] * dt;
   camloc[2] += cam_vel[2] * dt;

   view_x_vel *= pow(0.75, dt);
   view_z_vel *= pow(0.75, dt);

   view_x_vel += (pending_view_x - view_x_vel)*dt*60;
   view_z_vel += (pending_view_z - view_z_vel)*dt*60;

   pending_view_x -= view_x_vel * dt;
   pending_view_z -= view_z_vel * dt;
   camang[0] += view_x_vel * dt;
   camang[2] += view_z_vel * dt;
   camang[0] = stb_clamp(camang[0], -90, 90);
   camang[2] = fmod(camang[2], 360);
}

void process_tick(float dt)
{
   while (dt > 1.0/60) {
      process_tick_raw(1.0/60);
      dt -= 1.0/60;
   }
   process_tick_raw(dt);
}

void update_view(float dx, float dy)
{
   // hard-coded mouse sensitivity, not resolution independent?
   pending_view_z -= dx*300;
   pending_view_x -= dy*700;
}

extern int screen_x, screen_y;
extern int is_synchronous_debug;
float render_time;

extern int chunk_locations, chunks_considered, chunks_in_frustum;
extern int quads_considered, quads_rendered;
extern int chunk_storage_rendered, chunk_storage_considered, chunk_storage_total;
extern int view_dist_in_chunks;
extern int num_threads_active, num_meshes_started, num_meshes_uploaded;
extern float chunk_server_activity;

static Uint64 start_time, end_time; // render time

float chunk_server_status[32];
int chunk_server_pos;

void draw_stats(void)
{
   int i;

   static Uint64 last_frame_time;
   Uint64 cur_time = SDL_GetPerformanceCounter();
   float chunk_server=0;
   float frame_time = (cur_time - last_frame_time) / (float) SDL_GetPerformanceFrequency();
   last_frame_time = cur_time;

   chunk_server_status[chunk_server_pos] = chunk_server_activity;
   chunk_server_pos = (chunk_server_pos+1) %32;

   for (i=0; i < 32; ++i)
      chunk_server += chunk_server_status[i] / 32.0;

   stb_easy_font_spacing(-0.75);
   pos_y = 10;
   text_color[0] = text_color[1] = text_color[2] = 1.0f;
   print("Frame time: %6.2fms, CPU frame render time: %5.2fms", frame_time*1000, render_time*1000);
   print("Tris: %4.1fM drawn of %4.1fM in range", 2*quads_rendered/1000000.0f, 2*quads_considered/1000000.0f);
   print("Vbuf storage: %dMB in frustum of %dMB in range of %dMB in cache", chunk_storage_rendered>>20, chunk_storage_considered>>20, chunk_storage_total>>20);
   print("Num mesh builds started this frame: %d; num uploaded this frame: %d\n", num_meshes_started, num_meshes_uploaded);
   print("QChunks: %3d in frustum of %3d valid of %3d in range", chunks_in_frustum, chunks_considered, chunk_locations);
   print("Mesh worker threads active: %d", num_threads_active);
   print("View distance: %d blocks", view_dist_in_chunks*16);
   print("%s", glGetString(GL_RENDERER));

   if (is_synchronous_debug) {
      text_color[0] = 1.0;
      text_color[1] = 0.5;
      text_color[2] = 0.5;
      print("SLOWNESS: Synchronous debug output is enabled!");
   }
}

void draw_main(void)
{
   glEnable(GL_CULL_FACE);
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   #ifdef REVERSE_DEPTH
   glDepthFunc(GL_GREATER);
   glClearDepth(0);
   #else
   glDepthFunc(GL_LESS);
   glClearDepth(1);
   #endif
   glDepthMask(GL_TRUE);
   glDisable(GL_SCISSOR_TEST);
   glClearColor(0.6,0.7,0.9,0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glColor3f(1,1,1);
   glFrontFace(GL_CW);
   glEnable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);


   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   #ifdef REVERSE_DEPTH
   stbgl_Perspective(player_zoom, 90, 70, 3000, 1.0/16);
   #else
   stbgl_Perspective(player_zoom, 90, 70, 1.0/16, 3000);
   #endif

   // now compute where the camera should be
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   stbgl_initCamera_zup_facing_y();

   //glTranslatef(0,150,-5);
   // position the camera and render it

   if (third_person) {
      glTranslatef(0,2.5,0);
      glRotatef(-camang[0],1,0,0);

      glTranslatef(0,2,0);
      glRotatef(-camang[2]-rotate_view,0,0,1);

      //glTranslatef(0,0,1);
      //glTranslatef(0,0,-1);
   } else {
      glRotatef(-camang[0],1,0,0);
      glRotatef(-camang[2],0,0,1);
   }

   glTranslatef(-camloc[0], -camloc[1], -camloc[2]);

   start_time = SDL_GetPerformanceCounter();
   render_caves(camloc);
   end_time = SDL_GetPerformanceCounter();

   render_time = (end_time - start_time) / (float) SDL_GetPerformanceFrequency();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,screen_x/2,screen_y/2,0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
   glDisable(GL_CULL_FACE);
   draw_stats();
}
