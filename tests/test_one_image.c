#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char **argv)
{
    int x,y,n;
    stbi_uc *data;

    if (argc < 2) {
        printf("test_one_image <file>\n");
        printf("writes 'decoded.png'\n");
        return 1;
    }

    data = stbi_load(argv[1], &x, &y, &n, 4);
    if (!data) {
        printf("image failed to load: %s\n", stbi_failure_reason());
        return 1;
    }

    stbi_write_png("decoded.png", x, y, 4, data, x * 4);
    stbi_image_free(data);
    return 0;
}
