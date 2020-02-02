#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    int x, y, channels;

    if(!stbi_info_from_memory(data, size, &x, &y, &channels)) return 0;

    /* exit if the image is larger than ~80MB */
    if(y && x > (80000000 / 4) / y) return 0;

    unsigned char *img = stbi_load_from_memory(data, size, &x, &y, &channels, 4);

    free(img);

    return 0;
}
