/* Round-trip fuzzer for stb_image_write.h + stb_image.h
 * (OSS-Fuzz coverage-pipeline pair stb-image-write-roundtrip-fuzzer).
 *
 * Threat model:
 *   - Untrusted input: an image blob (any format stb_image sniffs) plus a
 *     few harness-control bytes selecting the writer and its parameters —
 *     matching an app that loads an untrusted image, re-encodes it, and
 *     hands the result back to a decoder.
 *   - Trust boundary: the stb_image_write encoders (png/jpg/bmp/tga/hdr
 *     serialisers) — the encode direction is entirely absent from the
 *     existing OSS-Fuzz coverage — and the decode-back path.
 *   - Attacker controls: image bytes (dimensions, channel counts, content)
 *     and encoder/quality selection.
 *   - Expected bug classes: OOB reads/writes in encoders, buffer math
 *     overflows, hangs on pathological dimensions (bounded), plus the
 *     documented property violation below.
 *
 * Property: if encoding a successfully decoded image reports success, the
 * produced bytes must decode again with stbi_load_from_memory. A violation
 * aborts — that abort is a genuine encoder/decoder finding, not harness
 * noise, because the inputs were already accepted by stb_image itself.
 * (This version of stb_image_write.h ships png/jpg/bmp/tga/hdr writers.)
 */

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DECODED_BYTES (32L << 20) /* bound decoded w*h*4 */
#define MAX_DIMENSION 65535           /* header field limits of jpg/tga */

typedef struct {
    unsigned char *buf;
    size_t len;
    size_t cap;
    int failed;
} wbuf;

static void wfun(void *context, void *data, int n)
{
    wbuf *c = (wbuf *) context;
    if (c->failed || n <= 0) return;
    if (c->len + (size_t) n > c->cap) {
        size_t ncap = c->cap ? c->cap : 4096;
        while (ncap < c->len + (size_t) n) ncap *= 2;
        unsigned char *nb = (unsigned char *) realloc(c->buf, ncap);
        if (nb == NULL) {
            c->failed = 1;
            return;
        }
        c->buf = nb;
        c->cap = ncap;
    }
    memcpy(c->buf + c->len, data, (size_t) n);
    c->len += (size_t) n;
}

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 8) return 0;

    int x, y, channels;
    if (!stbi_info_from_memory(data, size, &x, &y, &channels)) return 0;
    if (y && x > (int) ((MAX_DECODED_BYTES / 4) / (unsigned) y)) return 0;

    unsigned writer = data[0] & 7u;
    int quality = 1 + (int) (data[1] & 31u) * 3; /* 1..94 for jpg */
    int comp = 1 + (int) (data[2] & 3u);         /* 1..4 */

    unsigned char *img = stbi_load_from_memory(data, size, &x, &y, &channels, comp);
    if (img == NULL) return 0;

    /* jpg/tga headers carry 16-bit dimensions: skip encoders that cannot
       represent the decoded size, otherwise a wrap would be harness noise. */
    int dims_fitable = (x <= MAX_DIMENSION && y <= MAX_DIMENSION);

    wbuf wb;
    memset(&wb, 0, sizeof(wb));
    int ok = 0;
    switch (writer) {
        case 0: ok = stbi_write_png_to_func(wfun, &wb, x, y, comp, img, x * comp); break;
        case 1: if (dims_fitable) ok = stbi_write_jpg_to_func(wfun, &wb, x, y, comp, img, quality); break;
        case 2: ok = stbi_write_bmp_to_func(wfun, &wb, x, y, comp, img); break;
        case 3: if (dims_fitable) ok = stbi_write_tga_to_func(wfun, &wb, x, y, comp, img); break;
        case 4: {
            float *fimg = (float *) malloc((size_t) x * y * comp * sizeof(float));
            if (fimg != NULL) {
                size_t i, n = (size_t) x * y * comp;
                for (i = 0; i < n; i++) fimg[i] = (float) img[i];
                ok = stbi_write_hdr_to_func(wfun, &wb, x, y, comp, fimg);
                free(fimg);
            }
            break;
        }
        default: break; /* writer selectors without a writer in this version */
    }

    if (!ok || wb.failed) {
        free(wb.buf);
        free(img);
        return 0;
    }

    /* Property: encoder-reported-success output must decode again. */
    int x2, y2, c2;
    unsigned char *back = stbi_load_from_memory(wb.buf, (int) wb.len, &x2, &y2, &c2, 0);
    if (back == NULL) {
        fprintf(stderr, "stb_image_write round-trip violation: writer %u on %dx%d comp %d produced %zu bytes that fail to decode\n",
                writer, x, y, comp, wb.len);
        abort();
    }
    free(back);
    free(wb.buf);
    free(img);
    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
