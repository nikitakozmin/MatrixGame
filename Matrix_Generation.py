import numpy as np

# Создание матрицы с гарантированной седловой точкой
def create_matrix_with_saddle_point(rows=3, cols=3):
    # Создаём случайную матрицу
    matrix = np.random.randint(-1000, 1000, size=(rows, cols))

    # Находим максимин строку (строка с наибольшим минимальным элементом)
    saddle_row = np.argmax(matrix.min(axis=1))  # Индекс строки с максимальным из минимальных элементов
    saddle_min = matrix[saddle_row, :].min()   # Минимальный элемент в этой строке
    saddle_col = matrix[saddle_row, :].argmin()  # Индекс минимального элемента (столбец)

    # Корректируем столбец, чтобы выбранный элемент оставался максимальным
    matrix[:, saddle_col] = np.random.randint(-1000, saddle_min, size=rows)  # Остальные элементы столбца меньше saddle_min

    # Возвращаем элемент [saddle_row, saddle_col] в первоначальное значение
    matrix[saddle_row, saddle_col] = saddle_min

    return matrix

# Поиск седловой точки
def find_saddle_point(matrix):
    rows, cols = matrix.shape

    for i in range(rows):
        # Находим минимальный элемент строки и его индекс
        row_min = matrix[i, :].min()
        col_idx = matrix[i, :].argmin()

        # Проверяем, является ли он максимальным в столбце
        if row_min == matrix[:, col_idx].max():
            return (i + 1, int(col_idx + 1), int(row_min))  # Возвращаем 1-индексацию: строка, столбец, значение

    return None  # Если седловой точки нет

# Пример использования
matrix = create_matrix_with_saddle_point(5, 5)
print("Матрица:")
print(matrix)

saddle_point = find_saddle_point(matrix)
print("\nСедловая точка (строка, столбец, значение):")
print(saddle_point if saddle_point else "Седловых точек нет")
