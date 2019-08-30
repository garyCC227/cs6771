#include <functional>
#include <iostream>
#include <string>

class BaseClass {
public:
  // int GetMember() const{ return member_; }
  // virtual std::string GetClassName() const{ return "BaseClass"; }
  // virtual std::string GetClassNmae() const = 0;

private:
  int size; int n;
  int member_;
  double size_;
};

// class SubClass : public BaseClass {
// public:
//   std::string GetClassName() const override{ return "SubClass"; }

// private:
//   int subclass_data_;
// };

// void PrintClassName(const BaseClass& base_class) {
//   std::cout << base_class.GetClassName() << ' ' << base_class.GetMember()
//             << '\n';
// }

int main() {
  BaseClass base_class;
  // SubClass subclass;
  std::cout << sizeof(BaseClass&) << '\n';
  // PrintClassName(base_class);
  // PrintClassName(subclass);
  // BaseClass& ref = subclass;
  // PrintClassName(ref);
  // std::cout << sizeof(ref) << '\n';

  std::cout << sizeof(base_class) << ", " << sizeof(std::ref(base_class)) <<
  '\n';
  // std::cout << sizeof(base_class) << ", " << sizeof(&base_class) << '\n';

}

// class Base {
// public:
//   virtual void PrintNum(int i = 1) { std::cout << "Base " << i << '\n'; }
// };
// class Derived : public Base {
// public:
//   void PrintNum(int i = 2) override { std::cout << "Derived " << i << '\n'; }
// };
// int main() {
//   Derived derived;
//   Base &base = derived;
//   derived.PrintNum(); // Prints "Derived 2"
//   base.PrintNum();   // Prints "Derived 1"
// }