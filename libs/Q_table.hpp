#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

#include "player_util.hpp"
#include "logging.hpp"
#include "print.hpp"

bool sort_pair(const std::pair<int, float> &a, const std::pair<int, float> &b)
{
  return (a.second < b.second);
}

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

  void save_model()
  {
    table_to_file(table);
  }

  void load_model()
  {
    table_from_file(table);
  }

  float &operator[](int key) { return table[key]; }

  friend std::ostream &operator<<(std::ostream &os, Q_table &Q)
  {
    for (auto el : Q.table)
    {
      if (el.second != 0)
      {
        os << el.first << " : " << el.second << std::endl;
      }
    }
    return os;
  }
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

  std::vector<std::pair<int, float>> possible_moves(t_board board, int player)
  {
    std::vector<std::pair<int, float>> value;
    std::vector<int> all_legal_moves = legal_moves(board);

    if (all_legal_moves.size() < 2)
    {
      int board_id = to_board_state(board);
      float reward = table[board_id];
      return {{board_id, reward}};
    }

    for (int move : legal_moves(board))
    {
      int row = move % 3;
      int column = move / 3;

      t_board virtual_board = board;
      virtual_board[column][row] = player;

      int new_state_id = to_board_state(virtual_board);
      float new_value = table[new_state_id];
      value.push_back({move, new_value});
    }
    return value;
  }

  std::pair<int, float> best_next_move(int board_state, int player)
  {
    t_board board;
    from_board_state(board_state, board);
    std::vector<std::pair<int, float>> ranked_moves = possible_moves(board, player);
    std::sort(ranked_moves.begin(), ranked_moves.end(), sort_pair);
    return ranked_moves.back();
  }

  int best_random_move(int board_state, int player)
  {
    int random_amplitude = 1;

    t_board board;
    from_board_state(board_state, board);
    std::vector<std::pair<int, float>> ranked_moves = possible_moves(board, player);
    for (auto &el : ranked_moves)
    {
      el.second += (rand() % 2 * random_amplitude) - random_amplitude;
    }
    std::sort(ranked_moves.begin(), ranked_moves.end(), sort_pair);
    return ranked_moves.back().first;
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

  void save_model()
  {
    table.save_model();
  }

  void load_model()
  {
    table.load_model();
  }

  friend std::ostream &operator<<(std::ostream &os, Q_learning &Q)
  {
    return os << Q.table;
  }
};
