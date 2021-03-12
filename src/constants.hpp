#pragma once

#include <array>

namespace board {
const int PLAYER1 = -1;
const int PLAYER2 = 1;
const int EMPTY_SQUARE = 0;
} // namespace board

namespace status {
const int IDLE = 0;
const int INVALID_MOVE = -1;
const int FINISHED = 1;
} // namespace status

namespace reward {
const int NONE = 0;
const int WIN = 10;
const int LOOSE = -10;
} // namespace reward

using t_board = std::array<std::array<int, 3>, 3>;
using t_player = int;
using t_reward = int;
using t_action = int;