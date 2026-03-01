#include <stdio.h>
#include <stdlib.h>

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
    unsigned int row;
    unsigned int column;
    TypeInfo* operation;
    void* data;
} Matrix;

void input_int(void* out) { 
    scanf("%d", (int*)out); 
}
void print_int(const void* in) { 
    printf("%d ", *(int*)in); 
}

void input_float(void* out) { 
    scanf("%f", (float*)out); 
}
void print_float(const void* in) { 
    printf("%.2f ", *(float*)in); 
}

Matrix* create_matrix(int r, int c, TypeInfo* operation) {
    void* elem_loc;
    Matrix* m = malloc(sizeof(Matrix));
    if (m == NULL) {
        printf("ќшибка: недостаточно пам€ти\n");
        return 0;
    }
    m->row = r;
    m->column = c;
    m->operation = operation;
    m->data = malloc(r * c * operation->size);
    for (int i = 0; i < m->row * m->column; i++) {
        elem_loc = (char*)m->data + (i * m->operation->size);
        printf("Ёлемент [%d]: ", i);
        m->operation->input(elem_loc);
    }
    return m;
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
    free(m->data);
    free(m);
}

void addition_int(const void* elem1, const void* elem2, void* elem_r) {
    *(int*)elem_r = *(int*)elem1 + *(int*)elem2;
}

void addition_float(const void* elem1, const void* elem2, void* elem_r) {
    *(float*)elem_r = *(float*)elem1 + *(float*)elem2;
}


int matrix_addition(Matrix* m1, Matrix* m2, Matrix* m_r) {
    void* m1_elem_loc;
    void* m2_elem_loc;
    void* m_r_elem_loc;
    for (int i = 0; i < m1->row; i++) {
        for(int j = 0; j < m1->column; j++) {
            m1_elem_loc = (char*)m1->data + (i * m1->column + j) * m1->operation->size;
            m2_elem_loc = (char*)m2->data + (i * m2->column + j) * m2->operation->size;
            m_r_elem_loc = (char*)m_r->data + (i * m_r->column + j) * m_r->operation->size;
            m_r->operation->addition(m1_elem_loc, m2_elem_loc, m_r_elem_loc);
        }
    }
}

int matrix_multiplication() {

}

int multiplication_by_a_scalar() {

}

int adding_a_linear_combination() {

}

void error_float(int *variable, int left_boudary, int right_boudary, char error_text[]) {
    int c;
    int var;
    while (1) {
                if (scanf("%f", &var) == 1 && (var >= left_boudary && var <= right_boudary)) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("%s", error_text);
                }
            }
    *variable = var;
}

void error_int(int *variable, int left_boudary, int right_boudary, char error_text[]) {
    int c;
    int var;
    while (1) {
                if (scanf("%d", &var) == 1 && (var >= left_boudary && var <= right_boudary)) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("%s", error_text);
                }
            }
    *variable = var;
}