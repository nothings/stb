INCLUDES = -I..
CFLAGS = -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST
CPPFLAGS = -Wno-write-strings -DSTB_DIVIDE_TEST

32:
	$(CC) -m32 $(INCLUDES) $(CFLAGS) ../stb_vorbis.c test_c_compilation.c     -lm
	$(CC) -m32 $(INCLUDES) $(CPPFLAGS) ../stb_vorbis.c test_cpp_compilation.cpp -lm

64:
	$(CC) -m64 $(INCLUDES) $(CFLAGS) ../stb_vorbis.c test_c_compilation.c     -lm
	$(CC) -m64 $(INCLUDES) $(CPPFLAGS) ../stb_vorbis.c test_cpp_compilation.cpp -lm
