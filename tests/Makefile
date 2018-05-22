INCLUDES = -I..
CFLAGS = $(INCLUDES) -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST -Wall -Wextra -Wstrict-aliasing
CPPFLAGS = $(INCLUDES) -Wno-write-strings -DSTB_DIVIDE_TEST -Wall -Wextra

all:
	$(CC) $(CFLAGS) ../stb_vorbis.c test_c_compilation.c -lm
	$(CC) $(CPPFLAGS) test_cpp_compilation.cpp -lm -lstdc++

sprintf: test_sprintf.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f sprintf test_sprintf.o
