from matrix_generations import *
from formula import *
from game_process import *


num_rows = 3
num_cols = 3
min_num_for_random = -99
max_num_for_random = 99
num_moves = 3


def loop():
    matrix = create_matrix_with_saddle_point(num_rows, num_cols, min_num_for_random, max_num_for_random)
    players_elections = game_process(matrix, num_rows, num_cols, num_moves)
    _, _, saddle_value = find_saddle_point(matrix)
    min_matrix_num = min([min(row) for row in matrix])
    max_matrix_num = max([max(row) for row in matrix])
    print(round(calculate_proximity_percentage(players_elections, saddle_value, min_matrix_num, max_matrix_num)))


if __name__ == "__main__":
    while True:
        loop()
    