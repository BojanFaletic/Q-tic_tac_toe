#pragma once

#include "player.hpp"
#include <assert.h>

class Player_q : public Player
{
private:
  float alpha = 0.1F;
  float gamma = 0.9F;
  float exploration = 0.1F;

  static bool sort_pair(const std::pair<int, float> &a, const std::pair<int, float> &b)
  {
    return (a.second < b.second);
  }

protected:
  int old_state;

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

  bool explore(){
    return (rand() % 101) < static_cast<int>(exploration*100);
  }

  int select_random_action(t_board &board){
    std::vector<std::pair<int, float>> ranked_moves = possible_moves(board, player);
    assert(ranked_moves.size()>0);
    std::size_t random_idx = static_cast<ulong>(rand()) % ranked_moves.size();
    return ranked_moves[random_idx].first;
  }

  int play(t_board &board) override
  {
    int board_state = to_board_state(board);
    int best_move = best_next_move(board_state, player).first;

    if (explore()){
      best_move = select_random_action(board);
    }

    old_state = board_state;

    return best_move;
  }

  void swap_player(status &st)
  {
    if (st == status::WIN_PLAYER1)
    {
      st = status::WIN_PLAYER2;
    }
    else if (st == status::WIN_PLAYER2)
    {
      st = status::WIN_PLAYER1;
    }
  }

  void observe(status st, t_board &board) override
  {
    int new_state = to_board_state(board);
    float reward = calculate_reward(st);

    float best_q = best_next_move(old_state, player).second;
    bool is_finished = st == status::FINISHED;

    learn(new_state, best_q, reward, is_finished);
  }

  void learn(int new_state, float best_reward, float reward, bool is_terminal)
  {
    float &Q_new = Q[new_state];

    if (is_terminal)
    {
      Q_new = reward;
    }
    else
    {
      Q_new = (1 - alpha) * Q[old_state] + alpha * (reward + gamma * best_reward);
      assert(!(Q_new<reward::LOOSE || Q_new>reward::WIN));
    }
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
    const float random_amplitude = 1.F;

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
    if (all_legal_moves.empty())
    {
      print_board(board);
      throw "No valid moves found!";
    }

    if (all_legal_moves.size() == 1)
    {
      int board_id = to_board_state(board);
      float reward = Q[board_id];
      return {{all_legal_moves.back(), reward}};
    }

    for (int move : legal_moves(board))
    {
      ulong row = static_cast<ulong>(move % 3);
      ulong column = static_cast<ulong>(move / 3);

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