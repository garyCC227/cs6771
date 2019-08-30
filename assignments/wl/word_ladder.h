#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// modify
#define MAX_DEPTH 100000000;

// d_word = destination word
// word_type  = (word string, [previous_position_for_change_char_for_the_current_word, how many char
// are same as d_word])
using WordType = std::pair<std::string, std::array<int, 2>>;
using Path = std::vector<WordType>;  // path is just list of word pair

struct CustomCompare {  // using for priority queue
  bool operator()(const WordType& lhs, const WordType& rhs) {
    return lhs.second[1] < rhs.second[1];
  }
};

struct ResultsCompare {  // use to sort the final solutions
  bool operator()(const Path& lhs, const Path& rhs) {
    auto r_iterator = rhs.begin();
    for (auto pos = lhs.begin(); pos != lhs.end(); ++pos) {
      if (pos->first == r_iterator->first) {
        ++r_iterator;
        continue;
      }

      return pos->first < r_iterator->first;
    }
    return false;
  }
};

// (word, all the possible words it can change to)
using PossWordMap =
    std::unordered_map<std::string,
                       std::priority_queue<WordType, std::vector<WordType>, CustomCompare>>;

std::vector<Path>
BFS2(const std::string& s_word, const std::string& d_word, std::unordered_set<std::string> lexicon);
std::unordered_set<std::string> Dictionary(std::unordered_set<std::string> lexicon,
                                           std::string word);
bool IsPrune(std::string curr_word, std::string d_word);
void MarkVisited(std::unordered_set<std::string>& lvl_visited,
                 std::unordered_set<std::string>& lexicon);
int NumberOfDiffChar(const std::string& s_word, const std::string& d_word);
std::priority_queue<WordType, std::vector<WordType>, CustomCompare>
PossibleWord(WordType& word,
             std::string d_word,
             std::unordered_set<std::string> lexicon,
             PossWordMap& possible_word_map);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
