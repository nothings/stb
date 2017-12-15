
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string.h>
#include <wchar.h>

static FILE *stbi__wfopen_wb(wchar_t const *filename)
{
   FILE *f;
#if defined(_MSC_VER) && _MSC_VER >= 1400
   if (0 != _wfopen_s(&f, filename, L"wb"))
      f=0;
#else
   f = wfopen(filename, L"wb");
#endif
   return f;
}

static FILE *stbi__wfopen_rb(wchar_t const *filename)
{
   FILE *f;
#if defined(_MSC_VER) && _MSC_VER >= 1400
   if (0 != _wfopen_s(&f, filename, L"rb"))
      f=0;
#else
   f = _wfopen(filename, L"rb");
#endif
   return f;
}

stbi_uc *stbi_loadW(wchar_t const *filename, int *x, int *y, int *comp, int req_comp)
{
   FILE *f = stbi__wfopen_rb(filename);
   if (!f) return stbi__errpuc("can't fopen", "Unable to open file");
   unsigned char *result = stbi_load_from_file(f,x,y,comp,req_comp);
   fclose(f);
   return result;
}

stbi_us *stbi_load_16W(wchar_t const *filename, int *x, int *y, int *comp, int req_comp)
{
   FILE *f = stbi__wfopen_rb(filename);
   if (!f) return (stbi_us *) stbi__errpuc("can't fopen", "Unable to open file");
   stbi__uint16 *result = stbi_load_from_file_16(f,x,y,comp,req_comp);
   fclose(f);
   return result;
}

int stbi_infoW(wchar_t const *filename, int *x, int *y, int *comp)
{
    FILE *f = stbi__wfopen_rb(filename);
    if (!f) return stbi__err("can't fopen", "Unable to open file");
    int result = stbi_info_from_file(f, x, y, comp);
    fclose(f);
    return result;
}

int stbi_write_bmpW(wchar_t const *filename, int x, int y, int comp, const void *data)
{
   FILE *f = stbi__wfopen_wb(filename);
   int result;
   if (!f) return 0;
   result = stbi_write_bmp_to_file(f, x, y, comp, data);
   fclose(f);
   return result;
   return stbi_write_bmp_to_file(stbi__wfopen_wb(filename),x, y, comp, data);
}

int stbi_write_tgaW(wchar_t const *filename, int x, int y, int comp, const void *data)
{
   FILE *f = stbi__wfopen_wb(filename);
   int result;
   if (!f) return 0;
   result = stbi_write_tga_to_file(f, x, y, comp, data);
   fclose(f);
   return result;
}

int stbi_write_hdrW(wchar_t const *filename, int x, int y, int comp, const float *data)
{
   FILE *f = stbi__wfopen_wb(filename);
   int result;
   if (!f) return 0;
   result = stbi_write_hdr_to_file(f, x, y, comp, data);
   fclose(f);
   return result;
}

int stbi_write_pngW(wchar_t const *filename, int x, int y, int comp, const void *data, int stride_bytes)
{
   FILE *f = stbi__wfopen_wb(filename);
   int result;
   if (!f) return 0;
   result = stbi_write_png_to_file(f, x, y, comp, data, stride_bytes);
   fclose(f);
   return result;
}

int stbi_write_jpgW(wchar_t const *filename, int x, int y, int comp, const void *data, int quality)
{
   FILE *f = stbi__wfopen_wb(filename);
   int result;
   if (!f) return 0;
   result = stbi_write_jpg_to_file(f, x, y, comp, data, quality);
   fclose(f);
   return result;
}

int wmain(int argc, wchar_t **argv)
{
   int w,h;
   int i, n;

   printf("test wchar edition\n");
   if (argc <= 1) {
	   printf("%ls [filename] ...\n", argv[0]);
	   return 0;
   }

   for (i=1; i < argc; ++i) {
	   const wchar_t *fn_src = argv[i];
	   int res;
	   int w2,h2,n2;
	   unsigned char *data;
	   wprintf(L"%s\n", fn_src);
	   res = stbi_infoW(fn_src, &w2, &h2, &n2);
	   data = stbi_loadW(fn_src, &w, &h, &n, 4); if (data) free(data); else printf("Failed &n\n");
	   data = stbi_loadW(fn_src, &w, &h,  0, 1); if (data) free(data); else printf("Failed 1\n");
	   data = stbi_loadW(fn_src, &w, &h,  0, 2); if (data) free(data); else printf("Failed 2\n");
	   data = stbi_loadW(fn_src, &w, &h,  0, 3); if (data) free(data); else printf("Failed 3\n");
	   data = stbi_loadW(fn_src, &w, &h, &n, 4);
	   assert(data);
	   assert(w == w2 && h == h2 && n == n2);
	   assert(res);
	   if (data) {
		   wchar_t fname[512];
		   wchar_t *p = wcsrchr(fn_src, L'\\');
		   if (p == NULL) p = wcsrchr(fn_src, L'/');
		   p++;
		   wcscpy(fname, p);
		   p = wcsrchr(fname, L'.');
		   *p = L'\0';
		   const wchar_t *fn_out = fname;
		   wchar_t fnamep[512];
		   swprintf(fnamep, sizeof(fnamep), L"output/%s.png", fn_out);
		   stbi_write_pngW(fnamep, w, h, 4, data, w*4);
		   swprintf(fnamep, sizeof(fnamep), L"output/%s.bmp", fn_out);
		   stbi_write_bmpW(fnamep, w, h, 4, data);
		   swprintf(fnamep, sizeof(fnamep), L"output/%s.tga", fn_out);
		   stbi_write_tgaW(fnamep, w, h, 4, data);
		   swprintf(fnamep, sizeof(fnamep), L"output/%s.jpg", fn_out);
		   stbi_write_jpgW(fnamep, w, h, 4, data, 90);
		   free(data);
	   } else
		   printf("FAILED 4\n");
   }
}

