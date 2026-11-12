CFLAGS := -O2 -g -I../.. -MMD -MP

TARGETS := bin/image_asan bin/image_msan bin/image_ubsan \
			  bin/vorbis_asan bin/vorbis_msan bin/vorbis_ubsan \
			  bin/c_lexer_asan bin/c_lexer_msan bin/c_lexer_ubsan
DEPS := $(addsuffix .d,$(TARGETS))

all: $(TARGETS) | bin

bin/%_asan: %.c | bin
	clang $(CFLAGS) -fsanitize=address,fuzzer $< -o $@

bin/%_msan: %.c | bin
	clang $(CFLAGS) -fsanitize=memory,fuzzer $< -o $@

bin/%_ubsan: %.c | bin
	clang $(CFLAGS) -fsanitize=undefined,fuzzer $< -o $@

bin:
	mkdir -p bin

-include $(DEPS)
