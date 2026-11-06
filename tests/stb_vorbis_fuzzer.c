/* Fuzzer for stb_vorbis.c (OSS-Fuzz coverage-pipeline pair stb-vorbis-fuzzer).
 *
 * Threat model:
 *   - Untrusted input: the whole fuzz buffer, interpreted as an Ogg Vorbis
 *     stream, exactly like a .ogg file downloaded from the internet and fed
 *     to stb_vorbis_open_memory() by an application.
 *   - Trust boundary: stb_vorbis_open_memory() header parsing (identification,
 *     comment, setup) and the frame decode / seek paths.
 *   - Attacker controls: every byte of the stream, plus (via the 8-byte
 *     harness control prefix) whether a seek is performed and to which
 *     sample offset.
 *   - Expected bug classes: OOB reads/writes in codebook, window, IMDCT and
 *     seek-table handling; integer overflows in offsets; hangs on
 *     pathological streams (bounded here by frame-batch limits).
 *
 * Layout: bytes [0,8) are harness control (op flag + seek target); the rest
 * is the untrusted Ogg stream handed to stb_vorbis.c.
 */

#include <stdint.h>
#include <stdlib.h>

#include "../stb_vorbis.c"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_FRAME_BATCH 16
#define MAX_STREAM_LEN  0x0fffffffu /* keep len inside int for open_memory */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 8) return 0;

    unsigned int op     = data[0];
    unsigned int target = (unsigned int) data[1]
                        | ((unsigned int) data[2] <<  8)
                        | ((unsigned int) data[3] << 16)
                        | ((unsigned int) data[4] << 24);

    size_t stream_len = size - 8;
    if (stream_len == 0 || stream_len > MAX_STREAM_LEN) return 0;

    int error;
    stb_vorbis *v = stb_vorbis_open_memory(data + 8, (int) stream_len, &error, NULL);
    if (v == NULL) return 0;

    stb_vorbis_info info = stb_vorbis_get_info(v);
    float **outputs = NULL;
    int n, i;

    /* Decode a bounded number of frames. */
    for (i = 0; i < MAX_FRAME_BATCH; i++) {
        n = stb_vorbis_get_frame_float(v, &info.channels, &outputs);
        if (n == 0) break;
    }

    /* Optionally exercise the seek path, then decode again. */
    if ((op & 1u) != 0) {
        unsigned int len = stb_vorbis_stream_length_in_samples(v);
        if (len > 0 && stb_vorbis_seek(v, target % len)) {
            for (i = 0; i < MAX_FRAME_BATCH; i++) {
                n = stb_vorbis_get_frame_float(v, &info.channels, &outputs);
                if (n == 0) break;
            }
        }
    }

    stb_vorbis_close(v);
    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
