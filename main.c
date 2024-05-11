#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.c"

#define ASSERT_FILES(filename1, filename2) assertTXT(filename1, filename2, __FUNCTION__)
#define MAX_FILE_SIZE 1024

void assertTXT(const char *filename1, const char *filename2, char const *funcName)
{
    FILE *f1 = fopen(filename1, "r");
    FILE *f2 = fopen(filename2, "r");
    if (f1 == NULL || f2 == NULL) {
        printf("Error\n");
        return;
    }
    char buffer1[MAX_FILE_SIZE];
    char buffer2[MAX_FILE_SIZE];

    while (fgets(buffer1, MAX_FILE_SIZE, f1) != NULL
           && fgets(buffer2, MAX_FILE_SIZE, f2) != NULL) {
        if (strcmp(buffer1, buffer2) != 0) {
            printf("Error: files is not similar\n");
            fclose(f1);
            fclose(f2);
            return;
        }
    }
    printf("Testing %s - %s passed\n", funcName);
}

int task_1(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("error reading\n");
        exit(1);
    }

    long long n;
    fscanf(file, "%lld", &n);

    matrix matrix = getMemMatrix((int) n, (int) n);

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
    const char *filename_1 = "task_1.txt";
    const char *exp_file_1 = "task_1_test.txt";
    int ans = task_1(filename_1);
    if (ans == 0)
        ASSERT_FILES(filename_1, exp_file_1);
}

int main() {
    test_task_1();
    return 0;
}

