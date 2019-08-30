#include <iostream>
#include <memory>

// namespace traits {
//   template <typename T> struct is_a_pointer { static const bool value = false; };

//   template <typename T> struct is_a_pointer<T *> {
//     static const bool value = true;
//   };
// } // namespace traits

// template <typename T> void printPointer(T t) {
//   if constexpr (traits::is_a_pointer<T>::value) {
//     std::cout << "Pointer" << "\n";
//   } else {
//     std::cout << "Not a pointer" << "\n";
//   }
// }

// int main() {
//   int i = 5;
//   int* t = &i;
//   printPointer(&i);
// }


///////======================== q8
// template <typename T, typename... B>
// auto my_make_unique(B&&... tails) {
//   return std::unique_ptr<T>{new T{std::forword<B>(tails)...}};
// }

// int main() {
//   MyClass myClass{"MyClass"};
//   std::cout << *my_make_unique<MyClass>(myClass) << "\n";
//   std::cout << *my_make_unique<MyClass>(std::move(myClass)) << "\n";
//   NonCopyable nonCopyable{"NonCopyable"};
//   std::cout << *my_make_unique<NonCopyable>(std::move(nonCopyable)) << "\n\n";

//   // Use the size constructor.
//   std::cout << my_make_unique<std::vector<MyClass>>(5U)->size() << "\n";

//   // Use the size-and-value constructor.
//   MyClass base{"hello"};
//   std::cout << my_make_unique<std::vector<MyClass>>(6U, base)->size() << "\n";
// }


//======================== q9

constexpr int factorial (int n) {
  if (n <= 1) {
  	return 1;
  }
  return n * factorial(n - 1);
};

template<int n> 
struct Factorial{
  static constexpr long val = Factorial<n-1>::val * n;
};

template<>
struct Factorial<0>{
  static constexpr int val = 1;
};

int main() {
  std::cout << Factorial<6>::val << std::endl;
}