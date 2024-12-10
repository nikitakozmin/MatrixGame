import pytest
from formula import calculate_proximity_percentage

@pytest.mark.parametrize("choices, saddle_value, min_num, max_num, expected", [
    ([4, 4, 4, 4, 4], 2, 0, 6, 50),
    ([2, 2, 1, 0, 0], 2, 0, 6, 50),
    ([0, 0, 0, 0, 0], 2, 0, 6, 0),
    ([2, 2, 2, 2, 2], 2, 0, 6, 100),
    ([2, 2, 2, 3, 0], 2, 0, 6, 75),
    ([4, 1, 0, 0, 0], 2, 0, 6, 25)
])
def test_calculate_proximity_percentage(choices, saddle_value, min_num, max_num, expected):
    assert calculate_proximity_percentage(choices, saddle_value, min_num, max_num) == expected