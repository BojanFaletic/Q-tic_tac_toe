#pragma once
#include "constants.hpp"
#include <string>
#include <sstream>

bool check_board(int row, int column, int player, t_board &tic_tac_toe);
status full_check(t_board &board);
void clear_board(t_board &board);