#include <stdio.h>

typedef struct {
    void (*create_matrix)(const void*)
} TypeInfo;

void error(int *variable, int left_boarder, int right_boarder, char error_text[]) {
    int c;
    int var = *variable;
    while (1) {
                if (scanf("%d", &var) == 1 && (var >= left_boarder && var <= right_boarder)) {
                    while ((c = getchar()) != '\n');
                    break;
                } else {
                    while ((c = getchar()) != '\n');
                    printf("%s", error_text);
                }
            }
    *variable = var;
}

void create_matrix_int(int size, const void* num) {
    printf("%d, %d\n", *(int*)num);
}

void create_matrix_float(int size, const void* num) {
    printf("%d, %f\n", *(float*)num);
}

int matrix_addition() {

}

int matrix_multiplication() {

}

int multiplication_by_a_scalar() {

}

int adding_a_linear_combination() {

}