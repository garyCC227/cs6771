#include <iostream>

void test(const int& val){
  std::cout << "const lvale" << '\n';
}


void test(int& val){
  std::cout << "lvaule" << '\n';
}

template<typename A>
void f(A&& a){
  test(std::forward<A>(a));
}

int i{1};
int g(){return i;}


int show(int a){
  std::cout << "int\n";
}

double show(i){
  std::cout << "int\n";
}

int main(){
  // f(g());
  show(2.2);

  return 0;
}