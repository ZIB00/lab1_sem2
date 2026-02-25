#include <stdio.h>

typedef struct {
    size_t size;
    void (*input)(void* out);
    void (*print)(const void* in);
} TypeInfo;

typedef struct {
    int row;
    int column;
    TypeInfo* operation;
    void* data;
} Matrix;

void input_int(void* out) { 
    scanf("%d", (int*)out); 
}
void print_int(const void* in) { 
    printf("%d ", *(int*)in); 
}

void input_double(void* out) { 
    scanf("%lf", (double*)out); 
}
void print_double(const void* in) { 
    printf("%.2f ", *(double*)in); 
}

Matrix* create_matrix(int r, int c, TypeInfo* operation) {
    Matrix* m = malloc(sizeof(Matrix));
    if (m == NULL) {
        fprintf(stderr, "ќшибка выделени€ пам€ти\n");
        return 0;
    }
    m->row = r;
    m->column = c;
    m->operation = operation;
    m->data = malloc(r * c * operation->size);
    for (int i = 0; i < m->row * m->column; i++) {
        void* element_ptr = (char*)m->data + (i * m->operation->size);
        printf("Ёлемент [%d]: ", i);
        m->operation->input(element_ptr);
    }
    return m;
}

void matrix_print(Matrix* m) {
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->column; j++) {
            void* element_ptr = (char*)m->data + (i * m->column + j) * m->operation->size;
            m->operation->print(element_ptr);
        }
        printf("\n");
    }
}

void matrix_del(Matrix* m) {
    free(m->data);
    free(m);
}

void error_double(int *variable, int left_boarder, int right_boarder, char error_text[]) {
    int c;
    int var = *variable;
    while (1) {
                if (scanf("%f", &var) == 1 && (var >= left_boarder && var <= right_boarder)) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("%s", error_text);
                }
            }
    *variable = var;
}

void error_int(int *variable, int left_boarder, int right_boarder, char error_text[]) {
    int c;
    int var = *variable;
    while (1) {
                if (scanf("%d", &var) == 1 && (var >= left_boarder && var <= right_boarder)) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("%s", error_text);
                }
            }
    *variable = var;
}

int matrix_addition() {

}

int matrix_multiplication() {

}

int multiplication_by_a_scalar() {

}

int adding_a_linear_combination() {

}