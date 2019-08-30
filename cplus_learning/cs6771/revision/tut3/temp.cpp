#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> vec{"We", "love", "lambda", "functions", "a"};

  std::sort(vec.begin(), vec.end(), [](const auto &lhs, const auto &rhs) {
    return (lhs.size() < rhs.size());
  });

  for(const auto& e : vec){
    std::cout << e << '\n';
  }
}