#!/usr/bin/env python3
"""Structured seed generator for stb_vorbis_fuzzer.

Reads the valid Vorbis anchor streams in tests/vorbis_seeds/ and emits into
the output directory:
  - valid streams wrapped in the 8-byte harness control prefix
    (decode-only and decode+seek variants, near-start and near-end targets),
  - deterministic truncated variants (miss later pages),
  - deterministic single-byte header-corruption variants,
so libFuzzer starts from structurally valid Ogg/Vorbis inputs and reaches
header parsing, frame decoding and the seek path immediately.

Run from tests/ossfuzz.sh as:
  python3 $SRC/stb/tests/generate_vorbis_seeds.py <output-dir>
"""

import os
import sys

OUT = sys.argv[1] if len(sys.argv) > 1 else "vorbis_fuzz_seeds"
HERE = os.path.dirname(os.path.abspath(__file__))
ANCHORS = os.path.join(HERE, "vorbis_seeds")
count = 0

# harness control prefix: data[0] = op (bit0: seek), data[1..5] = seek target
def control(op, target):
    return bytes([op & 0xFF,
                  target & 0xFF,
                  (target >> 8) & 0xFF,
                  (target >> 16) & 0xFF,
                  (target >> 24) & 0xFF,
                  0, 0, 0])

def main():
    global count
    os.makedirs(OUT, exist_ok=True)
    for name in sorted(os.listdir(ANCHORS)):
        if not name.endswith(".oga"):
            continue
        with open(os.path.join(ANCHORS, name), "rb") as f:
            raw = f.read()
        base = os.path.splitext(name)[0]

        def emit(suffix, blob):
            global count
            path = os.path.join(OUT, "%s_%s" % (base, suffix))
            with open(path, "wb") as g:
                g.write(blob)
            count += 1

        # decode-only and decode+seek (start / middle / far-end targets)
        emit("decode", control(0, 0) + raw)
        for tgt, tag in ((0, "seek0"), (4096, "seek4k"), (1 << 30, "seekfar")):
            emit(tag, control(1, tgt) + raw)

        # truncations: lose later pages / cut mid-header / cut mid-frame
        for frac in (1, 3, 8, 32):
            cut = max(64, len(raw) - len(raw) // frac)
            emit("trunc%d" % frac, control(0, 0) + raw[:cut])

        # deterministic header corruptions across the first bytes
        for off in (0x14, 0x1c, 0x28, 0x40, 0x80):
            if off < len(raw):
                m = bytearray(raw)
                m[off] ^= 0x5A
                emit("hdr%03x" % off, control(0, 0) + bytes(m))

    print("generate_vorbis_seeds: wrote %d seeds to %s" % (count, OUT))

if __name__ == "__main__":
    main()
