#ifndef RR_SPRINTF_H_INCLUDE
#define RR_SPRINTF_H_INCLUDE

/*
Single file sprintf replacement.

Originally written by Jeff Roberts at RAD Game Tools - 2015/10/20. 
Hereby placed in public domain.

This is a full sprintf replacement that supports everything that
the C runtime sprintfs support, including float/double, 64-bit integers,
hex floats, field parameters (%*.*d stuff), length reads backs, etc.

Why would you need this if sprintf already exists?  Well, first off,
it's *much* faster (see below). It's also much smaller than the CRT
versions code-space-wise. We've also added some simple improvements 
that are super handy (commas in thousands, callbacks at buffer full,
for example). Finally, the format strings for MSVC and GCC differ 
for 64-bit integers (among other small things), so this lets you use 
the same format strings in cross platform code.

It uses the standard single file trick of being both the header file
and the source itself. If you just include it normally, you just get 
the header file function definitions. To get the code, you include
it from a C or C++ file and define RR_SPRINTF_IMPLEMENTATION first.

It only uses va_args macros from the C runtime to do it's work. It
does cast doubles to S64s and shifts and divides U64s, which does 
drag in CRT code on most platforms.

It compiles to roughly 8K with float support, and 4K without.
As a comparison, when using MSVC static libs, calling sprintf drags
in 16K.

API:
====
int rrsprintf( char * buf, char const * fmt, ... )
int rrsnprintf( char * buf, int count, char const * fmt, ... )
  Convert an arg list into a buffer.  rrsnprintf always returns
  a zero-terminated string (unlike regular snprintf).

int rrvsprintf( char * buf, char const * fmt, va_list va )
int rrvsnprintf( char * buf, int count, char const * fmt, va_list va )
  Convert a va_list arg list into a buffer.  rrvsnprintf always returns
  a zero-terminated string (unlike regular snprintf).

int rrvsprintfcb( RRSPRINTFCB * callback, void * user, char * buf, char const * fmt, va_list va )
    typedef char * RRSPRINTFCB( char const * buf, void * user, int len );
  Convert into a buffer, calling back every RR_SPRINTF_MIN chars.
  Your callback can then copy the chars out, print them or whatever.
  This function is actually the workhorse for everything else.
  The buffer you pass in must hold at least RR_SPRINTF_MIN characters.
    // you return the next buffer to use or 0 to stop converting

void rrsetseparators( char comma, char period )
  Set the comma and period characters to use.

FLOATS/DOUBLES:
===============
This code uses a internal float->ascii conversion method that uses
doubles with error correction (double-doubles, for ~105 bits of
precision).  This conversion is round-trip perfect - that is, an atof
of the values output here will give you the bit-exact double back.

One difference is that our insignificant digits will be different than 
with MSVC or GCC (but they don't match each other either).  We also 
don't attempt to find the minimum length matching float (pre-MSVC15 
doesn't either).

If you don't need float or doubles at all, define RR_SPRINTF_NOFLOAT
and you'll save 4K of code space.

64-BIT INTS:
============
This library also supports 64-bit integers and you can use MSVC style or
GCC style indicators (%I64d or %lld).  It supports the C99 specifiers
for size_t and ptr_diff_t (%jd %zd) as well.

EXTRAS:
=======
Like some GCCs, for integers and floats, you can use a ' (single quote)
specifier and commas will be inserted on the thousands: "%'d" on 12345 
would print 12,345.

For integers and floats, you can use a "$" specifier and the number 
will be converted to float and then divided to get kilo, mega, giga or
tera and then printed, so "%$d" 1024 is "1.0 k", "%$.2d" 2536000 is 
"2.42 m", etc.

In addition to octal and hexadecimal conversions, you can print 
integers in binary: "%b" for 256 would print 100.

PERFORMANCE vs MSVC 2008 32-/64-bit (GCC is even slower than MSVC):
===================================================================
"%d" across all 32-bit ints (4.8x/4.0x faster than 32-/64-bit MSVC)
"%24d" across all 32-bit ints (4.5x/4.2x faster)
"%x" across all 32-bit ints (4.5x/3.8x faster)
"%08x" across all 32-bit ints (4.3x/3.8x faster)
"%f" across e-10 to e+10 floats (7.3x/6.0x faster)
"%e" across e-10 to e+10 floats (8.1x/6.0x faster)
"%g" across e-10 to e+10 floats (10.0x/7.1x faster)
"%f" for values near e-300 (7.9x/6.5x faster)
"%f" for values near e+300 (10.0x/9.1x faster)
"%e" for values near e-300 (10.1x/7.0x faster)
"%e" for values near e+300 (9.2x/6.0x faster)
"%.320f" for values near e-300 (12.6x/11.2x faster)
"%a" for random values (8.6x/4.3x faster)
"%I64d" for 64-bits with 32-bit values (4.8x/3.4x faster)
"%I64d" for 64-bits > 32-bit values (4.9x/5.5x faster)
"%s%s%s" for 64 char strings (7.1x/7.3x faster)
"...512 char string..." ( 35.0x/32.5x faster!)
*/

#ifdef RR_SPRINTF_STATIC
#define RRPUBLIC_DEC static
#define RRPUBLIC_DEF static
#else
#ifdef __cplusplus
#define RRPUBLIC_DEC extern "C"
#define RRPUBLIC_DEF extern "C"
#else
#define RRPUBLIC_DEC extern 
#define RRPUBLIC_DEF
#endif
#endif

#include <stdarg.h>  // for va_list()

#ifndef RR_SPRINTF_MIN
#define RR_SPRINTF_MIN 512 // how many characters per callback
#endif
typedef char * RRSPRINTFCB( char * buf, void * user, int len );

#ifndef RR_SPRINTF_DECORATE
#define RR_SPRINTF_DECORATE(name) rr##name  // define this before including if you want to change the names
#endif

#ifndef RR_SPRINTF_IMPLEMENTATION

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( vsprintf )( char * buf, char const * fmt, va_list va );
RRPUBLIC_DEF int RR_SPRINTF_DECORATE( vsnprintf )( char * buf, int count, char const * fmt, va_list va );
RRPUBLIC_DEF int RR_SPRINTF_DECORATE( sprintf ) ( char * buf, char const * fmt, ... );
RRPUBLIC_DEF int RR_SPRINTF_DECORATE( snprintf )( char * buf, int count, char const * fmt, ... );

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( vsprintfcb )( RRSPRINTFCB * callback, void * user, char * buf, char const * fmt, va_list va );
RRPUBLIC_DEF void RR_SPRINTF_DECORATE( setseparators )( char comma, char period );

#else

#include <stdlib.h>  // for va_arg()

#define rU32 unsigned int
#define rS32 signed int

#ifdef _MSC_VER
#define rU64 unsigned __int64
#define rS64 signed __int64
#else
#define rU64 unsigned long long
#define rS64 signed long long
#endif
#define rU16 unsigned short

#ifndef rUINTa 
#if defined(__ppc64__) || defined(__aarch64__) || defined(_M_X64) || defined(__x86_64__) || defined(__x86_64)
#define rUINTa rU64
#else
#define rUINTa rU32
#endif
#endif

#ifndef RR_SPRINTF_MSVC_MODE  // used for MSVC2013 and earlier (MSVC2015 matches GCC)
#if defined(_MSC_VER) && (_MSC_VER<1900)
#define RR_SPRINTF_MSVC_MODE
#endif
#endif

#ifdef RR_SPRINTF_NOUNALIGNED  // define this before inclusion to force rrsprint to always use aligned accesses
#define RR_UNALIGNED(code)
#else
#define RR_UNALIGNED(code) code
#endif

#ifndef RR_SPRINTF_NOFLOAT
// internal float utility functions
static rS32 rrreal_to_str( char const * * start, rU32 * len, char *out, rS32 * decimal_pos, double value, rU32 frac_digits );
static rS32 rrreal_to_parts( rS64 * bits, rS32 * expo, double value );
#define RRSPECIAL 0x7000
#endif

static char RRperiod='.';
static char RRcomma=',';
static char rrdiglookup[201]="00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";

RRPUBLIC_DEF void RR_SPRINTF_DECORATE( setseparators )( char pcomma, char pperiod )
{
  RRperiod=pperiod;
  RRcomma=pcomma;
}

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( vsprintfcb )( RRSPRINTFCB * callback, void * user, char * buf, char const * fmt, va_list va )
{
  static char hex[]="0123456789abcdefxp";
  static char hexu[]="0123456789ABCDEFXP";
  char * bf;
  char const * f;
  int tlen = 0;

  bf = buf;
  f = fmt;
  for(;;)
  {
    rS32 fw,pr,tz; rU32 fl;

    #define LJ 1
    #define LP 2
    #define LS 4
    #define LX 8
    #define LZ 16
    #define BI 32
    #define CS 64
    #define NG 128
    #define KI 256
    #define HW 512
 
    // macros for the callback buffer stuff
    #define chk_cb_bufL(bytes) { int len = (int)(bf-buf); if ((len+(bytes))>=RR_SPRINTF_MIN) { tlen+=len; if (0==(bf=buf=callback(buf,user,len))) goto done; } }
    #define chk_cb_buf(bytes) { if ( callback ) { chk_cb_bufL(bytes); } }
    #define flush_cb() { chk_cb_bufL(RR_SPRINTF_MIN-1); } //flush if there is even one byte in the buffer
    #define cb_buf_clamp(cl,v) cl = v; if ( callback ) { int lg = RR_SPRINTF_MIN-(int)(bf-buf); if (cl>lg) cl=lg; }

    // fast copy everything up to the next % (or end of string)
    for(;;)
    { 
      while (((rUINTa)f)&3)
      {
       schk1: if (f[0]=='%') goto scandd;
       schk2: if (f[0]==0) goto endfmt;
        chk_cb_buf(1); *bf++=f[0]; ++f;
      } 
      for(;;)
      { 
        rU32 v,c;
        v=*(rU32*)f; c=(~v)&0x80808080;
        if ((v-0x26262626)&c) goto schk1; 
        if ((v-0x01010101)&c) goto schk2; 
        if (callback) if ((RR_SPRINTF_MIN-(int)(bf-buf))<4) goto schk1;
        *(rU32*)bf=v; bf+=4; f+=4;
      }
    } scandd:

    ++f;

    // ok, we have a percent, read the modifiers first
    fw = 0; pr = -1; fl = 0; tz = 0;
    
    // flags
    for(;;)
    {
      switch(f[0])
      {
        // if we have left just
        case '-': fl|=LJ; ++f; continue;
        // if we have leading plus
        case '+': fl|=LP; ++f; continue; 
        // if we have leading space
        case ' ': fl|=LS; ++f; continue; 
        // if we have leading 0x
        case '#': fl|=LX; ++f; continue; 
        // if we have thousand commas
        case '\'': fl|=CS; ++f; continue; 
        // if we have kilo marker
        case '$': fl|=KI; ++f; continue; 
        // if we have leading zero
        case '0': fl|=LZ; ++f; goto flags_done; 
        default: goto flags_done;
      }
    }
    flags_done:
   
    // get the field width
    if ( f[0] == '*' ) {fw = va_arg(va,rU32); ++f;} else { while (( f[0] >= '0' ) && ( f[0] <= '9' )) { fw = fw * 10 + f[0] - '0'; f++; } }
    // get the precision
    if ( f[0]=='.' ) { ++f; if ( f[0] == '*' ) {pr = va_arg(va,rU32); ++f;} else { pr = 0; while (( f[0] >= '0' ) && ( f[0] <= '9' )) { pr = pr * 10 + f[0] - '0'; f++; } } } 
    
    // handle integer size overrides
    switch(f[0])
    {
      // are we halfwidth?
      case 'h': fl|=HW; ++f; break;
      // are we 64-bit (unix style)
      case 'l': ++f; if ( f[0]=='l') { fl|=BI; ++f; } break;
      // are we 64-bit on intmax? (c99)
      case 'j': fl|=BI; ++f; break; 
      // are we 64-bit on size_t or ptrdiff_t? (c99)
      case 'z': case 't': fl|=((sizeof(char*)==8)?BI:0); ++f; break; 
      // are we 64-bit (msft style)
      case 'I': if ( ( f[1]=='6') && ( f[2]=='4') ) { fl|=BI; f+=3; } else if ( ( f[1]=='3') && ( f[2]=='2') ) { f+=3; } else { fl|=((sizeof(void*)==8)?BI:0); ++f; } break;
      default: break;
    }

    // handle each replacement
    switch( f[0] )
    {
      #define NUMSZ 512 // big enough for e308 (with commas) or e-307 
      char num[NUMSZ]; 
      char lead[8]; 
      char tail[8]; 
      char *s;
      char const *h;
      rU32 l,n,cs;
      rU64 n64;
      #ifndef RR_SPRINTF_NOFLOAT      
      double fv; 
      #endif
      rS32 dp; char const * sn;

      case 's':
        // get the string
        s = va_arg(va,char*); if (s==0) s = (char*)"null";
        // get the length
        sn = s;
        for(;;)
        { 
          if ((((rUINTa)sn)&3)==0) break;
         lchk:
          if (sn[0]==0) goto ld;
          ++sn;
        }
        n = 0xffffffff;
        if (pr>=0) { n=(rU32)(sn-s); if (n>=(rU32)pr) goto ld; n=((rU32)(pr-n))>>2; }
        while(n) 
        { 
          rU32 v=*(rU32*)sn;
          if ((v-0x01010101)&(~v)&0x80808080UL) goto lchk; 
          sn+=4; 
          --n;
        }
        goto lchk;
       ld:

        l = (rU32) ( sn - s );
        // clamp to precision
        if ( l > (rU32)pr ) l = pr;
        lead[0]=0; tail[0]=0; pr = 0; dp = 0; cs = 0;
        // copy the string in
        goto scopy;

      case 'c': // char
        // get the character
        s = num + NUMSZ -1; *s = (char)va_arg(va,int);
        l = 1;
        lead[0]=0; tail[0]=0; pr = 0; dp = 0; cs = 0;
        goto scopy;

      case 'n': // weird write-bytes specifier
        { int * d = va_arg(va,int*);
        *d = tlen + (int)( bf - buf ); }
        break;

#ifdef RR_SPRINTF_NOFLOAT
      case 'A': // float
      case 'a': // hex float
      case 'G': // float
      case 'g': // float
      case 'E': // float
      case 'e': // float
      case 'f': // float
        va_arg(va,double); // eat it
        s = (char*)"No float";
        l = 8;
        lead[0]=0; tail[0]=0; pr = 0; dp = 0; cs = 0;
        goto scopy;
#else
      case 'A': // float
        h=hexu;  
        goto hexfloat;

      case 'a': // hex float
        h=hex;
       hexfloat: 
        fv = va_arg(va,double);
        if (pr==-1) pr=6; // default is 6
        // read the double into a string
        if ( rrreal_to_parts( (rS64*)&n64, &dp, fv ) )
          fl |= NG;
  
        s = num+64;

        // sign
        lead[0]=0; if (fl&NG) { lead[0]=1; lead[1]='-'; } else if (fl&LS) { lead[0]=1; lead[1]=' '; } else if (fl&LP) { lead[0]=1; lead[1]='+'; };

        if (dp==-1023) dp=(n64)?-1022:0; else n64|=(((rU64)1)<<52);
        n64<<=(64-56);
        if (pr<15) n64+=((((rU64)8)<<56)>>(pr*4));
        // add leading chars
        
        #ifdef RR_SPRINTF_MSVC_MODE
        *s++='0';*s++='x';
        #else
        lead[1+lead[0]]='0'; lead[2+lead[0]]='x'; lead[0]+=2;
        #endif
        *s++=h[(n64>>60)&15]; n64<<=4;
        if ( pr ) *s++=RRperiod;
        sn = s;

        // print the bits
        n = pr; if (n>13) n = 13; if (pr>(rS32)n) tz=pr-n; pr = 0;
        while(n--) { *s++=h[(n64>>60)&15]; n64<<=4; }

        // print the expo
        tail[1]=h[17];
        if (dp<0) { tail[2]='-'; dp=-dp;} else tail[2]='+';
        n = (dp>=1000)?6:((dp>=100)?5:((dp>=10)?4:3));
        tail[0]=(char)n;
        for(;;) { tail[n]='0'+dp%10; if (n<=3) break; --n; dp/=10; }

        dp = (int)(s-sn);
        l = (int)(s-(num+64));
        s = num+64;
        cs = 1 + (3<<24);
        goto scopy;

      case 'G': // float
        h=hexu;
        goto dosmallfloat;

      case 'g': // float
        h=hex;
       dosmallfloat:   
        fv = va_arg(va,double);
        if (pr==-1) pr=6; else if (pr==0) pr = 1; // default is 6
        // read the double into a string
        if ( rrreal_to_str( &sn, &l, num, &dp, fv, (pr-1)|0x80000000 ) )
          fl |= NG;

        // clamp the precision and delete extra zeros after clamp
        n = pr;
        if ( l > (rU32)pr ) l = pr; while ((l>1)&&(pr)&&(sn[l-1]=='0')) { --pr; --l; }

        // should we use %e
        if ((dp<=-4)||(dp>(rS32)n))
        {
          if ( pr > (rS32)l ) pr = l-1; else if ( pr ) --pr; // when using %e, there is one digit before the decimal
          goto doexpfromg;
        }
        // this is the insane action to get the pr to match %g sematics for %f
        if(dp>0) { pr=(dp<(rS32)l)?l-dp:0; } else { pr = -dp+((pr>(rS32)l)?l:pr); }
        goto dofloatfromg;

      case 'E': // float
        h=hexu;  
        goto doexp;

      case 'e': // float
        h=hex;
       doexp:   
        fv = va_arg(va,double);
        if (pr==-1) pr=6; // default is 6
        // read the double into a string
        if ( rrreal_to_str( &sn, &l, num, &dp, fv, pr|0x80000000 ) )
          fl |= NG;
       doexpfromg: 
        tail[0]=0; 
        lead[0]=0; if (fl&NG) { lead[0]=1; lead[1]='-'; } else if (fl&LS) { lead[0]=1; lead[1]=' '; } else if (fl&LP) { lead[0]=1; lead[1]='+'; };
        if ( dp == RRSPECIAL ) { s=(char*)sn; cs=0; pr=0; goto scopy; }
        s=num+64; 
        // handle leading chars
        *s++=sn[0];

        if (pr) *s++=RRperiod;

        // handle after decimal
        if ((l-1)>(rU32)pr) l=pr+1;
        for(n=1;n<l;n++) *s++=sn[n];
        // trailing zeros
        tz = pr-(l-1); pr=0;
        // dump expo
        tail[1]=h[0xe];
        dp -= 1;
        if (dp<0) { tail[2]='-'; dp=-dp;} else tail[2]='+';
        #ifdef RR_SPRINTF_MSVC_MODE
        n = 5;
        #else
        n = (dp>=100)?5:4;
        #endif
        tail[0]=(char)n;
        for(;;) { tail[n]='0'+dp%10; if (n<=3) break; --n; dp/=10; }
        cs = 1 + (3<<24); // how many tens
        goto flt_lead;   

      case 'f': // float
        fv = va_arg(va,double);
       doafloat: 
        // do kilos
        if (fl&KI) {while(fl<0x4000000) { if ((fv<1024.0) && (fv>-1024.0)) break; fv/=1024.0; fl+=0x1000000; }} 
        if (pr==-1) pr=6; // default is 6
        // read the double into a string
        if ( rrreal_to_str( &sn, &l, num, &dp, fv, pr ) )
          fl |= NG;
        dofloatfromg:
        tail[0]=0;
        // sign
        lead[0]=0; if (fl&NG) { lead[0]=1; lead[1]='-'; } else if (fl&LS) { lead[0]=1; lead[1]=' '; } else if (fl&LP) { lead[0]=1; lead[1]='+'; };
        if ( dp == RRSPECIAL ) { s=(char*)sn; cs=0; pr=0; goto scopy; }
        s=num+64; 

        // handle the three decimal varieties
        if (dp<=0) 
        { 
          rS32 i;
          // handle 0.000*000xxxx
          *s++='0'; if (pr) *s++=RRperiod; 
          n=-dp; if((rS32)n>pr) n=pr; i=n; while(i) { if ((((rUINTa)s)&3)==0) break; *s++='0'; --i; } while(i>=4) { *(rU32*)s=0x30303030; s+=4; i-=4; } while(i) { *s++='0'; --i; }
          if ((rS32)(l+n)>pr) l=pr-n; i=l; while(i) { *s++=*sn++; --i; }
          tz = pr-(n+l);
          cs = 1 + (3<<24); // how many tens did we write (for commas below)
        }
        else
        {
          cs = (fl&CS)?((600-(rU32)dp)%3):0;
          if ((rU32)dp>=l)
          {
            // handle xxxx000*000.0
            n=0; for(;;) { if ((fl&CS) && (++cs==4)) { cs = 0; *s++=RRcomma; } else { *s++=sn[n]; ++n; if (n>=l) break; } }
            if (n<(rU32)dp)
            {
              n = dp - n;
              if ((fl&CS)==0) { while(n) { if ((((rUINTa)s)&3)==0) break; *s++='0'; --n; }  while(n>=4) { *(rU32*)s=0x30303030; s+=4; n-=4; } }
              while(n) { if ((fl&CS) && (++cs==4)) { cs = 0; *s++=RRcomma; } else { *s++='0'; --n; } }
            }
            cs = (int)(s-(num+64)) + (3<<24); // cs is how many tens
            if (pr) { *s++=RRperiod; tz=pr;}
          }
          else
          {
            // handle xxxxx.xxxx000*000
            n=0; for(;;) { if ((fl&CS) && (++cs==4)) { cs = 0; *s++=RRcomma; } else { *s++=sn[n]; ++n; if (n>=(rU32)dp) break; } }
            cs = (int)(s-(num+64)) + (3<<24); // cs is how many tens
            if (pr) *s++=RRperiod;
            if ((l-dp)>(rU32)pr) l=pr+dp;
            while(n<l) { *s++=sn[n]; ++n; }
            tz = pr-(l-dp);
          }
        }
        pr = 0;
        
        // handle k,m,g,t
        if (fl&KI) { tail[0]=1; tail[1]=' '; { if (fl>>24) { tail[2]="_kmgt"[fl>>24]; tail[0]=2; } } };

        flt_lead:
        // get the length that we copied
        l = (rU32) ( s-(num+64) );
        s=num+64; 
        goto scopy;
#endif

      case 'B': // upper binary
        h = hexu;
        goto binary;

      case 'b': // lower binary
        h = hex;
        binary:
        lead[0]=0;
        if (fl&LX) { lead[0]=2;lead[1]='0';lead[2]=h[0xb]; }
        l=(8<<4)|(1<<8);
        goto radixnum;

      case 'o': // octal
        h = hexu;
        lead[0]=0;
        if (fl&LX) { lead[0]=1;lead[1]='0'; }
        l=(3<<4)|(3<<8);
        goto radixnum;

      case 'p': // pointer
        fl |= (sizeof(void*)==8)?BI:0;
        pr = sizeof(void*)*2;
        fl &= ~LZ; // 'p' only prints the pointer with zeros
        // drop through to X
      
      case 'X': // upper binary
        h = hexu;
        goto dohexb;

      case 'x': // lower binary
        h = hex; dohexb:
        l=(4<<4)|(4<<8);
        lead[0]=0;
        if (fl&LX) { lead[0]=2;lead[1]='0';lead[2]=h[16]; }
       radixnum: 
        // get the number
        if ( fl&BI )
          n64 = va_arg(va,rU64);
        else
          n64 = va_arg(va,rU32);

        s = num + NUMSZ; dp = 0;
        // clear tail, and clear leading if value is zero
        tail[0]=0; if (n64==0) { lead[0]=0; if (pr==0) { l=0; cs = ( ((l>>4)&15)) << 24; goto scopy; } }
        // convert to string
        for(;;) { *--s = h[n64&((1<<(l>>8))-1)]; n64>>=(l>>8); if ( ! ( (n64) || ((rS32) ( (num+NUMSZ) - s ) < pr ) ) ) break; if ( fl&CS) { ++l; if ((l&15)==((l>>4)&15)) { l&=~15; *--s=RRcomma; } } };
        // get the tens and the comma pos
        cs = (rU32) ( (num+NUMSZ) - s ) + ( ( ((l>>4)&15)) << 24 );
        // get the length that we copied
        l = (rU32) ( (num+NUMSZ) - s );
        // copy it
        goto scopy;

      case 'u': // unsigned
      case 'i':
      case 'd': // integer
        // get the integer and abs it
        if ( fl&BI )
        {
          rS64 i64 = va_arg(va,rS64); n64 = (rU64)i64; if ((f[0]!='u') && (i64<0)) { n64=(rU64)-i64; fl|=NG; }
        }
        else
        {
          rS32 i = va_arg(va,rS32); n64 = (rU32)i; if ((f[0]!='u') && (i<0)) { n64=(rU32)-i; fl|=NG; }
        }

        #ifndef RR_SPRINTF_NOFLOAT
        if (fl&KI) { if (n64<1024) pr=0; else if (pr==-1) pr=1; fv=(double)(rS64)n64; goto doafloat; } 
        #endif

        // convert to string
        s = num+NUMSZ; l=0; 
        
        for(;;)
        {
          // do in 32-bit chunks (avoid lots of 64-bit divides even with constant denominators)
          char * o=s-8;
          if (n64>=100000000) { n = (rU32)( n64 % 100000000);  n64 /= 100000000; } else {n = (rU32)n64; n64 = 0; }
          if((fl&CS)==0) { while(n) { s-=2; *(rU16*)s=*(rU16*)&rrdiglookup[(n%100)*2]; n/=100; } }
          while (n) { if ( ( fl&CS) && (l++==3) ) { l=0; *--s=RRcomma; --o; } else { *--s=(char)(n%10)+'0'; n/=10; } }
          if (n64==0) { if ((s[0]=='0') && (s!=(num+NUMSZ))) ++s; break; }
          while (s!=o) if ( ( fl&CS) && (l++==3) ) { l=0; *--s=RRcomma; --o; } else { *--s='0'; }
        }

        tail[0]=0;
        // sign
        lead[0]=0; if (fl&NG) { lead[0]=1; lead[1]='-'; } else if (fl&LS) { lead[0]=1; lead[1]=' '; } else if (fl&LP) { lead[0]=1; lead[1]='+'; };

        // get the length that we copied
        l = (rU32) ( (num+NUMSZ) - s ); if ( l == 0 ) { *--s='0'; l = 1; }
        cs = l + (3<<24);
        if (pr<0) pr = 0;

       scopy: 
        // get fw=leading/trailing space, pr=leading zeros
        if (pr<(rS32)l) pr = l;
        n = pr + lead[0] + tail[0] + tz;
        if (fw<(rS32)n) fw = n;
        fw -= n;
        pr -= l;

        // handle right justify and leading zeros
        if ( (fl&LJ)==0 )
        {
          if (fl&LZ) // if leading zeros, everything is in pr
          { 
            pr = (fw>pr)?fw:pr;
            fw = 0;
          }
          else
          {
            fl &= ~CS; // if no leading zeros, then no commas
          }
        }

        // copy the spaces and/or zeros
        if (fw+pr)
        {
          rS32 i; rU32 c; 

          // copy leading spaces (or when doing %8.4d stuff)
          if ( (fl&LJ)==0 ) while(fw>0) { cb_buf_clamp(i,fw); fw -= i; while(i) { if ((((rUINTa)bf)&3)==0) break; *bf++=' '; --i; } while(i>=4) { *(rU32*)bf=0x20202020; bf+=4; i-=4; } while (i) {*bf++=' '; --i;} chk_cb_buf(1); }
        
          // copy leader
          sn=lead+1; while(lead[0]) { cb_buf_clamp(i,lead[0]); lead[0] -= (char)i; while (i) {*bf++=*sn++; --i;} chk_cb_buf(1); }
          
          // copy leading zeros
          c = cs >> 24; cs &= 0xffffff;
          cs = (fl&CS)?((rU32)(c-((pr+cs)%(c+1)))):0;
          while(pr>0) { cb_buf_clamp(i,pr); pr -= i; if((fl&CS)==0) { while(i) { if ((((rUINTa)bf)&3)==0) break; *bf++='0'; --i; } while(i>=4) { *(rU32*)bf=0x30303030; bf+=4; i-=4; } } while (i) { if((fl&CS) && (cs++==c)) { cs = 0; *bf++=RRcomma; } else *bf++='0'; --i; } chk_cb_buf(1); }
        }

        // copy leader if there is still one
        sn=lead+1; while(lead[0]) { rS32 i; cb_buf_clamp(i,lead[0]); lead[0] -= (char)i; while (i) {*bf++=*sn++; --i;} chk_cb_buf(1); }

        // copy the string
        n = l; while (n) { rS32 i; cb_buf_clamp(i,n); n-=i; RR_UNALIGNED( while(i>=4) { *(rU32*)bf=*(rU32*)s; bf+=4; s+=4; i-=4; } ) while (i) {*bf++=*s++; --i;} chk_cb_buf(1); }

        // copy trailing zeros
        while(tz) { rS32 i; cb_buf_clamp(i,tz); tz -= i; while(i) { if ((((rUINTa)bf)&3)==0) break; *bf++='0'; --i; } while(i>=4) { *(rU32*)bf=0x30303030; bf+=4; i-=4; } while (i) {*bf++='0'; --i;} chk_cb_buf(1); }

        // copy tail if there is one
        sn=tail+1; while(tail[0]) { rS32 i; cb_buf_clamp(i,tail[0]); tail[0] -= (char)i; while (i) {*bf++=*sn++; --i;} chk_cb_buf(1); }

        // handle the left justify
        if (fl&LJ) if (fw>0) { while (fw) { rS32 i; cb_buf_clamp(i,fw); fw-=i; while(i) { if ((((rUINTa)bf)&3)==0) break; *bf++=' '; --i; } while(i>=4) { *(rU32*)bf=0x20202020; bf+=4; i-=4; } while (i--) *bf++=' '; chk_cb_buf(1); } }
        break;

      default: // unknown, just copy code
        s = num + NUMSZ -1; *s = f[0];
        l = 1;
        fw=pr=fl=0;
        lead[0]=0; tail[0]=0; pr = 0; dp = 0; cs = 0;
        goto scopy;
    }
    ++f;
  }
 endfmt:

  if (!callback) 
    *bf = 0;
  else
    flush_cb();
 
 done:
  return tlen + (int)(bf-buf);
}

// cleanup
#undef LJ
#undef LP
#undef LS
#undef LX
#undef LZ
#undef BI
#undef CS
#undef NG
#undef KI
#undef NUMSZ
#undef chk_cb_bufL
#undef chk_cb_buf
#undef flush_cb
#undef cb_buf_clamp

// ============================================================================
//   wrapper functions

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( sprintf )( char * buf, char const * fmt, ... )
{
  va_list va;
  va_start( va, fmt );
  return RR_SPRINTF_DECORATE( vsprintfcb )( 0, 0, buf, fmt, va );
}

typedef struct RRCCS
{
  char * buf;
  int count;
  char tmp[ RR_SPRINTF_MIN ];
} RRCCS;

static char * rrclampcallback( char * buf, void * user, int len )
{
  RRCCS * c = (RRCCS*)user;

  if ( len > c->count ) len = c->count;

  if (len)
  {
    if ( buf != c->buf )
    {
      char * s, * d, * se;
      d = c->buf; s = buf; se = buf+len;
      do{ *d++ = *s++; } while (s<se);
    }
    c->buf += len;
    c->count -= len;
  }
  
  if ( c->count <= 0 ) return 0;
  return ( c->count >= RR_SPRINTF_MIN ) ? c->buf : c->tmp; // go direct into buffer if you can
}

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( vsnprintf )( char * buf, int count, char const * fmt, va_list va )
{
  RRCCS c;
  int l;

  if ( count == 0 )
    return 0;

  c.buf = buf;
  c.count = count;

  RR_SPRINTF_DECORATE( vsprintfcb )( rrclampcallback, &c, rrclampcallback(0,&c,0), fmt, va );
  
  // zero-terminate
  l = (int)( c.buf - buf );
  if ( l >= count ) // should never be greater, only equal (or less) than count
    l = count - 1;
  buf[l] = 0;

  return l;
}

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( snprintf )( char * buf, int count, char const * fmt, ... )
{
  va_list va;
  va_start( va, fmt );

  return RR_SPRINTF_DECORATE( vsnprintf )( buf, count, fmt, va );
}

RRPUBLIC_DEF int RR_SPRINTF_DECORATE( vsprintf )( char * buf, char const * fmt, va_list va )
{
  return RR_SPRINTF_DECORATE( vsprintfcb )( 0, 0, buf, fmt, va );
}

// =======================================================================
//   low level float utility functions

#ifndef RR_SPRINTF_NOFLOAT

 // copies d to bits w/ strict aliasing (this compiles to nothing on /Ox)
 #define RRCOPYFP(dest,src) { int cn; for(cn=0;cn<8;cn++) ((char*)&dest)[cn]=((char*)&src)[cn]; }
 
// get float info
static rS32 rrreal_to_parts( rS64 * bits, rS32 * expo, double value )
{
  double d;
  rS64 b = 0;

  // load value and round at the frac_digits
  d = value;

  RRCOPYFP( b, d );

  *bits = b & ((((rU64)1)<<52)-1);
  *expo = ((b >> 52) & 2047)-1023;
    
  return (rS32)(b >> 63);
}

static double const rrbot[23]={1e+000,1e+001,1e+002,1e+003,1e+004,1e+005,1e+006,1e+007,1e+008,1e+009,1e+010,1e+011,1e+012,1e+013,1e+014,1e+015,1e+016,1e+017,1e+018,1e+019,1e+020,1e+021,1e+022};
static double const rrnegbot[22]={1e-001,1e-002,1e-003,1e-004,1e-005,1e-006,1e-007,1e-008,1e-009,1e-010,1e-011,1e-012,1e-013,1e-014,1e-015,1e-016,1e-017,1e-018,1e-019,1e-020,1e-021,1e-022};
static double const rrnegboterr[22]={-5.551115123125783e-018,-2.0816681711721684e-019,-2.0816681711721686e-020,-4.7921736023859299e-021,-8.1803053914031305e-022,4.5251888174113741e-023,4.5251888174113739e-024,-2.0922560830128471e-025,-6.2281591457779853e-026,-3.6432197315497743e-027,6.0503030718060191e-028,2.0113352370744385e-029,-3.0373745563400371e-030,1.1806906454401013e-032,-7.7705399876661076e-032,2.0902213275965398e-033,-7.1542424054621921e-034,-7.1542424054621926e-035,2.4754073164739869e-036,5.4846728545790429e-037,9.2462547772103625e-038,-4.8596774326570872e-039};
static double const rrtop[13]={1e+023,1e+046,1e+069,1e+092,1e+115,1e+138,1e+161,1e+184,1e+207,1e+230,1e+253,1e+276,1e+299};
static double const rrnegtop[13]={1e-023,1e-046,1e-069,1e-092,1e-115,1e-138,1e-161,1e-184,1e-207,1e-230,1e-253,1e-276,1e-299};
static double const rrtoperr[13]={8388608,6.8601809640529717e+028,-7.253143638152921e+052,-4.3377296974619174e+075,-1.5559416129466825e+098,-3.2841562489204913e+121,-3.7745893248228135e+144,-1.7356668416969134e+167,-3.8893577551088374e+190,-9.9566444326005119e+213,6.3641293062232429e+236,-5.2069140800249813e+259,-5.2504760255204387e+282};
static double const rrnegtoperr[13]={3.9565301985100693e-040,-2.299904345391321e-063,3.6506201437945798e-086,1.1875228833981544e-109,-5.0644902316928607e-132,-6.7156837247865426e-155,-2.812077463003139e-178,-5.7778912386589953e-201,7.4997100559334532e-224,-4.6439668915134491e-247,-6.3691100762962136e-270,-9.436808465446358e-293,8.0970921678014997e-317};

#if defined(_MSC_VER) && (_MSC_VER<=1200)                                                                                                                                                                                       
static rU64 const rrpot[20]={1,10,100,1000, 10000,100000,1000000,10000000, 100000000,1000000000,10000000000,100000000000,  1000000000000,10000000000000,100000000000000,1000000000000000,  10000000000000000,100000000000000000,1000000000000000000,10000000000000000000U };
#define rrtento19th ((rU64)1000000000000000000)
#else
static rU64 const rrpot[20]={1,10,100,1000, 10000,100000,1000000,10000000, 100000000,1000000000,10000000000ULL,100000000000ULL,  1000000000000ULL,10000000000000ULL,100000000000000ULL,1000000000000000ULL,  10000000000000000ULL,100000000000000000ULL,1000000000000000000ULL,10000000000000000000ULL };
#define rrtento19th (1000000000000000000ULL)
#endif

#define rrddmulthi(oh,ol,xh,yh) \
{ \
  double ahi=0,alo,bhi=0,blo; \
  rS64 bt; \
  oh = xh * yh; \
  RRCOPYFP(bt,xh); bt&=((~(rU64)0)<<27); RRCOPYFP(ahi,bt); alo = xh-ahi; \
  RRCOPYFP(bt,yh); bt&=((~(rU64)0)<<27); RRCOPYFP(bhi,bt); blo = yh-bhi; \
  ol = ((ahi*bhi-oh)+ahi*blo+alo*bhi)+alo*blo; \
}

#define rrddtoS64(ob,xh,xl) \
{ \
  double ahi=0,alo,vh,t;\
  ob = (rS64)ph;\
  vh=(double)ob;\
  ahi = ( xh - vh );\
  t = ( ahi - xh );\
  alo = (xh-(ahi-t))-(vh+t);\
  ob += (rS64)(ahi+alo+xl);\
}


#define rrddrenorm(oh,ol) { double s; s=oh+ol; ol=ol-(s-oh); oh=s; }

#define rrddmultlo(oh,ol,xh,xl,yh,yl) \
  ol = ol + ( xh*yl + xl*yh ); \

#define rrddmultlos(oh,ol,xh,yl) \
  ol = ol + ( xh*yl ); \

static void rrraise_to_power10( double *ohi, double *olo, double d, rS32 power )  // power can be -323 to +350
{
  double ph, pl;
  if ((power>=0) && (power<=22))
  {
    rrddmulthi(ph,pl,d,rrbot[power]);
  }
  else
  {
    rS32 e,et,eb;
    double p2h,p2l;

    e=power; if (power<0) e=-e; 
    et = (e*0x2c9)>>14;/* %23 */ if (et>13) et=13; eb = e-(et*23);

    ph = d; pl = 0.0;
    if (power<0)
    {
      if (eb) { --eb; rrddmulthi(ph,pl,d,rrnegbot[eb]); rrddmultlos(ph,pl,d,rrnegboterr[eb]); }
      if (et)
      { 
        rrddrenorm(ph,pl);
        --et; rrddmulthi(p2h,p2l,ph,rrnegtop[et]); rrddmultlo(p2h,p2l,ph,pl,rrnegtop[et],rrnegtoperr[et]); ph=p2h;pl=p2l;
      }
    }
    else
    {
      if (eb) 
      { 
        e = eb; if (eb>22) eb=22; e -= eb;
        rrddmulthi(ph,pl,d,rrbot[eb]); 
        if ( e ) { rrddrenorm(ph,pl); rrddmulthi(p2h,p2l,ph,rrbot[e]); rrddmultlos(p2h,p2l,rrbot[e],pl); ph=p2h;pl=p2l; }
      }
      if (et)
      {
        rrddrenorm(ph,pl);
        --et; rrddmulthi(p2h,p2l,ph,rrtop[et]); rrddmultlo(p2h,p2l,ph,pl,rrtop[et],rrtoperr[et]); ph=p2h;pl=p2l;
      }
    }
  }
  rrddrenorm(ph,pl);
  *ohi = ph; *olo = pl;
}

// given a float value, returns the significant bits in bits, and the position of the
//   decimal point in decimal_pos.  +/-INF and NAN are specified by special values
//   returned in the decimal_pos parameter.
// frac_digits is absolute normally, but if you want from first significant digits (got %g and %e), or in 0x80000000
static rS32 rrreal_to_str( char const * * start, rU32 * len, char *out, rS32 * decimal_pos, double value, rU32 frac_digits )
{
  double d;
  rS64 bits = 0;
  rS32 expo, e, ng, tens;

  d = value;
  RRCOPYFP(bits,d);
  expo = (bits >> 52) & 2047;
  ng = (rS32)(bits >> 63);
  if (ng) d=-d;

  if ( expo == 2047 ) // is nan or inf?
  {
    *start = (bits&((((rU64)1)<<52)-1)) ? "NaN" : "Inf";
    *decimal_pos =  RRSPECIAL;
    *len = 3;
    return ng;
  } 

  if ( expo == 0 ) // is zero or denormal
  {
    if ((bits<<1)==0) // do zero
    {
      *decimal_pos = 1; 
      *start = out;
      out[0] = '0'; *len = 1;
      return ng;
    }
    // find the right expo for denormals
    {
      rS64 v = ((rU64)1)<<51;
      while ((bits&v)==0) { --expo; v >>= 1; }
    }
  }

  // find the decimal exponent as well as the decimal bits of the value
  {
    double ph,pl;

    // log10 estimate - very specifically tweaked to hit or undershoot by no more than 1 of log10 of all expos 1..2046
    tens=expo-1023; tens = (tens<0)?((tens*617)/2048):(((tens*1233)/4096)+1);

    // move the significant bits into position and stick them into an int 
    rrraise_to_power10( &ph, &pl, d, 18-tens );

    // get full as much precision from double-double as possible
    rrddtoS64( bits, ph,pl );

    // check if we undershot
    if ( ((rU64)bits) >= rrtento19th ) ++tens; 
  }

  // now do the rounding in integer land
  frac_digits = ( frac_digits & 0x80000000 ) ? ( (frac_digits&0x7ffffff) + 1 ) : ( tens + frac_digits );
  if ( ( frac_digits < 24 ) )
  {
    rU32 dg = 1; if ((rU64)bits >= rrpot[9] ) dg=10; while( (rU64)bits >= rrpot[dg] ) { ++dg; if (dg==20) goto noround; }
    if ( frac_digits < dg )
    {
      rU64 r;
      // add 0.5 at the right position and round
      e = dg - frac_digits;
      if ( (rU32)e >= 24 ) goto noround;
      r = rrpot[e];
      bits = bits + (r/2);
      if ( (rU64)bits >= rrpot[dg] ) ++tens;
      bits /= r;
    } 
    noround:;
  }

  // kill long trailing runs of zeros
  if ( bits )
  {
    rU32 n; for(;;) { if ( bits<=0xffffffff ) break; if (bits%1000) goto donez; bits/=1000; } n = (rU32)bits; while ((n%1000)==0) n/=1000; bits=n; donez:;
  }

  // convert to string
  out += 64;
  e = 0; 
  for(;;)
  {
    rU32 n;
    char * o = out-8;
    // do the conversion in chunks of U32s (avoid most 64-bit divides, worth it, constant denomiators be damned)
    if (bits>=100000000) { n = (rU32)( bits % 100000000);  bits /= 100000000; } else {n = (rU32)bits; bits = 0; }
    while(n) { out-=2; *(rU16*)out=*(rU16*)&rrdiglookup[(n%100)*2]; n/=100; e+=2; }
    if (bits==0) { if ((e) && (out[0]=='0')) { ++out; --e; } break; }
    while( out!=o ) { *--out ='0'; ++e; }
  }
  
  *decimal_pos = tens;
  *start = out;
  *len = e;
  return ng;
}

#undef rrddmulthi
#undef rrddrenorm
#undef rrddmultlo
#undef rrddmultlos
#undef RRSPECIAL 
#undef RRCOPYFP
 
#endif

// clean up
#undef rU16
#undef rU32 
#undef rS32 
#undef rU64
#undef rS64
#undef RRPUBLIC_DEC
#undef RRPUBLIC_DEF
#undef RR_SPRINTF_DECORATE
#undef RR_UNALIGNED

#endif

#endif
