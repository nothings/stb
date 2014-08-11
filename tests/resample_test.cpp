#ifdef _WIN32
#define STBR_ASSERT(x) \
	if (!(x)) \
		__debugbreak();
#else
#include <assert.h>
#define STBR_ASSERT(x) assert(x)
#endif

#define STB_RESAMPLE_IMPLEMENTATION
#define STB_RESAMPLE_STATIC
#include "stb_resample.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef _WIN32
#include <sys/timeb.h>
#endif

void test_suite();

int main(int argc, char** argv)
{
	unsigned char* input_data;
	unsigned char* output_data;
	int w, h;
	int n;
	int out_w, out_h, out_stride;

#if 1
	test_suite();
	return 0;
#endif

	if (argc <= 1)
	{
		printf("No input image\n");
		return 1;
	}

	input_data = stbi_load(argv[1], &w, &h, &n, 0);
	if (!input_data)
	{
		printf("Input image could not be loaded");
		return 1;
	}

	out_w = 512;
	out_h = 512;
	out_stride = (out_w + 10) * n;

	output_data = (unsigned char*)malloc(out_stride * out_h);

	int in_w = 512;
	int in_h = 512;

	float s0 = 0.25f;
	float t0 = 0.25f;
	float s1 = 0.75f;
	float t1 = 0.75f;

	// Cut out the outside 64 pixels all around to test the stride.
	int border = 64;
	STBR_ASSERT(in_w + border <= w);
	STBR_ASSERT(in_h + border <= h);

#ifdef PERF_TEST
	struct timeb initial_time_millis, final_time_millis;

	long average = 0;
	for (int j = 0; j < 10; j++)
	{
		ftime(&initial_time_millis);
		for (int i = 0; i < 100; i++)
			stbr_resize_advanced(input_data + w * border * n + border * n, in_w, in_h, w*n, output_data, out_w, out_h, out_stride, n, STBR_TYPE_UINT8, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB);
		ftime(&final_time_millis);
		long lapsed_ms = (long)(final_time_millis.time - initial_time_millis.time) * 1000 + (final_time_millis.millitm - initial_time_millis.millitm);
		printf("Resample: %dms\n", lapsed_ms);

		average += lapsed_ms;
	}

	average /= 10;

	printf("Average: %dms\n", average);
#else
	stbr_resize_arbitrary(input_data + w * border * n + border * n, in_w, in_h, w*n, output_data, out_w, out_h, out_stride, s0, t0, s1, t1, n, -1, STBR_TYPE_UINT8, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB);
#endif

	stbi_image_free(input_data);

	stbi_write_png("output.png", out_w, out_h, n, output_data, out_stride);

	free(output_data);

	return 0;
}

void resize_image(const char* filename, float width_percent, float height_percent, stbr_filter filter, stbr_edge edge, stbr_colorspace colorspace, const char* output_filename)
{
	int w, h, n;

	unsigned char* input_data = stbi_load(filename, &w, &h, &n, 0);
	if (!input_data)
	{
		printf("Input image could not be loaded");
		return;
	}

	int out_w = (int)(w * width_percent);
	int out_h = (int)(h * height_percent);

	unsigned char* output_data = (unsigned char*)malloc(out_w * out_h * n);

	stbr_resize_arbitrary(input_data, w, h, 0, output_data, out_w, out_h, 0, 0, 0, 1, 1, n, -1, STBR_TYPE_UINT8, filter, edge, colorspace);

	stbi_image_free(input_data);

	stbi_write_png(output_filename, out_w, out_h, n, output_data, 0);

	free(output_data);
}

template <typename F, typename T>
void convert_image(const F* input, T* output, int length)
{
	double f = (pow(2.0, 8.0 * sizeof(T)) - 1) / (pow(2.0, 8.0 * sizeof(F)) - 1);
	for (int i = 0; i < length; i++)
		output[i] = (T)(((double)input[i]) * f);
}

template <typename T>
void test_format(const char* file, float width_percent, float height_percent, stbr_type type, stbr_colorspace colorspace)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 0);

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	T* T_data = (T*)malloc(w * h * n * sizeof(T));
	convert_image<unsigned char, T>(input_data, T_data, w * h * n);

	T* output_data = (T*)malloc(new_w * new_h * n * sizeof(T));

	stbr_resize_arbitrary(T_data, w, h, 0, output_data, new_w, new_h, 0, 0, 0, 1, 1, n, -1, type, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, colorspace);

	free(T_data);
	stbi_image_free(input_data);

	unsigned char* char_data = (unsigned char*)malloc(new_w * new_h * n * sizeof(char));
	convert_image<T, unsigned char>(output_data, char_data, new_w * new_h * n);

	char output[200];
	sprintf(output, "test-output/type-%d-%d-%d-%d-%s", type, colorspace, new_w, new_h, file);
	stbi_write_png(output, new_w, new_h, n, char_data, 0);

	free(char_data);
	free(output_data);
}

void convert_image_float(const unsigned char* input, float* output, int length)
{
	for (int i = 0; i < length; i++)
		output[i] = ((float)input[i])/255;
}

void convert_image_float(const float* input, unsigned char* output, int length)
{
	for (int i = 0; i < length; i++)
		output[i] = (unsigned char)(input[i] * 255);
}

void test_float(const char* file, float width_percent, float height_percent, stbr_type type, stbr_colorspace colorspace)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 0);

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	float* T_data = (float*)malloc(w * h * n * sizeof(float));
	convert_image_float(input_data, T_data, w * h * n);

	float* output_data = (float*)malloc(new_w * new_h * n * sizeof(float));

	stbr_resize_arbitrary(T_data, w, h, 0, output_data, new_w, new_h, 0, 0, 0, 1, 1, n, -1, type, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, colorspace);

	free(T_data);
	stbi_image_free(input_data);

	unsigned char* char_data = (unsigned char*)malloc(new_w * new_h * n * sizeof(char));
	convert_image_float(output_data, char_data, new_w * new_h * n);

	char output[200];
	sprintf(output, "test-output/type-%d-%d-%d-%d-%s", type, colorspace, new_w, new_h, file);
	stbi_write_png(output, new_w, new_h, n, char_data, 0);

	free(char_data);
	free(output_data);
}

void test_channels(const char* file, float width_percent, float height_percent, int channels)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 0);

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	unsigned char* channels_data = (unsigned char*)malloc(w * h * channels * sizeof(unsigned char));

	for (int i = 0; i < w * h; i++)
	{
		int input_position = i * n;
		int output_position = i * channels;

		for (int c = 0; c < channels; c++)
			channels_data[output_position + c] = input_data[input_position + stbr__min(c, n)];
	}

	unsigned char* output_data = (unsigned char*)malloc(new_w * new_h * channels * sizeof(unsigned char));

	stbr_resize_uint8_srgb(channels_data, w, h, output_data, new_w, new_h, channels, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP);

	free(channels_data);
	stbi_image_free(input_data);

	char output[200];
	sprintf(output, "test-output/channels-%d-%d-%d-%s", channels, new_w, new_h, file);
	stbi_write_png(output, new_w, new_h, channels, output_data, 0);

	free(output_data);
}

void test_subpixel(const char* file, float width_percent, float height_percent, float s1, float t1)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 0);

	s1 = ((float)w - 1 + s1)/w;
	t1 = ((float)h - 1 + t1)/h;

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	unsigned char* output_data = (unsigned char*)malloc(new_w * new_h * n * sizeof(unsigned char));

	stbr_resize_arbitrary(input_data, w, h, 0, output_data, new_w, new_h, 0, 0, 0, s1, t1, n, -1, STBR_TYPE_UINT8, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB);

	stbi_image_free(input_data);

	char output[200];
	sprintf(output, "test-output/subpixel-%d-%d-%f-%f-%s", new_w, new_h, s1, t1, file);
	stbi_write_png(output, new_w, new_h, n, output_data, 0);

	free(output_data);
}

void test_premul(const char* file)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 4);
	n = 4;

	// Set alpha for the top half.
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h / 2; y++)
			input_data[(y*w + x)*n + 3] = input_data[(y*w + x)*n + 0];
	}

	stbi_write_png("test-output/premul-original.png", w, h, n, input_data, 0);

	int new_w = (int)(w * .1);
	int new_h = (int)(h * .1);

	unsigned char* output_data = (unsigned char*)malloc(new_w * new_h * n * sizeof(unsigned char));

	stbr_resize_arbitrary(input_data, w, h, 0, output_data, new_w, new_h, 0, 0, 0, 1, 1, n, 3, STBR_TYPE_UINT8, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB);

	char output[200];
	sprintf(output, "test-output/premul-%s", file);
	stbi_write_png(output, new_w, new_h, n, output_data, 0);

	stbr_resize_arbitrary(input_data, w, h, 0, output_data, new_w, new_h, 0, 0, 0, 1, 1, n, -1, STBR_TYPE_UINT8, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB);

	sprintf(output, "test-output/nopremul-%s", file);
	stbi_write_png(output, new_w, new_h, n, output_data, 0);

	stbi_image_free(input_data);

	free(output_data);
}

void test_suite()
{
	test_premul("barbara.png");

	for (int i = 0; i < 10; i++)
		test_subpixel("barbara.png", 0.5f, 0.5f, (float)i / 10, 1);

	for (int i = 0; i < 10; i++)
		test_subpixel("barbara.png", 0.5f, 0.5f, 1, (float)i / 10);

	for (int i = 0; i < 10; i++)
		test_subpixel("barbara.png", 2, 2, (float)i / 10, 1);

	for (int i = 0; i < 10; i++)
		test_subpixel("barbara.png", 2, 2, 1, (float)i / 10);

	// Channels test
	test_channels("barbara.png", 0.5f, 0.5f, 1);
	test_channels("barbara.png", 0.5f, 0.5f, 2);
	test_channels("barbara.png", 0.5f, 0.5f, 3);
	test_channels("barbara.png", 0.5f, 0.5f, 4);

	test_channels("barbara.png", 2, 2, 1);
	test_channels("barbara.png", 2, 2, 2);
	test_channels("barbara.png", 2, 2, 3);
	test_channels("barbara.png", 2, 2, 4);

	// Edge behavior tests
	resize_image("hgradient.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_LINEAR, "test-output/hgradient-clamp.png");
	resize_image("hgradient.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_WRAP, STBR_COLORSPACE_LINEAR, "test-output/hgradient-wrap.png");

	resize_image("vgradient.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_LINEAR, "test-output/vgradient-clamp.png");
	resize_image("vgradient.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_WRAP, STBR_COLORSPACE_LINEAR, "test-output/vgradient-wrap.png");

	resize_image("1px-border.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_REFLECT, STBR_COLORSPACE_LINEAR, "test-output/1px-border-reflect.png");
	resize_image("1px-border.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_LINEAR, "test-output/1px-border-clamp.png");

	// sRGB tests
	resize_image("gamma_colors.jpg", .5f, .5f, STBR_FILTER_CATMULLROM, STBR_EDGE_REFLECT, STBR_COLORSPACE_SRGB, "test-output/gamma_colors.jpg");
	resize_image("gamma_2.2.jpg", .5f, .5f, STBR_FILTER_CATMULLROM, STBR_EDGE_REFLECT, STBR_COLORSPACE_SRGB, "test-output/gamma_2.2.jpg");
	resize_image("gamma_dalai_lama_gray.jpg", .5f, .5f, STBR_FILTER_CATMULLROM, STBR_EDGE_REFLECT, STBR_COLORSPACE_SRGB, "test-output/gamma_dalai_lama_gray.jpg");

	// filter tests
	resize_image("barbara.png", 2, 2, STBR_FILTER_NEAREST, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-upsample-nearest.png");
	resize_image("barbara.png", 2, 2, STBR_FILTER_BILINEAR, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-upsample-bilinear.png");
	resize_image("barbara.png", 2, 2, STBR_FILTER_BICUBIC, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-upsample-bicubic.png");
	resize_image("barbara.png", 2, 2, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-upsample-catmullrom.png");
	resize_image("barbara.png", 2, 2, STBR_FILTER_MITCHELL, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-upsample-mitchell.png");

	resize_image("barbara.png", 0.5f, 0.5f, STBR_FILTER_NEAREST, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-downsample-nearest.png");
	resize_image("barbara.png", 0.5f, 0.5f, STBR_FILTER_BILINEAR, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-downsample-bilinear.png");
	resize_image("barbara.png", 0.5f, 0.5f, STBR_FILTER_BICUBIC, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-downsample-bicubic.png");
	resize_image("barbara.png", 0.5f, 0.5f, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-downsample-catmullrom.png");
	resize_image("barbara.png", 0.5f, 0.5f, STBR_FILTER_MITCHELL, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, "test-output/barbara-downsample-mitchell.png");

	for (int i = 10; i < 100; i++)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-width-%d.jpg", i);
		resize_image("barbara.png", (float)i / 100, 1, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, outname);
	}

	for (int i = 110; i < 500; i += 10)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-width-%d.jpg", i);
		resize_image("barbara.png", (float)i / 100, 1, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, outname);
	}

	for (int i = 10; i < 100; i++)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-height-%d.jpg", i);
		resize_image("barbara.png", 1, (float)i / 100, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, outname);
	}

	for (int i = 110; i < 500; i += 10)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-height-%d.jpg", i);
		resize_image("barbara.png", 1, (float)i / 100, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, outname);
	}

	for (int i = 50; i < 200; i += 10)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-width-height-%d.jpg", i);
		resize_image("barbara.png", 100 / (float)i, (float)i / 100, STBR_FILTER_CATMULLROM, STBR_EDGE_CLAMP, STBR_COLORSPACE_SRGB, outname);
	}

	test_format<unsigned short>("barbara.png", 0.5, 2.0, STBR_TYPE_UINT16, STBR_COLORSPACE_SRGB);
	test_format<unsigned short>("barbara.png", 0.5, 2.0, STBR_TYPE_UINT16, STBR_COLORSPACE_LINEAR);
	test_format<unsigned short>("barbara.png", 2.0, 0.5, STBR_TYPE_UINT16, STBR_COLORSPACE_SRGB);
	test_format<unsigned short>("barbara.png", 2.0, 0.5, STBR_TYPE_UINT16, STBR_COLORSPACE_LINEAR);

	test_format<unsigned int>("barbara.png", 0.5, 2.0, STBR_TYPE_UINT32, STBR_COLORSPACE_SRGB);
	test_format<unsigned int>("barbara.png", 0.5, 2.0, STBR_TYPE_UINT32, STBR_COLORSPACE_LINEAR);
	test_format<unsigned int>("barbara.png", 2.0, 0.5, STBR_TYPE_UINT32, STBR_COLORSPACE_SRGB);
	test_format<unsigned int>("barbara.png", 2.0, 0.5, STBR_TYPE_UINT32, STBR_COLORSPACE_LINEAR);

	test_float("barbara.png", 0.5, 2.0, STBR_TYPE_FLOAT, STBR_COLORSPACE_SRGB);
	test_float("barbara.png", 0.5, 2.0, STBR_TYPE_FLOAT, STBR_COLORSPACE_LINEAR);
	test_float("barbara.png", 2.0, 0.5, STBR_TYPE_FLOAT, STBR_COLORSPACE_SRGB);
	test_float("barbara.png", 2.0, 0.5, STBR_TYPE_FLOAT, STBR_COLORSPACE_LINEAR);
}


