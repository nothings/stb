#ifdef __cplusplus
extern "C" {
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    int x, y, comp, z;
    int *delays = NULL; 

    if (size > INT_MAX) {
        return 0; 
    }

    stbi_uc *image = stbi_load_gif_from_memory(data, (int)size, &delays, &x, &y, &z, &comp, 0);

    if (image) {
        stbi_image_free(image);
        if (delays) {
            STBI_FREE(delays); 
        }
    }

    return 0;
}

#ifdef __cplusplus
}
#endif
