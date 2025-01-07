import pytest
from matrix_generations import *
from matrix_handler import *


@pytest.mark.parametrize("fst_expected_value, snd_expected_value, fst_real_value, snd_real_value, expected", [
    (1, 1, 0, 0, 0),
    (0, 0, 0, 0, 100),
    (0.5, 0.5, 0.5, 0.5, 100),
    (0.5, 0.5, 0, 0, 50),
    (1, 1, 0.5, 0.5, 50),
])
def test_probability_selection_efficiency(fst_expected_value, snd_expected_value, fst_real_value, snd_real_value, expected):
    assert probability_selection_efficiency(fst_expected_value, snd_expected_value, fst_real_value, snd_real_value) == expected


@pytest.mark.parametrize("matrix, mate_expectation, expected_probabilities", [
    ([[1, 2], [2, 1]], 1.5, (0.5, 0.5)),
    ([[0, 2], [2, 1]], 1.33, (0.33, 0.33)),
    ([[2, 0], [-2, 1]], 0.4, (0.6, 0.2)),
])
def test_ideal_probabilities_for_mixed_strategy(matrix, mate_expectation, expected_probabilities):
    assert mate_expectation_of_game_matrix(matrix, *expected_probabilities) == mate_expectation
    assert ideal_probabilities_for_mixed_strategy(matrix) == expected_probabilities
