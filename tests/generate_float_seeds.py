#!/usr/bin/env python3
"""Structured seed generator for stbi_float_fuzzer.

Synthesizes from scratch (no external downloads) structurally valid images in
the formats whose decoders are dark in the existing OSS-Fuzz coverage:

  - Radiance HDR (.hdr): text header + flat RGBE pixels,
  - PNM (.pgm/.ppm): 8-bit binary P5/P6 and 16-bit P5,
  - PSD (.psd): raw (uncompressed) 8-bit RGB and 16-bit greyscale,
  - Softimage PIC (.pic): magic + PICT + 16-bit dims + uncompressed RGB packet,
  - TGA (.tga): uncompressed 24-bit,

and writes a couple of deterministic corruption variants per file. All inputs
are the exact bytes an attacker would hand to stbi_loadf in an application.

Run from tests/ossfuzz.sh as:
  python3 $SRC/stb/tests/generate_float_seeds.py <output-dir>
"""

import os
import struct
import sys

OUT = sys.argv[1] if len(sys.argv) > 1 else "float_fuzz_seeds"

W = H = 8

def hdr_flat(w, h):
    header = b"#?RADIANCE\nFORMAT=32-bit_rle_rgbe\nEXPOSURE=1.0\n\n-Y %d +X %d\n" % (h, w)
    body = bytearray()
    for y in range(h):
        for x in range(w):
            body += bytes([x * 8 % 256, y * 16 % 256, 64, 128])  # RGBE, e=128
    return header + bytes(body)

def pnm(magic, w, h, maxval, data):
    return b"%s\n%d %d\n%d\n" % (magic, w, h, maxval) + data

def psd(w, h, channels, depth):
    head = b"8BPS" + struct.pack(">H", 1) + b"\x00" * 6
    head += struct.pack(">H", channels) + struct.pack(">II", h, w)
    head += struct.pack(">HI", depth, 3)  # mode 3 = RGB
    head += struct.pack(">I", 0)          # colour mode data length
    head += struct.pack(">I", 0)          # image resources length
    head += struct.pack(">I", 0)          # layer & mask length
    head += struct.pack(">H", 0)          # compression: raw
    nchanbytes = channels * w * h * (depth // 8)
    body = bytearray(range(256)) * (nchanbytes // 256 + 1)
    return head + bytes(body[:nchanbytes])

def pic(w, h):
    b = bytearray(b"\x53\x80\xf6\x34")     # magic
    b += b"\x00" * 84                      # skipped header area
    b += b"PICT"                           # at offset 88
    b += struct.pack(">HH", w, h)          # width, height (16-bit BE)
    b += struct.pack(">I", 0)              # ratio
    b += struct.pack(">HH", 1, 0)          # fields, pad
    b += bytes([0, 8, 0, 7])               # chained=0, size=8, type=0 raw, channel=RGB
    for y in range(h):
        for x in range(w):
            b += bytes([x * 8 % 256, y * 16 % 256, 64])
    return bytes(b)

def tga24(w, h):
    head = struct.pack("<BBBHHBHHHHBB", 0, 0, 2, 0, 0, 0, 0, 0, w, h, 24, 0x20)
    body = bytearray()
    for y in range(h):
        for x in range(w):
            body += bytes([x * 8 % 256, y * 16 % 256, 64])
    return head + bytes(body)

def main():
    os.makedirs(OUT, exist_ok=True)
    files = {
        "gen_8x4.hdr": hdr_flat(8, 4),
        "gen_8x8.ppm": pnm(b"P6", W, H, 255, bytes((i * 7) % 256 for i in range(W * H * 3))),
        "gen_8x8.pgm": pnm(b"P5", W, H, 255, bytes((i * 11) % 256 for i in range(W * H))),
        "gen_8x8_16bit.pgm": pnm(b"P5", W, H, 65535,
                                 b"".join(struct.pack(">H", (i * 523) % 65536) for i in range(W * H))),
        "gen_8x8_rgb8.psd": psd(W, H, 3, 8),
        "gen_8x8_ga16.psd": psd(W, H, 2, 16),
        "gen_8x8.pic": pic(W, H),
        "gen_8x8.tga": tga24(W, H),
    }
    count = 0
    for name, blob in files.items():
        path = os.path.join(OUT, name)
        with open(path, "wb") as f:
            f.write(blob)
        count += 1
        # deterministic corruption variant: flip one byte mid-file
        m = bytearray(blob)
        pos = len(blob) // 2
        m[pos] ^= 0xA5
        with open(os.path.join(OUT, "corrupt_" + name), "wb") as f:
            f.write(bytes(m))
        count += 1
    print("generate_float_seeds: wrote %d seeds to %s" % (count, OUT))

if __name__ == "__main__":
    main()
