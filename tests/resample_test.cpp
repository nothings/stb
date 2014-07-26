#ifdef _WIN32
#define STBR_ASSERT(x) \
	if (!(x)) \
		__debugbreak();
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

int main(int argc, char** argv)
{
	unsigned char* input_data;
	unsigned char* output_data;
	int w, h;
	int n;
	int out_w, out_h, out_stride;

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

	out_w = 256;
	out_h = 256;
	out_stride = (out_w + 10) * n;

	output_data = (unsigned char*)malloc(out_stride * out_h);

	int in_w = 512;
	int in_h = 512;

	size_t memory_required = stbr_calculate_memory(in_w, in_h, w*n, out_w, out_h, out_stride, n, STBR_FILTER_BICUBIC);
	void* extra_memory = malloc(memory_required);

	// Cut out the outside 64 pixels all around to test the stride.
	int border = 64;
	STBR_ASSERT(in_w + border <= w);
	STBR_ASSERT(in_h + border <= h);

	stbr_resize_arbitrary(input_data + w * border * n + border * n, in_w, in_h, w*n, output_data, out_w, out_h, out_stride, n, STBR_TYPE_UINT8, STBR_FILTER_BICUBIC, STBR_EDGE_CLAMP, extra_memory, memory_required);

	free(extra_memory);

	stbi_write_png("output.png", out_w, out_h, n, output_data, out_stride);

	free(output_data);

	return 0;
}
