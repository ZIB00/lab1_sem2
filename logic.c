#include <stdio.h>
#include <stdlib.h>
#include "logic.h"

void input_int(void* out) {
    scanf("%d", (int*)out); 
}
void print_int(const void* in) {
    printf("%d ", *(int*)in);
}
void sum_int(const void* a, const void* b, void* r) {
    *(int*)r = *(int*)a + *(int*)b;
}
void multiplication_int(const void* a, const void* b, void* r) {
    *(int*)r = *(int*)a * *(int*)b;
}
void add_int(const void* from, void* to) {
    *(int*)to += *(int*)from;
}
void set_zero_int(void* a) {
    *(int*)a = 0;
}

TypeInfo operation_int = { sizeof(int), 
                            input_int, 
                            print_int, 
                            sum_int, 
                            multiplication_int, 
                            add_int, 
                            set_zero_int };

void input_float(void* out) {
    scanf("%f", (float*)out);
}
void print_float(const void* in) {
    printf("%.2f ", *(float*)in);
}
void sum_float(const void* a, const void* b, void* r) {
    *(float*)r = *(float*)a + *(float*)b;
}
void multiplication_float(const void* a, const void* b, void* r) {
    *(float*)r = *(float*)a * *(float*)b;
}
void add_float(const void* from, void* to) {
    *(float*)to += *(float*)from;
}
void set_zero_float(void* a) {
    *(float*)a = 0.0f;
}

TypeInfo operation_float = { sizeof(float), 
                            input_float, 
                            print_float, 
                            sum_float, 
                            multiplication_float, 
                            add_float, 
                            set_zero_float };

static void* get_location(Matrix* m, int r, int c) {
    return (char*)m->data + (r * m->column + c) * m->operation->size;
}

Matrix* create_empty_matrix(unsigned int r, unsigned int c, TypeInfo* operation) {
    Matrix* m = malloc(sizeof(Matrix));
    if (m == NULL) { printf("Ошибка: недостаточно памяти\n"); return NULL; }

    m->row = r; 
    m->column = c; 
    m->operation = operation;
    m->data = malloc(r * c * operation->size);
    return m;
}

Matrix* create_matrix(unsigned int r, unsigned int c, TypeInfo* operation) {
    Matrix* m = create_empty_matrix(r, c, operation);

    if (m != NULL) {
        for (int i = 0; i < r * c; i++) {
            printf("Элемент [%d]: ", i);
            operation->input((char*)m->data + i * operation->size);
        }
        return m;
    }
}

void matrix_print(Matrix* m) {
    void* elem_loc;

    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->column; j++) {
            elem_loc = (char*)m->data + (i * m->column + j) * m->operation->size;
            m->operation->print(elem_loc);
        }
        printf("\n");
    }
}

void matrix_del(Matrix* m) {
    if (m != NULL) {
        free(m->data);
        free(m);
    }
}

int matrix_sum(Matrix* m1, Matrix* m2, Matrix* m_r) {
    void* m1_elem_loc, *m2_elem_loc, *m_r_elem_loc;

    for (int i = 0; i < m1->row; i++) {
        for(int j = 0; j < m1->column; j++) {
            m1_elem_loc = (char*)m1->data + (i * m1->column + j) * m1->operation->size;
            m2_elem_loc = (char*)m2->data + (i * m2->column + j) * m2->operation->size;
            m_r_elem_loc = (char*)m_r->data + (i * m_r->column + j) * m_r->operation->size;
            m_r->operation->sum(m1_elem_loc, m2_elem_loc, m_r_elem_loc);
        } 
    }
    return 0;
}


int matrix_multiplication(Matrix* m1, Matrix* m2, Matrix* m_r) {
    void* res;
    void* temp = malloc(m1->operation->size);
    if (temp == NULL) { printf("Ошибка: недостаточно памяти\n"); return -1; }

    for (int i = 0; i < m1->row; i++) {
        for (int j = 0; j < m2->column; j++) {
            res = get_location(m_r, i, j);
            m1->operation->set_zero(res);
            for (int k = 0; k < m1->column; k++) {
                m1->operation->multiplication(get_location(m1, i, k), get_location(m2, k, j), temp);
                m1->operation->addition(temp, res);
            }
        }
    }
    free(temp);
    return 0;
}

int multiplication_by_a_scalar(Matrix* m, void* scalar, Matrix* m_r) {
    void* m_elem_loc;

    for (int i = 0; i < m->row * m->column; i++) {
        m_elem_loc = (char*)m->data + i * m->operation->size;
        m->operation->multiplication(m_elem_loc, scalar, (char*)m_r->data + i * m_r->operation->size);
    }
    return 0;
}

int adding_a_linear_combination(Matrix* m, int r_f, int r_t, void* scalar) {
    void* temp = malloc(m->operation->size);
    if (m == NULL) { printf("Ошибка: недостаточно памяти\n"); return -1; }

    for (int j = 0; j < m->column; j++) {
        m->operation->multiplication(get_location(m, r_f-1, j), scalar, temp);
        m->operation->addition(temp, get_location(m, r_t-1, j));
    }
    free(temp);
    return 0;
}

void error_int(int *variable, int left_boardery, int right_boardery, char error_text[]) {
    int v, c;
    while (scanf("%d", &v) != 1 || v < left_boardery || v > right_boardery) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("%s", error_text);
    }
    while ((c = getchar()) != '\n' && c != EOF);
    *variable = v;
}

void error_float(float *variable, float left_boardery, float right_boardery, char error_text[]) {
    float v; 
    int c;
    while (scanf("%f", &v) != 1 || (left_boardery < right_boardery && (v < left_boardery || v > right_boardery))) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("%s", error_text);
    }
    while ((c = getchar()) != '\n' && c != EOF);
    *variable = v;
}