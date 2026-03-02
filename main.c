#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "logic.h"

#define MAX_SIZE 500 //500 произвольно взятое число, нужно, чтобы не работать со слишком большими матрицами
#define MAX_SCALAR 1000 //тоже произвольно

int main(int args, char * argv[]) {
    if (args == 2 && strcmp(argv[1], "--test") == 0) {
        test();
        return 0;
    } else {
        int size, type_of_numbers, type_of_operation = 0, flag, c;
        int row_from, row_to;
        float scalar_float; int scalar_int;
        TypeInfo* selected_operation;
        Matrix *m1 = NULL, *m2 = NULL, *m_res = NULL;

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
            m1 = create_matrix(size, size, selected_operation);

            printf("\nВаша матрица:\n");
            matrix_print(m1);
            type_of_operation = 0;
            while (type_of_operation != 5) {
                printf("Какую операцию сделать c матрицей? впишите соответствующую цифру\n"
                    "1. Mатричное сложение\n"
                    "2. Матричное умножение\n"
                    "3. Умножение на скаляр\n"
                    "4. Прибавление к строке линейной комбинации других строк\n"
                    "5. Никакую\n");
                error_int(&type_of_operation, 1, 5, "Ошибка: выберите от 1 до 5\n");

                if (type_of_operation == 5) break;
                if (type_of_operation <= 3) m_res = create_empty_matrix(size, size, selected_operation);

                switch (type_of_operation) {
                    case 1:
                        printf("Задайте матрицу с которой будете складывать\n"
                            "Важно: она того же размера, что и исходная, а именно %dx%d\n", size, size);
                        m2 = create_matrix(size, size, selected_operation);
                        matrix_sum(m1, m2, m_res);
                        matrix_del(m2);
                        break;
                    case 2:
                        printf("Задайте матрицу на которую будете умножать\n"
                            "Важно: она того же размера, что и исходная, а именно %dx%d\n", size, size);
                        m2 = create_matrix(size, size, selected_operation);
                        matrix_multiplication(m1, m2, m_res);
                        matrix_del(m2);
                        break;
                    case 3:
                        printf("Задайте число, на которое умножите матрицу (от -1000 до 1000)\n");
                        if (type_of_numbers == 1) {
                            error_int(&scalar_int, -MAX_SCALAR, MAX_SCALAR, "Ошибка: введите целое число\n");
                            multiplication_by_a_scalar(m1, &scalar_int, m_res);
                        } else {
                            error_float(&scalar_float, 0, 0, "Ошибка: введите вещественное число\n");
                            multiplication_by_a_scalar(m1, &scalar_float, m_res);
                        }
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
                            printf("%s", "Ошибка: неккоректное значение\n");      
                        }
                        printf("Множитель (от -1000 до 1000): ");
                        if (type_of_numbers == 1) { 
                            error_int(&scalar_int, -MAX_SCALAR, MAX_SCALAR, "Ошибка: неккоректное значение\n"); 
                            adding_a_linear_combination(m1, row_from, row_to, &scalar_int); 
                        }
                        else { 
                            error_float(&scalar_float, 0, 0, "!\n"); 
                            adding_a_linear_combination(m1, row_from, row_to, &scalar_float); 
                        }
                        m_res = m1; 
                        m1 = NULL;
                        break;
                }

                if (m_res) {
                    matrix_del(m1);
                    m1 = NULL;
                    printf("\nРезультат:\n");
                    matrix_print(m_res);
                }
            }
            matrix_del(m1);
            printf("Повторить работу программы? 1 — Да, 0 — Нет\n");
            error_int(&flag, 0, 1, "Ошибка: Два варианта: 1 — Да, 0 — Нет\n");
            if (flag == 0) {
                return 0;
            }
        }
    }
}