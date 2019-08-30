#include <iostream>
#include <memory>

class BaseClass {
public:
  BaseClass(){
    // std::cout << "Baseclass constructing\n";
  }

  virtual std::string GetClassName(){return "BaseClass\n";}
  virtual ~BaseClass() { std::cout << "Destructing base class\n"; }
};

class SubClass : public BaseClass {
  int size = 5;
public:
  SubClass(){
    // std::cout << "Subclass constructing\n";
  }

  std::string GetClassName()  { return "SubClass\n"; }
  ~SubClass() { 
    std::cout << size << '\n';
    std::cout << "Destructing subclass\n";
  }
};

int main() {
  SubClass child;
  BaseClass base = child;
  // std::unique_ptr<BaseClass> subclass{std::make_unique<SubClass>()};
  // std::cout << subclass->GetClassName();
}
