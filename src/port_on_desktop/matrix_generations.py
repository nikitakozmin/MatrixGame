import random
from matrix_handler import *

# Создание матрицы без седловой точки
def create_matrix_with_no_saddle_point(rows=2, cols=2, max_num=100):
    # Генерация положительных чисел для главной диагонали
    a11 = random.randint(1, max_num)
    a22 = random.randint(1, max_num)

    # Общая сумма
    total_sum = a11 + a22

    # Ограничиваем разбиение, чтобы ни a12, ни a21 не превышали 100 по модулю
    if total_sum > max_num:
        split = random.randint(total_sum//2, max_num)
        a12 = -split
        a21 = -(total_sum - split)
    else:
        split = random.randint(1, total_sum - 1)
        a12 = -split
        a21 = -(total_sum - split)

    # Создаем матрицу
    matrix = [
        [a11, a12],
        [a21, a22]
    ]

    # Проверка на седловую точку
    while find_saddle_point(matrix) != None:
        matrix = create_matrix_with_no_saddle_point()

    return matrix
