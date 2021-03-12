#include "gtest/gtest.h"

#include "../src/game.hpp"
#include "../src/player.hpp"

TEST(TestBoard, position1){
  Game G1 = Game();
  t_board board = {0};
  board[0] = {0,0,0};
  board[1] = {-1,0,1};
  board[2] = {1,0,-1};

  G1.set_board(board, board::PLAYER1);

  int action = 2;
  int current_player;
  int reward;
  G1.play(action, board, current_player, reward);

  EXPECT_EQ(0, G1.is_game_active());
}

TEST(TestPlayer, position1){
  t_board board = {0};
  board[0] = {0,0,0};
  board[1] = {-1,0,1};
  board[2] = {1,0,-1};

  Player P1 = Player(board::PLAYER1);

  std::vector<int> expected{0,1,2,4,7};
  EXPECT_EQ(expected, P1.legal_moves(board));
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}