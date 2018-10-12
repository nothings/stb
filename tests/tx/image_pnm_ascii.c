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

	{
int width, height, channels;
unsigned char *image = stbi_load("images/feep.pgm",
                                 &width,
                                 &height,
                                 &channels,
                                 0);

	if(width != 24 || height != 7 || channels != 1)
		printf("not ");
	printf("ok 1 - read grayscale image header\n");

	if(!(image && 0 == memcmp(image, feepP58bit, sizeof(feepP58bit))))
		printf("not ");
	printf("ok 2 - read grayscale image data\n");

stbi_image_free(image);
	}

	{
int width, height, channels;
unsigned char *image = stbi_load("images/feep.ppm",
                                 &width,
                                 &height,
                                 &channels,
                                 0);

	if(width != 4 || height != 4 || channels != 3)
		printf("not ");
	printf("ok 3 - read RGB image header\n");

	if(!(image && 0 == memcmp(image, feepP68bit, sizeof(feepP68bit))))
		printf("not ");
	printf("ok 4 - read RGB image data\n");

stbi_image_free(image);
	}
}
