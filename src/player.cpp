#include "constants.hpp"
#include <cmath>
#include <vector>

const int empty_square = 0;
const int player_0 = 1;
const int player_1 = 2;

std::vector<int> legal_moves(t_board &board) {
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

int player_to_ID(int board_square) {
  switch (board_square) {
  case board::PLAYER1:
    return player_0;
  case board::PLAYER2:
    return player_1;
  default:
    return empty_square;
  }
}

int ID_to_player(int id) {
  switch (id) {
  case player_0:
    return board::PLAYER1;
  case player_1:
    return board::PLAYER2;
  default:
    return board::EMPTY_SQUARE;
  }
}

int to_board_state(t_board &board) {
  int board_idx = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int idx = i * 3 + j;
      board_idx += std::pow(3, idx) * player_to_ID(board[i][j]);
    }
  }
  return board_idx;
}

void from_board_state(int board_state, t_board &board) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int square_id = board_state % 3;
      board_state /= 3;
      board[i][j] = ID_to_player(square_id);
    }
  }
}
