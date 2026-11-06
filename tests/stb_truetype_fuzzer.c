/* Fuzzer for stb_truetype.h (OSS-Fuzz coverage-pipeline pair stb-truetype-fuzzer).
 *
 * Threat model:
 *   - Untrusted input: the whole fuzz buffer, interpreted as a TrueType/OpenType
 *     font file, exactly like a .ttf an application loads from disk/web.
 *   - Trust boundary: stbtt_InitFont table parsing and the glyph metric,
 *     outline (glyf/loca) and kerning paths.
 *   - Attacker controls: every byte of the font, subfont index, codepoints,
 *     glyph selection and rasterisation pixel height (bounded).
 *   - Expected bug classes: OOB reads in table/glyf parsing, integer
 *     overflows in offset arithmetic, OOB writes in outline decoding,
 *     pathological bitmap allocations (bounded here).
 */

#define STB_TRUETYPE_IMPLEMENTATION
#include "../stb_truetype.h"

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BITMAP_PIXELS (1L << 20) /* bound raster allocations */

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 16) return 0;

    (void) stbtt_GetNumberOfFonts(data);

    int offset = stbtt_GetFontOffsetForIndex(data, (int) (data[0] & 3u));
    if (offset < 0) return 0;

    stbtt_fontinfo font;
    if (!stbtt_InitFont(&font, data, offset)) return 0;

    int x0, y0, x1, y1, ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    stbtt_GetFontBoundingBox(&font, &x0, &y0, &x1, &y1);

    int cp1 = (int) (((unsigned) data[1] << 8) | (unsigned) data[2]);
    int cp2 = (int) (((unsigned) data[3] << 8) | (unsigned) data[4]);
    int g1 = stbtt_FindGlyphIndex(&font, cp1);
    int g2 = stbtt_FindGlyphIndex(&font, cp2);

    int aw, lsb;
    stbtt_GetCodepointHMetrics(&font, cp1, &aw, &lsb);
    stbtt_GetGlyphBox(&font, g1, &x0, &y0, &x1, &y1);
    (void) stbtt_GetCodepointKernAdvance(&font, cp1, cp2);

    stbtt_vertex *verts = NULL;
    int nv = stbtt_GetGlyphShape(&font, g1, &verts);
    if (verts != NULL) stbtt_FreeShape(&font, verts);
    (void) nv;

    /* Rasterise one glyph with a bounded pixel height and bounded output. */
    float scale = stbtt_ScaleForPixelHeight(&font, (float) (8 + (data[5] & 31u)));
    int bw, bh, bx, by;
    stbtt_GetGlyphBitmapBox(&font, g2, scale, scale, &x0, &y0, &x1, &y1);
    bw = x1 - x0 + 1;
    bh = y1 - y0 + 1;
    if (bw > 0 && bh > 0 && (long) bw * (long) bh <= MAX_BITMAP_PIXELS) {
        unsigned char *bmp = stbtt_GetGlyphBitmap(&font, scale, scale, g2, &bw, &bh, &bx, &by);
        free(bmp);
    }
    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
