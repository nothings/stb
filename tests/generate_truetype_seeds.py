#!/usr/bin/env python3
"""Structured seed generator for stb_truetype_fuzzer.

Reads the valid TrueType anchor font in tests/truetype_seeds/ and emits into
the output directory:
  - the valid font itself,
  - deterministic truncations (lose trailing tables),
  - deterministic single-byte corruptions in the table-directory region
    (offsets/lengths) and glyph-data region,
so libFuzzer starts from structurally valid sfnt input and reaches table
parsing, glyph outline decoding and rasterisation immediately.

Run from tests/ossfuzz.sh as:
  python3 $SRC/stb/tests/generate_truetype_seeds.py <output-dir>
"""

import os
import sys

OUT = sys.argv[1] if len(sys.argv) > 1 else "truetype_fuzz_seeds"
HERE = os.path.dirname(os.path.abspath(__file__))
ANCHORS = os.path.join(HERE, "truetype_seeds")
count = 0

def main():
    global count
    os.makedirs(OUT, exist_ok=True)
    for name in sorted(os.listdir(ANCHORS)):
        if not name.endswith(".ttf"):
            continue
        with open(os.path.join(ANCHORS, name), "rb") as f:
            raw = f.read()
        base = os.path.splitext(name)[0]

        def emit(suffix, blob):
            global count
            path = os.path.join(OUT, "%s_%s.ttf" % (base, suffix))
            with open(path, "wb") as g:
                g.write(blob)
            count += 1

        emit("valid", raw)

        # truncations: cut into the tail tables
        for frac in (2, 4, 16):
            cut = max(256, len(raw) - len(raw) // frac)
            emit("trunc%d" % frac, raw[:cut])

        # deterministic corruptions: table directory (offsets/lengths) and glyf
        # directory starts at 12, 16 bytes per table entry
        for off in (12, 16, 28, 44, 0x100, 0x1000, 0x2000):
            if off < len(raw):
                m = bytearray(raw)
                m[off] ^= 0x5A
                emit("dir%04x" % off, bytes(m))

    print("generate_truetype_seeds: wrote %d seeds to %s" % (count, OUT))

if __name__ == "__main__":
    main()
