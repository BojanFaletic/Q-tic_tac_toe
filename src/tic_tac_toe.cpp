#include <iostream>

#include "board.hpp"
#include "game.hpp"
#include "player.hpp"

void print_vector(std::vector<int> &v)
{
  for (auto el : v)
  {
    std::cout << el;
  }
  std::cout << std::endl;
}

void play_n_games(int n_games)
{

  Game G1 = Game();
  Player P1 = Player(board::PLAYER1);
  Player P2 = Player(board::PLAYER2);

  t_board obs_board;
  t_player current_player;
  t_action action;
  status st;

  int wins_player1 = 0;
  int wins_player2 = 0;

  // player observe board
  for (int i = 0; i < n_games; i++)
  {
    G1.reset();
    G1.observe(obs_board);
    current_player = G1.player();

    // play random
    while (G1.is_game_active())
    {
      if (current_player == P1)
      {
        action = P1.play_random(obs_board);
      }
      else
      {
        action = P2.play_random(obs_board);
      }
      st = G1.play(action, obs_board, current_player);

      if (false)
      {
        std::cout << ((current_player == P1) ? "P1" : "P2") << " action: " << action
                  << std::endl;
        std::cout << G1;
      }
    }
    wins_player1 += P1.is_winner(st);
    wins_player2 += P2.is_winner(st);
  }
  std::cout << "Number of games" << n_games << std::endl;
  std::cout << "Wins p1" << wins_player1 << std::endl;
  std::cout << "Wins p2" << wins_player1 << std::endl;
}

int main()
{

  srand(time(NULL));
  // srand(12345);

  play_n_games(100);
}
