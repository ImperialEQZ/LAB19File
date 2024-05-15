#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "matrix.c"
#include "vectorVoid.h"
void copyFileContent(const char* sourceFile, const char* destinationFile) {
    FILE *source, *destination;
    char ch;
    source = fopen(sourceFile, "r");
    if (source == NULL) {
        printf("error opening the source file\n");
        return;
    }
    destination = fopen(destinationFile, "w");
    if (destination == NULL) {
        printf("file could not be opened for writing\n");
        fclose(source);
        return;
    }
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, destination);
    fclose(source);
    fclose(destination);
}
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

int task_4(const char *filename, char sequence[20]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }
    FILE *result_file = fopen("result_file", "w");
    if (result_file == NULL) {
        printf("File opening error\n");
        fclose(file);
        return 1;
    }
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        if (strstr(word, sequence) != NULL)
            fprintf(result_file, "%s", word);
    }
    fclose(file);
    fclose(result_file);
    return 0;
}

void test_task_4_1() {
    const char filename[] = "19_4_test_1";

    char expression[] = "Hello World";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_4("19_4_test_1", "Hello");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "Hello";

    assert(strcmp(data, res));
}

void test_task_4_void() {
    const char filename[] = "19_4_test_2";

    char expression[] = "";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_4("19_4_test_2", "");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "";

    assert(strcmp(data, res));
}

void test_task_4_3() {
    const char filename[] = "19_4_test_3";

    char expression[] = "!?234";
    FILE* file = fopen(filename, "w");

    fputs(expression, file);

    fclose(file);

    task_4("19_4_test_3", "!?");

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char res[] = "234";

    assert(strcmp(data, res));
}

void test_task_4() {
    test_task_4_1();
    test_task_4_void();
    test_task_4_3();
}

int task_5(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }
    FILE *result_file = fopen("result_file", "w");
    if (result_file == NULL) {
        printf("File opening error\n");
        fclose(file);
        return 1;
    }
    char line[1024], longest_word[1000];
    int maxLen = 0;
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, " ");
        while (key != NULL) {
            if (strlen(key) > maxLen) {
                maxLen = strlen(key);
                strcpy(longest_word, key);
            }
            key = strtok(NULL, " ");
        }
        fprintf(result_file, "%s", longest_word);
        maxLen = 0;
        longest_word[0] = '\0';
    }
    fclose(file);
    fclose(result_file);
    copyFileContent("result_file", filename);
    return 0;
}

void test_task_5_void_file() {
    const char filename[] = "19_5_test_void";

    FILE* file = fopen(filename, "w");
    fclose(file);

    task_5(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fprintf(file, "%s", data);

    fclose(file);

    assert(strcmp(data, "") == 0);
}

void test_task_5_2() {
    const char filename[] = "19_5_test_2";

    char line_1[] = "qwe";
    char line_2[] = "rty";

    FILE* file = fopen(filename, "w");

    fprintf(file, "%s\n", line_1);
    fprintf(file, "%s\n", line_2);

    fclose(file);

    task_5(filename);

    file = fopen(filename, "r");

    char res_line_1[3] = "";
    fscanf(file, "%s\n", res_line_1);

    char res_line_2[3] = "";
    fscanf(file, "%s\n", res_line_2);

    fclose(file);

    assert(strcmp(line_1, res_line_1) == 0);
    assert(strcmp(line_2, res_line_2) == 0);
}

void test_task_5_all() {
    test_task_5_void_file();
    test_task_5_2();
}

typedef struct {
    int power;
    int coefficient;
} Polynomial;

void task_6() {
    FILE *input_file = fopen("19_6", "rb");
    FILE *output_file = fopen("19_6_res", "wb");

    double x = 2.000;

    while (!feof(input_file)) {
        int term_count;
        if (fread(&term_count, sizeof(int), 1, input_file) != 1)
            break;

        Polynomial *polys = (Polynomial *)malloc(term_count * sizeof(Polynomial));
        fread(polys, sizeof(Polynomial), term_count, input_file);

        double sum = 0.0;
        for (int i = 0; i < term_count; i++) {
            sum += polys[i].coefficient * pow(x, polys[i].power);
        }

        if (sum != 0) {
            fwrite(&term_count, sizeof(int), 1, output_file);
            fwrite(polys, sizeof(Polynomial), term_count, output_file);
        }

        free(polys);
    }

    fclose(input_file);
    fclose(output_file);
}

void generate_task_6() {
    FILE *input_file = fopen("19_6", "wb");
    FILE *excepted_file = fopen("19_6_excepted", "wb");

    int power = 3;
    Polynomial _1[] = {{2, 3}, {1, -12}, {0, 12}};
    fwrite(&power, sizeof(int), 1, input_file);
    fwrite(_1, sizeof(Polynomial), power, input_file);

    power = 4;
    Polynomial _2[] = {{3, 8}, {2, -6}, {1, 12}, {0, -88}};
    fwrite(&power, sizeof(int), 1, input_file);
    fwrite(_2, sizeof(Polynomial), power, input_file);

    fwrite(&power, sizeof(int), 1, excepted_file);
    fwrite(_2, sizeof(Polynomial), power, excepted_file);

    power = 2;
    Polynomial _3[] = {{1, 15}, {0, -7}};
    fwrite(&power, sizeof(int), 1, input_file);
    fwrite(_3, sizeof(Polynomial), power, input_file);

    power = 5;
    Polynomial _4[] = {{4, 15}, {3, -7}, {2, 44}, {1, 28}, {0, 0}};
    fwrite(&power, sizeof(int), 1, input_file);
    fwrite(_4, sizeof(Polynomial), power, input_file);


    fclose(input_file);
    fclose(input_file);
}

void test_task_6() {
    generate_task_6();
    task_6();

    FILE *output_file = fopen("19_6_test_output", "rb");
    FILE *excepted_file = fopen("19_6_test_excepted", "rb");

    int num_1, num_2;
    int flag = 0;
    while (fread(&num_1, sizeof(int), 1, output_file) == 1 && fread(&num_2, sizeof(int), 1, excepted_file) == 1) {
        if (num_1 != num_2) {
            flag = 1;
            break;
        }
    }
    fclose(output_file);
    fclose(excepted_file);
    if (flag == 1) {
        printf("Error\n");
    }
}
int main() {
    //test_task_1();
    //test_task_2();
    //test_task_3_all_action();
    //test_task_4();
    //test_task_5_all();
    test_task_6();

    return 0;
}

