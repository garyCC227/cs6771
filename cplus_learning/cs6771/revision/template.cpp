#include <iostream>

template<typename A>
void print(const A& msg){
  std::cout << msg << '\n';
}
template<typename T, typename... B>
void print(T head, B... tails){
  print(head);
  print(tails...);
}

template<typename... T>
void show(T&&... elements){
  print(std::forward<T>(elements)...);
}

template<typename T, typename Y>
T min(T&& A, Y&& B){
  return (A > B) ? B : A;
}

int main(){
  // show(1,2,3,4,5,5,6,"hello world");
  std::cout << min<int, double>(10.5, 5.5) << '\n';
}