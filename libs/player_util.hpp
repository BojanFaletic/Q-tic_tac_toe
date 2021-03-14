#pragma once

#include "constants.hpp"
#include <vector>

std::vector<int> legal_moves(t_board &board);
int to_board_state(t_board &board);
void from_board_state(int board_state, t_board &board);