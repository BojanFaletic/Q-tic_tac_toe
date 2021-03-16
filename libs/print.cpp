#include "print.hpp"

const char *space = "      ";

void print(std::vector<std::pair<int, float>> v)
{
  for (auto el : v)
  {
    std::cout << el.first << ":" << el.second << " ";
  }
  std::cout << '\n';
}

void print(std::vector<int> v)
{
  for (auto el : v)
  {
    std::cout << el;
  }
  std::cout << '\n';
}

void print_header(std::size_t n)
{
  const char *header = "---+---+---";
  for (ulong i = 0; i < n; i++)
  {
    std::cout << header << space;
  }
  std::cout << '\n';
}

void print_player(int player_id, bool use_number, int idx)
{
  switch (player_id)
  {
  case board::PLAYER1:
    std::cout << symbols::PLAYER1;
    return;
  case board::PLAYER2:
    std::cout << symbols::PLAYER2;
    return;
  default:
    std::cout << ((use_number) ? *std::to_string(idx).c_str() : symbols::BLANK);
  }
}

void print_score(std::vector<std::pair<int, float>> score)
{
  for (auto &el : score)
  {
    std::cout << el.first << " : " << el.second << std::endl;
  }
}

void print_line(std::vector<t_board> &b, std::size_t row_num, bool use_number)
{
  const char *vertical_line = " | ";
  const char *small_seperator = " ";

  for (unsigned int j = 0; j < 3 * b.size(); j++)
  {
    std::size_t k = j % 3;
    std::size_t board_id = j / 3;

    if (k == 1 || k == 2)
    {
      std::cout << vertical_line;
    }
    if (k == 0)
    {
      std::cout << small_seperator;
    }
    int idx = static_cast<int>(row_num * 3 + k);
    print_player(b[board_id][row_num][k], use_number, idx);

    if (k == 2)
    {
      std::cout << small_seperator;
      std::cout << space;
    }
  }
  std::cout << "\n";
}

void print_help_board(t_board &b){
  t_board blank_board;
  clear_board(blank_board);
  std::vector<t_board> tmp_board{b, blank_board};
  print_board(tmp_board, true);
}

void print_board(t_board &b)
{
  std::vector<t_board> vector{b};
  print_board(vector, false);
}

void print_board(t_board &b, bool use_numbers)
{
  std::vector<t_board> vector{b};
  print_board(vector, use_numbers);
}

void print_board(std::vector<t_board> &b, bool use_numbers)
{
  std::cout << "\n";
  print_line(b, 0, use_numbers);
  print_header(b.size());
  print_line(b, 1, use_numbers);
  print_header(b.size());
  print_line(b, 2, use_numbers);
}
