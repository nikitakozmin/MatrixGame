import random


# Создание матрицы с гарантированной седловой точкой - данная функция является тестовой и не используется в макете на Arduino
def create_matrix_with_saddle_point(rows=2, cols=2, min_num=-99, max_num=99):
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


def create_matrix_for_game(rows=2, cols=2, min_num=-99, max_num=99):
    """Создание матрицы, в которой седловых точек не больше одной"""
    row_values = [set() for _ in range(rows)]
    col_values = [set() for _ in range(cols)]
    matrix = [[0 for _ in range(cols)] for  _ in range(rows)]
    for i in range(rows):
        for j in range(cols):
            new_value = random.randint(min_num, max_num)
            while new_value in row_values[i] or new_value in col_values[j]:
                new_value = random.randint(min_num, max_num)
            row_values[i].add(new_value)
            col_values[j].add(new_value)
            matrix[i][j] = new_value
    return matrix
