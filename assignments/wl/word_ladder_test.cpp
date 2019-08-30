/*

== Explanation and rational of testing ==
******************************************
Important Note:
A assumption: All inputs words are valid
so they are : equal length, valid word
******************************************

 so this test file, will use as much as possible valid input words and special inputs words,
 to test the correctness of all the functions.(coverage all possible input words as much as I can)

===== short-cut for each test case: (for more explanations, go down to each test case.)
 - 1st: test the correctness of BFS by a random sample set of input words
 - 2nd: test the correctness of BFS for special edge case
 - 3rd: test IsPrune()
 - 4nd: test Dictionary()
 - 5nd: test MarkVisited()
 - 6nd: test NumOfCharDiff()
 - 7nd: test PossibleWord()

*/

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"
#include "catch.h"

// support functions
// support function to get correct results for test.cpp from data.txt
std::vector<std::vector<std::string>> GetCorrectResult(const std::string& s_word) {
  std::vector<std::vector<std::string>> results;
  std::ifstream f{"assignments/wl/data.txt"};

  std::string start = "#" + s_word + "_start";
  std::string end = "#" + s_word + "_end";

  if (!f) {
    std::cerr << "Failed to open file\n";
  }

  std::string line;
  bool found = false;

  // read the correct solution date set
  while (getline(f, line, '\n')) {
    if (found) {
      if (line.find(end) != std::string::npos) {
        f.close();
        break;
      }
      // if no ladder found, return a empty results
      if (line.find("No ladder found.") != std::string::npos) {
        return results;
      }
      // put into results
      std::istringstream input{line};
      std::string word;

      // add all paths to correct results
      std::vector<std::string> path;
      while (input >> word) {
        path.push_back(word);
      }
      results.push_back(path);
    }

    if (line.find(start) != std::string::npos) {
      found = true;
    } else {
      continue;
    }
  }

  if (f.bad()) {
    std::cerr << "I/O error while reading\n";
  }

  return results;
}

/* 1st test case: test the correctness for BFS()
 * By the limitation we cant call ./reference_solution in .cpp file. I manually create a
 * data.txt file that store all the expected output.
 * and I randomly select a sample set of input words, their length are between 2 - 11;
 *
 * by randomly select a data sample to test the correctness for BFS(),
 * with the random sample in statistic, we hopefully can guarantee the correctness of BFS
 * for all the possible input words.
 */
SCENARIO("Testing my BFS algorithm with word ladder for solutions correctness") {
  GIVEN("A lexicon dictionary") {
    auto word_list = GetLexicon("assignments/wl/words.txt");

    // 1st test case: con -> cat
    WHEN("1st case: con -> cat") {
      std::string s_word = "con";
      std::string d_word = "cat";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for con -> cat") {
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 2nd case: work->play
    WHEN("2nd case: work -> play") {
      // init value for testing
      std::string s_word = "work";
      std::string d_word = "play";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for work -> play") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 3rd case: code -> data
    WHEN("3rd case: code -> data") {
      // init value for testing
      std::string s_word = "code";
      std::string d_word = "data";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for code -> data") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 4th case: awake -> sleep
    WHEN("4th case: awake -> sleep") {
      // init value for testing
      std::string s_word = "awake";
      std::string d_word = "sleep";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for awake -> sleep") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 5th case: go -> if
    WHEN("5th case: go -> if") {
      // init value for testing
      std::string s_word = "go";
      std::string d_word = "if";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for go -> if") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 6th case: chi -> ego
    WHEN("6th case: chi -> ego") {
      // init value for testing
      std::string s_word = "chi";
      std::string d_word = "ego";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for chi -> ego") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 7th case: airplane -> tricycle
    WHEN("7th case: airplane -> tricycle") {
      // init value for testing
      std::string s_word = "airplane";
      std::string d_word = "tricycle";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() == 0);

      THEN("Searching the solution, and compare to the correct results for airplane -> tricycle") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 8th case: atom -> unau
    WHEN("8th case: atom -> unau") {
      // init value for testing
      std::string s_word = "atom";
      std::string d_word = "unau";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for atom -> unau") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 9th case: decanting -> derailing
    WHEN("9th case: decanting -> derailing") {
      // init value for testing
      std::string s_word = "decanting";
      std::string d_word = "derailing";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN(
          "Searching the solution, and compare to the correct results for decanting -> derailing") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }

    // 10th case: blistering -> swithering
    WHEN("10th case: blistering -> swithering") {
      // init value for testing
      std::string s_word = "blistering";
      std::string d_word = "swithering";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Searching the solution, and compare to the correct results for blistering -> "
           "swithering") {
        // geting my results
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }
  }
}

/*
 * 2nd case: edge case: s_word == d_word
 */

SCENARIO("Testing my BFS algorithm correctness for those edge case") {
  GIVEN("A lexicon dictionary") {
    auto word_list = GetLexicon("assignments/wl/words.txt");

    // 1st case. if the start_word == end_word
    WHEN("special case1: start_word == end_word:  triangles -> triangles") {
      // init value for testing
      std::string s_word = "triangles";
      std::string d_word = "triangles";

      // get lexicon dictionary and correct results
      auto lexicon = Dictionary(word_list, s_word);
      auto corr_results = GetCorrectResult(s_word);
      CHECK(corr_results.size() > 0);

      THEN("Running my algorithm for triangles -> triangles to check correct or not") {
        auto results = BFS2(s_word, d_word, lexicon);
        std::sort(results.begin(), results.end(), ResultsCompare());

        // checking get correct number of results
        REQUIRE(results.size() == corr_results.size());

        // change my results to the type vector<vector<string>>
        // so easy to check
        std::vector<std::vector<std::string>> filtred_results;
        for (auto result = results.begin(); result != results.end(); ++result) {
          std::vector<std::string> path;

          // filter the path to a  filtered result
          for (const auto& letter : *result) {
            path.push_back(letter.first);
          }

          filtred_results.push_back(path);
        }

        REQUIRE(filtred_results == corr_results);
      }
    }
  }
}

// 3rd test case -> to check the correctness of IsPrune() function
// so if the s_word have less than n-1 chars that are same as d_word, we will prune,
// otherwise, not prune.  To check this, we set d_word as 'play'. and following 4 sub-test
// 1.ploy == not prune. 2.play == not prune 3.plat == prune 4. pork == prune
SCENARIO("Testing IsPrune() function, by given s_word and d_word") {
  GIVEN("Given a  destination word -> d_word, say length of d_word is n") {
    std::string d_word{"play"};

    WHEN("s_word have n-1 chars are same as d_word") {
      std::string s_word{"ploy"};

      THEN("This should return false, for not prune") { REQUIRE(IsPrune(s_word, d_word) == false); }
    }

    WHEN("s_word == d_word") {
      std::string s_word{"play"};

      THEN("return false") { REQUIRE(IsPrune(s_word, d_word) == false); }
    }

    // for all the number of same char < n-1
    // for the following sub - test
    WHEN("s_word have 2 char are same as d_word") {
      std::string s_word{"plot"};

      THEN("return true, for prune") { REQUIRE(IsPrune(s_word, d_word) == true); }
    }

    WHEN("s_word have only 1 char are same as d_Word") {
      std::string s_word{"pork"};

      THEN("return true, for prune") { REQUIRE(IsPrune(s_word, d_word) == true); }
    }
  }
}

// 4th test case: test Dictionary()
// randomly select the length of input words
// by random sample, we should guarantee this function works for all length.
// (since there are too many length .... Forgive me)
// How to check:
// check my_lexicon has all the words have the length == given length
SCENARIO("Testing Dictionary() function") {
  GIVEN("A old dictionary ") {
    std::unordered_set<std::string> word_list{"aaaa", "bbbb", "cbbbb", "ddddd", "eeeee", "f"};

    WHEN("input words have length 4") {
      std::string word{"play"};

      THEN("we should able to get a new lexicon dictionary that all the words have length 4") {
        auto lexicon = Dictionary(word_list, word);
        // so only 2 two have length 4
        REQUIRE(lexicon.size() == 2);

        for (const auto& letter : lexicon) {
          REQUIRE(letter.size() == 4);
        }
      }
    }

    WHEN("input words have length 5") {
      std::string word{"awake"};

      THEN("we should able to get a new lexicon dictionary that all the words have length 5") {
        auto lexicon = Dictionary(word_list, word);

        REQUIRE(lexicon.size() == 3);
        for (const auto& letter : lexicon) {
          REQUIRE(letter.size() == 5);
        }
      }
    }
  }
}

// 5th test case: for MarkVisited()
// so if we use this function to mark visited
// the lexicon dictionary will erase that word
// since my algorithm is need auto fixed size lexicon dictionary
// so for the test case, we just assume the size is 4!!
// How to check:
// call the function to mark visited, then find if the dictionary erase the word or not.
SCENARIO("Testing MarkVisited(). it will mark visited for all the elements in the depth") {
  GIVEN("a lexicon that contain all length are 4 words") {
    auto word_list = GetLexicon("assignments/wl/words.txt");

    WHEN("in this depth, we only visited 1 element") {
      std::unordered_set<std::string> level_visited{"play"};
      auto lexicon = Dictionary(word_list, "play");

      THEN("we wont find 'play' after we mark it visited!") {
        // we can find them from lexicon before marking
        for (const auto& word : level_visited) {
          REQUIRE(lexicon.find(word) != lexicon.end());
        }

        MarkVisited(level_visited, lexicon);

        REQUIRE(lexicon.find("play") == lexicon.end());
      }
    }

    WHEN("in this depth, we visited more than 1 elements") {
      std::unordered_set<std::string> level_visited{"play", "pork", "work"};
      auto lexicon = Dictionary(word_list, "play");

      THEN("we wont find them after we mark it visited!") {
        // we can find them from lexicon before marking
        for (const auto& word : level_visited) {
          REQUIRE(lexicon.find(word) != lexicon.end());
        }

        MarkVisited(level_visited, lexicon);

        for (const auto& word : level_visited) {
          REQUIRE(lexicon.find(word) == lexicon.end());
        }
      }
    }

    WHEN("in this depth, we visited 0 element") {
      std::unordered_set<std::string> level_visited;
      auto lexicon = Dictionary(word_list, "play");
      auto old_size = lexicon.size();

      THEN("the size of lexion should stay the same") {
        MarkVisited(level_visited, lexicon);

        REQUIRE(old_size == lexicon.size());
      }
    }
  }
}

// 6th case: Testing NumberOfDiffChar()
// this function is used for find out how many char are the same for two given words.
// How to check:
// compare the return value of NumberOfDiffChar() == given_size
SCENARIO("Testing NumberOfDiffChar..") {
  GIVEN("Given a d_word") {
    std::string d_word{"play"};

    WHEN("when 0 char are same") {
      std::string s_word{"work"};

      THEN("should return 0") { REQUIRE(NumberOfDiffChar(s_word, d_word) == 0); }
    }

    WHEN("when 1 char are same") {
      std::string s_word{"pork"};

      THEN("should return 1") { REQUIRE(NumberOfDiffChar(s_word, d_word) == 1); }
    }

    WHEN("when s_word == d_word ") {
      std::string s_word{"play"};

      THEN("return 4") { REQUIRE(NumberOfDiffChar(s_word, d_word) == 4); }
    }
  }
}

// 7th test case: Test PossibleWord()
// this function is used to find all the words from a lexicon that have 1 char different from
// the given word. and possible words will be stored in a priority queue by order
// so we will like to test all the functionality work correctly
// Using my own lexicon to check by creating it manually.(may not be valid word from traditional
// lexicon);  limitation by complex data structure.  is more easier to check it during debug.
// How to check:
// get the return value, and we set the correct value by myself, then compare them
SCENARIO("Testing PossibleWord()") {
  GIVEN("Given a lexicon dictionary, a d_word, a searching map") {
    std::string d_word{"play"};
    std::unordered_set<std::string> lexicon{"worn", "baby", "pork", "fill"};
    PossWordMap search_map;

    WHEN("s_word had already search, we will use the searching map to return a result") {
      WordType result = std::make_pair("if", std::array{-1, -1});
      std::priority_queue<WordType, std::vector<WordType>, CustomCompare> temp;
      temp.push(result);
      search_map["go"] = temp;

      THEN("return should be equal to the result in search_map") {
        WordType s_word = std::make_pair("go", std::array{-1, -1});
        auto my_result = PossibleWord(s_word, d_word, lexicon, search_map);

        REQUIRE(my_result.size() == temp.size());

        while (!my_result.empty() && !temp.empty()) {
          auto curr = my_result.top();
          my_result.pop();

          auto correct = temp.top();
          temp.pop();

          REQUIRE(curr == correct);
        }
      }
    }

    WHEN("To find all possible word from s_word in lexicon, and check the order in return queue") {
      std::vector<std::string> correct{"pork", "worn"};

      THEN("Compare with expect output") {
        WordType s_word = std::make_pair("work", std::array{-1, -1});
        auto my_result = PossibleWord(s_word, d_word, lexicon, search_map);

        REQUIRE(my_result.size() == correct.size());

        auto iter = correct.begin();
        while (!my_result.empty()) {
          auto curr = my_result.top();
          my_result.pop();

          // compare the word are same, if they are in same order.
          REQUIRE(curr.first == *iter);
          ++iter;
        }
      }
    }
  }
}
