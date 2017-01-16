INCLUDES = -I..
FLAGS = -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST

32:
	$(CC) -m32 $(INCLUDES) $(FLAGS) ../stb_vorbis.c test_c_compilation.c     -lm
	$(CC) -m32 $(INCLUDES) $(FLAGS) ../stb_vorbis.c test_cpp_compilation.cpp -lm

64:
	$(CC) -m64 $(INCLUDES) $(FLAGS) ../stb_vorbis.c test_c_compilation.c     -lm
	$(CC) -m64 $(INCLUDES) $(FLAGS) ../stb_vorbis.c test_cpp_compilation.cpp -lm
