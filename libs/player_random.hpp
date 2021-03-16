#pragma once

#include "player.hpp"

class Player_random : public Player
{
public:
  Player_random(t_player player_id) : Player(player_id)
  {
  }

  int play(t_board &board) final
  {
    std::vector<int> valid_moves = legal_moves(board);
    if (valid_moves.size() < 1)
    {
      return status::INVALID_MOVE;
    }
    std::size_t choice = static_cast<std::size_t>(rand() % static_cast<int>(valid_moves.size()));
    return valid_moves[choice];
  }
};