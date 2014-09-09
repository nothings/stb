#include <malloc.h>

#if defined(_WIN32) && _MSC_VER > 1200
#define STBIR_ASSERT(x) \
	if (!(x)) {         \
		__debugbreak();  \
	} else
#else
#include <assert.h>
#define STBIR_ASSERT(x) assert(x)
#endif

#define STBIR_MALLOC stbir_malloc
#define STBIR_FREE stbir_free

class stbir_context {
public:
	stbir_context()
	{
		size = 1000000;
		memory = malloc(size);
	}

	~stbir_context()
	{
		free(memory);
	}

	size_t size;
	void* memory;
} g_context;

void* stbir_malloc(void* context, size_t size)
{
	if (!context)
		return malloc(size);

	stbir_context* real_context = (stbir_context*)context;
	if (size > real_context->size)
		return 0;

	return real_context->memory;
}

void stbir_free(void* context, void* memory)
{
	if (!context)
		return free(memory);
}

void stbir_progress(float p)
{
	STBIR_ASSERT(p >= 0 && p <= 1);
}

#define STBIR_PROGRESS_REPORT stbir_progress

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include "stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef _WIN32
#include <sys/timeb.h>
#endif

#include <direct.h>

#define MT_SIZE 624
static size_t g_aiMT[MT_SIZE];
static size_t g_iMTI = 0;

// Mersenne Twister implementation from Wikipedia.
// Avoiding use of the system rand() to be sure that our tests generate the same test data on any system.
void mtsrand(size_t iSeed)
{
	g_aiMT[0] = iSeed;
	for (size_t i = 1; i < MT_SIZE; i++)
	{
		size_t inner1 = g_aiMT[i - 1];
		size_t inner2 = (g_aiMT[i - 1] >> 30);
		size_t inner = inner1 ^ inner2;
		g_aiMT[i] = (0x6c078965 * inner) + i;
	}

	g_iMTI = 0;
}

size_t mtrand()
{
	if (g_iMTI == 0)
	{
		for (size_t i = 0; i < MT_SIZE; i++)
		{
			size_t y = (0x80000000 & (g_aiMT[i])) + (0x7fffffff & (g_aiMT[(i + 1) % MT_SIZE]));
			g_aiMT[i] = g_aiMT[(i + 397) % MT_SIZE] ^ (y >> 1);
			if ((y % 2) == 1)
				g_aiMT[i] = g_aiMT[i] ^ 0x9908b0df;
		}
	}

	size_t y = g_aiMT[g_iMTI];
	y = y ^ (y >> 11);
	y = y ^ ((y << 7) & (0x9d2c5680));
	y = y ^ ((y << 15) & (0xefc60000));
	y = y ^ (y >> 18);

	g_iMTI = (g_iMTI + 1) % MT_SIZE;

	return y;
}


inline float mtfrand()
{
	const int ninenine = 999999;
	return (float)(mtrand() % ninenine)/ninenine;
}


void test_suite(int argc, char **argv);

int main(int argc, char** argv)
{
	unsigned char* input_data;
	unsigned char* output_data;
	int w, h;
	int n;
	int out_w, out_h, out_stride;

#if 1
	test_suite(argc, argv);
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
	STBIR_ASSERT(in_w + border <= w);
	STBIR_ASSERT(in_h + border <= h);

#ifdef PERF_TEST
	struct timeb initial_time_millis, final_time_millis;

	long average = 0;
	for (int j = 0; j < 10; j++)
	{
		ftime(&initial_time_millis);
		for (int i = 0; i < 100; i++)
			stbir_resize(input_data + w * border * n + border * n, in_w, in_h, w*n, output_data, out_w, out_h, out_stride, STBIR_TYPE_UINT8, n, n - 1, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context);
		ftime(&final_time_millis);
		long lapsed_ms = (long)(final_time_millis.time - initial_time_millis.time) * 1000 + (final_time_millis.millitm - initial_time_millis.millitm);
		printf("Resample: %dms\n", lapsed_ms);

		average += lapsed_ms;
	}

	average /= 10;

	printf("Average: %dms\n", average);

	stbi_image_free(input_data);

	stbi_write_png("output.png", out_w, out_h, n, output_data, out_stride);
#else
	stbir_resize_region(input_data + w * border * n + border * n, in_w, in_h, w*n, output_data, out_w, out_h, out_stride, STBIR_TYPE_UINT8, n, n-1, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, s0, t0, s1, t1);

	stbi_write_png("output-region.png", out_w, out_h, n, output_data, out_stride);

	stbir_resize_subpixel(input_data + w * border * n + border * n, in_w, in_h, w*n, output_data, out_w, out_h, out_stride, STBIR_TYPE_UINT8, n, n-1, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, in_w*s0, in_h*t0, 0.5f, 0.5f);

	stbi_write_png("output-subpixel.png", out_w, out_h, n, output_data, out_stride);

	stbi_image_free(input_data);
#endif

	free(output_data);

	return 0;
}

void resize_image(const char* filename, float width_percent, float height_percent, stbir_filter filter, stbir_edge edge, stbir_colorspace colorspace, const char* output_filename)
{
	int w, h, n;

	unsigned char* input_data = stbi_load(filename, &w, &h, &n, 0);
	if (!input_data)
	{
		printf("Input image could not be loaded\n");
		return;
	}

	int out_w = (int)(w * width_percent);
	int out_h = (int)(h * height_percent);

	unsigned char* output_data = (unsigned char*)malloc(out_w * out_h * n);

	stbir_resize(input_data, w, h, 0, output_data, out_w, out_h, 0, STBIR_TYPE_UINT8, n, STBIR_ALPHA_CHANNEL_NONE, 0, edge, edge, filter, filter, colorspace, &g_context);

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
void test_format(const char* file, float width_percent, float height_percent, stbir_datatype type, stbir_colorspace colorspace)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 0);

	if (input_data == NULL)
		return;


	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	T* T_data = (T*)malloc(w * h * n * sizeof(T));
	convert_image<unsigned char, T>(input_data, T_data, w * h * n);

	T* output_data = (T*)malloc(new_w * new_h * n * sizeof(T));

	stbir_resize(T_data, w, h, 0, output_data, new_w, new_h, 0, type, n, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, colorspace, &g_context);

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

void test_float(const char* file, float width_percent, float height_percent, stbir_datatype type, stbir_colorspace colorspace)
{
	int w, h, n;
	unsigned char* input_data = stbi_load(file, &w, &h, &n, 0);

	if (input_data == NULL)
		return;

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	float* T_data = (float*)malloc(w * h * n * sizeof(float));
	convert_image_float(input_data, T_data, w * h * n);

	float* output_data = (float*)malloc(new_w * new_h * n * sizeof(float));

	stbir_resize_float_generic(T_data, w, h, 0, output_data, new_w, new_h, 0, n, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, colorspace, &g_context);

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

	if (input_data == NULL)
		return;

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	unsigned char* channels_data = (unsigned char*)malloc(w * h * channels * sizeof(unsigned char));

	for (int i = 0; i < w * h; i++)
	{
		int input_position = i * n;
		int output_position = i * channels;

		for (int c = 0; c < channels; c++)
			channels_data[output_position + c] = input_data[input_position + stbir__min(c, n)];
	}

	unsigned char* output_data = (unsigned char*)malloc(new_w * new_h * channels * sizeof(unsigned char));

	stbir_resize_uint8_srgb(channels_data, w, h, 0, output_data, new_w, new_h, 0, channels, STBIR_ALPHA_CHANNEL_NONE, 0);

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

	if (input_data == NULL)
		return;

	s1 = ((float)w - 1 + s1)/w;
	t1 = ((float)h - 1 + t1)/h;

	int new_w = (int)(w * width_percent);
	int new_h = (int)(h * height_percent);

	unsigned char* output_data = (unsigned char*)malloc(new_w * new_h * n * sizeof(unsigned char));

	stbir_resize_region(input_data, w, h, 0, output_data, new_w, new_h, 0, STBIR_TYPE_UINT8, n, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, 0, 0, s1, t1);

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

	if (input_data == NULL)
		return;


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

	stbir_resize_uint8_generic(input_data, w, h, 0, output_data, new_w, new_h, 0, n, n - 1, 0, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context);

	char output[200];
	sprintf(output, "test-output/premul-%s", file);
	stbi_write_png(output, new_w, new_h, n, output_data, 0);

	stbir_resize_uint8_generic(input_data, w, h, 0, output_data, new_w, new_h, 0, n, n - 1, STBIR_FLAG_PREMULTIPLIED_ALPHA, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context);

	sprintf(output, "test-output/nopremul-%s", file);
	stbi_write_png(output, new_w, new_h, n, output_data, 0);

	stbi_image_free(input_data);

	free(output_data);
}

// test that splitting a pow-2 image into tiles produces identical results
void test_subpixel_1()
{
	unsigned char image[8 * 8];

	mtsrand(0);

	for (int i = 0; i < sizeof(image); i++)
		image[i] = mtrand() & 255;

	unsigned char output_data[16 * 16];

	stbir_resize_region(image, 8, 8, 0, output_data, 16, 16, 0, STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, 0, 0, 1, 1);

	unsigned char output_left[8 * 16];
	unsigned char output_right[8 * 16];

	stbir_resize_region(image, 8, 8, 0, output_left, 8, 16, 0, STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, 0, 0, 0.5f, 1);
	stbir_resize_region(image, 8, 8, 0, output_right, 8, 16, 0, STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, 0.5f, 0, 1, 1);

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			STBIR_ASSERT(output_data[y * 16 + x] == output_left[y * 8 + x]);
			STBIR_ASSERT(output_data[y * 16 + x + 8] == output_right[y * 8 + x]);
		}
	}
}

// test that replicating an image and using a subtile of it produces same results as wraparound
void test_subpixel_2()
{
	unsigned char image[8 * 8];

	mtsrand(0);

	for (int i = 0; i < sizeof(image); i++)
		image[i] = mtrand() & 255;

	unsigned char large_image[32 * 32];

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					large_image[j*4*8*8 + i*8 + y*4*8 + x] = image[y*8 + x];
			}
		}
	}

	unsigned char output_data_1[16 * 16];
	unsigned char output_data_2[16 * 16];

	stbir_resize(image, 8, 8, 0, output_data_1, 16, 16, 0, STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_WRAP, STBIR_EDGE_WRAP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context);
	stbir_resize_region(large_image, 32, 32, 0, output_data_2, 16, 16, 0, STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_WRAP, STBIR_EDGE_WRAP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_SRGB, &g_context, 0.25f, 0.25f, 0.5f, 0.5f);

	{for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
			STBIR_ASSERT(output_data_1[y * 16 + x] == output_data_2[y * 16 + x]);
	}}
}

// test that 0,0,1,1 subpixel produces same result as no-rect
void test_subpixel_3()
{
	unsigned char image[8 * 8];

	mtsrand(0);

	for (int i = 0; i < sizeof(image); i++)
		image[i] = mtrand() & 255;

	unsigned char output_data_1[32 * 32];
	unsigned char output_data_2[32 * 32];

	stbir_resize_region(image, 8, 8, 0, output_data_1, 32, 32, 0, STBIR_TYPE_UINT8, 1, 0, STBIR_ALPHA_CHANNEL_NONE, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_CATMULLROM, STBIR_FILTER_CATMULLROM, STBIR_COLORSPACE_LINEAR, NULL, 0, 0, 1, 1);
	stbir_resize_uint8(image, 8, 8, 0, output_data_2, 32, 32, 0, 1);

	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
			STBIR_ASSERT(output_data_1[y * 32 + x] == output_data_2[y * 32 + x]);
	}
}

// test that 1:1 resample using s,t=0,0,1,1 with bilinear produces original image
void test_subpixel_4()
{
	unsigned char image[8 * 8];

	mtsrand(0);

	for (int i = 0; i < sizeof(image); i++)
		image[i] = mtrand() & 255;

	unsigned char output[8 * 8];

	stbir_resize_region(image, 8, 8, 0, output, 8, 8, 0, STBIR_TYPE_UINT8, 1, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_BILINEAR, STBIR_FILTER_BILINEAR, STBIR_COLORSPACE_LINEAR, &g_context, 0, 0, 1, 1);
	STBIR_ASSERT(memcmp(image, output, 8 * 8) == 0);
}

static unsigned char image88 [8][8];
static unsigned char output88[8][8];
static unsigned char output44[4][4];
static unsigned char output22[2][2];
static unsigned char output11[1][1];

void resample_88(stbir_filter filter)
{
	stbir_resize_uint8_generic(image88[0],8,8,0, output88[0],8,8,0, 1,-1,0, STBIR_EDGE_CLAMP, filter, STBIR_COLORSPACE_LINEAR, NULL);
	stbir_resize_uint8_generic(image88[0],8,8,0, output44[0],4,4,0, 1,-1,0, STBIR_EDGE_CLAMP, filter, STBIR_COLORSPACE_LINEAR, NULL);
	stbir_resize_uint8_generic(image88[0],8,8,0, output22[0],2,2,0, 1,-1,0, STBIR_EDGE_CLAMP, filter, STBIR_COLORSPACE_LINEAR, NULL);
	stbir_resize_uint8_generic(image88[0],8,8,0, output11[0],1,1,0, 1,-1,0, STBIR_EDGE_CLAMP, filter, STBIR_COLORSPACE_LINEAR, NULL);
}

void verify_box(void)
{
	int i,j,t;

	resample_88(STBIR_FILTER_BOX);

	for (i=0; i < sizeof(image88); ++i)
		STBIR_ASSERT(image88[0][i] == output88[0][i]);

	t = 0;
	for (j=0; j < 4; ++j)
		for (i=0; i < 4; ++i) {
			int n = image88[j*2+0][i*2+0]
			      + image88[j*2+0][i*2+1]
				  + image88[j*2+1][i*2+0]
				  + image88[j*2+1][i*2+1];
			STBIR_ASSERT(output44[j][i] == ((n+2)>>2));
			t += n;
		}
	STBIR_ASSERT(output11[0][0] == ((t+32)>>6));
}

void verify_filter_normalized(stbir_filter filter, unsigned char* output, int output_size)
{
	int value = 64;

	int i, j;
	for (j = 0; j < 8; ++j)
		for (i = 0; i < 8; ++i)
			image88[j][i] = value;

	stbir_resize_uint8_generic(image88[0], 8, 8, 0, output, output_size, output_size, 0, 1, -1, 0, STBIR_EDGE_CLAMP, filter, STBIR_COLORSPACE_LINEAR, NULL);

	for (j = 0; j < output_size; ++j)
		for (i = 0; i < output_size; ++i)
			STBIR_ASSERT(value == output[j*output_size + i]);
}

void test_filters(void)
{
	int i,j;

	for (i=0; i < sizeof(image88); ++i)
		image88[0][i] = mtrand() & 255;
	verify_box();

	for (i=0; i < sizeof(image88); ++i)
		image88[0][i] = 0;
	image88[4][4] = 255;
	verify_box();

	for (j=0; j < 8; ++j)
		for (i=0; i < 8; ++i)
			image88[j][i] = (j^i)&1 ? 255 : 0;
	verify_box();

	for (j=0; j < 8; ++j)
		for (i=0; i < 8; ++i)
			image88[j][i] = i&2 ? 255 : 0;
	verify_box();

	verify_filter_normalized(STBIR_FILTER_BOX, &output88[0][0], 8);
	verify_filter_normalized(STBIR_FILTER_BILINEAR, &output88[0][0], 8);
	verify_filter_normalized(STBIR_FILTER_BICUBIC, &output88[0][0], 8);
	verify_filter_normalized(STBIR_FILTER_CATMULLROM, &output88[0][0], 8);
	verify_filter_normalized(STBIR_FILTER_MITCHELL, &output88[0][0], 8);

	verify_filter_normalized(STBIR_FILTER_BOX, &output44[0][0], 4);
	verify_filter_normalized(STBIR_FILTER_BILINEAR, &output44[0][0], 4);
	verify_filter_normalized(STBIR_FILTER_BICUBIC, &output44[0][0], 4);
	verify_filter_normalized(STBIR_FILTER_CATMULLROM, &output44[0][0], 4);
	verify_filter_normalized(STBIR_FILTER_MITCHELL, &output44[0][0], 4);

	verify_filter_normalized(STBIR_FILTER_BOX, &output22[0][0], 2);
	verify_filter_normalized(STBIR_FILTER_BILINEAR, &output22[0][0], 2);
	verify_filter_normalized(STBIR_FILTER_BICUBIC, &output22[0][0], 2);
	verify_filter_normalized(STBIR_FILTER_CATMULLROM, &output22[0][0], 2);
	verify_filter_normalized(STBIR_FILTER_MITCHELL, &output22[0][0], 2);

	verify_filter_normalized(STBIR_FILTER_BOX, &output11[0][0], 1);
	verify_filter_normalized(STBIR_FILTER_BILINEAR, &output11[0][0], 1);
	verify_filter_normalized(STBIR_FILTER_BICUBIC, &output11[0][0], 1);
	verify_filter_normalized(STBIR_FILTER_CATMULLROM, &output11[0][0], 1);
	verify_filter_normalized(STBIR_FILTER_MITCHELL, &output11[0][0], 1);
}


void test_suite(int argc, char **argv)
{
	int i;
	char *barbara;

	_mkdir("test-output");

	if (argc > 1)
		barbara = argv[1];
	else
		barbara = "barbara.png";

	#if 1
	{
		float x,y;
		for (x = -1; x < 1; x += 0.05f) {
			float sums[4] = {0};
			float o;
			for (o=-5; o <= 5; ++o) {
				sums[0] += stbir__filter_mitchell(x+o);
				sums[1] += stbir__filter_catmullrom(x+o);
				sums[2] += stbir__filter_bicubic(x+o);
				sums[3] += stbir__filter_bilinear(x+o);
			}
			for (i=0; i < 4; ++i)
				STBIR_ASSERT(sums[i] >= 1.0 - 0.001 && sums[i] <= 1.0 + 0.001);
		}

		#if 1	
		for (y = 0.11f; y < 1; y += 0.01f) {
			for (x = -1; x < 1; x += 0.05f) {
				float sums[4] = {0};
				float o;
				for (o=-5; o <= 5; o += y) {
					sums[0] += y * stbir__filter_mitchell(x+o);
					sums[1] += y * stbir__filter_catmullrom(x+o);
					sums[2] += y * stbir__filter_bicubic(x+o);
					sums[3] += y * stbir__filter_bilinear(x+o);
				}
				for (i=0; i < 3; ++i)
					STBIR_ASSERT(sums[i] >= 1.0 - 0.02 && sums[i] <= 1.0 + 0.02);
			}
		}
		#endif
	}
	#endif

	#if 0 // linear_to_srgb_uchar table
	for (i=0; i < 256; ++i) {
		float f = stbir__srgb_to_linear((i+0.5f)/256.0f);
		printf("%9d, ", (int) ((f) * (1<<28)));
		if ((i & 7) == 7)
			printf("\n");
	}
	#endif

	test_filters();

	test_subpixel_1();
	test_subpixel_2();
	test_subpixel_3();
	test_subpixel_4();

	test_premul(barbara);

	for (i = 0; i < 10; i++)
		test_subpixel(barbara, 0.5f, 0.5f, (float)i / 10, 1);

	for (i = 0; i < 10; i++)
		test_subpixel(barbara, 0.5f, 0.5f, 1, (float)i / 10);

	for (i = 0; i < 10; i++)
		test_subpixel(barbara, 2, 2, (float)i / 10, 1);

	for (i = 0; i < 10; i++)
		test_subpixel(barbara, 2, 2, 1, (float)i / 10);

	// Channels test
	test_channels(barbara, 0.5f, 0.5f, 1);
	test_channels(barbara, 0.5f, 0.5f, 2);
	test_channels(barbara, 0.5f, 0.5f, 3);
	test_channels(barbara, 0.5f, 0.5f, 4);

	test_channels(barbara, 2, 2, 1);
	test_channels(barbara, 2, 2, 2);
	test_channels(barbara, 2, 2, 3);
	test_channels(barbara, 2, 2, 4);

	// filter tests
	resize_image(barbara, 2, 2, STBIR_FILTER_BOX       , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-upsample-nearest.png");
	resize_image(barbara, 2, 2, STBIR_FILTER_BILINEAR  , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-upsample-bilinear.png");
	resize_image(barbara, 2, 2, STBIR_FILTER_BICUBIC   , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-upsample-bicubic.png");
	resize_image(barbara, 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-upsample-catmullrom.png");
	resize_image(barbara, 2, 2, STBIR_FILTER_MITCHELL  , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-upsample-mitchell.png");

	resize_image(barbara, 0.5f, 0.5f, STBIR_FILTER_BOX       , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-downsample-nearest.png");
	resize_image(barbara, 0.5f, 0.5f, STBIR_FILTER_BILINEAR  , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-downsample-bilinear.png");
	resize_image(barbara, 0.5f, 0.5f, STBIR_FILTER_BICUBIC   , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-downsample-bicubic.png");
	resize_image(barbara, 0.5f, 0.5f, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-downsample-catmullrom.png");
	resize_image(barbara, 0.5f, 0.5f, STBIR_FILTER_MITCHELL  , STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, "test-output/barbara-downsample-mitchell.png");

	for (i = 10; i < 100; i++)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-width-%d.jpg", i);
		resize_image(barbara, (float)i / 100, 1, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, outname);
	}

	for (i = 110; i < 500; i += 10)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-width-%d.jpg", i);
		resize_image(barbara, (float)i / 100, 1, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, outname);
	}

	for (i = 10; i < 100; i++)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-height-%d.jpg", i);
		resize_image(barbara, 1, (float)i / 100, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, outname);
	}

	for (i = 110; i < 500; i += 10)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-height-%d.jpg", i);
		resize_image(barbara, 1, (float)i / 100, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, outname);
	}

	for (i = 50; i < 200; i += 10)
	{
		char outname[200];
		sprintf(outname, "test-output/barbara-width-height-%d.jpg", i);
		resize_image(barbara, 100 / (float)i, (float)i / 100, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_SRGB, outname);
	}

	test_format<unsigned short>(barbara, 0.5, 2.0, STBIR_TYPE_UINT16, STBIR_COLORSPACE_SRGB);
	test_format<unsigned short>(barbara, 0.5, 2.0, STBIR_TYPE_UINT16, STBIR_COLORSPACE_LINEAR);
	test_format<unsigned short>(barbara, 2.0, 0.5, STBIR_TYPE_UINT16, STBIR_COLORSPACE_SRGB);
	test_format<unsigned short>(barbara, 2.0, 0.5, STBIR_TYPE_UINT16, STBIR_COLORSPACE_LINEAR);

	test_format<unsigned int>(barbara, 0.5, 2.0, STBIR_TYPE_UINT32, STBIR_COLORSPACE_SRGB);
	test_format<unsigned int>(barbara, 0.5, 2.0, STBIR_TYPE_UINT32, STBIR_COLORSPACE_LINEAR);
	test_format<unsigned int>(barbara, 2.0, 0.5, STBIR_TYPE_UINT32, STBIR_COLORSPACE_SRGB);
	test_format<unsigned int>(barbara, 2.0, 0.5, STBIR_TYPE_UINT32, STBIR_COLORSPACE_LINEAR);

	test_float(barbara, 0.5, 2.0, STBIR_TYPE_FLOAT, STBIR_COLORSPACE_SRGB);
	test_float(barbara, 0.5, 2.0, STBIR_TYPE_FLOAT, STBIR_COLORSPACE_LINEAR);
	test_float(barbara, 2.0, 0.5, STBIR_TYPE_FLOAT, STBIR_COLORSPACE_SRGB);
	test_float(barbara, 2.0, 0.5, STBIR_TYPE_FLOAT, STBIR_COLORSPACE_LINEAR);

	// Edge behavior tests
	resize_image("hgradient.png", 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_LINEAR, "test-output/hgradient-clamp.png");
	resize_image("hgradient.png", 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_WRAP, STBIR_COLORSPACE_LINEAR, "test-output/hgradient-wrap.png");

	resize_image("vgradient.png", 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_LINEAR, "test-output/vgradient-clamp.png");
	resize_image("vgradient.png", 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_WRAP, STBIR_COLORSPACE_LINEAR, "test-output/vgradient-wrap.png");

	resize_image("1px-border.png", 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_REFLECT, STBIR_COLORSPACE_LINEAR, "test-output/1px-border-reflect.png");
	resize_image("1px-border.png", 2, 2, STBIR_FILTER_CATMULLROM, STBIR_EDGE_CLAMP, STBIR_COLORSPACE_LINEAR, "test-output/1px-border-clamp.png");

	// sRGB tests
	resize_image("gamma_colors.jpg", .5f, .5f, STBIR_FILTER_CATMULLROM, STBIR_EDGE_REFLECT, STBIR_COLORSPACE_SRGB, "test-output/gamma_colors.jpg");
	resize_image("gamma_2.2.jpg", .5f, .5f, STBIR_FILTER_CATMULLROM, STBIR_EDGE_REFLECT, STBIR_COLORSPACE_SRGB, "test-output/gamma_2.2.jpg");
	resize_image("gamma_dalai_lama_gray.jpg", .5f, .5f, STBIR_FILTER_CATMULLROM, STBIR_EDGE_REFLECT, STBIR_COLORSPACE_SRGB, "test-output/gamma_dalai_lama_gray.jpg");
}
