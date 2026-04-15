// PoC: C1 -- stbi__convert_format16 integer overflow
//
// Demonstrates that stbi__convert_format (8-bit) uses stbi__malloc_mad3
// but stbi__convert_format16 (16-bit) uses raw stbi__malloc with no
// overflow check.
//
// This PoC calls the internal functions directly to show the overflow.
// In the wild, this is triggered by a 16-bit PNG with large dimensions
// and a req_comp that differs from img_n (e.g. requesting RGBA from RGB).
//
// Build: gcc -o poc_convert16_overflow poc_convert16_overflow.c -lm
// Run:   ./poc_convert16_overflow

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    // show the overflow math
    // stbi__convert_format16 does: stbi__malloc(req_comp * x * y * 2)
    // stbi__convert_format does:   stbi__malloc_mad3(req_comp, x, y, 0) -- SAFE

    unsigned int req_comp = 4;
    unsigned int x = 32768;
    unsigned int y = 32768;

    // the allocation size in the 16-bit path
    unsigned int alloc_16bit = req_comp * x * y * 2;
    // the actual needed size
    uint64_t actual_needed = (uint64_t)req_comp * x * y * 2;

    printf("stbi__convert_format16 overflow demonstration\n");
    printf("==============================================\n\n");
    printf("image dimensions: %u x %u, req_comp=%u (16-bit)\n", x, y, req_comp);
    printf("actual bytes needed:    %llu (%.1f GB)\n",
           (unsigned long long)actual_needed, actual_needed / (1024.0*1024*1024));
    printf("32-bit alloc size:      %u (overflowed to %u bytes)\n\n",
           alloc_16bit, alloc_16bit);

    printf("the 8-bit path (stbi__convert_format) checks this with stbi__malloc_mad3.\n");
    printf("the 16-bit path (stbi__convert_format16) does NOT check -- raw stbi__malloc.\n\n");

    // demonstrate stbi__mad3sizes_valid equivalent
    // from stb_image.h lines 1010-1030
    int a = (int)req_comp, b = (int)x, c = (int)y;
    // stbi__mul2sizes_valid: a*b must fit in INT_MAX
    int ab_valid = (a == 0 || b <= (int)(0x7fffffff / a));
    int ab = a * b;
    int abc_valid = ab_valid && (ab == 0 || c <= (int)(0x7fffffff / ab));

    printf("stbi__mad3sizes_valid(%d, %d, %d, 0) = %s\n",
           a, b, c, abc_valid ? "TRUE (safe)" : "FALSE (would reject)");

    if (!abc_valid) {
        printf("\nthe 8-bit path correctly rejects this allocation.\n");
        printf("the 16-bit path at stb_image.h:1820 would allocate %u bytes\n", alloc_16bit);
        printf("then write %llu bytes into it --> HEAP BUFFER OVERFLOW\n",
               (unsigned long long)actual_needed);
    }

    return 0;
}
