#include <iostream>

#include "board.hpp"
#include "game.hpp"
#include "player.hpp"
#include "logging.hpp"
#include "print.hpp"

std::string winner(int win_p1, int win_p2)
{
  if (win_p1)
  {
    return "WIN: X";
  }
  if (win_p2)
  {
    return "WIN: O";
  }
  return "Draw";
}

status turnament(Player &p1, Player &p2, Game &g, bool verbose_moves, bool verbose_game)
{
  t_board obs_board;
  t_player current_player;
  t_action action;
  status st;

  g.reset();
  g.observe(obs_board);
  current_player = g.player();

  // play random
  while (g.is_game_active())
  {
    if (current_player == p1)
    {
      action = p1.play_random(obs_board);
    }
    else
    {
      action = p2.play_Q(obs_board);
    }
    st = g.play(action, obs_board, current_player);

    // learn from action
    p2.observe(st, obs_board);

    if (verbose_moves)
    {
      std::cout << ((current_player == p1) ? "P2" : "P1") << " action: " << action
                << std::endl;
      std::cout << g;
    }
  }
  if (verbose_game)
  {
    std::cout << "End of game "
              << " " << winner(p1.is_winner(st), p2.is_winner(st)) << std::endl;
    std::cout << g;
    std::cout << "--------------------\n";
  }
  return st;
}

status user_turnament(Player &p1, Player &p2, Game &g)
{
  t_board obs_board;
  t_player current_player;
  t_action action;
  status st;

  g.reset();
  g.observe(obs_board);
  current_player = g.player();

  // play random
  while (g.is_game_active())
  {
    if (current_player == p1)
    {
      action = p1.play_user(obs_board);
    }
    else
    {
      action = p2.play_Q(obs_board);
    }
    st = g.play(action, obs_board, current_player);

    // learn from action
    p2.observe(st, obs_board);
  }
  return st;
}

void play_user()
{
  Game G1 = Game();
  Player P1 = Player(board::PLAYER1);
  Player P2 = Player(board::PLAYER2);

  t_board obs_board;
  t_player current_player;
  t_action action;
  status st;

  const bool load_model = true;

  if (load_model)
  {
    P2.load_model();
  }

  // player observe boardis_winner
  st = user_turnament(P1, P2, G1);

  std::cout << "End of game "
            << " " << winner(P1.is_winner(st), P2.is_winner(st)) << std::endl;
  std::cout << G1;
  std::cout << "--------------------\n";
}

void play_n_games(int n_games, bool save_model, bool load_model, bool print_summary)
{

  Game G1 = Game();
  Player P1 = Player(board::PLAYER1);
  Player P2 = Player(board::PLAYER2);

  t_board obs_board;
  t_player current_player;
  t_action action;
  status st;

  bool verbose_moves = true;
  bool verbose_ending = true;

  int wins_player1 = 0;
  int wins_player2 = 0;

  if (load_model)
  {
    P2.load_model();
  }

  // player observe boardis_winner
  for (int i = 0; i < n_games; i++)
  {
    st = turnament(P1, P2, G1, verbose_moves, verbose_ending);

    wins_player1 += P1.is_winner(st);
    wins_player2 += P2.is_winner(st);
  }
  if (print_summary)
  {
    std::cout << "Number of games: " << n_games << std::endl;
    std::cout << "Wins p1: " << wins_player1 << std::endl;
    std::cout << "Wins p2: " << wins_player2 << std::endl;
  }

  if (save_model)
  {
    P2.save_model();
  }
}

void train(bool use_existing)
{
  const int train_for = 100000;
  const int epoch = 10;
  for (int i = 0; i < epoch; i++)
  {
    play_n_games(train_for, true, use_existing, true);
  }
}

void play(bool use_existing)
{
}

int main()
{

  srand(time(NULL));
  //srand(12345);

  //train(true);

  play_user();
}
