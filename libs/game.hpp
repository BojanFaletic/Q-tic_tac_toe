#pragma once

#include <stdlib.h>
#include "print.hpp"
#include "board.hpp"
#include "constants.hpp"

class Game
{
private:
  t_board tic_tac_toe;
  int current_player;
  bool is_active;
  int move_counter;
  int player_1_wins, player_2_wins;
  int total_games;
  status board_status;

public:
  Game()
  {
    player_1_wins = 0;
    player_2_wins = 0;
    total_games = 0;
    board_status = init_status();
    reset();
  };

  Game(t_board brd, int player)
  {
    player_1_wins = 0;
    player_2_wins = 0;
    total_games = 0;
    tic_tac_toe = brd;
    current_player = player;
    is_active = is_finished();
    move_counter = 0;
    board_status = init_status();
  }

  status init_status()
  {
    return full_check(tic_tac_toe);
  }

  void reset()
  {
    clear_board(tic_tac_toe);
    current_player = (rand() % 2) ? board::PLAYER1 : board::PLAYER2;
    move_counter = 0;
    total_games++;
    is_active = is_finished();
  }

  int player() { return current_player; }

  void swap_player()
  {
    if (current_player == board::PLAYER1)
    {
      current_player = board::PLAYER2;
    }
    else
    {
      current_player = board::PLAYER1;
    }
  }

  bool is_finished()
  {
    board_status = full_check(tic_tac_toe);
    return board_status != status::IDLE || is_full();
  }

  bool is_full()
  {
    for (auto &row:tic_tac_toe){
      for (auto el:row){
        if (el==board::EMPTY_SQUARE){
          return false;
        }
      }
    }
    return true;
  }

  void increment_move_cnt() { move_counter++; }

  bool is_valid_move(ulong row, ulong column)
  {
    return tic_tac_toe[column][row] == board::EMPTY_SQUARE;
  }

  status make_valid_move(ulong row, ulong column)
  {
    tic_tac_toe[column][row] = player();
    increment_move_cnt();
    if (is_finished())
    {
      is_active = false;
      status st = (current_player == board::PLAYER1) ? status::WIN_PLAYER1 : status::WIN_PLAYER2;
      if (st == status::WIN_PLAYER1)
      {
        player_1_wins++;
      }
      if (st == status::WIN_PLAYER2)
      {
        player_2_wins++;
      }
      return st;
    }
    return status::IDLE;
  }

  status check_status()
  {
    return status::WIN_PLAYER1;
  }

  status play(int action, t_board &observation, t_player &current_player)
  {
    if (action < 0 || action > 8)
    {
      is_active = false;
      board_status = status::INVALID_MOVE;
      return board_status;
    }

    const ulong row = static_cast<ulong>(action) % 3;
    const ulong column = static_cast<ulong>(action) / 3;

    if (is_valid_move(row, column))
    {
      board_status = make_valid_move(row, column);
      swap_player();
    }
    else
    {
      is_active = false;
      board_status = status::INVALID_MOVE;
      return board_status;
    }

    current_player = player();
    observation = tic_tac_toe;

    if (is_full())
    {
      is_active = false;
      board_status = status::FINISHED;
    }
    return board_status;
  }

  void set_board(t_board new_board, t_player new_player)
  {
    tic_tac_toe = new_board;
    current_player = new_player;
  }

  t_board get_board(){
    return tic_tac_toe;
  }

  void observe(t_board &board) { board = tic_tac_toe; }

  void number_of_wins(int &p1_wins, int &p2_wins)
  {
    p1_wins = player_1_wins;
    p2_wins = player_2_wins;
  }

  int number_of_games()
  {
    return total_games - 1;
  }

  friend std::ostream &operator<<(std::ostream &os, Game &G)
  {
    print_board(G.tic_tac_toe);
    return os;
  }

  status get_status()
  {
    return board_status;
  }

  bool is_game_active()
  {
    return !is_finished();
  }
};