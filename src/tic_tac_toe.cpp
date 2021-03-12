#include <iostream>

#include "board.hpp"
#include "game.hpp"
#include "player.hpp"

void print_vector(std::vector<int> &v){
  for (auto el:v){
    std::cout << el;
  }
  std::cout << std::endl;
}

int main() {

  Game G1 = Game();

  Player P1 = Player(board::PLAYER1);
  Player P2 = Player(board::PLAYER2);

  srand(time(NULL));
  // srand(12345);

  t_board obs_board;
  t_player current_player;
  t_action action;

  // player observe board
  G1.observe(obs_board);
  current_player = G1.player();

  // play random
  while (G1.is_game_active()) {
    if (current_player == P1) {
      action = P1.play_random(obs_board);
    } else {
      action = P2.play_random(obs_board);
    }
    G1.play(action, obs_board, current_player);

    std::cout << ((current_player == P1) ? "P1" : "P2") << " action: " << action
              << std::endl;
    std::cout << G1;
  }
}
