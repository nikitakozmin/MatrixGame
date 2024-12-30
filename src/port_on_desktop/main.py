from matrix_generations import *
from matrix_handler import *
from game_process import *


num_rows = 2
num_cols = 2
min_num_for_random = -99
max_num_for_random = 99
num_moves = 5


def loop():
    matrix = create_matrix_for_game(num_rows, num_cols, min_num_for_random, max_num_for_random)
    print(*matrix, sep='\n')
    game_sum, total_effect = game_process(matrix, num_moves)
    print("Total effect:", total_effect, "|", "Score:", game_sum)
    
if __name__ == "__main__":
    while True:
        loop()
    