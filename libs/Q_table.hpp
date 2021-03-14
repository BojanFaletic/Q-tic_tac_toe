#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

#include "player_util.hpp"
#include "logging.hpp"
#include "print.hpp"

class Q_table
{
  std::map<int, float> table;
  int player_id;

public:
  Q_table() { player_id = board::PLAYER1; };
  Q_table(int player_id) : player_id{player_id}
  {
  }

  void write(int key, float value) { table[key] = value; }

  float read(int key)
  {
    auto it = table.find(key);
    if (it == table.end())
    {
      return 0;
    }
    return it->second;
  }

  void save_model()
  {
    table_to_file(table, player_id);
  }

  void load_model()
  {
    table_from_file(table, player_id);
  }

  float &operator[](int key) { return table[key]; }

  friend std::ostream &operator<<(std::ostream &os, Q_table &Q)
  {
    for (auto el : Q.table)
    {
      if (el.second != 0)
      {
        os << el.first << " : " << el.second << std::endl;
      }
    }
    return os;
  }
};