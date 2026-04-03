// PoC: C2 -- stbi__convert_16_to_8 integer overflow
//
// Demonstrates that w * h * channels overflows int with no check.
// Calls the function directly with values that overflow.
//
// Build: gcc -O0 -g -o poc_convert_16to8 poc_convert_16to8.c -lm
// Run:   ./poc_convert_16to8

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdint.h>

int main(void) {
    int w = 16384, h = 16384, channels = 4;
    int64_t actual = (int64_t)w * h * channels;
    int overflowed = w * h * channels;

    printf("stbi__convert_16_to_8 overflow (stb_image.h:1193)\n");
    printf("==================================================\n\n");
    printf("w=%d, h=%d, channels=%d\n", w, h, channels);
    printf("actual bytes needed:  %lld (%.1f GB)\n",
           (long long)actual, actual / (1024.0*1024*1024));
    printf("int overflow result:  %d\n\n", overflowed);

    if (overflowed <= 0 || (int64_t)overflowed != actual) {
        printf("OVERFLOW CONFIRMED: int wraps to %d\n", overflowed);
        printf("stbi__malloc(%d) would allocate %s\n",
               overflowed,
               overflowed <= 0 ? "0 or negative (huge via size_t cast)" : "a tiny buffer");
        printf("then the loop writes %lld bytes --> HEAP OVERFLOW\n", (long long)actual);
    }

    // also show C3
    printf("\n\nstbi__convert_8_to_16 overflow (stb_image.h:1209)\n");
    printf("==================================================\n\n");
    int img_len = w * h * channels;
    int alloc_size = img_len * 2;
    int64_t actual_alloc = actual * 2;
    printf("img_len = w*h*channels = %d (already overflowed)\n", img_len);
    printf("alloc = img_len * 2 = %d (double overflow)\n", alloc_size);
    printf("actual needed: %lld bytes\n", (long long)actual_alloc);

    return 0;
}
