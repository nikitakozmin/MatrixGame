#include "gaming_functions.h"
#include <Arduino.h>

// Функция для генерации случайного бинарного числа на основе вероятности p
int random_binary(float p) {
    if (p > 1.0) {
      p = 1.0;
    }
    else if (p < 0.0) {
      p = 0.0;
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
    probabilities.q = (matrix[1][0] - matrix[1][1]) / (-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]);
    probabilities.p = (matrix[0][1] - matrix[1][1]) / (-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]);
    probabilities.q = round_to(probabilities.q, 2);
    probabilities.p = round_to(probabilities.p, 2);
    return probabilities;
}

int probability_selection_efficiency(float fst_expected_value, float snd_expected_value, float fst_real_value, float snd_real_value) {
    return int((1 - abs(fst_expected_value - fst_real_value) + 1 - abs(snd_expected_value - snd_real_value)) / 2 * 100.0);
}


void create_matrix_for_game(int matrix[2][2], int rows = 2, int cols = 2, int min_num = -99, int max_num = 99) {
  randomSeed(analogRead(A0));  // Инициализация генератора случайных чисел с использованием аналогового входа

  // Перемешивание чисел и заполнение каждой строки уникальными значениями
  for (int i = 0; i < rows; i++) {
    // Создаем массив всех возможных чисел в пределах диапазона для текущей строки
    int num_elements = max_num - min_num + 1;
    int all_numbers[200];  // Делаем массив фиксированного размера (достаточно для диапазона от -99 до 99)

    // Заполняем массив всеми числами от min_num до max_num
    for (int n = 0; n < num_elements; n++) {
      all_numbers[n] = min_num + n;
    }

    // Перемешиваем этот массив
    for (int j = num_elements - 1; j > 0; j--) {
      int k = random(j + 1);  // Генерация случайного индекса
      int temp = all_numbers[j];
      all_numbers[j] = all_numbers[k];
      all_numbers[k] = temp;
    }

    // Заполняем текущую строку матрицы уникальными числами
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = all_numbers[j]; // Используем первые 'cols' чисел после перемешивания
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
