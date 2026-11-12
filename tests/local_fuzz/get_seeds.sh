#!/bin/sh

# download files to cache dir if they don't exist already
mkdir -p cache

wget -nv -cO cache/gif.tar.gz https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/imagetestsuite/imagetestsuite-gif-1.00.tar.gz
wget -nv -cO cache/jpg.tar.gz https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/imagetestsuite/imagetestsuite-jpg-1.00.tar.gz
wget -nv -cO cache/bmp.zip http://entropymine.com/jason/bmpsuite/releases/bmpsuite-2.6.zip
wget -nv -cO cache/tga.zip https://github.com/richgel999/tga_test_files/archive/master.zip

# unpack image seeds
mkdir -p image_seeds

tar xzvf cache/gif.tar.gz --directory image_seeds
tar xzvf cache/jpg.tar.gz --directory image_seeds
unzip    cache/bmp.zip    -d          image_seeds
unzip    cache/tga.zip    -d          image_seeds

# concatenate dicts into combined image dict
cat ../stb_png.dict ../stbi_*.dict > image.dict

# seed for C lexer is the lexer itself
mkdir -p c_lexer_seeds
cp ../../stb_c_lexer.h c_lexer_seeds
