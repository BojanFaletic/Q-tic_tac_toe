#pragma once

#include "constants.hpp"
#include "Q_table.hpp"
#include "player_util.hpp"
#include "logging.hpp"

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <map>

class Player
{
protected:
  t_player player;

public:
  Player(t_player player_id)
  {
    player = player_id;
  }

  virtual int play(t_board &board)
  {
    std::vector<int> valid_moves = legal_moves(board);
    if (valid_moves.size() < 1)
    {
      return status::INVALID_MOVE;
    }
    return valid_moves.back();
  }

  virtual void observe(status st, t_board &board){

  };

  int is_winner(status st)
  {
    if (st == status::WIN_PLAYER1)
    {
      return (player == board::PLAYER1) ? true : false;
    }
    else if (st == status::WIN_PLAYER2)
    {
      return (player == board::PLAYER2) ? true : false;
    }
    return false;
  }

  friend bool operator==(const t_player p1, const Player &p)
  {
    return p1 == p.player;
  }
};
