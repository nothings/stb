#!/bin/bash -eu
# This script is meant to be run by
# https://github.com/google/oss-fuzz/blob/master/projects/stb/Dockerfile

$CXX $CXXFLAGS -std=c++11 -I. -DSTBI_ONLY_PNG  \
    $SRC/stb/tests/stbi_read_fuzzer.c \
    -o $OUT/stb_png_read_fuzzer $LIB_FUZZING_ENGINE

$CXX $CXXFLAGS -std=c++11 -I. \
    $SRC/stb/tests/stbi_read_fuzzer.c \
    -o $OUT/stbi_read_fuzzer $LIB_FUZZING_ENGINE

find $SRC/stb/tests/pngsuite -name "*.png" | \
     xargs zip $OUT/stb_png_read_fuzzer_seed_corpus.zip

cp $SRC/stb/tests/stb_png.dict $OUT/stb_png_read_fuzzer.dict


find $SRC/stb/tests -name "*.png" -o -name "*.jpg" -o -name "*.gif" \
                 -o -name "*.bmp" -o -name "*.tga" -o -name "*.TGA" \
                 -o -name "*.ppm" -o -name "*.pgm" \
    | xargs zip $OUT/stbi_read_fuzzer_seed_corpus.zip

echo "" >> $SRC/stb/tests/gif.dict
cat $SRC/stb/tests/gif.dict $SRC/stb/tests/stb_png.dict > $OUT/stbi_read_fuzzer.dict
