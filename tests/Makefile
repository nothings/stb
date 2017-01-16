INCLUDE = -I..
DEFINES = -DSTB_C_LEXER_SELF_TEST

32:
	$(CC) -m32 $(INCLUDE) $(DEFINES) ../stb_vorbis.c test_c_compilation.c ../stb.c -lm
	$(CC) -m32 $(INCLUDE) $(DEFINES) ../stb_vorbis.c test_cpp_compilation.cpp -lm

64:
	$(CC) -m64 $(INCLUDE) $(DEFINES) ../stb_vorbis.c test_c_compilation.c ../stb.c -lm
	$(CC) -m64 $(INCLUDE) $(DEFINES) ../stb_vorbis.c test_cpp_compilation.cpp -lm
