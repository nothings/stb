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
//    result = stbr_resize(input_data, input_w, input_h, 0, output_data, output_w, output_h, 0, channels, alpha_channel, STBR_TYPE_UINT8, STBR_FILTER_BILINEAR, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB);
//
//    input_data is your supplied texels.
//    output_data will be the resized texels. It should be of size output_w * output_h * input_components (or output_h * output_stride if you provided a stride.)
//    If input_stride or output_stride is 0 (as in this example) the stride will be automatically calculated as width*components.
//    Returned result is 1 for success or 0 in case of an error.

typedef enum
{
	STBR_FILTER_NEAREST = 1,
	STBR_FILTER_LINEAR = 2,
} stbr_filter;

typedef enum
{
	STBR_EDGE_CLAMP = 1,
} stbr_edge;

typedef enum
{
	STBR_COLORSPACE_LINEAR = 1,
	STBR_COLORSPACE_SRGB = 2,
} stbr_colorspace;

typedef enum
{
	STBR_TYPE_UINT8 = 1,
} stbr_type;

typedef unsigned char stbr_uc;
typedef unsigned int stbr_size_t; // to avoid including a header for size_t

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

	STBRDEF stbr_size_t stbr_calculate_memory(int input_w, int input_h, int input_stride_in_bytes,
		int output_w, int output_h, int output_stride_in_bytes,
		int channels, stbr_filter filter);

	STBRDEF int stbr_resize_arbitrary(const void* input_data, int input_w, int input_h, int input_stride_in_bytes,
		void* output_data, int output_w, int output_h, int output_stride_in_bytes,
		//int channels, int alpha_channel, stbr_type type, stbr_filter filter, stbr_edge edge, stbr_colorspace colorspace,
		int channels, stbr_type type, stbr_filter filter, stbr_edge edge,
		void* tempmem, stbr_size_t tempmem_size_in_bytes);


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

#ifdef STBR_DEBUG
#define STBR_DEBUG_ASSERT STBR_ASSERT
#else
#define STBR_DEBUG_ASSERT
#endif

// If you hit this it means I haven't done it yet.
#define STBR_UNIMPLEMENTED(x) STBR_ASSERT(!(x))

#ifdef STBR_DEBUG_OVERWRITE_TEST
#include <string.h>
#endif


#include <math.h>


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

#define STBR_ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))

// Kernel function centered at 0
typedef float (stbr__kernel_fn)(float x);

typedef struct
{
	stbr__kernel_fn* kernel;
	float support;
} stbr__filter_info;

// When upsampling, the contributors are which source texels contribute.
// When downsampling, the contributors are which destination texels are contributed to.
typedef struct
{
	int n0; // First contributing texel
	int n1; // Last contributing texel
} stbr__contributors;

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

	int channels;
	stbr_type type;
	stbr_filter filter;
	stbr_edge edge;

	stbr__contributors* horizontal_contributors;
	float* horizontal_coefficients;

	stbr__contributors vertical_contributors;
	float* vertical_coefficients;

	int decode_buffer_texels;
	float* decode_buffer;

	float* horizontal_buffer;

	int ring_buffer_length_bytes; // The length of an individual entry in the ring buffer. The total number of ring buffers is stbr__get_filter_texel_width(filter)
	int ring_buffer_first_scanline;
	int ring_buffer_last_scanline;
	int ring_buffer_begin_index;
	float* ring_buffer;

	float* encode_buffer; // A temporary buffer to store floats so we don't lose precision while we do multiply-adds.
} stbr__info;


static stbr_inline int stbr__min(int a, int b)
{
	return a < b ? a : b;
}

static stbr_inline int stbr__max(int a, int b)
{
	return a > b ? a : b;
}


static float stbr__filter_nearest(float x)
{
	if (fabs(x) <= 0.5)
		return 1;
	else
		return 0;
}

static float stbr__filter_linear(float x)
{
	x = (float)fabs(x);

	if (x <= 1.0f)
		return 1 - x;
	else
		return 0;
}

static stbr__filter_info stbr__filter_info_table[] = {
		{ NULL,                 0.0f },
		{ stbr__filter_nearest, 0.5f },
		{ stbr__filter_linear,  1.0f },
};

stbr_inline static int stbr__use_width_upsampling_noinfo(int output_w, int input_w)
{
	return output_w > input_w;
}

stbr_inline static int stbr__use_height_upsampling_noinfo(int output_h, int input_h)
{
	return output_h > input_h;
}

stbr_inline static int stbr__use_width_upsampling(stbr__info* stbr_info)
{
	return stbr__use_width_upsampling_noinfo(stbr_info->output_w, stbr_info->input_w);
}

stbr_inline static int stbr__use_height_upsampling(stbr__info* stbr_info)
{
	return stbr__use_height_upsampling_noinfo(stbr_info->output_h, stbr_info->input_h);
}

// This is the maximum number of input samples that can affect an output sample
// with the given filter
stbr_inline static int stbr__get_filter_texel_width(stbr_filter filter)
{
	STBR_ASSERT(filter != 0);
	STBR_ASSERT(filter < STBR_ARRAY_SIZE(stbr__filter_info_table));

	return (int)ceil(stbr__filter_info_table[filter].support * 2);
}

// This is how much to expand buffers to account for filters seeking outside
// the image boundaries.
stbr_inline static int stbr__get_filter_texel_margin(stbr_filter filter)
{
	return stbr__get_filter_texel_width(filter) / 2;
}

stbr_inline static int stbr__get_horizontal_contributors(stbr_filter filter, int input_w, int output_w)
{
	if (stbr__use_width_upsampling_noinfo(output_w, input_w))
		return output_w;
	else
		return (input_w + stbr__get_filter_texel_margin(filter) * 2);
}

stbr_inline static int stbr__get_total_coefficients(stbr_filter filter, int input_w, int output_w)
{
	return stbr__get_horizontal_contributors(filter, input_w, output_w) * stbr__get_filter_texel_width(filter);
}

stbr_inline static stbr__contributors* stbr__get_contributor(stbr__info* stbr_info, int n)
{
	STBR_DEBUG_ASSERT(n >= 0 && n < stbr__get_horizontal_contributors(stbr_info->filter, stbr_info->input_w, stbr_info->output_w));
	return &stbr_info->horizontal_contributors[n];
}

stbr_inline static float* stbr__get_coefficient(stbr__info* stbr_info, int n, int c)
{
	return &stbr_info->horizontal_coefficients[stbr__get_filter_texel_width(stbr_info->filter)*n + c];
}

stbr_inline static int stbr__edge_wrap(stbr_edge edge, int n, int max)
{
	STBR_UNIMPLEMENTED(edge != STBR_EDGE_CLAMP);

	switch (edge)
	{
	default:
	case STBR_EDGE_CLAMP:
		if (n < 0)
			return 0;
		if (n >= max)
			return max - 1;
		return n;
	}
}

// What input texels contribute to this output texel?
static void stbr__calculate_sample_range_upsample(int n, float out_filter_radius, float scale_ratio, int* in_first_texel, int* in_last_texel, float* in_center_of_out)
{
	float out_texel_center = (float)n + 0.5f;
	float out_texel_influence_lowerbound = out_texel_center - out_filter_radius;
	float out_texel_influence_upperbound = out_texel_center + out_filter_radius;

	float in_texel_influence_lowerbound = out_texel_influence_lowerbound / scale_ratio;
	float in_texel_influence_upperbound = out_texel_influence_upperbound / scale_ratio;

	*in_center_of_out = out_texel_center / scale_ratio;
	*in_first_texel = (int)(floor(in_texel_influence_lowerbound + 0.5));
	*in_last_texel = (int)(floor(in_texel_influence_upperbound - 0.5));
}

// What output texels does this input texel contribute to?
static void stbr__calculate_sample_range_downsample(int n, float in_pixels_radius, float scale_ratio, int* out_first_texel, int* out_last_texel, float* out_center_of_in)
{
	float in_texel_center = (float)n + 0.5f;
	float in_texel_influence_lowerbound = in_texel_center - in_pixels_radius;
	float in_texel_influence_upperbound = in_texel_center + in_pixels_radius;

	float out_texel_influence_lowerbound = in_texel_influence_lowerbound * scale_ratio;
	float out_texel_influence_upperbound = in_texel_influence_upperbound * scale_ratio;

	*out_center_of_in = in_texel_center * scale_ratio;
	*out_first_texel = (int)(floor(out_texel_influence_lowerbound + 0.5));
	*out_last_texel = (int)(floor(out_texel_influence_upperbound - 0.5));
}

static void stbr__calculate_coefficients_upsample(stbr__info* stbr_info, int in_first_texel, int in_last_texel, float in_center_of_out, stbr__contributors* contributor, float* coefficient_group)
{
	int i;
	float total_filter = 0;
	float filter_scale;
	stbr_filter filter = stbr_info->filter;

	STBR_DEBUG_ASSERT(in_last_texel - in_first_texel <= stbr__get_filter_texel_width(filter));
	STBR_DEBUG_ASSERT(in_last_texel < stbr__get_horizontal_contributors(stbr_info->filter, stbr_info->input_w, stbr_info->output_w));

	contributor->n0 = in_first_texel;
	contributor->n1 = in_last_texel;

	for (i = 0; i <= in_last_texel - in_first_texel; i++)
	{
		float in_texel_center = (float)(i + in_first_texel) + 0.5f;
		total_filter += coefficient_group[i] = stbr__filter_info_table[filter].kernel(in_center_of_out - in_texel_center);
	}

	STBR_DEBUG_ASSERT(total_filter > 0);
	STBR_DEBUG_ASSERT(fabs(1 - total_filter) < 0.1f); // Make sure it's not way off.

	// Make sure the sum of all coefficients is 1.
	filter_scale = 1 / total_filter;

	for (i = 0; i <= in_last_texel - in_first_texel; i++)
		coefficient_group[i] *= filter_scale;
}

static void stbr__calculate_coefficients_downsample(stbr__info* stbr_info, float scale_ratio, int out_first_texel, int out_last_texel, float out_center_of_in, stbr__contributors* contributor, float* coefficient_group)
{
	int i;
	stbr_filter filter = stbr_info->filter;

	STBR_DEBUG_ASSERT(out_last_texel - out_first_texel <= stbr__get_filter_texel_width(filter));
	STBR_DEBUG_ASSERT(out_last_texel < stbr__get_horizontal_contributors(stbr_info->filter, stbr_info->input_w, stbr_info->output_w));

	contributor->n0 = out_first_texel;
	contributor->n1 = out_last_texel;

	for (i = 0; i <= out_last_texel - out_first_texel; i++)
	{
		float in_texel_center = (float)(i + out_first_texel) + 0.5f;
		coefficient_group[i] = stbr__filter_info_table[filter].kernel(out_center_of_in - in_texel_center) * scale_ratio;
	}
}

// Each scan line uses the same kernel values so we should calculate the kernel
// values once and then we can use them for every scan line.
static void stbr__calculate_horizontal_filters(stbr__info* stbr_info)
{
	int n;
	float scale_ratio = (float)stbr_info->output_w / stbr_info->input_w;

	int total_contributors = stbr__get_horizontal_contributors(stbr_info->filter, stbr_info->input_w, stbr_info->output_w);

	if (stbr__use_width_upsampling(stbr_info))
	{
		float out_pixels_radius = stbr__filter_info_table[stbr_info->filter].support * scale_ratio;

		// Looping through out texels
		for (n = 0; n < total_contributors; n++)
		{
			float in_center_of_out; // Center of the current out texel in the in texel space
			int in_first_texel, in_last_texel;

			stbr__calculate_sample_range_upsample(n, out_pixels_radius, scale_ratio, &in_first_texel, &in_last_texel, &in_center_of_out);

			stbr__calculate_coefficients_upsample(stbr_info, in_first_texel, in_last_texel, in_center_of_out, stbr__get_contributor(stbr_info, n), stbr__get_coefficient(stbr_info, n, 0));
		}
	}
	else
	{
		float in_pixels_radius = stbr__filter_info_table[stbr_info->filter].support / scale_ratio;

		// Looping through in texels
		for (n = 0; n < total_contributors; n++)
		{
			float out_center_of_in; // Center of the current out texel in the in texel space
			int out_first_texel, out_last_texel;
			int n_adjusted = n - stbr__get_filter_texel_margin(stbr_info->filter);

			stbr__calculate_sample_range_downsample(n_adjusted, in_pixels_radius, scale_ratio, &out_first_texel, &out_last_texel, &out_center_of_in);

			stbr__calculate_coefficients_downsample(stbr_info, scale_ratio, out_first_texel, out_last_texel, out_center_of_in, stbr__get_contributor(stbr_info, n), stbr__get_coefficient(stbr_info, n, 0));
		}
	}
}

static float* stbr__get_decode_buffer(stbr__info* stbr_info)
{
	// The 0 index of the decode buffer starts after the margin. This makes
	// it okay to use negative indexes on the decode buffer.
	return &stbr_info->decode_buffer[stbr__get_filter_texel_margin(stbr_info->filter) * stbr_info->channels];
}

static void stbr__decode_scanline(stbr__info* stbr_info, int n)
{
	int x, c;
	int channels = stbr_info->channels;
	int input_w = stbr_info->input_w;
	int input_stride_bytes = stbr_info->input_stride_bytes;
	const void* input_data = stbr_info->input_data;
	float* decode_buffer = stbr__get_decode_buffer(stbr_info);
	stbr_edge edge = stbr_info->edge;
	int in_buffer_row_index = stbr__edge_wrap(edge, n, stbr_info->input_h) * input_stride_bytes;
	int max_x = input_w + stbr__get_filter_texel_margin(stbr_info->filter);

	STBR_UNIMPLEMENTED(stbr_info->type != STBR_TYPE_UINT8);

	for (x = -stbr__get_filter_texel_margin(stbr_info->filter); x < max_x; x++)
	{
		int decode_texel_index = x * channels;
		int input_texel_index = in_buffer_row_index + stbr__edge_wrap(edge, x, input_w) * channels;

		for (c = 0; c < channels; c++)
			decode_buffer[decode_texel_index + c] = ((float)((const unsigned char*)input_data)[input_texel_index + c]) / 255;
	}
}

static float* stbr__get_ring_buffer_entry(float* ring_buffer, int index, int ring_buffer_length)
{
	return &ring_buffer[index * ring_buffer_length];
}

static float* stbr__add_empty_ring_buffer_entry(stbr__info* stbr_info, int n)
{
	int ring_buffer_index;
	float* ring_buffer;

	if (stbr_info->ring_buffer_begin_index < 0)
	{
		ring_buffer_index = stbr_info->ring_buffer_begin_index = 0;
		stbr_info->ring_buffer_first_scanline = n;
	}
	else
	{
		ring_buffer_index = (stbr_info->ring_buffer_begin_index + (stbr_info->ring_buffer_last_scanline - stbr_info->ring_buffer_first_scanline) + 1) % stbr__get_filter_texel_width(stbr_info->filter);
		STBR_DEBUG_ASSERT(ring_buffer_index != stbr_info->ring_buffer_begin_index);
	}

	ring_buffer = stbr__get_ring_buffer_entry(stbr_info->ring_buffer, ring_buffer_index, stbr_info->ring_buffer_length_bytes / sizeof(float));
	memset(ring_buffer, 0, stbr_info->ring_buffer_length_bytes);

	stbr_info->ring_buffer_last_scanline = n;

	return ring_buffer;
}

static void stbr__resample_horizontal_upsample(stbr__info* stbr_info, int n, float* output_buffer)
{
	int x, k, c;
	int output_w = stbr_info->output_w;
	int kernel_texel_width = stbr__get_filter_texel_width(stbr_info->filter);
	int channels = stbr_info->channels;
	float* decode_buffer = stbr__get_decode_buffer(stbr_info);
	stbr__contributors* horizontal_contributors = stbr_info->horizontal_contributors;
	float* horizontal_coefficients = stbr_info->horizontal_coefficients;

	for (x = 0; x < output_w; x++)
	{
		int n0 = horizontal_contributors[x].n0;
		int n1 = horizontal_contributors[x].n1;

		int out_texel_index = x * channels;
		int coefficient_group_index = x * kernel_texel_width;
		int coefficient_counter = 0;

		STBR_DEBUG_ASSERT(n1 >= n0);
		STBR_DEBUG_ASSERT(n0 >= -stbr__get_filter_texel_margin(stbr_info->filter));
		STBR_DEBUG_ASSERT(n1 >= -stbr__get_filter_texel_margin(stbr_info->filter));
		STBR_DEBUG_ASSERT(n0 < stbr_info->input_w + stbr__get_filter_texel_margin(stbr_info->filter));
		STBR_DEBUG_ASSERT(n1 < stbr_info->input_w + stbr__get_filter_texel_margin(stbr_info->filter));

		for (k = n0; k <= n1; k++)
		{
			int coefficient_index = coefficient_group_index + (coefficient_counter++);
			int in_texel_index = k * channels;
			float coefficient = horizontal_coefficients[coefficient_index];

			for (c = 0; c < channels; c++)
			{
				output_buffer[out_texel_index + c] += decode_buffer[in_texel_index + c] * coefficient;

				STBR_DEBUG_ASSERT(output_buffer[out_texel_index + c] <= 1.0f);
			}
		}
	}
}

static void stbr__resample_horizontal_downsample(stbr__info* stbr_info, int n, float* output_buffer)
{
	int x, k, c;
	int input_w = stbr_info->input_w;
	int output_w = stbr_info->output_w;
	int kernel_texel_width = stbr__get_filter_texel_width(stbr_info->filter);
	int channels = stbr_info->channels;
	float* decode_buffer = stbr__get_decode_buffer(stbr_info);
	stbr__contributors* horizontal_contributors = stbr_info->horizontal_contributors;
	float* horizontal_coefficients = stbr_info->horizontal_coefficients;
	int filter_texel_margin = stbr__get_filter_texel_margin(stbr_info->filter);
	int max_x = input_w + filter_texel_margin * 2;

	STBR_DEBUG_ASSERT(!stbr__use_width_upsampling(stbr_info));

	for (x = 0; x < max_x; x++)
	{
		int n0 = horizontal_contributors[x].n0;
		int n1 = horizontal_contributors[x].n1;

		int in_x = x - filter_texel_margin;
		int in_texel_index = in_x * channels;
		int max_n = stbr__min(n1, output_w-1);
		int coefficient_group = x*kernel_texel_width;

		STBR_DEBUG_ASSERT(n1 >= n0);

		// Using min and max to avoid writing into invalid texels.
		for (k = stbr__max(n0, 0); k <= max_n; k++)
		{
			int coefficient_index = (k - n0) + coefficient_group;
			int out_texel_index = k * channels;
			float coefficient = horizontal_coefficients[coefficient_index];

			for (c = 0; c < channels; c++)
			{
				output_buffer[out_texel_index + c] += decode_buffer[in_texel_index + c] * coefficient;

				STBR_DEBUG_ASSERT(output_buffer[out_texel_index + c] <= 1.0); // This would indicate that the sum of kernels for this texel doesn't add to 1.
			}
		}
	}
}

static void stbr__decode_and_resample_upsample(stbr__info* stbr_info, int n)
{
	// Decode the nth scanline from the source image into the decode buffer.
	stbr__decode_scanline(stbr_info, n);

	// Now resample it into the ring buffer.
	if (stbr__use_width_upsampling(stbr_info))
		stbr__resample_horizontal_upsample(stbr_info, n, stbr__add_empty_ring_buffer_entry(stbr_info, n));
	else
		stbr__resample_horizontal_downsample(stbr_info, n, stbr__add_empty_ring_buffer_entry(stbr_info, n));

	// Now it's sitting in the ring buffer ready to be used as source for the vertical sampling.
}

static void stbr__decode_and_resample_downsample(stbr__info* stbr_info, int n)
{
	// Decode the nth scanline from the source image into the decode buffer.
	stbr__decode_scanline(stbr_info, n);

	memset(stbr_info->horizontal_buffer, 0, stbr_info->output_w * stbr_info->channels * sizeof(float));

	// Now resample it into the horizontal buffer.
	if (stbr__use_width_upsampling(stbr_info))
		stbr__resample_horizontal_upsample(stbr_info, n, stbr_info->horizontal_buffer);
	else
		stbr__resample_horizontal_downsample(stbr_info, n, stbr_info->horizontal_buffer);

	// Now it's sitting in the horizontal buffer ready to be distributed into the ring buffers.
}

// Get the specified scan line from the ring buffer.
static float* stbr__get_ring_buffer_scanline(int get_scanline, float* ring_buffer, int begin_index, int first_scanline, int ring_buffer_size, int ring_buffer_length)
{
	int ring_buffer_index = (begin_index + (get_scanline - first_scanline)) % ring_buffer_size;
	return stbr__get_ring_buffer_entry(ring_buffer, ring_buffer_index, ring_buffer_length);
}

static void stbr__resample_vertical_upsample(stbr__info* stbr_info, int n, int in_first_scanline, int in_last_scanline, float in_center_of_out)
{
	int x, k, c;
	int output_w = stbr_info->output_w;
	stbr__contributors* vertical_contributors = &stbr_info->vertical_contributors;
	float* vertical_coefficients = stbr_info->vertical_coefficients;
	int channels = stbr_info->channels;
	int kernel_texel_width = stbr__get_filter_texel_width(stbr_info->filter);
	void* output_data = stbr_info->output_data;
	float* encode_buffer = stbr_info->encode_buffer;

	float* ring_buffer = stbr_info->ring_buffer;
	int ring_buffer_begin_index = stbr_info->ring_buffer_begin_index;
	int ring_buffer_first_scanline = stbr_info->ring_buffer_first_scanline;
	int ring_buffer_last_scanline = stbr_info->ring_buffer_last_scanline;
	int ring_buffer_length = stbr_info->ring_buffer_length_bytes/sizeof(float);

	STBR_UNIMPLEMENTED(stbr_info->type != STBR_TYPE_UINT8);

	stbr__calculate_coefficients_upsample(stbr_info, in_first_scanline, in_last_scanline, in_center_of_out, vertical_contributors, vertical_coefficients);

	int n0 = vertical_contributors->n0;
	int n1 = vertical_contributors->n1;

	int output_row_index = n * stbr_info->output_stride_bytes;

	STBR_DEBUG_ASSERT(stbr__use_height_upsampling(stbr_info));
	STBR_DEBUG_ASSERT(n0 >= in_first_scanline);
	STBR_DEBUG_ASSERT(n1 <= in_last_scanline);

	for (x = 0; x < output_w; x++)
	{
		int in_texel_index = x * channels;
		int out_texel_index = output_row_index + x * channels;
		int coefficient_counter = 0;

		STBR_DEBUG_ASSERT(n1 >= n0);

		memset(encode_buffer, 0, sizeof(float) * channels);

		for (k = n0; k <= n1; k++)
		{
			int coefficient_index = coefficient_counter++;
			float* ring_buffer_entry = stbr__get_ring_buffer_scanline(k, ring_buffer, ring_buffer_begin_index, ring_buffer_first_scanline, kernel_texel_width, ring_buffer_length);
			float coefficient = vertical_coefficients[coefficient_index];

			for (c = 0; c < channels; c++)
				encode_buffer[c] += ring_buffer_entry[in_texel_index + c] * coefficient;
		}

		for (c = 0; c < channels; c++)
			((unsigned char*)output_data)[out_texel_index + c] = (unsigned char)(encode_buffer[c] * 255);
	}
}

static void stbr__resample_vertical_downsample(stbr__info* stbr_info, int n, int in_first_scanline, int in_last_scanline, float in_center_of_out)
{
	int x, k, c;
	int output_w = stbr_info->output_w;
	int output_h = stbr_info->output_h;
	stbr__contributors* vertical_contributors = &stbr_info->vertical_contributors;
	float* vertical_coefficients = stbr_info->vertical_coefficients;
	int channels = stbr_info->channels;
	int kernel_texel_width = stbr__get_filter_texel_width(stbr_info->filter);
	void* output_data = stbr_info->output_data;
	float* horizontal_buffer = stbr_info->horizontal_buffer;

	float* ring_buffer = stbr_info->ring_buffer;
	int ring_buffer_begin_index = stbr_info->ring_buffer_begin_index;
	int ring_buffer_first_scanline = stbr_info->ring_buffer_first_scanline;
	int ring_buffer_last_scanline = stbr_info->ring_buffer_last_scanline;
	int ring_buffer_length = stbr_info->ring_buffer_length_bytes/sizeof(float);

	stbr__calculate_coefficients_downsample(stbr_info, (float)stbr_info->output_h / stbr_info->input_h, in_first_scanline, in_last_scanline, in_center_of_out, vertical_contributors, vertical_coefficients);

	int n0 = vertical_contributors->n0;
	int n1 = vertical_contributors->n1;

	STBR_DEBUG_ASSERT(!stbr__use_height_upsampling(stbr_info));
	STBR_DEBUG_ASSERT(n0 >= in_first_scanline);
	STBR_DEBUG_ASSERT(n1 <= in_last_scanline);

	for (x = 0; x < output_w; x++)
	{
		int in_texel_index = x * channels;
		int max_n = stbr__min(n1, output_h-1);

		STBR_DEBUG_ASSERT(n1 >= n0);

		// Using min and max to avoid writing into ring buffers that will be thrown out.
		for (k = stbr__max(n0, 0); k <= max_n; k++)
		{
			int coefficient_index = k - n0;
			float* ring_buffer_entry = stbr__get_ring_buffer_scanline(k, ring_buffer, ring_buffer_begin_index, ring_buffer_first_scanline, kernel_texel_width, ring_buffer_length);
			float coefficient = vertical_coefficients[coefficient_index];

			for (c = 0; c < channels; c++)
			{
				int index = in_texel_index + c;
				ring_buffer_entry[index] += horizontal_buffer[index] * coefficient;

				STBR_DEBUG_ASSERT(ring_buffer_entry[index] <= 1.0); // This would indicate that the sum of kernels for this texel doesn't add to 1.
			}
		}
	}
}

static void stbr__buffer_loop_upsample(stbr__info* stbr_info)
{
	int y;
	float scale_ratio = (float)stbr_info->output_h / stbr_info->input_h;
	float out_scanlines_radius = stbr__filter_info_table[stbr_info->filter].support * scale_ratio;

	STBR_DEBUG_ASSERT(stbr__use_height_upsampling(stbr_info));

	for (y = 0; y < stbr_info->output_h; y++)
	{
		float in_center_of_out = 0; // Center of the current out scanline in the in scanline space
		int in_first_scanline = 0, in_last_scanline = 0;

		stbr__calculate_sample_range_upsample(y, out_scanlines_radius, scale_ratio, &in_first_scanline, &in_last_scanline, &in_center_of_out);

		STBR_DEBUG_ASSERT(in_last_scanline - in_first_scanline <= stbr__get_filter_texel_width(stbr_info->filter));
		STBR_DEBUG_ASSERT(in_first_scanline >= -stbr__get_filter_texel_margin(stbr_info->filter));
		STBR_DEBUG_ASSERT(in_last_scanline < stbr_info->input_w + stbr__get_filter_texel_margin(stbr_info->filter));

		if (stbr_info->ring_buffer_begin_index >= 0)
		{
			// Get rid of whatever we don't need anymore.
			while (in_first_scanline > stbr_info->ring_buffer_first_scanline)
			{
				if (stbr_info->ring_buffer_first_scanline == stbr_info->ring_buffer_last_scanline)
				{
					// We just popped the last scanline off the ring buffer.
					// Reset it to the empty state.
					stbr_info->ring_buffer_begin_index = -1;
					stbr_info->ring_buffer_first_scanline = 0;
					stbr_info->ring_buffer_last_scanline = 0;
					break;
				}
				else
				{
					stbr_info->ring_buffer_first_scanline++;
					stbr_info->ring_buffer_begin_index = (stbr_info->ring_buffer_begin_index + 1) % stbr__get_filter_texel_width(stbr_info->filter);
				}
			}
		}

		// Load in new ones.
		if (stbr_info->ring_buffer_begin_index < 0)
			stbr__decode_and_resample_upsample(stbr_info, in_first_scanline);

		while (in_last_scanline > stbr_info->ring_buffer_last_scanline)
			stbr__decode_and_resample_upsample(stbr_info, stbr_info->ring_buffer_last_scanline + 1);

		// Now all buffers should be ready to write a row of vertical sampling.
		stbr__resample_vertical_upsample(stbr_info, y, in_first_scanline, in_last_scanline, in_center_of_out);
	}
}

static void stbr__empty_ring_buffer(stbr__info* stbr_info, int first_necessary_scanline)
{
	int output_stride_bytes = stbr_info->output_stride_bytes;
	int channels = stbr_info->channels;
	int output_w = stbr_info->output_w;
	void* output_data = stbr_info->output_data;

	float* ring_buffer = stbr_info->ring_buffer;
	int ring_buffer_length = stbr_info->ring_buffer_length_bytes/sizeof(float);

	if (stbr_info->ring_buffer_begin_index >= 0)
	{
		// Get rid of whatever we don't need anymore.
		while (first_necessary_scanline > stbr_info->ring_buffer_first_scanline || first_necessary_scanline < 0)
		{
			int x, c;
			int output_row = stbr_info->ring_buffer_first_scanline * output_stride_bytes;
			float* ring_buffer_entry = stbr__get_ring_buffer_entry(ring_buffer, stbr_info->ring_buffer_begin_index, ring_buffer_length);

			STBR_UNIMPLEMENTED(stbr_info->type != STBR_TYPE_UINT8);

			if (stbr_info->ring_buffer_first_scanline >= 0 && stbr_info->ring_buffer_first_scanline < stbr_info->output_h)
			{
				for (x = 0; x < output_w; x++)
				{
					int texel_index = x * channels;
					int ring_texel_index = texel_index;
					int output_texel_index = output_row + texel_index;
					for (c = 0; c < channels; c++)
						((unsigned char*)output_data)[output_texel_index + c] = (unsigned char)(ring_buffer_entry[ring_texel_index + c] * 255);
				}
			}

			if (stbr_info->ring_buffer_first_scanline == stbr_info->ring_buffer_last_scanline)
			{
				// We just popped the last scanline off the ring buffer.
				// Reset it to the empty state.
				stbr_info->ring_buffer_begin_index = -1;
				stbr_info->ring_buffer_first_scanline = 0;
				stbr_info->ring_buffer_last_scanline = 0;
				break;
			}
			else
			{
				stbr_info->ring_buffer_first_scanline++;
				stbr_info->ring_buffer_begin_index = (stbr_info->ring_buffer_begin_index + 1) % stbr__get_filter_texel_width(stbr_info->filter);
			}
		}
	}
}

static void stbr__buffer_loop_downsample(stbr__info* stbr_info)
{
	int y;
	float scale_ratio = (float)stbr_info->output_h / stbr_info->input_h;
	float in_pixels_radius = stbr__filter_info_table[stbr_info->filter].support / scale_ratio;

	STBR_DEBUG_ASSERT(!stbr__use_height_upsampling(stbr_info));

	for (y = 0; y < stbr_info->input_h; y++)
	{
		float out_center_of_in; // Center of the current out scanline in the in scanline space
		int out_first_scanline, out_last_scanline;

		stbr__calculate_sample_range_downsample(y, in_pixels_radius, scale_ratio, &out_first_scanline, &out_last_scanline, &out_center_of_in);

		STBR_DEBUG_ASSERT(out_last_scanline - out_first_scanline <= stbr__get_filter_texel_width(stbr_info->filter));
		STBR_DEBUG_ASSERT(out_first_scanline >= -stbr__get_filter_texel_margin(stbr_info->filter));
		STBR_DEBUG_ASSERT(out_last_scanline < stbr_info->input_w + stbr__get_filter_texel_margin(stbr_info->filter));

		stbr__empty_ring_buffer(stbr_info, out_first_scanline);

		stbr__decode_and_resample_downsample(stbr_info, y);

		// Load in new ones.
		if (stbr_info->ring_buffer_begin_index < 0)
			stbr__add_empty_ring_buffer_entry(stbr_info, out_first_scanline);

		while (out_last_scanline > stbr_info->ring_buffer_last_scanline)
			stbr__add_empty_ring_buffer_entry(stbr_info, stbr_info->ring_buffer_last_scanline + 1);

		// Now the horizontal buffer is ready to write to all ring buffer rows.
		stbr__resample_vertical_downsample(stbr_info, y, out_first_scanline, out_last_scanline, out_center_of_in);
	}

	stbr__empty_ring_buffer(stbr_info, -1);
}

STBRDEF int stbr_resize_arbitrary(const void* input_data, int input_w, int input_h, int input_stride_in_bytes,
	void* output_data, int output_w, int output_h, int output_stride_in_bytes,
	int channels, stbr_type type, stbr_filter filter, stbr_edge edge,
	void* tempmem, stbr_size_t tempmem_size_in_bytes)
{
	int width_stride_input = input_stride_in_bytes ? input_stride_in_bytes : channels * input_w;
	int width_stride_output = output_stride_in_bytes ? output_stride_in_bytes : channels * output_w;

#ifdef STBR_DEBUG_OVERWRITE_TEST
#define OVERWRITE_ARRAY_SIZE 64
	unsigned char overwrite_output_pre[OVERWRITE_ARRAY_SIZE];
	unsigned char overwrite_tempmem_pre[OVERWRITE_ARRAY_SIZE];

	stbr_size_t begin_forbidden = width_stride_output * (output_h - 1) + output_w * channels;
	memcpy(overwrite_output_pre, &((unsigned char*)output_data)[begin_forbidden], OVERWRITE_ARRAY_SIZE);
	memcpy(overwrite_tempmem_pre, &((unsigned char*)tempmem)[tempmem_size_in_bytes], OVERWRITE_ARRAY_SIZE);
#endif

	STBR_UNIMPLEMENTED(type != STBR_TYPE_UINT8);

	STBR_ASSERT(filter != 0);
	STBR_ASSERT(filter < STBR_ARRAY_SIZE(stbr__filter_info_table));

	if (!tempmem)
		return 0;

	if (tempmem_size_in_bytes < stbr_calculate_memory(input_w, input_h, input_stride_in_bytes, output_w, output_h, output_stride_in_bytes, channels, STBR_FILTER_NEAREST))
		return 0;

	memset(tempmem, 0, tempmem_size_in_bytes);

	stbr__info* stbr_info = (stbr__info*)tempmem;

	stbr_info->input_data = input_data;
	stbr_info->input_w = input_w;
	stbr_info->input_h = input_h;
	stbr_info->input_stride_bytes = width_stride_input;

	stbr_info->output_data = output_data;
	stbr_info->output_w = output_w;
	stbr_info->output_h = output_h;
	stbr_info->output_stride_bytes = width_stride_output;

	stbr_info->channels = channels;
	stbr_info->type = type;
	stbr_info->filter = filter;
	stbr_info->edge = edge;

	stbr_info->ring_buffer_length_bytes = output_w * channels * sizeof(float);
	stbr_info->decode_buffer_texels = input_w + stbr__get_filter_texel_margin(filter) * 2;

#define STBR__NEXT_MEMPTR(current, old, newtype) (newtype*)(((unsigned char*)current) + old)

	stbr_info->horizontal_contributors = STBR__NEXT_MEMPTR(stbr_info, sizeof(stbr__info), stbr__contributors);
	stbr_info->horizontal_coefficients = STBR__NEXT_MEMPTR(stbr_info->horizontal_contributors, stbr__get_horizontal_contributors(filter, input_w, output_w) * sizeof(stbr__contributors), float);
	stbr_info->vertical_coefficients = STBR__NEXT_MEMPTR(stbr_info->horizontal_coefficients, stbr__get_total_coefficients(filter, input_w, output_w) * sizeof(float), float);
	stbr_info->decode_buffer = STBR__NEXT_MEMPTR(stbr_info->vertical_coefficients, stbr__get_filter_texel_width(filter) * sizeof(float), float);

	if (stbr__use_height_upsampling(stbr_info))
	{
		stbr_info->horizontal_buffer = NULL;
		stbr_info->ring_buffer = STBR__NEXT_MEMPTR(stbr_info->decode_buffer, stbr_info->decode_buffer_texels * channels * sizeof(float), float);
		stbr_info->encode_buffer = STBR__NEXT_MEMPTR(stbr_info->ring_buffer, stbr_info->ring_buffer_length_bytes * stbr__get_filter_texel_width(filter), float);

		STBR_DEBUG_ASSERT((size_t)STBR__NEXT_MEMPTR(stbr_info->encode_buffer, stbr_info->channels * sizeof(float), unsigned char) == (size_t)tempmem + tempmem_size_in_bytes);
	}
	else
	{
		stbr_info->horizontal_buffer = STBR__NEXT_MEMPTR(stbr_info->decode_buffer, stbr_info->decode_buffer_texels * channels * sizeof(float), float);
		stbr_info->ring_buffer = STBR__NEXT_MEMPTR(stbr_info->horizontal_buffer, output_w * channels * sizeof(float), float);
		stbr_info->encode_buffer = NULL;

		STBR_DEBUG_ASSERT((size_t)STBR__NEXT_MEMPTR(stbr_info->ring_buffer, stbr_info->ring_buffer_length_bytes * stbr__get_filter_texel_width(filter), unsigned char) == (size_t)tempmem + tempmem_size_in_bytes);
	}

#undef STBR__NEXT_MEMPTR

	// This signals that the ring buffer is empty
	stbr_info->ring_buffer_begin_index = -1;

	stbr__calculate_horizontal_filters(stbr_info);

	if (stbr__use_height_upsampling(stbr_info))
		stbr__buffer_loop_upsample(stbr_info);
	else
		stbr__buffer_loop_downsample(stbr_info);

#ifdef STBR_DEBUG_OVERWRITE_TEST
	STBR_DEBUG_ASSERT(memcmp(overwrite_output_pre, &((unsigned char*)output_data)[begin_forbidden], OVERWRITE_ARRAY_SIZE) == 0);
	STBR_DEBUG_ASSERT(memcmp(overwrite_tempmem_pre, &((unsigned char*)tempmem)[tempmem_size_in_bytes], OVERWRITE_ARRAY_SIZE) == 0);
#endif

	return 1;
}


STBRDEF stbr_size_t stbr_calculate_memory(int input_w, int input_h, int input_stride_in_bytes,
	int output_w, int output_h, int output_stride_in_bytes,
	int channels, stbr_filter filter)
{
	STBR_ASSERT(filter != 0);
	STBR_ASSERT(filter < STBR_ARRAY_SIZE(stbr__filter_info_table));

	int texel_margin = stbr__get_filter_texel_margin(filter);

	int info_size = sizeof(stbr__info);
	int contributors_size = stbr__get_horizontal_contributors(filter, input_w, output_w) * sizeof(stbr__contributors);
	int horizontal_coefficients_size = stbr__get_total_coefficients(filter, input_w, output_w) * sizeof(float);
	int vertical_coefficients_size = stbr__get_filter_texel_width(filter) * sizeof(float);
	int decode_buffer_size = (input_w + texel_margin*2) * channels * sizeof(float);
	int horizontal_buffer_size = output_w * channels * sizeof(float);
	int ring_buffer_size = output_w * channels * sizeof(float) * stbr__get_filter_texel_width(filter);
	int encode_buffer_size = channels * sizeof(float);

	if (stbr__use_height_upsampling_noinfo(output_h, input_h))
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

#endif // STB_RESAMPLE_IMPLEMENTATION

/*
revision history:
*/
