import random
# Создание матрицы
def create_matrix(rows=3, cols=3, min_num=-99, max_num=99):
    # Создаём случайную матрицу
    matrix = [[random.randint(min_num, max_num) for i in range(cols)] for i in range(rows)]

    # Корректируем элементы матрицы, чтобы они не повторялись
    seen = set()  # Множество для отслеживания уникальных значений
    for i in range(rows):
        for j in range(cols):
            while matrix[i][j] in seen:  # Пока элемент уже встречался
                matrix[i][j] = random.randint(min_num, max_num)  # Генерируем новое значение
            seen.add(matrix[i][j])  # Добавляем уникальный элемент в множество
    return matrix