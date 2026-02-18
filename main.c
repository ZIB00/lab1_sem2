#include <stdio.h>
#include <locale.h>
#include "logic.h"

int main() {
    int size = 0; //Размер квадратной матрицы
    int type_of_numbers = 0; //Тип чисел в матрице
    int type_of_operation = 0; //Тип операции над матрицей
    int flag = 0; //Нужен для выяснения необходимости повторить программу

    setlocale(LC_ALL, "Russian");

    while (1) {
        printf("Квадратную матрицу какого размера вы ходите задать?\n");
        scanf("%d", size);
        printf("Выберите тип чисел, написав соответствующую цифру\n");
        printf("1. Целые\n");
        printf("2. Вещественные\n");
        scanf("%d", type_of_numbers);
        create_matrix(size, type_of_numbers);

        while (type_of_operation != 5) {
            printf("Какую операцию сделать c матрицей? впишите соответствующую цифру\n"
                "1. Mатричное сложение\n"
                "2. Матричное умножение\n"
                "3. Умножение на скаляр\n"
                "4. Прибавление к строке линейной комбинации других строк\n"
                "5. Никакую\n");
            scanf("%d", type_of_operation);
            switch (type_of_operation) {
                case 1:
                    matrix_addition();
                    break;
                case 2:
                    matrix_multiplication();
                    break;
                case 3:
                    multiplication_by_a_scalar();
                    break;
                case 4:
                    adding_a_linear_combination();
                    break;
                default:
                    break;
            }
            if (type_of_operation == 5) {
                break;
            }
        }
        printf("Повторить работу программы? 1 — Да, 0 — Нет\n");
        scanf("%d", flag);
        if (flag == 0) {
            break;
        }
    }
}
