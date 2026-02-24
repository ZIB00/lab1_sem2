#include <stdio.h>
#include <locale.h>
#include "logic.h"

int main() {
    int size = 0; //Размер квадратной матрицы
    int num; //Первое число в матрице
    int type_of_operation = 0; //Тип операции над матрицей
    int flag = 0; //Нужен для выяснения необходимости повторить программу
    int c = 0; //Для getchar()

    setlocale(LC_ALL, "Russian");

    while (1) {
        printf("Квадратную матрицу какого размера вы ходите задать? (от 1 до 500)\n"); //500 произвольно взятое число, нужно, чтобы не работать со слишком большими матрицами, а с нулевой матрицой нет смысла работать
        error(&size, 1, 500, "Ошибка: выбери число от 1 до 500\n");
        printf("Выберите тип чисел(целые или вещественные), написав соответствующее число\n");
        //error(&num, 1, 2, "char error_text\n");
        printf("%d\n", num);
        create_matrix(size, num);

        while (type_of_operation != 5) {
            printf("Какую операцию сделать c матрицей? впишите соответствующую цифру\n"
                "1. Mатричное сложение\n"
                "2. Матричное умножение\n"
                "3. Умножение на скаляр\n"
                "4. Прибавление к строке линейной комбинации других строк\n"
                "5. Никакую\n");
            error(&type_of_operation, 1, 5, "Ошибка: выберите от 1 до 5\n");
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
        error(&flag, 0, 1, "Ошибка: Два варианта: 1 — Да, 0 — Нет\n");
        if (flag == 0) {
            break;
        }
    }
}
