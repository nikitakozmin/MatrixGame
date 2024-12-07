#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <locale.h>
#include <math.h>

// Создание матрицы с гарантированной седловой точкой
void create_matrix_with_saddle_point(int rows, int cols, int matrix[rows][cols]) {
    // Инициализируем генератор случайных чисел
    srand(time(NULL));

    // Создаём случайную матрицу
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 2001 - 1000; // Диапазон от -1000 до 1000
        }
    }

    // Находим строку с наибольшим минимальным элементом
    int saddle_row = 0;
    int saddle_min = INT_MIN;
    for (int i = 0; i < rows; i++) {
        int row_min = INT_MAX;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < row_min) {
                row_min = matrix[i][j];
            }
        }
        if (row_min > saddle_min) {
            saddle_min = row_min;
            saddle_row = i;
        }
    }

    // Находим столбец минимального элемента в выбранной строке
    int saddle_col = 0;
    for (int j = 0; j < cols; j++) {
        if (matrix[saddle_row][j] == saddle_min) {
            saddle_col = j;
            break;
        }
    }

    // Корректируем столбец, чтобы остальные элементы были меньше saddle_min
    for (int i = 0; i < rows; i++) {
        if (i != saddle_row) {
            matrix[i][saddle_col] = -1000 + rand() % (saddle_min + 1000);
        }
    }

    // Убедимся, что выбранный элемент остался прежним
    matrix[saddle_row][saddle_col] = saddle_min;
}

// Поиск седловой точки
int find_saddle_point(int rows, int cols, int matrix[rows][cols], int *saddle_row, int *saddle_col, int *saddle_value) {
    for (int i = 0; i < rows; i++) {
        int row_min = INT_MAX;
        int col_idx = 0;

        // Находим минимальный элемент в строке
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < row_min) {
                row_min = matrix[i][j];
                col_idx = j;
            }
        }

        // Проверяем, является ли он максимальным в столбце
        int is_saddle = 1;
        for (int k = 0; k < rows; k++) {
            if (matrix[k][col_idx] > row_min) {
                is_saddle = 0;
                break;
            }
        }

        if (is_saddle) {
            *saddle_row = i + 1; // 1-индексация
            *saddle_col = col_idx + 1;
            *saddle_value = row_min;
            return 1; // Найдена седловая точка
        }
    }
    return 0; // Седловой точки нет
}

// Главная функция
int main() {
//    setlocale(LC_ALL, "");
    int rows = 5, cols = 5;
    int matrix[rows][cols];

    create_matrix_with_saddle_point(rows, cols, matrix);

    printf("Матрица:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }

    int saddle_row, saddle_col, saddle_value;
    if (find_saddle_point(rows, cols, matrix, &saddle_row, &saddle_col, &saddle_value)) {
        printf("\nСедловая точка (строка, столбец, значение): %d, %d, %d\n", saddle_row, saddle_col, saddle_value);
    } else {
        printf("\nСедловых точек нет\n");
    }

    return 0;
}
