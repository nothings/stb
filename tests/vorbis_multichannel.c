// Synthetic Vorbis only: no game files, encoder, or audio device required.
// Exercise type-2 residues beyond the stereo bound and decode with a caller-owned arena.
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_VORBIS_NO_STDIO
#define STB_VORBIS_NO_INTEGER_CONVERSION
#include "../stb_vorbis.c"

typedef struct { unsigned char data[8192]; int bits; } packet;
typedef struct { unsigned char data[32768]; int size, seq; } stream;
static void bits(packet *p, unsigned value, int n) {
    assert(p->bits + n <= (int)sizeof(p->data) * 8);
    for (int i = 0; i < n; i++, p->bits++)
        p->data[p->bits / 8] |= ((value >> i) & 1) << (p->bits % 8);
}
static packet header(int type) {
    packet p = {0}; bits(&p, type, 8);
    for (int i = 0; i < 6; i++) bits(&p, "vorbis"[i], 8);
    return p;
}
static void page(stream *s, packet *p, int flags, unsigned granule) {
    int len = (p->bits + 7) / 8, segments = len / 255 + 1;
    int start = s->size, size = 27 + segments + len;
    assert(start + size <= (int)sizeof(s->data));
    unsigned char *d = s->data + start;
    memcpy(d, "OggS", 4); d[5] = flags;
    for (int i = 0; i < 4; i++) { d[6+i] = granule >> (8*i); d[18+i] = s->seq >> (8*i); }
    d[14] = 1; d[26] = segments;
    for (int i = 0; i < segments; i++) d[27+i] = i+1 == segments ? len % 255 : 255;
    memcpy(d + 27 + segments, p->data, len);
    unsigned crc = 0;
    for (int i = 0; i < size; i++) crc = crc32_update(crc, d[i]);
    for (int i = 0; i < 4; i++) d[22+i] = crc >> (8*i);
    s->size += size; s->seq++;
}
static void codebook(packet *p, int lookup) {
    bits(p, 0x564342, 24); bits(p, 1, 16); bits(p, 1, 24); // one dimension, one entry
    bits(p, 0, 1); bits(p, 0, 1); bits(p, 0, 5);         // unordered, dense, one-bit code
    bits(p, lookup, 4);
    if (lookup) {
        bits(p, (788u << 21) | 1, 32); bits(p, 0, 32);   // minimum 1.0, delta 0.0
        bits(p, 0, 4); bits(p, 0, 1); bits(p, 0, 1);   // one-bit multiplicand, no sequence
    }
}
static stream fixture(int channels, int type, int split, int blocksize) {
    int exponent = 0; while ((1 << exponent) < blocksize) exponent++;
    stream s = {0}; packet p = header(1);
    bits(&p, 0, 32); bits(&p, channels, 8); bits(&p, 48000, 32);
    for (int i = 0; i < 3; i++) bits(&p, 0, 32);
    bits(&p, exponent | (exponent << 4), 8); bits(&p, 1, 8); // equal short/long blocks, framing flag
    page(&s, &p, 2, 0);
    p = header(3); bits(&p, 0, 32); bits(&p, 0, 32); bits(&p, 1, 8); page(&s, &p, 0, 0);
    p = header(5); bits(&p, 1, 8); codebook(&p, 0); codebook(&p, 1);
    bits(&p, 0, 6); bits(&p, 0, 16);                     // one time configuration
    bits(&p, 0, 6); bits(&p, 1, 16); bits(&p, 0, 5);    // one floor 1, no partitions
    bits(&p, 0, 2); bits(&p, 5, 4);                    // multiplier 1, range 32
    bits(&p, split ? 1 : 0, 6);
    for (int i = 0; i < 1 + split; i++) {
        int ch = split ? (i ? 1 : channels-1) : channels;
        bits(&p, type, 16); bits(&p, 0, 24);
        bits(&p, (blocksize / 2) * (type == 2 ? ch : 1), 24);        // complete interleaved vector
        bits(&p, 31, 24); bits(&p, 0, 6); bits(&p, 0, 8); // partition size 32, classbook 0
        bits(&p, 1, 3); bits(&p, 0, 1); bits(&p, 1, 8); // pass 0 uses vector codebook 1
    }
    bits(&p, 0, 6); bits(&p, 0, 16); bits(&p, split, 1);
    if (split) bits(&p, 1, 4);
    bits(&p, 0, 1); bits(&p, 0, 2);                    // no coupling, reserved bits
    if (split) for (int i = 0; i < channels; i++) bits(&p, i == channels-1, 4);
    for (int i = 0; i < 1 + split; i++) { bits(&p, 0, 8); bits(&p, 0, 8); bits(&p, i, 8); }
    bits(&p, 0, 6); bits(&p, 0, 1); bits(&p, 0, 16); bits(&p, 0, 16); bits(&p, 0, 8);
    bits(&p, 1, 1); page(&s, &p, 0, 0);
    for (int frame = 0; frame < 4; frame++) {
        p = (packet){0}; bits(&p, 0, 1);
        for (int i = 0; i < channels; i++) { bits(&p, 1, 1); bits(&p, 255, 8); bits(&p, 255, 8); }
        // Each 32-bin partition consumes one scalar code and 32 vector codes, all zero.
        for (int i = 0; i < channels * (blocksize / 64); i++) { bits(&p, 0, 1); bits(&p, 0, 32); }
        page(&s, &p, frame == 3 ? 4 : 0, frame * (blocksize / 2));
    }
    return s;
}
static int decode(stream *s, int push, const stb_vorbis_alloc *arena, float *output) {
    int error = 0, used = 0, offset = 0, total = 0;
    stb_vorbis *f = push ? stb_vorbis_open_pushdata(s->data, s->size, &used, &error, arena)
                        : stb_vorbis_open_memory(s->data, s->size, &error, arena);
    assert(f && error == 0); offset = used;
    for (;;) {
        float **pcm = NULL; int frames = 0;
        if (push) {
            if (offset == s->size) break;
            used = stb_vorbis_decode_frame_pushdata(f, s->data + offset, s->size - offset, NULL, &pcm, &frames);
            assert(used || frames); offset += used;
        } else frames = stb_vorbis_get_frame_float(f, NULL, &pcm);
        if (!push && !frames) break;
        assert(total + frames <= 3 * f->blocksize_1 / 2);
        for (int i = 0; i < frames; i++) for (int c = 0; c < f->channels; c++) {
            float v = pcm[c][i]; assert(isfinite(v)); output[(total+i)*f->channels+c] = v;
        }
        total += frames;
    }
    assert(stb_vorbis_get_error(f) == 0); stb_vorbis_close(f); return total;
}
static void residue_input(stb_vorbis *f, unsigned char *data, int size) {
    f->stream = data; f->stream_end = data + size;
    f->bytes_in_seg = 0; f->last_seg = FALSE;
    f->next_seg = 0; f->segment_count = size / 255 + 1;
    for (int i = 0; i < f->segment_count; i++) f->segments[i] = i+1 == f->segment_count ? size % 255 : 255;
    f->valid_bits = 0; f->acc = 0;
}
static void check(int channels, int type, int split, int blocksize) {
    int spectrum = blocksize / 2;
    stream s = fixture(channels, type, split, blocksize); int error = 0;
    stb_vorbis *f = stb_vorbis_open_memory(s.data, s.size, &error, NULL); assert(f);
    stb_vorbis_info info = stb_vorbis_get_info(f);
    if (!split) {
        // Feed zero codes through the actual residue decoder: every coefficient must be one.
        unsigned char zeros[8192] = {0}, skip[8] = {0}; float values[8][4096], *planes[8];
        for (int c = 0; c < channels; c++) planes[c] = values[c];
        residue_input(f, zeros, sizeof zeros);
        decode_residue(f, planes, channels, spectrum, 0, skip);
        for (int c = 0; c < channels; c++) for (int i = 0; i < spectrum; i++) {
            if (values[c][i] != 1.0f) fprintf(stderr, "type %d, %d channels: coefficient [%d][%d] = %g, expected 1\n", type, channels, c, i, values[c][i]);
            assert(values[c][i] == 1.0f);
        }
        if (type == 2 && channels > 2) {
            // Muted planes stay in the type-2 interleave; only their output is skipped.
            memset(values, 0, sizeof values);
            memset(skip, 0, sizeof skip); skip[1] = 1; planes[1] = NULL;
            residue_input(f, zeros, sizeof zeros);
            decode_residue(f, planes, channels, spectrum, 0, skip);
            for (int c = 0; c < channels; c++) if (!skip[c])
                for (int i = 0; i < spectrum; i++) assert(values[c][i] == 1.0f);
            // An entirely skipped bundle must consume no residue codes.
            memset(skip, 1, sizeof skip);
            residue_input(f, zeros, sizeof zeros);
            decode_residue(f, planes, channels, spectrum, 0, skip); assert(f->stream == zeros);
        }
    }
    stb_vorbis_close(f);
    unsigned temp = info.temp_memory_required > info.setup_temp_memory_required ? info.temp_memory_required : info.setup_temp_memory_required;
    unsigned bytes = info.setup_memory_required + temp;
    // Use exactly the advertised requirement, rather than hiding an underestimate with a large arena.
    char *memory = malloc(bytes); assert(memory);
    stb_vorbis_alloc arena = { memory, (int)bytes };
    float *reference = malloc(3 * spectrum * channels * sizeof(float));
    float *actual = malloc(3 * spectrum * channels * sizeof(float));
    assert(reference && actual);
    int n = decode(&s, 0, NULL, reference); assert(n == 3 * spectrum);
    for (int push = 0; push <= 1; push++) for (int fixed = 0; fixed <= 1; fixed++) {
        int got = decode(&s, push, fixed ? &arena : NULL, actual); assert(got == n);
        double energy = 0;
        for (int i = 0; i < n*channels; i++) { assert(actual[i] == reference[i]); energy += actual[i]*actual[i]; }
        assert(energy > 0);
    }
    free(memory); free(reference); free(actual);
    printf("type %d, %d channels, %d submap(s), block %d: heap/arena pull/push passed\n", type, channels, 1+split, blocksize); fflush(stdout);
}
int main(void) {
    crc32_init();
    for (int type = 0; type <= 2; type++) { check(1, type, 0, 64); check(2, type, 0, 64); }
    for (int blocksize = 64; blocksize <= 8192; blocksize *= 4) {
        check(3, 2, 0, blocksize); check(6, 2, 0, blocksize);
        check(8, 2, 0, blocksize); check(6, 2, 1, blocksize);
    }
    check(6, 2, 0, 8192); check(6, 2, 1, 8192);
    return 0;
}
