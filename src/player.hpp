#pragma once

#include "constants.hpp"
#include <stdlib.h>
#include <vector>

std::vector<int> legal_moves(t_board &board);
int to_board_state(t_board &board);
void from_board_state(int board_state, t_board &board);

class Player {
private:
  t_player player;

public:
  Player(t_player player_id) { player = player_id; }

  int play_random(t_board &board) {
    std::vector<int> valid_moves = legal_moves(board);
    if (valid_moves.size() < 1) {
      return status::INVALID_MOVE;
    }
    int choice = rand() % valid_moves.size();
    return valid_moves[choice];
  }


  float calculate_reward(status st) {
    switch (st) {
    case status::INVALID_MOVE:
      return reward::LOOSE;
    case status::FINISHED:
      if (st == status::WIN_PLAYER1) {
        return (player == board::PLAYER1) ? reward::WIN : reward::LOOSE;
      } else {
        return (player == board::PLAYER2) ? reward::WIN : reward::LOOSE;
      }
    case status::WIN_PLAYER1:
      return (player == board::PLAYER1) ? reward::WIN : reward::LOOSE;
    case status::WIN_PLAYER2:
      return (player == board::PLAYER2) ? reward::WIN : reward::LOOSE;
    default:
      return reward::NONE;
    }
  }

  friend bool operator==(const t_player p1, const Player &p) {
    return p1 == p.player;
  }
};