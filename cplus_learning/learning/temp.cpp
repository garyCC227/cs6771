/*

== Explanation and rational of testing ==

Explain and justify how you approached testing, the degree
to which you're certain you have covered all possibilities,
and why you think your tests are that thorough.

*/

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"
#include "catch.h"


/*
* For all the test cases,
* in my main(), I put the error checker there for invalid words,
* so in this test file, assume all the input are valid
*/
SCENARIO("Testing BFS algorithm with word ladder"){
    GIVEN("A lexicon dictionary"){
        auto word_list = GetLexicon("assignments/wl/words.txt");
        /*
        * from all the sub-case in this test case.
        * they all test for correctness
        * with compare to reference solution output
        * with the range of the length of words is 2 - 11
        */

        //1st test case: con -> cat
        WHEN("1st case: con -> cat"){

            std::string s_word = "con";
            std::string d_word = "cat";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for con -> cat"){
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);

            }
        }

        //2nd case: work->play
        WHEN("2nd case: work -> play"){
            //init value for testing
            std::string s_word = "work";
            std::string d_word = "play";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for work -> play"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //3rd case: code -> data
        WHEN("3rd case: code -> data"){
            //init value for testing
            std::string s_word = "code";
            std::string d_word = "data";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for code -> data"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //4th case: awake -> sleep
        WHEN("4th case: awake -> sleep"){
            //init value for testing
            std::string s_word = "awake";
            std::string d_word = "sleep";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for awake -> sleep"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //5th case: go -> if
        WHEN("5th case: go -> if"){
            //init value for testing
            std::string s_word = "go";
            std::string d_word = "if";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for go -> if"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }


        //6th case: chi -> ego
        WHEN("6th case: chi -> ego"){
            //init value for testing
            std::string s_word = "chi";
            std::string d_word = "ego";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for chi -> ego"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //7th case: hylon -> iller
        WHEN("7th case: hylon -> iller"){
            //init value for testing
            std::string s_word = "hylon";
            std::string d_word = "iller";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for hylon -> iller"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //8th case: atom -> unau
        WHEN("8th case: atom -> unau"){
            //init value for testing
            std::string s_word = "atom";
            std::string d_word = "unau";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for atom -> unau"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //9th case: decanting -> derailing
        WHEN("9th case: decanting -> derailing"){
            //init value for testing
            std::string s_word = "decanting";
            std::string d_word = "derailing";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for decanting -> derailing"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

        //10th case: blistering -> swithering
        WHEN("10th case: blistering -> swithering"){
            //init value for testing
            std::string s_word = "blistering";
            std::string d_word = "swithering";

            //get lexicon dictionary and correct results
            auto lexicon = Dictionary(word_list, s_word);
            auto corr_results = GetCorrectResult(s_word);

            THEN("Searching the solution, and compare to the correct results for blistering -> swithering"){
                //geting my results
                auto results = BFS2(s_word, d_word, lexicon);
                //std::sort(results.begin(),results.end(), ResultsCompare());

                //checking get correct number of results
                REQUIRE(results.size() == corr_results.size());

                //change my results to the type vector<vector<string>>
                //so easy to check
                std::vector<std::vector<std::string>> filtred_results;
                for(auto result = results.begin(); result != results.end(); ++result){

                    std::vector<std::string> path;

                    //filter the path to a  filtered result
                    for(const auto& letter: *result){
                        path.push_back(letter.first);
                    }

                    filtred_results.push_back(path);
                }

                REQUIRE(filtred_results == corr_results);
            }
        }

    }
}
