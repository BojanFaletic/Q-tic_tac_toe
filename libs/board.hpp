#pragma once
#include <string>
#include "constants.hpp"

bool check_board(int row, int column, int player, t_board &tic_tac_toe);
const std::string print_board(t_board &b);