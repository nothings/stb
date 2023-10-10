#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stop() __debugbreak()
#include <windows.h>
#define int64 __int64

#pragma warning(disable:4127)

#define STBIR__WEIGHT_TABLES  
#define STBIR_PROFILE
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"  

static int * file_read( char const * filename )
{
  size_t s;
  int * m;
  FILE * f = fopen( filename, "rb" );
  if ( f == 0 ) return 0;
  
  fseek( f, 0, SEEK_END);
  s = ftell( f );
  fseek( f, 0, SEEK_SET);
  m = malloc( s + 4 );
  m[0] = (int)s;
  fread( m+1, 1, s, f);
  fclose(f);

  return( m );
}

typedef struct fileinfo
{
  int * timings;
  int timing_count;
  int dimensionx, dimensiony;
  int numtypes;
  int * types;
  int * effective;
  int cpu;
  int simd;
  int numinputrects;
  int * inputrects;
  int outputscalex, outputscaley;
  int milliseconds;
  int64 cycles;
  double scale_time;
  int bitmapx, bitmapy;
  char const * filename;
} fileinfo;

int numfileinfo;
fileinfo fi[256];
unsigned char * bitmap;
int bitmapw, bitmaph, bitmapp;

static int use_timing_file( char const * filename, int index )
{
  int * base = file_read( filename );
  int * file = base;

  if ( base == 0 ) return 0;

  ++file; // skip file image size;
  if ( *file++ != 'VFT1' ) return 0;
  fi[index].cpu = *file++;
  fi[index].simd = *file++;
  fi[index].dimensionx = *file++;
  fi[index].dimensiony = *file++;
  fi[index].numtypes = *file++;
  fi[index].types = file; file += fi[index].numtypes;
  fi[index].effective = file; file += fi[index].numtypes;
  fi[index].numinputrects = *file++;
  fi[index].inputrects = file; file += fi[index].numinputrects * 2;
  fi[index].outputscalex = *file++;
  fi[index].outputscaley = *file++;
  fi[index].milliseconds = *file++;
  fi[index].cycles = ((int64*)file)[0]; file += 2;
  fi[index].filename = filename;

  fi[index].timings = file;
  fi[index].timing_count = (int) ( ( base[0] - ( ((char*)file - (char*)base - sizeof(int) ) ) ) / (sizeof(int)*2) );

  fi[index].scale_time = (double)fi[index].milliseconds / (double)fi[index].cycles;

  return 1;
}

static int vert_first( float weights_table[STBIR_RESIZE_CLASSIFICATIONS][4], int ox, int oy, int ix, int iy, int filter, STBIR__V_FIRST_INFO * v_info )
{
  float h_scale=(float)ox/(float)(ix);
  float v_scale=(float)oy/(float)(iy);
  stbir__support_callback * support = stbir__builtin_supports[filter];
  int vertical_filter_width = stbir__get_filter_pixel_width(support,v_scale,0);
  int vertical_gather = ( v_scale >= ( 1.0f - stbir__small_float ) ) || ( vertical_filter_width <= STBIR_FORCE_GATHER_FILTER_SCANLINES_AMOUNT );

  return stbir__should_do_vertical_first( weights_table, stbir__get_filter_pixel_width(support,h_scale,0), h_scale, ox, vertical_filter_width, v_scale, oy, vertical_gather, v_info );
} 

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static void alloc_bitmap()
{
  int findex;
  int x = 0, y = 0;
  int w = 0, h = 0;

  for( findex = 0 ; findex < numfileinfo ; findex++ )
  {
    int nx, ny;
    int thisw, thish;

    thisw = ( fi[findex].dimensionx * fi[findex].numtypes ) + ( fi[findex].numtypes - 1 );
    thish = ( fi[findex].dimensiony * fi[findex].numinputrects ) + ( fi[findex].numinputrects - 1 );

    for(;;)
    {
      nx = x + ((x)?4:0) + thisw;
      ny = y + ((y)?4:0) + thish;
      if ( ( nx <= 3600 ) || ( x == 0 ) )
      { 
        fi[findex].bitmapx = x + ((x)?4:0);
        fi[findex].bitmapy = y + ((y)?4:0);
        x = nx;
        if ( x > w ) w = x;
        if ( ny > h ) h = ny;
        break;
      }
      else
      {
        x = 0;
        y = h;
      }
    }
  }

  w = (w+3) & ~3;
  bitmapw = w;
  bitmaph = h;
  bitmapp = w * 3; // RGB
  bitmap = malloc( bitmapp * bitmaph );

  memset( bitmap, 0, bitmapp * bitmaph );
}

static void build_bitmap( float weights[STBIR_RESIZE_CLASSIFICATIONS][4], int do_channel_count_index, int findex )
{
  static int colors[STBIR_RESIZE_CLASSIFICATIONS];
  STBIR__V_FIRST_INFO v_info = {0};

  int * ts;
  int ir;
  unsigned char * bitm = bitmap + ( fi[findex].bitmapx*3 ) + ( fi[findex].bitmapy*bitmapp) ;

  for( ir = 0; ir < STBIR_RESIZE_CLASSIFICATIONS ; ir++ ) colors[ ir ] = 127*ir/STBIR_RESIZE_CLASSIFICATIONS+128;

  ts = fi[findex].timings;

  for( ir = 0 ; ir < fi[findex].numinputrects ; ir++ )
  {
    int ix, iy, chanind;
    ix = fi[findex].inputrects[ir*2];
    iy = fi[findex].inputrects[ir*2+1];

    for( chanind = 0 ; chanind < fi[findex].numtypes ; chanind++ )
    {
      int ofs, h, hh;

      // just do the type that we're on
      if ( chanind != do_channel_count_index )
      {
        ts += 2 * fi[findex].dimensionx * fi[findex].dimensiony;
        continue;
      }

      // bitmap offset
      ofs=chanind*(fi[findex].dimensionx+1)*3+ir*(fi[findex].dimensiony+1)*bitmapp;

      h = 1;
      for( hh = 0 ; hh < fi[findex].dimensiony; hh++ )
      {
        int ww, w = 1;
        for( ww = 0 ; ww < fi[findex].dimensionx; ww++ )
        {
          int good, v_first, VF, HF;

          VF = ts[0];
          HF = ts[1];

          v_first = vert_first( weights, w, h, ix, iy, STBIR_FILTER_MITCHELL, &v_info );

          good = ( ((HF<=VF) && (!v_first)) || ((VF<=HF) && (v_first)));

          if ( good )
          {
            bitm[ofs+2] = 0;
            bitm[ofs+1] = (unsigned char)colors[v_info.v_resize_classification];
          }
          else
          {
            double r;

            if ( HF < VF )
              r = (double)(VF-HF)/(double)HF;
            else
              r = (double)(HF-VF)/(double)VF;
            
            if ( r > 0.4f) r = 0.4;
            r *= 1.0f/0.4f;   

            bitm[ofs+2] = (char)(255.0f*r);
            bitm[ofs+1] = (char)(((float)colors[v_info.v_resize_classification])*(1.0f-r));
          }
          bitm[ofs] = 0;

          ofs += 3;
          ts += 2;
          w += fi[findex].outputscalex;
        }
        ofs += bitmapp - fi[findex].dimensionx*3;
        h += fi[findex].outputscaley;
      }
    }
  }
}

static void build_comp_bitmap( float weights[STBIR_RESIZE_CLASSIFICATIONS][4], int do_channel_count_index )
{
  int * ts0;
  int * ts1;
  int ir;
  unsigned char * bitm = bitmap + ( fi[0].bitmapx*3 ) + ( fi[0].bitmapy*bitmapp) ;

  ts0 = fi[0].timings;
  ts1 = fi[1].timings;

  for( ir = 0 ; ir < fi[0].numinputrects ; ir++ )
  {
    int ix, iy, chanind;
    ix = fi[0].inputrects[ir*2];
    iy = fi[0].inputrects[ir*2+1];

    for( chanind = 0 ; chanind < fi[0].numtypes ; chanind++ )
    {
      int ofs, h, hh;

      // just do the type that we're on
      if ( chanind != do_channel_count_index )
      {
        ts0 += 2 * fi[0].dimensionx * fi[0].dimensiony;
        ts1 += 2 * fi[0].dimensionx * fi[0].dimensiony;
        continue;
      }

      // bitmap offset
      ofs=chanind*(fi[0].dimensionx+1)*3+ir*(fi[0].dimensiony+1)*bitmapp;

      h = 1;
      for( hh = 0 ; hh < fi[0].dimensiony; hh++ )
      {
        int ww, w = 1;
        for( ww = 0 ; ww < fi[0].dimensionx; ww++ )
        {
          int v_first, time0, time1;

          v_first = vert_first( weights, w, h, ix, iy, STBIR_FILTER_MITCHELL, 0 );

          time0 = ( v_first ) ? ts0[0] : ts0[1];
          time1 = ( v_first ) ? ts1[0] : ts1[1];

          if ( time0 < time1 )
          {
            double r = (double)(time1-time0)/(double)time0;
            if ( r > 0.4f) r = 0.4;
            r *= 1.0f/0.4f;   
            bitm[ofs+2] = 0;
            bitm[ofs+1] = (char)(255.0f*r);
            bitm[ofs] = (char)(64.0f*(1.0f-r));
          }
          else
          {
            double r = (double)(time0-time1)/(double)time1;
            if ( r > 0.4f) r = 0.4;
            r *= 1.0f/0.4f;   
            bitm[ofs+2] = (char)(255.0f*r);
            bitm[ofs+1] = 0;
            bitm[ofs] = (char)(64.0f*(1.0f-r));
          }
          ofs += 3;
          ts0 += 2;
          ts1 += 2;
          w += fi[0].outputscalex;
        }
        ofs += bitmapp - fi[0].dimensionx*3;
        h += fi[0].outputscaley;
      }
    }
  }
}

static void write_bitmap()
{
  stbi_write_png( "results.png", bitmapp / 3, bitmaph, 3|STB_IMAGE_BGR, bitmap, bitmapp );
}


static void calc_errors( float weights_table[STBIR_RESIZE_CLASSIFICATIONS][4], int * curtot, double * curerr, int do_channel_count_index )
{
  int th, findex;
  STBIR__V_FIRST_INFO v_info = {0};

  for(th=0;th<STBIR_RESIZE_CLASSIFICATIONS;th++)
  {
    curerr[th]=0;
    curtot[th]=0;
  }

  for( findex = 0 ; findex < numfileinfo ; findex++ )
  {
    int * ts;
    int ir;
    ts = fi[findex].timings;

    for( ir = 0 ; ir < fi[findex].numinputrects ; ir++ )
    {
      int ix, iy, chanind;
      ix = fi[findex].inputrects[ir*2];
      iy = fi[findex].inputrects[ir*2+1];

      for( chanind = 0 ; chanind < fi[findex].numtypes ; chanind++ )
      {
        int h, hh;

        // just do the type that we're on
        if ( chanind != do_channel_count_index )
        {
          ts += 2 * fi[findex].dimensionx * fi[findex].dimensiony;
          continue;
        }

        h = 1;
        for( hh = 0 ; hh < fi[findex].dimensiony; hh++ )
        {
          int ww, w = 1;
          for( ww = 0 ; ww < fi[findex].dimensionx; ww++ )
          {
            int good, v_first, VF, HF;

            VF = ts[0];
            HF = ts[1];

            v_first = vert_first( weights_table, w, h, ix, iy, STBIR_FILTER_MITCHELL, &v_info );

            good = ( ((HF<=VF) && (!v_first)) || ((VF<=HF) && (v_first)));

            if ( !good )
            {
              double diff;
              if ( VF < HF )
                diff = ((double)HF-(double)VF) * fi[findex].scale_time;
              else
                diff = ((double)VF-(double)HF) * fi[findex].scale_time;

              curtot[v_info.v_resize_classification] += 1;
              curerr[v_info.v_resize_classification] += diff;
            }

            ts += 2;
            w += fi[findex].outputscalex;
          }
          h += fi[findex].outputscaley;
        }
      }
    }
  }
}

#define TRIESPERWEIGHT 32
#define MAXRANGE ((TRIESPERWEIGHT+1) * (TRIESPERWEIGHT+1) * (TRIESPERWEIGHT+1) * (TRIESPERWEIGHT+1) - 1)

static void expand_to_floats( float * weights, int range )
{
  weights[0] = (float)( range % (TRIESPERWEIGHT+1) ) / (float)TRIESPERWEIGHT;
  weights[1] = (float)( range/(TRIESPERWEIGHT+1) % (TRIESPERWEIGHT+1) ) / (float)TRIESPERWEIGHT;
  weights[2] = (float)( range/(TRIESPERWEIGHT+1)/(TRIESPERWEIGHT+1) % (TRIESPERWEIGHT+1) ) / (float)TRIESPERWEIGHT;
  weights[3] = (float)( range/(TRIESPERWEIGHT+1)/(TRIESPERWEIGHT+1)/(TRIESPERWEIGHT+1) % (TRIESPERWEIGHT+1) ) / (float)TRIESPERWEIGHT;
}

static char const * expand_to_string( int range )
{
  static char str[128];
  int w0,w1,w2,w3;
  w0 = range % (TRIESPERWEIGHT+1);
  w1 = range/(TRIESPERWEIGHT+1) % (TRIESPERWEIGHT+1);
  w2 = range/(TRIESPERWEIGHT+1)/(TRIESPERWEIGHT+1) % (TRIESPERWEIGHT+1);
  w3 = range/(TRIESPERWEIGHT+1)/(TRIESPERWEIGHT+1)/(TRIESPERWEIGHT+1) % (TRIESPERWEIGHT+1);
  sprintf( str, "[ %2d/%d %2d/%d %2d/%d %2d/%d ]",w0,TRIESPERWEIGHT,w1,TRIESPERWEIGHT,w2,TRIESPERWEIGHT,w3,TRIESPERWEIGHT );
  return str;
}

static void print_weights( float weights[STBIR_RESIZE_CLASSIFICATIONS][4], int channel_count_index, int * tots, double * errs )
{
  int th;
  printf("ChInd: %d  Weights:\n",channel_count_index);
  for(th=0;th<STBIR_RESIZE_CLASSIFICATIONS;th++)
  {
    float * w = weights[th];
    printf("  %d: [%1.5f %1.5f %1.5f %1.5f] (%d %.4f)\n",th, w[0], w[1], w[2], w[3], tots[th], errs[th] );
  }
  printf("\n");
}

static int windowranges[ 16 ];
static int windowstatus = 0;
static DWORD trainstart = 0;

static void opt_channel( float best_output_weights[STBIR_RESIZE_CLASSIFICATIONS][4], int channel_count_index )
{
  int newbest = 0;
  float weights[STBIR_RESIZE_CLASSIFICATIONS][4] = {0};
  double besterr[STBIR_RESIZE_CLASSIFICATIONS];
  int besttot[STBIR_RESIZE_CLASSIFICATIONS];
  int best[STBIR_RESIZE_CLASSIFICATIONS]={0};

  double curerr[STBIR_RESIZE_CLASSIFICATIONS];
  int curtot[STBIR_RESIZE_CLASSIFICATIONS];
  int th, range;
  DWORD lasttick = 0;

  for(th=0;th<STBIR_RESIZE_CLASSIFICATIONS;th++) 
  {
    besterr[th]=1000000000000.0;
    besttot[th]=0x7fffffff;
  }

  newbest = 0;

  // try the whole range  
  range = MAXRANGE;
  do
  {
    for(th=0;th<STBIR_RESIZE_CLASSIFICATIONS;th++)
      expand_to_floats( weights[th], range );

    calc_errors( weights, curtot, curerr, channel_count_index );

    for(th=0;th<STBIR_RESIZE_CLASSIFICATIONS;th++)
    {
      if ( curerr[th] < besterr[th] )
      {
        besterr[th] = curerr[th];
        besttot[th] = curtot[th];
        best[th] = range;
        expand_to_floats( best_output_weights[th], best[th] );
        newbest = 1;
      }
    }

    {
      DWORD t = GetTickCount();
      if ( range == 0 )
        goto do_bitmap;

      if ( newbest )
      {
        if ( ( GetTickCount() - lasttick ) > 200 )
        {
          int findex;
        
         do_bitmap:
          lasttick = t;
          newbest = 0;

          for( findex = 0 ; findex < numfileinfo ; findex++ )
            build_bitmap( best_output_weights, channel_count_index, findex );

          lasttick = GetTickCount();
        }
      }
    }
   
    windowranges[ channel_count_index ] = range;

    // advance all the weights and loop
    --range;
  } while( ( range >= 0 ) && ( !windowstatus ) );

  // if we hit here, then we tried all weights for this opt, so save them 
}

static void print_struct( float weight[5][STBIR_RESIZE_CLASSIFICATIONS][4], char const * name )
{
  printf("\n\nstatic float %s[5][STBIR_RESIZE_CLASSIFICATIONS][4]=\n{", name );
  {
    int i;
    for(i=0;i<5;i++) 
    { 
      int th;
      for(th=0;th<STBIR_RESIZE_CLASSIFICATIONS;th++)
      {
        int j;
        printf("\n  "); 
        for(j=0;j<4;j++) 
          printf("%1.5ff, ", weight[i][th][j] ); 
      }
      printf("\n");
    }
    printf("\n};\n");
  }
}

static float retrain_weights[5][STBIR_RESIZE_CLASSIFICATIONS][4];

static DWORD __stdcall retrain_shim( LPVOID p )
{
  int chanind = (int) (size_t)p;
  opt_channel( retrain_weights[chanind], chanind );
  return 0;
}

static char const * gettime( int ms )
{
  static char time[32];
  if (ms > 60000)
    sprintf( time, "%dm %ds",ms/60000, (ms/1000)%60 );
  else  
    sprintf( time, "%ds",ms/1000 );
  return time;
}

static BITMAPINFOHEADER bmiHeader;
static DWORD extrawindoww, extrawindowh;
static HINSTANCE instance;
static int curzoom = 1;

static LRESULT WINAPI WindowProc( HWND   window,
                                  UINT   message,
                                  WPARAM wparam,
                                  LPARAM lparam )
{
  switch( message )
  {
    case WM_CHAR:
      if ( wparam != 27 )
        break;
      // falls through

    case WM_CLOSE:
    {
      int i;
      int max = 0;
      
      for( i = 0 ; i < fi[0].numtypes ; i++ )
        if( windowranges[i] > max ) max = windowranges[i];
   
      if ( ( max == 0 ) || ( MessageBox( window, "Cancel before training is finished?", "Vertical First Training", MB_OKCANCEL|MB_ICONSTOP ) == IDOK ) )
      {
        for( i = 0 ; i < fi[0].numtypes ; i++ )
          if( windowranges[i] > max ) max = windowranges[i];
        if ( max )
          windowstatus = 1;
        DestroyWindow( window );
      }
    }
    return 0;
       
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC dc;

      dc = BeginPaint( window, &ps );
      StretchDIBits( dc, 
        0, 0, bitmapw*curzoom, bitmaph*curzoom,
        0, 0, bitmapw, bitmaph,
        bitmap, (BITMAPINFO*)&bmiHeader, DIB_RGB_COLORS, SRCCOPY );

      PatBlt( dc, bitmapw*curzoom, 0, 4096, 4096, WHITENESS );
      PatBlt( dc, 0, bitmaph*curzoom, 4096, 4096, WHITENESS );

      SetTextColor( dc, RGB(0,0,0)  );
      SetBkColor( dc, RGB(255,255,255) );
      SetBkMode( dc, OPAQUE );

      {
        int i, l = 0, max = 0;
        char buf[1024];
        RECT rc;
        POINT p;

        for( i = 0 ; i < fi[0].numtypes ; i++ )
        {
          l += sprintf( buf + l, "channels: %d %s\n", fi[0].effective[i], windowranges[i] ? expand_to_string( windowranges[i] ) : "Done." );
          if ( windowranges[i] > max ) max = windowranges[i];
        }

        rc.left = 32; rc.top = bitmaph*curzoom+10;
        rc.right = 512; rc.bottom = rc.top + 512;
        DrawText( dc, buf, -1, &rc, DT_TOP );

        l = 0;
        if ( max == 0 )
        {
          static DWORD traindone = 0;
          if ( traindone == 0 ) traindone = GetTickCount();
          l = sprintf( buf, "Finished in %s.", gettime( traindone - trainstart ) );
        }
        else if ( max != MAXRANGE )
          l = sprintf( buf, "Done in %s...", gettime( (int) ( ( ( (int64)max * ( (int64)GetTickCount() - (int64)trainstart ) ) ) / (int64) ( MAXRANGE - max ) ) ) );

        GetCursorPos( &p );
        ScreenToClient( window, &p );

        if ( ( p.x >= 0 ) && ( p.y >= 0 ) && ( p.x < (bitmapw*curzoom) ) && ( p.y < (bitmaph*curzoom) ) )
        {
          int findex;
          int x, y, w, h, sx, sy, ix, iy, ox, oy;
          int ir, chanind;
          int * ts;
          char badstr[64];
          STBIR__V_FIRST_INFO v_info={0};

          p.x /= curzoom;
          p.y /= curzoom;

          for( findex = 0 ; findex < numfileinfo ; findex++ )
          {
            x = fi[findex].bitmapx;
            y = fi[findex].bitmapy;
            w = x + ( fi[findex].dimensionx + 1 ) * fi[findex].numtypes;
            h = y + ( fi[findex].dimensiony + 1 ) * fi[findex].numinputrects;

            if ( ( p.x >= x ) && ( p.y >= y ) && ( p.x < w ) && ( p.y < h ) )
              goto found;
          }
          goto nope;
         
         found:
            
          ir = ( p.y - y ) / ( fi[findex].dimensiony + 1 );
          sy = ( p.y - y ) % ( fi[findex].dimensiony + 1 );
          if ( sy >= fi[findex].dimensiony ) goto nope;

          chanind = ( p.x - x ) / ( fi[findex].dimensionx + 1 );
          sx = ( p.x - x ) % ( fi[findex].dimensionx + 1 );
          if ( sx >= fi[findex].dimensionx ) goto nope;

          ix = fi[findex].inputrects[ir*2];
          iy = fi[findex].inputrects[ir*2+1];

          ts = fi[findex].timings + ( ( fi[findex].dimensionx * fi[findex].dimensiony * fi[findex].numtypes * ir ) + ( fi[findex].dimensionx * fi[findex].dimensiony * chanind ) + ( fi[findex].dimensionx * sy ) + sx ) * 2;

          ox = 1+fi[findex].outputscalex*sx;
          oy = 1+fi[findex].outputscaley*sy;

          if ( windowstatus != 2 )
          {
            int VF, HF, v_first, good;
            VF = ts[0];
            HF = ts[1];

            v_first = vert_first( retrain_weights[chanind], ox, oy, ix, iy, STBIR_FILTER_MITCHELL, &v_info );

            good = ( ((HF<=VF) && (!v_first)) || ((VF<=HF) && (v_first)));

            if ( good )
              badstr[0] = 0;
            else
            {
              double r;

              if ( HF < VF )
                r = (double)(VF-HF)/(double)HF;
              else
                r = (double)(HF-VF)/(double)VF;
              sprintf( badstr, " %.1f%% off", r*100 );
            }
            sprintf( buf + l, "\n\n%s\nCh: %d Resize: %dx%d to %dx%d\nV: %d H: %d  Order: %c (%s%s)\nClass: %d Scale: %.2f %s", fi[findex].filename,fi[findex].effective[chanind], ix,iy,ox,oy, VF, HF, v_first?'V':'H', good?"Good":"Wrong", badstr, v_info.v_resize_classification, (double)oy/(double)iy, v_info.is_gather ? "Gather" : "Scatter" );
          }
          else
          {
            int v_first, time0, time1;
            float (* weights)[4] = stbir__compute_weights[chanind];
            int * ts1;
            char b0[32], b1[32];

            ts1 = fi[1].timings + ( ts - fi[0].timings );

            v_first = vert_first( weights, ox, oy, ix, iy, STBIR_FILTER_MITCHELL, &v_info );

            time0 = ( v_first ) ? ts[0] : ts[1];
            time1 = ( v_first ) ? ts1[0] : ts1[1];
            
            b0[0] = b1[0] = 0;
            if ( time0 < time1 )
              sprintf( b0," (%.f%% better)", ((double)time1-(double)time0)*100.0f/(double)time0);
            else
              sprintf( b1," (%.f%% better)", ((double)time0-(double)time1)*100.0f/(double)time1);

            sprintf( buf + l, "\n\n0: %s\n1: %s\nCh: %d Resize: %dx%d to %dx%d\nClass: %d Scale: %.2f %s\nTime0: %d%s\nTime1: %d%s", fi[0].filename, fi[1].filename, fi[0].effective[chanind], ix,iy,ox,oy, v_info.v_resize_classification, (double)oy/(double)iy, v_info.is_gather ? "Gather" : "Scatter", time0, b0, time1, b1 );
          }
        }
       nope:

        rc.left = 32+320; rc.right = 512+320; 
        SetTextColor( dc, RGB(0,0,128) );
        DrawText( dc, buf, -1, &rc, DT_TOP );

      }
      EndPaint( window, &ps );
      return 0;
    }

    case WM_TIMER:
      InvalidateRect( window, 0, 0 );
      return 0;

    case WM_DESTROY:
      PostQuitMessage( 0 );
      return 0;
  }
   

  return DefWindowProc( window, message, wparam, lparam );
}

static void SetHighDPI(void)
{
  typedef HRESULT WINAPI setdpitype(int v);
  HMODULE h=LoadLibrary("Shcore.dll");
  if (h)
  {
    setdpitype * sd = (setdpitype*)GetProcAddress(h,"SetProcessDpiAwareness");
    if (sd )
      sd(1);
  }
} 

static void draw_window()
{
  WNDCLASS wc;
  HWND w;
  MSG msg;
  
  instance = GetModuleHandle(NULL);

  wc.style = 0;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = instance;
  wc.hIcon = 0;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = 0;
  wc.lpszMenuName = 0;
  wc.lpszClassName = "WHTrain";

  if ( !RegisterClass( &wc ) )
    exit(1);

  SetHighDPI();

  bmiHeader.biSize          =  sizeof(BITMAPINFOHEADER);
  bmiHeader.biWidth         =  bitmapp/3;
  bmiHeader.biHeight        =  -bitmaph;
  bmiHeader.biPlanes        =  1;
  bmiHeader.biBitCount      =  24;
  bmiHeader.biCompression   =  BI_RGB;

  w = CreateWindow( "WHTrain",
                    "Vertical First Training",
                    WS_CAPTION | WS_POPUP| WS_CLIPCHILDREN |
                    WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX,
                    CW_USEDEFAULT,CW_USEDEFAULT,
                    CW_USEDEFAULT,CW_USEDEFAULT,
                    0, 0, instance, 0 );

  {
    RECT r, c;
    GetWindowRect( w, &r );
    GetClientRect( w, &c );
    extrawindoww = ( r.right - r.left ) - ( c.right - c.left );
    extrawindowh = ( r.bottom - r.top ) - ( c.bottom - c.top );
    SetWindowPos( w, 0, 0, 0, bitmapw * curzoom + extrawindoww, bitmaph * curzoom + extrawindowh + 164, SWP_NOMOVE );
  }

  ShowWindow( w, SW_SHOWNORMAL );
  SetTimer( w, 1, 250, 0 );

  {
    BOOL ret;
    while( ( ret = GetMessage( &msg, w, 0, 0 ) ) != 0 )
    { 
      if ( ret == -1 )
        break;
      TranslateMessage( &msg ); 
      DispatchMessage( &msg ); 
    }
  }
}

static void retrain()
{
  HANDLE threads[ 16 ];
  int chanind;

  trainstart = GetTickCount();
  for( chanind = 0 ; chanind < fi[0].numtypes ; chanind++ )
    threads[ chanind ] = CreateThread( 0, 2048*1024, retrain_shim, (LPVOID)(size_t)chanind, 0, 0 );

  draw_window();

  for( chanind = 0 ; chanind < fi[0].numtypes ; chanind++ )
  {
    WaitForSingleObject( threads[ chanind ], INFINITE );
    CloseHandle( threads[ chanind ] );
  }

  write_bitmap();

  print_struct( retrain_weights, "retained_weights" );
  if ( windowstatus ) printf( "CANCELLED!\n" );
}

static void info()
{
  int findex;

  // display info about each input file
  for( findex = 0 ; findex < numfileinfo ; findex++ )
  {
    int i, h,m,s;
    if ( findex ) printf( "\n" );
    printf( "Timing file: %s\n", fi[findex].filename );
    printf( "CPU type: %d  %s\n", fi[findex].cpu, fi[findex].simd?(fi[findex].simd==2?"SIMD8":"SIMD4"):"Scalar" );
    h = fi[findex].milliseconds/3600000;
    m = (fi[findex].milliseconds-h*3600000)/60000;
    s = (fi[findex].milliseconds-h*3600000-m*60000)/1000;
    printf( "Total time in test: %dh %dm %ds  Cycles/sec: %.f\n", h,m,s, 1000.0/fi[findex].scale_time );
    printf( "Each tile of samples is %dx%d, and is scaled by %dx%d.\n", fi[findex].dimensionx,fi[findex].dimensiony, fi[findex].outputscalex,fi[findex].outputscaley );
    printf( "So the x coords are: " );
    for( i=0; i < fi[findex].dimensionx ; i++ ) printf( "%d ",1+i*fi[findex].outputscalex );
    printf( "\n" );
    printf( "And the y coords are: " );
    for( i=0; i < fi[findex].dimensiony ; i++ ) printf( "%d ",1+i*fi[findex].outputscaley );
    printf( "\n" );
    printf( "There are %d channel counts and they are: ", fi[findex].numtypes );
    for( i=0; i < fi[findex].numtypes ; i++ ) printf( "%d ",fi[findex].effective[i] );
    printf( "\n" );
    printf( "There are %d input rect sizes and they are: ", fi[findex].numinputrects );
    for( i=0; i < fi[findex].numtypes ; i++ ) printf( "%dx%d ",fi[findex].inputrects[i*2],fi[findex].inputrects[i*2+1] );
    printf( "\n" );
  }
}

static void current( int do_win, int do_bitmap )
{
  int i, findex;

  trainstart = GetTickCount();

  // clear progress
  memset( windowranges, 0, sizeof( windowranges ) );
  // copy in appropriate weights
  memcpy( retrain_weights, stbir__compute_weights, sizeof( retrain_weights ) );

  // build and print current errors and build current bitmap
  for( i = 0 ; i < fi[0].numtypes ; i++ )
  {
    double curerr[STBIR_RESIZE_CLASSIFICATIONS];
    int curtot[STBIR_RESIZE_CLASSIFICATIONS];
    float (* weights)[4] = retrain_weights[i];
 
    calc_errors( weights, curtot, curerr, i );
    if ( !do_bitmap )
      print_weights( weights, i, curtot, curerr );

    for( findex = 0 ; findex < numfileinfo ; findex++ )
      build_bitmap( weights, i, findex );
  }

  if ( do_win )
    draw_window();

  if ( do_bitmap )
    write_bitmap();
}

static void compare()
{
  int i;

  trainstart = GetTickCount();
  windowstatus = 2; // comp mode

  // clear progress
  memset( windowranges, 0, sizeof( windowranges ) );

  if ( ( fi[0].numtypes != fi[1].numtypes ) || ( fi[0].numinputrects != fi[1].numinputrects ) ||
       ( fi[0].dimensionx != fi[1].dimensionx ) || ( fi[0].dimensiony != fi[1].dimensiony ) || 
       ( fi[0].outputscalex != fi[1].outputscalex ) || ( fi[0].outputscaley != fi[1].outputscaley ) )
  {
   err:
    printf( "Timing files don't match.\n" );
    exit(5);
  }

  for( i=0; i < fi[0].numtypes ; i++ )
  {
    if ( fi[0].effective[i]      != fi[1].effective[i] ) goto err;
    if ( fi[0].inputrects[i*2]   != fi[1].inputrects[i*2] ) goto err;
    if ( fi[0].inputrects[i*2+1] != fi[1].inputrects[i*2+1] ) goto err;
  }
    
  alloc_bitmap( 1 );
  
  for( i = 0 ; i < fi[0].numtypes ; i++ )
  {
    float (* weights)[4] = stbir__compute_weights[i];
    build_comp_bitmap( weights, i );
  }

  draw_window();
}

static void load_files( char ** args, int count )
{
  int i;

  if ( count == 0 )
  {
    printf( "No timing files listed!" );
    exit(3);
  }

  for ( i = 0 ; i < count ; i++ )
  {
    if ( !use_timing_file( args[i], i ) )
    {
      printf( "Bad timing file %s\n", args[i] );
      exit(2);
    }
  }
  numfileinfo = count;
}  

int main( int argc, char ** argv )
{
  int check;
  if ( argc < 3 )
  {
   err:
    printf( "vf_train retrain [timing_filenames....] - recalcs weights for all the files on the command line.\n");
    printf( "vf_train info [timing_filenames....] - shows info about each timing file.\n");
    printf( "vf_train check [timing_filenames...] - show results for the current weights for all files listed.\n");
    printf( "vf_train compare <timing file1> <timing file2> - compare two timing files (must only be two files and same resolution).\n");
    printf( "vf_train bitmap [timing_filenames...] - write out results.png, comparing against the current weights for all files listed.\n");
    exit(1);
  }
  
  check = ( strcmp( argv[1], "check" ) == 0 );
  if ( ( check ) || ( strcmp( argv[1], "bitmap" ) == 0 ) )
  {
    load_files( argv + 2, argc - 2 );
    alloc_bitmap( numfileinfo );
    current( check, !check );
  }
  else if ( strcmp( argv[1], "info" ) == 0 ) 
  {
    load_files( argv + 2, argc - 2 );
    info();
  }
  else if ( strcmp( argv[1], "compare" ) == 0 ) 
  {
    if ( argc != 4 )
    {
      printf( "You must specify two files to compare.\n" );
      exit(4);
    }

    load_files( argv + 2, argc - 2 );
    compare();
  }
  else if ( strcmp( argv[1], "retrain" ) == 0 ) 
  {
    load_files( argv + 2, argc - 2 );
    alloc_bitmap( numfileinfo );
    retrain();  
  }
  else
  {
    goto err;
  }

  return 0;
}
