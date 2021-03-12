#include <array>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

namespace constants {
const int PLAYER1 = -1;
const int PLAYER2 = 1;
const int INVALID_MOVE = -1;
const int EMPTY_SQUARE = 0;
const int VALID_MOVE = 1;
const int WIN_REWARD = 10;
const int LOOSE_REWARD = -10;
const int IDLE_REWARD = 0;
const int FINISHED = 1;
} // namespace constants

using t_board = std::array<std::array<int, 3>, 3>;
using t_player = int;
using t_reward = int;
using t_action = int;

const std::string print_board(t_board &b) {
  std::stringstream os;
  for (int i = 0; i < 3; i++) {
    if (i > 0) {
      os << " ----+---+----\n";
    } else {
      os << '\n';
    }
    for (int j = 0; j < 3; j++) {
      if (j > 0) {
        os << " | ";
      } else {
        os << "   ";
      }
      if (b[i][j] == constants::PLAYER1) {
        os << "X";
      } else if (b[i][j] == constants::PLAYER2) {
        os << "O";
      } else {
        os << " ";
      }
    }
    os << " \n";
  }
  os << std::endl;
  return os.str();
}

class Game {
private:
  t_board tic_tac_toe;
  int current_player;
  int move_counter;

  bool check_row(int row, int player) {
    for (int i = 0; i < 3; i++) {
      if (tic_tac_toe[i][row] != player) {
        return false;
      }
    }
    return true;
  }

  bool check_column(int column, int player) {
    for (int i = 0; i < 3; i++) {
      if (tic_tac_toe[column][i] != player) {
        return false;
      }
    }
    return true;
  }

  bool check_diag_1(int player) {
    for (int i = 0; i < 3; i++) {
      if (tic_tac_toe[i][i] != player) {
        return false;
      }
    }
    return true;
  }

  bool check_diag_2(int player) {
    for (int i = 0; i < 3; i++) {
      if (tic_tac_toe[2 - i][2 - i] != player) {
        return false;
      }
    }
    return true;
  }

  bool check_diag(int row, int column, int player) {
    if (row == 1 || column == 1) {
      return false;
    }
    return check_diag_1(player) || check_diag_2(player);
  }

  bool check_line(int row, int column, int player) {
    return check_row(row, player) || check_column(column, player);
  }

public:
  Game() { this->reset(); };

  void reset() {
    tic_tac_toe = {constants::EMPTY_SQUARE};
    current_player = constants::PLAYER1;
    move_counter = 0;
  }

  int player() { return current_player; }

  void swap_player() {
    if (current_player == constants::PLAYER1) {
      current_player = constants::PLAYER2;
    } else {
      current_player = constants::PLAYER1;
    }
  }

  bool check_board(int row, int column, int player) {
    return check_diag(row, column, player) || check_line(row, column, player);
  }

  bool is_finished(const int move_idx, t_player player) {
    int row = move_idx % 3;
    int column = move_idx / 3;

    return check_board(row, column, player);
  }

  bool is_full() {
    const int number_of_squares = 9;
    if (move_counter == number_of_squares) {
      return true;
    }
    return false;
  }

  void increment_move_cnt() { move_counter++; }

  bool is_valid_move(const int row, const int column) {
    return tic_tac_toe[column][row] == constants::EMPTY_SQUARE;
  }

  int play(int action, t_board &observation, t_player &current_player,
           t_reward &reward) {

    int status = constants::IDLE_REWARD;
    reward = constants::LOOSE_REWARD;

    if (action < 0 || action > 8) {
      status = constants::INVALID_MOVE;
      return status;
    }

    if (is_full()){
      status = constants::FINISHED;
      return status;
    }

    int row = action % 3;
    int column = action / 3;

    if (is_valid_move(row, column)) {
      tic_tac_toe[column][row] = player();
      increment_move_cnt();
      reward = constants::VALID_MOVE;
      if (is_finished(action, player())) {
        status = constants::FINISHED;
      }
      swap_player();
    } else {
      reward = constants::LOOSE_REWARD;
      status = constants::INVALID_MOVE;
    }

    observation = tic_tac_toe;
    current_player = player();

    return status;
  }

  void set_board(t_board new_board, t_player new_player) {
    tic_tac_toe = new_board;
    current_player = new_player;
  }

  void observe(t_board& board) {
    board = tic_tac_toe;
  }

  friend std::ostream &operator<<(std::ostream &os, Game &G) {
    os << print_board(G.tic_tac_toe);
    return os;
  }
};

class Player {
private:
  t_player player;
  t_board local_board;

public:
  Player(t_player player_id) {
    player = player_id;
    }

  t_action play() {
    std::vector<int> valid_moves = legal_moves();
    if (valid_moves.size() > 0){
      return valid_moves[0];
    }
    return constants::INVALID_MOVE;
  }

  int play_random() {
    std::vector<int> valid_moves = legal_moves();
    if (valid_moves.size() < 1){
      return constants::INVALID_MOVE;
    }
    int choice = rand() % valid_moves.size();
    return valid_moves[choice];
  }

  std::vector<int> legal_moves(){
    std::vector<int> valid;
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){
        if (local_board[i][j] == constants::EMPTY_SQUARE){
          valid.push_back(i*3+j);
        }
      }
    }
    return valid;
  }

  void read_board(t_board &board) { local_board = board; }

  friend bool operator==(const t_player p1, const Player &p2){
    return p1 == p2.player;
  }
};

bool done(int status){
  return status == constants::INVALID_MOVE || status == constants::FINISHED;
}

int main() {

  Game G1 = Game();

  Player P1 = Player(constants::PLAYER1);
  Player P2 = Player(constants::PLAYER2);
  srand (time(NULL));


  t_board obs_board;
  t_player current_player;
  t_reward reward;
  t_action action;

  int status = 0;

  // player observe board
  G1.observe(obs_board);
  current_player = G1.player();

  // play random
  while (!done(status)){
    if (current_player == P1){
      P1.read_board(obs_board);
      action = P1.play_random();
      status = G1.play(action,obs_board, current_player, reward);
    }
    else{
      P2.read_board(obs_board);
      action = P2.play_random();
      status = G1.play(action,obs_board, current_player, reward);
    }

    std::cout << G1;

  }
}
