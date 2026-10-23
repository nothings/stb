// PoC: M2 -- stbi__vertical_flip_slices unchecked overflow
//
// slice_size = w * h * bytes_per_pixel with no overflow check.
// Used as a pointer increment: bytes += slice_size.
// If it overflows, pointer arithmetic wraps, causing OOB access
// during vertical flipping.
//
// Build: gcc -O0 -g -o poc_vertical_flip poc_vertical_flip.c -lm
// Run:   ./poc_vertical_flip

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(void) {
    printf("stbi__vertical_flip_slices overflow (stb_image.h:1250)\n");
    printf("======================================================\n\n");

    // the function computes:
    //   int slice_size = w * h * bytes_per_pixel;
    //   bytes += slice_size;  // per-slice pointer advance

    struct { int w; int h; int bpp; } cases[] = {
        {32768, 32768, 4},   // animated GIF RGBA
        {16384, 16384, 4},   // smaller but still overflows
        {65536, 65536, 1},   // single channel
    };

    for (int i = 0; i < 3; i++) {
        int w = cases[i].w, h = cases[i].h, bpp = cases[i].bpp;
        int slice_size = w * h * bpp;
        int64_t actual = (int64_t)w * h * bpp;

        printf("w=%d h=%d bpp=%d\n", w, h, bpp);
        printf("  actual slice size: %lld bytes\n", (long long)actual);
        printf("  int overflow:      %d\n", slice_size);
        if ((int64_t)slice_size != actual)
            printf("  OVERFLOW: pointer advances by %d instead of %lld\n\n",
                   slice_size, (long long)actual);
        else
            printf("  (no overflow)\n\n");
    }

    printf("when stbi_set_flip_vertically_on_load(1) is called and an\n");
    printf("animated GIF with large frames is loaded, the flip function\n");
    printf("uses the overflowed slice_size for pointer arithmetic.\n");

    return 0;
}
