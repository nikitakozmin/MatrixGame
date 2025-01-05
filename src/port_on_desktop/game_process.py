import random
from matrix_handler import *


def random_binary(p):
    """Задаем выбор в зависимости от вероятности"""
    if p > 1 or p < 0:
        raise ValueError
    if p <= 0.5:
        return 0 if random.random() <= p else 1
    if p > 0.5:
        return 0 if random.random() < p else 1


def one_round(input_p, matrix):
    """Выбор элемента в зависимости от вероятности"""
    pA, pB = input_p
    return matrix[random_binary(pA)][random_binary(pB)] # Элемент матрицы за раунд


def game_process(matrix, num_moves=3):
    if len(matrix) != 2:
        raise ValueError("Incorrect column length")
    if len(matrix[0]) != 2:
        raise ValueError("Incorrect row length")

    saddle_point = find_saddle_point(matrix)
    if saddle_point != None:
        saddle_point_row_index, saddle_point_column_index, saddle_point = saddle_point
            
    game_sum = 0
    total_effect = 0
    
    for _ in range(num_moves):
        fst_row_probability, fst_column_probability, *_ = [
            float(i) for i in input("Enter two probabilities separated by a space: ").strip().split()
        ]
        game_sum += one_round([fst_row_probability, fst_column_probability], matrix)
        
        # Задаём значения, которые должны были получится для идеальной стратегии
        if saddle_point:
            ideal_row_probability, ideal_column_probability = saddle_point_row_index, saddle_point_column_index
        else:
            ideal_row_probability, ideal_column_probability = ideal_probabilities_for_mixed_strategy(matrix)
        
        effect = probability_selection_efficiency(
            ideal_row_probability, ideal_column_probability, fst_row_probability, fst_column_probability
        )
        
        print("Effect:", str(effect)+'%', "|", "Score:", game_sum)
        total_effect += effect
        
    total_effect = int(round(total_effect / num_moves, 2))
    return game_sum, total_effect
