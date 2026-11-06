/* Fuzzer for the stb_image.h float-image API family
 * (OSS-Fuzz coverage-pipeline pair stb-image-float-api-fuzzer).
 *
 * Threat model:
 *   - Untrusted input: an image blob in any format stb_image sniffs, as when
 *     an application loads untrusted HDR/Radiance, Softimage PIC, PSD or PNM
 *     files through the stbi_loadf float API.
 *   - Trust boundary: stbi_info_from_memory format sniffing, the integer
 *     decode path, and the stbi_loadf float path (stbi__loadf_main ->
 *     hdr/psd/pic/pnm float decoders and the float conversion wrappers).
 *   - Attacker controls: every byte of the file.
 *   - Expected bug classes: OOB reads in RLE decode (hdr), exponent/float
 *     conversion overflows, OOB in planar channel handling (psd/pic),
 *     integer overflow in dimension math, hangs (bounded here).
 *
 * This is the only stb_image harness family that reaches the float API:
 * the two production fuzzers call stbi_load/stbi_info only, leaving the
 * stbi_loadf family statically reachable but dynamically unreached
 * (introspector: ~2.6k accumulated complexity at 0.0%).
 */

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_DECODED_BYTES (32L << 20) /* bound decoded w*h*4 */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    int x, y, channels;

    if (!stbi_info_from_memory(data, (int) size, &x, &y, &channels)) return 0;
    if (y && x > (int) ((MAX_DECODED_BYTES / 4) / (unsigned) y)) return 0;

    /* Integer decode path (shared with production fuzzers). */
    unsigned char *img = stbi_load_from_memory(data, (int) size, &x, &y, &channels, 4);
    free(img);

    /* Float decode path: hdr/pic/pnm/psd float decoders + conversion. */
    int fx, fy, fc;
    float *fimg = stbi_loadf_from_memory(data, (int) size, &fx, &fy, &fc, 4);
    free(fimg);

    /* 16-bit data-path predicate used alongside the float API. */
    (void) stbi_is_16_bit_from_memory(data, (int) size);

    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
