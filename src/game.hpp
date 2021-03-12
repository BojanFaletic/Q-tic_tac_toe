#pragma once

#include "board.hpp"
#include "constants.hpp"

class Game {
private:
  t_board tic_tac_toe;
  int current_player;
  int move_counter;
  int status;

public:
  Game() { this->reset(); };

  void reset() {
    tic_tac_toe = {board::EMPTY_SQUARE};
    current_player = board::PLAYER1;
    move_counter = 0;
    status = reward::NONE;
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
    if (move_counter == number_of_squares) {
      return true;
    }
    return false;
  }

  void increment_move_cnt() { move_counter++; }

  bool is_valid_move(const int row, const int column) {
    return tic_tac_toe[column][row] == board::EMPTY_SQUARE;
  }

  int make_valid_move(int row, int column) {
    tic_tac_toe[column][row] = player();
    increment_move_cnt();
    if (is_finished(row, column, player())) {
      return status::FINISHED;
    }
    return status::IDLE;
  }

  int play(int action, t_board &observation, t_player &current_player,
           t_reward &reward) {

    status = status::IDLE;
    reward = reward::LOOSE;

    if (action < 0 || action > 8) {
      status = status::INVALID_MOVE;
      return status;
    }

    if (is_full()) {
      status = status::FINISHED;
      return status;
    }

    const int row = action % 3;
    const int column = action / 3;

    if (is_valid_move(row, column)) {
      status = make_valid_move(row, column);
      swap_player();
      reward = reward::NONE;
    } else {
      reward = reward::LOOSE;
      status = status::INVALID_MOVE;
    }

    current_player = player();
    observation = tic_tac_toe;
    return status;
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

  bool is_game_active() { return status == status::IDLE; }
};