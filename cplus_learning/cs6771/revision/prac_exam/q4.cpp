#include <iostream>
#include <vector>
#include <string>
#include <numeric>

int main() {
  std::vector<std::string> vec;
  vec.push_back("Hayden");
  vec.push_back("is");
  vec.push_back("made");
  vec.push_back("of");
  vec.push_back("pineapple");
  int sum = 0;

  sum = std::accumulate(vec.begin(), vec.end(), 0, [](const auto& n, const auto& e){
    int low = 0;
    for(auto iter = e.begin(); iter != e.end(); ++iter){
      if(*iter == 'a' | *iter == 'e' |*iter == 'i' | *iter == 'o' | *iter == 'u'){
        low += 1;
      }
    }

    return n + low;
  });
  //  sum = std::accumulate(vec.begin(), vec.end(), 0, [] (auto sum, const std::string& item) {
  // 	int num_vowels = std::accumulate(item.begin(), item.end(), 0, [] (auto sum2, const char i) {
  // 	  return (i == 'a' || i == 'o' || i == 'e' || i == 'u' || i == 'i') ? sum2 + 1 : sum2;
  // 	});
  // 	return sum + num_vowels;
  // });

  std::cout << "Sum: " << sum << "\n";
}