#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.c"
#include "vectorVoid.h"

void task_1(const char *filename, size_t n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() % 10);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void transpose_matrix_in_file_task_1(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    long long int n;
    fscanf(file, "%lld", &n);

    matrix matrix = getMemMatrix((int) n , (int) n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);

    fclose(file);

    transposeSquareMatrix(&matrix);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", matrix.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    freeMemMatrix(&matrix);
}
void test_task_1() {
    const char filename[] = "19_1";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {9, 8, 7,
                                              0, 5, 4,
                                              -7, 29, -1}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    transpose_matrix_in_file_task_1(filename);

    freeMemMatrix(&m);
}
void task_2(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    vectorVoid v = createVectorV(0, sizeof(float));

    while (!feof(file)) {
        float x;
        fscanf(file, "%f", &x);

        pushBackVectorV(&v, &x);
    }

    fclose(file);

    file = fopen(filename, "w");

    for (size_t i = 0; i < v.size; i++) {
        float x;
        getVectorValueV(&v, i, &x);
        fprintf(file, "%.2lf ", x);
    }

    deleteVectorV(&v);
    fclose(file);
}

void test_task_2_zero_numb() {
    const char filename[] = "19_2_test_zero_numb";

    FILE* file = fopen(filename, "w");
    fclose(file);

    task_2(filename);

    file = fopen(filename, "r");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp(data, "0.00") == 0);
}

void test_task_2_three_numb() {
    const char filename[] = "19_2_test_three_numb";

    float num_1 = 3.143423;
    float num_2 = 2.241518;
    float num_3 = 9.353738;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%f %f %f", num_1, num_2, num_3);

    fclose(file);

    task_2(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[100] = "3.14 2.24 9.35 ";

    assert(strcmp(data, res) == 0);
}
void test_task_2() {
    test_task_2_zero_numb();
    test_task_2_three_numb();
}

int task_3(const char *filename) {
    FILE *file = fopen(filename, "r+");
    char action;
    int num_1, num_2, answer;
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }
    fscanf(file, "%d %c %d", &num_1, &action, &num_2);
    switch (action) {
        case '+':
            answer = num_1 + num_2;
            break;
        case '-':
            answer = num_1 - num_2;
            break;
        case '*':
            answer = num_1 * num_2;
            break;
        case '/':
            if (num_2 == 0) {
                fprintf(stderr, "Сannot be divided zero");
                exit(1);
            }
            answer = num_1 / num_2;
            break;
        default:
            printf("Operation error\n");
            fclose(file);
            return 1;
    }
    fprintf(file, "\nAnswer: %d\n", answer);
    fclose(file);
    return 0;
}

void test_task_3_test_1() {
    const char filename[] = "19_3_test_1";

    char expression[] = "3 * 4";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_3("19_3_test_1");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "3 * 4 = 12";

    assert(strcmp(data, res));
}

void test_task_3_test_2() {
    const char filename[] = "19_3_test_2";

    char expression[] = "4 / 0";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_3("19_3_test_2");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "4 / 0 = Сannot be divided zero";

    assert(strcmp(data, res));
}
void test_task_3_test_3() {
    const char filename[] = "19_3_test_3";

    char expression[] = "10 - 5";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_3("19_3_test_3");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "10 - 5 = 5";

    assert(strcmp(data, res));
}
void test_task_3_test_4() {
    const char filename[] = "19_3_test_4";

    char expression[] = "77 + 33";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_3("19_3_test_4");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "77 + 33 = 110";

    assert(strcmp(data, res));
}

void test_task_3_all_action() {
    test_task_3_test_1();
    test_task_3_test_2();
    test_task_3_test_3();
    test_task_3_test_4();
}

int main() {
    test_task_1();
    test_task_2();
    //test_task_3_all_action();
    return 0;
}

