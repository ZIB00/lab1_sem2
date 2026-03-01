#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "logic.h"
#define MAX_SIZE 500 //500 произвольно взятое число, нужно, чтобы не работать со слишком большими матрицами

int main() {
    int size = 0; //Размер квадратной матрицы
    int type_of_numbers; //Первое число в матрице
    int type_of_operation = 0; //Тип операции над матрицей
    int flag = 0; //Нужен для выяснения необходимости повторить программу
    int c = 0; //Для getchar()
    int scalar_int;
    float scalar_float;
    int row_from, row_to;
    TypeInfo* selected_operation;
    Matrix* matrix1;
    Matrix* matrix2;
    Matrix* matrix_result;
    Matrix* matrix_buffer;

    setlocale(LC_ALL, "Russian");

    while (1) {
        printf("Квадратную матрицу какого размера вы ходите задать? (от 1 до %d)\n", MAX_SIZE); 
        error_int(&size, 1, MAX_SIZE, "Ошибка: выбери число от 1 до 500\n");
        printf("Выберите тип чисел, написав соответствующее число\n"
            "1. Целые\n"
            "2. Вещественные\n");
        error_int(&type_of_numbers, 1, 2, "Ошибка: 1 — Целые, 2 — Вещественные, напишите 1 или 2\n");
        if (type_of_numbers == 1) {
            selected_operation = &operation_int;
        } else {
            selected_operation = &operation_float;
        }
        matrix1 = create_matrix(size, size, selected_operation);

        printf("\nВаша матрица:\n");
        matrix_print(matrix1);

        while (type_of_operation != 5) {
            printf("Какую операцию сделать c матрицей? впишите соответствующую цифру\n"
                "1. Mатричное сложение\n"
                "2. Матричное умножение\n"
                "3. Умножение на скаляр\n"
                "4. Прибавление к строке линейной комбинации других строк\n"
                "5. Никакую\n");
            error_int(&type_of_operation, 1, 5, "Ошибка: выберите от 1 до 5\n");
            switch (type_of_operation) {
                case 1:
                    printf("Задайте матрицу с которой будете складывать\n"
                        "Важно: она того же размера, что и исходная, а именно %dx%d\n", size, size);
                    matrix2 = create_matrix(size, size, selected_operation);
                    matrix_result = malloc(sizeof(Matrix));
                    if (matrix_result == NULL) {
                        printf("Ошибка: недостаточно памяти\n");
                        break;
                    };
                    matrix_result->column = size;
                    matrix_result->row = size;
                    matrix_result->operation = selected_operation;
                    matrix_result->data = malloc(size * size * selected_operation->size);
                    if (matrix_result->data == NULL) {
                        printf("Ошибка: недостаточно памяти\n");
                        break;
                    }
                    matrix_sum(matrix1, matrix2, matrix_result);
                    printf("Матрица 1\n");
                    matrix_print(matrix1);
                    printf("Матрица 2\n");
                    matrix_print(matrix2);
                    printf("Результат\n");
                    matrix_print(matrix_result);
                    matrix_buffer = matrix1;
                    matrix1 = matrix_result;
                    matrix_del(matrix_buffer);
                    matrix_del(matrix2);
                    printf("Теперь это ваша матрица. Итак..\n");
                    break;
                case 2:
                    printf("Задайте матрицу на которую будете умножать\n"
                        "Важно: она того же размера, что и исходная, а именно %dx%d\n", size, size);
                    matrix2 = create_matrix(size, size, selected_operation);
                    matrix_result = malloc(sizeof(Matrix));
                    if (matrix_result == NULL) {
                        printf("Ошибка: недостаточно памяти\n");
                        break;
                    };
                    matrix_result->column = size;
                    matrix_result->row = size;
                    matrix_result->operation = selected_operation;
                    matrix_result->data = malloc(size * size * selected_operation->size);
                    if (matrix_result->data == NULL) {
                        printf("Ошибка: недостаточно памяти\n");
                        break;
                    }
                    matrix_multiplication(matrix1, matrix2, matrix_result);
                    printf("Матрица 1\n");
                    matrix_print(matrix1);
                    printf("Матрица 2\n");
                    matrix_print(matrix2);
                    printf("Результат\n");
                    matrix_print(matrix_result);
                    matrix_buffer = matrix1;
                    matrix1 = matrix_result;
                    matrix_del(matrix_buffer);
                    matrix_del(matrix2);
                    printf("Теперь это ваша матрица. Итак..\n");
                    break;
                case 3:
                    printf("Задайте число, на которое умножите матрицу\n");
                    if (type_of_numbers == 1) {
                        error_int(&scalar_int, 1, 0, "Ошибка: введите целое число\n");
                        multiplication_by_a_scalar(matrix1, scalar_int, matrix_result);
                    } else {
                        error_float(&scalar_float, 1, 0, "Ошибка: введите вещественное число\n");
                        multiplication_by_a_scalar(matrix1, scalar_float, matrix_result);
                    }
                    matrix_buffer = matrix1;
                    matrix1 = matrix_result;
                    matrix_del(matrix_buffer);
                    printf("Результат\n");
                    matrix_print(matrix_result);
                    printf("Теперь это ваша матрица. Итак..\n");
                    break;
                case 4:
                    printf("Какую строку хотите прибавить?\n");
                    error_int(&row_from, 1, size, "Ошибка: выберете номер строки\n");
                    printf("К какой строке её хотите прибавить?\n"
                        "Важно: это должна быть не та же строка\n");
                    while (1) {
                        if (scanf("%d", &row_to) == 1 && row_to >= 1 && row_to <= size && row_to != row_from && (c = getchar()) != '\n' && c != EOF) {
                            break;
                        }
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("%s", "Ошибка: неккоректное значение");      
                    }
                    error_int(&row_to, 1, size, "Ошибка: выберете номер строки\n");
                    adding_a_linear_combination(matrix1, row_from, row_to, matrix_result);
                    matrix_buffer = matrix1;
                    matrix1 = matrix_result;
                    matrix_del(matrix_buffer);
                    printf("Результат\n");
                    matrix_print(matrix_result);
                    printf("Теперь это ваша матрица. Итак..\n");
                    break;
                default:
                    break;
            }
            if (type_of_operation == 5) {
                break;
            }
            printf("\nВаша матрица:\n");
            matrix_print(matrix1);
        }
        matrix_del(matrix1);
        printf("Повторить работу программы? 1 — Да, 0 — Нет\n");
        error_int(&flag, 0, 1, "Ошибка: Два варианта: 1 — Да, 0 — Нет\n");
        if (flag == 0) {
            return 0;
        }
    }
}