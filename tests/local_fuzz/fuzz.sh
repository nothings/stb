#!/bin/sh
make -j8 -O
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
	*)
		echo "Target not recognized."
		exit 1
		;;
esac

mkdir -p $1

bin/$1 $1 -max_len=4096 $EXTRA_ARGS
