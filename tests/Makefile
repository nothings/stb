INCLUDES = -I..
CFLAGS = -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST
CPPFLAGS = -Wno-write-strings -DSTB_DIVIDE_TEST

# Uncomment this line for reproducing OSS-Fuzz bugs with image_fuzzer
#CFLAGS += -O -fsanitize=address 

all:
	$(CC) $(INCLUDES) $(CFLAGS) ../stb_vorbis.c test_c_compilation.c test_c_lexer.c test_dxt.c test_easyfont.c test_image.c test_image_write.c test_sprintf.c test_truetype.c test_voxel.c -lm
	$(CC) $(INCLUDES) $(CPPFLAGS) -std=c++0x test_cpp_compilation.cpp -lm -lstdc++
	$(CC) $(INCLUDES) $(CFLAGS) -DIWT_TEST image_write_test.c -lm -o image_write_test
	$(CC) $(INCLUDES) $(CFLAGS) fuzz_main.c stbi_read_fuzzer.c -lm -o image_fuzzer
