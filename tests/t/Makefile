INCLUDES = -I../..
CFLAGS = $(INCLUDES) -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -DSTB_DIVIDE_TEST
CPPFLAGS = $(INCLUDES) -Wno-write-strings -DSTB_DIVIDE_TEST
LDLIBS = -lm

all: clean image_pnm image_pnm_8bit image_pnm_ascii

clean:
	rm -f image_pnm image_pnm_8bit image_pnm_ascii

.PHONY: all clean
