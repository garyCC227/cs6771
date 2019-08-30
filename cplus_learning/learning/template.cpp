#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template <typename T>
class AddElements{
    public:
        T add(const T& e2);
    private:
        T element_;
};

template <typename T>
T AddElements<T>::add(const T& e2) {
    return this->element_ + e2;
}

int main () {
    std::string e1 = "2";
    std::string resutls = "1" + e1;
  std::cout << resutls;
  return 0;
}
