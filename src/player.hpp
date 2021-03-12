#pragma once

#include "constants.hpp"
#include <stdlib.h>
#include <vector>

class Player {
private:
  t_player player;

public:
  Player(t_player player_id) { player = player_id; }

  int play_random(t_board& board) {
    std::vector<int> valid_moves = legal_moves(board);
    if (valid_moves.size() < 1) {
      return status::INVALID_MOVE;
    }
    int choice = rand() % valid_moves.size();
    return valid_moves[choice];
  }

  std::vector<int> legal_moves(t_board& board) {
    std::vector<int> valid;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == board::EMPTY_SQUARE) {
          valid.push_back(i * 3 + j);
        }
      }
    }
    return valid;
  }

  friend bool operator==(const t_player p1, const Player &p2) {
    return p1 == p2.player;
  }
};