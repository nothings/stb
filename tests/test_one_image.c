#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char **argv)
{
    int x,y,n;
    stbi_info_res res;
    stbi_uc *data;

    if (argc < 2) {
        printf("test_one_image <file>\n");
        printf("writes 'decoded.png'\n");
        return 1;
    }

    res = stbi_info2(argv[1]);
    if (res.type != STBI_type_unsupported) {
        printf("info successful! type=%d\n", res.type);
        printf("  x=%d\n  y=%d\n  comp=%d\n  is_16_bit=%d\n  is_hdr=%d\n  is_iphone_png=%d\n",
            res.x, res.y, res.comp, res.is_16_bit, res.is_hdr, res.is_iphone_png);
    } else {
        printf("info failed!\n");
    }

    data = stbi_load(argv[1], &x, &y, &n, 4);
    if (!data) {
        printf("image failed to load: %s\n", stbi_failure_reason());
        return 1;
    }

    printf("%dx%d, ncomp=%d\n", x, y, n);
    printf("stbi_is_16_bit(\"%s\") = %d\n", argv[1], stbi_is_16_bit(argv[1]));

    stbi_write_png("decoded.png", x, y, 4, data, x * 4);
    stbi_image_free(data);
    return 0;
}
