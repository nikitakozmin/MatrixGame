#include <Arduino.h>
#include "gaming_functions.h"

// Функция для генерации случайного бинарного числа на основе вероятности p
int random_binary(float p) {
    if (p > 1.0) {
      p = 1.0;
    }
    else if (p < 0.0) {
      p = 0.0;
    }
    if (p <= 0.5) {
        return (random(100) / 100.0) <= p ? 0 : 1;
    }
    return (random(100) / 100.0) < p ? 0 : 1;
}

// Функция, которая возвращает сумму за раунд
int one_round(float pA, float pB, int matrix[2][2]) {
    int row = random_binary(pA);
    int col = random_binary(pB);

    return matrix[row][col];
}

// Функция для возведения 10 в степень без использования pow
double scale_factor(int decimals) {
    double scale = 1.0;
    for (int i = 0; i < decimals; ++i) {
        scale *= 10.0;
    }
    return scale;
}

// Округление до заданного количества знаков после запятой
double round_to(double value, int decimals) {
    double scale = scale_factor(decimals);
    return round(value * scale) / scale;
}

// Ожидаемое значение для матрицы игры
// matrix - матрица выигрышей, q и p - вероятности выбора строк и столбцов
double mate_expectation_of_game_matrix(int matrix[2][2], double q, double p) {
    return round_to(matrix[0][0] * p * q + 
                 matrix[0][1] * q * (1 - p) + 
                 matrix[1][0] * p * (1 - q) + 
                 matrix[1][1] * (1 - q) * (1 - p), 2);
}

Probabilities ideal_probabilities_for_mixed_strategy(int matrix[2][2]) {
    Probabilities probabilities;
    probabilities.q = (matrix[1][0] - matrix[1][1]) / double(-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]);
    probabilities.p = (matrix[0][1] - matrix[1][1]) / double(-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]);
    probabilities.q = round_to(probabilities.q, 2);
    probabilities.p = round_to(probabilities.p, 2);
    return probabilities;
}

int probability_selection_efficiency(float fst_expected_value, float snd_expected_value, float fst_real_value, float snd_real_value) {
    return int((1 - abs(fst_expected_value - fst_real_value) + 1 - abs(snd_expected_value - snd_real_value)) / 2 * 100.0);
}


void create_matrix_for_game(int matrix[2][2], int rows = 2, int cols = 2, int min_num, int max_num) {
    // Инициализация случайного генератора с использованием аналогового пина для генерации случайных чисел
    randomSeed(analogRead(A0));
    
    // Массивы для отслеживания уникальных значений в строках и столбцах
    bool rowValues[rows][max_num - min_num + 1]; // Массив для строк (максимальное количество уникальных значений)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < max_num - min_num + 1; j++) {
            rowValues[i][j] = false;
        }
    }

    bool colValues[cols][max_num - min_num + 1];  // Массив для столбцов (максимальное количество уникальных значений)
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < max_num - min_num + 1; j++) {
            colValues[i][j] = false;
        }
    }

    // Перебор всех ячеек матрицы
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int newValue;

            // Генерация уникального значения для ячейки
            do {
                newValue = random(min_num, max_num + 1); // Случайное число от min_num до max_num
            } while (rowValues[i][newValue - min_num] || colValues[j][newValue - min_num]);

            // Заполнение матрицы новым значением
            matrix[i][j] = newValue;
    
            // Обновление флагов для строк и столбцов
            rowValues[i][newValue - min_num] = true;
            colValues[j][newValue - min_num] = true;
        }
    }
}

//функция для поиска седловой точки
bool findSaddlePoint(int matrix[2][2], int& saddleRow, int& saddleCol, int& saddleValue) {
  int rows = 2;
  int cols = 2;
  int rowMin = 1000;
  int colIdx = 0;
  int colMax = -1000;
  // Находим минимальный элемент в строке
  for (int i = 0; i < rows; i++){
    for (int j = 1; j < cols; j++){
      if (matrix[i][j] < rowMin){
        rowMin = matrix[i][j];
        colIdx = j;
      }
    }
    // Проверяем, является ли этот элемент максимальным в своем столбце
    for (int j = 1; j < rows; j++) {
      if (matrix[j][colIdx] > colMax) {
        colMax = matrix[j][colIdx];
      }
    }

    // Если минимальный элемент строки равен максимальному в столбце, это седловая точка
    if (rowMin == colMax) {
      saddleRow = i;
      saddleCol = colIdx;
      saddleValue = rowMin;
      return true;
    }
  }

  return false;  // Если седловой точки нет
}
