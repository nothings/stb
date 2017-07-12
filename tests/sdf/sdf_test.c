#define STB_DEFINE
#include "stb.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// used both to compute SDF and in 'shader'
float sdf_size = 32.0;          // the larger this is, the better large font sizes look
float pixel_dist_scale = 64.0;  // trades off precision w/ ability to handle *smaller* sizes
int onedge_value = 128;
int padding = 3; // not used in shader

typedef struct
{
   float advance;
   signed char xoff;
   signed char yoff;
   unsigned char w,h;
   unsigned char *data;
} fontchar;

fontchar fdata[128];

#define BITMAP_W  1200
#define BITMAP_H  800
unsigned char bitmap[BITMAP_H][BITMAP_W][3];

char *sample = "This is goofy text, size %d!";
char *small_sample = "This is goofy text, size %d! Really needs in-shader supersampling to look good.";

void blend_pixel(int x, int y, int color, float alpha)
{
   int i;
   for (i=0; i < 3; ++i)
      bitmap[y][x][i] = (unsigned char) (stb_lerp(alpha, bitmap[y][x][i], color)+0.5); // round
}

void draw_char(float px, float py, char c, float relative_scale)
{
   int x,y;
   fontchar *fc = &fdata[c];
   float fx0 = px + fc->xoff*relative_scale;
   float fy0 = py + fc->yoff*relative_scale;
   float fx1 = fx0 + fc->w*relative_scale;
   float fy1 = fy0 + fc->h*relative_scale;
   int ix0 = (int) floor(fx0);
   int iy0 = (int) floor(fy0);
   int ix1 = (int) ceil(fx1);
   int iy1 = (int) ceil(fy1);
   // clamp to viewport
   if (ix0 < 0) ix0 = 0;
   if (iy0 < 0) iy0 = 0;
   if (ix1 > BITMAP_W) ix1 = BITMAP_W;
   if (iy1 > BITMAP_H) iy1 = BITMAP_H;

   for (y=iy0; y < iy1; ++y) {
      for (x=ix0; x < ix1; ++x) {
         float sdf_dist, pix_dist;
         float bmx = stb_linear_remap(x, fx0, fx1, 0, fc->w);
         float bmy = stb_linear_remap(y, fy0, fy1, 0, fc->h);
         int v00,v01,v10,v11;
         float v0,v1,v;
         int sx0 = (int) bmx;
         int sx1 = sx0+1;
         int sy0 = (int) bmy;
         int sy1 = sy0+1;
         // compute lerp weights
         bmx = bmx - sx0;
         bmy = bmy - sy0;
         // clamp to edge
         sx0 = stb_clamp(sx0, 0, fc->w-1);
         sx1 = stb_clamp(sx1, 0, fc->w-1);
         sy0 = stb_clamp(sy0, 0, fc->h-1);
         sy1 = stb_clamp(sy1, 0, fc->h-1);
         // bilinear texture sample
         v00 = fc->data[sy0*fc->w+sx0];
         v01 = fc->data[sy0*fc->w+sx1];
         v10 = fc->data[sy1*fc->w+sx0];
         v11 = fc->data[sy1*fc->w+sx1];
         v0 = stb_lerp(bmx,v00,v01);
         v1 = stb_lerp(bmx,v10,v11);
         v  = stb_lerp(bmy,v0 ,v1 );
         #if 0
         // non-anti-aliased
         if (v > onedge_value)
            blend_pixel(x,y,0,1.0);
         #else
         // Following math can be greatly simplified

         // convert distance in SDF value to distance in SDF bitmap
         sdf_dist = stb_linear_remap(v, onedge_value, onedge_value+pixel_dist_scale, 0, 1);
         // convert distance in SDF bitmap to distance in output bitmap
         pix_dist = sdf_dist * relative_scale;
         // anti-alias by mapping 1/2 pixel around contour from 0..1 alpha
         v = stb_linear_remap(pix_dist, -0.5f, 0.5f, 0, 1);
         if (v > 1) v = 1;
         if (v > 0)
            blend_pixel(x,y,0,v);
         #endif
      }
   }
}


void print_text(float x, float y, char *text, float scale)
{
   int i;
   for (i=0; text[i]; ++i) {
      if (fdata[text[i]].data)
         draw_char(x,y,text[i],scale);
      x += fdata[text[i]].advance * scale;
   }
}

int main(int argc, char **argv)
{
   int ch;
   float scale, ypos;
   stbtt_fontinfo font;
   void *data = stb_file("c:/windows/fonts/times.ttf", NULL);
   stbtt_InitFont(&font, data, 0);

   scale = stbtt_ScaleForPixelHeight(&font, sdf_size);

   for (ch=32; ch < 127; ++ch) {
      fontchar fc;
      int xoff,yoff,w,h, advance;
      fc.data = stbtt_GetCodepointSDF(&font, scale, ch, padding, onedge_value, pixel_dist_scale, &w, &h, &xoff, &yoff);
      fc.xoff = xoff;
      fc.yoff = yoff;
      fc.w = w;
      fc.h = h;
      stbtt_GetCodepointHMetrics(&font, ch, &advance, NULL);
      fc.advance = advance * scale;
      fdata[ch] = fc;
   }

   ypos = 60;
   memset(bitmap, 255, sizeof(bitmap));
   print_text(400, ypos+30, stb_sprintf("sdf bitmap height %d", (int) sdf_size), 30/sdf_size);
   ypos += 80;
   for (scale = 8.0; scale < 120.0; scale *= 1.33f) {
      print_text(80, ypos+scale, stb_sprintf(scale == 8.0 ? small_sample : sample, (int) scale), scale / sdf_size);
      ypos += scale*1.05f + 20;
   }

   stbi_write_png("sdf_test.png", BITMAP_W, BITMAP_H, 3, bitmap, 0);
   return 0;
}
