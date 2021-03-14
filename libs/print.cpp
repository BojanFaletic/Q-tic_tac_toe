#include "print.hpp"

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