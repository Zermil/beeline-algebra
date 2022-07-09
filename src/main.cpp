#include <cstdio>
#include <cstdlib>

#define GAME_MATH_IMPLEMENTATION
#include "game_math.h"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("\nFill matrix\n");
    {
        Matrix matrix_a = matrix_create(2, 2, 3);
        GM_PRINT_MAT(&matrix_a);
        
        Matrix matrix_b = matrix_create(2, 2);
        matrix_fill(&matrix_b, 4);
        GM_PRINT_MAT(&matrix_b);

        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
    }

    printf("\nIdentity matrix\n");
    {
        Matrix identity_a = matrix_identity(4, 4);
        GM_PRINT_MAT(&identity_a);

        Matrix identity_b = matrix_identity(2, 2);
        GM_PRINT_MAT(&identity_b);
        
        matrix_free(&identity_a);
        matrix_free(&identity_b);
    }

    printf("\nMatrix basic math\n");
    {
        Matrix matrix_a = matrix_create(2, 2);
        matrix_set(&matrix_a, 0, 0, 1);
        matrix_set(&matrix_a, 0, 1, 2);
        matrix_set(&matrix_a, 1, 0, 3);
        matrix_set(&matrix_a, 1, 1, 4);
        
        Matrix matrix_b = matrix_create(2, 2);
        matrix_set(&matrix_b, 0, 0, 5);
        matrix_set(&matrix_b, 0, 1, 6);
        matrix_set(&matrix_b, 1, 0, 7);
        matrix_set(&matrix_b, 1, 1, 8);
        
        Matrix add = matrix_add(&matrix_a, &matrix_b);
        GM_PRINT_MAT(&add);

        matrix_scale(&matrix_a, 2);
        GM_PRINT_MAT(&matrix_a);

        matrix_set(&matrix_a, 0, 0, 4);
        matrix_set(&matrix_a, 0, 1, 2);
        matrix_set(&matrix_a, 1, 0, 1);
        matrix_set(&matrix_a, 1, 1, 6);

        matrix_set(&matrix_b, 0, 0, 2);
        matrix_set(&matrix_b, 0, 1, 4);
        matrix_set(&matrix_b, 1, 0, 0);
        matrix_set(&matrix_b, 1, 1, 1);
        
        Matrix sub = matrix_sub(&matrix_a, &matrix_b);
        GM_PRINT_MAT(&sub);

        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        matrix_free(&add);
        matrix_free(&sub);
    }
    
    printf("\nMultiply matricies\n");
    {
        Matrix matrix_a = matrix_create(2, 2);
        matrix_set(&matrix_a, 0, 0, 1);
        matrix_set(&matrix_a, 0, 1, 2);
        matrix_set(&matrix_a, 1, 0, 3);
        matrix_set(&matrix_a, 1, 1, 4);
    
        Matrix matrix_b = matrix_create(2, 2);
        matrix_set(&matrix_b, 0, 0, 5);
        matrix_set(&matrix_b, 0, 1, 6);
        matrix_set(&matrix_b, 1, 0, 7);
        matrix_set(&matrix_b, 1, 1, 8);

        Matrix mult = matrix_mult(&matrix_a, &matrix_b);
        GM_PRINT_MAT(&mult);
    
        matrix_free(&matrix_a);
        matrix_free(&matrix_b);
        matrix_free(&mult);
    }

    printf("\nVector basics\n");
    {
        Vector vec2 = vector_create(2);
        vector_set(&vec2, 0, 1);
        vector_set(&vec2, 1, 2);
        GM_PRINT_VEC(&vec2);

        Vector vec3 = vector_create(3);
        vector_set(&vec3, 0, 1);
        vector_set(&vec3, 1, 2);
        vector_set(&vec3, 2, 3);
        GM_PRINT_VEC(&vec3);

        Vector vec5 = vector_create(5);
        vector_set(&vec5, 0, 1);
        vector_set(&vec5, 1, 2);
        vector_set(&vec5, 2, 3);
        vector_set(&vec5, 3, 4);
        vector_set(&vec5, 4, 5);
        GM_PRINT_VEC(&vec5);

        vector_free(&vec2);
        vector_free(&vec3);
        vector_free(&vec5);
    }

    return 0;
}
