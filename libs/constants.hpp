#pragma once

#include <array>
#include <stdlib.h>

namespace board
{
  const int PLAYER1 = -1;
  const int PLAYER2 = 1;
  const int EMPTY_SQUARE = 0;
}

enum status
{
  IDLE,
  INVALID_MOVE,
  FINISHED,
  WIN_PLAYER1,
  WIN_PLAYER2
};

namespace reward
{
  const float NONE = 0;
  const float WIN = 10;
  const float LOOSE = -10;
}

namespace symbols
{
  const char PLAYER1 = 'X';
  const char PLAYER2 = 'Y';
}

using t_board = std::array<std::array<int, 3>, 3>;
using t_player = int;
using t_reward = int;
using t_action = int;