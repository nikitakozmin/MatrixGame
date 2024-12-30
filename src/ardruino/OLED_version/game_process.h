// Функция для генерации случайного бинарного числа на основе вероятности p
int random_binary(float p) {
    if (p > 1.0) {
      p = 1.0;
    }
    else if (p < 0.0) {
      p = 0.0;
    }
    return (rand() / (float)RAND_MAX) < p ? 0 : 1;
}

// Функция, которая возвращает сумму за раунд
int one_round(float pA, float pB, int matrix[2][2]) {
    int row = random_binary(pA);
    int col = random_binary(pB);

    return matrix[row][col];
}

// Функция для возведения 10 в степень без использования pow
double scale_factor(int decimals) {
    double scale = 1.0;
    for (int i = 0; i < decimals; ++i) {
        scale *= 10.0;
    }
    return scale;
}

// Округление до заданного количества знаков после запятой
double round_to(double value, int decimals) {
    double scale = scale_factor(decimals);
    return round(value * scale) / scale;
}

// Ожидаемое значение для матрицы игры
// matrix - матрица выигрышей, q и p - вероятности выбора строк и столбцов
double mate_expectation_of_game_matrix(int matrix[2][2], double q, double p) {
    return round_to(matrix[0][0] * p * q + 
                 matrix[0][1] * q * (1 - p) + 
                 matrix[1][0] * p * (1 - q) + 
                 matrix[1][1] * (1 - q) * (1 - p), 2);
}

struct Probabilities {
    double q;
    double p;
};

Probabilities ideal_probabilities_for_mixed_strategy(int matrix[2][2]) {
    Probabilities probabilities;
    probabilities.q = (matrix[1][0] - matrix[1][1]) / (-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]);
    probabilities.p = (matrix[0][1] - matrix[1][1]) / (-matrix[0][0] + matrix[0][1] + matrix[1][0] - matrix[1][1]);
    probabilities.q = round_to(probabilities.q, 2);
    probabilities.p = round_to(probabilities.p, 2);
    return probabilities;
}

int probability_selection_efficiency(float fst_expected_value, float snd_expected_value, float fst_real_value, float snd_real_value) {
    return (1 - abs(fst_expected_value - fst_real_value) + 1 - abs(snd_expected_value - snd_real_value)) / 2 * 100.0;
}

