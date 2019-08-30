#include <iostream>
#include <set>

template <typename T, typename CONT = std::set<T>>
class SillySet {
 public:
  void insert(T t){
    set_.insert(t);
  }
  bool erase(T t){
    auto it = set_.find(t);
    if(it != set_.end()){
      set_.erase(it);
      return true;
    }
    return false;
  }

  friend std::ostream& operator<<(std::ostream& os, SillySet<T>& s){
    for(const auto& e:s.set_){
      os << e;
    }
    os << '\n';

    return os;
  } 
 private:
  CONT set_;
};

int main() {

  SillySet<float> s;
  SillySet<int> us;

  s.insert(5.4);
  s.insert(6.2);
  s.erase(5.4);
  std::cout << s << "\n";

  us.insert(5);
  us.insert(6);
  us.erase(5);

  std::cout << us << "\n";

}