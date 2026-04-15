// PoC: H8 -- PNG IDAT idata_limit doubling overflow
//
// The IDAT accumulation loop doubles idata_limit until it fits:
//   while (ioff + c.length > idata_limit) idata_limit *= 2;
//
// If idata_limit overflows uint32, it wraps to 0 or a small value.
// STBI_REALLOC_SIZED gets a tiny size, then stbi__getn writes
// a large chunk into it.
//
// Build: gcc -O0 -g -o poc_png_idat_overflow poc_png_idat_overflow.c -lm
// Run:   ./poc_png_idat_overflow

#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("PNG IDAT idata_limit doubling overflow (stb_image.h:5188-5191)\n");
    printf("==============================================================\n\n");

    // simulate the doubling loop
    uint32_t idata_limit = 1024 * 1024; // 1MB initial
    uint32_t chunk_size = 1u << 30;     // 1GB per IDAT (max allowed)

    printf("scenario: multiple IDAT chunks of %u bytes each\n\n", chunk_size);

    uint32_t ioff = 0;
    int chunk_num = 0;
    while (1) {
        chunk_num++;
        uint32_t old_limit = idata_limit;

        // simulate the doubling
        int doublings = 0;
        while (ioff + chunk_size > idata_limit) {
            uint32_t prev = idata_limit;
            idata_limit *= 2;
            doublings++;
            if (idata_limit < prev) {
                printf("chunk %d: idata_limit OVERFLOWED at doubling %d\n", chunk_num, doublings);
                printf("  ioff = 0x%08x (%u)\n", ioff, ioff);
                printf("  chunk_size = 0x%08x\n", chunk_size);
                printf("  idata_limit went from 0x%08x to 0x%08x\n", prev, idata_limit);
                printf("  STBI_REALLOC_SIZED would allocate %u bytes\n", idata_limit);
                printf("  then stbi__getn writes %u bytes into it\n\n", chunk_size);
                printf("result: heap buffer overflow or infinite loop\n");
                return 0;
            }
        }

        ioff += chunk_size;

        if (ioff < chunk_size) {
            printf("chunk %d: ioff itself overflowed to %u\n", chunk_num, ioff);
            break;
        }

        printf("chunk %d: ioff=0x%08x, idata_limit=0x%08x (doubled %d times)\n",
               chunk_num, ioff, idata_limit, doublings);

        if (chunk_num > 10) {
            printf("(stopping simulation)\n");
            break;
        }
    }

    return 0;
}
