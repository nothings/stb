#!/usr/bin/python3
import subprocess
import sys

if __name__ == '__main__':
    FORMAT_FLAGS = [
        'STBI_NO_JPEG',
        'STBI_NO_PNG',
        'STBI_NO_BMP',
        'STBI_NO_PSD',
        'STBI_NO_TGA',
        'STBI_NO_GIF',
        'STBI_NO_HDR',
        'STBI_NO_PNM',
    ]
    OTHER_FLAGS = [
        'STBI_NO_STDIO',
        'STBI_NO_LINEAR',
        'STBI_NO_SIMD',
    ]
    # put the image formats first, we want to cover all those permutations early
    # the rest goes later
    BINARY_FLAGS = FORMAT_FLAGS + OTHER_FLAGS
    no_formats_mask = (1 << len(FORMAT_FLAGS)) - 1

    nflags = len(BINARY_FLAGS)
    count = 1 << nflags
    for i in range(count):
        # we don't support _no_ formats selected, so skip over these configs
        if (i & no_formats_mask) == no_formats_mask:
            continue

        args = ['clang', '-o', '/dev/null', '-c', '-O0', '-Wall', '-Werror', '-I..']
        for j, flag in enumerate(BINARY_FLAGS):
            if (i & (1 << j)) != 0:
                args.append('-D' + flag)

        print(f'\r{i}/{count} ', end='')
        args.append('test_image_compile.c')
        result = subprocess.run(args)
        if result.returncode != 0:
            print('failed command was:', ' '.join(args))
            sys.exit(result)

    print('\x1b[2K\r', end='')
