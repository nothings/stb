/* stb_image_resize - v0.50 - public domain image resampling
   no warranty implied; use at your own risk

   Do this:
      #define STB_IMAGE_RESIZE_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   #define STBIR_ASSERT(x) to avoid using assert.h.

   #define STBIR_MALLOC and STBIR_FREE to avoid using stdlib.h malloc. This will apply
      to all functions except stbir_resize_arbitrary(), which doesn't allocate memory.

   QUICK NOTES:
      Written with emphasis on usage and speed. Only the resize operation is
          currently supported, no rotations or translations.

      Supports arbitrary resize for separable filters. For a list of
          supported filters see the stbir_filter enum. To add a new filter,
          write a filter function and add it to stbir__filter_info_table.

   Latest revisions:
      0.50 (2014-07-29) first released version

   See end of file for full revision history.

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

// Basic usage:
//    result = stbir_resize_uint8_srgb(input_data, input_w, input_h, output_data, output_w, output_h, channels, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP);
//       * input_data is your supplied pixels.
//       * output_data will be the resized pixels. It should be of size output_w * output_h * channels
//       * Returned result is 1 for success or 0 in case of an error. In the case of an error an assert with be triggered, #define STBIR_ASSERT() to see it.
//       * If you're unsure of which filter to use, Catmull-Rom is a good upsampling filter and Mitchell is a good downsampling filter.
//
//
//    Data types provided: uint8, uint16, uint32, float.
//
//
//    Other function groups are provided, one for each data type, for more advanced functionality:
//
//    stbir_resize_type_alphaweighted(input_data, input_w, input_h, output_data, output_w, output_h, channels, alpha_channel, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB)
//       * alpha_channel - if nonnegative, this channel will be multiplied into all other channels before resampling, then divided back out after.
//
//    stbir_resize_type_subpixel(input_data, input_w, input_h, output_data, output_w, output_h, s0, t0, s1, t1, channels, filter, edge)
//       * s0, t0, s1, t1 are the top-left and bottom right corner (uv addressing style: [0, 1]x[0, 1]) of a region of the input image to use.
//
//
//    All functionality is offered in this function:
//
//    result = stbir_resize_arbitrary(input_data, input_w, input_h, input_stride_in_bytes,
//            output_data, output_w, output_h, output_stride_in_bytes,
//            s0, t0, s1, t1,
//            channels, alpha_channel, flags, STBIR_TYPE_UINT8, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB);
//
//       * input_stride_in_bytes and output_stride_in_bytes can be 0. If so they will be automatically calculated as width * channels.
//       * s0, t0, s1, t1 are the top-left and bottom right corner (uv addressing style: [0, 1]x[0, 1]) of a region of the input image to use.
//       * flags are from the stbir_flags enum and should be bitwise OR'd together.
//       * First edge parameter is for horizontal edge behavior, second is for vertical.
//       * Returned result is 1 for success or 0 in case of an error. In the case of an error an assert with be triggered, #define STBIR_ASSERT() to see it.
//       * Memory required grows approximately linearly with input and output size, but with discontinuities at input_w == output_w and input_h == output_height.
//       * To use temporary memory, define an STBIR_MALLOC that returns the temp memory and make STBIR_FREE do nothing--each function only ever allocates one block


typedef enum
{
	STBIR_FILTER_NEAREST     = 1,
	STBIR_FILTER_BILINEAR    = 2,
	STBIR_FILTER_BICUBIC     = 3,  // A cubic b spline
	STBIR_FILTER_CATMULLROM  = 4,
	STBIR_FILTER_MITCHELL    = 5,
} stbir_filter;

typedef enum
{
	STBIR_EDGE_CLAMP   = 1,
	STBIR_EDGE_REFLECT = 2,
	STBIR_EDGE_WRAP    = 3,
} stbir_edge;

typedef enum
{
	STBIR_COLORSPACE_LINEAR,
	STBIR_COLORSPACE_SRGB,

	STBIR_MAX_COLORSPACES,
} stbir_colorspace;

typedef enum
{
	STBIR_TYPE_UINT8 ,
	STBIR_TYPE_UINT16,
	STBIR_TYPE_UINT32,
	STBIR_TYPE_FLOAT ,

	STBIR_MAX_TYPES
} stbir_type;

typedef enum
{
	STBIR_FLAG_NONPREMUL_ALPHA    = (1 << 0), // The specified alpha channel will be multiplied into all other channels before resampling, then divided back out after.
	STBIR_FLAG_GAMMA_CORRECT_ALPHA = (1 << 1), // The specified alpha channel should be handled as a linear value even when doing sRGB operations.
} stbir_flags;

typedef unsigned char stbir_uint8;

#ifdef _MSC_VER
typedef unsigned short stbir_uint16;
typedef unsigned int   stbir_uint32;
#else
#include <stdint.h>
typedef uint16_t stbir_uint16;
typedef uint32_t stbir_uint32;
#endif

typedef unsigned int stbir_size_t; // to avoid including a header for size_t

#ifdef STB_IMAGE_RESIZE_STATIC
#define STBRDEF static
#else
#ifdef __cplusplus
#define STBRDEF extern "C"
#else
#define STBRDEF extern
#endif
#endif

//////////////////////////////////////////////////////////////////////////////
//
// PRIMARY API - sRGB type-safe image resizing.
//

STBRDEF int stbir_resize_uint8_srgb(const stbir_uint8* input_data, int input_w, int input_h,
	stbir_uint8* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge);

STBRDEF int stbir_resize_uint16_srgb(const stbir_uint16* input_data, int input_w, int input_h,
	stbir_uint16* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge);

STBRDEF int stbir_resize_uint32_srgb(const stbir_uint32* input_data, int input_w, int input_h,
	stbir_uint32* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge);

STBRDEF int stbir_resize_float_srgb(const float* input_data, int input_w, int input_h,
	float* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge);


STBRDEF int stbir_resize_uint8_alphaweighted(const stbir_uint8* input_data, int input_w, int input_h,
	stbir_uint8* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace);

STBRDEF int stbir_resize_uint16_alphaweighted(const stbir_uint16* input_data, int input_w, int input_h,
	stbir_uint16* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace);

STBRDEF int stbir_resize_uint32_alphaweighted(const stbir_uint32* input_data, int input_w, int input_h,
	stbir_uint32* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace);

STBRDEF int stbir_resize_float_alphaweighted(const float* input_data, int input_w, int input_h,
	float* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace);


STBRDEF int stbir_resize_uint8_subpixel(const stbir_uint8* input_data, int input_w, int input_h,
	stbir_uint8* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge);

STBRDEF int stbir_resize_uint16_subpixel(const stbir_uint16* input_data, int input_w, int input_h,
	stbir_uint16* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge);

STBRDEF int stbir_resize_uint32_subpixel(const stbir_uint32* input_data, int input_w, int input_h,
	stbir_uint32* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge);

STBRDEF int stbir_resize_float_subpixel(const float* input_data, int input_w, int input_h,
	float* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge);


STBRDEF int stbir_resize_arbitrary(const void* input_data, int input_w, int input_h, int input_stride_in_bytes,
	void* output_data, int output_w, int output_h, int output_stride_in_bytes,
	float s0, float t0, float s1, float t1,
	int channels, int alpha_channel, stbir_uint32 flags, stbir_type type, stbir_filter filter, stbir_edge edge_horizontal, stbir_edge edge_vertical, stbir_colorspace colorspace);

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

#define STBIR_MALLOC(x) malloc(x)
#define STBIR_FREE(x)   free(x)
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

// must match stbir_type
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
	stbir_type type;
	stbir_filter filter;
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

static unsigned char stbir__linear_uchar_to_srgb_uchar[256] = {
	0, 12, 21, 28, 33, 38, 42, 46, 49, 52, 55, 58, 61, 63, 66, 68, 70, 73, 75, 77, 79, 81, 82, 84, 86, 88, 89, 91, 93, 94,
	96, 97, 99, 100, 102, 103, 104, 106, 107, 109, 110, 111, 112, 114, 115, 116, 117, 118, 120, 121, 122, 123, 124, 125, 126,
	127, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 142, 143, 144, 145, 146, 147, 148, 149, 150,
	151, 151, 152, 153, 154, 155, 156, 157, 157, 158, 159, 160, 161, 161, 162, 163, 164, 165, 165, 166, 167, 168, 168, 169,
	170, 171, 171, 172, 173, 174, 174, 175, 176, 176, 177, 178, 179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 185, 186,
	187, 187, 188, 189, 189, 190, 191, 191, 192, 193, 193, 194, 194, 195, 196, 196, 197, 197, 198, 199, 199, 200, 201, 201,
	202, 202, 203, 204, 204, 205, 205, 206, 206, 207, 208, 208, 209, 209, 210, 210, 211, 212, 212, 213, 213, 214, 214, 215,
	215, 216, 217, 217, 218, 218, 219, 219, 220, 220, 221, 221, 222, 222, 223, 223, 224, 224, 225, 226, 226, 227, 227, 228,
	228, 229, 229, 230, 230, 231, 231, 232, 232, 233, 233, 234, 234, 235, 235, 236, 236, 237, 237, 237, 238, 238, 239, 239,
	240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250, 250, 251,
	251, 251, 252, 252, 253, 253, 254, 254, 255
};

float stbir__srgb_to_linear(float f)
{
	if (f <= 0.04045f)
		return f / 12.92f;
	else
		return (float)pow((f + 0.055f) / 1.055f, 2.4f);
}

float stbir__linear_to_srgb(float f)
{
	if (f <= 0.0031308f)
		return f * 12.92f;
	else
		return 1.055f * (float)pow(f, 1 / 2.4f) - 0.055f;
}



static float stbir__filter_nearest(float x)
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
		return 0.66666666666f + x*x*(0.5f*x  - 1);
	else if (x < 2.0f)
		return 1.3333333333f + x*(-2 + x*(1 - 0.16666666f * x));

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
		return 0.8888888888f + x*x*(1.1666666666666f * x - 2.0f);
	else if (x < 2.0f)
		return 1.777777777777f + x*(-3.3333333333f + x*(2 - 0.3888888888888f*x));

	return (0.0f);
}

static stbir__filter_info stbir__filter_info_table[] = {
		{ NULL,                    0.0f },
		{ stbir__filter_nearest,    0.5f },
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
stbir__inline static int stbir__get_filter_pixel_width(stbir_filter filter, int input_w, int output_w, float scale)
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
	return stbir__get_filter_pixel_width(stbir_info->filter, stbir_info->input_w, stbir_info->output_w, stbir_info->horizontal_scale);
}

stbir__inline static int stbir__get_filter_pixel_width_vertical(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->filter, stbir_info->input_h, stbir_info->output_h, stbir_info->vertical_scale);
}

// This is how much to expand buffers to account for filters seeking outside
// the image boundaries.
stbir__inline static int stbir__get_filter_pixel_margin(stbir_filter filter, int input_w, int output_w, float scale)
{
	return stbir__get_filter_pixel_width(filter, input_w, output_w, scale) / 2;
}

stbir__inline static int stbir__get_filter_pixel_margin_horizontal(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->filter, stbir_info->input_w, stbir_info->output_w, stbir_info->horizontal_scale) / 2;
}

stbir__inline static int stbir__get_filter_pixel_margin_vertical(stbir__info* stbir_info)
{
	return stbir__get_filter_pixel_width(stbir_info->filter, stbir_info->input_h, stbir_info->output_h, stbir_info->vertical_scale) / 2;
}

stbir__inline static int stbir__get_horizontal_contributors_noinfo(stbir_filter filter, int input_w, int output_w, float horizontal_scale)
{
	if (stbir__use_upsampling(horizontal_scale))
		return output_w;
	else
		return (input_w + stbir__get_filter_pixel_margin(filter, input_w, output_w, horizontal_scale) * 2);
}

stbir__inline static int stbir__get_horizontal_contributors(stbir__info* stbir_info)
{
	return stbir__get_horizontal_contributors_noinfo(stbir_info->filter, stbir_info->input_w, stbir_info->output_w, stbir_info->horizontal_scale);
}

stbir__inline static int stbir__get_total_coefficients_noinfo(stbir_filter filter, int input_w, int output_w, float horizontal_scale)
{
	return stbir__get_horizontal_contributors_noinfo(filter, input_w, output_w, horizontal_scale) * stbir__get_filter_pixel_width(filter, input_w, output_w, horizontal_scale);
}

stbir__inline static int stbir__get_total_coefficients(stbir__info* stbir_info)
{
	return stbir__get_total_coefficients_noinfo(stbir_info->filter, stbir_info->input_w, stbir_info->output_w, stbir_info->horizontal_scale);
}

stbir__inline static stbir__contributors* stbir__get_contributor(stbir__info* stbir_info, int n)
{
	STBIR__DEBUG_ASSERT(n >= 0 && n < stbir__get_horizontal_contributors(stbir_info));
	return &stbir_info->horizontal_contributors[n];
}

stbir__inline static float* stbir__get_coefficient(stbir__info* stbir_info, int n, int c)
{
	return &stbir_info->horizontal_coefficients[stbir__get_filter_pixel_width(stbir_info->filter, stbir_info->input_w, stbir_info->output_w, stbir_info->horizontal_scale)*n + c];
}

static int stbir__edge_wrap_slow(stbir_edge edge, int n, int max)
{
	switch (edge)
	{
	case STBIR_EDGE_CLAMP:
		if (n < 0)
			return 0;

		if (n >= max)
			return max - 1;

		return n;

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

		return n;
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

static void stbir__calculate_coefficients_upsample(stbir__info* stbir_info, int in_first_pixel, int in_last_pixel, float in_center_of_out, stbir__contributors* contributor, float* coefficient_group)
{
	int i;
	float total_filter = 0;
	float filter_scale;
	stbir_filter filter = stbir_info->filter;

	STBIR__DEBUG_ASSERT(in_last_pixel - in_first_pixel <= stbir__get_filter_pixel_width_horizontal(stbir_info));

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

static void stbir__calculate_coefficients_downsample(stbir__info* stbir_info, float scale_ratio, int out_first_pixel, int out_last_pixel, float out_center_of_in, stbir__contributors* contributor, float* coefficient_group)
{
	int i;
	stbir_filter filter = stbir_info->filter;

	STBIR__DEBUG_ASSERT(out_last_pixel - out_first_pixel <= stbir__get_filter_pixel_width_horizontal(stbir_info));

	contributor->n0 = out_first_pixel;
	contributor->n1 = out_last_pixel;

	STBIR__DEBUG_ASSERT(contributor->n1 >= contributor->n0);

	for (i = 0; i <= out_last_pixel - out_first_pixel; i++)
	{
		float in_pixel_center = (float)(i + out_first_pixel) + 0.5f;
		coefficient_group[i] = stbir__filter_info_table[filter].kernel((out_center_of_in - in_pixel_center)/scale_ratio);
	}
}

#ifdef STBIR_DEBUG
static void stbir__check_downsample_coefficients(stbir__info* stbir_info)
{
	int i;
	for (i = 0; i < stbir_info->output_w; i++)
	{
		float total = 0;
		int j;
		for (j = 0; j < stbir__get_horizontal_contributors(stbir_info); j++)
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
		STBIR__DEBUG_ASSERT(total <= 1.0f + 1.0f / (pow(2.0f, 8.0f * stbir__type_size[stbir_info->type]) - 1));
	}
}
#endif

// Each scan line uses the same kernel values so we should calculate the kernel
// values once and then we can use them for every scan line.
static void stbir__calculate_horizontal_filters(stbir__info* stbir_info)
{
	int n;
	float scale_ratio = stbir_info->horizontal_scale;

	int total_contributors = stbir__get_horizontal_contributors(stbir_info);

	if (stbir__use_width_upsampling(stbir_info))
	{
		float out_pixels_radius = stbir__filter_info_table[stbir_info->filter].support * scale_ratio;

		// Looping through out pixels
		for (n = 0; n < total_contributors; n++)
		{
			float in_center_of_out; // Center of the current out pixel in the in pixel space
			int in_first_pixel, in_last_pixel;

			stbir__calculate_sample_range_upsample(n, out_pixels_radius, scale_ratio, stbir_info->horizontal_shift, &in_first_pixel, &in_last_pixel, &in_center_of_out);

			stbir__calculate_coefficients_upsample(stbir_info, in_first_pixel, in_last_pixel, in_center_of_out, stbir__get_contributor(stbir_info, n), stbir__get_coefficient(stbir_info, n, 0));
		}
	}
	else
	{
		float in_pixels_radius = stbir__filter_info_table[stbir_info->filter].support / scale_ratio;

		// Looping through in pixels
		for (n = 0; n < total_contributors; n++)
		{
			float out_center_of_in; // Center of the current out pixel in the in pixel space
			int out_first_pixel, out_last_pixel;
			int n_adjusted = n - stbir__get_filter_pixel_margin_horizontal(stbir_info);

			stbir__calculate_sample_range_downsample(n_adjusted, in_pixels_radius, scale_ratio, stbir_info->horizontal_shift, &out_first_pixel, &out_last_pixel, &out_center_of_in);

			stbir__calculate_coefficients_downsample(stbir_info, scale_ratio, out_first_pixel, out_last_pixel, out_center_of_in, stbir__get_contributor(stbir_info, n), stbir__get_coefficient(stbir_info, n, 0));
		}

#ifdef STBIR_DEBUG
		stbir__check_downsample_coefficients(stbir_info);
#endif
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
	int input_stride = stbir_info->input_stride_bytes / stbir__type_size[stbir_info->type];
	const void* input_data = stbir_info->input_data;
	float* decode_buffer = stbir__get_decode_buffer(stbir_info);
	stbir_edge edge_horizontal = stbir_info->edge_horizontal;
	stbir_edge edge_vertical = stbir_info->edge_vertical;
	int in_buffer_row_index = stbir__edge_wrap(edge_vertical, n, stbir_info->input_h) * input_stride;
	int max_x = input_w + stbir__get_filter_pixel_margin_horizontal(stbir_info);
	int decode = STBIR__DECODE(type, colorspace);

	int x = -stbir__get_filter_pixel_margin_horizontal(stbir_info);

	switch (decode)
	{
	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = ((float)((const unsigned char*)input_data)[input_pixel_index + c]) / 255;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_uchar_to_linear_float[((const unsigned char*)input_data)[input_pixel_index + c]];

			if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
				decode_buffer[decode_pixel_index + alpha_channel] = ((float)((const unsigned char*)input_data)[input_pixel_index + alpha_channel]) / 255;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = ((float)((const unsigned short*)input_data)[input_pixel_index + c]) / 65535;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_to_linear(((float)((const unsigned short*)input_data)[input_pixel_index + c]) / 65535);

			if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
				decode_buffer[decode_pixel_index + alpha_channel] = ((float)((const unsigned short*)input_data)[input_pixel_index + alpha_channel]) / 65535;
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = (float)(((double)((const unsigned int*)input_data)[input_pixel_index + c]) / 4294967295);
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_to_linear((float)(((double)((const unsigned int*)input_data)[input_pixel_index + c]) / 4294967295));

			if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
				decode_buffer[decode_pixel_index + alpha_channel] = (float)(((double)((const unsigned int*)input_data)[input_pixel_index + alpha_channel]) / 4294967295);
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_LINEAR):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = ((const float*)input_data)[input_pixel_index + c];
		}
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_SRGB):
		for (; x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			for (c = 0; c < channels; c++)
				decode_buffer[decode_pixel_index + c] = stbir__srgb_to_linear(((const float*)input_data)[input_pixel_index + c]);

			if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
				decode_buffer[decode_pixel_index + alpha_channel] = ((const float*)input_data)[input_pixel_index + alpha_channel];
		}

		break;

	default:
		STBIR__UNIMPLEMENTED("Unknown type/colorspace/channels combination.");
		break;
	}

	if (stbir_info->flags & STBIR_FLAG_NONPREMUL_ALPHA)
	{
		for (x = -stbir__get_filter_pixel_margin_horizontal(stbir_info); x < max_x; x++)
		{
			int decode_pixel_index = x * channels;
			int input_pixel_index = in_buffer_row_index + stbir__edge_wrap(edge_horizontal, x, input_w) * channels;
			float alpha = decode_buffer[decode_pixel_index + alpha_channel];
			for (c = 0; c < channels; c++)
			{
				if (c == alpha_channel)
					continue;

				decode_buffer[decode_pixel_index + c] *= alpha;
			}
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
		int max_n = stbir__min(n1, output_w-1);
		int coefficient_group = x*kernel_pixel_width;

		STBIR__DEBUG_ASSERT(n1 >= n0);

		// Using min and max to avoid writing into invalid pixels.
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


static stbir__inline void stbir__encode_pixel(stbir__info* stbir_info, void* output_buffer, int output_pixel_index, float* encode_buffer, int encode_pixel_index, int channels, int alpha_channel, int decode)
{
	int n;
	float divide_alpha = 1;

	if (stbir_info->flags&STBIR_FLAG_NONPREMUL_ALPHA) {
		float alpha = encode_buffer[encode_pixel_index + alpha_channel];
		float reciprocal_alpha = alpha ? 1.0f / alpha : 0;
		for (n = 0; n < channels; n++)
			if (n != alpha_channel)
				encode_buffer[encode_pixel_index + n] *= reciprocal_alpha;
	}

	switch (decode)
	{
	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_LINEAR):
		for (n = 0; n < channels; n++)
			((unsigned char*)output_buffer)[output_pixel_index + n] = (unsigned char)(stbir__saturate(encode_buffer[encode_pixel_index + n]) * 255);
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT8, STBIR_COLORSPACE_SRGB):
		for (n = 0; n < channels; n++)
			((unsigned char*)output_buffer)[output_pixel_index + n] = stbir__linear_uchar_to_srgb_uchar[(unsigned char)(stbir__saturate(encode_buffer[encode_pixel_index + n]) * 255)];

		if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
			((unsigned char*)output_buffer)[output_pixel_index + alpha_channel] = (unsigned char)(stbir__saturate(encode_buffer[encode_pixel_index + alpha_channel]) * 255);

		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_LINEAR):
		for (n = 0; n < channels; n++)
			((unsigned short*)output_buffer)[output_pixel_index + n] = (unsigned short)(stbir__saturate(encode_buffer[encode_pixel_index + n]) * 65535);
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT16, STBIR_COLORSPACE_SRGB):
		for (n = 0; n < channels; n++)
			((unsigned short*)output_buffer)[output_pixel_index + n] = (unsigned short)(stbir__linear_to_srgb(stbir__saturate(encode_buffer[encode_pixel_index + n])) * 65535);

		if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
			((unsigned short*)output_buffer)[output_pixel_index + alpha_channel] = (unsigned char)(stbir__saturate(encode_buffer[encode_pixel_index + alpha_channel]) * 255);

		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_LINEAR):
		for (n = 0; n < channels; n++)
			((unsigned int*)output_buffer)[output_pixel_index + n] = (unsigned int)(((double)stbir__saturate(encode_buffer[encode_pixel_index + n])) * 4294967295);
		break;

	case STBIR__DECODE(STBIR_TYPE_UINT32, STBIR_COLORSPACE_SRGB):
		for (n = 0; n < channels; n++)
			((unsigned int*)output_buffer)[output_pixel_index + n] = (unsigned int)(((double)stbir__linear_to_srgb(stbir__saturate(encode_buffer[encode_pixel_index + n]))) * 4294967295);

		if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
			((unsigned int*)output_buffer)[output_pixel_index + alpha_channel] = (unsigned int)(((double)stbir__saturate(encode_buffer[encode_pixel_index + alpha_channel])) * 4294967295);

		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_LINEAR):
		for (n = 0; n < channels; n++)
			((float*)output_buffer)[output_pixel_index + n] = encode_buffer[encode_pixel_index + n];
		break;

	case STBIR__DECODE(STBIR_TYPE_FLOAT, STBIR_COLORSPACE_SRGB):
		for (n = 0; n < channels; n++)
			((float*)output_buffer)[output_pixel_index + n] = stbir__linear_to_srgb(encode_buffer[encode_pixel_index + n]);

		if (!(stbir_info->flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA))
			((float*)output_buffer)[output_pixel_index + alpha_channel] = encode_buffer[encode_pixel_index + alpha_channel];

		break;

	default:
		STBIR__UNIMPLEMENTED("Unknown type/colorspace/channels combination.");
		break;
	}
}

// @OPTIMIZE: embed stbir__encode_pixel and move switch out of per-pixel loop
static void stbir__encode_scanline(stbir__info* stbir_info, int num_pixels, void *output_buffer, int output_offset, float *encode_buffer, int channels, int alpha_channel, int decode)
{
	int x;
	for (x=0; x < num_pixels; ++x)
	{
		stbir__encode_pixel(stbir_info, output_buffer, output_offset+x*channels, encode_buffer, x*channels, channels, alpha_channel, decode);
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

	int n0,n1, output_row_index;

	stbir__calculate_coefficients_upsample(stbir_info, in_first_scanline, in_last_scanline, in_center_of_out, vertical_contributors, vertical_coefficients);

	n0 = vertical_contributors->n0;
	n1 = vertical_contributors->n1;

	output_row_index = n * stbir_info->output_stride_bytes / stbir__type_size[type];

	STBIR__DEBUG_ASSERT(stbir__use_height_upsampling(stbir_info));
	STBIR__DEBUG_ASSERT(n0 >= in_first_scanline);
	STBIR__DEBUG_ASSERT(n1 <= in_last_scanline);

	memset(encode_buffer, 0, output_w * sizeof(float) * channels);

	for (x = 0; x < output_w; x++)
	{
		int in_pixel_index = x * channels;
		int out_pixel_index = output_row_index + x * channels;
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
	stbir__encode_scanline(stbir_info, output_w, output_data, output_row_index, encode_buffer, channels, alpha_channel, decode);
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

	stbir__calculate_coefficients_downsample(stbir_info, stbir_info->vertical_scale, in_first_scanline, in_last_scanline, in_center_of_out, vertical_contributors, vertical_coefficients);

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
	float out_scanlines_radius = stbir__filter_info_table[stbir_info->filter].support * scale_ratio;

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
	}
}

static void stbir__empty_ring_buffer(stbir__info* stbir_info, int first_necessary_scanline)
{
	int output_stride = stbir_info->output_stride_bytes / stbir__type_size[stbir_info->type];
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
				int output_row = stbir_info->ring_buffer_first_scanline * output_stride;
				float* ring_buffer_entry = stbir__get_ring_buffer_entry(ring_buffer, stbir_info->ring_buffer_begin_index, ring_buffer_length);
				stbir__encode_scanline(stbir_info, output_w, output_data, output_row, ring_buffer_entry, channels, alpha_channel, decode);
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
	float in_pixels_radius = stbir__filter_info_table[stbir_info->filter].support / scale_ratio;
	int max_y = stbir_info->input_h + stbir__get_filter_pixel_margin_vertical(stbir_info);

	STBIR__DEBUG_ASSERT(!stbir__use_height_upsampling(stbir_info));

	for (y = -stbir__get_filter_pixel_margin_vertical(stbir_info); y < max_y; y++)
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

static stbir__inline stbir_size_t stbir__calculate_memory(int input_w, int input_h, int output_w, int output_h, float s0, float t0, float s1, float t1, int channels, stbir_filter filter)
{
	float horizontal_scale = ((float)output_w / input_w) / (s1 - s0);
	float vertical_scale = ((float)output_h / input_h) / (t1 - t0);

	int pixel_margin = stbir__get_filter_pixel_margin(filter, input_w, output_w, horizontal_scale);
	int filter_height = stbir__get_filter_pixel_width(filter, input_h, output_h, vertical_scale);

	int info_size = sizeof(stbir__info);
	int contributors_size = stbir__get_horizontal_contributors_noinfo(filter, input_w, output_w, horizontal_scale) * sizeof(stbir__contributors);
	int horizontal_coefficients_size = stbir__get_total_coefficients_noinfo(filter, input_w, output_w, horizontal_scale) * sizeof(float);
	int vertical_coefficients_size = filter_height * sizeof(float);
	int decode_buffer_size = (input_w + pixel_margin*2) * channels * sizeof(float);
	int horizontal_buffer_size = output_w * channels * sizeof(float);
	int ring_buffer_size = output_w * channels * filter_height * sizeof(float);
	int encode_buffer_size = output_w * channels * sizeof(float);

	STBIR_ASSERT(filter != 0);
	STBIR_ASSERT(filter < STBIR__ARRAY_SIZE(stbir__filter_info_table)); // this now happens too late

	if (stbir__use_upsampling(horizontal_scale))
		// The horizontal buffer is for when we're downsampling the height and we
		// can't output the result of sampling the decode buffer directly into the
		// ring buffers.
		horizontal_buffer_size = 0;
	else
		// The encode buffer is to retain precision in the height upsampling method
		// and isn't used when height downsampling.
		encode_buffer_size = 0;

	return info_size + contributors_size + horizontal_coefficients_size + vertical_coefficients_size + decode_buffer_size + horizontal_buffer_size + ring_buffer_size + encode_buffer_size;
}

static int stbir__resize_allocated(const void* input_data, int input_w, int input_h, int input_stride_in_bytes,
	void* output_data, int output_w, int output_h, int output_stride_in_bytes,
	float s0, float t0, float s1, float t1,
	int channels, int alpha_channel, stbir_uint32 flags, stbir_type type, stbir_filter filter, stbir_edge edge_horizontal, stbir_edge edge_vertical, stbir_colorspace colorspace,
	void* tempmem, stbir_size_t tempmem_size_in_bytes)
{
	stbir__info* stbir_info = (stbir__info*)tempmem;

	stbir_size_t memory_required = stbir__calculate_memory(input_w, input_h, output_w, output_h, s0, t0, s1, t1, channels, filter);

	int width_stride_input = input_stride_in_bytes ? input_stride_in_bytes : channels * input_w * stbir__type_size[type];
	int width_stride_output = output_stride_in_bytes ? output_stride_in_bytes : channels * output_w * stbir__type_size[type];

#ifdef STBIR_DEBUG_OVERWRITE_TEST
#define OVERWRITE_ARRAY_SIZE 8
	unsigned char overwrite_output_before_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_tempmem_before_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_output_after_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_tempmem_after_pre[OVERWRITE_ARRAY_SIZE];

	stbir_size_t begin_forbidden = width_stride_output * (output_h - 1) + output_w * channels * stbir__type_size[type];
	memcpy(overwrite_output_before_pre, &((unsigned char*)output_data)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_output_after_pre, &((unsigned char*)output_data)[begin_forbidden], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_tempmem_before_pre, &((unsigned char*)tempmem)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_tempmem_after_pre, &((unsigned char*)tempmem)[tempmem_size_in_bytes], OVERWRITE_ARRAY_SIZE);
#endif

	STBIR_ASSERT(filter != 0);
	STBIR_ASSERT(filter < STBIR__ARRAY_SIZE(stbir__filter_info_table));

	if (!filter || filter >= STBIR__ARRAY_SIZE(stbir__filter_info_table))
		return 0;

	STBIR_ASSERT(s1 > s0);
	STBIR_ASSERT(t1 > t0);

	if (s1 <= s0 || t1 <= t0)
		return 0;

	STBIR_ASSERT(s1 <= 1 && s0 >= 0 && t1 <= 1 && t0 >= 0);

	if (s1 > 1 || s0 < 0 || t1 > 1 || t0 < 0)
		return 0;

	if (alpha_channel < 0)
		flags = STBIR_FLAG_GAMMA_CORRECT_ALPHA; // this shouldn't be necessary in the long run, but safety for now

	if (!(flags&STBIR_FLAG_GAMMA_CORRECT_ALPHA) || (flags&STBIR_FLAG_NONPREMUL_ALPHA))
		STBIR_ASSERT(alpha_channel >= 0 && alpha_channel < channels);

	if (alpha_channel >= channels)
		return 0;

	STBIR_ASSERT(tempmem);

	if (!tempmem)
		return 0;

	STBIR_ASSERT(tempmem_size_in_bytes >= memory_required);

	if (tempmem_size_in_bytes < memory_required)
		return 0;

	memset(tempmem, 0, tempmem_size_in_bytes);

	stbir_info->input_data = input_data;
	stbir_info->input_w = input_w;
	stbir_info->input_h = input_h;
	stbir_info->input_stride_bytes = width_stride_input;

	stbir_info->output_data = output_data;
	stbir_info->output_w = output_w;
	stbir_info->output_h = output_h;
	stbir_info->output_stride_bytes = width_stride_output;

	stbir_info->s0 = s0;
	stbir_info->t0 = t0;
	stbir_info->s1 = s1;
	stbir_info->t1 = t1;

	stbir_info->horizontal_scale = ((float)output_w / input_w) / (s1 - s0);
	stbir_info->vertical_scale = ((float)output_h / input_h) / (t1 - t0);

	stbir_info->horizontal_shift = s0 * input_w / (s1 - s0);
	stbir_info->vertical_shift = t0 * input_h / (t1 - t0);

	stbir_info->channels = channels;
	stbir_info->alpha_channel = alpha_channel;
	stbir_info->flags = flags;
	stbir_info->type = type;
	stbir_info->filter = filter;
	stbir_info->edge_horizontal = edge_horizontal;
	stbir_info->edge_vertical = edge_vertical;
	stbir_info->colorspace = colorspace;

	stbir_info->ring_buffer_length_bytes = output_w * channels * sizeof(float);
	stbir_info->decode_buffer_pixels = input_w + stbir__get_filter_pixel_margin_horizontal(stbir_info) * 2;

#define STBIR__NEXT_MEMPTR(current, old, newtype) (newtype*)(((unsigned char*)current) + old)

	stbir_info->horizontal_contributors = STBIR__NEXT_MEMPTR(stbir_info, sizeof(stbir__info), stbir__contributors);
	stbir_info->horizontal_coefficients = STBIR__NEXT_MEMPTR(stbir_info->horizontal_contributors, stbir__get_horizontal_contributors(stbir_info) * sizeof(stbir__contributors), float);
	stbir_info->vertical_coefficients = STBIR__NEXT_MEMPTR(stbir_info->horizontal_coefficients, stbir__get_total_coefficients(stbir_info) * sizeof(float), float);
	stbir_info->decode_buffer = STBIR__NEXT_MEMPTR(stbir_info->vertical_coefficients, stbir__get_filter_pixel_width_vertical(stbir_info) * sizeof(float), float);

	if (stbir__use_height_upsampling(stbir_info))
	{
		stbir_info->horizontal_buffer = NULL;
		stbir_info->ring_buffer = STBIR__NEXT_MEMPTR(stbir_info->decode_buffer, stbir_info->decode_buffer_pixels * channels * sizeof(float), float);
		stbir_info->encode_buffer = STBIR__NEXT_MEMPTR(stbir_info->ring_buffer, stbir_info->ring_buffer_length_bytes * stbir__get_filter_pixel_width_horizontal(stbir_info), float);

		STBIR__DEBUG_ASSERT((size_t)STBIR__NEXT_MEMPTR(stbir_info->encode_buffer, stbir_info->channels * sizeof(float), unsigned char) == (size_t)tempmem + tempmem_size_in_bytes);
	}
	else
	{
		stbir_info->horizontal_buffer = STBIR__NEXT_MEMPTR(stbir_info->decode_buffer, stbir_info->decode_buffer_pixels * channels * sizeof(float), float);
		stbir_info->ring_buffer = STBIR__NEXT_MEMPTR(stbir_info->horizontal_buffer, output_w * channels * sizeof(float), float);
		stbir_info->encode_buffer = NULL;

		STBIR__DEBUG_ASSERT((size_t)STBIR__NEXT_MEMPTR(stbir_info->ring_buffer, stbir_info->ring_buffer_length_bytes * stbir__get_filter_pixel_width_vertical(stbir_info), unsigned char) == (size_t)tempmem + tempmem_size_in_bytes);
	}

#undef STBIR__NEXT_MEMPTR

	// This signals that the ring buffer is empty
	stbir_info->ring_buffer_begin_index = -1;

	stbir__calculate_horizontal_filters(stbir_info);

	if (stbir__use_height_upsampling(stbir_info))
		stbir__buffer_loop_upsample(stbir_info);
	else
		stbir__buffer_loop_downsample(stbir_info);

#ifdef STBIR_DEBUG_OVERWRITE_TEST
	STBIR__DEBUG_ASSERT(memcmp(overwrite_output_before_pre, &((unsigned char*)output_data)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE) == 0);
	STBIR__DEBUG_ASSERT(memcmp(overwrite_output_after_pre, &((unsigned char*)output_data)[begin_forbidden], OVERWRITE_ARRAY_SIZE) == 0);
	STBIR__DEBUG_ASSERT(memcmp(overwrite_tempmem_before_pre, &((unsigned char*)tempmem)[-OVERWRITE_ARRAY_SIZE], OVERWRITE_ARRAY_SIZE) == 0);
	STBIR__DEBUG_ASSERT(memcmp(overwrite_tempmem_after_pre, &((unsigned char*)tempmem)[tempmem_size_in_bytes], OVERWRITE_ARRAY_SIZE) == 0);
#endif

	return 1;
}


STBRDEF int stbir_resize_arbitrary(const void* input_data, int input_w, int input_h, int input_stride_in_bytes,
	void* output_data, int output_w, int output_h, int output_stride_in_bytes,
	float s0, float t0, float s1, float t1,
	int channels, int alpha_channel, stbir_uint32 flags, stbir_type type, stbir_filter filter, stbir_edge edge_horizontal, stbir_edge edge_vertical, stbir_colorspace colorspace)
{
	int result;
	size_t memory_required = stbir__calculate_memory(input_w, input_h, output_w, output_h, 0, 0, 1, 1, channels, filter);
	void* extra_memory = STBIR_MALLOC(memory_required);

	if (!extra_memory)
		return 0;

	result = stbir__resize_allocated(input_data, input_w, input_h, input_stride_in_bytes, output_data, output_w, output_h, output_stride_in_bytes, s0, t0, s1, t1, channels, alpha_channel, flags, type, filter, edge_horizontal, edge_vertical, colorspace, extra_memory, memory_required);

	STBIR_FREE(extra_memory);

	return result;
}

STBRDEF int stbir_resize_uint8_srgb(const stbir_uint8* input_data, int input_w, int input_h,
	stbir_uint8* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, 0, 0, STBIR_TYPE_UINT8, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_uint16_srgb(const stbir_uint16* input_data, int input_w, int input_h,
	stbir_uint16* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, 0, 0, STBIR_TYPE_UINT16, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_uint32_srgb(const stbir_uint32* input_data, int input_w, int input_h,
	stbir_uint32* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, 0, 0, STBIR_TYPE_UINT32, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_float_srgb(const float* input_data, int input_w, int input_h,
	float* output_data, int output_w, int output_h,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, 0, 0, STBIR_TYPE_FLOAT, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_uint8_alphaweighted(const stbir_uint8* input_data, int input_w, int input_h,
	stbir_uint8* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, alpha_channel, STBIR_FLAG_NONPREMUL_ALPHA, STBIR_TYPE_UINT8, filter, edge, edge, colorspace);
}

STBRDEF int stbir_resize_uint16_alphaweighted(const stbir_uint16* input_data, int input_w, int input_h,
	stbir_uint16* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, alpha_channel, STBIR_FLAG_NONPREMUL_ALPHA, STBIR_TYPE_UINT16, filter, edge, edge, colorspace);
}

STBRDEF int stbir_resize_uint32_alphaweighted(const stbir_uint32* input_data, int input_w, int input_h,
	stbir_uint32* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, alpha_channel, STBIR_FLAG_NONPREMUL_ALPHA, STBIR_TYPE_UINT32, filter, edge, edge, colorspace);
}

STBRDEF int stbir_resize_float_alphaweighted(const float* input_data, int input_w, int input_h,
	float* output_data, int output_w, int output_h,
	int channels, int alpha_channel, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, 0, 0, 1, 1, channels, alpha_channel, STBIR_FLAG_NONPREMUL_ALPHA, STBIR_TYPE_FLOAT, filter, edge, edge, colorspace);
}

STBRDEF int stbir_resize_uint8_subpixel(const stbir_uint8* input_data, int input_w, int input_h,
	stbir_uint8* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, s0, t0, s1, t1, channels, 0, 0, STBIR_TYPE_UINT8, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_uint16_subpixel(const stbir_uint16* input_data, int input_w, int input_h,
	stbir_uint16* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, s0, t0, s1, t1, channels, 0, 0, STBIR_TYPE_UINT16, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_uint32_subpixel(const stbir_uint32* input_data, int input_w, int input_h,
	stbir_uint32* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, s0, t0, s1, t1, channels, 0, 0, STBIR_TYPE_UINT32, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

STBRDEF int stbir_resize_float_subpixel(const float* input_data, int input_w, int input_h,
	float* output_data, int output_w, int output_h,
	float s0, float t0, float s1, float t1,
	int channels, stbir_filter filter, stbir_edge edge)
{
	return stbir_resize_arbitrary(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, s0, t0, s1, t1, channels, 0, 0, STBIR_TYPE_FLOAT, filter, edge, edge, STBIR_COLORSPACE_SRGB);
}

#endif // STB_IMAGE_RESIZE_IMPLEMENTATION

/*
revision history:
      0.50 (2014-07-29)
             first released version
*/
