/*

  == Explanation and rational of testing ==
    this test will have the coverage:
    1. function coverage: all the functions will be called in this test
    2. branch/ statement/ expression coverage:
        I will cover all the possible input as much as I can, so guarantee that
        all the statement/expression/if_else branch would be implemented(in this function).
            such as
            (1) type (int, double, double/int)
            (2) weired input(e.g. 0-dimesnion vector)
            (3) special input that will call the if_else branch (or others expression/ statement)
            (4) normal input
            e.t.c
    and with 1. and 2. , we hopefully we can cover all the situations, then we will compare the my
    output with the expected output. Finally, if all match, we could say all my functions work
 properly.

    - for const vector:
        we will test for any const vector will have valid const memeber function to call.
        but some of methods both have setter and getter, then I will only test for getter,
        since Clion will tell us setter cannot be use, since we have const vector object.

 -------------------------------------------------------------------------------------------
                        Table of Content For Each Test Case
                    (To see detail, go the corresponding test case section)
 -------------------------------------------------------------------------------------------
 1. default constructor         6. copy assignment                          11. *= operator
 2. constructor                 7. move assignment                          12. /= operator
 3. range constructor           8. subscript operator(getter and modifier)  13. std::vector type
 conversion
 4. copy constructor            9. += operator                              14. std::list type
 conversion
 5. move constructor           10. -= operator                              15. at() methods
 ============================================================================================
 16.GetNumDimensions()         20. != operator                              24. / operator
 17.GetEuclideanNorm()         21. + operator                               25. << operator
 18.CreateUnitVector()         22. - operator                               26. const vector
 19. == operator               23. * operator
*/

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

/*
 *  1. Test default constructor. How to test:
 *  after initialized the vector with default constructor,
 *  check dimension and magnitudes
 */
SCENARIO("Testing default constructor") {
  GIVEN("We will initialized a vector by all the possible ways by using the default constructor") {
    WHEN("when `EuclidenVector vec` -> then dimension should be 1, magnitudes[0] is 0") {
      EuclideanVector vec;

      THEN("then dimension should be 1, magnitudes[0] is 0") {
        REQUIRE(vec.GetNumDimensions() == 1);
        REQUIRE(vec[0] == 0);
      }
    }

    WHEN("when we initialized a 0-dimension vector ") {
      EuclideanVector vec{0};

      THEN("-> dimension should be 0, and throw for maginitudes[0]") {
        REQUIRE(vec.GetNumDimensions() == 0);
        // if index 0 is not valid, we can say the whole vector is empty
        REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
      }
    }

    WHEN("when initialized with some positive int, such d = 10 ") {
      EuclideanVector vec{10};

      THEN("-> dimension = 10 and magnitudes are all 0") {
        REQUIRE(vec.GetNumDimensions() == 10);
        for (int i = 0; i < 10; ++i) {
          REQUIRE(vec[i] == 0);
        }
      }
    }

    WHEN("when we initialized with some int type variable instead of numeric value") {
      int d{5};
      EuclideanVector vec{d};

      THEN("we should get the same result") {
        REQUIRE(vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == 0);
        }
      }
    }
  }
}

/*
 * 2. Test the constructor (int, double)
 *  -  check dimension and magnitudes
 */
SCENARIO("Testing constructor(d = int, m = double)") {
  GIVEN("Given all possible test cases") {
    WHEN("when we initialized for a 0-dimension vector") {
      EuclideanVector vec{0, 5.5};

      THEN("-> dimension = 0, magnitudes cannot access (throw)") {
        REQUIRE(vec.GetNumDimensions() == 0);
        // if index 0 is not valid, we can say the whole vector is empty
        REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
      }
    }

    WHEN("(Normal case) when we initialized with d = any positive value, m = any double value ") {
      EuclideanVector vec{5, 5.5};

      THEN("check with expected output") {
        REQUIRE(vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == 5.5);
        }
      }
    }

    WHEN("when we initialized with variables, d = int type variable, m = double type variable ") {
      int d{5};
      double m{5.5};
      EuclideanVector vec{d, m};

      THEN("Check expected output") {
        REQUIRE(vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == 5.5);
        }
      }
    }
  }
}

/*
 * 3. Test range constructor. with given a pair of vector iterator.
 *  -   check dimension and magnitudes
 */
SCENARIO("Testing range constructor") {
  GIVEN("Given all possible test cases for this constructor") {
    WHEN("when we initialized with a empty std::vector ") {
      std::vector<double> temp;
      EuclideanVector vec{temp.begin(), temp.end()};

      THEN("-> we should get a 0-dimension Euclidean vector") {
        REQUIRE(vec.GetNumDimensions() == 0);
        // if index 0 is not valid, we can say the whole vector is empty
        REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
      }
    }

    WHEN("(Normal case) initialized with some normal vector ") {
      std::vector<double> temp{1, 2, 3, 4, 5, 6};
      EuclideanVector vec{temp.begin(), temp.end()};

      THEN(
          "-> dimension = std::vector.size(), magnitudes should be same as the std::vector value") {
        REQUIRE(vec.GetNumDimensions() == static_cast<int>(temp.size()));
        for (int i = 0; i < vec.GetNumDimensions(); ++i) {
          REQUIRE(vec[i] == temp[i]);
        }
      }
    }

    WHEN("(Normal case) initialized with some normal vector") {
      std::vector<double> temp{-1, -2, -3, -4, -5, 6};
      EuclideanVector vec{temp.begin(), temp.end()};

      THEN(
          "-> dimension = std::vector.size(), magnitudes should be same as the std::vector value") {
        REQUIRE(vec.GetNumDimensions() == static_cast<int>(temp.size()));
        for (int i = 0; i < vec.GetNumDimensions(); ++i) {
          REQUIRE(vec[i] == temp[i]);
        }
      }
    }
  }
}

/*
 * 4. Test copy constructor
 *  -   compare old and new Euclidean vector
 */
SCENARIO("Testing copy constructor") {
  GIVEN("Given a old_vec") {
    EuclideanVector vec{5, 0.5};

    WHEN("we copy from the old_vec") {
      EuclideanVector new_vec{vec};
      THEN("we need to check if old == new??") { REQUIRE(vec == new_vec); }
    }
  }
}

/*
 * 5. Test move constructor
 *  -   check dimension and m
 */
SCENARIO("Testing move constructor") {
  GIVEN("given a old_vec and a copy of it") {
    EuclideanVector old_vec{5, 5.5};
    EuclideanVector copy_old_vec{old_vec};

    WHEN("so we move old_vec to the new one -> ") {
      EuclideanVector new_vec{std::move(old_vec)};

      THEN("check if new_one == the copy of old_one? and check did we set old_one to "
           "nothing?(0-dimesnion vector)") {
        REQUIRE(new_vec == copy_old_vec);

        // so we will set the old one to a 0-dimension vector
        // check old vector to default or not?
        REQUIRE(old_vec.GetNumDimensions() == 0);
        // if index 0 is not valid, we can say the whole vector is empty
        REQUIRE_THROWS_WITH(old_vec.at(0), "Index 0 is not valid for this EuclideanVector object");
      }
    }
  }
}

/*
 * 6. Test: copy assignment
 * -    check dimension and m
 */
SCENARIO("Testing copy assignment") {
  GIVEN("Given a old vector") {
    EuclideanVector old_vec{5, 5.5};

    WHEN("when we do self copy -> we just want to check if that works?") {
      REQUIRE_NOTHROW(old_vec = old_vec);
    }

    WHEN("copy assign with two different dimensions vectors") {
      EuclideanVector new_vec{1, 4.0};
      REQUIRE(new_vec.GetNumDimensions() == 1);  // check d and m before assignment
      REQUIRE(new_vec[0] == 4);

      new_vec = old_vec;
      THEN("-> we care the dimension and magnitudes of new_vec before and after assignment") {
        REQUIRE(new_vec.GetNumDimensions() == 5);  // check d and m after assignment
        REQUIRE(new_vec == old_vec);
      }
    }
  }
}

/*
 * 7. Test: move assignment
 * - check dimension and m with new_vec and old_vec
 */
SCENARIO("Testing move assignment") {
  GIVEN("Given a old_vec") {
    EuclideanVector old_vec{5, 5.5};

    WHEN("check if self assignment works") { REQUIRE_NOTHROW(old_vec = old_vec); }

    WHEN("move assignment with two different dimensions vectors ") {
      EuclideanVector new_vec{1, 4.0};
      REQUIRE(new_vec.GetNumDimensions() == 1);
      REQUIRE(new_vec[0] == 4);

      THEN("-> check both dimensions and magnitudes as expected?") {
        new_vec = std::move(old_vec);
        REQUIRE(new_vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(new_vec[i] == 5.5);
        }
        // check old_vec set back to default?
        REQUIRE(old_vec.GetNumDimensions() == 0);
        // check index 0, guarantee its magnitudes set back to default
        REQUIRE_THROWS_WITH(old_vec.at(0), "Index 0 is not valid for this EuclideanVector object");
      }
    }
  }
}

/*
 * 8. Test: subscript operator (getter and setter)
 *  -   check getter and setter work after :
 *      1. initialized
 *      2. reassign by another vector
 *      3. (things didnt do: not-valid index)
 *          since we use `assert` instead of throw.
 */
SCENARIO("Testing subscript operator") {
  GIVEN("Given a list of sub-test cases ") {
    WHEN("when we initialized a vector ") {
      EuclideanVector vec{5};

      THEN("-> getter and setter should works properly") {
        // test getter
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == 0);
        }

        // test setter
        for (int i = 0; i < 5; ++i) {
          REQUIRE_NOTHROW(vec[i] = 5);
        }
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == 5);
        }
      }
    }

    WHEN("after using assignment") {
      EuclideanVector vec{5};
      EuclideanVector old_vec{4, 5.5};
      vec = old_vec;

      THEN("-> getter and setter should works properly ") {
        // test getter
        for (int i = 0; i < 4; ++i) {
          REQUIRE(vec[i] == 5.5);
        }

        // test setter
        for (int i = 0; i < 4; ++i) {
          REQUIRE_NOTHROW(vec[i] = 5);
        }
        for (int i = 0; i < 4; ++i) {
          REQUIRE(vec[i] == 5);
        }
      }
    }
  }
}

/*
 * 9. test += operator: test cases
 *  1. dimensions no match
 *  2. normal += operator
 *  3. (Things not do, but CLion will cover it): += operation on `not a EuclideanVector object`
 */
SCENARIO("Testing += operator") {
  GIVEN("a vector to +=") {
    EuclideanVector vec{5, 5.5};

    WHEN("when dimensions is not match") {
      EuclideanVector bad_vec{4, 4.0};

      THEN("we should get a error message") {
        REQUIRE_THROWS_WITH(vec += bad_vec, "Dimensions of LHS(5) and RHS(4) do not match");
      }
    }

    WHEN("normal += operation") {
      std::vector<double> input{1, 2, 3, 4, 5};
      EuclideanVector good_vec{input.begin(), input.end()};
      vec += good_vec;

      THEN("the magnitudes of both vectors should have the expected value") {
        // require good_vec not change
        REQUIRE(good_vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(good_vec[i] == input[i]);
        }

        // require vec will be expected
        REQUIRE(vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == (5.5 + input[i]));
        }
      }
    }
  }
}

/*
 * 10. test -= operator
 *      1. dimensions no match
 *      2. normal += operator
 *      3. (Things not do, but CLion will cover it): -= operation on `not a EuclideanVector object`
 *      4. two 0-dimension vectors
 */
SCENARIO("Testing -= operator") {
  GIVEN("a vector to -=") {
    EuclideanVector vec{5, 5.5};

    WHEN("when two vectors have different dimensions") {
      EuclideanVector bad_vec{4, 4.0};

      THEN("-> throw exception with the erro message") {
        REQUIRE_THROWS_WITH(vec -= bad_vec, "Dimensions of LHS(5) and RHS(4) do not match");
      }
    }

    WHEN("(normal case) -= operation with two normal vectors") {
      std::vector<double> input{1, 2, 3, 4, 5};
      EuclideanVector good_vec{input.begin(), input.end()};
      vec -= good_vec;

      THEN("the magnitudes of both vector should have the expected value") {
        // require good_vec not change
        REQUIRE(good_vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(good_vec[i] == input[i]);
        }

        // require vec will be expected
        REQUIRE(vec.GetNumDimensions() == 5);
        for (int i = 0; i < 5; ++i) {
          REQUIRE(vec[i] == (5.5 - input[i]));
        }
      }
    }

    WHEN("when -= operation on two 0-dimension vectors ") {
      EuclideanVector v1{0, 5.5};
      EuclideanVector v2{0};

      THEN("-> return a 0-dimension vector") {
        // all 0-dimension vector are same, so we just check v1 == output?
        REQUIRE(v1 == (v1 -= v2));
      }
    }
  }
}

/*
 * 11. Test *= operator:
 *  -   check expected output for input type is(since we have implicit type conversion, so )
 *      1. int
 *      2. double
 *      3. 0 dimensions vector
 */
SCENARIO("Testing *= operator") {
  GIVEN("Given a list of tests case") {
    WHEN("when *= with int type value ") {
      int b{2};
      EuclideanVector vec{4, 4.5};
      vec *= b;

      THEN("check the magnitudes with expected value") {
        REQUIRE(vec.GetNumDimensions() == 4);
        for (int i = 0; i < 4; ++i) {
          REQUIRE(vec[i] == (4.5 * (2.0)));
        }
      }
    }

    WHEN("when *= with double type value") {
      double b{2.5};
      EuclideanVector vec{4, 4.5};
      vec *= b;

      THEN("-> check with expected output for magnitudes") {
        REQUIRE(vec.GetNumDimensions() == 4);
        for (int i = 0; i < 4; ++i) {
          REQUIRE(vec[i] == (4.5 * 2.5));
        }
      }
    }

    WHEN("0-dimension vector *= any value") {
      double b{2.5};
      EuclideanVector v1{0, 4.4};

      THEN("-> return a 0-dimension vector") { REQUIRE(v1 == (v1 *= b)); }
    }
  }
}

/*
 * 12. Test /= operator:
 *  -   check expected output for input type is(since we have implicit type conversion, so )
 *      1. int
 *      2. double
 *      3. input is 0
 *      4. 0-dimension vector
 */
SCENARIO("Testing /= operator") {
  GIVEN("a list of tests case") {
    WHEN("when *= with int type value ") {
      int b{2};
      EuclideanVector vec{4, 4.5};
      vec /= b;

      THEN("-> check with expected output for magnitudes") {
        REQUIRE(vec.GetNumDimensions() == 4);
        for (int i = 0; i < 4; ++i) {
          REQUIRE(vec[i] == (4.5 / (2.0)));  // since we have implicit type conversion
        }
      }
    }

    WHEN("when *= with double type value ") {
      double b{2.5};
      EuclideanVector vec{4, 4.5};
      vec /= b;

      THEN("-> check with expected output with magnitudes") {
        REQUIRE(vec.GetNumDimensions() == 4);
        for (int i = 0; i < 4; ++i) {
          REQUIRE(vec[i] == (4.5 / 2.5));
        }
      }
    }

    WHEN("when /= with 0 ") {
      double b{0};
      EuclideanVector vec{4, 4.5};

      THEN("> throw exception") { REQUIRE_THROWS_WITH(vec /= b, "Invalid vector division by 0"); }
    }

    WHEN("0-dimension vector /= any value ") {
      EuclideanVector v1{0};

      THEN("-> return 0-dimension vector") { REQUIRE(v1 == (v1 /= 5.5)); }
    }
  }
}

/*
 * 13.Test : std::vector conversion operator
 *  -   just check if is expected output
 */
SCENARIO("Test std::vector<double> type conversion") {
  GIVEN("a std::vector we want to convert to, and a Euclidean vector have same value") {
    std::vector<double> correct_vec = {4, 5, 6, 7, 8, 1};
    EuclideanVector vec{correct_vec.begin(), correct_vec.end()};

    WHEN("Euclidean vector to std::vector<double>") {
      auto output = static_cast<std::vector<double>>(vec);

      THEN("-> check output ==  expected std::vector ?") { REQUIRE(output == correct_vec); }
    }
  }
}

/*
 * 13.Test : std::list conversion operator
 *  -   just check if is expected output
 */
SCENARIO("Test std::list<double> type conversion") {
  GIVEN("a std::list we want to convert to, and a Euclidean vector have same value") {
    std::list<double> correct_list = {4.5, 4.5, 4.5, 4.5, 4.5, 4.5};
    EuclideanVector vec{6, 4.5};
    REQUIRE(correct_list.size() == 6);

    WHEN("Euclidean vector to std::list<double>") {
      auto output = static_cast<std::list<double>>(vec);

      THEN("-> check output == expected std::list?") { REQUIRE(output == correct_list); }
    }
  }
}

/*
 * 14. test at() method. -> both getter and setter
 *      1. invalid index
 *      2. normal index
 *      3. index is double
 *
 */
SCENARIO("Test at() method") {
  GIVEN("given a vector ") {
    std::vector<double> temp{1, 2, 3, 4};
    EuclideanVector vec{temp.begin(), temp.end()};
    REQUIRE((temp.size() == 4 && vec.GetNumDimensions() == 4));

    WHEN("when index is invalid") {
      int index1{-1};
      int index2{4};

      THEN("-> throw exception for both getter and setter") {
        // for getter
        REQUIRE_THROWS_WITH(vec.at(index1),
                            "Index -1 is not valid for this EuclideanVector object");
        REQUIRE_THROWS_WITH(vec.at(index2), "Index 4 is not valid for this EuclideanVector object");
        // for setter
        REQUIRE_THROWS_WITH(vec.at(index1) = 1,
                            "Index -1 is not valid for this EuclideanVector object");
        REQUIRE_THROWS_WITH(vec.at(index2) = 2,
                            "Index 4 is not valid for this EuclideanVector object");
      }
    }

    WHEN("when valid index") {
      int index{2};
      REQUIRE(vec.at(index) == 3);

      THEN("-> check with expected value for magnitudes[index]") {
        // test setter
        EuclideanVector temp1{3};
        REQUIRE(temp1.at(index) == 0);
        temp1.at(index) = 2;
        REQUIRE(temp1.at(index) == 2);
      }
    }

    WHEN("when index is a double number") {
      double index{2.5};

      THEN("-> so vec.at(2.5) == vec.at(2)") {
        // by implicit type conversion double to int in c++
        // should be index 2.5 -> 2. so we are checking vec.at(2)
        REQUIRE(vec.at(index) == 3);

        // test setter
        EuclideanVector temp1{3};
        REQUIRE(temp1.at(index) == 0);
        temp1.at(index) = 2;
        REQUIRE(temp1.at(index) == 2);
      }
    }
  }
}

/*
 * 15. test GetNumDimensions() methods
 *  -    check if is the expected output, after all the situations that might change the dimension
 *      1. after copy constructor
 *      2. after copy assignment
 *      3. after move constructor
 *      4. after move assignment
 *      5. normal constructor
 *      6. default constructor
 *      7. unit vector
 */
SCENARIO("Test GetNumDimensions() methods") {
  GIVEN("we will test if GetNumDimensions() works after all possible way that we change or "
        "initialized the vector ") {
    EuclideanVector temp_vec{4, 4.0};

    WHEN("7. create a unit vector") {
      auto unit_vec = temp_vec.CreateUnitVector();

      THEN("check the output dimension == expected?") { REQUIRE(unit_vec.GetNumDimensions() == 4); }
    }

    WHEN("6.after using default constructor") {
      EuclideanVector vec{5};

      THEN("check the output dimension == expected?") { REQUIRE(vec.GetNumDimensions() == 5); }
    }

    WHEN("5.after using normal constructor -> check the output dimension == expected?") {
      REQUIRE(temp_vec.GetNumDimensions() == 4);
    }

    WHEN("4.after using move assignment") {
      EuclideanVector dest_vec{5, 5.5};
      EuclideanVector start_vec{4, 5.5};
      REQUIRE(start_vec.GetNumDimensions() == 4);
      start_vec = std::move(dest_vec);

      THEN("check the output dimension == expected?") {
        // check the dimension of start and destination vector
        REQUIRE(start_vec.GetNumDimensions() == 5);
        REQUIRE(dest_vec.GetNumDimensions() == 0);
      }
    }

    WHEN("3.move constructor") {
      EuclideanVector dest_vec{5, 5.5};
      EuclideanVector start_vec = std::move(dest_vec);

      THEN("check the output dimension == expected?") {
        // check the dimension of start and destination vector
        REQUIRE(start_vec.GetNumDimensions() == 5);
        REQUIRE(dest_vec.GetNumDimensions() == 0);
      }
    }

    WHEN("2.after using copy assignment") {
      EuclideanVector start_vec{1, 5.5};
      REQUIRE(start_vec.GetNumDimensions() == 1);
      start_vec = temp_vec;

      THEN("check the output dimension == expected?") {
        REQUIRE(start_vec.GetNumDimensions() == 4);
        REQUIRE(temp_vec.GetNumDimensions() == 4);
      }
    }

    WHEN("1. after using copy constructor") {
      REQUIRE(temp_vec.GetNumDimensions() == 4);
      EuclideanVector vec{temp_vec};

      THEN("check the output dimension == expected?") { REQUIRE(vec.GetNumDimensions() == 4); }
    }
  }
}

/*
 * 16. Test: GetEuclideanNorm()
 *  -   check if the normal value is correct
 *  - error case: dimension is 0
 */
SCENARIO("Test GetEuclideanNorm() ..") {
  GIVEN("A list of `normal value` for some vector") {
    // norm for vector {2,3,5,6}
    double norm1 = sqrt(pow(2, 2) + pow(3, 2) + pow(5, 2) + pow(6, 2));
    // norm for magnitudes is double. for a vector{1.5, 3.5, 4, 4.5}
    double norm2 = sqrt(pow(1.5, 2) + pow(3.5, 2) + pow(4, 2) + pow(4.5, 2));

    WHEN("vector is {2, 3, 4, 5} ") {
      std::vector<double> v1{2, 3, 5, 6};
      EuclideanVector vec{v1.begin(), v1.end()};

      THEN("the output normal == expected normal?") { REQUIRE(vec.GetEuclideanNorm() == norm1); }
    }

    WHEN("vector is {1.5, 3.5, 4, 4.5} ") {
      std::vector<double> v2{1.5, 3.5, 4, 4.5};
      EuclideanVector vec{v2.begin(), v2.end()};

      THEN("the output normal == expected normal?") { REQUIRE(vec.GetEuclideanNorm() == norm2); }
    }

    WHEN("dimension is 0") {
      EuclideanVector vec{0};

      THEN("-> throw exception") {
        REQUIRE_THROWS_WITH(vec.GetEuclideanNorm(),
                            "EuclideanVector with no dimensions does not have a norm");
      }
    }
  }
}

/*
 * 17.Test: CreateUnitVector()
 * -    error case1: 0 dimension
 * -    error case2: norm is 0
 * -    magnitudes is negative, positive, normal vector -> check if they have normal == 1?
 */
SCENARIO("Testing UnitVector()") {
  GIVEN("Given the normal of all unit vector, which is 1") {
    double unit_norm{1};

    WHEN("when 0-dimension vector ") {
      EuclideanVector vec{0};

      THEN("-> throw exception") {
        REQUIRE_THROWS_WITH(vec.CreateUnitVector(),
                            "EuclideanVector with no dimensions does not have a unit vector");
      }
    }

    WHEN("the normal of original vector is 0, it cant create a unit vector ") {
      // all magnitudes is 0, so normal will be 0
      EuclideanVector vec{5};
      REQUIRE(vec.GetEuclideanNorm() == 0);

      THEN("-> throw exception") {
        REQUIRE_THROWS_WITH(
            vec.CreateUnitVector(),
            "EuclideanVector with euclidean normal of 0 does not have a unit vector");
      }
    }

    WHEN("can we create a unit_vector when the vector have negative magnitudes? ") {
      std::vector<double> temp{-1, -2, -3, -4, -5};
      EuclideanVector vec{temp.begin(), temp.end()};

      THEN("-> check normal of output unit_vecotr == 1?") {
        REQUIRE(vec.CreateUnitVector().GetEuclideanNorm() == unit_norm);
      }
    }

    WHEN("can we create a unit_vector when the vector have positive magnitudes? ") {
      std::vector<double> temp{5, 10, 1.5, 15.5, 13};
      EuclideanVector vec{temp.begin(), temp.end()};

      THEN("-> check normal of output unit_vecotr == 1?") {
        REQUIRE(vec.CreateUnitVector().GetEuclideanNorm() == unit_norm);
      }
    }

    WHEN("can we create a unit_vector when the vector have both positive and negative "
         "magnitudes? ") {
      std::vector<double> temp{5, 3.5, -2, 5, -4.5};
      EuclideanVector vec{temp.begin(), temp.end()};

      THEN("-> check normal of output unit_vecotr == 1?") {
        REQUIRE(vec.CreateUnitVector().GetEuclideanNorm() == unit_norm);
      }
    }
  }
}

/*
 * 18. test == operator
 */
SCENARIO("Testing == operator") {
  GIVEN("given a vector to test") {
    std::vector<double> temp{2, 3, 4, 5, 6};
    EuclideanVector vec{temp.begin(), temp.end()};

    WHEN("When two vector are not the same") {
      // dimension not the same
      EuclideanVector temp1{2, 5};
      EuclideanVector temp2{0};
      std::vector<double> temp3_v{1, 3.0};
      EuclideanVector temp3{temp3_v.begin(), temp3_v.end()};

      // dimension same, but value not
      EuclideanVector temp4{5, 5.5};
      EuclideanVector temp5{5};
      EuclideanVector temp6{vec};
      temp6[0] = 10;

      THEN("-> return false") {
        REQUIRE_FALSE((vec == temp1 && vec == temp2 && vec == temp3));
        REQUIRE_FALSE((vec == temp4 && vec == temp5 && vec == temp6));
      }
    }

    WHEN("when two vector are same ") {
      EuclideanVector same_vec{vec};

      THEN("-> return true") { REQUIRE(same_vec == vec); }
    }
  }
}

/*
 * 19. test != operator
 */
SCENARIO("Testing != operator") {
  GIVEN("given a vector to test") {
    std::vector<double> temp{2, 3, 4, 5, 6};
    EuclideanVector vec{temp.begin(), temp.end()};

    WHEN("when two vector are not the same") {
      // dimension not the same
      EuclideanVector temp1{2, 5};
      EuclideanVector temp2{0};
      std::vector<double> temp3_v{1, 3.0};
      EuclideanVector temp3{temp3_v.begin(), temp3_v.end()};

      // dimension same, but value not
      EuclideanVector temp4{5, 5.5};
      EuclideanVector temp5{5};
      EuclideanVector temp6{vec};
      temp6[0] = 10;

      THEN("-> return true") {
        REQUIRE((vec != temp1 && vec != temp2 && vec != temp3));
        REQUIRE((vec != temp4 && vec != temp5 && vec != temp6));
      }
    }

    WHEN("when two vector are same") {
      EuclideanVector same_vec{vec};

      THEN("-> return false") { REQUIRE_FALSE(same_vec != vec); }
    }
  }
}

/*
 * 20. Test + operator
 *  -   different dimensions
 *  -   dimension 0 + dimension 0
 *  -   magnitudes are all 0
 *  -   normal + operation
 */
SCENARIO("Testing + operator") {
  GIVEN("a list of test cases") {
    WHEN("two vectors have different dimensions") {
      EuclideanVector v1{0, 5};
      EuclideanVector v2{1, 5};

      THEN("-> throw exception") {
        REQUIRE_THROWS_WITH(v1 + v2, "Dimensions of LHS(0) and RHS(1) do not match");
      }
    }

    WHEN("+operation on two 0-dimension vectors ") {
      EuclideanVector v1{0};
      EuclideanVector v2{0};

      THEN("-> return a 0-dimension vector") { REQUIRE(v1 == (v1 + v2)); }
    }

    WHEN("+ operation on identity vector") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector v2{5};  // identity vector : magnitudes are all 0

      THEN("-> v1+identity == v1") { REQUIRE(v1 == (v1 + v2)); }
    }

    WHEN("when + operation on two normal vector") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector v2{5, 1};
      EuclideanVector v3{5, 6.5};

      THEN("-> check magnitudes of output vector with its magnitudes") { REQUIRE(v3 == (v1 + v2)); }
    }
  }
}

/*
 * 21. Test - operator
 *  -   different dimensions
 *  -   dimension 0 + dimension 0
 *  -   magnitudes are all 0
 *  -   normal + operation
 */
SCENARIO("Testing - operator") {
  GIVEN("a list of test cases") {
    WHEN("two vectors have different dimensions") {
      EuclideanVector v1{0, 5};
      EuclideanVector v2{1, 5};

      THEN("-> throw exception") {
        REQUIRE_THROWS_WITH(v1 - v2, "Dimensions of LHS(0) and RHS(1) do not match");
      }
    }

    WHEN("-operation on two 0-dimension vectors ") {
      EuclideanVector v1{0};
      EuclideanVector v2{0};

      THEN("-> return a 0-dimension vector") { REQUIRE(v1 == (v1 - v2)); }
    }

    WHEN("- operation on identity vector") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector v2{5};  // identity vector : magnitudes are all 0

      THEN("-> v1 - identity == v1") { REQUIRE(v1 == (v1 - v2)); }
    }

    WHEN("when - operation on two normal vector") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector v2{5, 1};
      EuclideanVector v3{5, 4.5};

      THEN("-> check magnitudes of output vector with its magnitudes") { REQUIRE(v3 == (v1 - v2)); }
    }
  }
}

/*
 * 22. Test : * operator -> for dot product of two vector
 *  1. dimension not match
 *  2. one of the dimension with all magnitudes are 0
 *  3. one of the vector is identity vector
 *  4. two normal vector with no decimal magnitudes
 *  5. two normal vectors with decimal value magnitudes
 */
SCENARIO("Testing * operator(dot product)") {
  GIVEN("a list of test cases") {
    WHEN("two vectors have different dimension") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector v2{6, 5};

      THEN("-> throw exception") {
        REQUIRE_THROWS_WITH(v1 * v2, "Dimensions of LHS(5) and RHS(6) do not match");
      }
    }

    WHEN("one of the vector have magnitudes are all 0") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector v2{5};

      THEN("-> dot product = 0") { REQUIRE((v1 * v2) == 0); }
    }

    WHEN("one of the vector is identity vector") {
      EuclideanVector v1{5, 5.5};
      EuclideanVector identity{5, 1};

      THEN("-> result = sum of v1's magnitudes") {
        // so v1 * identity = sum of v1's magnitudes
        double sum = 5 * 5.5;
        REQUIRE(sum == (v1 * identity));
      }
    }

    WHEN("vector both have no decimal magnitudes") {
      std::vector<double> temp1{1, 2, 3, 4};
      std::vector<double> temp2{2, 3, 4, 5};
      EuclideanVector v1{temp1.begin(), temp1.end()};
      EuclideanVector v2{temp2.begin(), temp2.end()};

      THEN("-> check with expected output") {
        double correct_solution = 1 * 2 + 2 * 3 + 3 * 4 + 4 * 5;
        REQUIRE(correct_solution == (v1 * v2));
      }
    }

    WHEN("vector both have decimal magnitudes") {
      EuclideanVector v1{4, 3.2};
      EuclideanVector v2{4, 1.5};

      THEN("-> check with expected output") {
        double correct_solution = 4 * (3.2 * 1.5);
        REQUIRE(correct_solution == (v1 * v2));
      }
    }
  }
}

/*
 * 23. Testing * operator
 *  1. int
 *  2. double
 *  3. 0
 *  4. 0-dimensions vector
 */
SCENARIO("Testing * operator") {
  GIVEN("given a vector") {
    std::vector<double> temp{1, 2, 3, 4, 5};
    EuclideanVector vec{temp.begin(), temp.end()};

    WHEN("* int value") {
      auto new_vec = vec * 2;
      std::vector<double> temp2{2, 4, 6, 8, 10};
      EuclideanVector correct_vec{temp2.begin(), temp2.end()};

      THEN("-> check with expected output") { REQUIRE(correct_vec == new_vec); }
    }

    WHEN("* double value") {
      auto new_vec = vec * 0.5;
      std::vector<double> temp2{0.5, 1, 1.5, 2, 2.5};
      EuclideanVector correct_vec{temp2.begin(), temp2.end()};

      THEN("-> check with expected output") { REQUIRE(new_vec == correct_vec); }
    }

    WHEN("* 0 ") {
      auto new_vec = vec * 0;
      EuclideanVector correct_vec{5, 0};

      THEN("-> return a vector with all magnitudes are 0") { REQUIRE(correct_vec == new_vec); }
    }

    WHEN("* on 0-dimension vector") {
      EuclideanVector v1{0};

      THEN("-> return a 0-dimension vector") { REQUIRE((v1 * 5) == v1); }
    }
  }
}

/*
 * 24. Test: divide / operator
 *  1. 0
 *  2. int
 *  3. double
 *  4. 0-dimension vector
 */
SCENARIO("Testing / operator") {
  GIVEN("given a vector") {
    std::vector<double> temp{2, 4, 6, 8, 10};
    EuclideanVector vec{temp.begin(), temp.end()};

    WHEN("/ int value ") {
      auto new_vec = vec / 2;
      std::vector<double> temp2{1, 2, 3, 4, 5};
      EuclideanVector correct_vec{temp2.begin(), temp2.end()};

      THEN("-> check with expected output") { REQUIRE(correct_vec == new_vec); }
    }

    WHEN("/ double value ") {
      auto new_vec = vec / 2.5;
      std::vector<double> temp2{0.8, 1.6, 2.4, 3.2, 4.0};
      EuclideanVector correct_vec{temp2.begin(), temp2.end()};

      THEN("-> check with expected output") { REQUIRE(new_vec == correct_vec); }
    }

    WHEN("/ 0 -> throw a exception") {
      REQUIRE_THROWS_WITH(vec / 0, "Invalid vector division by 0");
    }

    WHEN("/ operation on 0-dimension vector") {
      EuclideanVector v1{0};

      THEN("-> return 0-dimension vector") { REQUIRE((v1 / 5) == v1); }
    }
  }
}

/*
 * 25. Test << operator
 *  -   check output format
 */
SCENARIO("Testing << operator") {
  GIVEN("a list of test cases") {
    WHEN("0-dimension vector") {
      EuclideanVector empty{0};
      std::ostringstream os;
      os << empty;

      THEN("Check with the expected output") {
        std::ostringstream correct;
        correct << "[]";
        REQUIRE(os.str() == correct.str());
      }
    }

    WHEN("normal vector") {
      EuclideanVector v1{4, 5.5};
      std::ostringstream os;
      os << v1;

      THEN("Check with the expected output") {
        std::ostringstream correct;
        correct << "[5.5 5.5 5.5 5.5]";
        REQUIRE(os.str() == correct.str());
      }
    }
  }
}

/*
 * 26. Testing : const vector
 *      - check all the valid methods work properly
 *      - (no check invalid method -> since Clion already told us no this methods to use)
 *          no valid methods:
 *              +=, -=,
 */
SCENARIO("Testing const vector") {
  GIVEN("When a const vector is given") {
    const EuclideanVector vec{5, 5.5};

    WHEN("Check subscript getter works?") {
      REQUIRE(vec[1] == 5.5);  // subscript getter
    }

    WHEN("check at() getter works?") { REQUIRE(vec.at(1) == 5.5); }

    WHEN("check GetNumDimension() works") { REQUIRE(vec.GetNumDimensions() == 5); }

    WHEN("check GetEuclideanNorm() works") { REQUIRE_NOTHROW(vec.GetEuclideanNorm()); }

    WHEN("check CreateUnitVector() works") { REQUIRE_NOTHROW(vec.CreateUnitVector()); }

    WHEN("check std::vector conversion works?") {
      std::vector<double> correct{5.5, 5.5, 5.5, 5.5, 5.5};
      REQUIRE(correct == static_cast<std::vector<double>>(vec));
    }

    WHEN("check std::list conversion works?") {
      std::list<double> correct{5.5, 5.5, 5.5, 5.5, 5.5};
      REQUIRE(correct == static_cast<std::list<double>>(vec));
    }
  }
}
