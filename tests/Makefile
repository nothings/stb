INCLUDES = -I..
CFLAGS = -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST
CPPFLAGS = -Wno-write-strings -DSTB_DIVIDE_TEST

all:
	$(CC) $(INCLUDES) $(CFLAGS) ../stb_vorbis.c test_c_compilation.c -lm
	$(CC) $(INCLUDES) $(CPPFLAGS) test_cpp_compilation.cpp -lm -lstdc++
