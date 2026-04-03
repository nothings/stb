# stb PoC Results

Target: nothings/stb (33k stars)
Date: 2026-04-02
All PoCs built with gcc -O0 -g, run on Linux x86_64.

## Confirmed Triggers

| PoC file | Bug ID | Severity | Result |
|----------|--------|----------|--------|
| poc_palette_leak | H3 | High | 161/255 pixels contain leaked stack memory |
| poc_convert16_overflow | C1 | Critical | 8 GB needed, 32-bit arithmetic gives 0 bytes |
| poc_gif_twoback | H2 | High | ASAN SEGV at stb_image.h:6818 (read before heap) |
| poc_vorbis_clamp | H1 | High | Buggy clamp allows 2-10 extra samples past buffer |
| poc_convert_16to8 | C2/C3 | Critical | img_len*2 wraps to -2147483648 |
| poc_gif_layers_overflow | C4 | Critical | Overflow at 3356 frames (400x400), practical in ~65 KB GIF |
| poc_png_colordepth | H5 | High | RGB depth=4 accepted (should reject per PNG spec) |
| poc_jpeg_progressive_leak | H4 | High | 64/64 coefficients are 0xABAB (heap poison visible) |
| poc_marker_return | H6 | High | return 1 on failure confirmed (logic bug) |
| poc_png_idat_overflow | H8 | High | idata_limit overflows to 0, would write 1 GB into nothing |
| poc_bmp_palette | M5 | Medium | 96 pixels contain leaked stack data |
| poc_vertical_flip | M2 | Medium | slice_size wraps to 0, pointer never advances |

## How to reproduce

Build any PoC:
    gcc -O0 -g -o <name> <name>.c -lm

For ASAN detection (gif_twoback, png_colordepth):
    gcc -O0 -g -fsanitize=address -o <name> <name>.c -lm

## Bugs not covered by PoCs

C5, C6: stb_vorbis codebook overflows (need crafted .ogg generator)
M1: zlib decompression bomb (needs large deflate stream)
M3: PIC RLE infinite loop (needs crafted .pic file)
M4: GIF LZW unbounded recursion (needs 4096-deep code chain)
M6: PSD skip sign truncation (needs crafted .psd)
M7: stb_vorbis vendor string overflow (needs crafted .ogg)
M8, M9: stb_truetype OOB/recursion (architectural, library disclaims security)

## Full audit report

See ../stb-audit.md for detailed descriptions of all 27 findings.
