// tested in VC6 (1998) and VS 2019
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_MEAN_AND_LEAN
#include <windows.h>

#include <stdio.h>
#include <tchar.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <gl/gl.h>
#include <gl/glu.h>

int screen_x=1024, screen_y=768;
GLuint tex;

unsigned char ttf_buffer[1<<20];
unsigned char temp_bitmap[1024*1024];
stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs

void init(void)
{
   fread(ttf_buffer, 1, 1<<20, fopen("c:/windows/fonts/times.ttf", "rb"));
   stbtt_BakeFontBitmap(ttf_buffer,0, 64.0, temp_bitmap,1024,1024, 32,96, cdata);
   glGenTextures(1, &tex);
   glBindTexture(GL_TEXTURE_2D, tex);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 1024,1024,0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void print(float x, float y, char *text)
{
   // assume orthographic projection with units = screen pixels, origin at top left
   glBindTexture(GL_TEXTURE_2D, tex);
   glBegin(GL_QUADS);
   while (*text) {
      if (*text >= 32 && *text < 128) {
         stbtt_aligned_quad q;
         stbtt_GetBakedQuad(cdata, 1024,1024, *text-32, &x,&y,&q,1);//1=opengl & d3d10+,0=d3d9
         glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y0);
         glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y0);
         glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y1);
         glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y1);
      }
      ++text;
   }
   glEnd();
}

void draw(void)
{
   glViewport(0,0,screen_x,screen_y);
   glClearColor(0.45f,0.45f,0.75f,0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glDisable(GL_CULL_FACE);
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_BLEND);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0,screen_x,screen_y,0,-1,1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glEnable(GL_TEXTURE_2D);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glColor3f(1,1,1);

   print(100,150, "This is a simple test!");

   // show font bitmap
   glBegin(GL_QUADS);
      glTexCoord2f(0,0); glVertex2f(256,200+0);
      glTexCoord2f(1,0); glVertex2f(768,200+0);
      glTexCoord2f(1,1); glVertex2f(768,200+512);
      glTexCoord2f(0,1); glVertex2f(256,200+512);
   glEnd();
}

///////////////////////////////////////////////////////////////////////
///
///
///  Windows OpenGL setup
///
///

HINSTANCE app;
HWND  window;
HGLRC rc;
HDC   dc;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

int mySetPixelFormat(HWND win)
{
   PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1, PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA };
   int                   pixel_format;
   pfd.dwLayerMask  = PFD_MAIN_PLANE;
   pfd.cColorBits   = 24;
   pfd.cAlphaBits   = 8;
   pfd.cDepthBits   = 24;
   pfd.cStencilBits = 8;
   pixel_format = ChoosePixelFormat(dc, &pfd);
   if (!pixel_format) return FALSE;
   if (!DescribePixelFormat(dc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
      return FALSE;
   SetPixelFormat(dc, pixel_format, &pfd);
   return TRUE;
}

static int WINAPI WinProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
   switch (msg) {
      case WM_CREATE: {
         LPCREATESTRUCT lpcs = (LPCREATESTRUCT) lparam;
         dc = GetDC(wnd);
         if (mySetPixelFormat(wnd)) {
            rc = wglCreateContext(dc);
            if (rc) {
               wglMakeCurrent(dc, rc);
               return 0;
            }
         }
         return -1;
      }

      case WM_DESTROY:
         wglMakeCurrent(NULL, NULL); 
         if (rc) wglDeleteContext(rc);
         PostQuitMessage (0);
         return 0;

      default:
         return DefWindowProc (wnd, msg, wparam, lparam);
   }

   return DefWindowProc (wnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   DWORD dwstyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
   WNDCLASSEX  wndclass;
   wndclass.cbSize        = sizeof(wndclass);
   wndclass.style         = CS_OWNDC;
   wndclass.lpfnWndProc   = (WNDPROC) WinProc;
   wndclass.cbClsExtra    = 0;
   wndclass.cbWndExtra    = 0;
   wndclass.hInstance     = hInstance;
   wndclass.hIcon         = LoadIcon(hInstance, _T("appicon"));
   wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
   wndclass.hbrBackground = GetStockObject(NULL_BRUSH);
   wndclass.lpszMenuName  = _T("truetype-test");
   wndclass.lpszClassName = _T("truetype-test");
   wndclass.hIconSm       = NULL;
   app = hInstance;

   if (!RegisterClassEx(&wndclass))
      return 0;

   window = CreateWindow(_T("truetype-test"), _T("truetype test"), dwstyle,
                      CW_USEDEFAULT,0, screen_x, screen_y,
                      NULL, NULL, app,  NULL);
   ShowWindow(window, SW_SHOWNORMAL);
   init();

   for(;;) {
      MSG msg;
      if (GetMessage(&msg, NULL, 0, 0)) {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      } else {
         return 1;   // WM_QUIT
      }
      wglMakeCurrent(dc, rc);
      draw();
      SwapBuffers(dc);
   }
   return 0;
}
