#include <iostream>
#include <memory>

template<int N>
struct Fabonacci{
  static constexpr long val = Fabonacci<N-1>::val + Fabonacci<N-2>::val;  
};

template<>
struct Fabonacci<0>
{
  static constexpr int val = 1;
};

template<>
struct Fabonacci<1>
{
  static constexpr int val = 1;
};

template<int first, int second, bool found>
struct GCD{
  static constexpr long val = GCD<second, first % second , (first % second == 0)>::val;
};

template<int first, int second>
struct GCD<first, second, true>{
  static constexpr int val = first;
};

// template<int first>
// struct GCD<first, 1, false>{
//   static constexpr int val = 1;
// };


int main(){
  // std::cout << Fabonacci<3>::val << "\n";
  std::cout << GCD<24, 36, (5%3 == 0)>::val << '\n';
}