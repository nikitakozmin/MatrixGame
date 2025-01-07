from matrix_handler import *

def game_process(matrix, num_moves=3):
    if len(matrix) != 2:
        raise ValueError("Incorrect column length")
    if len(matrix[0]) != 2:
        raise ValueError("Incorrect row length")
            
    game_sum = 0
    total_effect = 0
    effect = 0

    ideal_row_probability, ideal_column_probability = ideal_probabilities_for_mixed_strategy(matrix)
    ideal_expectation_of_game_matrix = mate_expectation_of_game_matrix(matrix, ideal_row_probability, ideal_column_probability)
    
    for _ in range(num_moves):
        fst_row_probability, fst_column_probability, *_ = [
            float(i) for i in input("Enter two probabilities separated by a space: ").strip().split()
        ]

        game_sum += round(mate_expectation_of_game_matrix(matrix, fst_row_probability, fst_column_probability))

        effect = probability_selection_efficiency(
            ideal_row_probability, ideal_column_probability, fst_row_probability, fst_column_probability
        )
        
        print("Effect:", str(round(effect, 2))+'%', "|", "Score:", round(game_sum, 2))

        total_effect += effect
        
    total_effect = int(round(total_effect / num_moves, 2))
    return game_sum, total_effect
