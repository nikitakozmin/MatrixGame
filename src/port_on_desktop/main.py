from matrix_generations import *
from game_process import *

num_rows = 2
num_cols = 2
max_num_for_random = 99
num_moves = 5

def loop():
    matrix = create_matrix_with_no_saddle_point(num_rows, num_cols, max_num_for_random)
    print(*matrix, sep='\n')
    game_sum, total_effect = game_process(matrix, num_moves)
    print("Total effect:", str(round(total_effect, 2)) + '%', "|", "Score:", round(game_sum, 2))
    
if __name__ == "__main__":
    while True:
        loop()
