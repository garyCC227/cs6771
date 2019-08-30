#include <iostream>

int Factorial(int N){
  int base = 1;
  int result = N;
  int size = 2;
  auto found = [&](int& N){
    for(auto i = (N-1); i >= base; --i){
      result *= i;
    }
    std::cout << size << '\n';
    return result;
  };
  return found(N);
}

int main(){
  std::cout << Factorial(8) << '\n';
}