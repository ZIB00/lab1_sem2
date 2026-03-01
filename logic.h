#ifndef LOGIC_H
#define LOGIC_H

typedef struct {
    size_t size;
    void (*input)(void* out);
    void (*print)(const void* in);
    void (*addition)(const void* elem1, const void* elem2, void* elem_r);
    void (*matrix_multiplication);
    void (*multiplication_by_a_scalar);
    void (*adding_a_linear_combination);
} TypeInfo;

typedef struct {
    int row;
    int column;
    TypeInfo* operation;
    void* data;
} Matrix;

void input_int(void* out);
void print_int(const void* in);
void addition_int(const void* elem1, const void* elem2, void* elem_r);
TypeInfo operation_int = { sizeof(int), input_int, print_int, addition_int };

void input_float(void* out);
void print_float(const void* in);
void addition_float(const void* elem1, const void* elem2, void* elem_r);
TypeInfo operation_float = { sizeof(float), input_float, print_float, addition_float };

Matrix* create_matrix(int r, int c, TypeInfo* operation);
void matrix_print(Matrix* m1);
void matrix_del(Matrix* m1);

void matrix_addition(Matrix* m1, Matrix* m2, Matrix* m_r);
void matrix_multiplication(Matrix* m1, Matrix* m2, Matrix* m_r);
void multiplication_by_a_scalar(Matrix* m1, Matrix* m2, Matrix* m_r);
void adding_a_linear_combination(Matrix* m1, Matrix* m2, Matrix* m_r);

void error_int(int *variable, int left_boarder, int right_boarder, char error_text[]);
void error_float(int *variable, int left_boarder, int right_boarder, char error_text[]);

#endif