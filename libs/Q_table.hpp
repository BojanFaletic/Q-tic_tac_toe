#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <map>

#include "player_util.hpp"

class Q_table
{
  std::map<int, float> table;

public:
  Q_table() {}

  void write(int key, float value) { table[key] = value; }

  float read(int key)
  {
    auto it = table.find(key);
    if (it == table.end())
    {
      return 0;
    }
    return it->second;
  }

  float &operator[](int key) { return table[key]; }
};

class Q_learning
{
  const float discount_factor = 0.9;
  const float learning_rate = 0.1;
  Q_table table = Q_table();

public:
  int prev_state;
  Q_learning()
  {
    prev_state = 0;
  }

  std::pair<int, float> best_next_move(int board_state, int player)
  {
    std::pair<int, float> value{0, -100};
    t_board board;
    from_board_state(board_state, board);
    for (int move : legal_moves(board))
    {
      int row = move % 3;
      int column = move / 3;

      t_board virtual_board = board;
      virtual_board[column][row] = player;

      int new_state_id = to_board_state(virtual_board);
      float new_value = table[new_state_id];
      if (new_value > value.second)
      {
        value = {move, new_value};
      }
    }
    return value;
  }

  void learn(t_board &board, float reward, int player)
  {
    int state = to_board_state(board);
    std::pair<int, float> next_move = best_next_move(state, player);
    table[state] =
        table[state] +
        learning_rate *
            (reward + discount_factor * next_move.second - table[state]);

    int action = next_move.first;
  }
};
