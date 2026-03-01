#ifndef LOGIC_H
#define LOGIC_H

typedef struct {
    size_t size;
    void (*input)(void* out);
    void (*print)(const void* in);
    void (*sum)(const void* elem1, const void* elem2, void* elem_r);
    void (*multiplication)(const void* elem1, const void* elem2, void* elem_r);
    void (*multiplication_by_a_scalar);
    void (*adding_a_linear_combination);
    void (*set_zero)(void* elem);
} TypeInfo;

typedef struct {
    unsigned int row;
    unsigned int column;
    TypeInfo* operation;
    void* data;
} Matrix;

TypeInfo operation_int;
TypeInfo operation_float;

Matrix* create_matrix(int r, int c, TypeInfo* operation);
void matrix_print(Matrix* m1);
void matrix_del(Matrix* m1);

void matrix_sum(Matrix* m1, Matrix* m2, Matrix* m_r);
void matrix_multiplication(Matrix* m1, Matrix* m2, Matrix* m_r);
void multiplication_by_a_scalar(Matrix* m1, void* scalar, Matrix* m_r);
void adding_a_linear_combination(Matrix* m1, int r_f, int r_t, Matrix* m_r);

void error_int(int *variable, int left_boarder, int right_boarder, char error_text[]);
void error_float(int *variable, int left_boarder, int right_boarder, char error_text[]);

#endif