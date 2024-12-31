// display_params.h
#ifndef GAMING_FUNCTIONS_H
#define GAMING_FUNCTIONS_H

// Функция для генерации случайного бинарного числа на основе вероятности p
int random_binary(float p);

// Функция, которая возвращает сумму за раунд
int one_round(float pA, float pB, int matrix[2][2]);

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

int probability_selection_efficiency(float fst_expected_value, float snd_expected_value, float fst_real_value, float snd_real_value);

void create_matrix_for_game(int matrix[2][2], int rows = 2, int cols = 2, int min_num = -99, int max_num = 99);

//функция для поиска седловой точки
bool findSaddlePoint(int matrix[2][2], int& saddleRow, int& saddleCol, int& saddleValue);

#endif //GAMING_FUNCTIONS_H