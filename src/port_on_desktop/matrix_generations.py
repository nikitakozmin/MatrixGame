import random

# Создание матрицы с гарантированной седловой точкой
def create_matrix_with_saddle_point(rows=3, cols=3, min_num=-99, max_num=99):
    # Создаём случайную матрицу
    matrix = [[random.randint(min_num, max_num) for i in range(cols)] for i in range(rows)]

    # Находим строку с наибольшим из минимальных элементов (первую, если их несколько)
    min_values = [min(row) for row in matrix]           # Массив минимумов строк
    saddle_row = min_values.index(max(min_values))      # Индекс строки с максимальным из минимальных элементов
    saddle_min = min(matrix[saddle_row])                # Минимальный элемент в этой строке
    saddle_col = matrix[saddle_row].index(saddle_min)   # Столбец минимального элемента

    # Корректируем, чтобы выбранный минимальный элемент оставался максимальным в столбце
    for i in range(rows):
        if i != saddle_row:
            matrix[i][saddle_col] = random.randint(min_num, saddle_min)  # Остальные элементы меньше saddle_min

    return matrix

# Поиск седловой точки
def find_saddle_point(matrix):
    rows = len(matrix)
    cols = len(matrix[0])

    for i in range(rows):
        # Находим минимальный элемент строки и его индекс
        row_min = min(matrix[i])
        col_idx = matrix[i].index(row_min)

        # Проверяем, является ли он максимальным в столбце
        col_max = max(matrix[j][col_idx] for j in range(rows))
        if row_min == col_max:
            return (i, col_idx, row_min)  # Возвращаем: индекс строки, индекс столбца, значение

    return None  # Если седловой точки нет
