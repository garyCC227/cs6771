/*Linchen Chen  14/06/2019
 *
 * algorithm explanning - word ladder
 *
 * Given: start word, destination word,
 *        lexicon dictionary (same length as start word and destination word)
 *
 * ---- my algorithm breif code:
 * while(queue is not empty)
 *     curr_path = queue.pop()
 *
 *     if depth > depth limit
 *          break
 *
 *     if solution found
 *          decide to prune this branch or not
 *
 *     find all possible words
 *     for each word in possible words:
 *          if(word == d_word)
 *              set depth limit
 *              add the path to result
 *              prune this branch
 *
 *          if(solution_not_found)
 *              put word into level visited
 *              create a new path for this word
 *              queue.push(new_path)
 *
 *
 *     in each end of depth
 *          make all the level visited word as visited in lexicon dictionary
 *          increase depth
 *
 *
 * ------ some optimisation method when finding the possible words
 *
 * 1. similar to killer heuristic. in each branch, we put the letter in an order.
 *      the order is number of char that letter is same as d_word
 * 2. word->ward->wmrd (suppose wmrd is valid word now)
 *  in ward, we dont want to change 'a' again, since word->ward, we change the char at position 2
 *  so from ward->wmrd, we dont want to change the char at position 2.
 *  in summary, dont change the char in the position that its parent letter already changed.
 *
 */

#include <algorithm>
#include <iostream>
#include <string>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::string s_word, d_word;  // start word, destination word

  // get start word and dest word
  std::cout << "Enter start word (RETURN to quit): ";
  getline(std::cin, s_word);
  if (s_word == "")
    return 0;  // quit if enter return or no a valid word

  std::cout << "Enter destination word: ";
  getline(std::cin, d_word);
  if (d_word == "")
    return 0;

  if (s_word.size() != d_word.size())
    return 0;

  auto lexicon2 = Dictionary(lexicon, s_word);

  // algorithm starting running
  auto results = BFS2(s_word, d_word, lexicon2);

  // print solutions
  if (!results.empty()) {
    std::cout << "Found ladder: ";
    std::sort(results.begin(), results.end(), ResultsCompare());

    for (const auto& path : results) {
      for (const auto& path_word : path) {
        std::cout << path_word.first << " ";
      }
      std::cout << '\n';
    }
  } else {
    std::cout << "No ladder found.\n";
  }

  return 0;
}
