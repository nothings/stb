// PoC: C4 -- GIF animated loader layers*stride integer overflow
//
// Generates an animated GIF with enough frames to overflow layers*stride.
// With 1x1 pixels (stride=4), overflow happens at ~537 million frames,
// which is impractical. With 256x256 (stride=262144), it happens at ~8192.
// This PoC uses a small frame size and demonstrates the math.
//
// Build: gcc -O0 -g -o poc_gif_layers_overflow poc_gif_layers_overflow.c -lm
// Run:   ./poc_gif_layers_overflow

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(void) {
    printf("GIF animated loader layers*stride overflow (stb_image.h:6991-7021)\n");
    printf("==================================================================\n\n");

    struct { int w; int h; } sizes[] = {
        {1, 1}, {10, 10}, {100, 100}, {256, 256}, {400, 400}, {1024, 1024}
    };
    int n = sizeof(sizes) / sizeof(sizes[0]);

    printf("%-12s %-12s %-18s %-12s\n", "Dimensions", "Stride", "Frames to overflow", "GIF size ~");

    for (int i = 0; i < n; i++) {
        int w = sizes[i].w, h = sizes[i].h;
        int stride = w * h * 4;
        int64_t frames_needed = (int64_t)INT_MAX / stride + 1;
        int64_t gif_size = frames_needed * 20; // rough estimate per frame

        printf("%4dx%-4d    %-12d %-18lld ~%.0f MB\n",
               w, h, stride, (long long)frames_needed,
               gif_size / (1024.0 * 1024));
    }

    printf("\nthe 400x400 case is practical: ~3356 frames in a ~65 KB GIF\n");
    printf("after overflow, layers*stride wraps small, realloc shrinks,\n");
    printf("then memcpy at line 7021 writes stride bytes past the end.\n");

    // show exact overflow point for 400x400
    int w = 400, h = 400;
    int stride = w * h * 4;
    int layers = INT_MAX / stride;
    printf("\nwith stride=%d:\n", stride);
    printf("  layers=%d: layers*stride = %lld (fits in int)\n",
           layers, (long long)layers * stride);
    printf("  layers=%d: layers*stride = %lld (overflows int to %d)\n",
           layers + 1, (long long)(layers + 1) * stride,
           (int)((long long)(layers + 1) * stride));

    return 0;
}
