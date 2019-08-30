#include "assignments/wl/word_ladder.h"

// curr word must have n char that are same as d_word, otherwise we dont need to search its next
// level
// n = d_word.size() - 1;
bool IsPrune(std::string curr_word, std::string d_word) {
  int cout = 0;
  bool prune = false;
  for (std::string::size_type pos = 0; pos < d_word.size(); ++pos) {
    if (d_word[pos] != curr_word[pos]) {
      cout++;
    }
    if (cout == 2) {
      prune = true;
      break;
    }
  }

  return prune;
}

/*
 * extract same length words from the original lexicon to create my own lexicon dictionary
 * same length as s_word and d_word
 */
std::unordered_set<std::string> Dictionary(std::unordered_set<std::string> lexicon,
                                           std::string word) {
  auto length = word.size();

  std::unordered_set<std::string> dictionary;
  for (auto letter = lexicon.begin(); letter != lexicon.end(); ++letter) {
    if (letter->size() == length) {
      dictionary.insert(*letter);
    }
  }

  return dictionary;
}

std::vector<Path> BFS2(const std::string& s_word,
                       const std::string& d_word,
                       std::unordered_set<std::string> lexicon) {
  std::queue<Path> path_q;
  std::vector<Path> results_q;
  PossWordMap possible_word_map;

  // edge case: if the s_word == d_word already;
  if (s_word == d_word) {
    auto start_word = std::make_pair(s_word, std::array<int, 2>{-1, -1});
    Path solution{start_word, start_word};

    results_q.push_back(solution);
    return results_q;
  }

  // init value to search
  int start_diff =
      NumberOfDiffChar(s_word, d_word);  // number of diff char between s_word and d_word
  auto first_word = std::make_pair(s_word, std::array<int, 2>{-1, start_diff});
  Path root{first_word}, curr_path;
  path_q.push(root);

  int max_depth = MAX_DEPTH;
  int depth_count = 1;
  int curr_depth = 1;
  bool solution_found = false;  // we found a shortest path or not

  std::unordered_set<std::string> level_visited;  // what words we visited in this whole level
  level_visited.insert(s_word);                   // root level ->in level one we visited s_word

  // start searching
  while (!path_q.empty()) {
    curr_path = path_q.front();
    path_q.pop();

    // if curr_depth == max_depth. we find all the shortest path. EXIT searching!
    if (curr_depth >= max_depth) {
      break;
    }

    // reduce depth counter
    if (depth_count == 0) {
      depth_count = path_q.size();
    } else {
      depth_count--;
    }

    std::string curr_word = curr_path.back().first;  // get the last word string of current path

    // if solution is found
    // we can decide to prune this branch or not
    // if the last node of this branch, the curr_word does not have d_word.size()-1 chars that are
    // same as d_word we can prune, since change one letter will not find the solution
    if (solution_found) {
      if (IsPrune(curr_word, d_word)) {
        // if after pop the curr_path, the depth_count is 0, mean the depth increase 1
        if (depth_count == 0) {
          MarkVisited(level_visited, lexicon);
          lexicon.insert(d_word);
          curr_depth += 1;
        }
        continue;
      }
    }

    // find all the possible word, that change one char from curr_word
    auto possible_words = PossibleWord(curr_path.back(), d_word, lexicon, possible_word_map);

    if (possible_words.size() != 0) {
      while (!possible_words.empty()) {
        auto word = possible_words.top();
        possible_words.pop();

        // check if is dest word
        // if in this branch find the dest word, prune this branch
        if (word.first == d_word) {
          // in first time we find a solution
          // once we reach here, we find the shortest path, so we need to update the max_depth
          // so we set a depth limit for this searching
          if (curr_depth + 1 < max_depth) {
            max_depth = curr_depth + 1;
            solution_found = true;
          }

          // add the result_q
          curr_path.push_back(std::make_pair(d_word, std::array<int, 2>{-1, -1}));
          results_q.push_back(curr_path);

          // if after pop the curr_path, the depth_count is 0, mean the depth increase 1
          if (depth_count == 0) {
            MarkVisited(level_visited, lexicon);
            lexicon.insert(d_word);
            curr_depth += 1;
          }

          // prune this branch, since we already found a solution in this branch
          break;
        }

        // once we found one solution, for other branch, we just need to check rest of the words
        // in the same depth that is == d_word
        // we the above "if" statement will do this for us.
        // and we dont need to create a new path
        if (curr_depth + 1 < max_depth) {
          // create a new path for this word
          // and set this word as visited
          Path new_path(curr_path);
          new_path.push_back(word);
          level_visited.insert(word.first);

          // push new_path into path_q
          path_q.push(new_path);
        }
      }
    }

    // if after pop the curr_path, the depth_count is 0, mean the depth increase 1
    if (depth_count == 0) {
      MarkVisited(level_visited, lexicon);
      lexicon.insert(d_word);
      curr_depth += 1;
    }
  }

  return results_q;
}
/*
 * to find all the possible words from all the letter in lexicon
 * optimisation method:
 * 1. similar to killer heuristic. in each branch, we put the letter in an order.
 *      the order is number of char that letter is same as d_word
 * 2. word->ward->wmrd (suppose wmrd is valid word now)
 *  in ward, we dont want to change 'a' again, since word->ward, we change the char at position 2
 *  so from ward->wmrd, we dont want to change the char at position 2.
 *  in summary, dont change the char in the position that its parent letter already changed.
 */
std::priority_queue<WordType, std::vector<WordType>, CustomCompare>
PossibleWord(WordType& word,
             std::string d_word,
             std::unordered_set<std::string> lexicon,
             PossWordMap& possible_word_map) {
  std::string& curr_word = word.first;
  // this word we already search
  if (possible_word_map.find(curr_word) != possible_word_map.end()) {
    return possible_word_map[curr_word];
  } else {
    std::priority_queue<WordType, std::vector<WordType>, CustomCompare> results;
    int cout, same_char, no_change_index = word.second[0];
    for (auto letter = lexicon.begin(); letter != lexicon.end(); ++letter) {
      cout = 0;
      int diff_position = -1;
      for (size_t i = 0; i < letter->size(); ++i) {
        if (letter->at(i) != curr_word[i]) {
          if (no_change_index == static_cast<int>(i)) {  // optimisation method 2
            cout = -1;
            break;
          }

          diff_position = i;
          ++cout;
        }

        if (cout > 1)
          break;
      }
      if (cout == 1) {
        same_char = 0;
        for (size_t i = 0; i < curr_word.size(); ++i) {  // optimisation method 1, by priority queue
          if (curr_word[i] == d_word[i]) {
            ++same_char;
          }
        }

        results.push(std::make_pair(*letter, std::array<int, 2>{diff_position, same_char}));
      }
    }

    possible_word_map[curr_word] = results;
    return results;
  }
}

// Another optimisation method
// after each level finished, and we enter next level
// we will mark all the visited words as visited
// by doing that, we just erase these words from lexicon
void MarkVisited(std::unordered_set<std::string>& lvl_visited,
                 std::unordered_set<std::string>& lexicon) {
  for (auto& letter : lvl_visited) {
    lexicon.erase(letter);
  }

  lvl_visited.clear();
}

// how many char are the same with two words
int NumberOfDiffChar(const std::string& s_word, const std::string& d_word) {
  int cout = 0;
  for (size_t i = 0; i < s_word.size(); ++i) {
    if (s_word[i] == d_word[i]) {
      ++cout;
    }
  }
  return cout;
}
