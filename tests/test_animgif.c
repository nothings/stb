#include <stdio.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static unsigned int fnv1a_hash32(const stbi_uc *bytes, size_t len)
{
   unsigned int hash = 0x811c9dc5;
   unsigned int mul = 0x01000193;
   size_t i;

   for (i = 0; i < len; ++i)
      hash = (hash ^ bytes[i]) * mul;

   return hash;
}

int main(int argc, char **argv)
{
    int x,y,n,nframes;
    stbi_uc *data;
    stbi__context s;
    FILE *f;
    int *delays = NULL;

    if (argc < 2) {
        printf("test_animgif <file>\n");
        printf("writes 'decoded0000.png' plus following\n");
        return 1;
    }

    printf("loading %s\n", argv[1]);
    f = fopen(argv[1], "rb");
    if (!f)
    {
        printf("error opening file!\n");
        return 1;
    }
    stbi__start_file(&s,f);
    data = stbi__load_gif_main(&s, &delays, &x, &y, &nframes, &n, 4);
    fclose(f);

    if (!data) {
        printf("image failed to load: %s\n", stbi_failure_reason());
        return 1;
    }

    printf("loaded %d frames, hash=0x%08x\n", nframes, fnv1a_hash32(data, x * y * 4 * nframes));

    for (n = 0; n < nframes; n++) {
        char buffer[128];
        sprintf(buffer, "decoded%04d.png", n);
        printf("  saving %s\n", buffer);
        stbi_write_png(buffer, x, y, 4, data + (x*y*4)*n, x * 4);
    }

    stbi_image_free(data);
    stbi_image_free(delays);
    return 0;
}
