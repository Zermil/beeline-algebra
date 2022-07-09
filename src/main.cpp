#include <cstdio>
#include <cstdlib>

#define BEELINE_IMPLEMENTATION
#include "bee_algebra.hpp"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("Matrices\n--------------------");
    {
        Mat4 matrix = create_mat4(3.0f);
        scale_mat4(&matrix, 2.0f);
        GM_PRINT_MAT4(&matrix);

        Mat4 identity = create_mat4_identity(3.0f);
        GM_PRINT_MAT4(&identity);

        Mat4 add = add_mat4(&matrix, &identity);
        Mat4 sub = sub_mat4(&matrix, &identity);
        
        GM_PRINT_MAT4(&add);
        GM_PRINT_MAT4(&sub);

        Mat4 a = {};
        a.elements[0] = 1.0f;
        a.elements[1] = 2.0f;
        a.elements[4] = 3.0f;
        a.elements[5] = 4.0f;
        
        Mat4 b = {};
        b.elements[0] = 5.0f;
        b.elements[1] = 6.0f;
        b.elements[4] = 7.0f;
        b.elements[5] = 8.0f;

        Mat4 mult = mult_mat4(&a, &b);
        GM_PRINT_MAT4(&mult);

        Mat4 ortho = create_mat4_ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        Mat4 perspective = create_mat4_perspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
        GM_PRINT_MAT4(&ortho);
        GM_PRINT_MAT4(&perspective);
    }

    printf("\nVectors\n--------------------\n");
    {
        Vec2 vec2 = create_vec2(1.0f, 2.0f);
        Vec3 vec3 = create_vec3(1.0f, 2.0f, 3.0f);
        
        Vec4 vec4 = create_vec4(1.0f, 2.0f, 3.0f, 4.0f);
        scale_vec4(&vec4, 2.0f);
        
        GM_PRINT_VEC2(&vec2);
        GM_PRINT_VEC3(&vec3);
        GM_PRINT_VEC4(&vec4);

        Vec2 a = create_vec2(0.6f, -0.8f);
        Vec2 b = create_vec2(0.0f, 1.0f);
        float dot = dot_vec2(&a, &b);
        printf("Dot product: %.2f\n", dot);

        Vec3 u = create_vec3(2.0f, 0.0f, 0.0f);
        Vec3 v = create_vec3(2.0f, 2.0f, 0.0f);
        Vec3 uv = cross_vec3(&u, &v);

        GM_PRINT_VEC3(&uv);

        float len = len_vec2(&vec2);
        printf("Length: %.2f\n", len);
    }
    
    return 0;
}
