#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define HEAVYTM
#include "tm.h"

#ifdef RADUSETM3
tm_api * g_tm_api;
//#define PROFILE_MODE
#endif

#include <math.h>

#ifdef _MSC_VER
#define stop() __debugbreak()
#include <windows.h>
#define int64 __int64
#define uint64 unsigned __int64
#else
#define stop() __builtin_trap()
#define int64 long long
#define uint64 unsigned long long
#endif

#ifdef _MSC_VER
#pragma warning(disable:4127)
#endif

//#define NOCOMP


//#define PROFILE_NEW_ONLY
//#define PROFILE_MODE


#if defined(_x86_64) || defined( __x86_64__ ) || defined( _M_X64 ) || defined(__x86_64) || defined(__SSE2__) || defined(STBIR_SSE) || defined( _M_IX86_FP ) || defined(__i386) || defined( __i386__ ) || defined( _M_IX86 ) || defined( _X86_ )

#ifdef _MSC_VER

  uint64 __rdtsc();
  #define __cycles() __rdtsc()

#else // non msvc

  static inline uint64 __cycles() 
  {
    unsigned int lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi) );
    return ( ( (uint64) hi ) << 32 ) | ( (uint64) lo );
  }

#endif  // msvc

#elif defined( _M_ARM64 ) || defined( __aarch64__ ) || defined( __arm64__ ) || defined(__ARM_NEON__) 

#ifdef _MSC_VER

  #define __cycles() _ReadStatusReg(ARM64_CNTVCT)

#else

  static inline uint64 __cycles()
  {
    uint64 tsc;
    asm volatile("mrs %0, cntvct_el0" : "=r" (tsc));
    return tsc;
  }

#endif

#else // x64, arm

#error Unknown platform for timing.

#endif  //x64 and   


#ifdef PROFILE_MODE

#define STBIR_ASSERT(cond)

#endif

#ifdef _DEBUG
#undef STBIR_ASSERT
#define STBIR_ASSERT(cond) { if (!(cond)) stop(); }
#endif


#define SHRINKBYW 2
#define ZOOMBYW 2
#define SHRINKBYH 2
#define ZOOMBYH 2


int mem_count = 0;

#ifdef TEST_WITH_VALLOC

#define STBIR__SEPARATE_ALLOCATIONS

#if TEST_WITH_LIMIT_AT_FRONT

  void * wmalloc(SIZE_T size)
  {
     static unsigned int pagesize=0;
     void* p;
     SIZE_T s;

     // get the page size, if we haven't yet
     if (pagesize==0)
     {
       SYSTEM_INFO si;
       GetSystemInfo(&si);
       pagesize=si.dwPageSize;
     }

     // we need room for the size, 8 bytes to hide the original pointer and a
     //   validation dword, and enough data to completely fill one page
     s=(size+(pagesize-1))&~(pagesize-1);

     // allocate the size plus a page (for the guard)
     p=VirtualAlloc(0,(SIZE_T)s,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
     
     return p;
   }

  void wfree(void * ptr)
  {
    if (ptr)
    {
      if ( ((ptrdiff_t)ptr) & 4095 ) stop();
      if ( VirtualFree(ptr,0,MEM_RELEASE) == 0 ) stop();
    }
  }

#else

  void * wmalloc(SIZE_T size)
  {
     static unsigned int pagesize=0;
     void* p;
     SIZE_T s;

     // get the page size, if we haven't yet
     if (pagesize==0)
     {
       SYSTEM_INFO si;
       GetSystemInfo(&si);
       pagesize=si.dwPageSize;
     }

     // we need room for the size, 8 bytes to hide the original pointer and a
     //   validation dword, and enough data to completely fill one page
     s=(size+16+(pagesize-1))&~(pagesize-1);

     // allocate the size plus a page (for the guard)
     p=VirtualAlloc(0,(SIZE_T)(s+pagesize+pagesize),MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);

     if (p)
     {
       DWORD oldprot;
       void* orig=p;

       // protect the first page
       VirtualProtect(((char*)p),pagesize,PAGE_NOACCESS,&oldprot);

       // protect the final page
       VirtualProtect(((char*)p)+s+pagesize,pagesize,PAGE_NOACCESS,&oldprot);

       // now move the returned pointer so that it bumps right up against the
       //   the next (protected) page (this may result in unaligned return
       //   addresses - pre-align the sizes if you always want aligned ptrs)
//#define ERROR_ON_FRONT
#ifdef ERROR_ON_FRONT
       p=((char*)p)+pagesize+16;
#else
       p=((char*)p)+(s-size)+pagesize;
#endif

       // hide the validation value and the original pointer (which we'll
       //   need used for freeing) right behind the returned pointer
       ((unsigned int*)p)[-1]=0x98765432;
       ((void**)p)[-2]=orig;
       ++mem_count;
//printf("aloc: %p bytes: %d\n",p,(int)size);
       return(p);
     }

     return 0;
  }

  void wfree(void * ptr)
  {
    if (ptr)
    {
      int err=0;

      // is this one of our allocations?
      if (((((unsigned int*)ptr)[-1])!=0x98765432) || ((((void**)ptr)[-2])==0))
      {
        err=1;
      }

      if (err)
      {
        __debugbreak();
      }
      else
      {

        // back up to find the original pointer
        void* p=((void**)ptr)[-2];

        // clear the validation value and the original pointer
        ((unsigned int*)ptr)[-1]=0;
        ((void**)ptr)[-2]=0;

//printf("free: %p\n",ptr);

        --mem_count;

        // now free the pages
        if (p)
          VirtualFree(p,0,MEM_RELEASE);

      }
    }
  }

#endif

#define STBIR_MALLOC(size,user_data) ((void)(user_data), wmalloc(size))
#define STBIR_FREE(ptr,user_data)    ((void)(user_data), wfree(ptr))

#endif

#define STBIR_PROFILE
//#define STBIR_NO_SIMD
//#define STBIR_AVX
//#define STBIR_AVX2
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"  // new one!

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int tsizes[5] =   { 1, 1, 2, 4, 2 };
int ttypes[5] =   { STBIR_TYPE_UINT8, STBIR_TYPE_UINT8_SRGB, STBIR_TYPE_UINT16, STBIR_TYPE_FLOAT, STBIR_TYPE_HALF_FLOAT };

int cedges[4] =   { STBIR_EDGE_CLAMP, STBIR_EDGE_REFLECT, STBIR_EDGE_ZERO, STBIR_EDGE_WRAP };
int flts[5] =     { STBIR_FILTER_BOX, STBIR_FILTER_TRIANGLE, STBIR_FILTER_CUBICBSPLINE, STBIR_FILTER_CATMULLROM, STBIR_FILTER_MITCHELL };
int buffers[20] = { STBIR_1CHANNEL, STBIR_2CHANNEL, STBIR_RGB, STBIR_4CHANNEL, 
                    STBIR_BGRA, STBIR_ARGB, STBIR_RA, STBIR_AR,
                    STBIR_RGBA_PM, STBIR_ARGB_PM, STBIR_RA_PM, STBIR_AR_PM,
                    STBIR_RGBA, STBIR_ARGB, STBIR_RA, STBIR_AR,
                    STBIR_RGBA_PM, STBIR_ARGB_PM, STBIR_RA_PM, STBIR_AR_PM,
                  };
int obuffers[20] = { STBIR_1CHANNEL, STBIR_2CHANNEL, STBIR_RGB, STBIR_4CHANNEL, 
                     STBIR_BGRA, STBIR_ARGB, STBIR_RA, STBIR_AR,
                     STBIR_RGBA_PM, STBIR_ARGB_PM, STBIR_RA_PM, STBIR_AR_PM,
                     STBIR_RGBA_PM, STBIR_ARGB_PM, STBIR_RA_PM, STBIR_AR_PM,
                     STBIR_RGBA, STBIR_ARGB, STBIR_RA, STBIR_AR,
                   };

int bchannels[20] = { 1, 2, 3, 4,  4,4, 2,2,  4,4, 2,2,  4,4, 2,2,  4,4, 2,2  }; 
int alphapos[20] = { -1, -1, -1, -1,  3,0,  1,0,   3,0,  1,0,   3,0,  1,0,3,0,  1,0 }; 


char const * buffstrs[20] = { "1ch", "2ch", "3ch", "4ch",  "RGBA", "ARGB", "RA", "AR",  "RGBA_both_pre", "ARGB_both_pre", "RA_both_pre", "AR_both_pre",  "RGBA_out_pre", "ARGB_out_pre", "RA_out_pre", "AR_out_pre",  "RGBA_in_pre", "ARGB_in_pre", "RA_in_pre", "AR_in_pre" };
char const * typestrs[5] =  { "Bytes", "BytesSRGB", "Shorts", "Floats", "Half Floats"};
char const * edgestrs[4] =  { "Clamp", "Reflect", "Zero", "Wrap" };
char const * fltstrs[5] =   { "Box", "Triangle", "Cubic", "Catmullrom", "Mitchell" };

#ifdef STBIR_PROFILE
  static void do_acc_zones( STBIR_PROFILE_INFO * profile )
  {
    stbir_uint32 j;
    stbir_uint64 start = tmGetAccumulationStart( tm_mask ); start=start;

    for( j = 0 ; j < profile->count ; j++ )
    {
      if ( profile->clocks[j] )
        tmEmitAccumulationZone( 0, 0, (tm_uint64*)&start, 0, profile->clocks[j], profile->descriptions[j] );
    }
  }
#else
  #define do_acc_zones(...)
#endif

int64 vert;

//#define WINTHREADTEST
#ifdef WINTHREADTEST

static STBIR_RESIZE * thread_resize;
static LONG which;
static int threads_started = 0;
static HANDLE threads[32];
static HANDLE starts,stops;
  
static DWORD resize_shim( LPVOID p )
{
  for(;;)
  {
    LONG wh;

    WaitForSingleObject( starts, INFINITE );

    wh = InterlockedAdd( &which, 1 ) - 1;

    ENTER( "Split %d", wh );
    stbir_resize_split( thread_resize, wh, 1 );
  #ifdef STBIR_PROFILE
    { STBIR_PROFILE_INFO profile; stbir_resize_split_profile_info( &profile, thread_resize, wh, 1 ); do_acc_zones( &profile ); vert = profile.clocks[1]; }
  #endif
    LEAVE();

    ReleaseSemaphore( stops, 1, 0 );
  }
}

#endif

void nresize( void * o, int ox, int oy, int op, void * i, int ix, int iy, int ip, int buf, int type, int edg, int flt )
{
  STBIR_RESIZE resize;
 
  stbir_resize_init( &resize, i, ix, iy, ip, o, ox, oy, op, buffers[buf], ttypes[type] );
  stbir_set_pixel_layouts( &resize, buffers[buf], obuffers[buf] );
  stbir_set_edgemodes( &resize, cedges[edg], cedges[edg] );
  stbir_set_filters( &resize, flts[flt], /*STBIR_FILTER_POINT_SAMPLE */ flts[flt] );
  //stbir_set_input_subrect( &resize, 0.55f,0.333f,0.75f,0.50f);
  //stbir_set_output_pixel_subrect( &resize, 00, 00, ox/2,oy/2);
  //stbir_set_pixel_subrect(&resize, 1430,1361,30,30);
  
  ENTER( "Resize" );
 
  #ifndef WINTHREADTEST

  ENTER( "Filters" );
  stbir_build_samplers_with_splits( &resize, 1 );
  #ifdef STBIR_PROFILE
    { STBIR_PROFILE_INFO profile; stbir_resize_build_profile_info( &profile, &resize ); do_acc_zones( &profile ); }
  #endif
  LEAVE();
 
  ENTER( "Resize" );
  if(!stbir_resize_extended( &resize ) )
    stop();
  #ifdef STBIR_PROFILE
    { STBIR_PROFILE_INFO profile; stbir_resize_extended_profile_info( &profile, &resize ); do_acc_zones( &profile ); vert = profile.clocks[1]; }
  #endif
  LEAVE();

  #else
  {
    int c, cnt;
 
    ENTER( "Filters" );
    cnt =  stbir_build_samplers_with_splits( &resize, 4 );
    #ifdef STBIR_PROFILE
      { STBIR_PROFILE_INFO profile; stbir_resize_build_profile_info( &profile, &resize ); do_acc_zones( &profile ); }
    #endif
    LEAVE();
    
    ENTER( "Thread start" );
    if ( threads_started == 0 )
    {
      starts = CreateSemaphore( 0, 0, 32, 0 );
      stops = CreateSemaphore( 0, 0, 32, 0 );
    }
    for( c = threads_started ; c < cnt ; c++ )
      threads[ c ] = CreateThread( 0, 2048*1024, resize_shim, 0, 0, 0 );
    
    threads_started = cnt;
    thread_resize = &resize;
    which = 0;
    LEAVE();

    // starts the threads
    ReleaseSemaphore( starts, cnt, 0 );

    ENTER( "Wait" );
    for( c = 0 ; c < cnt; c++ )
      WaitForSingleObject( stops, INFINITE );
    LEAVE();
  }
  #endif

  ENTER( "Free" );
  stbir_free_samplers( &resize );
  LEAVE();
  LEAVE();
}


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern void oresize( void * o, int ox, int oy, int op, void * i, int ix, int iy, int ip, int buf, int type, int edg, int flt );



#define TYPESTART 0
#define TYPEEND   4

#define LAYOUTSTART  0
#define LAYOUTEND   19

#define SIZEWSTART 0
#define SIZEWEND   2

#define SIZEHSTART 0
#define SIZEHEND   2

#define EDGESTART 0
#define EDGEEND   3

#define FILTERSTART 0
#define FILTEREND   4

#define HEIGHTSTART 0
#define HEIGHTEND   2

#define WIDTHSTART 0
#define WIDTHEND   2




static void * convert8to16( unsigned char * i, int w, int h, int c )
{
  unsigned short * ret;
  int p;

  ret = malloc( w*h*c*sizeof(short) );
  for(p = 0 ; p < (w*h*c) ; p++ )
  {
    ret[p]=(short)((((int)i[p])<<8)+i[p]);
  }

  return ret;
}

static void * convert8tof( unsigned char * i, int w, int h, int c )
{
  float * ret;
  int p;

  ret = malloc( w*h*c*sizeof(float) );
  for(p = 0 ; p < (w*h*c) ; p++ )
  {
    ret[p]=((float)i[p])*(1.0f/255.0f);
  }

  return ret;
}

static void * convert8tohf( unsigned char * i, int w, int h, int c )
{
  stbir__FP16 * ret;
  int p;

  ret = malloc( w*h*c*sizeof(stbir__FP16) );
  for(p = 0 ; p < (w*h*c) ; p++ )
  {
    ret[p]=stbir__float_to_half(((float)i[p])*(1.0f/255.0f));
  }

  return ret;
}

static void * convert8tohff( unsigned char * i, int w, int h, int c )
{
  float * ret;
  int p;

  ret = malloc( w*h*c*sizeof(float) );
  for(p = 0 ; p < (w*h*c) ; p++ )
  {
    ret[p]=stbir__half_to_float(stbir__float_to_half(((float)i[p])*(1.0f/255.0f)));
  }

  return ret;
}

static int isprime( int v )
{
  int i;

  if ( v <= 3 )
    return ( v > 1 );
  if ( ( v & 1 ) == 0 )
    return 0;
  if ( ( v % 3 ) == 0 )
    return 0;
  i = 5;
  while ( (i*i) <= v )
  {
    if ( ( v % i ) == 0 )
      return 0;
    if ( ( v % ( i + 2 ) ) == 0 )
      return 0;
    i += 6;
  }

  return 1;
}

static int getprime( int v )
{
  int i;
  i = 0;
  for(;;)
  {
    if ( i >= v )
      return v;  // can't find any, just return orig
    if (isprime(v - i))
      return v - i;
    if (isprime(v + i))
      return v + i;
    ++i;
  }
}


int main( int argc, char ** argv )
{
  int ix, iy, ic;
  unsigned char * input[6];
  char * ir1;
  char * ir2;
  int szhs[3];
  int szws[3];
  int aw, ah, ac;
  unsigned char * correctalpha;
  int layouts, types, heights, widths, edges, filters;

  if ( argc != 2 )
  {
    printf("command: stbirtest [imagefile]\n");
    exit(1);
  }

  SetupTM( "127.0.0.1" );

  correctalpha = stbi_load( "correctalpha.png", &aw, &ah, &ac, 0 );

  input[0] = stbi_load( argv[1], &ix, &iy, &ic, 0 );
  input[1] = input[0];
  input[2] = convert8to16( input[0], ix, iy, ic );
  input[3] = convert8tof( input[0], ix, iy, ic );
  input[4] = convert8tohf( input[0], ix, iy, ic );
  input[5] = convert8tohff( input[0], ix, iy, ic );

  printf("Input %dx%d (%d channels)\n",ix,iy,ic);

  ir1 = malloc( 4 * 4 * 3000 * 3000ULL );
  ir2 = malloc( 4 * 4 * 3000 * 3000ULL );

  szhs[0] = getprime( iy/SHRINKBYH );
  szhs[1] = iy;
  szhs[2] = getprime( iy*ZOOMBYH );

  szws[0] = getprime( ix/SHRINKBYW );
  szws[1] = ix;
  szws[2] = getprime( ix*ZOOMBYW );

  #if 1
  for( types = TYPESTART ; types <= TYPEEND ; types++ )
  #else
  for( types = 1 ; types <= 1 ; types++ )
  #endif
  {
    ENTER( "Test type: %s",typestrs[types]);
    #if 1
    for( layouts = LAYOUTSTART ; layouts <= LAYOUTEND ; layouts++ )
    #else
    for( layouts = 16; layouts <= 16 ; layouts++ )
    #endif
    {
      ENTER( "Test layout: %s",buffstrs[layouts]);
      
      #if 0
      for( heights = HEIGHTSTART ; heights <= HEIGHTEND ; heights++ )
      {
        int w, h = szhs[heights];
      #else
      for( heights = 0 ; heights <= 11 ; heights++ )
      {
        static int szhsz[12]={32, 200, 350, 400, 450, 509, 532, 624, 700, 824, 1023, 2053 };
        int w, h = szhsz[heights];
      #endif

        ENTER( "Test height: %d %s %d",iy,(h<iy)?"Down":((h>iy)?"Up":"Same"),h);
  
        #if 0
        for( widths = WIDTHSTART ; widths <= WIDTHEND ; widths++ )
        {
          w = szws[widths];
        #else
        for( widths = 0 ; widths <= 12 ; widths++ )
        {
          static int szwsz[13]={2, 32, 200, 350, 400, 450, 509, 532, 624, 700, 824, 1023, 2053 };
          w = szwsz[widths];
        #endif

          ENTER( "Test width: %d %s %d",ix, (w<ix)?"Down":((w>ix)?"Up":"Same"), w);

          #if 0
          for( edges = EDGESTART ; edges <= EDGEEND ; edges++ )
          #else
          for( edges = 0 ; edges <= 0 ; edges++ )
          #endif
          {
            ENTER( "Test edge: %s",edgestrs[edges]);
            #if 0
            for( filters = FILTERSTART ; filters <= FILTEREND ; filters++ )
            #else
            for( filters = 3 ; filters <= 3 ; filters++ )
            #endif
            {
              int op, opw, np,npw, c, a;
              #ifdef COMPARE_SAME                        
              int oldtypes = types;
              #else
              int oldtypes = (types==4)?3:types;
              #endif
            
              ENTER( "Test filter: %s",fltstrs[filters]);
              {
                c = bchannels[layouts];
                a = alphapos[layouts];

                op = w*tsizes[oldtypes]*c + 60;
                opw = w*tsizes[oldtypes]*c;

                np = w*tsizes[types]*c + 60;
                npw = w*tsizes[types]*c;

                printf( "%s:layout: %s  w: %d h: %d edge: %s filt: %s\n", typestrs[types],buffstrs[layouts], w, h, edgestrs[edges], fltstrs[filters] );


                // clear pixel area to different, right edge to zero
                #ifndef NOCLEAR
                ENTER( "Test clear padding" );
                {
                  int d;
                  for( d = 0 ; d < h ; d++ )
                  {
                    int oofs = d * op;
                    int nofs = d * np;
                    memset( ir1 + oofs, 192, opw );
                    memset( ir1 + oofs+opw, 79, op-opw );
                    memset( ir2 + nofs, 255, npw );
                    memset( ir2 + nofs+npw, 79, np-npw );
                  }
                }
                LEAVE();

                #endif

                #ifdef COMPARE_SAME                        
                #define TIMINGS 1
                #else 
                #define TIMINGS 1
                #endif
                ENTER( "Test both" );
                {
                  #ifndef PROFILE_NEW_ONLY
                    {
                      int ttt, max = 0x7fffffff;
                      ENTER( "Test old" );
                      for( ttt = 0 ; ttt < TIMINGS ; ttt++ )
                      {
                        int64 m = __cycles();

                        oresize( ir1, w, h, op, 
                        #ifdef COMPARE_SAME                        
                        input[types], 
                        #else
                        input[(types==4)?5:types], 
                        #endif
                        ix, iy, ix*ic*tsizes[oldtypes], layouts, oldtypes, edges, filters );

                        m = __cycles() - m;
                        if ( ( (int)m ) < max )
                        max = (int) m;
                      }
                      LEAVE();
                      printf("old: %d\n", max );
                    }
                  #endif
     
                  {
                    int ttt, max = 0x7fffffff, maxv = 0x7fffffff;
                    ENTER( "Test new" );
                    for( ttt = 0 ; ttt < TIMINGS ; ttt++ )
                    {
                      int64 m = __cycles();

                      nresize( ir2, w, h, np, input[types], ix, iy, ix*ic*tsizes[types], layouts, types, edges, filters );
        
                      m = __cycles() - m;
                      if ( ( (int)m ) < max )
                        max = (int) m;
                      if ( ( (int)vert ) < maxv )
                        maxv = (int) vert;
                    }
                    LEAVE(); // test new
                    printf("new: %d (v: %d)\n", max, maxv );
                  }
                }
                LEAVE();  // test both

                if ( mem_count!= 0 )
                  stop();

              #ifndef NOCOMP
                ENTER( "Test compare" );
                {
                  int x,y,ch;
                  int nums = 0;
                  for( y = 0 ; y < h ; y++ )
                  {
                    for( x = 0 ; x < w ; x++ )
                    {
                      switch(types)
                      {
                        case 0:
                        case 1: //SRGB 
                        {
                          unsigned char * p1 = (unsigned char *)&ir1[y*op+x*c];
                          unsigned char * p2 = (unsigned char *)&ir2[y*np+x*c];
                          for( ch = 0 ; ch < c ; ch++ )
                          {
                            float pp1,pp2,d;
                            float av = (a==-1)?1.0f:((float)p1[a]/255.0f);

                            pp1 = p1[ch];
                            pp2 = p2[ch];

                            // compare in premult space
                            #ifndef COMPARE_SAME                        
                            if ( ( ( layouts >=4 ) && ( layouts <= 7 ) ) || ( ( layouts >=16 ) && ( layouts <= 19 ) ) )
                            {
                              pp1 *= av;
                              pp2 *= av;
                            }
                            #endif

                            d = pp1 - pp2;
                            if ( d < 0 ) d = -d;

                            #ifdef COMPARE_SAME                        
                            if ( d > 0 ) 
                            #else 
                            if ( d > 1 )
                            #endif
                            {
                              printf("Error at %d x %d (chan %d) (d: %g a: %g) [%d %d %d %d] [%d %d %d %d]\n",x,y,ch, d,av, p1[0],p1[1],p1[2],p1[3], p2[0],p2[1],p2[2],p2[3]);
                              ++nums;
                              if ( nums > 16 ) goto ex;
                              //if (d) exit(1);
                              //goto ex;
                            }
                          }  
                        }
                        break;

                        case 2:
                        {
                          unsigned short * p1 = (unsigned short *)&ir1[y*op+x*c*sizeof(short)];
                          unsigned short * p2 = (unsigned short *)&ir2[y*np+x*c*sizeof(short)];
                          for( ch = 0 ; ch < c ; ch++ )
                          {
                            float thres,pp1,pp2,d;
                            float av = (a==-1)?1.0f:((float)p1[a]/65535.0f);

                            pp1 = p1[ch];
                            pp2 = p2[ch];

                            // compare in premult space
                            #ifndef COMPARE_SAME                        
                            if ( ( ( layouts >=4 ) && ( layouts <= 7 ) ) || ( ( layouts >= 16 ) && ( layouts <= 19 ) ) )
                            {
                              pp1 *= av;
                              pp2 *= av;
                            }
                            #endif

                            d = pp1 - pp2;
                            if ( d < 0 ) d = -d;

                            thres=((float)p1[ch]*0.007f)+2.0f;
                            if (thres<4) thres = 4;
  
                            #ifdef COMPARE_SAME                        
                            if ( d > 0 ) 
                            #else 
                            if ( d > thres)
                            #endif
                            {
                              printf("Error at %d x %d (chan %d) %d %d [df: %g th: %g al: %g] (%d %d %d %d) (%d %d %d %d)\n",x,y,ch, p1[ch],p2[ch],d,thres,av,p1[0],p1[1],p1[2],p1[3],p2[0],p2[1],p2[2],p2[3]);
                              ++nums;
                              if ( nums > 16 ) goto ex;
                              //if (d) exit(1);
                              //goto ex;
                            }
                          }
                        }
                        break;

                        case 3:
                        {
                          float * p1 = (float *)&ir1[y*op+x*c*sizeof(float)];
                          float * p2 = (float *)&ir2[y*np+x*c*sizeof(float)];
                          for( ch = 0 ; ch < c ; ch++ )
                          {
                            float pp1 = p1[ch], pp2 = p2[ch];
                            float av = (a==-1)?1.0f:p1[a];
                            float thres, d;

                            // clamp
                            if (pp1<=0.0f) pp1 = 0;
                            if (pp2<=0.0f) pp2 = 0;
                            if (av<=0.0f) av = 0;
                            if (pp1>1.0f) pp1 = 1.0f;
                            if (pp2>1.0f) pp2 = 1.0f;
                            if (av>1.0f) av = 1.0f;

                            // compare in premult space
                            #ifndef COMPARE_SAME                        
                            if ( ( ( layouts >=4 ) && ( layouts <= 7 ) ) || ( ( layouts >= 16 ) && ( layouts <= 19 ) ) )
                            {
                              pp1 *= av;
                              pp2 *= av;
                            }
                            #endif

                            d = pp1 - pp2;
                            if ( d < 0 ) d = -d;

                            thres=(p1[ch]*0.002f)+0.0002f;
                            if ( thres < 0 ) thres = -thres;

                            #ifdef COMPARE_SAME                        
                            if ( d != 0.0f ) 
                            #else 
                            if ( d > thres )
                            #endif
                            {
                              printf("Error at %d x %d (chan %d) %g %g [df: %g th: %g al: %g] (%g %g %g %g) (%g %g %g %g)\n",x,y,ch, p1[ch],p2[ch],d,thres,av,p1[0],p1[1],p1[2],p1[3],p2[0],p2[1],p2[2],p2[3]);
                              ++nums;
                              if ( nums > 16 ) goto ex;
                              //if (d) exit(1);
                              //goto ex;
                            }
                          }
                        }
                        break;

                        case 4:
                        {
                          #ifdef COMPARE_SAME                        
                          stbir__FP16 * p1 = (stbir__FP16 *)&ir1[y*op+x*c*sizeof(stbir__FP16)];
                          #else
                          float * p1 = (float *)&ir1[y*op+x*c*sizeof(float)];
                          #endif
                          stbir__FP16 * p2 = (stbir__FP16 *)&ir2[y*np+x*c*sizeof(stbir__FP16)];
                          for( ch = 0 ; ch < c ; ch++ )
                          {
                            #ifdef COMPARE_SAME                        
                            float pp1  = stbir__half_to_float(p1[ch]);
                            float av = (a==-1)?1.0f:stbir__half_to_float(p1[a]);
                            #else
                            float pp1 = stbir__half_to_float(stbir__float_to_half(p1[ch]));
                            float av = (a==-1)?1.0f:stbir__half_to_float(stbir__float_to_half(p1[a]));
                            #endif
                            float pp2 = stbir__half_to_float(p2[ch]);
                            float d, thres;

                            // clamp
                            if (pp1<=0.0f) pp1 = 0;
                            if (pp2<=0.0f) pp2 = 0;
                            if (av<=0.0f) av = 0;
                            if (pp1>1.0f) pp1 = 1.0f;
                            if (pp2>1.0f) pp2 = 1.0f;
                            if (av>1.0f) av = 1.0f;

                            thres=(pp1*0.002f)+0.0002f;

                            // compare in premult space
                            #ifndef COMPARE_SAME                        
                            if ( ( ( layouts >=4 ) && ( layouts <= 7 ) ) || ( ( layouts >= 16 ) && ( layouts <= 19 ) ) )
                            {
                              pp1 *= av;
                              pp2 *= av;
                            }
                            #endif

                            d = pp1 - pp2;
                            if ( d < 0 ) d = -d;


                            #ifdef COMPARE_SAME                        
                            if ( d != 0.0f ) 
                            #else 
                            if ( d > thres )
                            #endif
                            {
                              printf("Error at %d x %d (chan %d) %g %g [df: %g th: %g al: %g] (%g %g %g %g) (%g %g %g %g)\n",x,y,ch, 
                              #ifdef COMPARE_SAME                        
                              stbir__half_to_float(p1[ch]), 
                              #else
                              p1[ch],
                              #endif
                              stbir__half_to_float(p2[ch]), 
                              d,thres,av,
                              #ifdef COMPARE_SAME                        
                              stbir__half_to_float(p1[0]),stbir__half_to_float(p1[1]),stbir__half_to_float(p1[2]),stbir__half_to_float(p1[3]),
                              #else
                              p1[0],p1[1],p1[2],p1[3],
                              #endif
                              stbir__half_to_float(p2[0]),stbir__half_to_float(p2[1]),stbir__half_to_float(p2[2]),stbir__half_to_float(p2[3]) );
                              ++nums;
                              if ( nums > 16 ) goto ex;
                              //if (d) exit(1);
                              //goto ex;
                            }
                          }
                        }
                        break;
                      }
                    }

                    for( x = (w*c)*tsizes[oldtypes]; x < op; x++ )
                    {
                      if ( ir1[y*op+x] != 79 )
                      {
                        printf("Margin error at %d x %d %d (should be 79) OLD!\n",x,y,(unsigned char)ir1[y*op+x]);
                        goto ex;
                      }
                    }

                    for( x = (w*c)*tsizes[types]; x < np; x++ )
                    {
                      if ( ir2[y*np+x] != 79 )
                      {
                        printf("Margin error at %d x %d %d (should be 79) NEW\n",x,y,(unsigned char)ir2[y*np+x]);
                        goto ex;
                      }
                    }
                  }
                
                  ex:
                  ENTER( "OUTPUT IMAGES" );
                  printf("  tot pix: %d, errs: %d\n", w*h*c,nums );

                  if (nums)
                  {
                    stbi_write_png("old.png", w, h, c, ir1, op);
                    stbi_write_png("new.png", w, h, c, ir2, np);
                    exit(1);
                  }

                  LEAVE(); // output images
                }
                LEAVE(); //test compare
              #endif



              }
              LEAVE(); // test filter
            }
            LEAVE(); // test edge
          }
          LEAVE(); // test width
        }
        LEAVE(); // test height
      }
      LEAVE(); // test type
    }
    LEAVE();  // test layout
  }

  CloseTM();
  return 0;
}
