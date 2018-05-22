#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char buf[1024];
    memset(buf, 0xFF, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;

    {
        char const *s = "hello, world";
        int len = stbsp_snprintf(buf, 1024, s);
        assert(len == (int)strlen(s));
        assert(strcmp(buf, s) == 0);
        len = stbsp_snprintf(NULL, 0, s);
        assert(len == (int)strlen(s));
    }

    memset(buf, 0xFF, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;

    {
        char const *s = "hello, world";
        int size = stbsp_snprintf(buf, 8, s);
        assert(size == (int)strlen(s));
        assert(strlen(buf) == 7);
        assert(buf[7] == 0);
        assert(buf[8] == -1);
        assert(buf[9] == -1);
        assert(strncmp(buf, s, strlen(buf)) == 0);
    }

    memset(buf, 0xFF, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;

    {
        char const *s = "hello, world";
        int size = stbsp_snprintf(buf, 3, "%d", 10000);
        assert(size == 5);
        assert(strlen(buf) == 2);
        assert(buf[0] == '1');
        assert(buf[1] == '0');
        assert(buf[2] == '\0');
        assert(strcmp(buf, "10") == 0);

        size = stbsp_snprintf(buf, 5, "%.*s", (int)strlen(s), s);
        assert(size == (int)strlen(s));
        assert(strlen(buf) == 4);
        assert(strcmp(buf, "hell") == 0);
    }

    memset(buf, 0xFF, sizeof(buf));
    buf[sizeof(buf) - 1] = 0;

    {
        char *lbuf = malloc(2048);
        int i, size;
        for (i = 0; i < 2047; ++i)
            lbuf[i] = 'a';
        lbuf[2047] = 0;

        size = stbsp_snprintf(buf, 1024, "%s", lbuf);
        assert(size == (int)strlen(lbuf));
        assert(strlen(buf) == 1023);
        assert(strncmp(buf, lbuf, strlen(buf)) == 0);
    }

    puts("ok");
    return 0;
}

