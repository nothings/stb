#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <strings.h>
#include <limits.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../images/feepP58bit.h"
#include "../images/feepP68bit.h"

int main() {
	printf("1..4\n");

	int maxv = 15;
	{
int width, height, channels;
unsigned char *image = stbi_load("images/feepP5.pgm",
                                 &width,
                                 &height,
                                 &channels,
                                 0);

	if(width != 24 || height != 7 || channels != 1)
		printf("not ");
	printf("ok 1 - read grayscale image header\n");

	for(size_t i = 0; i < sizeof(feepP58bit); i++)
		image[i] = floor(image[i] * (255.0f/maxv) + 0.5f);

	if(!(image && 0 == memcmp(image, feepP58bit, sizeof(feepP58bit))))
		printf("not ");
	printf("ok 2 - read grayscale image data\n");

stbi_image_free(image);
	}

	{
int width, height, channels;
unsigned char *image = stbi_load("images/feepP6.ppm",
                                 &width,
                                 &height,
                                 &channels,
                                 0);

	if(width != 4 || height != 4 || channels != 3)
		printf("not ");
	printf("ok 3 - read RGB image header\n");

	for(size_t i = 0; i < sizeof(feepP68bit); i++)
		image[i] = floor(image[i] * (255.0f/maxv) + 0.5f);

	if(!(image && 0 == memcmp(image, feepP68bit, sizeof(feepP68bit))))
		printf("not ");
	printf("ok 4 - read RGB image data\n");

stbi_image_free(image);
	}
}
