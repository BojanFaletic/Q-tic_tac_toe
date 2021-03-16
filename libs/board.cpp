#include "board.hpp"
#include "print.hpp"

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

int check_row(t_board &board, int row)
{
  if (board[row][0] != board::EMPTY_SQUARE &&
      board[row][0] == board[row][1] &&
      board[row][1] == board[row][2])
  {
    return board[row][0];
  }
  return board::EMPTY_SQUARE;
}

int check_column(t_board &board, int column)
{
  if (board[0][column] != board::EMPTY_SQUARE &&
      board[0][column] == board[1][column] &&
      board[1][column] == board[2][column])
  {
    return board[0][column];
  }
  return board::EMPTY_SQUARE;
}

int check_diagonal_1(t_board &board)
{
  if (board[0][0] != board::EMPTY_SQUARE && board[0][0] == board[1][1] &&
      board[1][1] == board[2][2])
  {
    return board[0][0];
  }
  return board::EMPTY_SQUARE;
}

int check_diagonal_2(t_board &board)
{
  if (board[0][2] != board::EMPTY_SQUARE && board[0][2] == board[1][1] &&
      board[1][1] == board[2][0])
  {
    return board[0][2];
  }
  return board::EMPTY_SQUARE;
}

status board_2status(int brd)
{
  switch (brd)
  {
  case board::PLAYER1:
    return status::WIN_PLAYER1;
  case board::PLAYER2:
    return status::WIN_PLAYER2;
  default:
    return status::IDLE;
  }
}

status full_check(t_board &board)
{
  int st;
  st = check_diagonal_1(board);
  if (st != board::EMPTY_SQUARE)
  {
    return board_2status(st);
  }
  st = check_diagonal_2(board);
  if (st != board::EMPTY_SQUARE)
  {
    return board_2status(st);
  }

  for (int i = 0; i < 3; i++)
  {
    st = check_row(board, i);
    if (st != board::EMPTY_SQUARE)
    {
      return board_2status(st);
    }
    st = check_column(board, i);
    if (st != board::EMPTY_SQUARE)
    {
      return board_2status(st);
    }
  }
  return board_2status(st);
}

void clear_board(t_board &board)
{
  for (auto &row : board)
  {
    for (auto &item : row)
    {
      item = board::EMPTY_SQUARE;
    }
  }
}