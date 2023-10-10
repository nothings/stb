#define STB_IMAGE_WRITE_STATIC
#define STBIWDEF static inline

#include "stb_image.h"
#include "stb_rect_pack.h"
#include "stb_truetype.h"
#include "stb_image_write.h"
#include "stb_c_lexer.h"
#include "stb_perlin.h"
#include "stb_dxt.h"
#include "stb_divide.h"
#include "stb_herringbone_wang_tile.h"
#include "stb_ds.h"
#include "stb_hexwave.h"

#include "stb_sprintf.h"
#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"


#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_PERLIN_IMPLEMENTATION
#define STB_DXT_IMPLEMENATION
#define STB_C_LEXER_IMPLEMENTATIOn
#define STB_DIVIDE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_HERRINGBONE_WANG_TILE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_VOXEL_RENDER_IMPLEMENTATION
#define STB_CONNECTED_COMPONENTS_IMPLEMENTATION
#define STB_HEXWAVE_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#define STBDS_UNIT_TESTS

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
#include "stb_divide.h"
#include "stb_herringbone_wang_tile.h"
#include "stb_ds.h"
#include "stb_hexwave.h"

#define STBCC_GRID_COUNT_X_LOG2  10
#define STBCC_GRID_COUNT_Y_LOG2  10
#include "stb_connected_components.h"

#define STBVOX_CONFIG_MODE 1
#include "stb_voxel_render.h"

#define STBTE_DRAW_RECT(x0,y0,x1,y1,color)      do ; while(0)
#define STBTE_DRAW_TILE(x,y,id,highlight,data)  do ; while(0)
#define STB_TILEMAP_EDITOR_IMPLEMENTATION
#include "stb_tilemap_editor.h"

#include "stb_easy_font.h"

#define STB_LEAKCHECK_IMPLEMENTATION
#include "stb_leakcheck.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

//#include "stretchy_buffer.h"  // deprecating


// avoid unused-function complaints
void dummy2(void)
{
   stb_easy_font_spacing(1.0);
   stb_easy_font_print(0,0,NULL,NULL,NULL,0);
   stb_easy_font_width(NULL);
   stb_easy_font_height(NULL);
}


////////////////////////////////////////////////////////////
//
// text edit

#include <stdlib.h>
#include <string.h> // memmove
#include <ctype.h>  // isspace

#define STB_TEXTEDIT_CHARTYPE   char
#define STB_TEXTEDIT_STRING     text_control

// get the base type
#include "stb_textedit.h"

// define our editor structure
typedef struct
{
   char *string;
   int stringlen;
   STB_TexteditState state;
} text_control;

// define the functions we need
void layout_func(StbTexteditRow *row, STB_TEXTEDIT_STRING *str, int start_i)
{
   int remaining_chars = str->stringlen - start_i;
   row->num_chars = remaining_chars > 20 ? 20 : remaining_chars; // should do real word wrap here
   row->x0 = 0;
   row->x1 = 20; // need to account for actual size of characters
   row->baseline_y_delta = 1.25;
   row->ymin = -1;
   row->ymax =  0;
}

int delete_chars(STB_TEXTEDIT_STRING *str, int pos, int num)
{
   memmove(&str->string[pos], &str->string[pos+num], str->stringlen - (pos+num));
   str->stringlen -= num;
   return 1; // always succeeds
}

int insert_chars(STB_TEXTEDIT_STRING *str, int pos, STB_TEXTEDIT_CHARTYPE *newtext, int num)
{
   str->string = (char *) realloc(str->string, str->stringlen + num);
   memmove(&str->string[pos+num], &str->string[pos], str->stringlen - pos);
   memcpy(&str->string[pos], newtext, num);
   str->stringlen += num;
   return 1; // always succeeds
}

// define all the #defines needed 

#define KEYDOWN_BIT                    0x40000000

#define STB_TEXTEDIT_STRINGLEN(tc)     ((tc)->stringlen)
#define STB_TEXTEDIT_LAYOUTROW         layout_func
#define STB_TEXTEDIT_GETWIDTH(tc,n,i)  (1) // quick hack for monospaced
#define STB_TEXTEDIT_KEYTOTEXT(key)    (((key) & KEYDOWN_BIT) ? 0 : (key))
#define STB_TEXTEDIT_GETCHAR(tc,i)     ((tc)->string[i])
#define STB_TEXTEDIT_NEWLINE           '\n'
#define STB_TEXTEDIT_IS_SPACE(ch)      isspace(ch)
#define STB_TEXTEDIT_DELETECHARS       delete_chars
#define STB_TEXTEDIT_INSERTCHARS       insert_chars

#define STB_TEXTEDIT_K_SHIFT           0x20000000
#define STB_TEXTEDIT_K_CONTROL         0x10000000
#define STB_TEXTEDIT_K_LEFT            (KEYDOWN_BIT | 1) // actually use VK_LEFT, SDLK_LEFT, etc
#define STB_TEXTEDIT_K_RIGHT           (KEYDOWN_BIT | 2) // VK_RIGHT
#define STB_TEXTEDIT_K_UP              (KEYDOWN_BIT | 3) // VK_UP
#define STB_TEXTEDIT_K_DOWN            (KEYDOWN_BIT | 4) // VK_DOWN
#define STB_TEXTEDIT_K_LINESTART       (KEYDOWN_BIT | 5) // VK_HOME
#define STB_TEXTEDIT_K_LINEEND         (KEYDOWN_BIT | 6) // VK_END
#define STB_TEXTEDIT_K_TEXTSTART       (STB_TEXTEDIT_K_LINESTART | STB_TEXTEDIT_K_CONTROL)
#define STB_TEXTEDIT_K_TEXTEND         (STB_TEXTEDIT_K_LINEEND   | STB_TEXTEDIT_K_CONTROL)
#define STB_TEXTEDIT_K_DELETE          (KEYDOWN_BIT | 7) // VK_DELETE
#define STB_TEXTEDIT_K_BACKSPACE       (KEYDOWN_BIT | 8) // VK_BACKSPACE
#define STB_TEXTEDIT_K_UNDO            (KEYDOWN_BIT | STB_TEXTEDIT_K_CONTROL | 'z')
#define STB_TEXTEDIT_K_REDO            (KEYDOWN_BIT | STB_TEXTEDIT_K_CONTROL | 'y')
#define STB_TEXTEDIT_K_INSERT          (KEYDOWN_BIT | 9) // VK_INSERT
#define STB_TEXTEDIT_K_WORDLEFT        (STB_TEXTEDIT_K_LEFT  | STB_TEXTEDIT_K_CONTROL)
#define STB_TEXTEDIT_K_WORDRIGHT       (STB_TEXTEDIT_K_RIGHT | STB_TEXTEDIT_K_CONTROL)
#define STB_TEXTEDIT_K_PGUP            (KEYDOWN_BIT | 10) // VK_PGUP -- not implemented
#define STB_TEXTEDIT_K_PGDOWN          (KEYDOWN_BIT | 11) // VK_PGDOWN -- not implemented

#define STB_TEXTEDIT_IMPLEMENTATION
#include "stb_textedit.h"


void dummy3(void)
{
  stb_textedit_click(0,0,0,0);
  stb_textedit_drag(0,0,0,0);
  stb_textedit_cut(0,0);
  stb_textedit_key(0,0,0);
  stb_textedit_initialize_state(0,0);
  stb_textedit_paste(0,0,0,0);
}

#include "stb_c_lexer.h"
