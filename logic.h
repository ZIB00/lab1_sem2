#ifndef LOGIC_H
#define LOGIC_H

#include <stddef.h>

typedef struct {
    size_t size;
    void (*input)(void* out);
    void (*print)(const void* in);
    void (*sum)(const void* elem1, const void* elem2, void* elem_r);
    void (*multiplication)(const void* elem1, const void* elem2, void* elem_r);
    void (*addition)(const void* elem_from, void* elem_to);
    void (*set_zero)(void* elem);
} TypeInfo;

typedef struct {
    unsigned int row;
    unsigned int column;
    TypeInfo* operation;
    void* data;
} Matrix;

extern TypeInfo operation_int;
extern TypeInfo operation_float;

Matrix* create_matrix(int r, int c, TypeInfo* operation);
Matrix* create_empty_matrix(int r, int c, TypeInfo* operation);
void matrix_print(Matrix* m);
void matrix_del(Matrix* m);

void matrix_sum(Matrix* m1, Matrix* m2, Matrix* m_r);
void matrix_multiplication(Matrix* m1, Matrix* m2, Matrix* m_r);
void multiplication_by_a_scalar(Matrix* m1, void* scalar, Matrix* m_r);
void adding_a_linear_combination(Matrix* m, int r_from, int r_to, void* scalar);

void error_int(int *variable, int left, int right, char text[]);
void error_float(float *variable, float left, float right, char text[]);

#endif