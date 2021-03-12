#pragma once

#include "board.hpp"
#include "constants.hpp"

class Game {
private:
  t_board tic_tac_toe;
  int current_player;
  bool is_active;
  int move_counter;

public:
  Game() { this->reset(); };

  void reset() {
    tic_tac_toe = {board::EMPTY_SQUARE};
    current_player = board::PLAYER1;
    move_counter = 0;
    is_active = true;
  }

  int player() { return current_player; }

  void swap_player() {
    if (current_player == board::PLAYER1) {
      current_player = board::PLAYER2;
    } else {
      current_player = board::PLAYER1;
    }
  }

  bool is_finished(int row, int column, t_player player) {
    return check_board(row, column, player, tic_tac_toe);
  }

  bool is_full() {
    const int number_of_squares = 9;
    return move_counter == number_of_squares;
  }

  void increment_move_cnt() { move_counter++; }

  bool is_valid_move(const int row, const int column) {
    return tic_tac_toe[column][row] == board::EMPTY_SQUARE;
  }

  status make_valid_move(int row, int column) {
    tic_tac_toe[column][row] = player();
    increment_move_cnt();
    if (is_finished(row, column, player())) {
      is_active = false;
      return status::FINISHED;
    }
    return status::IDLE;
  }

  status play(int action, t_board &observation, t_player &current_player) {
    if (action < 0 || action > 8) {
      is_active = false;
      return status::INVALID_MOVE;
    }

    const int row = action % 3;
    const int column = action / 3;
    status st{status::IDLE};

    if (is_valid_move(row, column)) {
      st = make_valid_move(row, column);
      swap_player();
    } else {
      is_active = false;
      st = status::INVALID_MOVE;
    }

    current_player = player();
    observation = tic_tac_toe;

    if (is_full()) {
      is_active = false;
      return status::FINISHED;
    }
    return st;
  }

  void set_board(t_board new_board, t_player new_player) {
    tic_tac_toe = new_board;
    current_player = new_player;
  }

  void observe(t_board &board) { board = tic_tac_toe; }

  friend std::ostream &operator<<(std::ostream &os, Game &G) {
    os << print_board(G.tic_tac_toe);
    return os;
  }

  bool is_game_active() { return is_active; }
};