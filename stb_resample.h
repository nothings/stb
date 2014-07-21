/* stb_resample - v0.1 - public domain image resampling
no warranty implied; use at your own risk

Do this:
#define STB_RESAMPLE_IMPLEMENTATION
before you include this file in *one* C or C++ file to create the implementation.

#define STBR_ASSERT(x) to avoid using assert.h.

Latest revisions:

See end of file for full revision history.

Initial implementation by Jorge L Rodriguez
*/

#ifndef STBR_INCLUDE_STB_RESAMPLE_H
#define STBR_INCLUDE_STB_RESAMPLE_H

// Basic usage:
//    result = stbr_resize(input_data, input_w, input_h, input_components, STBR_FILTER_NEAREST, output_data, output_w, output_h);
//
//    input_data is your supplied texels.
//    output_data will be the resized texels. It should be of size output_w * output_h * input_components.
//    Returned result is 1 for success or 0 in case of an error.

typedef enum
{
	STBR_FILTER_NEAREST = 1,
} stbr_filter;


typedef unsigned char stbr_uc;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_RESAMPLE_STATIC
#define STBRDEF static
#else
#define STBRDEF extern
#endif

	//////////////////////////////////////////////////////////////////////////////
	//
	// PRIMARY API - resize an image
	//

	STBRDEF int stbr_resize(const stbr_uc* input_data, int input_w, int input_h, int input_components, stbr_filter filter, stbr_uc* output_data, int output_w, int output_h);


#ifdef __cplusplus
}
#endif

//
//
////   end header file   /////////////////////////////////////////////////////
#endif // STBR_INCLUDE_STB_RESAMPLE_H

#ifdef STB_RESIZE_IMPLEMENTATION

#ifndef STBR_ASSERT
#include <assert.h>
#define STBR_ASSERT(x) assert(x)
#endif

#ifdef STBR_DEBUG_OVERWRITE_TEST
#include <string.h>
#endif


// For size_t
#include <stdlib.h>


#ifndef _MSC_VER
#ifdef __cplusplus
#define stbr_inline inline
#else
#define stbr_inline
#endif
#else
#define stbr_inline __forceinline
#endif


#ifdef _MSC_VER
typedef unsigned short stbr__uint16;
typedef   signed short stbr__int16;
typedef unsigned int   stbr__uint32;
typedef   signed int   stbr__int32;
#else
#include <stdint.h>
typedef uint16_t stbr__uint16;
typedef int16_t  stbr__int16;
typedef uint32_t stbr__uint32;
typedef int32_t  stbr__int32;
#endif

// should produce compiler error if size is wrong
typedef unsigned char stbr__validate_uint32[sizeof(stbr__uint32) == 4 ? 1 : -1];

#ifdef _MSC_VER
#define STBR_NOTUSED(v)  (void)(v)
#else
#define STBR_NOTUSED(v)  (void)sizeof(v)
#endif

// i0 is a texel in [0, n0-1]
// What's the nearest texel center to i0's center in [0, n1-1] ?
// Remapping [0, n0-1] to [0, n1-1] gives (i0 + 0.5)*n1/n0 but we want to avoid
// floating point math so we rearrange it as (n1*i0 + n1/2)/n0
stbr_inline static int stbr__nearest_texel(int i0, int n0, int n1)
{
	return (n1*i0 + n1/2) / n0;
}

stbr_inline static size_t stbr__texel_index(int x, int y, int c, int width_stride, int num_c, int w, int h)
{
	STBR_ASSERT(x >= 0 && x < w);
	STBR_ASSERT(y >= 0 && y < h);

	return y*width_stride + x*num_c + c;
}

static void stbr__filter_nearest_1(const stbr_uc* input_data, stbr_uc* output_data, size_t input_texel_index, size_t output_texel_index, size_t n)
{
	output_data[output_texel_index] = input_data[input_texel_index];
}

static void stbr__filter_nearest_3(const stbr_uc* input_data, stbr_uc* output_data, size_t input_texel_index, size_t output_texel_index, size_t n)
{
	output_data[output_texel_index] = input_data[input_texel_index];
	output_data[output_texel_index + 1] = input_data[input_texel_index + 1];
	output_data[output_texel_index + 2] = input_data[input_texel_index + 2];
}

static void stbr__filter_nearest_4(const stbr_uc* input_data, stbr_uc* output_data, size_t input_texel_index, size_t output_texel_index, size_t n)
{
	output_data[output_texel_index] = input_data[input_texel_index];
	output_data[output_texel_index + 1] = input_data[input_texel_index + 1];
	output_data[output_texel_index + 2] = input_data[input_texel_index + 2];
	output_data[output_texel_index + 3] = input_data[input_texel_index + 3];
}

static void stbr__filter_nearest_n(const stbr_uc* input_data, stbr_uc* output_data, size_t input_texel_index, size_t output_texel_index, size_t n)
{
	size_t c;
	for (c = 0; c < n; c++)
		output_data[output_texel_index + c] = input_data[input_texel_index + c];
}

typedef void (stbr__filter_fn)(const stbr_uc* input_data, stbr_uc* output_data, size_t input_texel_index, size_t output_texel_index, size_t n);

STBRDEF int stbr_resize(const stbr_uc* input_data, int input_w, int input_h, int input_components, stbr_filter filter, stbr_uc* output_data, int output_w, int output_h)
{
	int x, y;
	int width_stride_input = input_components * input_w;
	int width_stride_output = input_components * output_w;

#ifdef STBR_DEBUG_OVERWRITE_TEST
#define OVERWRITE_ARRAY_SIZE 64
	unsigned char overwrite_contents_pre[OVERWRITE_ARRAY_SIZE];

	memcpy(overwrite_contents_pre, &output_data[output_w * output_h * input_components], OVERWRITE_ARRAY_SIZE);
#endif

	if (filter == STBR_FILTER_NEAREST)
	{
		stbr__filter_fn* filter_fn;

		filter_fn = &stbr__filter_nearest_n;

		if (input_components == 1)
			filter_fn = &stbr__filter_nearest_1;
		else if (input_components == 3)
			filter_fn = &stbr__filter_nearest_3;
		else if (input_components == 4)
			filter_fn = &stbr__filter_nearest_4;

		for (y = 0; y < output_h; y++)
		{
			int nearest_y = stbr__nearest_texel(y, output_h, input_h);

			for (x = 0; x < output_w; x++)
			{
				int nearest_x = stbr__nearest_texel(x, output_w, input_w);
				size_t input_texel_index = stbr__texel_index(nearest_x, nearest_y, 0, width_stride_input, input_components, input_w, input_h);
				size_t output_texel_index = stbr__texel_index(x, y, 0, width_stride_output, input_components, output_w, output_h);

				filter_fn(input_data, output_data, input_texel_index, output_texel_index, input_components);
			}
		}
	}
	else
		return 0;

#ifdef STBR_DEBUG_OVERWRITE_TEST
	STBR_ASSERT(memcmp(overwrite_contents_pre, &output_data[output_w * output_h * input_components], OVERWRITE_ARRAY_SIZE) == 0);
#endif

	return 1;
}


#endif // STB_RESAMPLE_IMPLEMENTATION

/*
revision history:
*/
