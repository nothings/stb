/* stb_geo - v1.00 - public domain geometry library - http://nothings.org/stb
                          no warranty implied; use at your own risk

   Do this:
      #define STB_GEO_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   You can #define STB_GEO_ASSERT(x) before the #include to avoid using assert.h.

   QUICK NOTES:
      Simple geometry library for games and applications
      Supports 2D and 3D vector math
      Matrix operations (2x2, 3x3, 4x4)
      Quaternion operations
      Collision detection functions
      Shape generation and manipulation
      No external dependencies

   LICENSE

   See end of file for license information.

RECENT REVISION HISTORY:

      1.00  (2024-10-26) initial release

*/

#ifndef STB_GEO_H
#define STB_GEO_H

#ifdef __cplusplus
extern "C" {
#endif

// 2D vector structure
typedef struct {
    float x, y;
} stb_geo_vec2;

// 3D vector structure
typedef struct {
    float x, y, z;
} stb_geo_vec3;

// 4D vector structure
typedef struct {
    float x, y, z, w;
} stb_geo_vec4;

// 2x2 matrix structure (row-major)
typedef struct {
    float m00, m01;
    float m10, m11;
} stb_geo_mat2;

// 3x3 matrix structure (row-major)
typedef struct {
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
} stb_geo_mat3;

// 4x4 matrix structure (row-major)
typedef struct {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} stb_geo_mat4;

// Quaternion structure
typedef struct {
    float x, y, z, w;
} stb_geo_quat;

// Rectangle structure
typedef struct {
    float x, y, width, height;
} stb_geo_rect;

// Circle structure
typedef struct {
    float x, y, radius;
} stb_geo_circle;

// Sphere structure
typedef struct {
    float x, y, z, radius;
} stb_geo_sphere;

// Plane structure
typedef struct {
    stb_geo_vec3 normal;
    float distance;
} stb_geo_plane;

// Line segment structure
typedef struct {
    stb_geo_vec2 start;
    stb_geo_vec2 end;
} stb_geo_line2;

// Ray structure
typedef struct {
    stb_geo_vec3 origin;
    stb_geo_vec3 direction;
} stb_geo_ray;

// 2D vector operations
stb_geo_vec2 stb_geo_vec2_create(float x, float y);
stb_geo_vec2 stb_geo_vec2_add(stb_geo_vec2 a, stb_geo_vec2 b);
stb_geo_vec2 stb_geo_vec2_subtract(stb_geo_vec2 a, stb_geo_vec2 b);
stb_geo_vec2 stb_geo_vec2_multiply(stb_geo_vec2 a, stb_geo_vec2 b);
stb_geo_vec2 stb_geo_vec2_divide(stb_geo_vec2 a, stb_geo_vec2 b);
stb_geo_vec2 stb_geo_vec2_scale(stb_geo_vec2 v, float scalar);
float stb_geo_vec2_dot(stb_geo_vec2 a, stb_geo_vec2 b);
float stb_geo_vec2_length_squared(stb_geo_vec2 v);
float stb_geo_vec2_length(stb_geo_vec2 v);
stb_geo_vec2 stb_geo_vec2_normalize(stb_geo_vec2 v);
stb_geo_vec2 stb_geo_vec2_rotate(stb_geo_vec2 v, float angle_radians);
float stb_geo_vec2_angle(stb_geo_vec2 a, stb_geo_vec2 b);
float stb_geo_vec2_distance(stb_geo_vec2 a, stb_geo_vec2 b);

// 3D vector operations
stb_geo_vec3 stb_geo_vec3_create(float x, float y, float z);
stb_geo_vec3 stb_geo_vec3_add(stb_geo_vec3 a, stb_geo_vec3 b);
stb_geo_vec3 stb_geo_vec3_subtract(stb_geo_vec3 a, stb_geo_vec3 b);
stb_geo_vec3 stb_geo_vec3_multiply(stb_geo_vec3 a, stb_geo_vec3 b);
stb_geo_vec3 stb_geo_vec3_divide(stb_geo_vec3 a, stb_geo_vec3 b);
stb_geo_vec3 stb_geo_vec3_scale(stb_geo_vec3 v, float scalar);
float stb_geo_vec3_dot(stb_geo_vec3 a, stb_geo_vec3 b);
stb_geo_vec3 stb_geo_vec3_cross(stb_geo_vec3 a, stb_geo_vec3 b);
float stb_geo_vec3_length_squared(stb_geo_vec3 v);
float stb_geo_vec3_length(stb_geo_vec3 v);
stb_geo_vec3 stb_geo_vec3_normalize(stb_geo_vec3 v);
stb_geo_vec3 stb_geo_vec3_rotate(stb_geo_vec3 v, stb_geo_quat rotation);
float stb_geo_vec3_distance(stb_geo_vec3 a, stb_geo_vec3 b);
stb_geo_vec3 stb_geo_vec3_project(stb_geo_vec3 v, stb_geo_vec3 onto);

// 4D vector operations
stb_geo_vec4 stb_geo_vec4_create(float x, float y, float z, float w);
stb_geo_vec4 stb_geo_vec4_add(stb_geo_vec4 a, stb_geo_vec4 b);
stb_geo_vec4 stb_geo_vec4_subtract(stb_geo_vec4 a, stb_geo_vec4 b);
stb_geo_vec4 stb_geo_vec4_multiply(stb_geo_vec4 a, stb_geo_vec4 b);
stb_geo_vec4 stb_geo_vec4_divide(stb_geo_vec4 a, stb_geo_vec4 b);
stb_geo_vec4 stb_geo_vec4_scale(stb_geo_vec4 v, float scalar);
float stb_geo_vec4_dot(stb_geo_vec4 a, stb_geo_vec4 b);
float stb_geo_vec4_length_squared(stb_geo_vec4 v);
float stb_geo_vec4_length(stb_geo_vec4 v);
stb_geo_vec4 stb_geo_vec4_normalize(stb_geo_vec4 v);

// 2x2 matrix operations
stb_geo_mat2 stb_geo_mat2_identity(void);
stb_geo_mat2 stb_geo_mat2_translation(float tx, float ty);
stb_geo_mat2 stb_geo_mat2_rotation(float angle_radians);
stb_geo_mat2 stb_geo_mat2_scale(float sx, float sy);
stb_geo_mat2 stb_geo_mat2_multiply(stb_geo_mat2 a, stb_geo_mat2 b);
stb_geo_vec2 stb_geo_mat2_multiply_vec2(stb_geo_mat2 m, stb_geo_vec2 v);
stb_geo_mat2 stb_geo_mat2_transpose(stb_geo_mat2 m);
float stb_geo_mat2_determinant(stb_geo_mat2 m);
stb_geo_mat2 stb_geo_mat2_inverse(stb_geo_mat2 m);

// 3x3 matrix operations
stb_geo_mat3 stb_geo_mat3_identity(void);
stb_geo_mat3 stb_geo_mat3_translation(float tx, float ty);
stb_geo_mat3 stb_geo_mat3_rotation(float angle_radians);
stb_geo_mat3 stb_geo_mat3_scale(float sx, float sy);
stb_geo_mat3 stb_geo_mat3_multiply(stb_geo_mat3 a, stb_geo_mat3 b);
stb_geo_vec2 stb_geo_mat3_multiply_vec2(stb_geo_mat3 m, stb_geo_vec2 v);
stb_geo_mat3 stb_geo_mat3_transpose(stb_geo_mat3 m);
float stb_geo_mat3_determinant(stb_geo_mat3 m);
stb_geo_mat3 stb_geo_mat3_inverse(stb_geo_mat3 m);

// 4x4 matrix operations
stb_geo_mat4 stb_geo_mat4_identity(void);
stb_geo_mat4 stb_geo_mat4_translation(float tx, float ty, float tz);
stb_geo_mat4 stb_geo_mat4_rotation_x(float angle_radians);
stb_geo_mat4 stb_geo_mat4_rotation_y(float angle_radians);
stb_geo_mat4 stb_geo_mat4_rotation_z(float angle_radians);
stb_geo_mat4 stb_geo_mat4_rotation_euler(float pitch, float yaw, float roll);
stb_geo_mat4 stb_geo_mat4_rotation_quat(stb_geo_quat q);
stb_geo_mat4 stb_geo_mat4_scale(float sx, float sy, float sz);
stb_geo_mat4 stb_geo_mat4_perspective(float fov_y, float aspect, float near, float far);
stb_geo_mat4 stb_geo_mat4_orthographic(float left, float right, float bottom, float top, float near, float far);
stb_geo_mat4 stb_geo_mat4_look_at(stb_geo_vec3 eye, stb_geo_vec3 center, stb_geo_vec3 up);
stb_geo_mat4 stb_geo_mat4_multiply(stb_geo_mat4 a, stb_geo_mat4 b);
stb_geo_vec3 stb_geo_mat4_multiply_vec3(stb_geo_mat4 m, stb_geo_vec3 v);
stb_geo_vec4 stb_geo_mat4_multiply_vec4(stb_geo_mat4 m, stb_geo_vec4 v);
stb_geo_mat4 stb_geo_mat4_transpose(stb_geo_mat4 m);
float stb_geo_mat4_determinant(stb_geo_mat4 m);
stb_geo_mat4 stb_geo_mat4_inverse(stb_geo_mat4 m);

// Quaternion operations
stb_geo_quat stb_geo_quat_identity(void);
stb_geo_quat stb_geo_quat_from_axis_angle(stb_geo_vec3 axis, float angle_radians);
stb_geo_quat stb_geo_quat_from_euler(float pitch, float yaw, float roll);
stb_geo_quat stb_geo_quat_multiply(stb_geo_quat a, stb_geo_quat b);
stb_geo_vec3 stb_geo_quat_rotate_vec3(stb_geo_quat q, stb_geo_vec3 v);
stb_geo_quat stb_geo_quat_conjugate(stb_geo_quat q);
stb_geo_quat stb_geo_quat_inverse(stb_geo_quat q);
stb_geo_quat stb_geo_quat_normalize(stb_geo_quat q);
float stb_geo_quat_length_squared(stb_geo_quat q);
float stb_geo_quat_length(stb_geo_quat q);
void stb_geo_quat_to_euler(stb_geo_quat q, float* pitch, float* yaw, float* roll);

// Collision detection functions
int stb_geo_point_in_rect(stb_geo_vec2 point, stb_geo_rect rect);
int stb_geo_point_in_circle(stb_geo_vec2 point, stb_geo_circle circle);
int stb_geo_point_in_sphere(stb_geo_vec3 point, stb_geo_sphere sphere);
int stb_geo_point_in_plane(stb_geo_vec3 point, stb_geo_plane plane);

int stb_geo_rect_intersects_rect(stb_geo_rect a, stb_geo_rect b);
int stb_geo_circle_intersects_circle(stb_geo_circle a, stb_geo_circle b);
int stb_geo_sphere_intersects_sphere(stb_geo_sphere a, stb_geo_sphere b);
int stb_geo_sphere_intersects_plane(stb_geo_sphere sphere, stb_geo_plane plane);

int stb_geo_line_intersects_line(stb_geo_line2 a, stb_geo_line2 b, stb_geo_vec2* intersection);
int stb_geo_line_intersects_rect(stb_geo_line2 line, stb_geo_rect rect, stb_geo_vec2* intersection);
int stb_geo_ray_intersects_sphere(stb_geo_ray ray, stb_geo_sphere sphere, float* t);
int stb_geo_ray_intersects_plane(stb_geo_ray ray, stb_geo_plane plane, float* t);

// Shape generation functions
void stb_geo_generate_circle_vertices(stb_geo_vec2 center, float radius, int segments, stb_geo_vec2* vertices);
void stb_geo_generate_rect_vertices(stb_geo_rect rect, stb_geo_vec2* vertices);
void stb_geo_generate_sphere_vertices(stb_geo_sphere sphere, int segments, stb_geo_vec3* vertices, int* num_vertices);
void stb_geo_generate_plane_vertices(stb_geo_vec3 center, stb_geo_vec3 normal, float width, float height, stb_geo_vec3* vertices);

// Utility functions
float stb_geo_degrees_to_radians(float degrees);
float stb_geo_radians_to_degrees(float radians);
float stb_geo_clamp(float value, float min, float max);
float stb_geo_lerp(float a, float b, float t);
stb_geo_vec2 stb_geo_vec2_lerp(stb_geo_vec2 a, stb_geo_vec2 b, float t);
stb_geo_vec3 stb_geo_vec3_lerp(stb_geo_vec3 a, stb_geo_vec3 b, float t);
stb_geo_quat stb_geo_quat_slerp(stb_geo_quat a, stb_geo_quat b, float t);

#ifdef __cplusplus
}
#endif

#endif // STB_GEO_H

#ifdef STB_GEO_IMPLEMENTATION

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifndef STB_GEO_ASSERT
#define STB_GEO_ASSERT(x) assert(x)
#endif

#ifndef STB_GEO_PI
#define STB_GEO_PI 3.14159265358979323846f
#endif

// 2D vector operations
stb_geo_vec2 stb_geo_vec2_create(float x, float y) {
    stb_geo_vec2 v = { x, y };
    return v;
}

stb_geo_vec2 stb_geo_vec2_add(stb_geo_vec2 a, stb_geo_vec2 b) {
    return stb_geo_vec2_create(a.x + b.x, a.y + b.y);
}

stb_geo_vec2 stb_geo_vec2_subtract(stb_geo_vec2 a, stb_geo_vec2 b) {
    return stb_geo_vec2_create(a.x - b.x, a.y - b.y);
}

stb_geo_vec2 stb_geo_vec2_multiply(stb_geo_vec2 a, stb_geo_vec2 b) {
    return stb_geo_vec2_create(a.x * b.x, a.y * b.y);
}

stb_geo_vec2 stb_geo_vec2_divide(stb_geo_vec2 a, stb_geo_vec2 b) {
    STB_GEO_ASSERT(b.x != 0.0f && b.y != 0.0f);
    return stb_geo_vec2_create(a.x / b.x, a.y / b.y);
}

stb_geo_vec2 stb_geo_vec2_scale(stb_geo_vec2 v, float scalar) {
    return stb_geo_vec2_create(v.x * scalar, v.y * scalar);
}

float stb_geo_vec2_dot(stb_geo_vec2 a, stb_geo_vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float stb_geo_vec2_length_squared(stb_geo_vec2 v) {
    return v.x * v.x + v.y * v.y;
}

float stb_geo_vec2_length(stb_geo_vec2 v) {
    return sqrtf(stb_geo_vec2_length_squared(v));
}

stb_geo_vec2 stb_geo_vec2_normalize(stb_geo_vec2 v) {
    float length = stb_geo_vec2_length(v);
    STB_GEO_ASSERT(length != 0.0f);
    return stb_geo_vec2_scale(v, 1.0f / length);
}

stb_geo_vec2 stb_geo_vec2_rotate(stb_geo_vec2 v, float angle_radians) {
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    return stb_geo_vec2_create(
        v.x * cos_angle - v.y * sin_angle,
        v.x * sin_angle + v.y * cos_angle
    );
}

float stb_geo_vec2_angle(stb_geo_vec2 a, stb_geo_vec2 b) {
    float dot = stb_geo_vec2_dot(a, b);
    float len_a = stb_geo_vec2_length(a);
    float len_b = stb_geo_vec2_length(b);
    STB_GEO_ASSERT(len_a != 0.0f && len_b != 0.0f);
    float cos_angle = dot / (len_a * len_b);
    cos_angle = stb_geo_clamp(cos_angle, -1.0f, 1.0f);
    return acosf(cos_angle);
}

float stb_geo_vec2_distance(stb_geo_vec2 a, stb_geo_vec2 b) {
    return stb_geo_vec2_length(stb_geo_vec2_subtract(a, b));
}

// 3D vector operations
stb_geo_vec3 stb_geo_vec3_create(float x, float y, float z) {
    stb_geo_vec3 v = { x, y, z };
    return v;
}

stb_geo_vec3 stb_geo_vec3_add(stb_geo_vec3 a, stb_geo_vec3 b) {
    return stb_geo_vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

stb_geo_vec3 stb_geo_vec3_subtract(stb_geo_vec3 a, stb_geo_vec3 b) {
    return stb_geo_vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

stb_geo_vec3 stb_geo_vec3_multiply(stb_geo_vec3 a, stb_geo_vec3 b) {
    return stb_geo_vec3_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

stb_geo_vec3 stb_geo_vec3_divide(stb_geo_vec3 a, stb_geo_vec3 b) {
    STB_GEO_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f);
    return stb_geo_vec3_create(a.x / b.x, a.y / b.y, a.z / b.z);
}

stb_geo_vec3 stb_geo_vec3_scale(stb_geo_vec3 v, float scalar) {
    return stb_geo_vec3_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

float stb_geo_vec3_dot(stb_geo_vec3 a, stb_geo_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

stb_geo_vec3 stb_geo_vec3_cross(stb_geo_vec3 a, stb_geo_vec3 b) {
    return stb_geo_vec3_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float stb_geo_vec3_length_squared(stb_geo_vec3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float stb_geo_vec3_length(stb_geo_vec3 v) {
    return sqrtf(stb_geo_vec3_length_squared(v));
}

stb_geo_vec3 stb_geo_vec3_normalize(stb_geo_vec3 v) {
    float length = stb_geo_vec3_length(v);
    STB_GEO_ASSERT(length != 0.0f);
    return stb_geo_vec3_scale(v, 1.0f / length);
}

stb_geo_vec3 stb_geo_vec3_rotate(stb_geo_vec3 v, stb_geo_quat rotation) {
    // Quaternion rotation: v' = q * v * q^{-1}
    stb_geo_quat qv = { v.x, v.y, v.z, 0.0f };
    stb_geo_quat q_conj = stb_geo_quat_conjugate(rotation);
    stb_geo_quat result = stb_geo_quat_multiply(rotation, stb_geo_quat_multiply(qv, q_conj));
    return stb_geo_vec3_create(result.x, result.y, result.z);
}

float stb_geo_vec3_distance(stb_geo_vec3 a, stb_geo_vec3 b) {
    return stb_geo_vec3_length(stb_geo_vec3_subtract(a, b));
}

stb_geo_vec3 stb_geo_vec3_project(stb_geo_vec3 v, stb_geo_vec3 onto) {
    float onto_length_squared = stb_geo_vec3_length_squared(onto);
    STB_GEO_ASSERT(onto_length_squared != 0.0f);
    float dot = stb_geo_vec3_dot(v, onto);
    return stb_geo_vec3_scale(onto, dot / onto_length_squared);
}

// 4D vector operations
stb_geo_vec4 stb_geo_vec4_create(float x, float y, float z, float w) {
    stb_geo_vec4 v = { x, y, z, w };
    return v;
}

stb_geo_vec4 stb_geo_vec4_add(stb_geo_vec4 a, stb_geo_vec4 b) {
    return stb_geo_vec4_create(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

stb_geo_vec4 stb_geo_vec4_subtract(stb_geo_vec4 a, stb_geo_vec4 b) {
    return stb_geo_vec4_create(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

stb_geo_vec4 stb_geo_vec4_multiply(stb_geo_vec4 a, stb_geo_vec4 b) {
    return stb_geo_vec4_create(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

stb_geo_vec4 stb_geo_vec4_divide(stb_geo_vec4 a, stb_geo_vec4 b) {
    STB_GEO_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f && b.w != 0.0f);
    return stb_geo_vec4_create(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

stb_geo_vec4 stb_geo_vec4_scale(stb_geo_vec4 v, float scalar) {
    return stb_geo_vec4_create(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

float stb_geo_vec4_dot(stb_geo_vec4 a, stb_geo_vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float stb_geo_vec4_length_squared(stb_geo_vec4 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

float stb_geo_vec4_length(stb_geo_vec4 v) {
    return sqrtf(stb_geo_vec4_length_squared(v));
}

stb_geo_vec4 stb_geo_vec4_normalize(stb_geo_vec4 v) {
    float length = stb_geo_vec4_length(v);
    STB_GEO_ASSERT(length != 0.0f);
    return stb_geo_vec4_scale(v, 1.0f / length);
}

// 2x2 matrix operations
stb_geo_mat2 stb_geo_mat2_identity(void) {
    stb_geo_mat2 m = {
        1.0f, 0.0f,
        0.0f, 1.0f
    };
    return m;
}

stb_geo_mat2 stb_geo_mat2_translation(float tx, float ty) {
    (void)tx; (void)ty; // Translation is not supported in 2x2 matrix
    return stb_geo_mat2_identity();
}

stb_geo_mat2 stb_geo_mat2_rotation(float angle_radians) {
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    stb_geo_mat2 m = {
        cos_angle, -sin_angle,
        sin_angle, cos_angle
    };
    return m;
}

stb_geo_mat2 stb_geo_mat2_scale(float sx, float sy) {
    stb_geo_mat2 m = {
        sx, 0.0f,
        0.0f, sy
    };
    return m;
}

stb_geo_mat2 stb_geo_mat2_multiply(stb_geo_mat2 a, stb_geo_mat2 b) {
    stb_geo_mat2 m = {
        a.m00 * b.m00 + a.m01 * b.m10, a.m00 * b.m01 + a.m01 * b.m11,
        a.m10 * b.m00 + a.m11 * b.m10, a.m10 * b.m01 + a.m11 * b.m11
    };
    return m;
}

stb_geo_vec2 stb_geo_mat2_multiply_vec2(stb_geo_mat2 m, stb_geo_vec2 v) {
    return stb_geo_vec2_create(
        m.m00 * v.x + m.m01 * v.y,
        m.m10 * v.x + m.m11 * v.y
    );
}

stb_geo_mat2 stb_geo_mat2_transpose(stb_geo_mat2 m) {
    stb_geo_mat2 transposed = {
        m.m00, m.m10,
        m.m01, m.m11
    };
    return transposed;
}

float stb_geo_mat2_determinant(stb_geo_mat2 m) {
    return m.m00 * m.m11 - m.m01 * m.m10;
}

stb_geo_mat2 stb_geo_mat2_inverse(stb_geo_mat2 m) {
    float det = stb_geo_mat2_determinant(m);
    STB_GEO_ASSERT(det != 0.0f);
    float inv_det = 1.0f / det;
    stb_geo_mat2 inverse = {
        m.m11 * inv_det, -m.m01 * inv_det,
        -m.m10 * inv_det, m.m00 * inv_det
    };
    return inverse;
}

// 3x3 matrix operations
stb_geo_mat3 stb_geo_mat3_identity(void) {
    stb_geo_mat3 m = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat3 stb_geo_mat3_translation(float tx, float ty) {
    stb_geo_mat3 m = {
        1.0f, 0.0f, tx,
        0.0f, 1.0f, ty,
        0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat3 stb_geo_mat3_rotation(float angle_radians) {
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    stb_geo_mat3 m = {
        cos_angle, -sin_angle, 0.0f,
        sin_angle, cos_angle, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat3 stb_geo_mat3_scale(float sx, float sy) {
    stb_geo_mat3 m = {
        sx, 0.0f, 0.0f,
        0.0f, sy, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat3 stb_geo_mat3_multiply(stb_geo_mat3 a, stb_geo_mat3 b) {
    stb_geo_mat3 m = {
        a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20, a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21, a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,
        a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20, a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21, a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,
        a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20, a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21, a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22
    };
    return m;
}

stb_geo_vec2 stb_geo_mat3_multiply_vec2(stb_geo_mat3 m, stb_geo_vec2 v) {
    float x = m.m00 * v.x + m.m01 * v.y + m.m02;
    float y = m.m10 * v.x + m.m11 * v.y + m.m12;
    float w = m.m20 * v.x + m.m21 * v.y + m.m22;
    STB_GEO_ASSERT(w != 0.0f);
    return stb_geo_vec2_create(x / w, y / w);
}

stb_geo_mat3 stb_geo_mat3_transpose(stb_geo_mat3 m) {
    stb_geo_mat3 transposed = {
        m.m00, m.m10, m.m20,
        m.m01, m.m11, m.m21,
        m.m02, m.m12, m.m22
    };
    return transposed;
}

float stb_geo_mat3_determinant(stb_geo_mat3 m) {
    return m.m00 * (m.m11 * m.m22 - m.m12 * m.m21) - 
           m.m01 * (m.m10 * m.m22 - m.m12 * m.m20) + 
           m.m02 * (m.m10 * m.m21 - m.m11 * m.m20);
}

stb_geo_mat3 stb_geo_mat3_inverse(stb_geo_mat3 m) {
    float det = stb_geo_mat3_determinant(m);
    STB_GEO_ASSERT(det != 0.0f);
    float inv_det = 1.0f / det;
    
    stb_geo_mat3 inverse = {
        (m.m11 * m.m22 - m.m12 * m.m21) * inv_det, (m.m02 * m.m21 - m.m01 * m.m22) * inv_det, (m.m01 * m.m12 - m.m02 * m.m11) * inv_det,
        (m.m12 * m.m20 - m.m10 * m.m22) * inv_det, (m.m00 * m.m22 - m.m02 * m.m20) * inv_det, (m.m02 * m.m10 - m.m00 * m.m12) * inv_det,
        (m.m10 * m.m21 - m.m11 * m.m20) * inv_det, (m.m01 * m.m20 - m.m00 * m.m21) * inv_det, (m.m00 * m.m11 - m.m01 * m.m10) * inv_det
    };
    
    return inverse;
}

// 4x4 matrix operations
stb_geo_mat4 stb_geo_mat4_identity(void) {
    stb_geo_mat4 m = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat4 stb_geo_mat4_translation(float tx, float ty, float tz) {
    stb_geo_mat4 m = {
        1.0f, 0.0f, 0.0f, tx,
        0.0f, 1.0f, 0.0f, ty,
        0.0f, 0.0f, 1.0f, tz,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat4 stb_geo_mat4_rotation_x(float angle_radians) {
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    stb_geo_mat4 m = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos_angle, -sin_angle, 0.0f,
        0.0f, sin_angle, cos_angle, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat4 stb_geo_mat4_rotation_y(float angle_radians) {
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    stb_geo_mat4 m = {
        cos_angle, 0.0f, sin_angle, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sin_angle, 0.0f, cos_angle, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat4 stb_geo_mat4_rotation_z(float angle_radians) {
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    stb_geo_mat4 m = {
        cos_angle, -sin_angle, 0.0f, 0.0f,
        sin_angle, cos_angle, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat4 stb_geo_mat4_rotation_euler(float pitch, float yaw, float roll) {
    stb_geo_mat4 rx = stb_geo_mat4_rotation_x(pitch);
    stb_geo_mat4 ry = stb_geo_mat4_rotation_y(yaw);
    stb_geo_mat4 rz = stb_geo_mat4_rotation_z(roll);
    return stb_geo_mat4_multiply(stb_geo_mat4_multiply(rz, ry), rx);
}

stb_geo_mat4 stb_geo_mat4_rotation_quat(stb_geo_quat q) {
    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;
    
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    
    stb_geo_mat4 m = {
        1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
        2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f,
        2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return m;
}

stb_geo_mat4 stb_geo_mat4_scale(float sx, float sy, float sz) {
    stb_geo_mat4 m = {
        sx, 0.0f, 0.0f, 0.0f,
        0.0f, sy, 0.0f, 0.0f,
        0.0f, 0.0f, sz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return m;
}

stb_geo_mat4 stb_geo_mat4_perspective(float fov_y, float aspect, float near, float far) {
    STB_GEO_ASSERT(fov_y > 0.0f && fov_y < STB_GEO_PI);
    STB_GEO_ASSERT(aspect > 0.0f);
    STB_GEO_ASSERT(near > 0.0f);
    STB_GEO_ASSERT(far > near);
    
    float tan_half_fov = tanf(fov_y / 2.0f);
    float f = 1.0f / tan_half_fov;
    
    stb_geo_mat4 m = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (far + near) / (near - far), (2.0f * far * near) / (near - far),
        0.0f, 0.0f, -1.0f, 0.0f
    };
    
    return m;
}

stb_geo_mat4 stb_geo_mat4_orthographic(float left, float right, float bottom, float top, float near, float far) {
    STB_GEO_ASSERT(right > left);
    STB_GEO_ASSERT(top > bottom);
    STB_GEO_ASSERT(far > near);
    
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(far + near) / (far - near);
    
    stb_geo_mat4 m = {
        2.0f / (right - left), 0.0f, 0.0f, tx,
        0.0f, 2.0f / (top - bottom), 0.0f, ty,
        0.0f, 0.0f, -2.0f / (far - near), tz,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return m;
}

stb_geo_mat4 stb_geo_mat4_look_at(stb_geo_vec3 eye, stb_geo_vec3 center, stb_geo_vec3 up) {
    stb_geo_vec3 f = stb_geo_vec3_normalize(stb_geo_vec3_subtract(center, eye));
    stb_geo_vec3 s = stb_geo_vec3_normalize(stb_geo_vec3_cross(f, up));
    stb_geo_vec3 u = stb_geo_vec3_cross(s, f);
    
    stb_geo_mat4 m = {
        s.x, u.x, -f.x, -stb_geo_vec3_dot(s, eye),
        s.y, u.y, -f.y, -stb_geo_vec3_dot(u, eye),
        s.z, u.z, -f.z, -stb_geo_vec3_dot(f, eye),
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return m;
}

stb_geo_mat4 stb_geo_mat4_multiply(stb_geo_mat4 a, stb_geo_mat4 b) {
    stb_geo_mat4 m = {
        a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30, a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31, a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32, a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,
        a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30, a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31, a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32, a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,
        a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30, a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31, a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32, a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,
        a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30, a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31, a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32, a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33
    };
    return m;
}

stb_geo_vec3 stb_geo_mat4_multiply_vec3(stb_geo_mat4 m, stb_geo_vec3 v) {
    stb_geo_vec4 result = stb_geo_mat4_multiply_vec4(m, stb_geo_vec4_create(v.x, v.y, v.z, 1.0f));
    return stb_geo_vec3_create(result.x / result.w, result.y / result.w, result.z / result.w);
}

stb_geo_vec4 stb_geo_mat4_multiply_vec4(stb_geo_mat4 m, stb_geo_vec4 v) {
    return stb_geo_vec4_create(
        m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w,
        m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w,
        m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w,
        m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w
    );
}

stb_geo_mat4 stb_geo_mat4_transpose(stb_geo_mat4 m) {
    stb_geo_mat4 transposed = {
        m.m00, m.m10, m.m20, m.m30,
        m.m01, m.m11, m.m21, m.m31,
        m.m02, m.m12, m.m22, m.m32,
        m.m03, m.m13, m.m23, m.m33
    };
    return transposed;
}

float stb_geo_mat4_determinant(stb_geo_mat4 m) {
    // Calculate determinant using Laplace expansion
    float det00 = m.m00 * (m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31));
    float det01 = -m.m01 * (m.m10 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m32 - m.m22 * m.m30));
    float det02 = m.m02 * (m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m11 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m31 - m.m21 * m.m30));
    float det03 = -m.m03 * (m.m10 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m12 * (m.m20 * m.m31 - m.m21 * m.m30));
    return det00 + det01 + det02 + det03;
}

stb_geo_mat4 stb_geo_mat4_inverse(stb_geo_mat4 m) {
    float det = stb_geo_mat4_determinant(m);
    STB_GEO_ASSERT(det != 0.0f);
    float inv_det = 1.0f / det;
    
    // Calculate cofactor matrix
    stb_geo_mat4 cofactor = {
        m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31),
        - (m.m10 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m32 - m.m22 * m.m30)),
        m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m11 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m31 - m.m21 * m.m30),
        - (m.m10 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m12 * (m.m20 * m.m31 - m.m21 * m.m30)),
        
        - (m.m01 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m02 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m03 * (m.m21 * m.m32 - m.m22 * m.m31)),
        m.m00 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m02 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m03 * (m.m20 * m.m32 - m.m22 * m.m30),
        - (m.m00 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m01 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m03 * (m.m20 * m.m31 - m.m21 * m.m30)),
        m.m00 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m01 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m02 * (m.m20 * m.m31 - m.m21 * m.m30),
        
        m.m01 * (m.m12 * m.m33 - m.m13 * m.m32) - m.m02 * (m.m11 * m.m33 - m.m13 * m.m31) + m.m03 * (m.m11 * m.m32 - m.m12 * m.m31),
        - (m.m00 * (m.m12 * m.m33 - m.m13 * m.m32) - m.m02 * (m.m10 * m.m33 - m.m13 * m.m30) + m.m03 * (m.m10 * m.m32 - m.m12 * m.m30)),
        m.m00 * (m.m11 * m.m33 - m.m13 * m.m31) - m.m01 * (m.m10 * m.m33 - m.m13 * m.m30) + m.m03 * (m.m10 * m.m31 - m.m11 * m.m30),
        - (m.m00 * (m.m11 * m.m32 - m.m12 * m.m31) - m.m01 * (m.m10 * m.m32 - m.m12 * m.m30) + m.m02 * (m.m10 * m.m31 - m.m11 * m.m30)),
        
        - (m.m01 * (m.m12 * m.m23 - m.m13 * m.m22) - m.m02 * (m.m11 * m.m23 - m.m13 * m.m21) + m.m03 * (m.m11 * m.m22 - m.m12 * m.m21)),
        m.m00 * (m.m12 * m.m23 - m.m13 * m.m22) - m.m02 * (m.m10 * m.m23 - m.m13 * m.m20) + m.m03 * (m.m10 * m.m22 - m.m12 * m.m20),
        - (m.m00 * (m.m11 * m.m23 - m.m13 * m.m21) - m.m01 * (m.m10 * m.m23 - m.m13 * m.m20) + m.m03 * (m.m10 * m.m21 - m.m11 * m.m20)),
        m.m00 * (m.m11 * m.m22 - m.m12 * m.m21) - m.m01 * (m.m10 * m.m22 - m.m12 * m.m20) + m.m02 * (m.m10 * m.m21 - m.m11 * m.m20)
    };
    
    // Transpose cofactor matrix and multiply by inverse determinant
    stb_geo_mat4 inverse = stb_geo_mat4_transpose(cofactor);
    inverse.m00 *= inv_det; inverse.m01 *= inv_det; inverse.m02 *= inv_det; inverse.m03 *= inv_det;
    inverse.m10 *= inv_det; inverse.m11 *= inv_det; inverse.m12 *= inv_det; inverse.m13 *= inv_det;
    inverse.m20 *= inv_det; inverse.m21 *= inv_det; inverse.m22 *= inv_det; inverse.m23 *= inv_det;
    inverse.m30 *= inv_det; inverse.m31 *= inv_det; inverse.m32 *= inv_det; inverse.m33 *= inv_det;
    
    return inverse;
}

// Quaternion operations
stb_geo_quat stb_geo_quat_identity(void) {
    stb_geo_quat q = { 0.0f, 0.0f, 0.0f, 1.0f };
    return q;
}

stb_geo_quat stb_geo_quat_from_axis_angle(stb_geo_vec3 axis, float angle_radians) {
    stb_geo_vec3 normalized_axis = stb_geo_vec3_normalize(axis);
    float half_angle = angle_radians / 2.0f;
    float sin_half = sinf(half_angle);
    
    stb_geo_quat q = {
        normalized_axis.x * sin_half,
        normalized_axis.y * sin_half,
        normalized_axis.z * sin_half,
        cosf(half_angle)
    };
    
    return q;
}

stb_geo_quat stb_geo_quat_from_euler(float pitch, float yaw, float roll) {
    float half_pitch = pitch / 2.0f;
    float half_yaw = yaw / 2.0f;
    float half_roll = roll / 2.0f;
    
    float sin_pitch = sinf(half_pitch);
    float cos_pitch = cosf(half_pitch);
    float sin_yaw = sinf(half_yaw);
    float cos_yaw = cosf(half_yaw);
    float sin_roll = sinf(half_roll);
    float cos_roll = cosf(half_roll);
    
    stb_geo_quat q = {
        sin_roll * cos_pitch * cos_yaw - cos_roll * sin_pitch * sin_yaw,
        cos_roll * sin_pitch * cos_yaw + sin_roll * cos_pitch * sin_yaw,
        cos_roll * cos_pitch * sin_yaw - sin_roll * sin_pitch * cos_yaw,
        cos_roll * cos_pitch * cos_yaw + sin_roll * sin_pitch * sin_yaw
    };
    
    return q;
}

stb_geo_quat stb_geo_quat_multiply(stb_geo_quat a, stb_geo_quat b) {
    stb_geo_quat q = {
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
    };
    return q;
}

stb_geo_vec3 stb_geo_quat_rotate_vec3(stb_geo_quat q, stb_geo_vec3 v) {
    return stb_geo_vec3_rotate(v, q);
}

stb_geo_quat stb_geo_quat_conjugate(stb_geo_quat q) {
    stb_geo_quat conjugate = { -q.x, -q.y, -q.z, q.w };
    return conjugate;
}

stb_geo_quat stb_geo_quat_inverse(stb_geo_quat q) {
    float length_squared = stb_geo_quat_length_squared(q);
    STB_GEO_ASSERT(length_squared != 0.0f);
    float inv_length_squared = 1.0f / length_squared;
    return stb_geo_vec4_scale((stb_geo_vec4)q, inv_length_squared);
}

stb_geo_quat stb_geo_quat_normalize(stb_geo_quat q) {
    float length = stb_geo_quat_length(q);
    STB_GEO_ASSERT(length != 0.0f);
    return stb_geo_vec4_scale((stb_geo_vec4)q, 1.0f / length);
}

float stb_geo_quat_length_squared(stb_geo_quat q) {
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

float stb_geo_quat_length(stb_geo_quat q) {
    return sqrtf(stb_geo_quat_length_squared(q));
}

void stb_geo_quat_to_euler(stb_geo_quat q, float* pitch, float* yaw, float* roll) {
    STB_GEO_ASSERT(pitch != NULL && yaw != NULL && roll != NULL);
    
    float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    *roll = atan2f(sinr_cosp, cosr_cosp);
    
    float sinp = 2.0f * (q.w * q.y - q.z * q.x);
    if (fabsf(sinp) >= 1.0f) {
        *pitch = copysignf(STB_GEO_PI / 2.0f, sinp);
    } else {
        *pitch = asinf(sinp);
    }
    
    float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    *yaw = atan2f(siny_cosp, cosy_cosp);
}

// Collision detection functions
int stb_geo_point_in_rect(stb_geo_vec2 point, stb_geo_rect rect) {
    return point.x >= rect.x && point.x <= rect.x + rect.width && 
           point.y >= rect.y && point.y <= rect.y + rect.height;
}

int stb_geo_point_in_circle(stb_geo_vec2 point, stb_geo_circle circle) {
    stb_geo_vec2 delta = stb_geo_vec2_subtract(point, stb_geo_vec2_create(circle.x, circle.y));
    return stb_geo_vec2_length_squared(delta) <= circle.radius * circle.radius;
}

int stb_geo_point_in_sphere(stb_geo_vec3 point, stb_geo_sphere sphere) {
    stb_geo_vec3 delta = stb_geo_vec3_subtract(point, stb_geo_vec3_create(sphere.x, sphere.y, sphere.z));
    return stb_geo_vec3_length_squared(delta) <= sphere.radius * sphere.radius;
}

int stb_geo_point_in_plane(stb_geo_vec3 point, stb_geo_plane plane) {
    return stb_geo_vec3_dot(point, plane.normal) + plane.distance >= 0.0f;
}

int stb_geo_rect_intersects_rect(stb_geo_rect a, stb_geo_rect b) {
    return a.x < b.x + b.width && a.x + a.width > b.x && 
           a.y < b.y + b.height && a.y + a.height > b.y;
}

int stb_geo_circle_intersects_circle(stb_geo_circle a, stb_geo_circle b) {
    stb_geo_vec2 delta = stb_geo_vec2_subtract(
        stb_geo_vec2_create(a.x, a.y), 
        stb_geo_vec2_create(b.x, b.y)
    );
    float distance_squared = stb_geo_vec2_length_squared(delta);
    float radius_sum = a.radius + b.radius;
    return distance_squared <= radius_sum * radius_sum;
}

int stb_geo_sphere_intersects_sphere(stb_geo_sphere a, stb_geo_sphere b) {
    stb_geo_vec3 delta = stb_geo_vec3_subtract(
        stb_geo_vec3_create(a.x, a.y, a.z), 
        stb_geo_vec3_create(b.x, b.y, b.z)
    );
    float distance_squared = stb_geo_vec3_length_squared(delta);
    float radius_sum = a.radius + b.radius;
    return distance_squared <= radius_sum * radius_sum;
}

int stb_geo_sphere_intersects_plane(stb_geo_sphere sphere, stb_geo_plane plane) {
    float center_distance = stb_geo_vec3_dot(
        stb_geo_vec3_create(sphere.x, sphere.y, sphere.z), 
        plane.normal
    ) + plane.distance;
    return fabsf(center_distance) <= sphere.radius;
}

int stb_geo_line_intersects_line(stb_geo_line2 a, stb_geo_line2 b, stb_geo_vec2* intersection) {
    float x1 = a.start.x;
    float y1 = a.start.y;
    float x2 = a.end.x;
    float y2 = a.end.y;
    float x3 = b.start.x;
    float y3 = b.start.y;
    float x4 = b.end.x;
    float y4 = b.end.y;
    
    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (denominator == 0.0f) return 0; // Lines are parallel
    
    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;
    
    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
        if (intersection != NULL) {
            intersection->x = x1 + t * (x2 - x1);
            intersection->y = y1 + t * (y2 - y1);
        }
        return 1;
    }
    
    return 0;
}

int stb_geo_line_intersects_rect(stb_geo_line2 line, stb_geo_rect rect, stb_geo_vec2* intersection) {
    // Check if line starts or ends inside the rect
    if (stb_geo_point_in_rect(line.start, rect)) {
        if (intersection != NULL) *intersection = line.start;
        return 1;
    }
    if (stb_geo_point_in_rect(line.end, rect)) {
        if (intersection != NULL) *intersection = line.end;
        return 1;
    }
    
    // Check intersection with rect edges
    stb_geo_line2 top_edge = {
        { rect.x, rect.y },
        { rect.x + rect.width, rect.y }
    };
    stb_geo_line2 bottom_edge = {
        { rect.x, rect.y + rect.height },
        { rect.x + rect.width, rect.y + rect.height }
    };
    stb_geo_line2 left_edge = {
        { rect.x, rect.y },
        { rect.x, rect.y + rect.height }
    };
    stb_geo_line2 right_edge = {
        { rect.x + rect.width, rect.y },
        { rect.x + rect.width, rect.y + rect.height }
    };
    
    if (stb_geo_line_intersects_line(line, top_edge, intersection)) return 1;
    if (stb_geo_line_intersects_line(line, bottom_edge, intersection)) return 1;
    if (stb_geo_line_intersects_line(line, left_edge, intersection)) return 1;
    if (stb_geo_line_intersects_line(line, right_edge, intersection)) return 1;
    
    return 0;
}

int stb_geo_ray_intersects_sphere(stb_geo_ray ray, stb_geo_sphere sphere, float* t) {
    stb_geo_vec3 sphere_center = stb_geo_vec3_create(sphere.x, sphere.y, sphere.z);
    stb_geo_vec3 oc = stb_geo_vec3_subtract(ray.origin, sphere_center);
    
    float a = stb_geo_vec3_dot(ray.direction, ray.direction);
    float b = 2.0f * stb_geo_vec3_dot(oc, ray.direction);
    float c = stb_geo_vec3_dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4.0f * a * c;
    
    if (discriminant < 0.0f) return 0;
    
    float sqrt_discriminant = sqrtf(discriminant);
    float t0 = (-b - sqrt_discriminant) / (2.0f * a);
    float t1 = (-b + sqrt_discriminant) / (2.0f * a);
    
    if (t0 > 0.0f) {
        if (t != NULL) *t = t0;
        return 1;
    }
    if (t1 > 0.0f) {
        if (t != NULL) *t = t1;
        return 1;
    }
    
    return 0;
}

int stb_geo_ray_intersects_plane(stb_geo_ray ray, stb_geo_plane plane, float* t) {
    float denominator = stb_geo_vec3_dot(ray.direction, plane.normal);
    if (fabsf(denominator) < 0.00001f) return 0; // Ray is parallel to plane
    
    float numerator = -stb_geo_vec3_dot(ray.origin, plane.normal) - plane.distance;
    *t = numerator / denominator;
    
    return *t >= 0.0f;
}

// Shape generation functions
void stb_geo_generate_circle_vertices(stb_geo_vec2 center, float radius, int segments, stb_geo_vec2* vertices) {
    STB_GEO_ASSERT(segments >= 3);
    STB_GEO_ASSERT(vertices != NULL);
    
    float angle_step = 2.0f * STB_GEO_PI / segments;
    for (int i = 0; i < segments; ++i) {
        float angle = i * angle_step;
        vertices[i].x = center.x + radius * cosf(angle);
        vertices[i].y = center.y + radius * sinf(angle);
    }
}

void stb_geo_generate_rect_vertices(stb_geo_rect rect, stb_geo_vec2* vertices) {
    STB_GEO_ASSERT(vertices != NULL);
    
    vertices[0] = stb_geo_vec2_create(rect.x, rect.y);
    vertices[1] = stb_geo_vec2_create(rect.x + rect.width, rect.y);
    vertices[2] = stb_geo_vec2_create(rect.x + rect.width, rect.y + rect.height);
    vertices[3] = stb_geo_vec2_create(rect.x, rect.y + rect.height);
}

void stb_geo_generate_sphere_vertices(stb_geo_sphere sphere, int segments, stb_geo_vec3* vertices, int* num_vertices) {
    STB_GEO_ASSERT(segments >= 3);
    STB_GEO_ASSERT(vertices != NULL);
    STB_GEO_ASSERT(num_vertices != NULL);
    
    int rings = segments;
    int sides = segments * 2;
    *num_vertices = rings * sides;
    
    stb_geo_vec3 center = stb_geo_vec3_create(sphere.x, sphere.y, sphere.z);
    
    for (int ring = 0; ring < rings; ++ring) {
        float v = (float)ring / (rings - 1);
        float theta = v * STB_GEO_PI;
        float sin_theta = sinf(theta);
        float cos_theta = cosf(theta);
        
        for (int side = 0; side < sides; ++side) {
            float u = (float)side / sides;
            float phi = u * 2.0f * STB_GEO_PI;
            float sin_phi = sinf(phi);
            float cos_phi = cosf(phi);
            
            stb_geo_vec3 vertex = {
                sphere.radius * sin_theta * cos_phi,
                sphere.radius * cos_theta,
                sphere.radius * sin_theta * sin_phi
            };
            
            vertices[ring * sides + side] = stb_geo_vec3_add(center, vertex);
        }
    }
}

void stb_geo_generate_plane_vertices(stb_geo_vec3 center, stb_geo_vec3 normal, float width, float height, stb_geo_vec3* vertices) {
    STB_GEO_ASSERT(vertices != NULL);
    
    // Create orthogonal basis vectors
    stb_geo_vec3 up = stb_geo_vec3_create(0.0f, 1.0f, 0.0f);
    if (fabsf(stb_geo_vec3_dot(normal, up)) > 0.999f) {
        up = stb_geo_vec3_create(1.0f, 0.0f, 0.0f);
    }
    
    stb_geo_vec3 right = stb_geo_vec3_normalize(stb_geo_vec3_cross(normal, up));
    up = stb_geo_vec3_normalize(stb_geo_vec3_cross(right, normal));
    
    // Calculate half extents
    stb_geo_vec3 half_width = stb_geo_vec3_scale(right, width / 2.0f);
    stb_geo_vec3 half_height = stb_geo_vec3_scale(up, height / 2.0f);
    
    // Generate four vertices
    vertices[0] = stb_geo_vec3_subtract(stb_geo_vec3_subtract(center, half_width), half_height);
    vertices[1] = stb_geo_vec3_add(stb_geo_vec3_subtract(center, half_width), half_height);
    vertices[2] = stb_geo_vec3_add(stb_geo_vec3_add(center, half_width), half_height);
    vertices[3] = stb_geo_vec3_subtract(stb_geo_vec3_add(center, half_width), half_height);
}

// Utility functions
float stb_geo_degrees_to_radians(float degrees) {
    return degrees * STB_GEO_PI / 180.0f;
}

float stb_geo_radians_to_degrees(float radians) {
    return radians * 180.0f / STB_GEO_PI;
}

float stb_geo_clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float stb_geo_lerp(float a, float b, float t) {
    return a + t * (b - a);
}

stb_geo_vec2 stb_geo_vec2_lerp(stb_geo_vec2 a, stb_geo_vec2 b, float t) {
    return stb_geo_vec2_add(a, stb_geo_vec2_scale(stb_geo_vec2_subtract(b, a), t));
}

stb_geo_vec3 stb_geo_vec3_lerp(stb_geo_vec3 a, stb_geo_vec3 b, float t) {
    return stb_geo_vec3_add(a, stb_geo_vec3_scale(stb_geo_vec3_subtract(b, a), t));
}

stb_geo_quat stb_geo_quat_slerp(stb_geo_quat a, stb_geo_quat b, float t) {
    // Calculate dot product to determine shortest path
    float dot = stb_geo_vec4_dot((stb_geo_vec4)a, (stb_geo_vec4)b);
    
    // If dot is negative, flip one quaternion to take shortest path
    if (dot < 0.0f) {
        a = stb_geo_vec4_scale((stb_geo_vec4)a, -1.0f);
        dot = -dot;
    }
    
    // Clamp dot to avoid numerical issues
    dot = stb_geo_clamp(dot, -1.0f, 1.0f);
    
    // Calculate angle between quaternions
    float angle = acosf(dot);
    
    // If angle is too small, use linear interpolation
    if (angle < 0.001f) {
        return stb_geo_vec4_add(
            stb_geo_vec4_scale((stb_geo_vec4)a, 1.0f - t),
            stb_geo_vec4_scale((stb_geo_vec4)b, t)
        );
    }
    
    // Calculate interpolation factors
    float sin_angle = sinf(angle);
    float sin_t_angle = sinf(t * angle);
    float sin_one_minus_t_angle = sinf((1.0f - t) * angle);
    float s0 = sin_one_minus_t_angle / sin_angle;
    float s1 = sin_t_angle / sin_angle;
    
    // Interpolate quaternions
    return stb_geo_vec4_add(
        stb_geo_vec4_scale((stb_geo_vec4)a, s0),
        stb_geo_vec4_scale((stb_geo_vec4)b, s1)
    );
}

#endif // STB_GEO_IMPLEMENTATION