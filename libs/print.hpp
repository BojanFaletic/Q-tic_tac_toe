#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "constants.hpp"
#include "board.hpp"

void print(std::vector<std::pair<int, float>> v);
void print(std::vector<int> v);
void print_board(t_board &b, bool use_numbers);
void print_board(std::vector<t_board> &b, bool use_numbers);

void print_board(t_board &b);
void print_help_board(t_board &b);
void print_score(std::vector<std::pair<int, float>> score);