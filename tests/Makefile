INCLUDES = -I..
CFLAGS = -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST
CPPFLAGS = -Wno-write-strings -DSTB_DIVIDE_TEST

all:
	$(CC) $(INCLUDES) $(CFLAGS) ../stb_vorbis.c test_c_compilation.c -lm
	$(CC) $(INCLUDES) $(CPPFLAGS) test_cpp_compilation.cpp -lm -lstdc++
	$(MAKE) -C tx all || true
	prove -v -f tx || true
	$(MAKE) -C t all
	prove -f

clean:
	rm -f *.o
	$(MAKE) -C tx clean
	$(MAKE) -C t clean

.PHONY: all clean
