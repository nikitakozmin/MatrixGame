import random
from matrix_handler import *


def is_out_of_bounds(matrix):
    iq, ip = ideal_probabilities_for_mixed_strategy(matrix)
    return 0.1 > iq or iq > 0.9 or 0.1 > ip or ip > 0.9


# Создание матрицы без седловой точки
def create_matrix_with_no_saddle_point(rows=2, cols=2, max_num=99):
    # Генерация положительных чисел для главной диагонали
    a11 = random.randint(1, max_num)
    a22 = random.randint(1, max_num)

    # Общая сумма
    total_sum = a11 + a22

    # Ограничиваем разбиение, чтобы ни a12, ни a21 не превышали 99 по модулю
    if total_sum > max_num:
        split = random.randint(total_sum//2, max_num)
        a12 = -split
        a21 = -(total_sum - split)
    else:
        split = random.randint(1, total_sum - 1)
        a12 = -split
        a21 = -(total_sum - split)

    # Создаем матрицу
    if random.randint(0, 1):
        matrix = [
            [a11, a12],
            [a21, a22]
        ]
    else:
        # Транспонируем, чтобы возникали случаи с положительными числами на побочной диагонали
        matrix = [
            [a21, a11],
            [a22, a12]
        ]

    # Проверка на седловую точку
    while find_saddle_point(matrix) != None or is_out_of_bounds(matrix):
        matrix = create_matrix_with_no_saddle_point()

    return matrix
