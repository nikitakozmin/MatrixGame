# Рассчет математического ожидания
def calculate_difference(matrix, pA, pB):
    q = (matrix[1][0] - matrix[1][1]) / (-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]) # Идеальная вероятность для первого
    p = (matrix[0][1] - matrix[1][1])/(-matrix[0][0]+matrix[0][1]+matrix[1][0]-matrix[1][1])  # Идеальная вероятность для второго
    # Обрезаем значения до диапазона [0, 1]
    q = min(1, max(0, q))
    p = min(1, max(0, p))
    best_expected_value = matrix[0][0] * p * q + matrix[0][1] * q * (1 - p) + matrix[1][0] * p * (1 - q) + matrix[1][1] * (1 - q) * (1 - p)  # Идеальное мат.ожидание
    real_expecter_value = matrix[0][0] * pB * pA + matrix[0][1] * pA * (1 - pB) + matrix[1][0] * pB * (1 - pA) + matrix[1][1] * (1 - pA) * (1 - pB)  # Реально полученное мат.ожидание
    # Много вспомогательных выводов для тестов
    print("Отладочная информация: ", q, p, best_expected_value, real_expecter_value)
    return int(real_expecter_value/best_expected_value * 100)

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
