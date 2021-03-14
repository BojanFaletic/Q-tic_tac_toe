#pragma once

#include "constants.hpp"
#include "player.hpp"
#include "game.hpp"

#include "player_random.hpp"
#include "player_user.hpp"
#include "player_q.hpp"

void turnament(Player &p1, Player &p2, Game &g, bool verbose_moves, bool verbose_game);
void user_turnament();
void play_n_games(Player &p1, Player &p2, Game &g, int n_games, bool print_summary);
void winning_screen(status st, Game &g);
std::string winner(status st);
void display_move(bool is_p1_moved, int action, Game &g);
void computer_turnament();
void train();
void evaluate();
void train_random();