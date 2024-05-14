#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.c"
#include "vectorVoid.h"

FILE* check_file_open_without_error(const char* filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("error reading\n");
        exit(1);
    }

    return file;
}

void generate_random_matrix_file(const char *filename, size_t n) {
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

void transpose_matrix_in_file(const char* filename) {
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

int main() {
    generate_random_matrix_file("ex", 5);
    FILE *file = check_file_open_without_error("ex");


    long long n;
    fscanf(file, "%lld", &n);

    matrix matrix = getMemMatrix((int) n, (int) n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);

    outputMatrix(matrix);

    fclose(file);
    test_task_2();
    return 0;
}

