#!/bin/bash -eu
# This script is meant to be run by
# https://github.com/google/oss-fuzz/blob/master/projects/stb/Dockerfile

# oss-fuzz: "you _must_ use CXX as a linker, even if your project is written in pure C."
# could compile via CC then only link via CXX, but eh, it's fine
$CXX $CXXFLAGS -std=c++11 -I.. -DSTBI_ONLY_PNG  \
    $SRC/stb/tests/local_fuzz/image.c \
    -o $OUT/stb_png_read_fuzzer $LIB_FUZZING_ENGINE

$CXX $CXXFLAGS -std=c++11 -I.. \
    $SRC/stb/tests/local_fuzz/image.c \
    -o $OUT/stbi_read_fuzzer $LIB_FUZZING_ENGINE

$CXX $CXXFLAGS -std=c++11 -I.. \
	$SRC/stb/tests/local_fuzz/vorbis.c \
	-o $OUT/stb_vorbis_fuzzer $LIB_FUZZING_ENGINE

# PNG-only corpus

find $SRC/stb/tests/pngsuite -name "*.png" | \
     xargs zip $OUT/stb_png_read_fuzzer_seed_corpus.zip

# "All image formats" corpus

tar xvzf $SRC/stbi/jpg.tar.gz --directory $SRC/stb/tests
tar xvzf $SRC/stbi/gif.tar.gz --directory $SRC/stb/tests
unzip    $SRC/stbi/bmp.zip    -d $SRC/stb/tests
unzip    $SRC/stbi/tga.zip    -d $SRC/stb/tests

find $SRC/stb/tests -name "*.png" -o -name "*.jpg" -o -name "*.gif" \
                 -o -name "*.bmp" -o -name "*.tga" -o -name "*.TGA" \
                 -o -name "*.ppm" -o -name "*.pgm" -o -name "*.hdr" \
				 -o -name "*.psd" \
    | xargs zip $OUT/stbi_read_fuzzer_seed_corpus.zip

cat $SRC/stb/tests/stb_png.dict $SRC/stb/tests/stbi_*.dict > $OUT/stbi_read_fuzzer.dict

# stb_vorbis corpus

find $SRC/stb/tests/local_fuzz/vorbis_seeds -name "*.ogg" \
	| xargs zip $OUT/stb_vorbis_seed_corpus.zip

cp $SRC/stb/tests/stb_vorbis.dict $OUT/stb_vorbis_fuzzer.dict
