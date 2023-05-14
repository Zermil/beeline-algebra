#ifndef BEELINE_ALGEBRA_H
#define BEELINE_ALGEBRA_H

#ifndef BEELINE_SQRT
#include <math.h>
#define BEELINE_SQRT(x) sqrtf(x)
#endif BEELINE_SQRT

#ifndef NDEBUG
#include <stdio.h>
#include <stdlib.h>
#define GM_ASSERT(cond, msg) _gm_assert((cond), (msg), __LINE__, __FILE__)
#define GM_PRINT_MAT4(mat4_ptr) _gm_print_mat4((mat4_ptr))
#define GM_PRINT_VEC2(vec2_ptr) _gm_print_vec2((vec2_ptr))
#define GM_PRINT_VEC3(vec3_ptr) _gm_print_vec3((vec3_ptr))
#define GM_PRINT_VEC4(vec4_ptr) _gm_print_vec4((vec4_ptr))
#else // DEBUG
#define GM_ASSERT(cond, msg) ((void)0)
#define GM_PRINT_MAT4(mat4_ptr) ((void)0)
#define GM_PRINT_VEC2(vec2_ptr) ((void)0)
#define GM_PRINT_VEC3(vec3_ptr) ((void)0)
#define GM_PRINT_VEC4(vec4_ptr) ((void)0)
#endif // NDEBUG

union Vec2 {
    float elements[2];
  
    struct {
        float x;
        float y;
    };
};

union Vec3 {
    float elements[3];
  
    struct {
        float x;
        float y;
        float z;
    };
  
    struct {
        float r;
        float g;
        float b;
    };
  
    struct {
        Vec2 xy;
        float _dummy0;
    };
  
    struct {
        float _dummy1;
        Vec2 yz;
    };
};

union Vec4 {
    float elements[4];
  
    struct {
        float x;
        float y;
        float z;
        float w;
    };
  
    struct {
        float r;
        float g;
        float b;
        float a;
    };
  
    struct {
        Vec3 xyz;
        float _dummy0;
    };
  
    struct {
        float _dummy1;
        Vec3 yzw;
    };
  
    struct {
        Vec2 xy;
        float _dummy2;
        float _dummy3;
    };
  
    struct {
        float _dummy4;
        Vec2 yz;
        float _dummy5;
    };
  
    struct {
        float _dummy6;
        float _dummy7;
        Vec2 zw;
    };
};

union Mat4 {
    float elements[4 * 4];
};

Mat4 create_mat4(float num);
Mat4 create_mat4();
Mat4 create_mat4_identity(float num);
Mat4 create_mat4_identity();
Mat4 create_mat4_ortho(float l, float r, float b, float t, float n, float f);
Mat4 create_mat4_ortho(float l, float r, float b, float t);
Mat4 create_mat4_perspective(float fov_degrees, float aspect, float n, float f);
Mat4 sub_mat4(Mat4 *a, Mat4 *b);
Mat4 add_mat4(Mat4 *a, Mat4 *b);
Mat4 mult_mat4(Mat4 *a, Mat4 *b);
void scale_all_mat4(Mat4 *matrix, float scale);
void scale_assign_mat4(Mat4 *matrix, float x, float y, float z);
void scale_mat4(Mat4 *matrix, float x, float y, float z);
Mat4 transpose_mat4(Mat4 *matrix);
Mat4 create_mat4_translation(float x, float y, float z);
void translate_add_mat4(Mat4 *matrix, float x, float y, float z);
void translate_mat4(Mat4 *matrix, float x, float y, float z);

Vec2 create_vec2(float x, float y);
Vec2 create_vec2();
void scale_vec2(Vec2 *vec, float scale);
float dot_vec2(Vec2 *a, Vec2 *b);
void add_vec2_scalar(Vec2 *vec, float scalar);
void negate_vec2(Vec2 *vec);
Vec2 add_vec2(Vec2 *a, Vec2 *b);
Vec2 sub_vec2(Vec2 *a, Vec2 *b);
float len_vec2(Vec2 *vec);
float len_vec2_sqrt(Vec2 *vec);
void norm_vec2(Vec2 *vec);

Vec3 create_vec3(float x, float y, float z);
Vec3 create_vec3();
void scale_vec3(Vec3 *vec, float scale);
float dot_vec3(Vec3 *a, Vec3 *b);
Vec3 cross_vec3(Vec3 *a, Vec3 *b);
void add_vec3_scalar(Vec3 *vec, float scalar);
void negate_vec3(Vec3 *vec);
Vec3 add_vec3(Vec3 *a, Vec3 *b);
Vec3 sub_vec3(Vec3 *a, Vec3 *b);
float len_vec3(Vec3 *vec);
float len_vec3_sqrt(Vec3 *vec);
void norm_vec3(Vec3 *vec);

Vec4 create_vec4(float x, float y, float z, float w);
Vec4 create_vec4();
void scale_vec4(Vec4 *vec, float scale);
float dot_vec4(Vec4 *a, Vec4 *b);
void add_vec4_scalar(Vec4 *vec, float scalar);
void negate_vec4(Vec4 *vec);
Vec4 add_vec4(Vec4 *a, Vec4 *b);
Vec4 sub_vec4(Vec4 *a, Vec4 *b);
float len_vec4(Vec4 *vec);
float len_vec4_sqrt(Vec4 *vec);
void norm_vec4(Vec4 *vec);

float min(float a, float b);
float max(float a, float b);
float clamp(float v, float lower, float higher);
float lerp(float lower, float higher, float v);
float ilerp(float lower, float higher, float v);

#ifndef NDEBUG
void _gm_assert(int cond, const char *msg, int line, const char *file);
void _gm_print_mat4(Mat4 *matrix);
void _gm_print_vec2(Vec2 *vec);
void _gm_print_vec3(Vec3 *vec);
void _gm_print_vec4(Vec4 *vec);
#endif // NDEBUG

#endif // BEELINE_ALGEBRA_H
#ifdef BEELINE_IMPLEMENTATION

// ===========================================================================
// Matrix
// ===========================================================================
Mat4 create_mat4(float num)
{
    Mat4 out = {};
  
    for (int i = 0; i < 4 * 4; ++i) {
        out.elements[i] = num;
    }
  
    return out;
}

Mat4 create_mat4()
{
    return create_mat4(0.0f);
}

Mat4 create_mat4_identity(float num)
{
    Mat4 out = {};
  
    out.elements[0] = num;
    out.elements[5] = num;
    out.elements[10] = num;
    out.elements[15] = num;
  
    return out;
}

Mat4 create_mat4_identity()
{
    return create_mat4_identity(1.0f);
}

Mat4 create_mat4_ortho(float l, float r, float b, float t, float n, float f)
{
    Mat4 out = {};
  
    out.elements[0] = 2.0f / (r - l);
    out.elements[3] = -(r + l) / (r - l);
    out.elements[5] = 2.0f / (t - b);
    out.elements[7] = -(t + b) / (t - b);
    out.elements[10] = -2.0f / (f - n);
    out.elements[11] = -(f + n) / (f - n);
    out.elements[15] = 1.0f;
  
    return out;
}

Mat4 create_mat4_ortho(float l, float r, float b, float t)
{
    Mat4 out = {};
  
    out.elements[0] = 2.0f / (r - l);
    out.elements[5] = 2.0f / (t - b);
    out.elements[10] = -1.0f;
    out.elements[15] = 1.0f;
    out.elements[3] = -(r + l) / (r - l);
    out.elements[7] = -(t + b) / (t - b);
  
    return out;
}

Mat4 create_mat4_perspective(float fov_degrees, float aspect, float n, float f)
{
    Mat4 out = {};
  
    float radians = fov_degrees * (3.14159f / 180.0f);
    float t = n * tanf(radians / 2.0f);
    float b = -t;
    float r = t * aspect;
    float l = -r;
  
    out.elements[0] = 2.0f * n / (r - l);
    out.elements[3] = -n * (r + l) / (r - l);
    out.elements[5] = 2.0f * n / (t - b);
    out.elements[7] = n * (t + b) / (t - b);
    out.elements[10] = -(f + n) / (f - n);
    out.elements[11] = 2.0f * f * n / (n - f);
    out.elements[14] = -1.0f;
  
    return out;
}

void scale_all_mat4(Mat4 *matrix, float scale)
{
    for (int i = 0; i < 4 * 4; ++i) {
        matrix->elements[i] *= scale;
    }
}

void scale_assign_mat4(Mat4 *matrix, float x, float y, float z)
{
    matrix->elements[0] = x;
    matrix->elements[5] = y;
    matrix->elements[10] = z;
}

void scale_mat4(Mat4 *matrix, float x, float y, float z)
{
    matrix->elements[0] *= x;
    matrix->elements[5] *= y;
    matrix->elements[10] *= z;
}

Mat4 sub_mat4(Mat4 *a, Mat4 *b)
{
    Mat4 out = {};
  
    for (int i = 0; i < 4 * 4; ++i) {
        out.elements[i] = a->elements[i] - b->elements[i];
    }
  
    return out;
}

Mat4 add_mat4(Mat4 *a, Mat4 *b)
{
    Mat4 out = {};
  
    for (int i = 0; i < 4 * 4; ++i) {
        out.elements[i] = a->elements[i] + b->elements[i];
    }
  
    return out;    
}

Mat4 mult_mat4(Mat4 *a, Mat4 *b)
{
    Mat4 out = {};
  
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                out.elements[i * 4 + j] += a->elements[i * 4 + k] * b->elements[k * 4 + j];
            }
        }
    }
  
    return out;
}

Mat4 transpose_mat4(Mat4 *matrix)
{
    Mat4 out = {};
  
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out.elements[j * 4 + i] = matrix->elements[i * 4 + j];
        }
    }
  
    return out;
}

Mat4 create_mat4_translation(float x, float y, float z)
{
    Mat4 out = create_mat4_identity();
  
    out.elements[3] = x;
    out.elements[7] = y;
    out.elements[11] = z;
  
    return out;
}

void translate_add_mat4(Mat4 *matrix, float x, float y, float z)
{
    matrix->elements[3] += x;
    matrix->elements[7] += y;
    matrix->elements[11] += z;
}

void translate_mat4(Mat4 *matrix, float x, float y, float z)
{
    matrix->elements[3] = x;
    matrix->elements[7] = y;
    matrix->elements[11] = z;
}

// ===========================================================================
// Vectors
// ===========================================================================
Vec2 create_vec2(float x, float y)
{
    Vec2 out = {};
  
    out.x = x;
    out.y = y;
  
    return out;
}

Vec2 create_vec2()
{
    return create_vec2(0.0f, 0.0f);
}

void scale_vec2(Vec2 *vec, float scale)
{
    vec->x *= scale;
    vec->y *= scale;
}

float dot_vec2(Vec2 *a, Vec2 *b)
{
    return (a->x * b->x) + (a->y * b->y);
}

void add_vec2_scalar(Vec2 *vec, float scalar)
{
    vec->x += scalar;
    vec->y += scalar;
}

void negate_vec2(Vec2 *vec)
{
    vec->x = -(vec->x);
    vec->y = -(vec->y);
}

Vec2 add_vec2(Vec2 *a, Vec2 *b)
{
    Vec2 out = {};
  
    out.x = a->x + b->x;
    out.y = a->y + b->y;
  
    return out;
}

Vec2 sub_vec2(Vec2 *a, Vec2 *b)
{
    Vec2 out = {};
  
    out.x = a->x - b->x;
    out.y = a->y - b->y;
  
    return out;
}

float len_vec2(Vec2 *vec)
{
    return (vec->x * vec->x) + (vec->y * vec->y);
}

float len_vec2_sqrt(Vec2 *vec)
{
    return BEELINE_SQRT(len_vec2(vec));
}

void norm_vec2(Vec2 *vec)
{
    float len = len_vec2_sqrt(vec);
  
    vec->x = vec->x / len;
    vec->y = vec->y / len;
}

Vec3 create_vec3(float x, float y, float z)
{
    Vec3 out = {};
  
    out.x = x;
    out.y = y;
    out.z = z;
  
    return out;
}

Vec3 create_vec3()
{
    return create_vec3(0.0f, 0.0f, 0.0f);
}

void scale_vec3(Vec3 *vec, float scale)
{
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
}

float dot_vec3(Vec3 *a, Vec3 *b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

Vec3 cross_vec3(Vec3 *a, Vec3 *b)
{
    Vec3 out = {};
  
    out.x = (a->y * b->z) - (a->z * b->y);
    out.y = (a->z * b->x) - (a->x * b->z);
    out.z = (a->x * b->y) - (a->y * b->x);
  
    return out;
}

void add_vec3_scalar(Vec3 *vec, float scalar)
{
    vec->x += scalar;
    vec->y += scalar;
    vec->z += scalar;
}

void negate_vec3(Vec3 *vec)
{
    vec->x = -(vec->x);
    vec->y = -(vec->y);
    vec->z = -(vec->z); 
}

Vec3 add_vec3(Vec3 *a, Vec3 *b)
{
    Vec3 out = {};
  
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    out.z = a->z + b->z;
  
    return out;
}

Vec3 sub_vec3(Vec3 *a, Vec3 *b)
{
    Vec3 out = {};
  
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    out.z = a->z - b->z;
  
    return out;
}

float len_vec3(Vec3 *vec)
{
    return (vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z);
}

float len_vec3_sqrt(Vec3 *vec)
{
    return BEELINE_SQRT(len_vec3(vec));
}

void norm_vec3(Vec3 *vec)
{
    float len = len_vec3_sqrt(vec);
  
    vec->x = vec->x / len;
    vec->y = vec->y / len;
    vec->z = vec->z / len;
}

Vec4 create_vec4(float x, float y, float z, float w)
{
    Vec4 out = {};
  
    out.x = x;
    out.y = y;
    out.z = z;
    out.w = w;
  
    return out;
}

Vec4 create_vec4()
{
    return create_vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void scale_vec4(Vec4 *vec, float scale)
{
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
    vec->w *= scale;
}

float dot_vec4(Vec4 *a, Vec4 *b)
{
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
}

void add_vec4_scalar(Vec4 *vec, float scalar)
{
    vec->x += scalar;
    vec->y += scalar;
    vec->z += scalar;
    vec->w += scalar;
}

void negate_vec4(Vec4 *vec)
{
    vec->x = -(vec->x);
    vec->y = -(vec->y);
    vec->z = -(vec->z);
    vec->w = -(vec->w);
}

Vec4 add_vec4(Vec4 *a, Vec4 *b)
{
    Vec4 out = {};
  
    out.x = a->x + b->x;
    out.y = a->y + b->y;
    out.z = a->z + b->z;
    out.w = a->w + b->w;
  
    return out;   
}

Vec4 sub_vec4(Vec4 *a, Vec4 *b)
{
    Vec4 out = {};
  
    out.x = a->x - b->x;
    out.y = a->y - b->y;
    out.z = a->z - b->z;
    out.w = a->w - b->w;
  
    return out;   
}

float len_vec4(Vec4 *vec)
{
    return (vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z) + (vec->w * vec->w);
}

float len_vec4_sqrt(Vec4 *vec)
{
    return BEELINE_SQRT(len_vec4(vec));
}

void norm_vec4(Vec4 *vec)
{
    float len = len_vec4_sqrt(vec);
  
    vec->x = vec->x / len;
    vec->y = vec->y / len;
    vec->z = vec->z / len;
    vec->w = vec->w / len;
}

// ===========================================================================
// Math independent from vectors and matrices
// ===========================================================================
float min(float a, float b)
{
    return (a > b) ? b : a;
}

float max(float a, float b) 
{
    return (a > b) ? a : b;
}

float clamp(float v, float lower, float higher)
{
    return max(lower, min(v, higher));
}

float lerp(float lower, float higher, float v)
{
    return (higher - lower) * v + lower;
}

float ilerp(float lower, float higher, float v)
{
    return (v - lower) / (higher - lower);
}

// ===========================================================================
// Debug utilities
// ===========================================================================
#ifndef NDEBUG
void _gm_assert(int cond, const char *msg, int line, const char *file)
{
    if (!cond) {
        printf("Assertion failed in %s(%d)\n\t%s\n", file, line, msg);
        exit(1);
    }
}

void _gm_print_mat4(Mat4 *matrix)
{
    printf("\n");
  
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f ", matrix->elements[i * 4 + j]);
        }
    
        printf("\n");
    }
}

void _gm_print_vec2(Vec2 *vec)
{
    printf("x: %.2f y: %.2f\n", vec->x, vec->y);
}

void _gm_print_vec3(Vec3 *vec)
{
    printf("x: %.2f y: %.2f z: %.2f\n", vec->x, vec->y, vec->z);
}

void _gm_print_vec4(Vec4 *vec)
{
    printf("x: %.2f y: %.2f z: %.2f w: %.2f\n", vec->x, vec->y, vec->z, vec->w);
}
#endif // NDEBUG
#endif // BEELINE_IMPLEMENTATION
