#pragma once

#include "player.hpp"
#include "board.hpp"

class Player_user : public Player
{
public:
  Player_user(t_player player_id) : Player(player_id)
  {
  }

  int play(t_board &board) final
  {
    std::cout << "Enter move!\n";

    std::cout << print_board_with_numbers(board);
    std::vector<int> all_legal_moves = legal_moves(board);
    print(all_legal_moves);

    int user_move;
    bool is_valid = false;
    while (!is_valid)
    {
      std::cin >> user_move;

      for (auto el : all_legal_moves)
      {
        if (user_move == el)
        {
          return user_move;
        }
      }
    }
    return all_legal_moves.back();
  }
};