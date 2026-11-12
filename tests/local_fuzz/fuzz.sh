#!/bin/sh
make -j8 -O || exit 1
if [ ! -f "bin/$1" ]; then
   echo fuzz.sh [target]. Target fuzzer needs to be built in bin/ dir.
   exit 1
fi

EXTRA_ARGS=

case "$1" in
   image_asan)
      EXTRA_ARGS="-dict=image.dict image_seeds"
      ;;
   image_*)
      # ubsan and msan are expected to be run after asan and use asan's corpus as seed
      EXTRA_ARGS="-dict=image.dict image_asan"
      ;;
   vorbis_asan)
      EXTRA_ARGS="-dict=../stb_vorbis.dict vorbis_seeds"
      ;;
   vorbis_*)
      # again, ubsan and msan are expected to be run after asan and use that test corpus
      # as seed
      EXTRA_ARGS="-dict=../stb_vorbis.dict vorbis_asan"
      ;;
   c_lexer_asan)
      EXTRA_ARGS="-dict=../stb_c_lexer.dict c_lexer_seeds"
      ;;
   c_lexer_*)
      # same thing again
      EXTRA_ARGS="-dict=../stb_c_lexer.dict c_lexer_asan"
      ;;
   *)
      echo "Target not recognized."
      exit 1
      ;;
esac

mkdir -p $1

bin/$1 $1 -max_len=131072 $EXTRA_ARGS
