#ifdef _WIN32
#define STBR_ASSERT(x) \
	if (!(x)) \
		__debugbreak();
#endif

#define STB_RESAMPLE_IMPLEMENTATION
#include "stb_resample.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv)
{
	unsigned char* input_data;
	unsigned char* output_data;
	int w, h;
	int n;
	int out_w, out_h;

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

	output_data = malloc(out_w * out_h * n);

	stbr_resize(input_data, w, h, n, STBR_FILTER_NEAREST, output_data, out_w, out_h);

	stbi_write_png("output.png", out_w, out_h, n, output_data, out_w * n);

	free(output_data);

	return 0;
}
