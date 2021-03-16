#include "board.hpp"
#include "print.hpp"

int check_row(t_board &board, std::size_t row)
{
  if (board[row][0] != board::EMPTY_SQUARE &&
      board[row][0] == board[row][1] &&
      board[row][1] == board[row][2])
  {
    return board[row][0];
  }
  return board::EMPTY_SQUARE;
}

int check_column(t_board &board, std::size_t column)
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

  for (std::size_t i = 0; i < 3; i++)
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