#include "arena.hpp"

void winning_screen(status st, Game &g)
{
  std::cout << "\n";
  std::cout << "--------------------\n";
  std::cout << "End of game "
            << " " << winner(st) << std::endl;
  std::cout << g;
  std::cout << "--------------------\n";
  std::cout << "\n";
}

void display_move(bool is_p1_moved, int action, Game &g)
{
  std::cout << ((is_p1_moved) ? "P2" : "P1") << " action: " << action
            << std::endl;
  std::cout << g;
}

void tournament_summary(int n_games, int wins_p1, int wins_p2)
{
  int draws = n_games - (wins_p1 + wins_p2);

  int percentage_w1 = 100 * wins_p1 / n_games;
  int percentage_w2 = 100 *wins_p2 / n_games;
  int percentage_draw = 100 * draws / n_games;

  auto print_percent = [](int x) { return std::string(" (") + std::to_string(x) + std::string("%)\n"); };

  std::cout << "Number of games: " << n_games << std::endl;
  std::cout << "Wins p1: " << wins_p1 << print_percent(percentage_w1);
  std::cout << "Wins p2: " << wins_p2 << print_percent(percentage_w2);
  std::cout << "Draws: " << draws << print_percent(percentage_draw);
}

std::string winner(status st)
{
  if (st == status::WIN_PLAYER1)
  {
    return std::string("WIN: ") + symbols::PLAYER1;
  }
  if (st == status::WIN_PLAYER2)
  {
    return std::string("WIN: ") + symbols::PLAYER2;
  }
  return "Draw";
}

void turnament(Player &p1, Player &p2, Game &g, bool verbose_moves, bool verbose_game)
{
  t_board obs_board;
  t_player current_player;
  t_action action;
  status st;

  g.observe(obs_board);
  current_player = g.player();
  int timeout = 10;

  while (g.is_game_active())
  {
    if (current_player == p1)
    {
      action = p1.play(obs_board);
    }
    else
    {
      action = p2.play(obs_board);
    }
    st = g.play(action, obs_board, current_player);

    p2.observe(st, obs_board);
    p1.observe(st, obs_board);

    if (verbose_moves)
    {
      display_move(p1 == current_player, action, g);
    }
    if (timeout--==0){
      break;
    }
  }
  if (verbose_game)
  {
    winning_screen(g.get_status(), g);
  }
  g.reset();
}

void user_turnament()
{
  Player_random p1{board::PLAYER1};
  Player_user p2{board::PLAYER2};
  Game g;

  turnament(p1, p2, g, false, true);
}

void computer_turnament()
{
  const int n_games = 1000;

  Player_q p1{board::PLAYER1};
  Player_q p2{board::PLAYER2};
  Game g;

  p1.load_model();
  p2.load_model();

  play_n_games(p1, p2, g, n_games, true);

  p1.save_model();
  p2.save_model();
}

void train()
{
  const int n_games = 50000;
  const int epoch = 10;

  Player_q p1{board::PLAYER1};
  Player_q p2{board::PLAYER2};
  Game g;

  p1.load_model();
  p2.load_model();

  for (int i = 0; i < epoch; i++)
  {
    std::cout << "-----------------\n";
    play_n_games(p1, p2, g, n_games, true);
    std::cout << "Done epoch:" << i << '\n';
  }

  p1.save_model();
  p2.save_model();

  evaluate();
}

void train_random()
{
  const int n_games = 10000;
  const int epoch = 10;

  Player_q p1{board::PLAYER1};
  Player_random p2{board::PLAYER2};
  Game g;

  p1.load_model();

  for (int i = 0; i < epoch; i++)
  {
    std::cout << "-----------------\n";
    play_n_games(p1, p2, g, n_games, true);
    std::cout << "Done epoch:" << i << '\n';
  }

  p1.save_model();
}

void evaluate()
{
  const int n_games = 10000;

  Player_q p1{board::PLAYER1};
  Player_random p2{board::PLAYER2};
  Game g;

  p1.load_model();

  std::cout << "-----------------\n";
  play_n_games(p1, p2, g, n_games, true);
  std::cout << "Done" << '\n';
}

void play_n_games(Player &p1, Player &p2, Game &g, int n_games, bool print_summary)
{
  bool verbose_moves = false;
  bool verbose_ending = false;

  for (int i = 0; i < n_games; i++)
  {
    turnament(p1, p2, g, verbose_moves, verbose_ending);
  }
  if (print_summary)
  {
    int wins_player1 = 0;
    int wins_player2 = 0;
    g.number_of_wins(wins_player1, wins_player2);
    int cnt_games = g.number_of_games();
    tournament_summary(cnt_games, wins_player1, wins_player2);
  }
}

void debug_play()
{
  Player_q p1{board::PLAYER1};
  Player p2{board::PLAYER2};
  Game g;

  p1.load_model();
  play_n_games(p1, p2, g, 1, true);

  p1.save_model();
  std::cout << g;
}


void debug_single_move(){
  Player_q p1{board::PLAYER1};
  Player p2{board::PLAYER2};
  Game g;

  p1.load_model();
  turnament(p1, p2, g, true, true);
  p1.save_model();

}