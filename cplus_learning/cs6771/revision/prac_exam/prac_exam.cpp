#include <iostream>

class Magnitude {
 public:
  Magnitude() : Magnitude(1) {}
  Magnitude(int l) : litres_{l} {}
  
  friend Magnitude operator*(const Magnitude& a, const Magnitude& b){
    return Magnitude{ a.getLitres() * b.getLitres() };
  }
  int getLitres() const {
    return litres_;
  }
 private:
  int litres_;
};

int main() {
  Magnitude a{8};
  Magnitude b{9};
  std::cout << (a*b).getLitres() << '\n';
}