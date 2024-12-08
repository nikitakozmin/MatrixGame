import random # Единственный модуль

def game_process(rows=5, cols=5, min_num=0, max_num=100): #черновой черновик
    matrix = create_matrix_with_saddle_point(rows=rows, cols=cols, min_num=min_num, max_num=max_num)
    res = []
    saddle_point = find_saddle_point(matrix)
    # print("Матрица:") # Визуализация
    # for row in matrix:
    #     print(row)
    # print("Седловая точка ", saddle_point) # Перепроверка
    for round in range(5): # Если индексация с 0 - убрать минусы
        row = int(input())-1
        col = int(input())-1
        res.append(matrix[row][col])
    return res.count(saddle_point)/len(res)  # ЗДЕСЬ ПОСТАВИТЬ ДРУГУЮ ФОРМУЛУ ПОДСЧЁТА

# Создание матрицы с гарантированной седловой точкой
def create_matrix_with_saddle_point(rows=3, cols=3, min_num=0, max_num=100):
    # Создаём случайную матрицу
    matrix = [[random.randint(min_num, max_num) for i in range(cols)] for i in range(rows)]

    # Находим строку с наибольшим из минимальных элементов (первую, если их несколько)
    min_values = [min(row) for row in matrix]       # Массив минмумов строк
    saddle_row = min_values.index(max(min_values))  # Индекс строки с максимальным из минимальных элементов
    saddle_min = min(matrix[saddle_row])            # Минимальный элемент в этой строке
    saddle_col = matrix[saddle_row].index(saddle_min)  # Столбец минимального элемента

    # Корректируем, чтобы выбранный минимальных элемент оставался максимальным в столбце
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
            return (i + 1, col_idx + 1, row_min)  # Возвращаем 1-индексацию: строка, столбец, значение

    return None  # Если седловой точки нет
