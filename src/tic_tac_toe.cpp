#include <iostream>

#include "board.hpp"
#include "game.hpp"
#include "player.hpp"


int main() {

  Game G1 = Game();

  Player P1 = Player(board::PLAYER1);
  Player P2 = Player(board::PLAYER2);

  srand(time(NULL));
  //srand(12345);

  t_board obs_board;
  t_player current_player;
  t_reward reward;
  t_action action;

  // player observe board
  G1.observe(obs_board);
  current_player = G1.player();

  // play random
  while (true){
    if (current_player == P1) {
      action = P1.play_random(obs_board);
      G1.play(action, obs_board, current_player, reward);
    } else {
      action = P2.play_random(obs_board);
      G1.play(action, obs_board, current_player, reward);
    }

    if (!G1.is_game_active()){
      break;
    }
    std::cout << "Played action: " << action << std::endl;
    std::cout << G1;

  }
}
