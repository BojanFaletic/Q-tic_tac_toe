#pragma once

#include "constants.hpp"
#include "Q_table.hpp"
#include "player_util.hpp"

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <map>


class Player{
private:
  t_player player;
  Q_learning Q = Q_learning();

public:
  Player(t_player player_id) {
    player = player_id;
   }

  int play_random(t_board &board) {
    std::vector<int> valid_moves = legal_moves(board);
    if (valid_moves.size() < 1) {
      return status::INVALID_MOVE;
    }
    int choice = rand() % valid_moves.size();
    return valid_moves[choice];
  }

  int is_winner(status st){
    if (st == status::WIN_PLAYER1){
      return (player == board::PLAYER1) ? true : false;
    }
    else{
      return (player == board::PLAYER2) ? true : false;
    }
  }

  float calculate_reward(status st) {
    switch (st) {
    case status::INVALID_MOVE:
      return reward::LOOSE;
    case status::FINISHED:
      return (is_winner(st)) ? reward::WIN : reward::LOOSE;
    case status::WIN_PLAYER1:
      return (player == board::PLAYER1) ? reward::WIN : reward::LOOSE;
    case status::WIN_PLAYER2:
      return (player == board::PLAYER2) ? reward::WIN : reward::LOOSE;
    default:
      return reward::NONE;
    }
  }

  int play_Q(t_board &board){
    int board_state = to_board_state(board);
    int best_next_action = Q.best_next_move(board_state, player).first;

    return best_next_action;
  }

  void observe(status st, t_board &board){
    float reward = calculate_reward(st);
    Q.learn(board, reward, player);
  }

  friend bool operator==(const t_player p1, const Player &p) {
    return p1 == p.player;
  }
};