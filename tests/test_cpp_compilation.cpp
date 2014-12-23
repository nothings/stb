#define STB_TRUETYPE_IMPLEMENTATION
#define STB_PERLIN_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_DXT_IMPLEMENATION
#define STB_C_LEXER_IMPLEMENTATIOn
#define STB_DIVIDE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_HERRINGBONE_WANG_TILE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION

#define STBI_MALLOC     my_malloc
#define STBI_FREE       my_free
#define STBI_REALLOC    my_realloc

void *my_malloc(size_t) { return 0; }
void *my_realloc(void *, size_t) { return 0; }
void my_free(void *) { }

#include "stb_image.h"
#include "stb_rect_pack.h"
#include "stb_truetype.h"
#include "stb_image_write.h"
#include "stb_perlin.h"
#include "stb_dxt.h"
#include "stb_c_lexer.h"
#include "stb_divide.h"
#include "stb_herringbone_wang_tile.h"

#define STBTE_DRAW_RECT(x0,y0,x1,y1,color)      do ; while(0)
#define STBTE_DRAW_TILE(x,y,id,highlight,data)  do ; while(0)
#define STB_TILEMAP_EDITOR_IMPLEMENTATION
#include "stb_tilemap_editor.h"
