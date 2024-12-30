void create_matrix_for_game(int matrix[2][2], int rows = 2, int cols = 2, int min_num = -99, int max_num = 99) {
  // Инициализация генератора случайных чисел
  randomSeed(analogRead(A0));

  // Создание массива всех возможных чисел
  int num_elements = max_num - min_num + 1;
  int all_numbers[num_elements];
  for (int i = 0; i < num_elements; i++) {
    all_numbers[i] = min_num + i;
  }

  // Перемешивание массива чисел
  for (int i = num_elements - 1; i > 0; i--) {
    int j = random(i + 1);
    int temp = all_numbers[i];
    all_numbers[i] = all_numbers[j];
    all_numbers[j] = temp;
  }

  // Заполнение матрицы случайными числами
  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = all_numbers[index++];
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
