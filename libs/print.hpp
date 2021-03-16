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
void tournament_summary(int n_games, int wins_p1, int wins_p2);
void display_move(bool is_p1_moved, int action, t_board board);
void winning_screen(status st, t_board board);
std::string winner(status st);