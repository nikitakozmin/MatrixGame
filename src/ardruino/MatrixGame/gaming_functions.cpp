#include <Arduino.h>
#include "gaming_functions.h"

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
//ДОБАВИТЬ В H
bool is_out_of_bounds(int matrix[2][2]){
  Probabilities i_probabilities = ideal_probabilities_for_mixed_strategy(matrix);
  return (0.1 > i_probabilities.q || i_probabilities.q > 0.9 || 0.1 > i_probabilities.p || i_probabilities.p > 0.9);
}

// Создание матрицы без седловой точки
void create_matrix_with_no_saddle_point(int matrix[2][2], int max_num) {
  randomSeed(analogRead(A0)); 
  
  int a11 = random(1, max_num + 1); 
  int a22 = random(1, max_num + 1);
  
  int total_sum = a11 + a22;
  int split, a12, a21;

  if (total_sum > max_num) {
    split = random(total_sum / 2, max_num + 1);
  } else {
    split = random(1, total_sum);
  }

  a12 = -split;
  a21 = -(total_sum - split);

  if (random(0, 2) == 0) {
    matrix[0][0] = a11;
    matrix[0][1] = a12;
    matrix[1][0] = a21;
    matrix[1][1] = a22;
  } else {
    // Transpose the matrix
    matrix[0][0] = a21;
    matrix[0][1] = a11;
    matrix[1][0] = a22;
    matrix[1][1] = a12;
  }
  int saddleRow, saddleCol, saddleValue;
  while (findSaddlePoint(matrix, saddleRow, saddleCol, saddleValue)  == false || is_out_of_bounds(matrix)) {
    create_matrix_with_no_saddle_point(matrix, max_num);
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
