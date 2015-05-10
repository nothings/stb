/*
stb_gl2d_render.h - v0.1 - public domain - Dmitry Ivanov, May 2015
the most simplest render ever, based on OpenGL 1.1 only

--------------------------------------------------------------- motivation

While working on my hobby project I realized that I need to create
yet another 2d renderer. It was impossible to use existing libraries because
my project is about working tightly with compositing window manager,
and most other libraries take control of this part of code.

Also I've figured how much code you need to write simple 2d renderer nowadays :
- shaders
- vertex structure
- matrices
- etc

Yet another concern was that windows only supply OpenGL 1.1 header by default,
and all other functions one need to get through bulky extensions getter.

So combining everything together I've decided to create the most simple
2d renderer ever and make it as thin and small as possible.

API is based on subset of love.graphics module from love2d
(see https://love2d.org/wiki/love.graphics)
Code style : tab = 4 spaces, column at 80

--------------------------------------------------------------- example

// includes
#ifdef _WIN32
#include <windows.h>
#include <gl/GL.h>
#include <stb_gl2d_render.h>
#else
...
#endif

// init
unsigned int img = load_img(img, img_w, img_h, rgba8888);

// reder
set_viewport(0, 0, width, height);
setcolorx(0x40404000); // fill with gray
clear();
set_colorx(-1); // white
draw(img); // center of image will be rendered in the center of the viewport

--------------------------------------------------------------- todo

- use less opengl functions (glMatrixMode, glOrtho, etc)
- provide Direct2D/3D implementations
- provide OpenGL 4+ / OpenGL ES 2+ implementations

*/

#ifndef STB_INCLUDE_STB_GL2D_RENDER_H
#define STB_INCLUDE_STB_GL2D_RENDER_H

// ------------------------------------------------------------ declarations

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	rgba8888	= 0,
	rgb888		= 1
} pixel_format_t;

typedef enum
{
	blend_disabled			= 0,
	blend_additive			= 1,
	blend_alpha				= 2,
	blend_multiplicative	= 3
} blend_t;

// use default values for C++ version
#ifdef __cplusplus
#define ARG_DEF(value) = value
#else
#define ARG_DEF(value)
#endif

unsigned int load_img(const void * data,
				unsigned short w, unsigned short h,
				pixel_format_t format,
				unsigned char use_min_linear ARG_DEF(0),
				unsigned char use_mag_linear ARG_DEF(0));
void free_img(unsigned int id);
void set_viewport(int x, int y, int w, int h);
void set_blend(blend_t blend);
void set_color(float r, float g, float b, float a);
void set_colori(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a);
void set_colorx(unsigned int rgba8888);
void clear();
void draw(unsigned int img, float x ARG_DEF(0.0f), float y ARG_DEF(0.0f),
		  float r_deg ARG_DEF(0.0f),
		  float sx ARG_DEF(1.0f), float sy ARG_DEF(1.0f),
		  float ox ARG_DEF(0.0f), float oy ARG_DEF(0.0f));

#undef ARG_DEF

#ifdef __cplusplus
}
#endif

// ------------------------------------------------------------ implementation

#ifdef STB_GL2D_RENDER_IMPLEMENTATION

#ifndef STB_GL2D_API
#define STB_GL2D_API static
#endif

// current color
STB_GL2D_API float stb_gl2d_color_r = 1.0f, stb_gl2d_color_g = 1.0f,
				   stb_gl2d_color_b = 1.0f, stb_gl2d_color_a = 1.0f;


STB_GL2D_API unsigned int load_img(const void * data,
				unsigned short w, unsigned short h,
				pixel_format_t format,
				unsigned char use_min_linear,
				unsigned char use_mag_linear)
{
	const GLenum internal_formats[][3] =
	{
		{GL_RGBA8,	GL_RGBA,	GL_UNSIGNED_BYTE}, // rgba8888
		{GL_RGB8,	GL_RGB,		GL_UNSIGNED_BYTE}  // rgb888
	};

	GLuint texture = 0;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					use_min_linear ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
					use_mag_linear ? GL_LINEAR : GL_NEAREST);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_formats[format][0], w, h, 0,
				internal_formats[format][1], internal_formats[format][2], data);
	return texture;
}

STB_GL2D_API void free_img(unsigned int id)
{
	glDeleteTextures(1, &id);
}

STB_GL2D_API void set_viewport(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x - w / 2.0f, x + w / 2.0f,
			y - h / 2.0f, y + h / 2.0f,
			-1.0f, 1.0f);
}

STB_GL2D_API void set_blend(blend_t blend)
{
	const GLenum blend_func[][2] =
	{
		{GL_NONE,		GL_NONE},					// blend_disabled
		{GL_ONE,		GL_ONE},					// blend_additive
		{GL_SRC_ALPHA,	GL_ONE_MINUS_SRC_ALPHA},	// blend_alpha
		{GL_DST_COLOR,	GL_ZERO},					// blend_multiplicative
	};

	if(blend == blend_disabled)
		glDisable(GL_BLEND);
	else
	{
		glEnable(GL_BLEND);
		glBlendFunc(blend_func[blend][0], blend_func[blend][1]);
	}
}

STB_GL2D_API void set_color(float r, float g, float b, float a)
{
	stb_gl2d_color_r = r; stb_gl2d_color_g = g;
	stb_gl2d_color_b = b; stb_gl2d_color_a = a;
	glColor4f(r, g, b, a);
}

STB_GL2D_API void set_colori(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a)
{
	set_color((float)r / 255.0f, (float)g / 255.0f,
			  (float)b / 255.0f, (float)a / 255.0f);
}

STB_GL2D_API void set_colorx(unsigned int rgba8888)
{
	set_colori((rgba8888 >> 24) & 0xff, (rgba8888 >> 16) & 0xff,
			   (rgba8888 >> 8) & 0xff, (rgba8888) & 0xff);
}

STB_GL2D_API void clear()
{
	glClearColor(stb_gl2d_color_r, stb_gl2d_color_g,
				 stb_gl2d_color_b, stb_gl2d_color_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

STB_GL2D_API void draw(unsigned int img, float x, float y, float r_deg,
		  float sx, float sy, float ox, float oy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	glRotatef(r_deg, 0.0f, 0.0f, -1.0f);
	glScalef(sx, sy, 0.0f);

	glBindTexture(GL_TEXTURE_2D, (GLuint)img);
	glEnable(GL_TEXTURE_2D);

	int w, h;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
	float w2 = (float)w / 2.0f, h2 = (float)h / 2.0f;

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( w2 - ox,  h2 - oy, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w2 - ox,  h2 - oy, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-w2 - ox, -h2 - oy, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( w2 - ox, -h2 - oy, 0.0f);
	glEnd();
}

#endif
#endif
