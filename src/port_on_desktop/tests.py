import pytest
from matrix_generations import *

@pytest.mark.parametrize("iteration", range(100))
def test_to_create_guaranteed_saddle(iteration):
    assert find_saddle_point(create_matrix_with_saddle_point()) != None
