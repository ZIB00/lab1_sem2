#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logic.h"

int count_of_total_tests = 0;
int count_of_passed_tests = 0;

// --- ÂÑÏÎÌÎÃÀÒÅËÜÍÛÅ ÈÍÑÒÐÓÌÅÍÒÛ ---

void manual_set_matrix_data(Matrix* A, void* values) {
    size_t elem_size = A->operation->size;
    for (int i = 0; i < A->row * A->column; i++) {
        void* elem_from = (char*)A->data + i * elem_size;
        void* elem_to = (char*)values + i * elem_size;
        for (size_t b = 0; b < elem_size; b++) {
            *((char*)elem_from + b) = *((char*)elem_to + b);
        }
    }
}

int manual_compare_matrices(Matrix* m1, Matrix* m2) {
    if (m1->row != m2->row || m1->column != m2->column) return 0;
    for (int i = 0; i < m1->row * m1->column; i++) {
        if (m1->operation == &operation_int) {
            if (*((int*)m1->data + i) != *((int*)m2->data + i)) return 0;
        } else {
            if (fabsf(*((float*)m1->data + i) - *((float*)m2->data + i)) > 1e-5f) return 0;
        }
    }
    return 1;
}

void register_test(int result, const char* name) {
    count_of_total_tests++;
    if (result) {
        count_of_passed_tests++;
        printf("\033[32m[PASSED] %d. %s\033[0m\n", count_of_total_tests, name);
    } else {
        printf("\033[31m[FAIL]   %d. %s\033[0m\n", count_of_total_tests, name);
    }
}

// --- 1-5: ÑËÎÆÅÍÈÅ INT ---

void test_matrix_sum_int_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *B = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, b[] = {10, 10, 101, 10}, exp[] = {11, 12, 13, 14};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);
    manual_set_matrix_data(Expected, exp);

    matrix_sum(A, B, Result);
    register_test(manual_compare_matrices(Result, Expected), "Addition Work (Int)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result);
    matrix_del(Expected);
}

void test_matrix_addition_int_commutativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *B = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result1 = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result2 = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, b[] = {5, 6, 7, 8};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);

    matrix_sum(A, B, Result1);
    matrix_sum(B, A, Result2);
    register_test(manual_compare_matrices(Result1, Result2), "Addition Commutativity (Int)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result1);
    matrix_del(Result2);
}

void test_matrix_addition_int_associativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *B = create_empty_matrix(2, 2, &operation_int);
    Matrix *C = create_empty_matrix(2, 2, &operation_int);
    Matrix *T = create_empty_matrix(2, 2, &operation_int);
    Matrix *L = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);

    int d[] = {1, 1, 1, 1};
    manual_set_matrix_data(A, d);
    manual_set_matrix_data(B, d);
    manual_set_matrix_data(C, d);

    matrix_sum(A, B, T);
    matrix_sum(T, C, L);
    matrix_sum(B, C, T);
    matrix_sum(A, T, Result);
    register_test(manual_compare_matrices(L, Result), "Addition Associativity (Int)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(C);
    matrix_del(T);
    matrix_del(L);
    matrix_del(Result);
}

void test_matrix_addition_int_neutral_elem() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *Z = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);

    int a[] = {7, 8, 9, 10}, z[] = {0, 0, 0, 0};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(Z, z);

    matrix_sum(A, Z, Result);
    register_test(manual_compare_matrices(A, Result), "Addition Neutral Element (Int)");

    matrix_del(A);
    matrix_del(Z);
    matrix_del(Result);
}

void test_matrix_addition_int_inverse_elem() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *NegA = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);
    Matrix *Z = create_empty_matrix(2, 2, &operation_int);

    int a[] = {5, -2, 3, 0}, nd[] = {-5, 2, -3, 0}, z[] = {0, 0, 0, 0};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(NegA, nd);
    manual_set_matrix_data(Z, z);

    matrix_sum(A, NegA, Result);
    register_test(manual_compare_matrices(Result, Z), "Addition Inverse Element (Int)");

    matrix_del(A);
    matrix_del(NegA);
    matrix_del(Result);
    matrix_del(Z);
}

// --- 6-10: ÑËÎÆÅÍÈÅ FLOAT ---

void test_matrix_sum_float_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *B = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.5f, 1.5f, 1.5f, 1.5f}, b[] = {0.5f, 0.5f, 0.5f, 0.5f}, exp[] = {2.0f, 2.0f, 2.0f, 2.0f};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);
    manual_set_matrix_data(Expected, exp);

    matrix_sum(A, B, Result);
    register_test(manual_compare_matrices(Result, Expected), "Addition Work (Float)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result);
    matrix_del(Expected);
}

void test_matrix_addition_float_commutativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *B = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result1 = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result2 = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.5f, 2.5f, 3.5f, 4.5f}, b[] = {0.5f, 0.5f, 0.5f, 0.5f};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);

    matrix_sum(A, B, Result1);
    matrix_sum(B, A, Result2);
    register_test(manual_compare_matrices(Result1, Result2), "Addition Commutativity (Float)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result1);
    matrix_del(Result2);
}

void test_matrix_addition_float_associativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *B = create_empty_matrix(2, 2, &operation_float);
    Matrix *C = create_empty_matrix(2, 2, &operation_float);
    Matrix *T = create_empty_matrix(2, 2, &operation_float);
    Matrix *L = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);

    float d[] = {0.1f, 0.1f, 0.1f, 0.1f};
    manual_set_matrix_data(A, d);
    manual_set_matrix_data(B, d);
    manual_set_matrix_data(C, d);

    matrix_sum(A, B, T);
    matrix_sum(T, C, L);
    matrix_sum(B, C, T);
    matrix_sum(A, T, Result);
    register_test(manual_compare_matrices(L, Result), "Addition Associativity (Float)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(C);
    matrix_del(T);
    matrix_del(L);
    matrix_del(Result);
}

void test_matrix_addition_float_neutral_elem() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *Z = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.1f, 2.2f, 3.3f, 4.4f}, z[] = {0, 0, 0, 0};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(Z, z);

    matrix_sum(A, Z, Result);
    register_test(manual_compare_matrices(A, Result), "Addition Neutral Element (Float)");

    matrix_del(A);
    matrix_del(Z);
    matrix_del(Result);
}

void test_matrix_addition_float_inverse_elem() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *NegA = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);
    Matrix *Z = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.0f, -1.0f, 0.5f, 2.0f}, nd[] = {-1.0f, 1.0f, -0.5f, -2.0f}, z[] = {0, 0, 0, 0};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(NegA, nd);
    manual_set_matrix_data(Z, z);

    matrix_sum(A, NegA, Result);
    register_test(manual_compare_matrices(Result, Z), "Addition Inverse Element (Float)");

    matrix_del(A);
    matrix_del(NegA);
    matrix_del(Result);
    matrix_del(Z);
}

// --- 11-14: ÓÌÍÎÆÅÍÈÅ INT ---

void test_matrix_multiplication_int_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *B = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, b[] = {5, 6, 7, 8}, exp[] = {19, 22, 43, 50};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);
    manual_set_matrix_data(Expected, exp);

    matrix_multiplication(A, B, Result);
    register_test(manual_compare_matrices(Result, Expected), "Multiplication Work (Int)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result);
    matrix_del(Expected);
}

void test_matrix_multiplication_int_non_commutativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *B = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result1 = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result2 = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, b[] = {2, 0, 1, 2};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);

    matrix_multiplication(A, B, Result1);
    matrix_multiplication(B, A, Result2);
    register_test(!manual_compare_matrices(Result1, Result2), "Multiplication Non-commutativity (Int)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result1);
    matrix_del(Result2);
}

void test_matrix_multiplication_int_associativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *B = create_empty_matrix(2, 2, &operation_int);
    Matrix *C = create_empty_matrix(2, 2, &operation_int);
    Matrix *T = create_empty_matrix(2, 2, &operation_int);
    Matrix *L = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);

    int d[] = {2, 0, 0, 2};
    manual_set_matrix_data(A, d);
    manual_set_matrix_data(B, d);
    manual_set_matrix_data(C, d);

    matrix_multiplication(A, B, T);
    matrix_multiplication(T, C, L);
    matrix_multiplication(B, C, T);
    matrix_multiplication(A, T, Result);
    register_test(manual_compare_matrices(L, Result), "Multiplication Associativity (Int)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(C);
    matrix_del(T);
    matrix_del(L);
    matrix_del(Result);
}

void test_matrix_multiplication_int_identity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *E = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);

    int a[] = {10, 20, 30, 40}, e[] = {1, 0, 0, 1};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(E, e);

    matrix_multiplication(E, A, Result);
    register_test(manual_compare_matrices(A, Result), "Multiplication Identity E*A=A (Int)");

    matrix_del(A);
    matrix_del(E);
    matrix_del(Result);
}

// --- 15-18: ÓÌÍÎÆÅÍÈÅ FLOAT ---

void test_matrix_multiplication_float_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *B = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_float);

    float a[] = {0.5f, 2.0f, 0.0f, 1.0f}, b[] = {4.0f, 0.0f, 1.0f, 2.0f}, exp[] = {4.0f, 4.0f, 1.0f, 2.0f}; // (0.5*4 + 2*1) = 4   (0.5*0 + 2*2) = 4     (0*4 + 1*1) = 1    (0*0 + 1*2) = 2
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);
    manual_set_matrix_data(Expected, exp);

    matrix_multiplication(A, B, Result);
    register_test(manual_compare_matrices(Result, Expected), "Multiplication Work (Float)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result);
    matrix_del(Expected);
}

void test_matrix_multiplication_float_non_commutativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *B = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result1 = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result2 = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.0f, 2.0f, 3.0f, 4.0f}, b[] = {0.0f, 1.0f, 1.0f, 0.0f};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(B, b);

    matrix_multiplication(A, B, Result1);
    matrix_multiplication(B, A, Result2);
    register_test(!manual_compare_matrices(Result1, Result2), "Multiplication Non-commutativity (Float)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(Result1);
    matrix_del(Result2);
}

void test_matrix_multiplication_float_associativity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *B = create_empty_matrix(2, 2, &operation_float);
    Matrix *C = create_empty_matrix(2, 2, &operation_float);
    Matrix *T = create_empty_matrix(2, 2, &operation_float);
    Matrix *L = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);

    float d[] = {1.5f, 0.0f, 0.0f, 1.5f};
    manual_set_matrix_data(A, d);
    manual_set_matrix_data(B, d);
    manual_set_matrix_data(C, d);

    matrix_multiplication(A, B, T);
    matrix_multiplication(T, C, L);
    matrix_multiplication(B, C, T);
    matrix_multiplication(A, T, Result);
    register_test(manual_compare_matrices(L, Result), "Multiplication Associativity (Float)");

    matrix_del(A);
    matrix_del(B);
    matrix_del(C);
    matrix_del(T);
    matrix_del(L);
    matrix_del(Result);
}

void test_matrix_multiplication_float_identity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *E = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);

    float da[] = {0.5f, 1.5f, 2.5f, 3.5f}, de[] = {1.0f, 0.0f, 0.0f, 1.0f};
    manual_set_matrix_data(A, da);
    manual_set_matrix_data(E, de);

    matrix_multiplication(E, A, Result);
    register_test(manual_compare_matrices(A, Result), "Multiplication Identity E*A=A (Float)");

    matrix_del(A);
    matrix_del(E);
    matrix_del(Result);
}

// --- 19-21: ÑÊÀËßÐ INT ---

void test_matrix_scalar_int_identity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);

    int a[] = {10, 20, 30, 40}, s = 1;
    manual_set_matrix_data(A, a);

    multiplication_by_a_scalar(A, &s, Result);
    register_test(manual_compare_matrices(A, Result), "Scalar Identity 1*A=A (Int)");

    matrix_del(A);
    matrix_del(Result);
}

void test_matrix_scalar_int_zero() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);
    Matrix *Z = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, s = 0, z[] = {0, 0, 0, 0};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(Z, z);

    multiplication_by_a_scalar(A, &s, Result);
    register_test(manual_compare_matrices(Result, Z), "Scalar Zero 0*A=0 (Int)");

    matrix_del(A);
    matrix_del(Result);
    matrix_del(Z);
}

void test_matrix_scalar_int_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *Result = create_empty_matrix(2, 2, &operation_int);
    Matrix *E = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, s = 3, e[] = {3, 6, 9, 12};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(E, e);

    multiplication_by_a_scalar(A, &s, Result);
    register_test(manual_compare_matrices(Result, E), "Scalar Work 3*A (Int)");

    matrix_del(A);
    matrix_del(Result);
    matrix_del(E);
}

// --- 22-24: ÑÊÀËßÐ FLOAT ---

void test_matrix_scalar_float_identity() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.1f, 2.2f, 3.3f, 4.4f}, s = 1.0f;
    manual_set_matrix_data(A, a);

    multiplication_by_a_scalar(A, &s, Result);
    register_test(manual_compare_matrices(A, Result), "Scalar Identity 1*A=A (Float)");

    matrix_del(A);
    matrix_del(Result);
}

void test_matrix_scalar_float_zero() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);
    Matrix *Z = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.0f, 2.0f, 3.0f, 4.0f}, s = 0.0f, z[] = {0, 0, 0, 0};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(Z, z);

    multiplication_by_a_scalar(A, &s, Result);
    register_test(manual_compare_matrices(Result, Z), "Scalar Zero 0*A=0 (Float)");

    matrix_del(A);
    matrix_del(Result);
    matrix_del(Z);
}

void test_matrix_scalar_float_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *Result = create_empty_matrix(2, 2, &operation_float);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_float);

    float a[] = {10.0f, 20.0f, 30.0f, 40.0f}, s = 0.5f, exp[] = {5.0f, 10.0f, 15.0f, 20.0f};
    manual_set_matrix_data(A, a);
    manual_set_matrix_data(Expected, exp);

    multiplication_by_a_scalar(A, &s, Result);
    register_test(manual_compare_matrices(Result, Expected), "Scalar Work 0.5*A (Float)");

    matrix_del(A);
    matrix_del(Result);
    matrix_del(Expected);
}

// --- 25-29: ËÈÍÅÉÍÛÅ ÊÎÌÁÈÍÀÖÈÈ INT ---

void test_matrix_linear_int_work() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    int d[] = {10, 20, 30, 40}, scalar = -3;
    // Result2 = Result2 + (-3)*Result1 -> {30 - 30, 40 - 60} = {0, -20}
    manual_set_matrix_data(A, d);
    adding_a_linear_combination(A, 1, 2, &scalar);
    
    int res = (*((int*)A->data + 2) == 0 && *((int*)A->data + 3) == -20);
    register_test(res, "Linear Combination Work (Int)");

    matrix_del(A);
}

void test_matrix_linear_int_equivalence() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 3, 4}, s = 2;
    manual_set_matrix_data(A, a);

    adding_a_linear_combination(A, 1, 2, &s); // Result2 = Result2 + 2*Result1 -> {3+2, 4+4} = {5, 8}
    int res = (*((int*)A->data + 2) == 5 && *((int*)A->data + 3) == 8);
    register_test(res, "Linear Equivalence (Int)");

    matrix_del(A);
}

void test_matrix_linear_int_reversibility() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_int);

    int d[] = {1, 2, 3, 4}, s = 10, si = -10;
    manual_set_matrix_data(A, d);
    manual_set_matrix_data(Expected, d);

    adding_a_linear_combination(A, 1, 2, &s);
    adding_a_linear_combination(A, 1, 2, &si);

    register_test(manual_compare_matrices(A, Expected), "Linear Reversibility (Int)");

    matrix_del(A);
    matrix_del(Expected);
}

void test_matrix_linear_int_dependency() {
    Matrix *A = create_empty_matrix(2, 2, &operation_int);

    int a[] = {1, 2, 2, 4}, s = -2;
    manual_set_matrix_data(A, a);

    adding_a_linear_combination(A, 1, 2, &s);
    register_test(*((int*)A->data + 2) == 0 && *((int*)A->data + 3) == 0, "Linear Dependency (Int)");

    matrix_del(A);
}

void test_matrix_linear_int_determinant() {
    int det;
    Matrix *A = create_empty_matrix(2, 2, &operation_int);

    int a[] = {2, 1, 4, 3}, s = 5; // Det = 2
    manual_set_matrix_data(A, a);

    adding_a_linear_combination(A, 1, 2, &s);
    det = (*((int*)A->data + 0))*(*((int*)A->data + 3)) - (*((int*)A->data + 1))*(*((int*)A->data + 2));
    register_test(det == 2, "Linear Determinant Invariance (Int)");

    matrix_del(A);
}

// --- 30-34: ËÈÍÅÉÍÛÅ ÊÎÌÁÈÍÀÖÈÈ FLOAT ---

void test_matrix_linear_float_work() {
    int res;
    Matrix *A = create_empty_matrix(2, 2, &operation_float);

    float d[] = {2.0f, 4.0f, 1.0f, 1.0f}, scalar = 0.5f;
    // Result2 = Result2 + 0.5*Result1 -> {1 + 1, 1 + 2} = {2.0, 3.0}
    manual_set_matrix_data(A, d);
    adding_a_linear_combination(A, 1, 2, &scalar);
    
    res = (fabsf(*((float*)A->data + 2) - 2.0f) < 1e-5f && fabsf(*((float*)A->data + 3) - 3.0f) < 1e-5f);
    register_test(res, "Linear Combination Work (Float)");

    matrix_del(A);
}

void test_matrix_linear_float_equivalence() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.0f, 0.0f, 0.5f, 1.0f}, s = 2.0f;
    manual_set_matrix_data(A, a);

    adding_a_linear_combination(A, 1, 2, &s);
    register_test(fabsf(*((float*)A->data + 2) - 2.5f) < 1e-5f, "Linear Equivalence (Float)");

    matrix_del(A);
}

void test_matrix_linear_float_reversibility() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);
    Matrix *Expected = create_empty_matrix(2, 2, &operation_float);

    float d[] = {1.1f, 2.2f, 3.3f, 4.4f}, s = 0.5f, si = -0.5f;
    manual_set_matrix_data(A, d);
    manual_set_matrix_data(Expected, d);

    adding_a_linear_combination(A, 1, 2, &s);
    adding_a_linear_combination(A, 1, 2, &si);
    register_test(manual_compare_matrices(A, Expected), "Linear Reversibility (Float)");

    matrix_del(A);
    matrix_del(Expected);
}

void test_matrix_linear_float_dependency() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);

    float a[] = {1.0f, 1.0f, -1.0f, -1.0f}, s = 1.0f;
    manual_set_matrix_data(A, a);

    adding_a_linear_combination(A, 1, 2, &s);
    register_test(fabsf(*((float*)A->data + 2)) < 1e-5f, "Linear Dependency (Float)");

    matrix_del(A);
}

void test_matrix_linear_float_determinant() {
    Matrix *A = create_empty_matrix(2, 2, &operation_float);

    float a[] = {2.0f, 3.0f, 1.0f, 4.0f}, s = 3.14f; // Det = 5
    manual_set_matrix_data(A, a);

    adding_a_linear_combination(A, 1, 2, &s);
    float det = (*((float*)A->data + 0))*(*((float*)A->data + 3)) - (*((float*)A->data + 1))*(*((float*)A->data + 2));
    register_test(fabsf(det - 5.0f) < 1e-5f, "Linear Determinant Invariance (Float)");

    matrix_del(A);
}



int test() {
    printf("=== TEST BEGIN (28 TESTS) ===\n\n");

    // Áëîê Ñëîæåíèÿ (1-10)
    test_matrix_sum_int_work();
    test_matrix_addition_int_commutativity();
    test_matrix_addition_int_associativity();
    test_matrix_addition_int_neutral_elem();
    test_matrix_addition_int_inverse_elem();
    test_matrix_sum_float_work();
    test_matrix_addition_float_commutativity();
    test_matrix_addition_float_associativity();
    test_matrix_addition_float_neutral_elem();
    test_matrix_addition_float_inverse_elem();

    // Áëîê Óìíîæåíèÿ (11-18)
    test_matrix_multiplication_int_work();
    test_matrix_multiplication_int_non_commutativity();
    test_matrix_multiplication_int_associativity();
    test_matrix_multiplication_int_identity();
    test_matrix_multiplication_float_work();
    test_matrix_multiplication_float_non_commutativity();
    test_matrix_multiplication_float_associativity();
    test_matrix_multiplication_float_identity();

    // Áëîê Ñêàëÿðà (19-24)
    test_matrix_scalar_int_identity();
    test_matrix_scalar_int_zero();
    test_matrix_scalar_int_work();
    test_matrix_scalar_float_identity();
    test_matrix_scalar_float_zero();
    test_matrix_scalar_float_work();

    // Áëîê Ëèíåéíûõ Êîìáèíàöèé (25-34)
    test_matrix_linear_int_work();
    test_matrix_linear_int_equivalence();
    test_matrix_linear_int_reversibility();
    test_matrix_linear_int_dependency();
    test_matrix_linear_int_determinant();
    test_matrix_linear_float_work();
    test_matrix_linear_float_equivalence();
    test_matrix_linear_float_reversibility();
    test_matrix_linear_float_dependency();
    test_matrix_linear_float_determinant();

    printf("\n==============================================\n");
    printf("PASSED %d/%d TESTS\n", count_of_passed_tests, count_of_total_tests);
    printf("==============================================\n");

    return 0;
}