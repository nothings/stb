#pragma warning(disable:4244; disable:4305; disable:4018)

#define _WIN32_WINNT 0x400

#include "sdl.h"
#include "sdl_mixer.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

#include <windows.h>

#define STB_GLEXT_DEFINE "glext_list.h"
#include "stb_gl.h"

#define STB_DEFINE
#include "stb.h"

#include "caveview.h"

#define SCALE   2

void error(char *s)
{
   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", s, NULL);
   exit(0);
}

void ods(char *fmt, ...)
{
   char buffer[1000];
   va_list va;
   va_start(va, fmt);
   vsprintf(buffer, fmt, va);
   va_end(va);
   SDL_Log("%s", buffer);
}

#define TICKS_PER_SECOND  60

static SDL_Window *window;

extern void init_game(void);
extern void draw_main(void);
extern void process_tick(float dt);
extern void editor_init(void);

void draw(void)
{
   draw_main();
   SDL_GL_SwapWindow(window);
}


static int initialized=0;
static float last_dt;

int screen_x,screen_y;

float carried_dt = 0;
#define TICKRATE 60


int raw_level_time;
extern void init_game(void);
extern void draw_main(void);

float global_timer;

int loopmode(float dt, int real, int in_client)
{
   float actual_dt = dt;

   float jump_timer = dt;

   if (!initialized) return 0;

   if (!real)
      return 0;

   // don't allow more than 6 frames to update at a time
   if (dt > 0.075) dt = 0.075;

   global_timer += dt;

   carried_dt += dt;
   while (carried_dt > 1.0/TICKRATE) {
      //update_input();
      // if the player is dead, stop the sim
      carried_dt -= 1.0/TICKRATE;
   }

   process_tick(dt);
   draw();

   return 0;
}

static int quit;

//int winproc(void *data, stbwingraph_event *e)

extern int editor_scale;
extern void editor_key(enum stbte_action act);
extern int controls;

void active_control_set(int key)
{
   controls |= 1 << key;
}

void active_control_clear(int key)
{
   controls &= ~(1 << key);
}

extern void update_view(float dx, float dy);

void  process_sdl_mouse(SDL_Event *e)
{
   update_view((float) e->motion.xrel / screen_x, (float) e->motion.yrel / screen_y);
}

void process_event(SDL_Event *e)
{
   switch (e->type) {
      case SDL_MOUSEMOTION:
         process_sdl_mouse(e);
         break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEWHEEL:
         //stbte_mouse_sdl(edit_map, e, 1.0f/editor_scale,1.0f/editor_scale,0,0);
         break;

      case SDL_QUIT:
         quit = 1;
         break;

      case SDL_WINDOWEVENT:
         switch (e->window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
               screen_x = e->window.data1;
               screen_y = e->window.data2;
               loopmode(0,1,0);
               break;
         }
         break;

      case SDL_TEXTINPUT:
         switch(e->text.text[0]) {
            #if 0
            case 27: {
               #if 0
               int result;
               SDL_ShowCursor(SDL_ENABLE);
               if (MessageBox(e->handle, "Exit CLTT?", "CLTT", MB_OKCANCEL) == IDOK);
               #endif
               {
                  quit = 1;
                  break;
               }
               //SDL_ShowCursor(SDL_DISABLE);
               break;
            }
            #endif
         }
         break;

      case SDL_KEYDOWN: {
         int k = e->key.keysym.sym;
         int s = e->key.keysym.scancode;
         SDL_Keymod mod;
         mod = SDL_GetModState();
         if (k == SDLK_ESCAPE) {
#ifndef DO_EDITOR
            quit = 1;
#endif
         }

         if (s == SDL_SCANCODE_D)   active_control_set(0);
         if (s == SDL_SCANCODE_A)   active_control_set(1);
         if (s == SDL_SCANCODE_W)   active_control_set(2);
         if (s == SDL_SCANCODE_S)   active_control_set(3);
         if (k == SDLK_SPACE)       active_control_set(4); 
         if (s == SDL_SCANCODE_LCTRL)   active_control_set(5);
         if (s == SDL_SCANCODE_S)   active_control_set(6);
         if (s == SDL_SCANCODE_D)   active_control_set(7);

         #if 0
         if (game_mode == GAME_editor) {
            switch (k) {
               case SDLK_RIGHT: editor_key(STBTE_scroll_right); break;
               case SDLK_LEFT : editor_key(STBTE_scroll_left ); break;
               case SDLK_UP   : editor_key(STBTE_scroll_up   ); break;
               case SDLK_DOWN : editor_key(STBTE_scroll_down ); break;
            }
            switch (s) {
               case SDL_SCANCODE_S: editor_key(STBTE_tool_select); break;
               case SDL_SCANCODE_B: editor_key(STBTE_tool_brush ); break;
               case SDL_SCANCODE_E: editor_key(STBTE_tool_erase ); break;
               case SDL_SCANCODE_R: editor_key(STBTE_tool_rectangle ); break;
               case SDL_SCANCODE_I: editor_key(STBTE_tool_eyedropper); break;
               case SDL_SCANCODE_L: editor_key(STBTE_tool_link); break;
               case SDL_SCANCODE_G: editor_key(STBTE_act_toggle_grid); break;
            }
            if ((e->key.keysym.mod & KMOD_CTRL) && !(e->key.keysym.mod & ~KMOD_CTRL)) {
               switch (s) {
                  case SDL_SCANCODE_X: editor_key(STBTE_act_cut  ); break;
                  case SDL_SCANCODE_C: editor_key(STBTE_act_copy ); break;
                  case SDL_SCANCODE_V: editor_key(STBTE_act_paste); break;
                  case SDL_SCANCODE_Z: editor_key(STBTE_act_undo ); break;
                  case SDL_SCANCODE_Y: editor_key(STBTE_act_redo ); break;
               }
            }
         }
         #endif
         break;
      }
      case SDL_KEYUP: {
         int k = e->key.keysym.sym;
         int s = e->key.keysym.scancode;
         if (s == SDL_SCANCODE_D)   active_control_clear(0);
         if (s == SDL_SCANCODE_A)   active_control_clear(1);
         if (s == SDL_SCANCODE_W)   active_control_clear(2);
         if (s == SDL_SCANCODE_S)   active_control_clear(3);
         if (k == SDLK_SPACE)       active_control_clear(4); 
         if (s == SDL_SCANCODE_LCTRL)   active_control_clear(5);
         if (s == SDL_SCANCODE_S)   active_control_clear(6);
         if (s == SDL_SCANCODE_D)   active_control_clear(7);
         break;
      }
   }
}

static SDL_GLContext *context;

static float getTimestep(float minimum_time)
{
   float elapsedTime;
   double thisTime;
   static double lastTime = -1;
   
   if (lastTime == -1)
      lastTime = SDL_GetTicks() / 1000.0 - minimum_time;

   for(;;) {
      thisTime = SDL_GetTicks() / 1000.0;
      elapsedTime = (float) (thisTime - lastTime);
      if (elapsedTime >= minimum_time) {
         lastTime = thisTime;         
         return elapsedTime;
      }
      // @TODO: compute correct delay
      SDL_Delay(1);
   }
}

void APIENTRY gl_debug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *param)
{
   #if 0
   if (severity == GL_DEBUG_SEVERITY_LOW_ARB)
      return;
   #endif
   ods("%s\n", message);
}

extern void do_music(int16 *stream, int samples);

extern void foo(void);

void render_init(void);

int is_synchronous_debug;
void enable_synchronous(void)
{
   glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
   is_synchronous_debug = 1;
}

void prepare_threads(void);

//void stbwingraph_main(void)
int SDL_main(int argc, char **argv)
{
   SDL_Init(SDL_INIT_VIDEO);

   prepare_threads();

   Mix_Init(0);
   Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 1024); // 1024 bytes = 256 samples = 

   SDL_GL_SetAttribute(SDL_GL_RED_SIZE  , 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE , 8);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

   #ifdef GL_DEBUG
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
   #endif

   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

   screen_x = 1920;
   screen_y = 1080;

   window = SDL_CreateWindow("caveview", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   screen_x, screen_y,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                             );
   if (!window) error("Couldn't create window");

   context = SDL_GL_CreateContext(window);
   if (!context) error("Couldn't create context");

   SDL_GL_MakeCurrent(window, context); // is this true by default?

   // if (!IsDebuggerPresent())   
   SDL_SetRelativeMouseMode(SDL_TRUE);

   stbgl_initExtensions();

   #ifdef GL_DEBUG
   if (glDebugMessageCallbackARB) {
      glDebugMessageCallbackARB(gl_debug, NULL);

      enable_synchronous();
   }
   #endif

   SDL_GL_SetSwapInterval(0); // only when profiling

   render_init();
   mesh_init();
   world_init();

   init_game();
   //editor_init();
   initialized = 1;

   while (!quit) {
      SDL_Event e;
      while (SDL_PollEvent(&e))
         process_event(&e);

      loopmode(getTimestep(0.0166f/8), 1, 1);
      quit=quit;
   }
   //music_end();

   return 0;
}
