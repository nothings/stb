// stb_gl2d_render.h - v0.1 - public domain - Dmitry Ivanov, Mat 2015
// The most simplest render ever, using OpenGL 1.1 only
// TODO

#ifndef STB_INCLUDE_STB_GL2D_RENDER_H
#define STB_INCLUDE_STB_GL2D_RENDER_H

#ifdef STB_GL2D_RENDER_IMPLEMENTATION

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

unsigned int load_img(const void * data,
				unsigned short w, unsigned short h,
				pixel_format_t format,
				unsigned char use_min_linear,
				unsigned char use_mag_linear);
void free_img(unsigned int id);
void set_viewport(int x, int y, int w, int h);
void set_blend(blend_t blend);
void set_color(float r, float g, float b, float a);
void set_colori(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a);
void set_colorx(unsigned int rgba8888);
void clear();
void draw(unsigned int img, float x, float y, float r,
		  float sx, float sy, float ox, float oy);

static unsigned int load_img(const void * data,
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

static void free_img(unsigned int id)
{
	glDeleteTextures(1, &id);
}

static void set_viewport(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x - w / 2.0f, x + w / 2.0f,
			y - h / 2.0f, y + h / 2.0f,
			-1.0f, 1.0f);
}

static void set_blend(blend_t blend)
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

static float color_r = 1.0f, color_g = 1.0f, color_b = 1.0f, color_a = 1.0f;

static void set_color(float r, float g, float b, float a)
{
	color_r = r; color_g = g; color_b = b; color_a = a;
	glColor4f(r, g, b, a);
}

static void set_colori(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a)
{
	set_color((float)r / 255.0f, (float)g / 255.0f,
			  (float)b / 255.0f, (float)a / 255.0f);
}

static void set_colorx(unsigned int rgba8888)
{
	set_colori((rgba8888 >> 24) & 0xff, (rgba8888 >> 16) & 0xff,
			   (rgba8888 >> 8) & 0xff, (rgba8888) & 0xff);
}

static void clear()
{
	glClearColor(color_r, color_g, color_b, color_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

static void draw(unsigned int img, float x, float y, float r,
		  float sx, float sy, float ox, float oy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	glRotatef(r, 0.0f, 0.0f, -1.0f);
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
