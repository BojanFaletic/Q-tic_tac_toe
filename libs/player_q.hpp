#pragma once

#include "player.hpp"

class Player_q : public Player
{
private:
  int old_state;
  float alpha = 0.9;
  float gamma = 0.9;

  static bool sort_pair(const std::pair<int, float> &a, const std::pair<int, float> &b)
  {
    return (a.second < b.second);
  }

public:
  Q_table Q;
  Player_q(t_player player_id) : Player(player_id)
  {
    old_state = 0;
    Q = Q_table(player_id);
  }

  float calculate_reward(status st)
  {
    switch (st)
    {
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

  int play(t_board &board) final
  {
    int board_state = to_board_state(board);
    int best_next_action = best_next_move(board_state, player).first;

    old_state = board_state;

    return best_next_action;
  }

  void swap_player(status &st){
    if (st == status::WIN_PLAYER1){
      st = status::WIN_PLAYER2;
    }
    else if (st == status::WIN_PLAYER2){
      st = status::WIN_PLAYER1;
    }
  }

  void observe(status st, t_board &board) final
  {
    swap_player(st);
    int new_state = to_board_state(board);
    float reward = calculate_reward(st);
    learn(old_state, new_state, reward);
  }

  void learn(int old_state, int new_state, float reward)
  {
    Q[old_state] = Q[old_state] + alpha * (reward + gamma * Q[new_state] - Q[old_state]);
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

  std::vector<std::pair<int, float>> possible_moves(t_board board, int player)
  {
    std::vector<std::pair<int, float>> value;
    std::vector<int> all_legal_moves = legal_moves(board);

    if (all_legal_moves.size() < 2)
    {
      int board_id = to_board_state(board);
      float reward = Q[board_id];
      return {{board_id, reward}};
    }

    for (int move : legal_moves(board))
    {
      int row = move % 3;
      int column = move / 3;

      t_board virtual_board = board;
      virtual_board[column][row] = player;

      int new_state_id = to_board_state(virtual_board);
      float new_value = Q[new_state_id];
      value.push_back({move, new_value});
    }
    return value;
  }

  void save_model()
  {
    Q.save_model();
  }

  void load_model()
  {
    Q.load_model();
  }
};