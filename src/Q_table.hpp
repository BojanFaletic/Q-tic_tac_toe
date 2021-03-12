#include <iostream>
#include <map>

class Q_table {
  std::map<int, float> table;

public:
  Q_table() {}

  void write(int key, float value) { table[key] = value; }

  float read(int key) {
    auto it = table.find(key);
    if (it == table.end()) {
      return 0;
    }
    return it->second;
  }

  float &operator[](int key){
    return table[key];
  }
};

class Q_learning {
  const float discount_factor = 0.9;
  const float learning_rate = 0.1;
  Q_table table;

  int prev_state;

public:
  Q_learning() {
    table = Q_table();
    prev_state = 0;
  }


  void learn(int state, int action, float reward) {
  }
};
