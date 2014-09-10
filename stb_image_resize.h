/* stb_image_resize - v0.50 - public domain image resampling
   no warranty implied; use at your own risk

   Do this:
      #define STB_IMAGE_RESIZE_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   #define STBIR_ASSERT(x) to avoid using assert.h.

   #define STBIR_MALLOC(context,size) and STBIR_FREE(context,ptr) to avoid using stdlib.h malloc.
	   Each function makes exactly one call to malloc/free, so to avoid allocations,
		pass in a temp memory block as context and return that from MALLOC.

   QUICK NOTES:
      Written with emphasis on usage and speed. Only the resize operation is
          currently supported, no rotations or translations.

      Supports arbitrary resize for separable filters. For a list of
          supported filters see the stbir_filter enum. To add a new filter,
          write a filter function and add it to stbir__filter_info_table.

   STBIR_MAX_CHANNELS: defaults to 16, if you need more, bump it up

   Revisions:
      0.50 (2014-??-??) first released version

   TODO:
      Installable filters
      Specify wrap and filter modes independently for each axis
      Resize that respects alpha test coverage
         (Reference code: FloatImage::alphaTestCoverage and FloatImage::scaleAlphaToCoverage:
         https://code.google.com/p/nvidia-texture-tools/source/browse/trunk/src/nvimage/FloatImage.cpp )

   Initial implementation by Jorge L Rodriguez, @VinoBS
*/

#ifndef STBIR_INCLUDE_STB_IMAGE_RESIZE_H
#define STBIR_INCLUDE_STB_IMAGE_RESIZE_H

typedef unsigned char stbir_uint8;

#ifdef _MSC_VER
typedef unsigned short stbir_uint16;
typedef unsigned int   stbir_uint32;
#else
#include <stdint.h>
typedef uint16_t stbir_uint16;
typedef uint32_t stbir_uint32;
#endif

#ifdef STB_IMAGE_RESIZE_STATIC
#define STBIRDEF static
#else
#ifdef __cplusplus
#define STBIRDEF extern "C"
#else
#define STBIRDEF extern
#endif
#endif


//////////////////////////////////////////////////////////////////////////////
//
// Easy-to-use API:
//
//     * "input pixels" points to an array of image data with 'num_channels' channels (e.g. RGB=3, RGBA=4)
//     * input_w is input image width (x-axis), input_h is input image height (y-axis)
//     * stride is the offset between successive rows of image data in memory, in bytes. you can
//       specify 0 to mean packed continuously in memory
//     * alpha channel is treated identically to other channels.
//     * colorspace is linear or sRGB as specified by function name
//     * returned result is 1 for success or 0 in case of an error.
//       #define STBIR_ASSERT() to trigger an assert on parameter validation errors.
//     * Memory required grows approximately linearly with input and output size, but with
//       discontinuities at input_w == output_w and input_h == output_h.
//     * These functions use a "default" resampling filter defined at compile time. To change the filter,
//       you can change the compile-time defaults by #defining STBIR_DEFAULT_FILTER_UPSAMPLE
//       and STBIR_DEFAULT_FILTER_DOWNSAMPLE, or you can use the medium-complexity API.

STBIRDEF int stbir_resize_uint8(     const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                     int num_channels);

STBIRDEF int stbir_resize_float(     const float *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           float *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                     int num_channels);


// The following functions interpret image data as gamma-corrected sRGB. 
// Specify STBIR_ALPHA_CHANNEL_NONE if you have no alpha channel,
// or otherwise provide the index of the alpha channel. Flags value
// of 0 will probably do the right thing if you're not sure what
// the flags mean.

#define STBIR_ALPHA_CHANNEL_NONE       -1

// Set this flag if your texture has premultiplied alpha. Otherwise, stbir will
// use alpha-correct resampling by multiplying the the specified alpha channel
// into all other channels before resampling, then dividing back out after.
#define STBIR_FLAG_PREMULTIPLIED_ALPHA    (1 << 0)
// The specified alpha channel should be handled as gamma-corrected value even
// when doing sRGB operations.
#define STBIR_FLAG_ALPHA_USES_COLORSPACE  (1 << 1)

STBIRDEF int stbir_resize_uint8_srgb(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                     int num_channels, int alpha_channel, int flags);


typedef enum
{
	STBIR_EDGE_CLAMP   = 1,
	STBIR_EDGE_REFLECT = 2,
	STBIR_EDGE_WRAP    = 3,
	STBIR_EDGE_ZERO    = 4,
} stbir_edge;

// This function adds the ability to specify how requests to sample off the edge of the image are handled.
STBIRDEF int stbir_resize_uint8_srgb_edgemode(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                                    unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                              int num_channels, int alpha_channel, int flags,
                                              stbir_edge edge_wrap_mode);

//////////////////////////////////////////////////////////////////////////////
//
// Medium-complexity API
//
// This extends the easy-to-use API as follows:
//
//     * Alpha-channel can be processed separately
//       * If alpha_channel is not STBIR_ALPHA_CHANNEL_NONE
//         * Alpha channel will not be gamma corrected (unless flags&STBIR_FLAG_GAMMA_CORRECT)
//         * Filters can be weighted by alpha channel (if flags&STBIR_FLAG_NONPREMUL_ALPHA)
//     * Filter can be selected explicitly
//     * uint16 image type
//     * sRGB colorspace available for all types
//     * context parameter for passing to STBIR_MALLOC

typedef enum
{
	STBIR_FILTER_DEFAULT     = 0,  // use same filter type that easy-to-use API chooses
	STBIR_FILTER_BOX         = 1,
	STBIR_FILTER_BILINEAR    = 2,
	STBIR_FILTER_BICUBIC     = 3,  // A cubic b spline
	STBIR_FILTER_CATMULLROM  = 4,
	STBIR_FILTER_MITCHELL    = 5,
} stbir_filter;

typedef enum
{
	STBIR_COLORSPACE_LINEAR,
	STBIR_COLORSPACE_SRGB,

	STBIR_MAX_COLORSPACES,
} stbir_colorspace;

// The following functions are all identical except for the type of the image data

STBIRDEF int stbir_resize_uint8_generic( const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                               unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                         int num_channels, int alpha_channel, int flags,
                                         stbir_edge edge_wrap_mode, stbir_filter filter, stbir_colorspace space, 
                                         void *alloc_context);

STBIRDEF int stbir_resize_uint16_generic(const stbir_uint16 *input_pixels  , int input_w , int input_h , int input_stride_in_bytes,
                                               stbir_uint16 *output_pixels , int output_w, int output_h, int output_stride_in_bytes,
                                         int num_channels, int alpha_channel, int flags,
                                         stbir_edge edge_wrap_mode, stbir_filter filter, stbir_colorspace space, 
                                         void *alloc_context);

STBIRDEF int stbir_resize_float_generic( const float *input_pixels         , int input_w , int input_h , int input_stride_in_bytes,
                                               float *output_pixels        , int output_w, int output_h, int output_stride_in_bytes,
                                         int num_channels, int alpha_channel, int flags,
                                         stbir_edge edge_wrap_mode, stbir_filter filter, stbir_colorspace space, 
                                         void *alloc_context);



//////////////////////////////////////////////////////////////////////////////
//
// Full-complexity API
//
// This extends the medium API as follows:
//
//	   * uint32 image type
//     * not typesafe
//     * separate filter types for each axis
//     * separate edge modes for each axis
//     * can specify scale explicitly for subpixel correctness
//     * can specify image source tile using texture coordinates

typedef enum
{
	STBIR_TYPE_UINT8 ,
	STBIR_TYPE_UINT16,
	STBIR_TYPE_UINT32,
	STBIR_TYPE_FLOAT ,

	STBIR_MAX_TYPES
} stbir_datatype;

STBIRDEF int stbir_resize(         const void *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                         void *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   stbir_datatype datatype,
                                   int num_channels, int alpha_channel, int flags,
                                   stbir_edge edge_mode_horizontal, stbir_edge edge_mode_vertical, 
                                   stbir_filter filter_horizontal,  stbir_filter filter_vertical,
                                   stbir_colorspace space, void *alloc_context);

STBIRDEF int stbir_resize_subpixel(const void *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                         void *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   stbir_datatype datatype,
                                   int num_channels, int alpha_channel, int flags,
                                   stbir_edge edge_mode_horizontal, stbir_edge edge_mode_vertical, 
                                   stbir_filter filter_horizontal,  stbir_filter filter_vertical,
                                   stbir_colorspace space, void *alloc_context,
                                   float x_scale, float y_scale,
                                   float x_offset, float y_offset);

STBIRDEF int stbir_resize_region(  const void *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                         void *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   stbir_datatype datatype,
                                   int num_channels, int alpha_channel, int flags,
                                   stbir_edge edge_mode_horizontal, stbir_edge edge_mode_vertical, 
                                   stbir_filter filter_horizontal,  stbir_filter filter_vertical,
                                   stbir_colorspace space, void *alloc_context,
                                   float s0, float t0, float s1, float t1);
// (s0, t0) & (s1, t1) are the top-left and bottom right corner (uv addressing style: [0, 1]x[0, 1]) of a region of the input image to use.


// Define this if you want a progress report.
// Example:
// void my_progress_report(float progress)
// {
//     printf("Progress: %f%%\n", progress*100);
// }
//
// #define STBIR_PROGRESS_REPORT my_progress_report

#ifndef STBIR_PROGRESS_REPORT
#define STBIR_PROGRESS_REPORT(float_0_to_1)
#endif

//
//
////   end header file   /////////////////////////////////////////////////////
#endif // STBIR_INCLUDE_STB_IMAGE_RESIZE_H





#ifdef STB_IMAGE_RESIZE_IMPLEMENTATION

#ifndef STBIR_ASSERT
#include <assert.h>
#define STBIR_ASSERT(x) assert(x)
#endif

#ifdef STBIR_DEBUG
#define STBIR__DEBUG_ASSERT STBIR_ASSERT
#else
#define STBIR__DEBUG_ASSERT
#endif

// If you hit this it means I haven't done it yet.
#define STBIR__UNIMPLEMENTED(x) STBIR_ASSERT(!(x))

// For memset
#include <string.h>

#include <math.h>

#ifndef STBIR_MALLOC
#include <stdlib.h>

#define STBIR_MALLOC(c,x) malloc(x)
#define STBIR_FREE(c,x)   free(x)
#endif

#ifndef _MSC_VER
#ifdef __cplusplus
#define stbir__inline inline
#else
#define stbir__inline
#endif
#else
#define stbir__inline __forceinline
#endif


// should produce compiler error if size is wrong
typedef unsigned char stbir__validate_uint32[sizeof(stbir_uint32) == 4 ? 1 : -1];

#ifdef _MSC_VER
#define STBIR__NOTUSED(v)  (void)(v)
#else
#define STBIR__NOTUSED(v)  (void)sizeof(v)
#endif

#define STBIR__ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))

#ifndef STBIR_DEFAULT_FILTER_UPSAMPLE
#define STBIR_DEFAULT_FILTER_UPSAMPLE    STBIR_FILTER_CATMULLROM
#endif

#ifndef STBIR_DEFAULT_FILTER_DOWNSAMPLE
#define STBIR_DEFAULT_FILTER_DOWNSAMPLE  STBIR_FILTER_MITCHELL
#endif

#ifndef STBIR_MAX_CHANNELS
#define STBIR_MAX_CHANNELS  16
#endif

// must match stbir_datatype
static unsigned char stbir__type_size[] = {
	1, // STBIR_TYPE_UINT8
	2, // STBIR_TYPE_UINT16
	4, // STBIR_TYPE_UINT32
	4, // STBIR_TYPE_FLOAT
};

// Kernel function centered at 0
typedef float (stbir__kernel_fn)(float x);

typedef struct
{
	stbir__kernel_fn* kernel;
	float support;
} stbir__filter_info;

// When upsampling, the contributors are which source pixels contribute.
// When downsampling, the contributors are which destination pixels are contributed to.
typedef struct
{
	int n0; // First contributing pixel
	int n1; // Last contributing pixel
} stbir__contributors;

typedef struct
{
	const void* input_data;
	int input_w;
	int input_h;
	int input_stride_bytes;

	void* output_data;
	int output_w;
	int output_h;
	int output_stride_bytes;

	float s0, t0, s1, t1;

	float horizontal_shift; // Units: output pixels
	float vertical_shift;   // Units: output pixels
	float horizontal_scale;
	float vertical_scale;

	int channels;
	int alpha_channel;
	stbir_uint32 flags;
	stbir_datatype type;
	stbir_filter horizontal_filter;
	stbir_filter vertical_filter;
	stbir_edge edge_horizontal;
	stbir_edge edge_vertical;
	stbir_colorspace colorspace;

	stbir__contributors* horizontal_contributors;
	float* horizontal_coefficients;

	stbir__contributors vertical_contributors;
	float* vertical_coefficients;

	int decode_buffer_pixels;
	float* decode_buffer;

	float* horizontal_buffer;

	int ring_buffer_length_bytes; // The length of an individual entry in the ring buffer. The total number of ring buffers is stbir__get_filter_pixel_width(filter)
	int ring_buffer_first_scanline;
	int ring_buffer_last_scanline;
	int ring_buffer_begin_index;
	float* ring_buffer;

	float* encode_buffer; // A temporary buffer to store floats so we don't lose precision while we do multiply-adds.

	int horizontal_contributors_size;
	int horizontal_coefficients_size;
	int vertical_coefficients_size;
	int decode_buffer_size;
	int horizontal_buffer_size;
	int ring_buffer_size;
	int encode_buffer_size;
} stbir__info;

static stbir__inline int stbir__min(int a, int b)
{
	return a < b ? a : b;
}

static stbir__inline int stbir__max(int a, int b)
{
	return a > b ? a : b;
}

static stbir__inline float stbir__saturate(float x)
{
	if (x < 0)
		return 0;

	if (x > 1)
		return 1;

	return x;
}

static float stbir__srgb_uchar_to_linear_float[256] = {
	0.000000f, 0.000304f, 0.000607f, 0.000911f, 0.001214f, 0.001518f, 0.001821f, 0.002125f, 0.002428f, 0.002732f, 0.003035f,
	0.003347f, 0.003677f, 0.004025f, 0.004391f, 0.004777f, 0.005182f, 0.005605f, 0.006049f, 0.006512f, 0.006995f, 0.007499f,
	0.008023f, 0.008568f, 0.009134f, 0.009721f, 0.010330f, 0.010960f, 0.011612f, 0.012286f, 0.012983f, 0.013702f, 0.014444f,
	0.015209f, 0.015996f, 0.016807f, 0.017642f, 0.018500f, 0.019382f, 0.020289f, 0.021219f, 0.022174f, 0.023153f, 0.024158f,
	0.025187f, 0.026241f, 0.027321f, 0.028426f, 0.029557f, 0.030713f, 0.031896f, 0.033105f, 0.034340f, 0.035601f, 0.036889f,
	0.038204f, 0.039546f, 0.040915f, 0.042311f, 0.043735f, 0.045186f, 0.046665f, 0.048172f, 0.049707f, 0.051269f, 0.052861f,
	0.054480f, 0.056128f, 0.057805f, 0.059511f, 0.061246f, 0.063010f, 0.064803f, 0.066626f, 0.068478f, 0.070360f, 0.072272f,
	0.074214f, 0.076185f, 0.078187f, 0.080220f, 0.082283f, 0.084376f, 0.086500f, 0.088656f, 0.090842f, 0.093059f, 0.095307f,
	0.097587f, 0.099899f, 0.102242f, 0.104616f, 0.107023f, 0.109462f, 0.111932f, 0.114435f, 0.116971f, 0.119538f, 0.122139f,
	0.124772f, 0.127438f, 0.130136f, 0.132868f, 0.135633f, 0.138432f, 0.141263f, 0.144128f, 0.147027f, 0.149960f, 0.152926f,
	0.155926f, 0.158961f, 0.162029f, 0.165132f, 0.168269f, 0.171441f, 0.174647f, 0.177888f, 0.181164f, 0.184475f, 0.187821f,
	0.191202f, 0.194618f, 0.198069f, 0.201556f, 0.205079f, 0.208637f, 0.212231f, 0.215861f, 0.219526f, 0.223228f, 0.226966f,
	0.230740f, 0.234551f, 0.238398f, 0.242281f, 0.246201f, 0.250158f, 0.254152f, 0.258183f, 0.262251f, 0.266356f, 0.270498f,
	0.274677f, 0.278894f, 0.283149f, 0.287441f, 0.291771f, 0.296138f, 0.300544f, 0.304987f, 0.309469f, 0.313989f, 0.318547f,
	0.323143f, 0.327778f, 0.332452f, 0.337164f, 0.341914f, 0.346704f, 0.351533f, 0.356400f, 0.361307f, 0.366253f, 0.371238f,
	0.376262f, 0.381326f, 0.386430f, 0.391573f, 0.396755f, 0.401978f, 0.407240f, 0.412543f, 0.417885f, 0.423268f, 0.428691f,
	0.434154f, 0.439657f, 0.445201f, 0.450786f, 0.456411f, 0.462077f, 0.467784f, 0.473532f, 0.479320f, 0.485150f, 0.491021f,
	0.496933f, 0.502887f, 0.508881f, 0.514918f, 0.520996f, 0.527115f, 0.533276f, 0.539480f, 0.545725f, 0.552011f, 0.558340f,
	0.564712f, 0.571125f, 0.577581f, 0.584078f, 0.590619f, 0.597202f, 0.603827f, 0.610496f, 0.617207f, 0.623960f, 0.630757f,
	0.637597f, 0.644480f, 0.651406f, 0.658375f, 0.665387f, 0.672443f, 0.679543f, 0.686685f, 0.693872f, 0.701102f, 0.708376f,
	0.715694f, 0.723055f, 0.730461f, 0.737911f, 0.745404f, 0.752942f, 0.760525f, 0.768151f, 0.775822f, 0.783538f, 0.791298f,
	0.799103f, 0.806952f, 0.814847f, 0.822786f, 0.830770f, 0.838799f, 0.846873f, 0.854993f, 0.863157f, 0.871367f, 0.879622f,
	0.887923f, 0.896269f, 0.904661f, 0.913099f, 0.921582f, 0.930111f, 0.938686f, 0.947307f, 0.955974f, 0.964686f, 0.973445f,
	0.982251f, 0.991102f, 1.0f
};

// sRGB transition values, scaled by 1<<28
static int stbir__srgb_offset_to_linear_scaled[256] =
{
		40579,    121738,    202897,    284056,    365216,    446375,    527534,	608693,
	   689852,    771011,    852421,    938035,   1028466,   1123787,   1224073,   1329393,
	  1439819,   1555418,   1676257,   1802402,   1933917,   2070867,   2213313,   2361317,
	  2514938,   2674237,   2839271,   3010099,   3186776,   3369359,   3557903,   3752463,
	  3953090,   4159840,   4372764,   4591913,   4817339,   5049091,   5287220,   5531775,
	  5782804,   6040356,   6304477,   6575216,   6852618,   7136729,   7427596,   7725263,
	  8029775,   8341176,   8659511,   8984821,   9317151,   9656544,  10003040,  10356683,
	 10717513,  11085572,  11460901,  11843540,  12233529,  12630908,  13035717,  13447994,
	 13867779,  14295110,  14730025,  15172563,  15622760,  16080655,  16546285,  17019686,
	 17500894,  17989948,  18486882,  18991734,  19504536,  20025326,  20554138,  21091010,
	 21635972,  22189062,  22750312,  23319758,  23897432,  24483368,  25077600,  25680162,
	 26291086,  26910406,  27538152,  28174360,  28819058,  29472282,  30134062,  30804430,
	 31483418,  32171058,  32867378,  33572412,  34286192,  35008744,  35740104,  36480296,
	 37229356,  37987316,  38754196,  39530036,  40314860,  41108700,  41911584,  42723540,
	 43544600,  44374792,  45214140,  46062680,  46920440,  47787444,  48663720,  49549300,
	 50444212,  51348480,  52262136,  53185204,  54117712,  55059688,  56011160,  56972156,
	 57942704,  58922824,  59912552,  60911908,  61920920,  62939616,  63968024,  65006168,
	 66054072,  67111760,  68179272,  69256616,  70343832,  71440936,  72547952,  73664920,
	 74791848,  75928776,  77075720,  78232704,  79399760,  80576904,  81764168,  82961576,
	 84169152,  85386920,  86614904,  87853120,  89101608,  90360384,  91629480,  92908904,
	 94198688,  95498864,  96809440,  98130456,  99461928, 100803872, 102156320, 103519296,
	104892824, 106276920, 107671616, 109076928, 110492880, 111919504, 113356808, 114804824,
	116263576, 117733080, 119213360, 120704448, 122206352, 123719104, 125242720, 126777232,
	128322648, 129879000, 131446312, 133024600, 134613888, 136214192, 137825552, 139447968,
	141081456, 142726080, 144381808, 146048704, 147726768, 149416016, 151116496, 152828192,
	154551168, 156285408, 158030944, 159787808, 161556000, 163335568, 165126512, 166928864,
	168742640, 170567856, 172404544, 174252704, 176112384, 177983568, 179866320, 181760640,
	183666528, 185584032, 187513168, 189453952, 191406400, 193370544, 195346384, 197333952,
	199333264, 201344352, 203367216, 205401904, 207448400, 209506752, 211576960, 213659056,
	215753056, 217858976, 219976832, 222106656, 224248464, 226402272, 228568096, 230745952,
	232935872, 235137872, 237351968, 239578176, 241816512, 244066992, 246329648, 248604512,
	250891568, 253190848, 255502368, 257826160, 260162240, 262510608, 264871312, 267244336,
};

static float stbir__srgb_to_linear(float f)
{
	if (f <= 0.04045f)
		return f / 12.92f;
	else
		return (float)pow((f + 0.055f) / 1.055f, 2.4f);
}

static float stbir__linear_to_srgb(float f)
{
	if (f <= 0.0031308f)
		return f * 12.92f;
	else
		return 1.055f * (float)pow(f, 1 / 2.4f) - 0.055f;
}

static unsigned char stbir__linear_to_srgb_uchar(float f)
{
	int x = (int) (f * (1 << 28)); // has headroom so you don't need to clamp
	int v = 0;

	if (x >= stbir__srgb_offset_to_linear_scaled[ v+128 ]) v += 128;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+ 64 ]) v +=  64;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+ 32 ]) v +=  32;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+ 16 ]) v +=  16;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+  8 ]) v +=   8;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+  4 ]) v +=   4;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+  2 ]) v +=   2;
	if (x >= stbir__srgb_offset_to_linear_scaled[ v+  1 ]) v +=   1;
	return (unsigned char) v;
}

static float stbir__filter_box(float x)
{
	if (x <= -0.5f)
		return 0;
	else if (x > 0.5f)
		return 0;
	else
		return 1;
}

static float stbir__filter_bilinear(float x)
{
	x = (float)fabs(x);

	if (x <= 1.0f)
		return 1 - x;
	else
		return 0;
}

static float stbir__filter_bicubic(float x)
{
	x = (float)fabs(x);

	if (x < 1.0f)
		return (4 + x*x*(3*x - 6))/6;
	else if (x < 2.0f)
		return (8 + x*(-12 + x*(6 - x)))/6;

	return (0.0f);
}

static float stbir__filter_catmullrom(float x)
{
	x = (float)fabs(x);

	if (x < 1.0f)
		return 1 - x*x*(2.5f - 1.5f*x);
	else if (x < 2.0f)
		return 2 - x*(4 + x*(0.5f*x - 2.5f));

	return (0.0f);
}

static float stbir__filter_mitchell(float x)
{
	x = (float)fabs(x);

	if (x < 1.0f)
		return (16 + x*x*(21 * x - 36))/18;
	else if (x < 2.0f)
		return (32 + x*(-60 + x*(36 - 7*x)))/18;

	return (0.0f);
}

static stbir__filter_info stbir__filter_info_table[] = {
		{ NULL,                    0.0f },
		{ stbir__filter_box    ,    0.5f },
		{ stbir__filter_bilinear,   1.0f },
		{ stbir__filter_bicubic,    2.0f },
		{ stbir__filter_catmullrom, 2.0f },
		{ stbir__filter_mitchell,   2.0f },
};

stbir__inline static int stbir__use_upsampling(float ratio)
{
	return ratio > 1;
}

stbir__inline static int stbir__use_width_upsampling(stbir__info* stbir_info)
{
	return stbir__use_upsampling(stbir_info->horizontal_scale);
}

stbir__inline static int stbir__use_height_upsampling(stbir__info* stbir_info)
{
	return stbir__use_upsampling(stbir_info->vertical_scale);
}

// This is the maximum number of input samples that can affect an output sample
// with the given filter
stbir__inline static int stbir__get_filter_pixel_width(stbir_filter filter, float scale)
{
	STBIR_ASSERT(filter != 0);
	STBIR_ASSERT(filter < STBIR__ARRAY_SIZE(stbir__filter_info_table));

	if (stbir__use_upsampling(scale))
		return (int)ceil(stbir__filter_info_table[filter].support * 2);
	else
		return (int)ceil(stbir__filter_info_table[filter].support * 2 / scale);
}

stbir__inline static int stbir__get_filter_pixel_width_horizontal(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->horizontal_filter, stbir_info->horizontal_scale);
}

stbir__inline static int stbir__get_filter_pixel_width_vertical(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->vertical_filter, stbir_info->vertical_scale);
}

// This is how much to expand buffers to account for filters seeking outside
// the image boundaries.
stbir__inline static int stbir__get_filter_pixel_margin(stbir_filter filter, float scale)
{
	return stbir__get_filter_pixel_width(filter, scale) / 2;
}

stbir__inline static int stbir__get_filter_pixel_margin_horizontal(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->horizontal_filter, stbir_info->horizontal_scale) / 2;
}

stbir__inline static int stbir__get_filter_pixel_margin_vertical(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->vertical_filter, stbir_info->vertical_scale) / 2;
}

stbir__inline static int stbir__get_horizontal_contributors(stbir__info* info)
{
	if (stbir__use_upsampling(info->horizontal_scale))
		return info->output_w;
	else
		return (info->input_w + stbir__get_filter_pixel_margin(info->horizontal_filter, info->horizontal_scale) * 2);
}

stbir__inline static int stbir__get_total_coefficients(stbir__info* info)
{
	return stbir__get_horizontal_contributors(info)
	     * stbir__get_filter_pixel_width     (info->horizontal_filter, info->horizontal_scale);
}

stbir__inline static stbir__contributors* stbir__get_contributor(stbir__info* stbir_info, int n)
{
	STBIR__DEBUG_ASSERT(n >= 0 && n < stbir__get_horizontal_contributors(stbir_info));
	return &stbir_info->horizontal_contributors[n];
}

stbir__inline static float* stbir__get_coefficient(stbir__info* stbir_info, int n, int c)
{
	int width =	stbir__get_filter_pixel_width(stbir_info->horizontal_filter, stbir_info->horizontal_scale);
	return &stbir_info->horizontal_coefficients[width*n + c];
}

static int stbir__edge_wrap_slow(stbir_edge edge, int n, int max)
{
	switch (edge)
	{
	case STBIR_EDGE_ZERO:
		return 0; // we'll decode the wrong pixel here, and then overwrite with 0s later

	case STBIR_EDGE_CLAMP:
		if (n < 0)
			return 0;

		if (n >= max)
			return max - 1;

		return n; // NOTREACHED

	case STBIR_EDGE_REFLECT:
	{
		if (n < 0)
		{
			if (n < max)
				return -n;
			else
				return max - 1;
		}

		if (n >= max)
		{
			int max2 = max * 2;
			if (n >= max2)
				return 0;
			else
				return max2 - n - 1;
		}

		return n; // NOTREACHED
	}

	case STBIR_EDGE_WRAP:
		if (n >= 0)
			return (n % max);
		else
		{
			int m = (-n) % max;

			if (m != 0)
				m = max - m;

			return (m);
		}
		return n;  // NOTREACHED

	default:
		STBIR__UNIMPLEMENTED("Unimplemented edge type");
		return 0;
	}
}

stbir__inline static int stbir__edge_wrap(stbir_edge edge, int n, int max)
{
	// avoid per-pixel switch
	if (n >= 0 && n < max)
		return n;
	return stbir__edge_wrap_slow(edge, n, max);
}

// What input pixels contribute to this output pixel?
static void stbir__calculate_sample_range_upsample(int n, float out_filter_radius, float scale_ratio, float out_shift, int* in_first_pixel, int* in_last_pixel, float* in_center_of_out)
{
	float out_pixel_center = (float)n + 0.5f;
	float out_pixel_influence_lowerbound = out_pixel_center - out_filter_radius;
	float out_pixel_influence_upperbound = out_pixel_center + out_filter_radius;

	float in_pixel_influence_lowerbound = (out_pixel_influence_lowerbound + out_shift) / scale_ratio;
	float in_pixel_influence_upperbound = (out_pixel_influence_upperbound + out_shift) / scale_ratio;

	*in_center_of_out = (out_pixel_center + out_shift) / scale_ratio;
	*in_first_pixel = (int)(floor(in_pixel_influence_lowerbound + 0.5));
	*in_last_pixel = (int)(floor(in_pixel_influence_upperbound - 0.5));
}

// What output pixels does this input pixel contribute to?
static void stbir__calculate_sample_range_downsample(int n, float in_pixels_radius, float scale_ratio, float out_shift, int* out_first_pixel, int* out_last_pixel, float* out_center_of_in)
{
	float in_pixel_center = (float)n + 0.5f;
	float in_pixel_influence_lowerbound = in_pixel_center - in_pixels_radius;
	float in_pixel_influence_upperbound = in_pixel_center + in_pixels_radius;

	float out_pixel_influence_lowerbound = in_pixel_influence_lowerbound * scale_ratio - out_shift;
	float out_pixel_influence_upperbound = in_pixel_influence_upperbound * scale_ratio - out_shift;

	*out_center_of_in = in_pixel_center * scale_ratio - out_shift;
	*out_first_pixel = (int)(floor(out_pixel_influence_lowerbound + 0.5));
	*out_last_pixel = (int)(floor(out_pixel_influence_upperbound - 0.5));
}

static void stbir__calculate_coefficients_upsample(stbir__info* stbir_info, stbir_filter filter, int in_first_pixel, int in_last_pixel, float in_center_of_out, stbir__contributors* contributor, float* coefficient_group)
{
	int i;
	float total_filter = 0;
	float filter_scale;

	STBIR__DEBUG_ASSERT(in_last_pixel - in_first_pixel <= (int)ceil(stbir__filter_info_table[filter].support * 2)); // Taken directly from stbir__get_filter_pixel_width() which we can't call because we don't know if we're horizontal or vertical.

	contributor->n0 = in_first_pixel;
	contributor->n1 = in_last_pixel;

	STBIR__DEBUG_ASSERT(contributor->n1 >= contributor->n0);

	for (i = 0; i <= in_last_pixel - in_first_pixel; i++)
	{
		float in_pixel_center = (float)(i + in_first_pixel) + 0.5f;
		total_filter += coefficient_group[i] = stbir__filter_info_table[filter].kernel(in_center_of_out - in_pixel_center);
	}

	STBIR__DEBUG_ASSERT(total_filter > 0.9);
	STBIR__DEBUG_ASSERT(total_filter < 1.1f); // Make sure it's not way off.

	// Make sure the sum of all coefficients is 1.
	filter_scale = 1 / total_filter;

	for (i = 0; i <= in_last_pixel - in_first_pixel; i++)
		coefficient_group[i] *= filter_scale;
}

static void stbir__calculate_coefficients_downsample(stbir__info* stbir_info, stbir_filter filter, float scale_ratio, int out_first_pixel, int out_last_pixel, float out_center_of_in, stbir__contributors* contributor, float* coefficient_group)
{
	int i;

	STBIR__DEBUG_ASSERT(out_last_pixel - out_first_pixel <= (int)ceil(stbir__filter_info_table[filter].support * 2 / scale_ratio)); // Taken directly from stbir__get_filter_pixel_width() which we can't call because we don't know if we're horizontal or vertical.

	contributor->n0 = out_first_pixel;
	contributor->n1 = out_last_pixel;

	STBIR__DEBUG_ASSERT(contributor->n1 >= contributor->n0);

	for (i = 0; i <= out_last_pixel - out_first_pixel; i++)
	{
		float out_pixel_center = (float)(i + out_first_pixel) + 0.5f;
		float x = out_pixel_center - out_center_of_in;
		coefficient_group[i] = stbir__filter_info_table[filter].kernel(x) * scale_ratio;
	}
}

static void stbir__normalize_downsample_coefficients(stbir__info* stbir_info)
{
	int num_contributors = stbir__get_horizontal_contributors(stbir_info);
	int i;
	for (i = 0; i < stbir_info->output_w; i++)
	{
		float total = 0;
		int j;
		for (j = 0; j < num_contributors; j++)
		{
			if (i >= stbir_info->horizontal_contributors[j].n0 && i <= stbir_info->horizontal_contributors[j].n1)
			{
				float coefficient = *stbir__get_coefficient(stbir_info, j, i - stbir_info->horizontal_contributors[j].n0);
				total += coefficient;
			}
			else if (i < stbir_info->horizontal_contributors[j].n0)
				break;
		}

		STBIR__DEBUG_ASSERT(total > 0.9f);
		STBIR__DEBUG_ASSERT(total < 1.1f);

		float scale = 1 / total;

		for (j = 0; j < num_contributors; j++)
		{
			if (i >= stbir_info->horizontal_contributors[j].n0 && i <= stbir_info->horizontal_contributors[j].n1)
				*stbir__get_coefficient(stbir_info, j, i - stbir_info->horizontal_contributors[j].n0) *= scale;
			else if (i < stbir_info->horizontal_contributors[j].n0)
				break;
		}
	}

	// Using min to avoid writing into invalid pixels.
	for (i = 0; i < num_contributors; i++)
	{
		stbir__contributors* contributors = &stbir_info->horizontal_contributors[i];
		STBIR__DEBUG_ASSERT(contributors->n1 >= contributors->n0);

		contributors->n1 = stbir__min(contributors->n1, stbir_info->output_w - 1);
	}
}

// Each scan line uses the same kernel values so we should calculate the kernel
// values once and then we can use them for every scan line.
static void stbir__calculate_horizontal_filters(stbir__info* stbir_info)
{
	int n;
	float scale_ratio = stbir_info->horizontal_scale;

	int total_contributors = stbir__get_horizontal_contributors(stbir_info);

	if (stbir__use_width_upsampling(stbir_info))
	{
		float out_pixels_radius = stbir__filter_info_table[stbir_info->horizontal_filter].support * scale_ratio;

		// Looping through out pixels
		for (n = 0; n < total_contributors; n++)
		{
			float in_center_of_out; // Center of the current out pixel in the in pixel space
			int in_first_pixel, in_last_pixel;

			stbir__calculate_sample_range_upsample(n, out_pixels_radius, scale_ratio, stbir_info->horizontal_shift, &in_first_pixel, &in_last_pixel, &in_center_of_out);

			stbir__calculate_coefficients_upsample(stbir_info, stbir_info->horizontal_filter, in_first_pixel, in_last_pixel, in_center_of_out, stbir__get_contributor(stbir_info, n), stbir__get_coefficient(stbir_info, n, 0));
		}
	}
	else
	{
		float in_pixels_radius = stbir__filter_info_table[stbir_info->horizontal_filter].support / scale_ratio;

		// Looping through in pixels
		for (n = 0; n < total_contributors; n++)
		{
			float out_center_of_in; // Center of the current out pixel in the in pixel space
			int out_first_pixel, out_last_pixel;
			int n_adjusted = n - stbir__get_filter_pixel_margin_horizontal(stbir_info);

			stbir__calculate_sample_range_downsample(n_adjusted, in_pixels_radius, scale_ratio, stbir_info->horizontal_shift, &out_first_pixel, &out_last_pixel, &out_center_of_in);

			stbir__calculate_coefficients_downsample(stbir_info, stbir_info->horizontal_filter, scale_ratio, out_first_pixel, out_last_pixel, out_center_of_in, stbir__get_contributor(stbir_info, n), stbir__get_coefficient(stbir_info, n, 0));
		}

		stbir__normalize_downsample_coefficients(stbir_info);
	}
}

static float* stbir__get_decode_buffer(stbir__info* stbir_info)
{
	// The 0 index of the decode buffer starts after the margin. This makes
	// it okay to use negative indexes on the decode buffer.
	return &stbir_info->decode_buffer[stbir__get_filter_pixel_margin_horizontal(stbir_info) * stbir_info->channels];
}

#define STBIR__DECODE(type, colorspace) ((type) * (STBIR_MAX_COLORSPACES) + (colorspace))

static void stbir__decode_scanline(stbir__info* stbir_info, int n)
{
	int c;
	int channels = stbir_info->channels;
	int alpha_channel = stbir_info->alpha_channel;
	int type = stbir_info->type;
	int colorspace = stbir_info->colorspace;
	int input_w = stbir_info->input_w;
	int input_stride_bytes = stbir_info->input_stride_bytes;
	float* decode_buffer = stbir__get_decode_buffer(stbir_info);
	stbir_edge edge_horizontal = stbir_info->edge_horizontal;
	stbir_edge edge_vertical = stbir_info->edge_vertical;
	int in_buffer_row_offset = stbir__edge_wrap(edge_vertical, n, stbir_info->input_h) * input_stride_bytes;
	const void* input_data = (char *) stbir_info->input_data + in_buffer_row_offset;
	int max_x = input_w + stbir__get_filter_pixel_margin_horizontal(stbir_info);
	int decode = STBIR__DECODE(type, colorspace);

	int x = -stbir__get_filter_pixel_margin_horizontal(stbir_info);

	// special handling for STBIR_EDGE_ZERO because it needs to return an item that doesn't appear in the input,
	// and we want to avoid paying overhead on every pixel if not STBIR_EDGE_ZERO
	if (edge_vertical == STBIR_EDGE_ZERO && (n < 0 || n >= stbir_info->input_h))
	{
		for (; x < max_x; x++)
			for (c = 0; c < channels; c++)
				decode_buffer[x*channels + c] = 0;
		return;
	}

	switch (decode)
	{
	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = ((float)((const unsigned char*)input_data)[input_pixel_index + c]) / 255;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_uchar_to_linear_float[((const unsigned char*)input_data)[input_pixel_index + c]];

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				decode_buffer[decode_pixel_index + alpha_channel] = ((float)((const unsigned char*)input_data)[input_pixel_index + alpha_channel]) / 255;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = ((float)((const unsigned short*)input_data)[input_pixel_index + c]) / 65535;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_to_linear(((float)((const unsigned short*)input_data)[input_pixel_index + c]) / 65535);

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				decode_buffer[decode_pixel_index + alpha_channel] = ((float)((const unsigned short*)input_data)[input_pixel_index + alpha_channel]) / 65535;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = (float)(((double)((const unsigned int*)input_data)[input_pixel_index + c]) / 4294967295);
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_to_linear((float)(((double)((const unsigned int*)input_data)[input_pixel_index + c]) / 4294967295));

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				decode_buffer[decode_pixel_index + alpha_channel] = (float)(((double)((const unsigned int*)input_data)[input_pixel_index + alpha_channel]) / 4294967295);
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = ((const float*)input_data)[input_pixel_index + c];
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_to_linear(((const float*)input_data)[input_pixel_index + c]);

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				decode_buffer[decode_pixel_index + alpha_channel] = ((const float*)input_data)[input_pixel_index + alpha_channel];
		}

		break;

	default:
		STBIR__UNIMPLEMENTED("Unknown type/colorspace/channels combination.");
		break;
	}

	if (!(stbir_info->flags & STBIR_FLAG_PREMULTIPLIED_ALPHA))
	{
		for (x = -stbir__get_filter_pixel_margin_horizontal(stbir_info); x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			float alpha = decode_buffer[decode_pixel_index + alpha_channel];

			if (alpha == 0)
				alpha = decode_buffer[decode_pixel_index + alpha_channel] = (float)1 / 17179869184; // 1/2^34 should be small enough that it won't affect anything.

			for (c = 0; c < channels; c++)
			{
				if (c == alpha_channel)
					continue;

				decode_buffer[decode_pixel_index + c] *= alpha;
			}
		}
	}

	if (edge_horizontal == STBIR_EDGE_ZERO)
	{
		for (x = -stbir__get_filter_pixel_margin_horizontal(stbir_info); x < 0; x++)
		{
			for (c = 0; c < channels; c++)
				decode_buffer[x*channels + c] = 0;
		}
		for (x = input_w; x < max_x; x++)
		{
			for (c = 0; c < channels; c++)
				decode_buffer[x*channels + c] = 0;
		}
	}
}

static float* stbir__get_ring_buffer_entry(float* ring_buffer, int index, int ring_buffer_length)
{
	return &ring_buffer[index * ring_buffer_length];
}

static float* stbir__add_empty_ring_buffer_entry(stbir__info* stbir_info, int n)
{
	int ring_buffer_index;
	float* ring_buffer;

	if (stbir_info->ring_buffer_begin_index < 0)
	{
		ring_buffer_index = stbir_info->ring_buffer_begin_index = 0;
		stbir_info->ring_buffer_first_scanline = n;
	}
	else
	{
		ring_buffer_index = (stbir_info->ring_buffer_begin_index + (stbir_info->ring_buffer_last_scanline - stbir_info->ring_buffer_first_scanline) + 1) % stbir__get_filter_pixel_width_vertical(stbir_info);
		STBIR__DEBUG_ASSERT(ring_buffer_index != stbir_info->ring_buffer_begin_index);
	}

	ring_buffer = stbir__get_ring_buffer_entry(stbir_info->ring_buffer, ring_buffer_index, stbir_info->ring_buffer_length_bytes / sizeof(float));
	memset(ring_buffer, 0, stbir_info->ring_buffer_length_bytes);

	stbir_info->ring_buffer_last_scanline = n;

	return ring_buffer;
}


static void stbir__resample_horizontal_upsample(stbir__info* stbir_info, int n, float* output_buffer)
{
	int x, k;
	int output_w = stbir_info->output_w;
	int kernel_pixel_width = stbir__get_filter_pixel_width_horizontal(stbir_info);
	int channels = stbir_info->channels;
	float* decode_buffer = stbir__get_decode_buffer(stbir_info);
	stbir__contributors* horizontal_contributors = stbir_info->horizontal_contributors;
	float* horizontal_coefficients = stbir_info->horizontal_coefficients;

	for (x = 0; x < output_w; x++)
	{
		int n0 = horizontal_contributors[x].n0;
		int n1 = horizontal_contributors[x].n1;

		int out_pixel_index = x * channels;
		int coefficient_group_index = x * kernel_pixel_width;
		int coefficient_counter = 0;

		STBIR__DEBUG_ASSERT(n1 >= n0);
		STBIR__DEBUG_ASSERT(n0 >= -stbir__get_filter_pixel_margin_horizontal(stbir_info));
		STBIR__DEBUG_ASSERT(n1 >= -stbir__get_filter_pixel_margin_horizontal(stbir_info));
		STBIR__DEBUG_ASSERT(n0 < stbir_info->input_w + stbir__get_filter_pixel_margin_horizontal(stbir_info));
		STBIR__DEBUG_ASSERT(n1 < stbir_info->input_w + stbir__get_filter_pixel_margin_horizontal(stbir_info));

		for (k = n0; k <= n1; k++)
		{
			int coefficient_index = coefficient_group_index + (coefficient_counter++);
			int in_pixel_index = k * channels;
			float coefficient = horizontal_coefficients[coefficient_index];

			int c;
			for (c = 0; c < channels; c++)
				output_buffer[out_pixel_index + c] += decode_buffer[in_pixel_index + c] * coefficient;
		}
	}
}

static void stbir__resample_horizontal_downsample(stbir__info* stbir_info, int n, float* output_buffer)
{
	int x, k;
	int input_w = stbir_info->input_w;
	int output_w = stbir_info->output_w;
	int kernel_pixel_width = stbir__get_filter_pixel_width_horizontal(stbir_info);
	int channels = stbir_info->channels;
	float* decode_buffer = stbir__get_decode_buffer(stbir_info);
	stbir__contributors* horizontal_contributors = stbir_info->horizontal_contributors;
	float* horizontal_coefficients = stbir_info->horizontal_coefficients;
	int filter_pixel_margin = stbir__get_filter_pixel_margin_horizontal(stbir_info);
	int max_x = input_w + filter_pixel_margin * 2;

	STBIR__DEBUG_ASSERT(!stbir__use_width_upsampling(stbir_info));

	for (x = 0; x < max_x; x++)
	{
		int n0 = horizontal_contributors[x].n0;
		int n1 = horizontal_contributors[x].n1;

		int in_x = x - filter_pixel_margin;
		int in_pixel_index = in_x * channels;
		int max_n = n1;
		int coefficient_group = x*kernel_pixel_width;

		// Using max to avoid writing into invalid pixels.
		for (k = stbir__max(n0, 0); k <= max_n; k++)
		{
			int coefficient_index = (k - n0) + coefficient_group;
			int out_pixel_index = k * channels;
			float coefficient = horizontal_coefficients[coefficient_index];

			int c;
			for (c = 0; c < channels; c++)
				output_buffer[out_pixel_index + c] += decode_buffer[in_pixel_index + c] * coefficient;
		}
	}
}

static void stbir__decode_and_resample_upsample(stbir__info* stbir_info, int n)
{
	// Decode the nth scanline from the source image into the decode buffer.
	stbir__decode_scanline(stbir_info, n);

	// Now resample it into the ring buffer.
	if (stbir__use_width_upsampling(stbir_info))
		stbir__resample_horizontal_upsample(stbir_info, n, stbir__add_empty_ring_buffer_entry(stbir_info, n));
	else
		stbir__resample_horizontal_downsample(stbir_info, n, stbir__add_empty_ring_buffer_entry(stbir_info, n));

	// Now it's sitting in the ring buffer ready to be used as source for the vertical sampling.
}

static void stbir__decode_and_resample_downsample(stbir__info* stbir_info, int n)
{
	// Decode the nth scanline from the source image into the decode buffer.
	stbir__decode_scanline(stbir_info, n);

	memset(stbir_info->horizontal_buffer, 0, stbir_info->output_w * stbir_info->channels * sizeof(float));

	// Now resample it into the horizontal buffer.
	if (stbir__use_width_upsampling(stbir_info))
		stbir__resample_horizontal_upsample(stbir_info, n, stbir_info->horizontal_buffer);
	else
		stbir__resample_horizontal_downsample(stbir_info, n, stbir_info->horizontal_buffer);

	// Now it's sitting in the horizontal buffer ready to be distributed into the ring buffers.
}

// Get the specified scan line from the ring buffer.
static float* stbir__get_ring_buffer_scanline(int get_scanline, float* ring_buffer, int begin_index, int first_scanline, int ring_buffer_size, int ring_buffer_length)
{
	int ring_buffer_index = (begin_index + (get_scanline - first_scanline)) % ring_buffer_size;
	return stbir__get_ring_buffer_entry(ring_buffer, ring_buffer_index, ring_buffer_length);
}


// @OPTIMIZE: embed stbir__encode_pixel and move switch out of per-pixel loop
static void stbir__encode_scanline(stbir__info* stbir_info, int num_pixels, void *output_buffer, float *encode_buffer, int channels, int alpha_channel, int decode)
{
	int x;
	int n;

	if (!(stbir_info->flags&STBIR_FLAG_PREMULTIPLIED_ALPHA)) 
	{
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;
			float alpha = encode_buffer[encode_pixel_index + alpha_channel];
			STBIR__DEBUG_ASSERT(alpha > 0);
			float reciprocal_alpha = alpha ? 1.0f / alpha : 0;
			for (n = 0; n < channels; n++)
				if (n != alpha_channel)
					encode_buffer[encode_pixel_index + n] *= reciprocal_alpha;
		}
	}

	switch (decode)
	{
	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_LINEAR):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((unsigned char*)output_buffer)[output_pixel_index + n] = (unsigned char)(round(stbir__saturate(encode_buffer[encode_pixel_index + n]) * 255));
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_SRGB):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;


			for (n = 0; n < channels; n++)
				((unsigned char*)output_buffer)[output_pixel_index + n] = stbir__linear_to_srgb_uchar(encode_buffer[encode_pixel_index + n]);

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				((unsigned char*)output_buffer)[output_pixel_index + alpha_channel] = (unsigned char)(round(stbir__saturate(encode_buffer[encode_pixel_index + alpha_channel]) * 255));
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_LINEAR):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((unsigned short*)output_buffer)[output_pixel_index + n] = (unsigned short)(round(stbir__saturate(encode_buffer[encode_pixel_index + n]) * 65535));
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_SRGB):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((unsigned short*)output_buffer)[output_pixel_index + n] = (unsigned short)(round(stbir__linear_to_srgb(stbir__saturate(encode_buffer[encode_pixel_index + n])) * 65535));

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				((unsigned short*)output_buffer)[output_pixel_index + alpha_channel] = (unsigned short)(round(stbir__saturate(encode_buffer[encode_pixel_index + alpha_channel]) * 65535));
		}

		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_LINEAR):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((unsigned int*)output_buffer)[output_pixel_index + n] = (unsigned int)(round(((double)stbir__saturate(encode_buffer[encode_pixel_index + n])) * 4294967295));
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_SRGB):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((unsigned int*)output_buffer)[output_pixel_index + n] = (unsigned int)(round(((double)stbir__linear_to_srgb(stbir__saturate(encode_buffer[encode_pixel_index + n]))) * 4294967295));

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				((unsigned int*)output_buffer)[output_pixel_index + alpha_channel] = (unsigned int)(round(((double)stbir__saturate(encode_buffer[encode_pixel_index + alpha_channel])) * 4294967295));
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_LINEAR):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((float*)output_buffer)[output_pixel_index + n] = encode_buffer[encode_pixel_index + n];
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_SRGB):
		for (x=0; x < num_pixels; ++x)
		{
			int output_pixel_index = x*channels;
			int encode_pixel_index = x*channels;

			for (n = 0; n < channels; n++)
				((float*)output_buffer)[output_pixel_index + n] = stbir__linear_to_srgb(encode_buffer[encode_pixel_index + n]);

			if (!(stbir_info->flags&STBIR_FLAG_ALPHA_USES_COLORSPACE))
				((float*)output_buffer)[output_pixel_index + alpha_channel] = encode_buffer[encode_pixel_index + alpha_channel];
		}
		break;

	default:
		STBIR__UNIMPLEMENTED("Unknown type/colorspace/channels combination.");
		break;
	}
}

static void stbir__resample_vertical_upsample(stbir__info* stbir_info, int n, int in_first_scanline, int in_last_scanline, float in_center_of_out)
{
	int x, k;
	int output_w = stbir_info->output_w;
	stbir__contributors* vertical_contributors = &stbir_info->vertical_contributors;
	float* vertical_coefficients = stbir_info->vertical_coefficients;
	int channels = stbir_info->channels;
	int alpha_channel = stbir_info->alpha_channel;
	int type = stbir_info->type;
	int colorspace = stbir_info->colorspace;
	int kernel_pixel_width = stbir__get_filter_pixel_width_vertical(stbir_info);
	void* output_data = stbir_info->output_data;
	float* encode_buffer = stbir_info->encode_buffer;
	int decode = STBIR__DECODE(type, colorspace);

	float* ring_buffer = stbir_info->ring_buffer;
	int ring_buffer_begin_index = stbir_info->ring_buffer_begin_index;
	int ring_buffer_first_scanline = stbir_info->ring_buffer_first_scanline;
	int ring_buffer_last_scanline = stbir_info->ring_buffer_last_scanline;
	int ring_buffer_length = stbir_info->ring_buffer_length_bytes/sizeof(float);

	int n0,n1, output_row_start;

	stbir__calculate_coefficients_upsample(stbir_info, stbir_info->vertical_filter, in_first_scanline, in_last_scanline, in_center_of_out, vertical_contributors, vertical_coefficients);

	n0 = vertical_contributors->n0;
	n1 = vertical_contributors->n1;

	output_row_start = n * stbir_info->output_stride_bytes;

	STBIR__DEBUG_ASSERT(stbir__use_height_upsampling(stbir_info));
	STBIR__DEBUG_ASSERT(n0 >= in_first_scanline);
	STBIR__DEBUG_ASSERT(n1 <= in_last_scanline);

	memset(encode_buffer, 0, output_w * sizeof(float) * channels);

	for (x = 0; x < output_w; x++)
	{
		int in_pixel_index = x * channels;
		int coefficient_counter = 0;

		STBIR__DEBUG_ASSERT(n1 >= n0);

		for (k = n0; k <= n1; k++)
		{
			int coefficient_index = coefficient_counter++;
			float* ring_buffer_entry = stbir__get_ring_buffer_scanline(k, ring_buffer, ring_buffer_begin_index, ring_buffer_first_scanline, kernel_pixel_width, ring_buffer_length);
			float coefficient = vertical_coefficients[coefficient_index];

			int c;
			for (c = 0; c < channels; c++)
				encode_buffer[x*channels + c] += ring_buffer_entry[in_pixel_index + c] * coefficient;
		}
	}
	stbir__encode_scanline(stbir_info, output_w, (char *) output_data + output_row_start, encode_buffer, channels, alpha_channel, decode);
}

static void stbir__resample_vertical_downsample(stbir__info* stbir_info, int n, int in_first_scanline, int in_last_scanline, float in_center_of_out)
{
	int x, k;
	int output_w = stbir_info->output_w;
	int output_h = stbir_info->output_h;
	stbir__contributors* vertical_contributors = &stbir_info->vertical_contributors;
	float* vertical_coefficients = stbir_info->vertical_coefficients;
	int channels = stbir_info->channels;
	int kernel_pixel_width = stbir__get_filter_pixel_width_vertical(stbir_info);
	void* output_data = stbir_info->output_data;
	float* horizontal_buffer = stbir_info->horizontal_buffer;

	float* ring_buffer = stbir_info->ring_buffer;
	int ring_buffer_begin_index = stbir_info->ring_buffer_begin_index;
	int ring_buffer_first_scanline = stbir_info->ring_buffer_first_scanline;
	int ring_buffer_last_scanline = stbir_info->ring_buffer_last_scanline;
	int ring_buffer_length = stbir_info->ring_buffer_length_bytes/sizeof(float);
	int n0,n1,max_n;

	stbir__calculate_coefficients_downsample(stbir_info, stbir_info->vertical_filter, stbir_info->vertical_scale, in_first_scanline, in_last_scanline, in_center_of_out, vertical_contributors, vertical_coefficients);

	n0 = vertical_contributors->n0;
	n1 = vertical_contributors->n1;
	max_n = stbir__min(n1, output_h - 1);

	STBIR__DEBUG_ASSERT(!stbir__use_height_upsampling(stbir_info));
	STBIR__DEBUG_ASSERT(n0 >= in_first_scanline);
	STBIR__DEBUG_ASSERT(n1 <= in_last_scanline);
	STBIR__DEBUG_ASSERT(n1 >= n0);

	// Using min and max to avoid writing into ring buffers that will be thrown out.
	for (k = stbir__max(n0, 0); k <= max_n; k++)
	{
		int coefficient_index = k - n0;

		float* ring_buffer_entry = stbir__get_ring_buffer_scanline(k, ring_buffer, ring_buffer_begin_index, ring_buffer_first_scanline, kernel_pixel_width, ring_buffer_length);
		float coefficient = vertical_coefficients[coefficient_index];

		for (x = 0; x < output_w; x++)
		{
			int in_pixel_index = x * channels;

			int c;
			for (c = 0; c < channels; c++)
				ring_buffer_entry[in_pixel_index + c] += horizontal_buffer[in_pixel_index + c] * coefficient;
		}
	}
}

static void stbir__buffer_loop_upsample(stbir__info* stbir_info)
{
	int y;
	float scale_ratio = stbir_info->vertical_scale;
	float out_scanlines_radius = stbir__filter_info_table[stbir_info->vertical_filter].support * scale_ratio;

	STBIR__DEBUG_ASSERT(stbir__use_height_upsampling(stbir_info));

	for (y = 0; y < stbir_info->output_h; y++)
	{
		float in_center_of_out = 0; // Center of the current out scanline in the in scanline space
		int in_first_scanline = 0, in_last_scanline = 0;

		stbir__calculate_sample_range_upsample(y, out_scanlines_radius, scale_ratio, stbir_info->vertical_shift, &in_first_scanline, &in_last_scanline, &in_center_of_out);

		STBIR__DEBUG_ASSERT(in_last_scanline - in_first_scanline <= stbir__get_filter_pixel_width_vertical(stbir_info));

		if (stbir_info->ring_buffer_begin_index >= 0)
		{
			// Get rid of whatever we don't need anymore.
			while (in_first_scanline > stbir_info->ring_buffer_first_scanline)
			{
				if (stbir_info->ring_buffer_first_scanline == stbir_info->ring_buffer_last_scanline)
				{
					// We just popped the last scanline off the ring buffer.
					// Reset it to the empty state.
					stbir_info->ring_buffer_begin_index = -1;
					stbir_info->ring_buffer_first_scanline = 0;
					stbir_info->ring_buffer_last_scanline = 0;
					break;
				}
				else
				{
					stbir_info->ring_buffer_first_scanline++;
					stbir_info->ring_buffer_begin_index = (stbir_info->ring_buffer_begin_index + 1) % stbir__get_filter_pixel_width_horizontal(stbir_info);
				}
			}
		}

		// Load in new ones.
		if (stbir_info->ring_buffer_begin_index < 0)
			stbir__decode_and_resample_upsample(stbir_info, in_first_scanline);

		while (in_last_scanline > stbir_info->ring_buffer_last_scanline)
			stbir__decode_and_resample_upsample(stbir_info, stbir_info->ring_buffer_last_scanline + 1);

		// Now all buffers should be ready to write a row of vertical sampling.
		stbir__resample_vertical_upsample(stbir_info, y, in_first_scanline, in_last_scanline, in_center_of_out);

		STBIR_PROGRESS_REPORT((float)y / stbir_info->output_h);
	}
}

static void stbir__empty_ring_buffer(stbir__info* stbir_info, int first_necessary_scanline)
{
	int output_stride_bytes = stbir_info->output_stride_bytes;
	int channels = stbir_info->channels;
	int alpha_channel = stbir_info->alpha_channel;
	int type = stbir_info->type;
	int colorspace = stbir_info->colorspace;
	int output_w = stbir_info->output_w;
	void* output_data = stbir_info->output_data;
	int decode = STBIR__DECODE(type, colorspace);

	float* ring_buffer = stbir_info->ring_buffer;
	int ring_buffer_length = stbir_info->ring_buffer_length_bytes/sizeof(float);

	if (stbir_info->ring_buffer_begin_index >= 0)
	{
		// Get rid of whatever we don't need anymore.
		while (first_necessary_scanline > stbir_info->ring_buffer_first_scanline)
		{
			if (stbir_info->ring_buffer_first_scanline >= 0 && stbir_info->ring_buffer_first_scanline < stbir_info->output_h)
			{
				int output_row_start = stbir_info->ring_buffer_first_scanline * output_stride_bytes;
				float* ring_buffer_entry = stbir__get_ring_buffer_entry(ring_buffer, stbir_info->ring_buffer_begin_index, ring_buffer_length);
				stbir__encode_scanline(stbir_info, output_w, (char *) output_data + output_row_start, ring_buffer_entry, channels, alpha_channel, decode);
				STBIR_PROGRESS_REPORT((float)stbir_info->ring_buffer_first_scanline / stbir_info->output_h);
			}

			if (stbir_info->ring_buffer_first_scanline == stbir_info->ring_buffer_last_scanline)
			{
				// We just popped the last scanline off the ring buffer.
				// Reset it to the empty state.
				stbir_info->ring_buffer_begin_index = -1;
				stbir_info->ring_buffer_first_scanline = 0;
				stbir_info->ring_buffer_last_scanline = 0;
				break;
			}
			else
			{
				stbir_info->ring_buffer_first_scanline++;
				stbir_info->ring_buffer_begin_index = (stbir_info->ring_buffer_begin_index + 1) % stbir__get_filter_pixel_width_vertical(stbir_info);
			}
		}
	}
}

static void stbir__buffer_loop_downsample(stbir__info* stbir_info)
{
	int y;
	float scale_ratio = stbir_info->vertical_scale;
	int output_h = stbir_info->output_h;
	float in_pixels_radius = stbir__filter_info_table[stbir_info->vertical_filter].support / scale_ratio;
	int pixel_margin = stbir__get_filter_pixel_margin_vertical(stbir_info);
	int max_y = stbir_info->input_h + pixel_margin;

	STBIR__DEBUG_ASSERT(!stbir__use_height_upsampling(stbir_info));

	for (y = -pixel_margin; y < max_y; y++)
	{
		float out_center_of_in; // Center of the current out scanline in the in scanline space
		int out_first_scanline, out_last_scanline;

		stbir__calculate_sample_range_downsample(y, in_pixels_radius, scale_ratio, stbir_info->vertical_shift, &out_first_scanline, &out_last_scanline, &out_center_of_in);

		STBIR__DEBUG_ASSERT(out_last_scanline - out_first_scanline <= stbir__get_filter_pixel_width_vertical(stbir_info));

		if (out_last_scanline < 0 || out_first_scanline >= output_h)
			continue;

		stbir__empty_ring_buffer(stbir_info, out_first_scanline);

		stbir__decode_and_resample_downsample(stbir_info, y);

		// Load in new ones.
		if (stbir_info->ring_buffer_begin_index < 0)
			stbir__add_empty_ring_buffer_entry(stbir_info, out_first_scanline);

		while (out_last_scanline > stbir_info->ring_buffer_last_scanline)
			stbir__add_empty_ring_buffer_entry(stbir_info, stbir_info->ring_buffer_last_scanline + 1);

		// Now the horizontal buffer is ready to write to all ring buffer rows.
		stbir__resample_vertical_downsample(stbir_info, y, out_first_scanline, out_last_scanline, out_center_of_in);
	}

	stbir__empty_ring_buffer(stbir_info, stbir_info->output_h);
}

static void stbir__setup(stbir__info *info, int input_w, int input_h, int output_w, int output_h, int channels)
{
	info->input_w = input_w;
	info->input_h = input_h;
	info->output_w = output_w;
	info->output_h = output_h;
	info->channels = channels;
}

static void stbir__calculate_transform(stbir__info *info, float s0, float t0, float s1, float t1, float *transform)
{
	info->s0 = s0;
	info->t0 = t0;
	info->s1 = s1;
	info->t1 = t1;

	if (transform)
	{
		info->horizontal_scale = transform[0];
		info->vertical_scale   = transform[1];
		info->horizontal_shift = transform[2];
		info->vertical_shift   = transform[3];
	}
	else
	{
		info->horizontal_scale = ((float)info->output_w / info->input_w) / (s1 - s0);
		info->vertical_scale = ((float)info->output_h / info->input_h) / (t1 - t0);

		info->horizontal_shift = s0 * info->input_w / (s1 - s0);
		info->vertical_shift = t0 * info->input_h / (t1 - t0);
	}
}

static void stbir__choose_filter(stbir__info *info, stbir_filter h_filter, stbir_filter v_filter)
{
	if (h_filter == 0)
		h_filter = stbir__use_upsampling(info->horizontal_scale) ? STBIR_DEFAULT_FILTER_UPSAMPLE : STBIR_DEFAULT_FILTER_DOWNSAMPLE;
	if (v_filter == 0)
		v_filter = stbir__use_upsampling(info->vertical_scale)   ? STBIR_DEFAULT_FILTER_UPSAMPLE : STBIR_DEFAULT_FILTER_DOWNSAMPLE;
	info->horizontal_filter = h_filter;
	info->vertical_filter = v_filter;
}

static stbir_uint32 stbir__calculate_memory(stbir__info *info)
{
	int pixel_margin = stbir__get_filter_pixel_margin(info->horizontal_filter, info->horizontal_scale);
	int filter_height = stbir__get_filter_pixel_width(info->vertical_filter, info->vertical_scale);

	info->horizontal_contributors_size = stbir__get_horizontal_contributors(info) * sizeof(stbir__contributors);
	info->horizontal_coefficients_size = stbir__get_total_coefficients(info) * sizeof(float);
	info->vertical_coefficients_size = filter_height * sizeof(float);
	info->decode_buffer_size = (info->input_w + pixel_margin * 2) * info->channels * sizeof(float);
	info->horizontal_buffer_size = info->output_w * info->channels * sizeof(float);
	info->ring_buffer_size = info->output_w * info->channels * filter_height * sizeof(float);
	info->encode_buffer_size = info->output_w * info->channels * sizeof(float);

	STBIR_ASSERT(info->horizontal_filter != 0);
	STBIR_ASSERT(info->horizontal_filter < STBIR__ARRAY_SIZE(stbir__filter_info_table)); // this now happens too late
	STBIR_ASSERT(info->vertical_filter != 0);
	STBIR_ASSERT(info->vertical_filter < STBIR__ARRAY_SIZE(stbir__filter_info_table)); // this now happens too late

	if (stbir__use_height_upsampling(info))
		// The horizontal buffer is for when we're downsampling the height and we
		// can't output the result of sampling the decode buffer directly into the
		// ring buffers.
		info->horizontal_buffer_size = 0;
	else
		// The encode buffer is to retain precision in the height upsampling method
		// and isn't used when height downsampling.
		info->encode_buffer_size = 0;

	return info->horizontal_contributors_size + info->horizontal_coefficients_size
		+ info->vertical_coefficients_size + info->decode_buffer_size
		+ info->horizontal_buffer_size + info->ring_buffer_size
		+ info->encode_buffer_size;
}

static int stbir__resize_allocated(stbir__info *info,
    const void* input_data, int input_stride_in_bytes,
	void* output_data, int output_stride_in_bytes,
	int alpha_channel, stbir_uint32 flags, stbir_datatype type,
	stbir_edge edge_horizontal, stbir_edge edge_vertical, stbir_colorspace colorspace,
	void* tempmem, size_t tempmem_size_in_bytes)
{
	size_t memory_required = stbir__calculate_memory(info);

	int width_stride_input = input_stride_in_bytes ? input_stride_in_bytes : info->channels * info->input_w * stbir__type_size[type];
	int width_stride_output = output_stride_in_bytes ? output_stride_in_bytes : info->channels * info->output_w * stbir__type_size[type];

#ifdef STBIR_DEBUG_OVERWRITE_TEST
#define OVERWRITE_ARRAY_SIZE 8
	unsigned char overwrite_output_before_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_tempmem_before_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_output_after_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_tempmem_after_pre[OVERWRITE_ARRAY_SIZE];

	size_t begin_forbidden = width_stride_output * (info->output_h - 1) + info->output_w * info->channels * stbir__type_size[type];
	memcpy(overwrite_output_before_pre, &((unsigned char*)output_data)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_output_after_pre, &((unsigned char*)output_data)[begin_forbidden], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_tempmem_before_pre, &((unsigned char*)tempmem)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_tempmem_after_pre, &((unsigned char*)tempmem)[tempmem_size_in_bytes], OVERWRITE_ARRAY_SIZE);
#endif

	STBIR_ASSERT(info->channels <= STBIR_MAX_CHANNELS);
	STBIR_ASSERT(info->channels >= 0);

	if (info->channels > STBIR_MAX_CHANNELS || info->channels < 0)
		return 0;

	STBIR_ASSERT(info->horizontal_filter < STBIR__ARRAY_SIZE(stbir__filter_info_table));
	STBIR_ASSERT(info->vertical_filter < STBIR__ARRAY_SIZE(stbir__filter_info_table));

	if (info->horizontal_filter >= STBIR__ARRAY_SIZE(stbir__filter_info_table))
		return 0;
	if (info->vertical_filter >= STBIR__ARRAY_SIZE(stbir__filter_info_table))
		return 0;

	if (alpha_channel < 0)
		flags |= STBIR_FLAG_ALPHA_USES_COLORSPACE | STBIR_FLAG_PREMULTIPLIED_ALPHA;

	if (!(flags&STBIR_FLAG_ALPHA_USES_COLORSPACE) || !(flags&STBIR_FLAG_PREMULTIPLIED_ALPHA))
		STBIR_ASSERT(alpha_channel >= 0 && alpha_channel < info->channels);

	if (alpha_channel >= info->channels)
		return 0;

	STBIR_ASSERT(tempmem);

	if (!tempmem)
		return 0;

	STBIR_ASSERT(tempmem_size_in_bytes >= memory_required);

	if (tempmem_size_in_bytes < memory_required)
		return 0;

	memset(tempmem, 0, tempmem_size_in_bytes);

	info->input_data = input_data;
	info->input_stride_bytes = width_stride_input;

	info->output_data = output_data;
	info->output_stride_bytes = width_stride_output;

	info->alpha_channel = alpha_channel;
	info->flags = flags;
	info->type = type;
	info->edge_horizontal = edge_horizontal;
	info->edge_vertical = edge_vertical;
	info->colorspace = colorspace;

	info->ring_buffer_length_bytes = info->output_w * info->channels * sizeof(float);
	info->decode_buffer_pixels = info->input_w + stbir__get_filter_pixel_margin_horizontal(info) * 2;

#define STBIR__NEXT_MEMPTR(current, newtype) (newtype*)(((unsigned char*)current) + current##_size)

	info->horizontal_contributors = (stbir__contributors *) tempmem;
	info->horizontal_coefficients = STBIR__NEXT_MEMPTR(info->horizontal_contributors, float);
	info->vertical_coefficients = STBIR__NEXT_MEMPTR(info->horizontal_coefficients, float);
	info->decode_buffer = STBIR__NEXT_MEMPTR(info->vertical_coefficients, float);

	if (stbir__use_height_upsampling(info))
	{
		info->horizontal_buffer = NULL;
		info->ring_buffer = STBIR__NEXT_MEMPTR(info->decode_buffer, float);
		info->encode_buffer = STBIR__NEXT_MEMPTR(info->ring_buffer, float);

		STBIR__DEBUG_ASSERT((size_t)STBIR__NEXT_MEMPTR(info->encode_buffer, unsigned char) == (size_t)tempmem + tempmem_size_in_bytes);
	}
	else
	{
		info->horizontal_buffer = STBIR__NEXT_MEMPTR(info->decode_buffer, float);
		info->ring_buffer = STBIR__NEXT_MEMPTR(info->horizontal_buffer, float);
		info->encode_buffer = NULL;

		STBIR__DEBUG_ASSERT((size_t)STBIR__NEXT_MEMPTR(info->ring_buffer, unsigned char) == (size_t)tempmem + tempmem_size_in_bytes);
	}

#undef STBIR__NEXT_MEMPTR

	// This signals that the ring buffer is empty
	info->ring_buffer_begin_index = -1;

	stbir__calculate_horizontal_filters(info);

	STBIR_PROGRESS_REPORT(0);

	if (stbir__use_height_upsampling(info))
		stbir__buffer_loop_upsample(info);
	else
		stbir__buffer_loop_downsample(info);

	STBIR_PROGRESS_REPORT(1);

#ifdef STBIR_DEBUG_OVERWRITE_TEST
	STBIR__DEBUG_ASSERT(memcmp(overwrite_output_before_pre, &((unsigned char*)output_data)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE) == 0);
	STBIR__DEBUG_ASSERT(memcmp(overwrite_output_after_pre, &((unsigned char*)output_data)[begin_forbidden], OVERWRITE_ARRAY_SIZE) == 0);
	STBIR__DEBUG_ASSERT(memcmp(overwrite_tempmem_before_pre, &((unsigned char*)tempmem)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE) == 0);
	STBIR__DEBUG_ASSERT(memcmp(overwrite_tempmem_after_pre, &((unsigned char*)tempmem)[tempmem_size_in_bytes], OVERWRITE_ARRAY_SIZE) == 0);
#endif

	return 1;
}


static int stbir__resize_arbitrary(
	void *alloc_context,
    const void* input_data, int input_w, int input_h, int input_stride_in_bytes,
	void* output_data, int output_w, int output_h, int output_stride_in_bytes,
	float s0, float t0, float s1, float t1, float *transform,
	int channels, int alpha_channel, stbir_uint32 flags, stbir_datatype type,
	stbir_filter h_filter, stbir_filter v_filter,
	stbir_edge edge_horizontal, stbir_edge edge_vertical, stbir_colorspace colorspace)
{
	stbir__info info;
	int result;
	size_t memory_required;
	void* extra_memory;

	stbir__setup(&info, input_w, input_h, output_w, output_h, channels);
	stbir__calculate_transform(&info, s0,t0,s1,t1,transform);
	stbir__choose_filter(&info, h_filter, v_filter);
	memory_required = stbir__calculate_memory(&info);
	extra_memory = STBIR_MALLOC(alloc_context, memory_required);

	if (!extra_memory)
		return 0;

	result = stbir__resize_allocated(&info, input_data, input_stride_in_bytes,
	                                        output_data, output_stride_in_bytes, 
	                                        alpha_channel, flags, type,
	                                        edge_horizontal, edge_vertical,
	                                        colorspace, extra_memory, memory_required);

	STBIR_FREE(alloc_context, extra_memory);

	return result;
}

STBIRDEF int stbir_resize_uint8(     const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                     int num_channels)
{
	return stbir__resize_arbitrary(NULL, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,-1,0, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
		STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_LINEAR);
}

STBIRDEF int stbir_resize_float(     const float *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           float *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                     int num_channels)
{
	return stbir__resize_arbitrary(NULL, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,-1,0, STBIR_TYPE_FLOAT, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
		STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_LINEAR);
}

STBIRDEF int stbir_resize_uint8_srgb(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                           unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                     int num_channels, int alpha_channel, int flags)
{
	return stbir__resize_arbitrary(NULL, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,alpha_channel,flags, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
		STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB);
}

STBIRDEF int stbir_resize_uint8_srgb_edgemode(const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                                    unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                              int num_channels, int alpha_channel, int flags,
                                              stbir_edge edge_wrap_mode)
{
	return stbir__resize_arbitrary(NULL, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,alpha_channel,flags, STBIR_TYPE_UINT8, STBIR_FILTER_DEFAULT, STBIR_FILTER_DEFAULT,
		edge_wrap_mode, edge_wrap_mode, STBIR_COLORSPACE_SRGB);
}

STBIRDEF int stbir_resize_uint8_generic( const unsigned char *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                               unsigned char *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                         int num_channels, int alpha_channel, int flags,
                                         stbir_edge edge_wrap_mode, stbir_filter filter, stbir_colorspace space, 
                                         void *alloc_context)
{
	return stbir__resize_arbitrary(alloc_context, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,alpha_channel,flags, STBIR_TYPE_UINT8, filter, filter,
		edge_wrap_mode, edge_wrap_mode, space);
}

STBIRDEF int stbir_resize_uint16_generic(const stbir_uint16 *input_pixels  , int input_w , int input_h , int input_stride_in_bytes,
                                               stbir_uint16 *output_pixels , int output_w, int output_h, int output_stride_in_bytes,
                                         int num_channels, int alpha_channel, int flags,
                                         stbir_edge edge_wrap_mode, stbir_filter filter, stbir_colorspace space, 
                                         void *alloc_context)
{
	return stbir__resize_arbitrary(alloc_context, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,alpha_channel,flags, STBIR_TYPE_UINT16, filter, filter,
		edge_wrap_mode, edge_wrap_mode, space);
}


STBIRDEF int stbir_resize_float_generic( const float *input_pixels         , int input_w , int input_h , int input_stride_in_bytes,
                                               float *output_pixels        , int output_w, int output_h, int output_stride_in_bytes,
                                         int num_channels, int alpha_channel, int flags,
                                         stbir_edge edge_wrap_mode, stbir_filter filter, stbir_colorspace space, 
                                         void *alloc_context)
{
	return stbir__resize_arbitrary(alloc_context, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,alpha_channel,flags, STBIR_TYPE_FLOAT, filter, filter,
		edge_wrap_mode, edge_wrap_mode, space);
}


STBIRDEF int stbir_resize(         const void *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                         void *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   stbir_datatype datatype,
                                   int num_channels, int alpha_channel, int flags,
                                   stbir_edge edge_mode_horizontal, stbir_edge edge_mode_vertical, 
                                   stbir_filter filter_horizontal,  stbir_filter filter_vertical,
                                   stbir_colorspace space, void *alloc_context)
{
	return stbir__resize_arbitrary(alloc_context, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,NULL,num_channels,alpha_channel,flags, datatype, filter_horizontal, filter_vertical,
		edge_mode_horizontal, edge_mode_vertical, space);
}


STBIRDEF int stbir_resize_subpixel(const void *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                         void *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   stbir_datatype datatype,
                                   int num_channels, int alpha_channel, int flags,
                                   stbir_edge edge_mode_horizontal, stbir_edge edge_mode_vertical, 
                                   stbir_filter filter_horizontal,  stbir_filter filter_vertical,
                                   stbir_colorspace space, void *alloc_context,
                                   float x_scale, float y_scale,
                                   float x_offset, float y_offset)
{
	float transform[4];
	transform[0] = x_scale;
	transform[1] = y_scale;
	transform[2] = x_offset;
	transform[3] = y_offset;
	return stbir__resize_arbitrary(alloc_context, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		0,0,1,1,transform,num_channels,alpha_channel,flags, datatype, filter_horizontal, filter_vertical,
		edge_mode_horizontal, edge_mode_vertical, space);
}

STBIRDEF int stbir_resize_region(  const void *input_pixels , int input_w , int input_h , int input_stride_in_bytes,
                                         void *output_pixels, int output_w, int output_h, int output_stride_in_bytes,
                                   stbir_datatype datatype,
                                   int num_channels, int alpha_channel, int flags,
                                   stbir_edge edge_mode_horizontal, stbir_edge edge_mode_vertical, 
                                   stbir_filter filter_horizontal,  stbir_filter filter_vertical,
                                   stbir_colorspace space, void *alloc_context,
                                   float s0, float t0, float s1, float t1)
{
	return stbir__resize_arbitrary(alloc_context, input_pixels, input_w, input_h, input_stride_in_bytes,
		output_pixels, output_w, output_h, output_stride_in_bytes,
		s0,t0,s1,t1,NULL,num_channels,alpha_channel,flags, datatype, filter_horizontal, filter_vertical,
		edge_mode_horizontal, edge_mode_vertical, space);
}

#endif // STB_IMAGE_RESIZE_IMPLEMENTATION
