#ifndef GAMING_FUNCTIONS_H
#define GAMING_FUNCTIONS_H

// Функция для возведения 10 в степень без использования pow
double scale_factor(int decimals);

// Округление до заданного количества знаков после запятой
double round_to(double value, int decimals);

// Ожидаемое значение для матрицы игры
// matrix - матрица выигрышей, q и p - вероятности выбора строк и столбцов
double mate_expectation_of_game_matrix(int matrix[2][2], double q, double p);

struct Probabilities {
    double q;
    double p;
};

Probabilities ideal_probabilities_for_mixed_strategy(int matrix[2][2]);

bool is_out_of_bounds(int matrix[2][2]);

int probability_selection_efficiency(float fst_expected_value, float snd_expected_value, float fst_real_value, float snd_real_value);

// Создание матрицы без седловой точки
void create_matrix_with_no_saddle_point(int matrix[2][2], int max_num = 99);

//функция для поиска седловой точки
bool findSaddlePoint(int matrix[2][2], int& saddleRow, int& saddleCol, int& saddleValue);

#endif 
