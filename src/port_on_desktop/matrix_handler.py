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

def mate_expectation_of_game_matrix(matrix, q, p):
    return round(matrix[0][0] * p * q + matrix[0][1] * q * (1 - p) + matrix[1][0] * p * (1 - q) + matrix[1][1] * (1 - q) * (1 - p), 2)

def ideal_probabilities_for_mixed_strategy(matrix):
    # Частные производные, найденные от мат ожидания
    q = (matrix[1][0] - matrix[1][1]) / (-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]) # Идеальная вероятность для первого
    p = (matrix[0][1] - matrix[1][1])/(-matrix[0][0]+matrix[0][1]+matrix[1][0]-matrix[1][1])  # Идеальная вероятность для второго
    return round(q, 2), round(p, 2)

def probability_selection_efficiency(fst_expected_value, snd_expected_value, fst_real_value, snd_real_value):
    return int(round((1-abs(fst_expected_value - fst_real_value) + 1-abs(snd_expected_value - snd_real_value)) / 2, 2)*100)
