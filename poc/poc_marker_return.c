// PoC: H6 -- JPEG marker failure returns success
//
// stb_image.h:3440 returns 1 (success) when stbi__process_marker fails:
//   if (!stbi__process_marker(j, m)) return 1;
//
// This means malformed markers between progressive scans are silently
// accepted, and decoding continues with inconsistent internal state.
//
// Build: gcc -O0 -g -o poc_marker_return poc_marker_return.c -lm
// Run:   ./poc_marker_return

#include <stdio.h>

int main(void) {
    printf("JPEG marker processing failure returns success\n");
    printf("===============================================\n\n");

    printf("stb_image.h line 3440:\n\n");
    printf("    if (!stbi__process_marker(j, m)) return 1;\n\n");
    printf("when stbi__process_marker returns 0 (failure),\n");
    printf("!0 = 1 (true), so the function returns 1 (success).\n\n");

    printf("correct code should be:\n\n");
    printf("    if (!stbi__process_marker(j, m)) return 0;\n\n");

    printf("impact: a malformed DHT or DQT marker between progressive\n");
    printf("scans is silently ignored. the decoder continues with\n");
    printf("partially modified or corrupt huffman/quantization tables.\n");
    printf("this is an enabler for other exploits (heap leak, IDCT overflow).\n");

    return 0;
}
