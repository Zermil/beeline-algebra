#ifndef GAME_MATH_H_
#define GAME_MATH_H_

#include <stdlib.h>
#include <stdio.h>

#ifndef NDEBUG
#define GM_ASSERT(cond, msg)                                            \
    do {                                                                \
        if (!(cond)) {                                                  \
            fprintf(stderr, "Assertion failed in %s(%d):\n\t%s\n", __FILE__, __LINE__, msg); \
            abort();                                                    \
        }                                                               \
    } while (0)

#define GM_PRINT_MAT(matrix_ptr)                                        \
    do {                                                                \
        printf("----------\n");                                         \
        for (int i = 0; i < (matrix_ptr)->rows; ++i) {                  \
            for (int j = 0; j < (matrix_ptr)->cols; ++j) {              \
                printf("%f ", (matrix_ptr)->data[i * (matrix_ptr)->cols + j]); \
            }                                                           \
            printf("\n");                                               \
        }                                                               \
    } while (0)

#define GM_PRINT_VEC(vector_ptr)                                        \
    do {                                                                \
        const char vec_comp[4] = { 'x', 'y', 'z', 'w' };                \
        printf("----------");                                           \
        for (int i = 0; i < (vector_ptr)->components; ++i) {            \
            if (i % 4 == 0) printf("\n");                               \
            printf("%c = %f; ", vec_comp[i % 4], (vector_ptr)->data[i]); \
        }                                                               \
        printf("\n");                                                   \
    } while (0)
#else
#define GM_ASSERT(cond, msg) ((void)0)
#define GM_PRINT_MAT(matrix_ptr) ((void)0)
#define GM_PRINT_VEC(vector_ptr) ((void)0)
#endif // NDEBUG

typedef struct {
    int rows;
    int cols;
    float *data;
} Matrix;

typedef struct {
    int components;
    float *data;
} Vector;

// Matrix operations
Matrix matrix_create_filled(int rows, int cols, float val);
Matrix matrix_create(int rows, int cols);
void matrix_free(Matrix *matrix);
void matrix_set(Matrix *matrix, int row, int col, float val);
void matrix_fill(Matrix *matrix, float val);
Matrix matrix_identity(int row, int col);
Matrix matrix_identity(int row, int col, float val);
Matrix matrix_add(Matrix *a, Matrix *b);
Matrix matrix_sub(Matrix *a, Matrix *b);
Matrix matrix_mult(Matrix *a, Matrix *b);
void matrix_scale(Matrix *a, float s);

// Vector operations
Vector vector_create(int components);
void vector_free(Vector *vector);
void vector_set(Vector *vector, int idx, float val);

#endif // GAME_MATH_H_
#ifdef GAME_MATH_IMPLEMENTATION

// ================================================================================
// Matrix operations
// ================================================================================
Matrix matrix_create_filled(int rows, int cols, float val)
{
    GM_ASSERT(rows > 0 && cols > 0, "Trying to create a matrix with one dimension being <= 0");
    
    Matrix matrix = {};
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = (float *) malloc(rows * cols * sizeof(float));
    
    GM_ASSERT(matrix.data != NULL, "Could not allocate memory for matrix\'s data");
    
    for (int i = 0; i < rows * cols; ++i) {
        matrix.data[i] = val;
    }
    
    return matrix;
}

Matrix matrix_create(int rows, int cols)
{
    return matrix_create_filled(rows, cols, 0.0f); 
}

void matrix_free(Matrix *matrix)
{
    GM_ASSERT(matrix->data != NULL, "Attempting to free uninitialized memory");
    
    matrix->rows = 0;
    matrix->cols = 0;
    
    free(matrix->data);
    matrix->data = NULL;
}

void matrix_set(Matrix *matrix, int row, int col, float val)
{
    GM_ASSERT(matrix->data != NULL, "Matrix\'s data is not allocated");
    GM_ASSERT((row * matrix->cols + col) < (matrix->rows * matrix->cols), "Matrix\'s index out of bounds");
    
    matrix->data[row * matrix->cols + col] = val;
}

void matrix_fill(Matrix *matrix, float val)
{
    GM_ASSERT(matrix->data != NULL, "Matrix\'s data is not allocated");
    for (int i = 0; i < matrix->rows * matrix->cols; ++i) {
        matrix->data[i] = val;
    }
}

Matrix matrix_identity(int rows, int cols, float val)
{
    Matrix matrix = matrix_create(rows, cols);
    
    for (int i = 0; i < rows * cols; i += cols + 1) {
        matrix.data[i] = val;
    }
    
    return matrix;
}

Matrix matrix_identity(int rows, int cols)
{
    return matrix_identity(rows, cols, 1.0f);
}

Matrix matrix_add(Matrix *a, Matrix *b)
{
    GM_ASSERT(a->rows == b->rows && a->cols == b->cols, "Dimensions of both matricies need to be the same");
    GM_ASSERT(a->data != NULL && b->data != NULL, "Matrix\'s data is not allocated");

    Matrix out = matrix_create(a->rows, a->cols);

    for (int i = 0; i < out.rows; ++i) {
        for (int j = 0; j < out.cols; ++j) {
            out.data[i * out.cols + j] = a->data[i * a->cols + j] + b->data[i * b->cols + j];
        }
    }
    
    return out;
}

Matrix matrix_sub(Matrix *a, Matrix *b)
{
    GM_ASSERT(a->rows == b->rows && a->cols == b->cols, "Dimensions of both matricies need to be the same");
    GM_ASSERT(a->data != NULL && b->data != NULL, "Matrix\'s data is not allocated");

    Matrix out = matrix_create(a->rows, a->cols);

    for (int i = 0; i < out.rows; ++i) {
        for (int j = 0; j < out.cols; ++j) {
            out.data[i * out.cols + j] = a->data[i * a->cols + j] - b->data[i * b->cols + j];
        }
    }
    
    return out;
}

Matrix matrix_mult(Matrix *a, Matrix *b)
{
    GM_ASSERT(a->cols == b->rows, "Left matrix\'s columns != Right matrix\'s rows");
    GM_ASSERT(a->data != NULL && b->data != NULL, "Matrix\'s data is not allocated");
    
    Matrix out = matrix_create(a->rows, b->cols);

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < b->cols; ++j) {
            for (int k = 0; k < b->rows; ++k) {
                out.data[i * out.cols + j] += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
        }
    }
    
    return out;
}

void matrix_scale(Matrix *a, float s)
{
    GM_ASSERT(a->data != NULL, "Matrix\'s data is not allocated");

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            a->data[i * a->cols + j] *= s;
        }
    }
}

// ================================================================================
// Vector Operations
// ================================================================================
Vector vector_create(int components)
{
    Vector vec = {};
    vec.components = components;
    vec.data = (float *) malloc(components * sizeof(float));

    for (int i = 0; i < components; ++i) {
        vec.data[i] = 0;
    }
    
    return vec;
}

void vector_free(Vector *vector)
{
    GM_ASSERT(vector->data != NULL, "Attempting to free uninitialized memory");
    
    vector->components = 0;
    
    free(vector->data);
    vector->data = NULL;
}

void vector_set(Vector *vector, int idx, float val)
{
    GM_ASSERT(vector->data != NULL, "Vector\'s data is not allocated");
    GM_ASSERT(idx < vector->components, "Vector\'s index out of bounds");

    vector->data[idx] = val;
}

#endif // GAME_MATH_IMPLEMENTATION
