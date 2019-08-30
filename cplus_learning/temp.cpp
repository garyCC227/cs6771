#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Node {
  Node(int value, double value2): value{value}, value2{value2}{};
  int value;
  double value2;
};

template <typename N>
struct CustomComparator{
  bool operator()(const N& lhs, const N& rhs){
    return lhs.lock()->value < rhs.lock()->value;
  }
};

int main(int argc, char const *argv[]) {
  // std::set<std::weak_ptr<Node>, CustomComparator<std::weak_ptr<Node>>> temp;

  std::shared_ptr<Node> n1 = std::make_shared<Node>(4, 4.0); 
  std::shared_ptr<Node> n2 = std::make_shared<Node>(2, 4.0); 
  auto n3 = std::make_shared<Node>(5, 4.0); 
  auto n4 = std::make_shared<Node>(1, 4.0); 


  std::weak_ptr<Node> wp1 = n1;
  std::cout << wp1.lock()->value << '\n';
  
  n1.reset();
  if(!wp1.lock()){
    std::cout << "Null" << '\n';
  }
  wp1 = n2;
  
  std::cout << wp1.lock()->value << '\n';
  // std::cout << '------------------------\n';
  // // auto found = temp.find(n1);
  // for(const auto& n : temp){
  //   std::cout << n.value <<'\n';
  // }

  // auto ptr = std::make_shared<Node>(1, 5.0);
  // std::weak_ptr<Node> temp = ptr;
  // // {
  // //   auto temp2 = temp.lock();
  // //   if (temp2) {
  // //     std::cout << temp2->value << '\n';
  // //   }
  // // }

  // // std::shared_ptr<Node> ptr2 {std::move(ptr)};
  // // ptr2->value = 5;
  // // std::cout << ptr2.use_count() << '\n';

  // auto ptr2 = std::make_shared<Node>(5, 5.0);

  // ptr.swap(ptr2);

  // std::cout << ptr->value << '\n';
  // ptr2->value = 2;
  // auto temp2 = temp.lock();
  // if(temp2){
  //   std::cout << temp2->value << '\n';
  // }
  return 0;
}
