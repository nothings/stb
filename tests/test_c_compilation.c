#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"

#define STB_PERLIN_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_C_LEXER_IMPLEMENTATIOn
#define STB_DIVIDE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_HERRINGBONE_WANG_TILE_IMEPLEMENTATIOn
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_VOXEL_RENDER_IMPLEMENTATION
#define STB_EASY_FONT_IMPLEMENTATION
#define STB_DXT_IMPLEMENTATION
#define STB_INCLUDE_IMPLEMENTATION

#include "stb_herringbone_wang_tile.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_perlin.h"
#include "stb_c_lexer.h"
#include "stb_divide.h"
#include "stb_image_resize.h"
#include "stb_rect_pack.h"
#include "stb_dxt.h"
#include "stb_include.h"

#include "stb_ds.h"

#define STBVOX_CONFIG_MODE 1
#include "stb_voxel_render.h"

void STBTE_DRAW_RECT(int x0, int y0, int x1, int y1, unsigned int color)
{
}

void STBTE_DRAW_TILE(int x0, int y0, unsigned short id, int highlight, float *data)
{
}

#define STB_TILEMAP_EDITOR_IMPLEMENTATION
//#include "stb_tilemap_editor.h"   // @TODO: it's broken

int quicktest(void)
{
   char buffer[999];
   stbsp_sprintf(buffer, "test%%test");
   return 0;
}