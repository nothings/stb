#!/usr/bin/python3
import subprocess
import sys

if __name__ == '__main__':
    MODE_FLAGS = [
        'STB_VORBIS_NO_PULLDATA_API',
        'STB_VORBIS_NO_PUSHDATA_API',
    ]
    OTHER_FLAGS = [
        'STB_VORBIS_NO_STDIO',
        'STB_VORBIS_NO_COMMENTS',
        'STB_VORBIS_NO_INTEGER_CONVERSION',
    ]
    # mode flags first, other flags second
    BINARY_FLAGS = MODE_FLAGS + OTHER_FLAGS
    all_mode_mask = (1 << len(MODE_FLAGS)) - 1

    nflags = len(BINARY_FLAGS)
    count = 1 << nflags
    for i in range(count):
        # we don't support the no push/no pull combination, that's just "vorbis without vorbis"
        if (i & all_mode_mask) == all_mode_mask:
            continue

        args = ['clang', '-o', '/dev/null', '-c', '-O0', '-Wall', '-Werror', '-I..']
        for j, flag in enumerate(BINARY_FLAGS):
            if (i & (1 << j)) != 0:
                args.append('-D' + flag)

        print(f'\r{i}/{count} ', end='')
        args.append('../stb_vorbis.c')
        result = subprocess.run(args)
        if result.returncode != 0:
            print('failed command was:', ' '.join(args))
            sys.exit(result)

    print('\x1b[2K\r', end='')
