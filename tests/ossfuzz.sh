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

tar xvzf $SRC/stbi/jpg.tar.gz --directory $SRC/stb/tests
tar xvzf $SRC/stbi/gif.tar.gz --directory $SRC/stb/tests
unzip    $SRC/stbi/bmp.zip    -d $SRC/stb/tests
unzip    $SRC/stbi/tga.zip    -d $SRC/stb/tests

find $SRC/stb/tests -name "*.png" -o -name "*.jpg" -o -name "*.gif" \
                 -o -name "*.bmp" -o -name "*.tga" -o -name "*.TGA" \
                 -o -name "*.ppm" -o -name "*.pgm" \
    | xargs zip $OUT/stbi_read_fuzzer_seed_corpus.zip

echo "" >> $SRC/stbi/gif.dict
cat $SRC/stbi/gif.dict $SRC/stb/tests/stb_png.dict > $OUT/stbi_read_fuzzer.dict

# stbi_float_fuzzer (coverage-pipeline pair stb-image-float-api-fuzzer):
# drives the stbi_loadf float API family and the hdr/pic/pnm/psd decoders
# that no existing harness or corpus reaches. Seeds are synthesized from
# scratch by generate_float_seeds.py (no network downloads).
$CXX $CXXFLAGS -std=c++11 -I. \
    $SRC/stb/tests/stbi_float_fuzzer.c \
    -o $OUT/stbi_float_fuzzer $LIB_FUZZING_ENGINE

python3 $SRC/stb/tests/generate_float_seeds.py $SRC/stb/tests/float_fuzz_seeds
find $SRC/stb/tests/float_fuzz_seeds -type f | \
     xargs zip $OUT/stbi_float_fuzzer_seed_corpus.zip
find $SRC/stb/tests/pngsuite -name "*.png" | head -30 | \
     xargs zip $OUT/stbi_float_fuzzer_seed_corpus.zip

cp $SRC/stb/tests/stbi_float.dict $OUT/stbi_float_fuzzer.dict
