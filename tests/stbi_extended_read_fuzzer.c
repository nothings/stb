#ifdef __cplusplus
extern "C" {
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    int x, y, comp;

    stbi__uint16 *result_16 = stbi_load_16_from_memory(data, size, &x, &y, &comp, 0);
    if (result_16) {
        free(result_16);
    }

    float *result_f = stbi_loadf_from_memory(data, size, &x, &y, &comp, 0);
    if (result_f) {
        free(result_f);
    }

    int is_16_bit = stbi_is_16_bit_from_memory(data, size);

    stbi_info_from_memory(data, size, &x, &y, &comp);

    return 0;
}

#ifdef __cplusplus
}
#endif
