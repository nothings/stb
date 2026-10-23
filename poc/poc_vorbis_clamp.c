// PoC: H1 -- stb_vorbis bounds clamp sign error
//
// Demonstrates the logic bug at stb_vorbis.c:1891 where the bounds
// clamping formula uses subtraction instead of addition for c_inter.
//
// The comment says the offset is (p_inter*ch)+(c_inter), but the
// clamping computes: len*ch - (p_inter*ch - c_inter)
//                                          ^ should be +
//
// Build: gcc -o poc_vorbis_clamp poc_vorbis_clamp.c
// Run:   ./poc_vorbis_clamp

#include <stdio.h>

int main(void) {
    printf("stb_vorbis bounds clamp sign error (stb_vorbis.c:1891)\n");
    printf("======================================================\n\n");

    // simulate the variables
    int ch = 2;       // 2 channels (stereo)
    int len = 1024;   // buffer length per channel
    int p_inter = 1020; // position in interleaved buffer
    int c_inter = 1;    // current channel offset

    // the actual offset into the virtual interleaved buffer
    int actual_offset = p_inter * ch + c_inter;
    int total_space = len * ch;
    int actual_remaining = total_space - actual_offset;

    // what stb_vorbis computes (buggy)
    int buggy_remaining = len * ch - (p_inter * ch - c_inter);

    // what it should compute (correct)
    int correct_remaining = len * ch - (p_inter * ch + c_inter);

    printf("channels:          %d\n", ch);
    printf("buffer len:        %d (per channel)\n", len);
    printf("p_inter:           %d\n", p_inter);
    printf("c_inter:           %d\n\n", c_inter);

    printf("total virtual buffer:   %d\n", total_space);
    printf("current offset:         %d  (p_inter*ch + c_inter)\n", actual_offset);
    printf("actual remaining:       %d\n\n", actual_remaining);

    printf("BUGGY  effective clamp: %d  (len*ch - (p_inter*ch - c_inter))\n", buggy_remaining);
    printf("CORRECT effective clamp: %d  (len*ch - (p_inter*ch + c_inter))\n\n", correct_remaining);

    int overwrite = buggy_remaining - correct_remaining;
    printf("bug allows %d extra samples past the buffer end\n", overwrite);
    printf("(always 2 * c_inter = %d extra)\n\n", 2 * c_inter);

    // show a more extreme case
    c_inter = 5;
    ch = 6;
    p_inter = len - 2;
    actual_offset = p_inter * ch + c_inter;
    actual_remaining = len * ch - actual_offset;
    buggy_remaining = len * ch - (p_inter * ch - c_inter);
    correct_remaining = len * ch - (p_inter * ch + c_inter);
    overwrite = buggy_remaining - correct_remaining;

    printf("worse case: ch=%d, c_inter=%d, p_inter=%d\n", ch, c_inter, p_inter);
    printf("  actual remaining:  %d\n", actual_remaining);
    printf("  buggy clamp:       %d\n", buggy_remaining);
    printf("  correct clamp:     %d\n", correct_remaining);
    printf("  overwrite by:      %d samples\n", overwrite);

    return 0;
}
