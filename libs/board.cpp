#include "board.hpp"

bool check_row(int row, int player, t_board &tic_tac_toe)
{
  for (int i = 0; i < 3; i++)
  {
    if (tic_tac_toe[i][row] != player)
    {
      return false;
    }
  }
  return true;
}

bool check_column(int column, int player, t_board &tic_tac_toe)
{
  for (int i = 0; i < 3; i++)
  {
    if (tic_tac_toe[column][i] != player)
    {
      return false;
    }
  }
  return true;
}

bool check_diag_1(int player, t_board &tic_tac_toe)
{
  for (int i = 0; i < 3; i++)
  {
    if (tic_tac_toe[i][i] != player)
    {
      return false;
    }
  }
  return true;
}

bool check_diag_2(int player, t_board &tic_tac_toe)
{
  for (int i = 0; i < 3; i++)
  {
    if (tic_tac_toe[2 - i][i] != player)
    {
      return false;
    }
  }
  return true;
}

bool check_diag(int row, int column, int player, t_board &tic_tac_toe)
{
  if (row == 1 || column == 1)
  {
    return false;
  }
  return check_diag_1(player, tic_tac_toe) || check_diag_2(player, tic_tac_toe);
}

bool check_line(int row, int column, int player, t_board &tic_tac_toe)
{
  return check_row(row, player, tic_tac_toe) ||
         check_column(column, player, tic_tac_toe);
}

bool check_board(int row, int column, int player, t_board &tic_tac_toe)
{
  return check_diag(row, column, player, tic_tac_toe) ||
         check_line(row, column, player, tic_tac_toe);
}

const std::string print_board(t_board &b)
{
  std::stringstream os;
  for (int i = 0; i < 3; i++)
  {
    if (i > 0)
    {
      os << " ----+---+----\n";
    }
    else
    {
      os << '\n';
    }
    for (int j = 0; j < 3; j++)
    {
      if (j > 0)
      {
        os << " | ";
      }
      else
      {
        os << "   ";
      }
      if (b[i][j] == board::PLAYER1)
      {
        os << symbols::PLAYER1;
      }
      else if (b[i][j] == board::PLAYER2)
      {
        os << symbols::PLAYER2;
      }
      else
      {
        os << " ";
      }
    }
    os << " \n";
  }
  os << std::endl;
  return os.str();
}

const std::string print_board_with_numbers(t_board &b)
{
  std::stringstream os;
  for (int i = 0; i < 3; i++)
  {
    if (i > 0)
    {
      os << " ----+---+----\n";
    }
    else
    {
      os << '\n';
    }
    for (int j = 0; j < 3; j++)
    {
      if (j > 0)
      {
        os << " | ";
      }
      else
      {
        os << "   ";
      }
      if (b[i][j] == board::PLAYER1)
      {
        os << symbols::PLAYER1;
      }
      else if (b[i][j] == board::PLAYER2)
      {
        os << symbols::PLAYER2;
      }
      else
      {
        int idx = i * 3 + j;
        os << idx;
      }
    }
    os << " \n";
  }
  os << std::endl;
  return os.str();
}
