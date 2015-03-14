// @TODO
//
//   - compute full set of texture normals
//   - switch to #ifdef
//   - premultiplied alpha
//   - edge clamp
//   - gather vertex lighting from slopes correctly
//   - better support texture edge_clamp: explicitly mod texcoords by 1, use textureGrad to avoid
//     mipmap articats. Need to do compute texcoords in vertex shader, offset towards
//     center before modding, need 2 bits per vertex to know offset direction (is implicit
//     implicit for modes without vertex data)
//   - add 10-byte quad type (loses per-face tex1/tex2 blend mode)
//   - add 6-byte quad type (loses baked ao, most geometry, flags, texlerp)
//   - add 4-byte quad type (only texture or only color, no baked light, no recolor)


// stb_voxel_render.h - 0.01 - Sean Barrett, 2015
//
// This library helps render large "voxel" worlds for games,
// in this case one with blocks that can have textures and that
// can also be a few shapes other than cubes.
//
// It works by traditional rasterization, rendering the world
// as triangles.
//
// It provides:
//
//    1. a compact vertex data format (10-20 bytes per quad) to
//       allow large view distances while still allowing a lot
//       per-voxel variety and per-game/app variation
//    2. conversion from voxel data structure to vertex mesh
//    3. vertex & pixel shader
//    4. assistance in setting up shader state
//    5. planned support for more compact vertex data formats
//       (4-6 bytes per quad) with more limited features.
//
// Although most of it is designed to be API-agnostic, the shaders
// are currently only in GLSL; the HLSL port will be along soon when
// someone else writes it.
//
//
// USAGE:
//
//   #define the symbol STB_VOXEL_RENDER_IMPLEMENTATION in *one*
//   C/C++ file before the #include of this file; the impleemtnation
//   will be generated in that file.
//
//   If you define the symbols STB_VOXEL_RENDER_STATIC, then the
//   implementation will be private to that file.
//
//
// FEATURE SET:
//
//     - voxels are mostly just cubes, but there is also
//       support for half-height cubes and diagonal slopes,
//       and half-height diagonals and even odder shapes
//       for doing more-continuous "ground".
//
//     - you can choose textured blocks or solid-colored voxels
//
//     - if textured, each face specifies a base texture, chosen from
//       up to 256 textures stored in a texture array. All the textures
//       have be the same dimensions, but each texture can choose its
//       scale: it can repeat every block, or it can be finer (e.g.
//       repeat four times per block) or coarser (e.g. cover 4x4
//       blocks).
//
//       Texture coordinates are projections along one of the major
//       axes.
//
//     - a secondary texture: chosen from another set of 256 textures
//       (or the same set, if you choose), which have all the same
//       properties as above. these textures can be used to as
//       detail textures, to apply decals, or to have lightmapping
//       effects.
//
//     - each face gets one of 64 colors; per face, this can modulate
//       the primary texture, the secondary texture, or both.
//
//     - if you disable textures, then each face gets a 24-bit rgb color
//
//     - per face, you choose whether the secondary texture is
//       alpha composited onto the first texture, or multiplies
//       it (scaled up by 2, which can be used so that detail
//       textures don't darken on average). 
//
//     - per vertex, you choose an extra alpha that controls the
//       degree to which the secondary texture affects the primary;
//       for example, this can be used to soften effects locally,
//       or if both textures come from the same source, to transition
//       between two textures
//
//     - each vertex of each face computes a separate "lighting"
//       value. this is typically essentially an ambient lighting
//       value, which can be ambient occlusion, or baked local
//       lighting, or etc.
//
//     - per-pixel lighting is computed using a face normal and
//       a single directional light combined with the baked occlusion.
//
//     - per-face you can mark the face as being "fullbright",
//       in which case it is drawn without any lighting faces
//       (e.g. it's an emissive texture)
//
//     - you can install a custom lighting function that takes the
//       face normal & albedo color as input plus whatever uniforms
//       you want.
//
//     - the library generally takes care of coordinating the vertex
//       format with the meshdata for you.
//
//
// VOXEL MESH API
//
// Context
//
//   To understand the API, make sure you first understand the feature set
//   listed above.
//
//   Because the vertices are compact, they have very limited spatial
//   precision. Thus a single mesh can only contain the data for a limited
//   area. To make very large voxel maps, you'll need to build multiple
//   vertex buffers. (But you want this anyway for frustum culling.)
//
//   Each generated mesh has three components:
//           - vertex data (vertex buffer)
//           - face data (optional, stored in texture buffer)
//           - mesh transform (uniforms)
//
//   Once you've generated the mesh with this library, it's up to you
//   to upload it to the GPU, to keep track of the state, and to render
//   it.
//
// Concept
//
//   The basic design is that you pass in one or more 3D arrays; each array
//   is (typically) one-byte-per-voxel and contains information about one
//   or more properties of the voxel particular property.
//
//   Because there is so much per-vertex and per-face data possible
//   in the output, and each voxel can have 6 faces and 8 faces, it
//   would require an impossible large data structure to describe all
//   of the possibilities. Instead, the API provides multiple ways
//   to express each property; each such way has some limitations on
//   what it can express. For the extreme case where you want to control
//   every aspect manually, there is the option to pass in "sparse data",
//   where you only pass in data for voxels that affect rendering (but
//   in this case you could nearly build the mesh yourself).
//
//
// HISTORY:
//
//   zmc engine 96-byte quads      :  2011/10
//   zmc engine 32-byte quads      :  2013/12
//   stb_voxel_render 20-byte quads:  2015/01
//   stb_voxel_render 4..14 bytes  :  2015/02???




// 

#ifndef STBVOX_MODE
#define STBVOX_MODE 0
#endif

// The following are candidate voxel modes. Only modes 0, 1, and 20 are
// currently implemented. Reducing the storage-per-quad further
// shouldn't improve performance, although obviously it allow you
// to create larger worlds without streaming.
//
//        
//            Mode:     0     1     2     3     4     5     6       10    11    12       20    21    22    23
// ============================================================================================================
//  uses Tex Buffer     n     Y     Y     Y     Y     Y     Y        Y     Y     Y        Y     Y     Y     Y
//   bytes per quad    32    20    14    12    10     6     6        8     6     4       20    10     6     4
//       non-blocks   all   all   some  some  some slabs stairs    some  some  none     all  slabs slabs  none
//             tex1   256   256   256   256   256   256   256      256   256   256        n     n     n     n
//             tex2   256   256   256   256   256   256   128        n     n     n        n     n     n     n
//           colors    64    64    64    64    64    64    64        8     n     n      2^24  2^24  2^24  256
//        vertex ao     Y     Y     Y     Y     Y     n     n        Y     Y     n        Y     Y     n     n
//    face texblend     Y     Y     Y     Y     n     n     n        -     -     -        -     -     -     -
//   vertex texlerp     Y     Y     Y     n     n     n     n        -     -     -        -     -     -     -
//      x&y extents   127   127   128    64    64   128    64       64   128   128       64    64   128   128
//        z extents   255   255   128   128   128    64    64       32    64   128       64    64    64   128
//
//
// With TexBuffer for the fixed vertex data, we can actually do
// minecrafty non-blocks like stairs -- we still probably only
// want 256 or so, so we can't do the equivalent of all the vheight
// combos, but that's ok. The 256 includes baked rotations, but only
// some of them need it, and lots of block types share some faces.
//
// mode 5 (6 bytes):   mode 6 (6 bytes)
//   x:7                x:6
//   y:7                y:6
//   z:6                z:6
//   tex1:8             tex1:8
//   tex2:8             tex2:7
//   color:8            color:8
//   face:4             face:7
//
//
//  side faces (all x4)        top&bottom faces (2x)    internal faces (1x)
//     1  regular                1 regular
//     2  slabs                                             2
//     8  stairs                 4 stairs                  16
//     4  diag side                                         8
//     4  upper diag side                                   8
//     4  lower diag side                                   8
//                                                          4 crossed pairs
//
//    23*4                   +   5*4                    +  46
//  == 92 + 20 + 46 = 158
//
//   Must drop 30 of them to fit in 7 bits:
//       ceiling half diagonals: 16+8 = 24
//   Need to get rid of 6 more.
//       ceiling diagonals: 8+4 = 12
//   This brings it to 122, so can add a crossed-pair variant.
//       (diagonal and non-diagonal, or randomly offset)
//   Or carpet, which would be 5 more.
//
//
// Mode 4 (10 bytes):
//  v:  z:2,light:6
//  f:  x:6,y:6,z:7, t1:8,t2:8,c:8,f:5
//
// Mode ? (10 bytes)
//  v:  xyz:5 (27 values), light:3
//  f:  x:7,y:7,z:6, t1:8,t2:8,c:8,f:4
// (v:  x:2,y:2,z:2,light:2)


#ifndef INCLUDE_STB_VOXEL_RENDER_H
#define INCLUDE_STB_VOXEL_RENDER_H

#include <stdlib.h>

#ifdef STBVOX_BLOCKTYPE_SHORT
typedef unsigned short stbvox_block_type;
#else
typedef unsigned char stbvox_block_type;
#endif

// rendering API

enum
{
   STBVOX_UNIFORM_face_data,
   STBVOX_UNIFORM_transform,

   STBVOX_UNIFORM_tex_array,
   STBVOX_UNIFORM_texscale,

   STBVOX_UNIFORM_color_table,

   STBVOX_UNIFORM_normals,
   STBVOX_UNIFORM_texgen,

   STBVOX_UNIFORM_ambient,
   STBVOX_UNIFORM_camera_pos,

   STBVOX_UNIFORM_count,
};

enum
{
   STBVOX_UNIFORM_TYPE_none,
   STBVOX_UNIFORM_TYPE_sampler,
   STBVOX_UNIFORM_TYPE_vec2,
   STBVOX_UNIFORM_TYPE_vec3,
   STBVOX_UNIFORM_TYPE_vec4,
};

typedef struct
{
   int type;
   int bytes_per_element;
   int array_length;
   char *name;
   float *default_value; // if not NULL, you can use this as the uniform
   unsigned int tags;
} stbvox_uniform_info;

typedef struct stbvox_mesh_maker stbvox_mesh_maker;
typedef struct stbvox_input_description stbvox_input_description;

extern stbvox_uniform_info *stbvox_get_uniform_info(stbvox_mesh_maker *mm, int uniform);
extern void stbvox_init_mesh_maker(stbvox_mesh_maker *mm);
extern int stbvox_make_mesh(stbvox_mesh_maker *mm);
extern int stbvox_get_buffer_count(stbvox_mesh_maker *mm);
extern int stbvox_get_buffer_size_per_quad(stbvox_mesh_maker *mm, int n);
extern void stbvox_reset_buffers(stbvox_mesh_maker *mm);
extern void stbvox_set_buffer(stbvox_mesh_maker *mm, int mesh, int slot, void *buffer, size_t len);
extern void stbvox_set_input_range(stbvox_mesh_maker *mm, int x0, int y0, int z0, int x1, int y1, int z1);
extern void stbvox_set_input_stride(stbvox_mesh_maker *mm, int x_stride_in_bytes, int y_stride_in_bytes);
extern void stbvox_config_use_gl(stbvox_mesh_maker *mm, int use_tex_buffer, int use_gl_modelview);
extern void stbvox_config_set_z_precision(stbvox_mesh_maker *mm, int z_fractional_bits);
extern stbvox_input_description *stbvox_get_input_description(stbvox_mesh_maker *mm);
extern int stbvox_get_vertex_shader(stbvox_mesh_maker *mm, char *buffer, size_t buffer_size);
extern int stbvox_get_fragment_shader(stbvox_mesh_maker *mm, char *buffer, size_t buffer_size);
extern void stbvox_set_default_mesh(stbvox_mesh_maker *mm, int mesh);
extern int stbvox_get_quad_count(stbvox_mesh_maker *mm, int mesh);
extern void stbvox_get_transform(stbvox_mesh_maker *mm, float transform[3][3]);
extern void stbvox_get_bounds(stbvox_mesh_maker *mm, float bounds[2][3]);
extern void stbvox_set_mesh_coordinates(stbvox_mesh_maker *mm, int x, int y, int z);

// meshing API

enum
{
   STBVOX_GEOM_empty,
   STBVOX_GEOM_knockout,  // creates a hole in the mesh
   STBVOX_GEOM_solid,
   STBVOX_GEOM_transp,    // solid geometry, but transparent contents so neighbors generate normally, unless same blocktype

   // following 4 are redundant to vheight, but allowing them as well makes shared vheight more effective
   STBVOX_GEOM_slab_upper,
   STBVOX_GEOM_slab_lower,
   STBVOX_GEOM_floor_slope_north_is_top,
   STBVOX_GEOM_ceil_slope_north_is_bottom,

   STBVOX_GEOM_floor_slope_north_is_top_as_wall_UNIMPLEMENTED,   // same as floor_slope below, but uses wall's texture & texture projection
   STBVOX_GEOM_ceil_slope_north_is_bottom_as_wall_UNIMPLEMENTED,
   STBVOX_GEOM_crossed_pair,                       // corner-to-corner pairs, with normal vector bumped upwards
   STBVOX_GEOM_force,                              // all faces always visible, e.g. minecraft fancy leaves

   // these access vheight input
   STBVOX_GEOM_floor_vheight_02 = 12,  // diagonal is SW-NE -- assuming index buffer 0,1,2,0,2,3
   STBVOX_GEOM_floor_vheight_13,       // diagonal is SE-NW -- assuming index buffer 0,1,2,0,2,3
   STBVOX_GEOM_ceil_vheight_02,
   STBVOX_GEOM_ceil_vheight_13,

   STBVOX_GEOM_count, // number of geom cases
};
// TODO: could possibly add stairs, fences, etc, but they don't obey
// the "1 quad per face" rule and they need more precision, so they'd
// have to be built very differently; so I don't plan on doing anything
// like that.

enum
{
   STBVOX_VERTEX_HEIGHT_0,
   STBVOX_VERTEX_HEIGHT_half,
   STBVOX_VERTEX_HEIGHT_1,
};

enum
{
   STBVOX_TEXLERP_0,
   STBVOX_TEXLERP_half,
   STBVOX_TEXLERP_1,
   STBVOX_TEXLERP_use_vert,
};

enum
{
   STBVOX_TEXLERP4_0_8,
   STBVOX_TEXLERP4_1_8,
   STBVOX_TEXLERP4_2_8,
   STBVOX_TEXLERP4_3_8,
   STBVOX_TEXLERP4_4_8,
   STBVOX_TEXLERP4_5_8,
   STBVOX_TEXLERP4_6_8,
   STBVOX_TEXLERP4_7_8,

   STBVOX_TEXLERP4_use_vert=15,
};

enum
{
   STBVOX_FACE_east,
   STBVOX_FACE_north,
   STBVOX_FACE_west,
   STBVOX_FACE_south,
   STBVOX_FACE_up,
   STBVOX_FACE_down,

   STBVOX_FACE__count,
};


#define STBVOX_BLOCKTYPE_EMPTY    0

#ifdef STBVOX_BLOCKTYPE_SHORT
#define STBVOX_BLOCKTYPE_HOLE  65535
#else
#define STBVOX_BLOCKTYPE_HOLE    255
#endif

#define STBVOX_MAKE_GEOMETRY(geom, rotate, vheight) ((geom) + (rotate)*16 + (vheight)*64)
#define STBVOX_MAKE_VHEIGHT(v_sw, v_se, v_nw, v_ne) ((v_sw) + (v_se)*4 + (v_nw)*16 + (v_ne)*64)
#define STBVOX_MAKE_MATROT(block, overlay, tex2, color)  ((block) + (overlay)*4 + (tex2)*16 + (color)*64)
#define STBVOX_MAKE_TEX2_REPLACE(tex2, tex2_replace_face) ((tex2) + ((tex2_replace_face) & 3)*64)
#define STBVOX_MAKE_TEXLERP(ns2, ew2, ud2, vert)  ((ew2) + (ns2)*4 + (ud2)*16 + (vert)*64)
#define STBVOX_MAKE_TEXLERP1(vert,e2,n2,w2,s2,u4,d2) STBVOX_MAKE_TEXLERP(s2, w2, d2, vert)
#define STBVOX_MAKE_TEXLERP2(vert,e2,n2,w2,s2,u4,d2) ((u2)*16 + (n2)*4 + (s2))
#define STBVOX_MAKE_FACE_MASK(e,n,w,s,u,d)  ((e)+(n)*2+(w)*4+(s)*8+(u)*16+(d)*32)

#ifdef STBVOX_ROTATION_IN_LIGHTING
#define STBVOX_MAKE_LIGHTING(lighting, rot)  (((lighting)&~3)+(rot))
#else
#define STBVOX_MAKE_LIGHTING(lighting)       (lighting)
#endif

#ifndef STBVOX_MAX_MESHES
#define STBVOX_MAX_MESHES      2           // opaque & transparent
#endif

#define STBVOX_MAX_MESH_SLOTS  3           // one vertex & two faces, or two vertex and one face

struct stbvox_input_description
{
   unsigned char lighting_at_vertices;     // default is lighting values at block center

   // these are 3D maps you use to define your voxel world, using x_stride and y_stride
   // note that for cache efficiency, you want to use the block_foo palettes as much as possible instead
   stbvox_block_type *blocktype;           // index into palettes listed below
   unsigned char *overlay;                 // index into palettes listed below
   unsigned char *selector;                // raw selector (chooses which mesh to write to)
   unsigned char *geometry;                // STBVOX_MAKE_GEOMETRY   -- geom:4, rot:2, vheight:2
   unsigned char *rotate;                  // STBVOX_MAKE_MATROT     -- block:2, overlay:2, tex2:2, color:2
   unsigned char *tex2;                    // raw tex2 value to use on all sides of block
   unsigned char *tex2_replace;            // STBVOX_MAKE_TEX2_REPLACE --  tex2:6, face_1:2
   unsigned char *tex2_facemask;           // facemask:6 (use all bits of tex2_replace as texture)
   unsigned char *vheight;                 // STBVOX_MAKE_VHEIGHT   -- sw:2, se:2, nw:2, ne:2, doesn't rotate
   unsigned char *texlerp;                 // STBVOX_MAKE_TEXLERP   -- vert:2, ud:2, ew:2, ns:2
   unsigned char *texlerp2;                // STBVOX_MAKE_TEXLERP2 (and use STBVOX_MAKE_TEXLERP1 for 'texlerp' -- e:2, n:2, u:3, unused:1
   unsigned short *texlerp_vert3;          // e:3,n:3,w:3,s:3,u:3 (down comes from 'texlerp')
   unsigned short *texlerp_face3;          // e:3,n:3,w:3,s:3,u:2,d:2
   unsigned char *lighting;                // lighting:8
   unsigned char *color;                   // color for entire block
   unsigned char *extended_color;          // index into ecolor palettes
   unsigned char *color2, *color2_facemask;// additional override colors with face bitmask
   unsigned char *color3, *color3_facemask;// additional override colors with face bitmask

   // indexed by tex1, used to determine tex2 if not otherwise specified
   unsigned char *tex2_for_tex1;   // 256

   // @TODO: when specializing, build a single struct with all of the
   // below values, so it's AoS instead of SoA for better cache efficiency

   // these are "palettes" you use to define properties indexed by 'blocktype'
   // indexed by blocktype*6+side
   unsigned char (*block_tex1_face)[6];
   unsigned char (*block_tex2_face)[6];
   unsigned char (*block_color_face)[6];
   unsigned char (*block_texlerp_face)[6];

   // indexed by blocktype
   unsigned char *block_geometry; // STBVOX_MAKE_GEOMETRY(geom,rot,0) -- use selector to encode independent rotation
   unsigned char *block_vheight;  // defines slopes and such; this vheight DOES get rotated
   unsigned char *block_tex1;
   unsigned char *block_tex2;
   unsigned char *block_color;
   unsigned char *block_texlerp;
   unsigned char *block_selector;

   // indexed by overlay*6+side; in all cases 0 means 'nochange'
   unsigned char (*overlay_tex1)[6];
   unsigned char (*overlay_tex2)[6];
   unsigned char (*overlay_color)[6];

   // indexed by extended_color
   unsigned char *ecolor_color;    // 256
   unsigned char *ecolor_facemask; // 256
};


// don't mess with this directly, it's just here so you can
// declare stbvox_mesh_maker on the stack or as a global
struct stbvox_mesh_maker
{
   stbvox_input_description input;
   int cur_x, cur_y, cur_z;       // last unprocessed voxel if it splits into multiple buffers
   int x0,y0,z0,x1,y1,z1;
   int x_stride_in_bytes;
   int y_stride_in_bytes;
   int precision_z;
   int config_dirty;
   int default_mesh;
   unsigned int tags;

   int cube_vertex_offset[6][4]; // this allows access per-vertex data stored block-centered (like texlerp, ambient)
   int vertex_gather_offset[6][4];

   int pos_x,pos_y,pos_z;
   int full;

   // computed from user input
   char *output_cur   [STBVOX_MAX_MESHES][STBVOX_MAX_MESH_SLOTS];
   char *output_end   [STBVOX_MAX_MESHES][STBVOX_MAX_MESH_SLOTS];
   char *output_buffer[STBVOX_MAX_MESHES][STBVOX_MAX_MESH_SLOTS];
   int   output_len   [STBVOX_MAX_MESHES][STBVOX_MAX_MESH_SLOTS];

   // computed from config
   int   output_size  [STBVOX_MAX_MESHES][STBVOX_MAX_MESH_SLOTS]; // per quad
   int   output_step  [STBVOX_MAX_MESHES][STBVOX_MAX_MESH_SLOTS]; // per vertex or per face, depending
   int   num_mesh_slots;

   float default_tex_scale[128][2];
};

#endif //  INCLUDE_STB_VOXEL_RENDER_H


#ifdef STB_VOXEL_RENDER_IMPLEMENTATION

#include <stdlib.h>
#include <assert.h>
#include <string.h> // memset

#ifndef _MSC_VER
   #include <stdint.h>
   typedef uint16_t stbvox_uint16;
   typedef uint32_t stbvox_uint32;
#else
   typedef unsigned short stbvox_uint16;
   typedef unsigned int   stbvox_uint32;
#endif

#ifdef _MSC_VER
   #define STBVOX_NOTUSED(v)  (void)(v)
#else
   #define STBVOX_NOTUSED(v)  (void)sizeof(v)
#endif


// 20-byte quad format:
//
// per vertex:
//
//     x:7
//     y:7
//     z:9
//     ao:6
//     tex_lerp:3
//
// per face:
//
//     tex1:8
//     tex2:8
//     face:8
//     color:8


// Faces:
//
// Faces use the bottom bits to choose the texgen
// mode, and all the bits to choose the normal.
// Thus the bottom 3 bits have to be:
//      e, n, w, s, u, d, u, d

enum
{
   STBVOX_EFACE_east,
   STBVOX_EFACE_north,
   STBVOX_EFACE_west,
   STBVOX_EFACE_south,
   STBVOX_EFACE_up,
   STBVOX_EFACE_down,
   STBVOX_EFACE_east_up,
   STBVOX_EFACE_east_down,

   STBVOX_EFACE_east_up_wall,
   STBVOX_EFACE_north_up_wall,
   STBVOX_EFACE_west_up_wall,
   STBVOX_EFACE_south_up_wall,
   STBVOX_EFACE_dummy_up_2,
   STBVOX_EFACE_dummy_down_2,
   STBVOX_EFACE_north_up,
   STBVOX_EFACE_north_down,

   STBVOX_EFACE_ne_up,
   STBVOX_EFACE_nw_up,
   STBVOX_EFACE_sw_up,
   STBVOX_EFACE_se_up,
   STBVOX_EFACE_dummy_up_3,
   STBVOX_EFACE_dummy_down_3,
   STBVOX_EFACE_west_up,
   STBVOX_EFACE_west_down,

   STBVOX_EFACE_ne_down,
   STBVOX_EFACE_nw_down,
   STBVOX_EFACE_sw_down,
   STBVOX_EFACE_se_down,
   STBVOX_EFACE_dummy_up_4,
   STBVOX_EFACE_dummy_down_4,
   STBVOX_EFACE_south_up,
   STBVOX_EFACE_south_down,

   // @TODO either we need more than 5 bits to encode the normal to fit these, or we can replace 'dummy' above with them but need to use full-size texgen table
   // so for now we just texture them with the wrong projection
   STBVOX_EFACE_east_down_wall = STBVOX_EFACE_east_down,
   STBVOX_EFACE_north_down_wall = STBVOX_EFACE_north_down,
   STBVOX_EFACE_west_down_wall = STBVOX_EFACE_west_down,
   STBVOX_EFACE_south_down_wall = STBVOX_EFACE_south_down,
};

static float stbvox_default_texgen[2][32][3] =
{
   { {  0, 1,0 }, { 0, 0, 1 }, {  0,-1,0 }, { 0, 0,-1 },
     { -1, 0,0 }, { 0, 0, 1 }, {  1, 0,0 }, { 0, 0,-1 },
     {  0,-1,0 }, { 0, 0, 1 }, {  0, 1,0 }, { 0, 0,-1 },
     {  1, 0,0 }, { 0, 0, 1 }, { -1, 0,0 }, { 0, 0,-1 },
     {  1, 0,0 }, { 0, 1, 0 }, { -1, 0,0 }, { 0,-1, 0 },
     { -1, 0,0 }, { 0,-1, 0 }, {  1, 0,0 }, { 0, 1, 0 },
     {  1, 0,0 }, { 0, 1, 0 }, { -1, 0,0 }, { 0,-1, 0 },
     { -1, 0,0 }, { 0,-1, 0 }, {  1, 0,0 }, { 0, 1, 0 },
   },
   { { 0, 0,-1 }, {  0, 1,0 }, { 0, 0, 1 }, {  0,-1,0 },
     { 0, 0,-1 }, { -1, 0,0 }, { 0, 0, 1 }, {  1, 0,0 },
     { 0, 0,-1 }, {  0,-1,0 }, { 0, 0, 1 }, {  0, 1,0 },
     { 0, 0,-1 }, {  1, 0,0 }, { 0, 0, 1 }, { -1, 0,0 },
     { 0,-1, 0 }, {  1, 0,0 }, { 0, 1, 0 }, { -1, 0,0 },
     { 0, 1, 0 }, { -1, 0,0 }, { 0,-1, 0 }, {  1, 0,0 },
     { 0,-1, 0 }, {  1, 0,0 }, { 0, 1, 0 }, { -1, 0,0 },
     { 0, 1, 0 }, { -1, 0,0 }, { 0,-1, 0 }, {  1, 0,0 },
   },
};

#define STBVOX_RSQRT2   0.7071067811865f
#define STBVOX_RSQRT3   0.5773502691896f

static float stbvox_default_normals[32][3] =
{
   { 1,0,0 },  // east
   { 0,1,0 },  // north
   { -1,0,0 }, // west
   { 0,-1,0 }, // south
   { 0,0,1 },  // up
   { 0,0,-1 }, // down
   {  STBVOX_RSQRT2,0, STBVOX_RSQRT2 }, // east & up
   {  STBVOX_RSQRT2,0, -STBVOX_RSQRT2 }, // east & down

   {  STBVOX_RSQRT2,0, STBVOX_RSQRT2 }, // east & up
   { 0, STBVOX_RSQRT2, STBVOX_RSQRT2 }, // north & up
   { -STBVOX_RSQRT2,0, STBVOX_RSQRT2 }, // west & up
   { 0,-STBVOX_RSQRT2, STBVOX_RSQRT2 }, // south & up
   { 0,0,1 },  // up
   { 0,0,-1 }, // down
   { 0, STBVOX_RSQRT2, STBVOX_RSQRT2 }, // north & up
   { 0, STBVOX_RSQRT2, -STBVOX_RSQRT2 }, // north & down

   {  STBVOX_RSQRT3, STBVOX_RSQRT3,STBVOX_RSQRT3 }, // NE & up
   { -STBVOX_RSQRT3, STBVOX_RSQRT3,STBVOX_RSQRT3 }, // NW & up
   { -STBVOX_RSQRT3,-STBVOX_RSQRT3,STBVOX_RSQRT3 }, // SW & up
   {  STBVOX_RSQRT3,-STBVOX_RSQRT3,STBVOX_RSQRT3 }, // SE & up
   { 0,0,1 },  // up
   { 0,0,-1 }, // down
   { -STBVOX_RSQRT2,0, STBVOX_RSQRT2 }, // west & up
   { -STBVOX_RSQRT2,0, -STBVOX_RSQRT2 }, // west & down

   {  STBVOX_RSQRT3, STBVOX_RSQRT3,-STBVOX_RSQRT3 }, // NE & down
   { -STBVOX_RSQRT3, STBVOX_RSQRT3,-STBVOX_RSQRT3 }, // NW & down
   { -STBVOX_RSQRT3,-STBVOX_RSQRT3,-STBVOX_RSQRT3 }, // SW & down
   {  STBVOX_RSQRT3,-STBVOX_RSQRT3,-STBVOX_RSQRT3 }, // SE & down
   { 0,0,1 },  // up
   { 0,0,-1 }, // down
   { 0,-STBVOX_RSQRT2, STBVOX_RSQRT2 }, // south & up
   { 0,-STBVOX_RSQRT2, -STBVOX_RSQRT2 }, // south & down
};

static float stbvox_default_texscale[128][2] =
{
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

static unsigned char stbvox_default_palette_compact[64][3] =
{
   { 255,255,255 }, { 238,238,238 }, { 221,221,221 }, { 204,204,204 },
   { 187,187,187 }, { 170,170,170 }, { 153,153,153 }, { 136,136,136 },
   { 119,119,119 }, { 102,102,102 }, {  85, 85, 85 }, {  68, 68, 68 },
   {  51, 51, 51 }, {  34, 34, 34 }, {  17, 17, 17 }, {   0,  0,  0 },
   { 255,240,240 }, { 255,220,220 }, { 255,160,160 }, { 255, 32, 32 },
   { 200,120,160 }, { 200, 60,150 }, { 220,100,130 }, { 255,  0,128 },
   { 240,240,255 }, { 220,220,255 }, { 160,160,255 }, {  32, 32,255 },
   { 120,160,200 }, {  60,150,200 }, { 100,130,220 }, {   0,128,255 },
   { 240,255,240 }, { 220,255,220 }, { 160,255,160 }, {  32,255, 32 },
   { 160,200,120 }, { 150,200, 60 }, { 130,220,100 }, { 128,255,  0 },
   { 255,255,240 }, { 255,255,220 }, { 220,220,180 }, { 255,255, 32 },
   { 200,160,120 }, { 200,150, 60 }, { 220,130,100 }, { 255,128,  0 },
   { 255,240,255 }, { 255,220,255 }, { 220,180,220 }, { 255, 32,255 },
   { 160,120,200 }, { 150, 60,200 }, { 130,100,220 }, { 128,  0,255 },
   { 240,255,255 }, { 220,255,255 }, { 180,220,220 }, {  32,255,255 },
   { 120,200,160 }, {  60,200,150 }, { 100,220,130 }, {   0,255,128 },
};

static float stbvox_default_palette[64][4];

void stbvox_build_default_palette(void)
{
   int i;
   for (i=0; i < 64; ++i) {
      stbvox_default_palette[i][0] = stbvox_default_palette_compact[i][0] / 255.0f;
      stbvox_default_palette[i][1] = stbvox_default_palette_compact[i][1] / 255.0f;
      stbvox_default_palette[i][2] = stbvox_default_palette_compact[i][2] / 255.0f;
      stbvox_default_palette[i][3] = 0.0f;
   }
}

// Shaders

#define STBVOX_TAG_all                       (1 <<  0)
#define STBVOX_TAG_gl                        (1 <<  1)
#define STBVOX_TAG_d3d                       (1 <<  2)
#define STBVOX_TAG_glsl_130                  (1 <<  3)
#define STBVOX_TAG_glsl_150                  (1 <<  4)
#define STBVOX_TAG_glsl_150_compatibility    (1 <<  5)
#define STBVOX_TAG_face_sampled              (1 <<  6)
#define STBVOX_TAG_face_attribute            (1 <<  7)
#define STBVOX_TAG_gl_modelview              (1 <<  8)
#define STBVOX_TAG_textured                  (1 << 10)

#define STBVOX_TAG_NOT                       (1 << 31)

typedef struct
{
   unsigned int tag;
   char *str;
} stbvox_tagged_string;

stbvox_tagged_string stbvox_vertex_program[] =
{
   { STBVOX_TAG_glsl_130,

            "#version 130\n"
   },
   { STBVOX_TAG_glsl_150,

            "#version 150\n"
   },
   { STBVOX_TAG_glsl_150_compatibility,

            "#version 150 compatibility\n"
   },
   { STBVOX_TAG_face_sampled,

            "uniform usamplerBuffer facearray;\n"
   },
   { STBVOX_TAG_face_attribute,

            "in uvec4 attr_face;\n"
   },
   { STBVOX_TAG_all,

            // vertex input data
            "in uint attr_vertex;\n"

            // per-buffer data
            "uniform vec3 transform[3];\n"

            // to simplify things, we avoid using more than 256 uniform vectors
            // in fragment shader to avoid possible 1024 component limit, so
            // we access this table in the fragment shader.
            "uniform vec3 normal_table[32];\n"

            // fragment output data
            "flat out uvec4  facedata;\n"
            "     out  vec3  objectspace_pos;\n"
            "     out  vec3  vnormal;\n"
            "     out float  texlerp;\n"
            "     out float  amb_occ;\n"
   },
   { STBVOX_TAG_NOT | STBVOX_TAG_gl_modelview,

            "uniform mat44 model_view;\n"
   },
   { STBVOX_TAG_all,
   
            // @TODO handle the HLSL way to do this
            "void main()\n"
            "{\n"
   },
   { STBVOX_TAG_face_attribute,

            "   facedata = attr_face;\n"
   },
   { STBVOX_TAG_face_sampled,

            "   int faceID = gl_VertexID >> 2;\n"
            "   facedata   = texelFetch(facearray, faceID);\n"
   },
   { STBVOX_TAG_all,

            // extract data for vertex
            "   vec3 offset;\n"
            "   offset.x = float( (attr_vertex       ) & 127u );\n"             // a[0..6]
            "   offset.y = float( (attr_vertex >>  7u) & 127u );\n"             // a[7..13]
            "   offset.z = float( (attr_vertex >> 14u) & 511u );\n"             // a[14..22]
            "   amb_occ  = float( (attr_vertex >> 23u) &  63u ) / 63.0;\n"      // a[23..28]
            "   texlerp  = float( (attr_vertex >> 29u)        ) /  7.0;\n"      // a[29..31]

            "   vnormal = normal_table[(facedata.w>>2) & 31u];\n"
            "   objectspace_pos = offset * transform[0];\n"  // object-to-world scale
            "   vec3 position  = objectspace_pos + transform[1];\n"  // object-to-world translate
   },
   { STBVOX_TAG_NOT | STBVOX_TAG_gl_modelview,

            "   gl_Position = model_view * vec4(position,1.0);\n"
            "}"
   },
   { STBVOX_TAG_gl_modelview,

            "   gl_Position = gl_ModelViewProjectionMatrix * vec4(position,1.0);\n"
            "}"
   },
};


stbvox_tagged_string stbvox_fragment_program[] =
{
   { STBVOX_TAG_glsl_130,

            "#version 130\n"
   },
   { STBVOX_TAG_glsl_150,

            "#version 150\n"
   },
   { STBVOX_TAG_glsl_150_compatibility,

            "#version 150 compatibility\n"
   },
   { STBVOX_TAG_all,

            // rlerp is lerp but with t on the left, like god intended
            "#define rlerp(t,x,y) mix(x,y,t)\n"

            // fragment output data
            "flat in uvec4  facedata;\n"
            "     in  vec3  objectspace_pos;\n"
            "     in  vec3  vnormal;\n"
            "     in float  texlerp;\n"
            "     in float  amb_occ;\n"

            // per-buffer data
            "uniform vec3 transform[3];\n"

            // per-frame data
            "uniform vec3 camera_pos;\n"

            // probably constant data
            "uniform vec3 ambient[4];\n"

   },
   { STBVOX_TAG_textured,


            // generally constant data
            "uniform sampler2DArray tex_array[2];\n"
#if 0

            "uniform vec4 color_table[64];\n"
            "uniform vec2 texscale[64];\n" // instead of 128, to avoid running out of uniforms
            "uniform vec3 texgen[64];\n"
#else
            "uniform samplerBuffer color_table;\n"
            "uniform samplerBuffer texscale;\n"
            "uniform samplerBuffer texgen;\n"
#endif
   },
   { STBVOX_TAG_all,

            "out vec4  outcolor;\n"
            "uniform vec3 light_source[2];\n"
            "vec3 compute_lighting(vec3 pos, vec3 norm);\n"
   },
   { STBVOX_TAG_all,

            "void main()\n"
            "{\n"
            "   vec3 albedo;\n"
            "   float fragment_alpha;\n"

   },
   { STBVOX_TAG_textured,

            // unpack the values
            "   uint tex1_id = facedata.x;\n"
            "   uint tex2_id = facedata.y;\n"
            "   uint texprojid = facedata.w & 31u;\n"
            "   uint color_id  = facedata.z;\n"
            "   bool texblend_mode = ((facedata.w & 128u) != 0u);\n"

#if 0
            // load from uniforms / texture buffers 
            "   vec3 texgen_s = texgen[texprojid];\n"
            "   vec3 texgen_t = texgen[texprojid+32u];\n"
            "   float tex1_scale = texscale[tex1_id & 63u].x;\n"
            "   float tex2_scale = texscale[tex2_id & 63u].y;\n"
            "   vec4 color = color_table[color_id & 63u];\n"
#else
            "   vec3 texgen_s = texelFetch(texgen, int(texprojid)).xyz;\n"
            "   vec3 texgen_t = texelFetch(texgen, int(texprojid+32u)).xyz;\n"
            "   float tex1_scale = texelFetch(texscale, int(tex1_id & 127u)).x;\n"
            "   float tex2_scale = texelFetch(texscale, int(tex2_id & 127u)).y;\n"
            "   vec4 color = texelFetch(color_table, int(color_id & 63u));\n"
#endif
            "   vec2 texcoord;\n"
            "   vec3 texturespace_pos = objectspace_pos + transform[2].xyz;\n"
            "   texcoord.s = dot(texturespace_pos, texgen_s);\n"
            "   texcoord.t = dot(texturespace_pos, texgen_t);\n"

            // @TODO: use 2 bits of facedata.w to enable animation of facedata.x & y?
   
            "   vec4 tex1 = texture(tex_array[0], vec3(tex1_scale * texcoord, float(tex1_id)));\n"
            "   vec4 tex2 = texture(tex_array[1], vec3(tex2_scale * texcoord, float(tex2_id)));\n"

            "   bool emissive = (int(color.w) & 1) != 0;\n"

            // recolor textures
            "   if ((color_id &  64u) != 0u) tex1.xyz *= color.xyz;\n"
            "   if ((color_id & 128u) != 0u) tex2.xyz *= color.xyz;\n"

            "   tex2.a *= texlerp;\n"

            //  @TODO: could use a separate lookup table keyed on tex2 to determine this
            "   if (texblend_mode)\n"
            "      albedo = tex2.xyz * rlerp(tex2.a, 2.0*tex1.xyz, vec3(1.0,1.0,1.0));\n"
            "   else\n"
            "      albedo = rlerp(tex2.a, tex1.xyz, tex2.xyz);\n" // @TODO premultiplied alpha

            "   fragment_alpha = tex1.a;\n"
   },
   { STBVOX_TAG_NOT | STBVOX_TAG_textured,

            "   vec4 color;"
            "   color.xyz = vec3(facedata.xyz) / 255.0;\n"
            "   bool emissive = (facedata.w & 128) != 0;\n"
            "   albedo = color.xyz;\n"
            "   fragment_alpha = 1.0;\n"

   },
   { STBVOX_TAG_all,

            // compute the normal

            "   vec3 normal = vnormal;\n"
            //"   vec3 normal = normalize(vnormal);\n"

            // @TODO: bump map normal

            "   vec3 amb_color = dot(normal, ambient[0]) * ambient[1] + ambient[2];\n"

            "   amb_color = clamp(amb_color, 0.0, 1.0);"
            "   amb_color *= amb_occ;\n"

            "   vec3 lit_color;\n"
            "   vec3 lighting = compute_lighting(objectspace_pos + transform[1], normal) + amb_color * 0.25;\n"
            "   if (!emissive)\n"
            "      lit_color = lighting * albedo;\n"
            "   else\n"
            "      lit_color = albedo;\n"

            // @TODO dynamic lighting based on normal, and based on "vec3 worldspace_pos = objectspace_pos + o2w[1];\n"
            // @TODO shadow test
            // @TODO fog

// smoothstep fog:
#if 1
   "   vec3 dist = objectspace_pos + (transform[1] - camera_pos);\n"
   "   float f = sqrt(dot(dist,dist))/1320.0;\n"
   "   f = clamp(f, 0.0, 1.0);\n" 
   "   f = 3.0*f*f - 2.0*f*f*f;\n" // smoothstep
   "   f = f*f;\n"  // fade in more smoothly
   "   lit_color.xyz = rlerp(f, lit_color.xyz, ambient[3]);\n"
#endif



            "   vec4 final_color = vec4(lit_color, fragment_alpha);\n"
            "   outcolor = final_color;\n"
            "}"

"vec3 compute_lighting(vec3 pos, vec3 norm)\n"
"{\n"
"   vec3 light_dir = light_source[0] - pos;\n"
"   float lambert = dot(light_dir, norm) / dot(light_dir, light_dir);\n"
"   return light_source[1] * clamp(lambert, 0.0, 1.0);\n"
"}\n"
   },
};

static int stbvox_check_tag(stbvox_mesh_maker *mm, unsigned int test_tag)
{
   if (test_tag & STBVOX_TAG_NOT)
      return (test_tag & mm->tags) == 0;        // require absence of all tags
   else
      return (test_tag & mm->tags) == test_tag; // require AND of all tags

}

static int stbvox_build_tagged_string(stbvox_mesh_maker *mm, char *buffer, size_t buffer_size, stbvox_tagged_string *str, int num_chunks)
{
   size_t pos=0;
   int i;
   for (i=0; i < num_chunks; ++i) {
      if (stbvox_check_tag(mm, str[i].tag)) {
         char *text = str[i].str;
         while (*text) {
            if (pos < buffer_size)
               buffer[pos] = *text;
            ++pos;
            ++text;
         }
      }
   }
   if (pos < buffer_size) {
      buffer[pos++] = 0;
      return pos;
   } else {
      return -(int)pos;
   }
}

int stbvox_get_vertex_shader(stbvox_mesh_maker *mm, char *buffer, size_t buffer_size)
{
   return stbvox_build_tagged_string(mm, buffer, buffer_size,
                                     stbvox_vertex_program,
                                     sizeof(stbvox_vertex_program)/sizeof(stbvox_vertex_program[0]));
}

int stbvox_get_fragment_shader(stbvox_mesh_maker *mm, char *buffer, size_t buffer_size)
{
   return stbvox_build_tagged_string(mm, buffer, buffer_size,
                                     stbvox_fragment_program,
                                     sizeof(stbvox_fragment_program)/sizeof(stbvox_fragment_program[0]));
}

static float stbvox_dummy_transform[3][3];

stbvox_uniform_info stbvox_uniforms[] =
{
   { STBVOX_UNIFORM_TYPE_sampler  ,  4,   1, "facearray"    , 0                           , STBVOX_TAG_face_sampled },
   { STBVOX_UNIFORM_TYPE_vec3     , 12,   3, "transform"    , stbvox_dummy_transform[0]   , STBVOX_TAG_all },

   { STBVOX_UNIFORM_TYPE_sampler  ,  4,   2, "tex_array"    , 0                           , STBVOX_TAG_textured },
   { STBVOX_UNIFORM_TYPE_vec2     ,  8, 128, "texscale"     , stbvox_default_texscale[0]  , STBVOX_TAG_textured },

   { STBVOX_UNIFORM_TYPE_vec4     , 16,  64, "color_table"  , stbvox_default_palette[0]   , STBVOX_TAG_textured },

   { STBVOX_UNIFORM_TYPE_vec3     , 12,  32, "normal_table" , stbvox_default_normals[0]   , STBVOX_TAG_all },
   { STBVOX_UNIFORM_TYPE_vec3     , 12,  64, "texgen"       , stbvox_default_texgen[0][0] , STBVOX_TAG_textured },

   { STBVOX_UNIFORM_TYPE_vec3     , 12,   4, "ambient"      , 0                           , STBVOX_TAG_all },
   { STBVOX_UNIFORM_TYPE_vec3     , 12,   1, "camera_pos"   , stbvox_dummy_transform[0]   , STBVOX_TAG_all },
};

stbvox_uniform_info *stbvox_get_uniform_info(stbvox_mesh_maker *mm, int uniform)
{
   if (stbvox_default_palette[0][0] == 0) // NOTE: not threadsafe, so call once to init
      stbvox_build_default_palette();

   if (uniform < 0 || uniform >= STBVOX_UNIFORM_count)
      return NULL;

   if (stbvox_check_tag(mm, stbvox_uniforms[uniform].tags))
      return &stbvox_uniforms[uniform];
   else
      return NULL;
}

#define STBVOX_GET_GEO(geom_data)  ((geom_data) & 15)

typedef stbvox_uint32 stbvox_mesh_vertex;

typedef struct
{
   unsigned char tex1,tex2,color,face_info;
} stbvox_mesh_face;

#define stbvox_vertex_p(x,y,z,ao,texlerp) ((stbvox_uint32) ((x)+((y)<<7)+((z)<<14)+((ao)<<23)+((texlerp)<<29)))

typedef struct
{
   unsigned char block;
   unsigned char overlay;
   unsigned char facerot:4;
   unsigned char ecolor:4;
   unsigned char tex2;
} stbvox_rotate;

typedef struct
{
   unsigned char x,y,z;
} stbvox_pos;

static unsigned char stbvox_rotate_face[6][4] =
{
   { 0,1,2,3 },
   { 1,2,3,0 },
   { 2,3,0,1 },
   { 3,0,1,2 },
   { 4,4,4,4 },
   { 5,5,5,5 },   
};

#define STBVOX_ROTATE(x,r)   stbvox_rotate_face[x][r] // (((x)+(r))&3)

stbvox_mesh_face stbvox_compute_mesh_face_value(stbvox_mesh_maker *mm, stbvox_rotate rot, int face, int v_off, int normal)
{
   unsigned char color_face;
   stbvox_mesh_face face_data = { 0 };
   stbvox_block_type bt = mm->input.blocktype[v_off];
   unsigned char bt_face = STBVOX_ROTATE(face, rot.block);

   if (mm->input.color)
      face_data.color = mm->input.color[v_off];

   if (mm->input.block_tex1)
      face_data.tex1 = mm->input.block_tex1[bt];
   else if (mm->input.block_tex1_face)
      face_data.tex1 = mm->input.block_tex1_face[bt][bt_face];
   else
      face_data.tex1 = bt;

   if (mm->input.block_tex2)
      face_data.tex2 = mm->input.block_tex2[bt];
   else if (mm->input.block_tex2_face)
      face_data.tex2 = mm->input.block_tex2_face[bt][bt_face];

   if (mm->input.block_color) {
      unsigned char mcol = mm->input.block_color[bt];
      if (mcol)
         face_data.color = mcol;
   } else if (mm->input.block_color_face) {
      unsigned char mcol = mm->input.block_color_face[bt][bt_face];
      if (mcol)
         face_data.color = mcol;
   }

   if (mm->input.overlay) {
      int over_face = STBVOX_ROTATE(face, rot.overlay);
      unsigned char over = mm->input.overlay[v_off];
      if (mm->input.overlay_tex1) {
         unsigned char rep1 = mm->input.overlay_tex1[over][over_face];
         if (rep1)
            face_data.tex1 = rep1;
      }
      if (mm->input.overlay_tex2) {
         unsigned char rep2 = mm->input.overlay_tex1[over][over_face];
         if (rep2)
            face_data.tex2 = rep2;
      }
      if (mm->input.overlay_color) {
         unsigned char rep3 = mm->input.overlay_color[over][over_face];
         if (rep3)
            face_data.color = rep3;
      }
   }
   if (mm->input.tex2_for_tex1)
      face_data.tex2 = mm->input.tex2_for_tex1[face_data.tex1];
   if (mm->input.tex2)
      face_data.tex2 = mm->input.tex2[v_off];
   if (mm->input.tex2_replace) {
      int tex2_face = STBVOX_ROTATE(face, rot.tex2);
      if (mm->input.tex2_facemask[v_off] & (1 << tex2_face))
         face_data.tex2 = mm->input.tex2_replace[v_off];
   }
   color_face = STBVOX_ROTATE(face, rot.ecolor);
   if (mm->input.extended_color) {
      unsigned char ec = mm->input.extended_color[v_off];
      if (mm->input.ecolor_facemask[ec] & (1 << color_face))
         face_data.color = mm->input.ecolor_color[ec];
   }
   if (mm->input.color2) {
      if (mm->input.color2_facemask[v_off] & (1 << color_face))
         face_data.color = mm->input.color2[v_off];
      if (mm->input.color3 && (mm->input.color3_facemask[v_off] & (1 << color_face)))
         face_data.color = mm->input.color3[v_off];
   }
   face_data.face_info = (normal<<2) + rot.facerot;
   return face_data;
}

static unsigned char stbvox_face_lerp[6] = { 0,2,0,2,4,4 };
static unsigned char stbvox_vert3_lerp[6] = { 0,3,6,9,12,12 };
static unsigned char stbvox_vert_lerp_for_face_lerp[6] = { 0, 4, 7 };
static unsigned char stbvox_face3_lerp[6] = { 0,3,6,9,12,14 };
static unsigned char stbvox_face3_updown[8] = { 0,2,4,7,0,2,4,7 };

// vertex offsets for face vertices

static unsigned char stbvox_vertex_vector[6][4][3] =
{
   { { 1,0,1 }, { 1,1,1 }, { 1,1,0 }, { 1,0,0 } }, // east
   { { 1,1,1 }, { 0,1,1 }, { 0,1,0 }, { 1,1,0 } }, // north
   { { 0,1,1 }, { 0,0,1 }, { 0,0,0 }, { 0,1,0 } }, // west
   { { 0,0,1 }, { 1,0,1 }, { 1,0,0 }, { 0,0,0 } }, // south
   { { 0,1,1 }, { 1,1,1 }, { 1,0,1 }, { 0,0,1 } }, // up
   { { 0,0,0 }, { 1,0,0 }, { 1,1,0 }, { 0,1,0 } }, // down
};

// stbvox_vertex_vector, but read coordinates as binary numbers, zyx
static unsigned char stbvox_vertex_selector[6][4] =
{
   { 5,7,3,1 },
   { 7,6,2,3 },
   { 6,4,0,2 },
   { 4,5,1,0 },
   { 6,7,5,4 },
   { 0,1,3,2 },
};

static stbvox_mesh_vertex stbvox_vmesh_delta_normal[6][4] =
{
   {  stbvox_vertex_p(1,0,1,0,0) , 
      stbvox_vertex_p(1,1,1,0,0) ,
      stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0)  },
   {  stbvox_vertex_p(1,1,1,0,0) ,
      stbvox_vertex_p(0,1,1,0,0) ,
      stbvox_vertex_p(0,1,0,0,0) ,
      stbvox_vertex_p(1,1,0,0,0)  },
   {  stbvox_vertex_p(0,1,1,0,0) ,
      stbvox_vertex_p(0,0,1,0,0) ,
      stbvox_vertex_p(0,0,0,0,0) ,
      stbvox_vertex_p(0,1,0,0,0)  },
   {  stbvox_vertex_p(0,0,1,0,0) ,
      stbvox_vertex_p(1,0,1,0,0) ,
      stbvox_vertex_p(1,0,0,0,0) ,
      stbvox_vertex_p(0,0,0,0,0)  },
   {  stbvox_vertex_p(0,1,1,0,0) ,
      stbvox_vertex_p(1,1,1,0,0) ,
      stbvox_vertex_p(1,0,1,0,0) ,
      stbvox_vertex_p(0,0,1,0,0)  },
   {  stbvox_vertex_p(0,0,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0) ,
      stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(0,1,0,0,0)  }
};

static stbvox_mesh_vertex stbvox_vmesh_pre_vheight[6][4] =
{
   {  stbvox_vertex_p(1,0,0,0,0) , 
      stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0)  },
   {  stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(0,1,0,0,0) ,
      stbvox_vertex_p(0,1,0,0,0) ,
      stbvox_vertex_p(1,1,0,0,0)  },
   {  stbvox_vertex_p(0,1,0,0,0) ,
      stbvox_vertex_p(0,0,0,0,0) ,
      stbvox_vertex_p(0,0,0,0,0) ,
      stbvox_vertex_p(0,1,0,0,0)  },
   {  stbvox_vertex_p(0,0,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0) ,
      stbvox_vertex_p(0,0,0,0,0)  },
   {  stbvox_vertex_p(0,1,0,0,0) ,
      stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0) ,
      stbvox_vertex_p(0,0,0,0,0)  },
   {  stbvox_vertex_p(0,0,0,0,0) ,
      stbvox_vertex_p(1,0,0,0,0) ,
      stbvox_vertex_p(1,1,0,0,0) ,
      stbvox_vertex_p(0,1,0,0,0)  }
};

static stbvox_mesh_vertex stbvox_vmesh_delta_half_z[6][4] =
{
   { stbvox_vertex_p(1,0,2,0,0) , 
     stbvox_vertex_p(1,1,2,0,0) ,
     stbvox_vertex_p(1,1,0,0,0) ,
     stbvox_vertex_p(1,0,0,0,0)  },
   { stbvox_vertex_p(1,1,2,0,0) ,
     stbvox_vertex_p(0,1,2,0,0) ,
     stbvox_vertex_p(0,1,0,0,0) ,
     stbvox_vertex_p(1,1,0,0,0)  },
   { stbvox_vertex_p(0,1,2,0,0) ,
     stbvox_vertex_p(0,0,2,0,0) ,
     stbvox_vertex_p(0,0,0,0,0) ,
     stbvox_vertex_p(0,1,0,0,0)  },
   { stbvox_vertex_p(0,0,2,0,0) ,
     stbvox_vertex_p(1,0,2,0,0) ,
     stbvox_vertex_p(1,0,0,0,0) ,
     stbvox_vertex_p(0,0,0,0,0)  },
   { stbvox_vertex_p(0,1,2,0,0) ,
     stbvox_vertex_p(1,1,2,0,0) ,
     stbvox_vertex_p(1,0,2,0,0) ,
     stbvox_vertex_p(0,0,2,0,0)  },
   { stbvox_vertex_p(0,0,0,0,0) ,
     stbvox_vertex_p(1,0,0,0,0) ,
     stbvox_vertex_p(1,1,0,0,0) ,
     stbvox_vertex_p(0,1,0,0,0)  }
};

static stbvox_mesh_vertex stbvox_vmesh_crossed_pair[6][4] =
{
   { stbvox_vertex_p(1,0,2,0,0) , 
     stbvox_vertex_p(0,1,2,0,0) ,
     stbvox_vertex_p(0,1,0,0,0) ,
     stbvox_vertex_p(1,0,0,0,0)  },
   { stbvox_vertex_p(1,1,2,0,0) ,
     stbvox_vertex_p(0,0,2,0,0) ,
     stbvox_vertex_p(0,0,0,0,0) ,
     stbvox_vertex_p(1,1,0,0,0)  },
   { stbvox_vertex_p(0,1,2,0,0) ,
     stbvox_vertex_p(1,0,2,0,0) ,
     stbvox_vertex_p(1,0,0,0,0) ,
     stbvox_vertex_p(0,1,0,0,0)  },
   { stbvox_vertex_p(0,0,2,0,0) ,
     stbvox_vertex_p(1,1,2,0,0) ,
     stbvox_vertex_p(1,1,0,0,0) ,
     stbvox_vertex_p(0,0,0,0,0)  },
   // not used, so we leave it non-degenerate to make sure it doesn't get gen'd accidentally
   { stbvox_vertex_p(0,1,2,0,0) ,
     stbvox_vertex_p(1,1,2,0,0) ,
     stbvox_vertex_p(1,0,2,0,0) ,
     stbvox_vertex_p(0,0,2,0,0)  },
   { stbvox_vertex_p(0,0,0,0,0) ,
     stbvox_vertex_p(1,0,0,0,0) ,
     stbvox_vertex_p(1,1,0,0,0) ,
     stbvox_vertex_p(0,1,0,0,0)  }
};


void stbvox_get_quad_vertex_pointer(stbvox_mesh_maker *mm, int mesh, stbvox_mesh_vertex **vertices, stbvox_mesh_face face)
{
   char *p = mm->output_cur[mesh][0];
   int step = mm->output_step[mesh][0];

   // allocate a new quad from the mesh
   vertices[0] = (stbvox_mesh_vertex *) p; p += step;
   vertices[1] = (stbvox_mesh_vertex *) p; p += step;
   vertices[2] = (stbvox_mesh_vertex *) p; p += step;
   vertices[3] = (stbvox_mesh_vertex *) p; p += step;
   mm->output_cur[mesh][0] = p;

   // output the face
   if (mm->tags & STBVOX_TAG_face_attribute) {
      *(stbvox_mesh_face *) (vertices[0]+1) = face;
      *(stbvox_mesh_face *) (vertices[1]+1) = face;
      *(stbvox_mesh_face *) (vertices[2]+1) = face;
      *(stbvox_mesh_face *) (vertices[3]+1) = face;
   } else {
      *(stbvox_mesh_face *) mm->output_cur[mesh][1] = face;
      mm->output_cur[mesh][1] += 4;
   }
}

void stbvox_make_mesh_for_face(stbvox_mesh_maker *mm, stbvox_rotate rot, int face, int v_off, stbvox_pos pos, stbvox_mesh_vertex vertbase, stbvox_mesh_vertex *face_coord, unsigned char mesh, int normal)
{
   stbvox_mesh_face face_data = stbvox_compute_mesh_face_value(mm,rot,face,v_off, normal);

   // still need to compute ao & texlerp for each vertex

   // first compute texlerp into p1
   stbvox_mesh_vertex p1[4] = { 0 };

   if (mm->input.block_texlerp) {
      stbvox_block_type bt = mm->input.blocktype[v_off];
      unsigned char val = mm->input.block_texlerp[bt];
      p1[0] = p1[1] = p1[2] = p1[3] = stbvox_vertex_p(0,0,0,0,val);
   } else if (mm->input.block_texlerp_face) {
      stbvox_block_type bt = mm->input.blocktype[v_off];
      unsigned char bt_face = STBVOX_ROTATE(face, rot.block);
      unsigned char val = mm->input.block_texlerp_face[bt][bt_face];
      p1[0] = p1[1] = p1[2] = p1[3] = stbvox_vertex_p(0,0,0,0,val);
   } else if (mm->input.texlerp_face3) {
      unsigned char val = (mm->input.texlerp_face3[v_off] >> stbvox_face3_lerp[face]) & 7;
      if (face >= 4)
         val = stbvox_face3_updown[val];
      p1[0] = p1[1] = p1[2] = p1[3] = stbvox_vertex_p(0,0,0,0,val);
   } else if (mm->input.texlerp) {
      unsigned char facelerp = (mm->input.texlerp[v_off] >> stbvox_face_lerp[face]) & 3;
      if (facelerp == STBVOX_TEXLERP_use_vert) {
         if (mm->input.texlerp_vert3 && face != STBVOX_FACE_down) {
            unsigned char shift = stbvox_vert3_lerp[face];
            p1[0] = (mm->input.texlerp_vert3[mm->cube_vertex_offset[face][0]] >> shift) & 7;
            p1[1] = (mm->input.texlerp_vert3[mm->cube_vertex_offset[face][1]] >> shift) & 7;
            p1[2] = (mm->input.texlerp_vert3[mm->cube_vertex_offset[face][2]] >> shift) & 7;
            p1[3] = (mm->input.texlerp_vert3[mm->cube_vertex_offset[face][3]] >> shift) & 7;
         } else {
            p1[0] = stbvox_vert_lerp_for_face_lerp[mm->input.texlerp[mm->cube_vertex_offset[face][0]]>>6];
            p1[1] = stbvox_vert_lerp_for_face_lerp[mm->input.texlerp[mm->cube_vertex_offset[face][1]]>>6];
            p1[2] = stbvox_vert_lerp_for_face_lerp[mm->input.texlerp[mm->cube_vertex_offset[face][2]]>>6];
            p1[3] = stbvox_vert_lerp_for_face_lerp[mm->input.texlerp[mm->cube_vertex_offset[face][3]]>>6];
         }
         p1[0] = stbvox_vertex_p(0,0,0,0,p1[0]);
         p1[1] = stbvox_vertex_p(0,0,0,0,p1[1]);
         p1[2] = stbvox_vertex_p(0,0,0,0,p1[2]);
         p1[3] = stbvox_vertex_p(0,0,0,0,p1[3]);
      } else {
         p1[0] = p1[1] = p1[2] = p1[3] = stbvox_vertex_p(0,0,0,0,stbvox_vert_lerp_for_face_lerp[facelerp]);
      }
   } else {
      p1[0] = p1[1] = p1[2] = p1[3] = stbvox_vertex_p(0,0,0,0,7);
   }

   {
      stbvox_mesh_vertex *mv[4];
      stbvox_get_quad_vertex_pointer(mm, mesh, mv, face_data);

      if (mm->input.lighting) {
         if (mm->input.lighting_at_vertices) {
            int i;
            for (i=0; i < 4; ++i) {
               *mv[i] = vertbase + face_coord[i];
                          + stbvox_vertex_p(0,0,0,mm->input.lighting[v_off + mm->cube_vertex_offset[face][i]] & 63,0);
            }
         } else {
            unsigned char *amb = &mm->input.lighting[v_off];
            int i,j;
            #ifdef STBVOX_ROTATION_IN_LIGHTING
            #define STBVOX_GET_LIGHTING(light) ((light) & ~3)
            #define STBVOX_LIGHTING_ROUNDOFF   8
            #else
            #define STBVOX_GET_LIGHTING(light) (light)
            #define STBVOX_LIGHTING_ROUNDOFF   2
            #endif

            for (i=0; i < 4; ++i) {
               // for each vertex, gather from the four neighbor blocks it's facing
               unsigned char *vamb = &amb[mm->cube_vertex_offset[face][i]];
               int total=0;
               for (j=0; j < 4; ++j)
                  total += STBVOX_GET_LIGHTING(vamb[mm->vertex_gather_offset[face][j]]);
               *mv[i] = vertbase + face_coord[i]
                          + stbvox_vertex_p(0,0,0,(total+STBVOX_LIGHTING_ROUNDOFF)>>4,0);
                          // >> 4 is because:
                          //   >> 2 to divide by 4 to get average over 4 samples
                          //   >> 2 because input is 8 bits, output is 6 bits
            }

            // @TODO: gather baked lighting where we have precomputed
            // shadow bits for each light and we gather them from neighbors
            // as above then do normal diffuse light computation--this
            // needs a variant shader which has 8-bit rgb as well, in
            // which case 'lighting' isn't needed so we have ~14 more
            // bits to store stuff per vertex
            //
            // Or alternatively note that gathering baked *lighting*
            // is different from gathering baked ao; baked ao can count
            // solid blocks as 0 ao, but baked lighting wants average
            // of non-blocked, not average & treat blocked as 0. And
            // we can't bake the right value into the solid blocks
            // because they can have different lighting values on
            // different sides.

         }
      } else {
         *mv[0] = vertbase + face_coord[0] + p1[0];
         *mv[1] = vertbase + face_coord[1] + p1[1];
         *mv[2] = vertbase + face_coord[2] + p1[2];
         *mv[3] = vertbase + face_coord[3] + p1[3];
      }
   }
}

// render non-planar quads by splitting into two triangles, rendering each as a degenerate quad
void stbvox_make_02_split_mesh_for_face(stbvox_mesh_maker *mm, stbvox_rotate rot, int face1, int face2, int v_off, stbvox_pos pos, stbvox_mesh_vertex vertbase, stbvox_mesh_vertex *face_coord, unsigned char mesh)
{
   stbvox_mesh_vertex v[4];
   v[0] = face_coord[0];
   v[1] = face_coord[1];
   v[2] = face_coord[2];
   v[3] = face_coord[0];
   stbvox_make_mesh_for_face(mm, rot, face1, v_off, pos, vertbase, v, mesh, face1);
   v[1] = face_coord[2];
   v[2] = face_coord[3];
   stbvox_make_mesh_for_face(mm, rot, face2, v_off, pos, vertbase, v, mesh, face2);
}

void stbvox_make_13_split_mesh_for_face(stbvox_mesh_maker *mm, stbvox_rotate rot, int face1, int face2, int v_off, stbvox_pos pos, stbvox_mesh_vertex vertbase, stbvox_mesh_vertex *face_coord, unsigned char mesh)
{
   stbvox_mesh_vertex v[4];
   v[0] = face_coord[1];
   v[1] = face_coord[2];
   v[2] = face_coord[3];
   v[3] = face_coord[1];
   stbvox_make_mesh_for_face(mm, rot, face1, v_off, pos, vertbase, v, mesh, face1);
   v[1] = face_coord[3];
   v[2] = face_coord[0];
   stbvox_make_mesh_for_face(mm, rot, face2, v_off, pos, vertbase, v, mesh, face2);
}

// simple case for mesh generation: we have only solid and empty blocks
void stbvox_make_mesh_for_block(stbvox_mesh_maker *mm, stbvox_pos pos, int v_off, stbvox_mesh_vertex *vmesh)
{
   int ns_off = mm->y_stride_in_bytes;
   int ew_off = mm->x_stride_in_bytes;

   unsigned char *blockptr = &mm->input.blocktype[v_off];
   stbvox_mesh_vertex basevert = stbvox_vertex_p(pos.x, pos.y, pos.z<<mm->precision_z , 0,0);

   stbvox_rotate rot = { 0,0,0,0,0 };
   unsigned char simple_rot = 0;

   unsigned char mesh = mm->default_mesh;

   if (mm->input.selector)
      mesh = mm->input.selector[v_off];

   // check if we're going off the end
   if (mm->output_cur[mesh][0] + mm->output_size[mesh][0]*6 > mm->output_end[mesh][0]) {
      mm->full = 1;
      return;
   }

   #ifdef STBVOX_ROTATION_IN_LIGHTING
   simple_rot = mm->input.lighting[v_off] & 3;
   #endif

   if (blockptr[ 1]==0) {
      rot.facerot = simple_rot;
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_up  , v_off, pos, basevert, vmesh+4*STBVOX_FACE_up, mesh, STBVOX_FACE_up);
   }
   if (blockptr[-1]==0) {
      rot.facerot = (-simple_rot) & 3;
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_down, v_off, pos, basevert, vmesh+4*STBVOX_FACE_down, mesh, STBVOX_FACE_down);
   }

   if (mm->input.rotate) {
      unsigned char val = mm->input.rotate[v_off];
      rot.block   = (val >> 0) & 3;
      rot.overlay = (val >> 2) & 3;
      rot.tex2    = (val >> 4) & 3;
      rot.ecolor  = (val >> 6) & 3;
   } else {
      rot.block = rot.overlay = rot.tex2 = rot.ecolor = simple_rot;
   }
   rot.facerot = 0;

   if (blockptr[ ns_off]==0)
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_north, v_off, pos, basevert, vmesh+4*STBVOX_FACE_north, mesh, STBVOX_FACE_north);
   if (blockptr[-ns_off]==0)
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_south, v_off, pos, basevert, vmesh+4*STBVOX_FACE_south, mesh, STBVOX_FACE_south);
   if (blockptr[ ew_off]==0)
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_east , v_off, pos, basevert, vmesh+4*STBVOX_FACE_east, mesh, STBVOX_FACE_east);
   if (blockptr[-ew_off]==0)
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_west , v_off, pos, basevert, vmesh+4*STBVOX_FACE_west, mesh, STBVOX_FACE_west);
}


// void stbvox_make_mesh_for_block_with_geo(stbvox_mesh_maker *mm, stbvox_pos pos, int v_off)
//
// complex case for mesh generation: we have lots of different
// block types, and we don't want to generate faces of blocks
// if they're hidden by neighbors.
//
// we use lots of tables to determine this: we have a table
// which tells us what face type is generated for each type of
// geometry, and then a table that tells us whether that type
// is hidden by a neighbor.


#define STBVOX_MAX_GEOM     16
#define STBVOX_NUM_ROTATION  4

// this is used to determine if a face is ever generated at all
static unsigned char stbvox_hasface[STBVOX_MAX_GEOM][STBVOX_NUM_ROTATION] =
{
   { 0,0,0,0 }, // empty
   { 0,0,0,0 }, // knockout
   { 63,63,63,63 }, // solid
   { 63,63,63,63 }, // transp
   { 63,63,63,63 }, // slab
   { 63,63,63,63 }, // slab
   { 1|2|4|48, 8|1|2|48, 4|8|1|48, 2|4|8|48, }, // floor slopes
   { 1|2|4|48, 8|1|2|48, 4|8|1|48, 2|4|8|48, }, // ceil slopes
   { 47,47,47,47 }, // wall-projected diagonal with down face
   { 31,31,31,31 }, // wall-projected diagonal with up face
   { 63,63,63,63 }, // crossed-pair has special handling, but avoid early-out
   { 63,63,63,63 }, // force
   { 63,63,63,63 },
   { 63,63,63,63 },
   { 63,63,63,63 },
   { 63,63,63,63 },
};

// these are the types of faces each block can have
enum
{
   STBVOX_FT_none    ,
   STBVOX_FT_upper   ,
   STBVOX_FT_lower   ,
   STBVOX_FT_solid   ,
   STBVOX_FT_diag_012,
   STBVOX_FT_diag_023,
   STBVOX_FT_diag_013,
   STBVOX_FT_diag_123,
   STBVOX_FT_force   , // can't be covered up, used for internal faces, also hides nothing
   STBVOX_FT_partial , // only covered by solid, never covers anything else

   STBVOX_FT_count
};

// this determines which face type above is visible on each side of the geometry
static unsigned char stbvox_facetype[STBVOX_GEOM_count][6] =
{
   { 0, },  // STBVOX_GEOM_empty
   { STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid }, // knockout
   { STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid, STBVOX_FT_solid }, // solid
   { STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force }, // transp

   { STBVOX_FT_upper, STBVOX_FT_upper, STBVOX_FT_upper, STBVOX_FT_upper, STBVOX_FT_solid, STBVOX_FT_force },
   { STBVOX_FT_lower, STBVOX_FT_lower, STBVOX_FT_lower, STBVOX_FT_lower, STBVOX_FT_force, STBVOX_FT_solid },
   { STBVOX_FT_diag_123, STBVOX_FT_solid, STBVOX_FT_diag_023, STBVOX_FT_none, STBVOX_FT_force, STBVOX_FT_solid },
   { STBVOX_FT_diag_012, STBVOX_FT_solid, STBVOX_FT_diag_013, STBVOX_FT_none, STBVOX_FT_solid, STBVOX_FT_force },

   { STBVOX_FT_diag_123, STBVOX_FT_solid, STBVOX_FT_diag_023, STBVOX_FT_force, STBVOX_FT_none, STBVOX_FT_solid },
   { STBVOX_FT_diag_012, STBVOX_FT_solid, STBVOX_FT_diag_013, STBVOX_FT_force, STBVOX_FT_solid, STBVOX_FT_none },
   { STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, 0,0 }, // crossed pair
   { STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force, STBVOX_FT_force }, // GEOM_force

   { STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial, STBVOX_FT_force, STBVOX_FT_solid }, // floor vheight, all neighbors forced
   { STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial, STBVOX_FT_force, STBVOX_FT_solid }, // floor vheight, all neighbors forced
   { STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial, STBVOX_FT_solid, STBVOX_FT_force }, // ceil vheight, all neighbors forced
   { STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial,STBVOX_FT_partial, STBVOX_FT_solid, STBVOX_FT_force }, // ceil vheight, all neighbors forced
};

// This table indicates what normal to use for the "up" face of a sloped geom
// @TODO this could be done with math given the current arrangement of the enum, but let's not require it
static unsigned char stbvox_floor_slope_for_rot[4] =
{
   STBVOX_EFACE_south_up,
   STBVOX_EFACE_west_up, // @TODO: why is this reversed from what it should be? this is a north-is-up face, so slope should be south&up
   STBVOX_EFACE_north_up,
   STBVOX_EFACE_east_up,
};

static unsigned char stbvox_ceil_slope_for_rot[4] =
{
   STBVOX_EFACE_south_down,
   STBVOX_EFACE_east_down,
   STBVOX_EFACE_north_down,
   STBVOX_EFACE_west_down,
};

// this table indicates whether, for each pair of types above, a face is visible.
// each value indicates whether a given type is visible for all neighbor types
static unsigned short stbvox_face_visible[STBVOX_FT_count] =
{
   // we encode the table by listing which cases cause *obscuration*, and bitwise inverting that
   // table is pre-shifted by 5 to save a shift when it's accessed
   (unsigned short) ((~0x07ff                                          )<<5),  // none is completely obscured by everything
   (unsigned short) ((~((1<<STBVOX_FT_solid) | (1<<STBVOX_FT_upper)   ))<<5),  // upper
   (unsigned short) ((~((1<<STBVOX_FT_solid) | (1<<STBVOX_FT_lower)   ))<<5),  // lower
   (unsigned short) ((~((1<<STBVOX_FT_solid)                          ))<<5),  // solid is only completely obscured only by solid
   (unsigned short) ((~((1<<STBVOX_FT_solid) | (1<<STBVOX_FT_diag_013)))<<5),  // diag012 matches diag013
   (unsigned short) ((~((1<<STBVOX_FT_solid) | (1<<STBVOX_FT_diag_123)))<<5),  // diag023 matches diag123
   (unsigned short) ((~((1<<STBVOX_FT_solid) | (1<<STBVOX_FT_diag_012)))<<5),  // diag013 matches diag012
   (unsigned short) ((~((1<<STBVOX_FT_solid) | (1<<STBVOX_FT_diag_023)))<<5),  // diag123 matches diag023
   (unsigned short) ((~0                                               )<<5),  // force is always rendered regardless, always forces neighbor
   (unsigned short) ((~((1<<STBVOX_FT_solid)                          ))<<5),  // partial is only completely obscured only by solid
};

// the vertex heights of the block types, in binary vertex order (zyx):
// lower: SW, SE, NW, NE; upper: SW, SE, NW, NE
static stbvox_mesh_vertex stbvox_geometry_vheight[8][8] =
{
   #define STBVOX_HEIGHTS(a,b,c,d,e,f,g,h) \
     { stbvox_vertex_p(0,0,a,0,0),  \
       stbvox_vertex_p(0,0,b,0,0),  \
       stbvox_vertex_p(0,0,c,0,0),  \
       stbvox_vertex_p(0,0,d,0,0),  \
       stbvox_vertex_p(0,0,e,0,0),  \
       stbvox_vertex_p(0,0,f,0,0),  \
       stbvox_vertex_p(0,0,g,0,0),  \
       stbvox_vertex_p(0,0,h,0,0) }

   STBVOX_HEIGHTS(0,0,0,0, 2,2,2,2),
   STBVOX_HEIGHTS(0,0,0,0, 2,2,2,2),
   STBVOX_HEIGHTS(0,0,0,0, 2,2,2,2),
   STBVOX_HEIGHTS(0,0,0,0, 2,2,2,2),
   STBVOX_HEIGHTS(1,1,1,1, 2,2,2,2),
   STBVOX_HEIGHTS(0,0,0,0, 1,1,1,1),
   STBVOX_HEIGHTS(0,0,0,0, 0,0,2,2),
   STBVOX_HEIGHTS(2,2,0,0, 2,2,2,2),
};

// rotate vertices defined as [z][y][x] coords
static unsigned char stbvox_rotate_vertex[8][4] =
{
   { 0,1,3,2 }, // zyx=000
   { 1,3,2,0 }, // zyx=001
   { 2,0,1,3 }, // zyx=010
   { 3,2,0,1 }, // zyx=011
   { 4,5,7,6 }, // zyx=100
   { 5,7,6,4 }, // zyx=101
   { 6,4,5,7 }, // zyx=110
   { 7,6,4,5 }, // zyx=111
};

void stbvox_make_mesh_for_block_with_geo(stbvox_mesh_maker *mm, stbvox_pos pos, int v_off)
{
   int ns_off = mm->y_stride_in_bytes;
   int ew_off = mm->x_stride_in_bytes;
   int visible_faces, visible_base;
   unsigned char mesh;

   // first gather the geometry info for this block and all neighbors

   unsigned char bt, nbt[6];
   unsigned char geo, ngeo[6];
   unsigned char rot, nrot[6];

   bt = mm->input.blocktype[v_off];
   nbt[0] = mm->input.blocktype[v_off + ew_off];
   nbt[1] = mm->input.blocktype[v_off + ns_off];
   nbt[2] = mm->input.blocktype[v_off - ew_off];
   nbt[3] = mm->input.blocktype[v_off - ns_off];
   nbt[4] = mm->input.blocktype[v_off +      1];
   nbt[5] = mm->input.blocktype[v_off -      1];
   if (mm->input.geometry) {
      int i;
      geo = mm->input.geometry[v_off];
      ngeo[0] = mm->input.geometry[v_off + ew_off];
      ngeo[1] = mm->input.geometry[v_off + ns_off];
      ngeo[2] = mm->input.geometry[v_off - ew_off];
      ngeo[3] = mm->input.geometry[v_off - ns_off];
      ngeo[4] = mm->input.geometry[v_off +      1];
      ngeo[5] = mm->input.geometry[v_off -      1];

      #ifndef STBVOX_ROTATION_IN_LIGHTING
      rot = (geo >> 4) & 3;
      geo &= 15;
      for (i=0; i < 6; ++i) {
         nrot[i] = (ngeo[i] >> 4) & 3;
         ngeo[i] &= 15;
      }
      #endif
      STBVOX_NOTUSED(i);
   } else {
      int i;
      assert(mm->input.block_geometry);
      geo = mm->input.block_geometry[bt];
      for (i=0; i < 6; ++i)
         ngeo[i] = mm->input.block_geometry[nbt[i]];
      if (mm->input.selector) {
         #ifndef STBVOX_ROTATION_IN_LIGHTING
         rot     = (mm->input.selector[v_off         ] >> 4) & 3;
         nrot[0] = (mm->input.selector[v_off + ew_off] >> 4) & 3;
         nrot[1] = (mm->input.selector[v_off + ns_off] >> 4) & 3;
         nrot[2] = (mm->input.selector[v_off - ew_off] >> 4) & 3;
         nrot[3] = (mm->input.selector[v_off - ns_off] >> 4) & 3;
         nrot[4] = (mm->input.selector[v_off +      1] >> 4) & 3;
         nrot[5] = (mm->input.selector[v_off -      1] >> 4) & 3;
         #endif
      } else {
         #ifndef STBVOX_ROTATION_IN_LIGHTING
         rot = (geo>>4)&3;
         geo &= 15;
         for (i=0; i < 6; ++i) {
            nrot[i] = (ngeo[i]>>4)&3;
            ngeo[i] &= 15;
         }
         #endif
      }
   }

   #ifdef STBVOX_ROTATION_IN_LIGHTING
   rot = mm->input.lighting[v_off] & 3;
   nrot[0] = (mm->input.lighting[v_off + ew_off]) & 3;
   nrot[1] = (mm->input.lighting[v_off + ns_off]) & 3;
   nrot[2] = (mm->input.lighting[v_off - ew_off]) & 3;
   nrot[3] = (mm->input.lighting[v_off - ns_off]) & 3;
   nrot[4] = (mm->input.lighting[v_off +      1]) & 3;
   nrot[5] = (mm->input.lighting[v_off -      1]) & 3;
   #endif

   if (geo == STBVOX_GEOM_transp) {
      // transparency has a special rule: if the blocktype is the same,
      // and the faces are compatible, then can hide them; otherwise,
      // force them on
      // Note that this means we don't support any transparentshapes other
      // than solid blocks, since detecting them is too complicated. If
      // you wanted to do something like minecraft water, you probably
      // should just do that with a separate renderer anyway. (We don't
      // support transparency sorting so you need to use alpha test
      // anyway)
      int i;
      for (i=0; i < 6; ++i)
         if (nbt[i] != bt) {
            nbt[i] = 0;
            ngeo[i] = STBVOX_GEOM_empty;
         } else
            ngeo[i] = STBVOX_GEOM_solid;
      geo = STBVOX_GEOM_solid;
   }

   // now compute the face visibility
   visible_base = stbvox_hasface[geo][rot];
   // @TODO: assert(visible_base != 0); // we should have early-outted earlier in this case
   visible_faces = 0;

   // now, for every face that might be visible, check if neighbor hides it
   if (visible_base & (1 << STBVOX_FACE_east)) {
      int  type = stbvox_facetype[ geo   ][(STBVOX_FACE_east+ rot   )&3];
      int ntype = stbvox_facetype[ngeo[0]][(STBVOX_FACE_west+nrot[0])&3];
      visible_faces |= ((stbvox_face_visible[type]) >> (ntype + 5 - STBVOX_FACE_east)) & (1 << STBVOX_FACE_east);
   }
   if (visible_base & (1 << STBVOX_FACE_north)) {
      int  type = stbvox_facetype[ geo   ][(STBVOX_FACE_north+ rot   )&3];
      int ntype = stbvox_facetype[ngeo[1]][(STBVOX_FACE_south+nrot[1])&3];
      visible_faces |= ((stbvox_face_visible[type]) >> (ntype + 5 - STBVOX_FACE_north)) & (1 << STBVOX_FACE_north);
   }
   if (visible_base & (1 << STBVOX_FACE_west)) {
      int  type = stbvox_facetype[ geo   ][(STBVOX_FACE_west+ rot   )&3];
      int ntype = stbvox_facetype[ngeo[2]][(STBVOX_FACE_east+nrot[2])&3];
      visible_faces |= ((stbvox_face_visible[type]) >> (ntype + 5 - STBVOX_FACE_west)) & (1 << STBVOX_FACE_west);
   }
   if (visible_base & (1 << STBVOX_FACE_south)) {
      int  type = stbvox_facetype[ geo   ][(STBVOX_FACE_south+ rot   )&3];
      int ntype = stbvox_facetype[ngeo[3]][(STBVOX_FACE_north+nrot[3])&3];
      visible_faces |= ((stbvox_face_visible[type]) >> (ntype + 5 - STBVOX_FACE_south)) & (1 << STBVOX_FACE_south);
   }
   if (visible_base & (1 << STBVOX_FACE_up)) {
      int  type = stbvox_facetype[ geo   ][STBVOX_FACE_up];
      int ntype = stbvox_facetype[ngeo[4]][STBVOX_FACE_down];
      visible_faces |= ((stbvox_face_visible[type]) >> (ntype + 5 - STBVOX_FACE_up)) & (1 << STBVOX_FACE_up);
   }
   if (visible_base & (1 << STBVOX_FACE_down)) {
      int  type = stbvox_facetype[ geo   ][STBVOX_FACE_down];
      int ntype = stbvox_facetype[ngeo[5]][STBVOX_FACE_up];
      visible_faces |= ((stbvox_face_visible[type]) >> (ntype + 5 - STBVOX_FACE_down)) & (1 << STBVOX_FACE_down);
   }

   if (geo == STBVOX_GEOM_force)
      geo = STBVOX_GEOM_solid;

   assert((geo == STBVOX_GEOM_crossed_pair) ? (visible_faces == 15) : 1);

   // now we finally know for sure which faces are getting generated
   if (visible_faces == 0)
      return;

   mesh = mm->default_mesh;
   if (mm->input.selector)
      mesh = mm->input.selector[v_off];

   if (geo <= STBVOX_GEOM_ceil_slope_north_is_bottom) {
      // this is the simple case, we can just use regular block gen with special vmesh calculated with vheight
      stbvox_mesh_vertex basevert;
      stbvox_mesh_vertex vmesh[6][4];
      stbvox_rotate rotate = { 0,0,0,0,0 };
      unsigned char simple_rot = rot;
      int i;
      // we only need to do this for the displayed faces, but it's easier
      // to just do it up front; @OPTIMIZE check if it's faster to do it
      // for visible faces only
      for (i=0; i < 6*4; ++i) {
         int vert = stbvox_vertex_selector[0][i];
         vert = stbvox_rotate_vertex[vert][rot];
         vmesh[0][i] = stbvox_vmesh_pre_vheight[0][i]
                     + stbvox_geometry_vheight[geo][vert];
      }

      basevert = stbvox_vertex_p(pos.x, pos.y, pos.z<<mm->precision_z , 0,0);
      if (mm->input.selector) {
         mesh = mm->input.selector[v_off];
      }

      // check if we're going off the end
      if (mm->output_cur[mesh][0] + mm->output_size[mesh][0]*6 > mm->output_end[mesh][0]) {
         mm->full = 1;
         return;
      }

      if (geo >= STBVOX_GEOM_floor_slope_north_is_top) {
         if (visible_faces & (1 << STBVOX_FACE_up)) {
            int normal = geo == STBVOX_GEOM_floor_slope_north_is_top ? stbvox_floor_slope_for_rot[simple_rot] : STBVOX_FACE_up;
            rotate.facerot = simple_rot;
            stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_up  , v_off, pos, basevert, vmesh[STBVOX_FACE_up], mesh, normal);
         }
         if (visible_faces & (1 << STBVOX_FACE_down)) {
            int normal = geo == STBVOX_GEOM_ceil_slope_north_is_bottom ? stbvox_ceil_slope_for_rot[simple_rot] : STBVOX_FACE_down;
            rotate.facerot = (-rotate.facerot) & 3;
            stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_down, v_off, pos, basevert, vmesh[STBVOX_FACE_down], mesh, normal);
         }
      } else {
         if (visible_faces & (1 << STBVOX_FACE_up)) {
            rotate.facerot = simple_rot;
            stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_up  , v_off, pos, basevert, vmesh[STBVOX_FACE_up], mesh, STBVOX_FACE_up);
         }
         if (visible_faces & (1 << STBVOX_FACE_down)) {
            rotate.facerot = (-rotate.facerot) & 3;
            stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_down, v_off, pos, basevert, vmesh[STBVOX_FACE_down], mesh, STBVOX_FACE_down);
         }
      }

      if (mm->input.rotate) {
         unsigned char val = mm->input.rotate[v_off];
         rotate.block   = (val >> 0) & 3;
         rotate.overlay = (val >> 2) & 3;
         rotate.tex2    = (val >> 4) & 3;
         rotate.ecolor  = (val >> 6) & 3;
      } else {
         rotate.block = rotate.overlay = rotate.tex2 = rotate.ecolor = simple_rot;
      }

      rotate.facerot = 0;

      if (visible_faces & (1 << STBVOX_FACE_north))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_north, v_off, pos, basevert, vmesh[STBVOX_FACE_north], mesh, STBVOX_FACE_north);
      if (visible_faces & (1 << STBVOX_FACE_south))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_south, v_off, pos, basevert, vmesh[STBVOX_FACE_south], mesh, STBVOX_FACE_south);
      if (visible_faces & (1 << STBVOX_FACE_east))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_east , v_off, pos, basevert, vmesh[STBVOX_FACE_east ], mesh, STBVOX_FACE_east);
      if (visible_faces & (1 << STBVOX_FACE_west))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_west , v_off, pos, basevert, vmesh[STBVOX_FACE_west ], mesh, STBVOX_FACE_west);
   }
   if (geo >= STBVOX_GEOM_floor_vheight_02) {
      // this case can also be generated with regular block gen with special vmesh,
      // except:
      //     if we want to generate middle diagonal for 'weird' blocks
      //     it's more complicated to detect neighbor matchups
      stbvox_mesh_vertex vmesh[6][4];
      stbvox_mesh_vertex cube[8];
      stbvox_mesh_vertex basevert;
      stbvox_rotate rotate = { 0,0,0,0,0 };
      unsigned char simple_rot = rot;
      unsigned char ht[4];
      int extreme;

      // extract the heights
      if (mm->input.vheight) {
         unsigned char v =  mm->input.vheight[v_off];
         ht[0] = (v >> 0) & 3;
         ht[1] = (v >> 2) & 3;
         ht[2] = (v >> 4) & 3;
         ht[3] = (v >> 6) & 3;
      } else if (mm->input.block_vheight) {
         unsigned char v = mm->input.block_vheight[bt];
         unsigned char raw[4];
         int i;

         raw[0] = (v >> 0) & 3;
         raw[1] = (v >> 2) & 3;
         raw[2] = (v >> 4) & 3;
         raw[3] = (v >> 6) & 3;

         for (i=0; i < 4; ++i)
            ht[i] = raw[stbvox_rotate_vertex[i][rot]];
      } else {
         assert(0);
      }

      // flag whether any sides go off the top of the block, which means
      // our visible_faces test was wrong
      extreme = (ht[0] == 3 || ht[1] == 3 || ht[2] == 3 || ht[3] == 3);

      if (geo >= STBVOX_GEOM_ceil_vheight_02) {
         cube[0] = stbvox_vertex_p(0,0,ht[0],0,0);
         cube[1] = stbvox_vertex_p(0,0,ht[1],0,0);
         cube[2] = stbvox_vertex_p(0,0,ht[2],0,0);
         cube[3] = stbvox_vertex_p(0,0,ht[3],0,0);
         cube[4] = stbvox_vertex_p(0,0,2,0,0);
         cube[5] = stbvox_vertex_p(0,0,2,0,0);
         cube[6] = stbvox_vertex_p(0,0,2,0,0);
         cube[7] = stbvox_vertex_p(0,0,2,0,0);
      } else {
         cube[0] = stbvox_vertex_p(0,0,0,0,0);
         cube[1] = stbvox_vertex_p(0,0,0,0,0);
         cube[2] = stbvox_vertex_p(0,0,0,0,0);
         cube[3] = stbvox_vertex_p(0,0,0,0,0);
         cube[4] = stbvox_vertex_p(0,0,ht[0],0,0);
         cube[5] = stbvox_vertex_p(0,0,ht[1],0,0);
         cube[6] = stbvox_vertex_p(0,0,ht[2],0,0);
         cube[7] = stbvox_vertex_p(0,0,ht[3],0,0);
      }
      if (!mm->input.vheight && mm->input.block_vheight) {
      }

      // build vertex mesh
      {
         int i;
         for (i=0; i < 6*4; ++i) {
            int vert = stbvox_vertex_selector[0][i];
            vmesh[0][i] = stbvox_vmesh_pre_vheight[0][i]
                        + cube[vert];
         }
      }

      basevert = stbvox_vertex_p(pos.x, pos.y, pos.z<<mm->precision_z , 0,0);
      // check if we're going off the end
      if (mm->output_cur[mesh][0] + mm->output_size[mesh][0]*6 > mm->output_end[mesh][0]) {
         mm->full = 1;
         return;
      }

      // @TODO generate split faces
      if (visible_faces & (1 << STBVOX_FACE_up)) {
         #ifndef STBVOX_OPTIMIZED_VHEIGHT
         // check if it's planar
         if (geo < STBVOX_GEOM_ceil_vheight_02 && cube[5] + cube[6] != cube[4] + cube[7]) {
            // not planar, split along diagonal and make degenerate
            if (geo == STBVOX_GEOM_floor_vheight_02)
               stbvox_make_02_split_mesh_for_face(mm, rotate, STBVOX_FACE_up, STBVOX_FACE_up, v_off, pos, basevert, vmesh[STBVOX_FACE_up], mesh);
            else
               stbvox_make_13_split_mesh_for_face(mm, rotate, STBVOX_FACE_up, STBVOX_FACE_up, v_off, pos, basevert, vmesh[STBVOX_FACE_up], mesh);
         } else
         #endif
            stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_up  , v_off, pos, basevert, vmesh[STBVOX_FACE_up], mesh, STBVOX_FACE_up);
      }
      if (visible_faces & (1 << STBVOX_FACE_down)) {
         #ifndef STBVOX_OPTIMIZED_VHEIGHT
         // check if it's planar
         if (geo >= STBVOX_GEOM_ceil_vheight_02 && cube[1] + cube[2] != cube[0] + cube[3]) {
            // not planar, split along diagonal and make degenerate
            if (geo == STBVOX_GEOM_ceil_vheight_02)
               stbvox_make_02_split_mesh_for_face(mm, rotate, STBVOX_FACE_down, STBVOX_FACE_down, v_off, pos, basevert, vmesh[STBVOX_FACE_down], mesh);
            else
               stbvox_make_13_split_mesh_for_face(mm, rotate, STBVOX_FACE_down, STBVOX_FACE_down, v_off, pos, basevert, vmesh[STBVOX_FACE_down], mesh);
         } else
         #endif
            stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_down, v_off, pos, basevert, vmesh[STBVOX_FACE_down], mesh, STBVOX_FACE_down);
      }

      if (mm->input.rotate) {
         unsigned char val = mm->input.rotate[v_off];
         rotate.block   = (val >> 0) & 3;
         rotate.overlay = (val >> 2) & 3;
         rotate.tex2    = (val >> 4) & 3;
         rotate.ecolor  = (val >> 6) & 3;
      } else if (mm->input.selector) {
         rotate.block = rotate.overlay = rotate.tex2 = rotate.ecolor = simple_rot;
      }

      if ((visible_faces & (1 << STBVOX_FACE_north)) || (extreme && (ht[2] == 3 || ht[3] == 3)))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_north, v_off, pos, basevert, vmesh[STBVOX_FACE_north], mesh, STBVOX_FACE_north);
      if ((visible_faces & (1 << STBVOX_FACE_south)) || (extreme && (ht[0] == 3 || ht[1] == 3))) 
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_south, v_off, pos, basevert, vmesh[STBVOX_FACE_south], mesh, STBVOX_FACE_south);
      if ((visible_faces & (1 << STBVOX_FACE_east)) || (extreme && (ht[1] == 3 || ht[3] == 3)))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_east , v_off, pos, basevert, vmesh[STBVOX_FACE_east ], mesh, STBVOX_FACE_east);
      if ((visible_faces & (1 << STBVOX_FACE_west)) || (extreme && (ht[0] == 3 || ht[2] == 3)))
         stbvox_make_mesh_for_face(mm, rotate, STBVOX_FACE_west , v_off, pos, basevert, vmesh[STBVOX_FACE_west ], mesh, STBVOX_FACE_west);
   }

   if (geo == STBVOX_GEOM_crossed_pair) {
      // this can be generated with a special vmesh
      stbvox_mesh_vertex basevert = stbvox_vertex_p(pos.x, pos.y, pos.z<<mm->precision_z , 0,0);
      unsigned char simple_rot=0;
      stbvox_rotate rot = { 0,0,0,0,0 };
      unsigned char mesh = mm->default_mesh;
      if (mm->input.selector) {
         mesh = mm->input.selector[v_off];
         simple_rot = mesh >> 4;
         mesh &= 15;
      }

      // check if we're going off the end
      if (mm->output_cur[mesh][0] + mm->output_size[mesh][0]*4 > mm->output_end[mesh][0]) {
         mm->full = 1;
         return;
      }

      if (mm->input.rotate) {
         unsigned char val = mm->input.rotate[v_off];
         rot.block   = (val >> 0) & 3;
         rot.overlay = (val >> 2) & 3;
         rot.tex2    = (val >> 4) & 3;
         rot.ecolor  = (val >> 6) & 3;
      } else if (mm->input.selector) {
         rot.block = rot.overlay = rot.tex2 = rot.ecolor = simple_rot;
      }
      rot.facerot = 0;

      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_north, v_off, pos, basevert, stbvox_vmesh_crossed_pair[STBVOX_FACE_north], mesh, STBVOX_EFACE_ne_up);
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_south, v_off, pos, basevert, stbvox_vmesh_crossed_pair[STBVOX_FACE_south], mesh, STBVOX_EFACE_sw_up);
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_east , v_off, pos, basevert, stbvox_vmesh_crossed_pair[STBVOX_FACE_east ], mesh, STBVOX_EFACE_se_up);
      stbvox_make_mesh_for_face(mm, rot, STBVOX_FACE_west , v_off, pos, basevert, stbvox_vmesh_crossed_pair[STBVOX_FACE_west ], mesh, STBVOX_EFACE_nw_up);
   }


   // @TODO
   // STBVOX_GEOM_floor_slope_north_is_top_as_wall,
   // STBVOX_GEOM_ceil_slope_north_is_bottom_as_wall,
}

void stbvox_make_mesh_for_column(stbvox_mesh_maker *mm, int x, int y, int z0)
{
   stbvox_pos pos = { x,y,0 };
   int v_off = x * mm->x_stride_in_bytes + y * mm->y_stride_in_bytes;
   int ns_off = mm->y_stride_in_bytes;
   int ew_off = mm->x_stride_in_bytes;
   if (mm->input.geometry) {
      unsigned char *bt  = mm->input.blocktype + v_off;
      unsigned char *geo = mm->input.geometry + v_off;
      int z;
      for (z=z0; z < mm->z1; ++z) {
         if (bt[z] && ( !bt[z+ns_off] || !STBVOX_GET_GEO(geo[z+ns_off]) || !bt[z-ns_off] || !STBVOX_GET_GEO(geo[z-ns_off])
                      || !bt[z+ew_off] || !STBVOX_GET_GEO(geo[z+ew_off]) || !bt[z-ew_off] || !STBVOX_GET_GEO(geo[z-ew_off])))
         {  // TODO check up and down
            pos.z = z;
            stbvox_make_mesh_for_block_with_geo(mm, pos, v_off+z);
            if (mm->full) {
               mm->cur_z = z;
               return;
            }
         }
      }
   } else if (mm->input.block_geometry) {
      int z;
      unsigned char *bt  = mm->input.blocktype + v_off;
      unsigned char *geo = mm->input.block_geometry;
      for (z=z0; z < mm->z1; ++z) {
         if (bt[z] && (    geo[bt[z+ns_off]] != STBVOX_GEOM_solid
                        || geo[bt[z-ns_off]] != STBVOX_GEOM_solid
                        || geo[bt[z+ew_off]] != STBVOX_GEOM_solid
                        || geo[bt[z-ew_off]] != STBVOX_GEOM_solid
                        || geo[bt[z-1]] != STBVOX_GEOM_solid
                        || geo[bt[z+1]] != STBVOX_GEOM_solid))
         {
            pos.z = z;
            stbvox_make_mesh_for_block_with_geo(mm, pos, v_off+z);
            if (mm->full) {
               mm->cur_z = z;
               return;
            }
         }
      }
   } else {
      unsigned char *bt = mm->input.blocktype + v_off;
      int z;
      stbvox_mesh_vertex *vmesh = mm->precision_z ? stbvox_vmesh_delta_half_z[0] : stbvox_vmesh_delta_normal[0];
      for (z=z0; z < mm->z1; ++z) {
         // if it's solid and at least one neighbor isn't solid
         if (bt[z] && (!bt[z+ns_off] || !bt[z-ns_off] || !bt[z+ew_off] || !bt[z-ew_off] || !bt[z-1] || !bt[z+1])) {
            pos.z = z;
            stbvox_make_mesh_for_block(mm, pos, v_off+z, vmesh);
            if (mm->full) {
               mm->cur_z = z;
               return;
            }
         }
      }
   }
}

void stbvox_bring_up_to_date(stbvox_mesh_maker *mm)
{
   if (mm->config_dirty) {
      int i;
      mm->num_mesh_slots = (mm->tags & STBVOX_TAG_face_sampled ? 2 : 1);
      for (i=0; i < STBVOX_MAX_MESHES; ++i) {
         if (mm->num_mesh_slots == 2) {
            mm->output_size[i][0] = 16;
            mm->output_step[i][0] = 4;
            mm->output_size[i][1] = 4;
            mm->output_step[i][1] = 4;
         } else {
            mm->output_size[i][0] = 32;
            mm->output_step[i][0] = 8;
         }
      }

      mm->config_dirty = 0;
   }
}


int stbvox_make_mesh(stbvox_mesh_maker *mm)
{
   int x,y;
   stbvox_bring_up_to_date(mm);
   mm->full = 0;
   if (mm->cur_x || mm->cur_y || mm->cur_z) {
      stbvox_make_mesh_for_column(mm, mm->cur_x, mm->cur_y, mm->cur_z);
      if (mm->full)
         return 0;
      ++mm->cur_y;
      while (mm->cur_y < mm->y1 && !mm->full) {
         stbvox_make_mesh_for_column(mm, mm->cur_x, mm->cur_y, mm->z0);
         if (mm->full)
            return 0;
         ++mm->cur_y;
      }
   }
   for (x=mm->x0; x < mm->x1; ++x) {
      for (y=mm->y0; y < mm->y1; ++y) {
         stbvox_make_mesh_for_column(mm, x, y, mm->z0);
         if (mm->full) {
            mm->cur_x = x;
            mm->cur_y = y;
            return 0;
         }
      }
   }
   return 1;
}

void stbvox_init_mesh_maker(stbvox_mesh_maker *mm)
{
   memset(mm, 0, sizeof(*mm));
   stbvox_build_default_palette();
   mm->tags = STBVOX_TAG_textured;
   mm->precision_z  = 1;

   mm->config_dirty = 1;
   mm->default_mesh = 0;
}

int stbvox_get_buffer_count(stbvox_mesh_maker *mm)
{
   stbvox_bring_up_to_date(mm);
   return mm->num_mesh_slots;
}

int stbvox_get_buffer_size_per_quad(stbvox_mesh_maker *mm, int n)
{
   return mm->output_size[0][n];
}

void stbvox_reset_buffers(stbvox_mesh_maker *mm)
{
   int i;
   for (i=0; i < STBVOX_MAX_MESHES*STBVOX_MAX_MESH_SLOTS; ++i) {
      mm->output_cur[0][i] = 0;
      mm->output_buffer[0][i] = 0;
   }
}

void stbvox_set_buffer(stbvox_mesh_maker *mm, int mesh, int slot, void *buffer, size_t len)
{
   int i;
   stbvox_bring_up_to_date(mm);
   mm->output_buffer[mesh][slot] = (char *) buffer;
   mm->output_cur   [mesh][slot] = (char *) buffer;
   mm->output_len   [mesh][slot] = len;
   mm->output_end   [mesh][slot] = (char *) buffer + len;
   for (i=0; i < STBVOX_MAX_MESH_SLOTS; ++i) {
      if (mm->output_buffer[mesh][i]) {
         assert(mm->output_len[mesh][i] / mm->output_size[mesh][i] == mm->output_len[mesh][slot] / mm->output_size[mesh][slot]);
      }
   }
}

void stbvox_set_default_mesh(stbvox_mesh_maker *mm, int mesh)
{
   mm->default_mesh = mesh;
}

int stbvox_get_quad_count(stbvox_mesh_maker *mm, int mesh)
{
   return (mm->output_cur[mesh][0] - mm->output_buffer[mesh][0]) / mm->output_size[mesh][0];
}

stbvox_input_description *stbvox_get_input_description(stbvox_mesh_maker *mm)
{
   return &mm->input;
}

void stbvox_set_input_range(stbvox_mesh_maker *mm, int x0, int y0, int z0, int x1, int y1, int z1)
{
   mm->x0 = x0;
   mm->y0 = y0;
   mm->z0 = z0;

   mm->x1 = x1;
   mm->y1 = y1;
   mm->z1 = z1;

   mm->cur_x = x0;
   mm->cur_y = y0;
   mm->cur_z = z0;

   // @TODO validate that this range is representable in this mode
}

void stbvox_get_transform(stbvox_mesh_maker *mm, float transform[3][3])
{
   // scale
   transform[0][0] = 1.0;
   transform[0][1] = 1.0;
   transform[0][2] = mm->precision_z ? 0.5f : 1.0f;
   // translation
   transform[1][0] = (float) (mm->pos_x);
   transform[1][1] = (float) (mm->pos_y);
   transform[1][2] = (float) (mm->pos_z);
   // texture coordinate projection translation
   transform[2][0] = (float) (mm->pos_x & 63); // @TODO depends on max texture scale
   transform[2][1] = (float) (mm->pos_y & 63);
   transform[2][2] = (float) (mm->pos_z & 63);
}

void stbvox_get_bounds(stbvox_mesh_maker *mm, float bounds[2][3])
{
   bounds[0][0] = (float) (mm->pos_x + mm->x0);
   bounds[0][1] = (float) (mm->pos_y + mm->y0);
   bounds[0][2] = (float) (mm->pos_z + mm->z0);
   bounds[1][0] = (float) (mm->pos_x + mm->x1);
   bounds[1][1] = (float) (mm->pos_y + mm->y1);
   bounds[1][2] = (float) (mm->pos_z + mm->z1);
}

void stbvox_set_mesh_coordinates(stbvox_mesh_maker *mm, int x, int y, int z)
{
   mm->pos_x = x;
   mm->pos_y = y;
   mm->pos_z = z;
}

void stbvox_set_input_stride(stbvox_mesh_maker *mm, int x_stride_in_bytes, int y_stride_in_bytes)
{
   int f,v;
   mm->x_stride_in_bytes = x_stride_in_bytes;
   mm->y_stride_in_bytes = y_stride_in_bytes;
   for (f=0; f < 6; ++f) {
      for (v=0; v < 4; ++v) {
         mm->cube_vertex_offset[f][v]   =   stbvox_vertex_vector[f][v][0]    * mm->x_stride_in_bytes
                                         +  stbvox_vertex_vector[f][v][1]    * mm->y_stride_in_bytes
                                         +  stbvox_vertex_vector[f][v][2]                           ;
         mm->vertex_gather_offset[f][v] =  (stbvox_vertex_vector[f][v][0]-1) * mm->x_stride_in_bytes
                                         + (stbvox_vertex_vector[f][v][1]-1) * mm->y_stride_in_bytes
                                         + (stbvox_vertex_vector[f][v][2]-1)                        ; 
      }
   }
}

// this is designed to allow you to call it multiple times to change the mode
// in case you're using multiple variants for different purposes
void stbvox_config_use_gl(stbvox_mesh_maker *mm, int use_tex_buffer, int use_gl_modelview)
{
   mm->config_dirty = 1;

   mm->tags |= STBVOX_TAG_gl | STBVOX_TAG_all;

   if (use_tex_buffer) {
      mm->tags &= ~STBVOX_TAG_face_attribute;
      mm->tags |=  STBVOX_TAG_face_sampled;
   } else {
      mm->tags &= ~STBVOX_TAG_face_sampled;
      mm->tags |=  STBVOX_TAG_face_attribute;
   }

   if (use_gl_modelview)
      mm->tags |=  STBVOX_TAG_gl_modelview;
   else
      mm->tags &= ~STBVOX_TAG_gl_modelview;

   mm->tags &= ~(STBVOX_TAG_glsl_130 | STBVOX_TAG_glsl_150 | STBVOX_TAG_glsl_150_compatibility);
   if (use_tex_buffer)
      if (use_gl_modelview)
         mm->tags |= STBVOX_TAG_glsl_150_compatibility;
      else
         mm->tags |= STBVOX_TAG_glsl_150_compatibility;
   else
      mm->tags |= STBVOX_TAG_glsl_130;
}

void stbvox_config_set_z_precision(stbvox_mesh_maker *mm, int z_fractional_bits)
{
   assert(z_fractional_bits >= 0 && z_fractional_bits <= 1);
   mm->precision_z = z_fractional_bits;
}


#endif // STB_VOXEL_RENDER_IMPLEMENTATION
