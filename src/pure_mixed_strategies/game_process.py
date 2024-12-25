from math_expectation_saddle import find_saddle_point, calculate_difference
from matrix_generation import create_matrix
import random

# Задаем выбор в зависимости от вероятности
def random_binary(p):
    if p > 1 or p < 0:
        raise ValueError
    return 1 if random.random() < p else 0 

# Выбор элемента в зависимости от вероятности
def one_round(input_p, matrix):
    pA, pB = input_p
    return matrix[random_binary(pA)][random_binary(pB)] # Элемент матрицы за раунд

# Игровой процесс
def game_process():
    # Создаем матрицу
    matrix = create_matrix(2,2)
    num_rounds = 5 # Количество рандов
    game_sum = 0 # Игровая сумма
    effect = 0 # Эффективность на ходу
    total_effect = 0 # Результативная эффективность
    # Находим седловую точку
    saddle_point = find_saddle_point(matrix)

    print(matrix)
    print(saddle_point)

    for i in range(num_rounds):
        input_arr = [float(i) for i in input().split()]
        game_sum += one_round(input_arr, matrix)
        # Если седловая точка не равна None, то рассчет эффективности проводим с ее помощью
        if saddle_point:
            # Рассчет эффективности на каждом шаге через седловую точку - накопительный эффект
            effect = int((game_sum/(saddle_point[2]*(i+1))) * 100)
            total_effect += effect
            print(f"Эффективность за шаг {i+1}: {int(effect)} % и общий результат {int(total_effect/(i+1))} %")
        else:
            # Рассчет эффективности на каждом шаге через мат ожидание - накопительный эффект
            effect = calculate_difference(matrix, input_arr[0], input_arr[1])
            total_effect += effect
            print(f"Эффективность за шаг {i+1}: {int(effect/(i+1))} % и общий результат {int(total_effect/(i+1))} %")

    print(f"Результативная эффективность выбора: {total_effect/num_rounds}")