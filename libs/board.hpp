#pragma once
#include "constants.hpp"
#include <string>
#include <sstream>

bool check_board(int row, int column, int player, t_board &tic_tac_toe);
const std::string print_board(t_board &b);
const std::string print_board_with_numbers(t_board &b);