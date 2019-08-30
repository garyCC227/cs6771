#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>



struct Custom{
    bool operator()(const std::string& word){
        return (word.size() == 4);
    }
};


int main(){
    // std::vector<std::string> lexicon {"aaaa","bbbb","ccc"};
    // std::vector<std::string> copy;
    // std::unordered_set<std::string> lexicon2{"aaaa", "bbb", "cccc"};

    // std::remove_if(lexicon.begin(), lexicon.end(),Custom());
    // std::remove_if(lexicon2.begin(), lexicon2.end(), Custom());

    // for(const auto& letter: lexicon2){
    //     std::cout << letter;
    // }

    std::istringstream str{"string hello world"};
    std::istream_iterator<std::string> input{str};

    std::string word;
    std::cout << *(++input) << '\n';

    return 1;
}
