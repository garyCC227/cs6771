/*

  == Explanation and rational of testing ==
    this test will have the coverage:
    1. function coverage: all the functions will be called in this test
    2. branch/ statement/ expression coverage:
        I will cover all the possible input as much as I can, so guarantee that
        all the statement/expression/if_else branch would be implemented(in this function).
            such as
            (1) type(int, char, string)
            (2) weired graph(e.g have nullptr as edge pair)
            (3) special input that will call the if_else branch (or others expression/ statement)
            (4) normal input
            e.t.c
    and with 1. and 2. , we hopefully we can cover all the situations, then we will compare the my
    output with the expected output. Finally, if all match, we could say all my functions work
 properly.

    - for const graph:
        we will test for any const graph will have valid const memeber function to call.
        for some case, CLion already handle the error case for us

 -------------------------------------------------------------------------------------------
                        Table of Content For Each Test Case
                    (To see detail, go the corresponding test case section)
 -------------------------------------------------------------------------------------------
 1. Test constructor           2. Test template                  3.Test property method
 4. Test graph modification    5. Extended modification          6. Test graph friend
 7. Test const graph with all the graph methods
 ============================================================================================
 Graph iterator test case
 20. cbegin()           21. cend()                        22.crbegin()
 23. crend()            24. const_iterator ++operator     25.const_iterator --operator
 26. extended const_iterator ++ and -- operator           27. const_reverse_iterator ++operator
 28.const_reverse_iterator --operator
 29.extended const_reverse_iterator ++ and -- operator
 30. == operator        31. != operator                   32. find()
 33. erase()            34. const graph with iterator
 */

#include "assignments/dg/graph.h"
#include "catch.h"

/*
 *  1. Test constructors. How to test:
 *  How to test: Initiate constructors using all constructors available
 *
 *  method: Constructors
 */
SCENARIO("Testing default constructor") {
  GIVEN("We will initialise a Graph using the default constructor") {
    WHEN("when empty graph is intialised") {
      gdwg::Graph<int, int> g;
      THEN("-> then dimension should be 1, magnitudes[0] is 0")
      REQUIRE(g.GetNodes().size() == 0);
    }
  }

  GIVEN("We will initialise a Graph in using the given iterators") {
    WHEN("when graph is intialised") {
      std::vector<std::string> v{"1", "2", "3", "4"};
      gdwg::Graph<std::string, double> g{v.begin(), v.end()};
      THEN("-> then dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("The printed graph should be") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "1 (\n"
                            ")\n"
                            "2 (\n"
                            ")\n"
                            "3 (\n"
                            ")\n"
                            "4 (\n"
                            ")\n");
      }
    }
  }

  GIVEN("We will initialise a Graph using the list constructor using the given list") {
    WHEN("when empty graph is intialised") {
      gdwg::Graph<int, int> g{1, 2, 3, 4};
      THEN("-> then dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("The printed graph should be") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "1 (\n"
                            ")\n"
                            "2 (\n"
                            ")\n"
                            "3 (\n"
                            ")\n"
                            "4 (\n"
                            ")\n");
      }
    }
  }

  GIVEN("We will initialise a Graph in  by using the given edge tuples") {
    WHEN("when empty graph is intialised") {
      THEN("-> then dimension should be 4") {
        auto e1 = std::make_tuple("A", "B", 5);
        auto e2 = std::make_tuple("A", "C", 6);
        auto e3 = std::make_tuple("A", "D", 7);

        auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
        gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};
        REQUIRE(g.GetNodes().size() == 4);
        AND_THEN("The printed graph should be") {
          std::ostringstream os;
          os << g;
          REQUIRE(os.str() == "A (\n"
                              "  B | 5\n"
                              "  C | 6\n"
                              "  D | 7\n"
                              ")\n"
                              "B (\n"
                              ")\n"
                              "C (\n"
                              ")\n"
                              "D (\n"
                              ")\n");
        }
      }
    }
  }

  GIVEN("We will copy the Graph from a given graph") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1, 2, 3, 4};
      THEN("-> the dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We copy to another graph") {
        gdwg::Graph<int, int> g1{g};
        THEN("-> the dimension should be 4") {
          REQUIRE(g.GetNodes().size() == g1.GetNodes().size());
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g;
            REQUIRE(os.str() == "1 (\n"
                                ")\n"
                                "2 (\n"
                                ")\n"
                                "3 (\n"
                                ")\n"
                                "4 (\n"
                                ")\n");
          }
        }
        AND_WHEN("Modify the new graph") {
          g1.Clear();
          THEN("the new node should be empty now") { REQUIRE(g1.GetNodes().size() == 0); }
          AND_THEN("should not affect the old") { REQUIRE(g.GetNodes().size() == 4); }
        }
      }
    }
  }

  GIVEN("We will move the Graph from a given graph") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1, 2, 3, 4};
      THEN("-> the dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We move another graph") {
        gdwg::Graph<int, int> g1{std::move(g)};
        THEN("-> the new dimension should be 4") {
          REQUIRE(g1.GetNodes().size() == 4);
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g1;
            REQUIRE(os.str() == "1 (\n"
                                ")\n"
                                "2 (\n"
                                ")\n"
                                "3 (\n"
                                ")\n"
                                "4 (\n"
                                ")\n");
          }
        }
        AND_WHEN("New graph is constructed, the old graph should be empty") {
          REQUIRE(g.GetNodes().size() == 0);
        }
      }
    }
  }

  GIVEN("We will copy graph via = operator") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1, 2, 3, 4};
      THEN("-> the dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We copy to another graph") {
        gdwg::Graph<int, int> g1{2};
        g1 = g;
        THEN("-> the dimension should be 4") {
          REQUIRE(g.GetNodes().size() == g1.GetNodes().size());
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g;
            REQUIRE(os.str() == "1 (\n"
                                ")\n"
                                "2 (\n"
                                ")\n"
                                "3 (\n"
                                ")\n"
                                "4 (\n"
                                ")\n");
          }
        }
        AND_WHEN("Modify the new graph") {
          g1.Clear();
          THEN("the new node should be empty now") { REQUIRE(g1.GetNodes().size() == 0); }
          AND_THEN("should not affect the old") { REQUIRE(g.GetNodes().size() == 4); }
        }
      }
    }
  }

  GIVEN("We will move the Graph via = operator") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1, 2, 3, 4};
      THEN("-> the dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We move another graph") {
        gdwg::Graph<int, int> g1{};
        g1 = std::move(g);
        THEN("-> the new dimension should be 4") {
          REQUIRE(g1.GetNodes().size() == 4);
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g1;
            REQUIRE(os.str() == "1 (\n"
                                ")\n"
                                "2 (\n"
                                ")\n"
                                "3 (\n"
                                ")\n"
                                "4 (\n"
                                ")\n");
          }
        }
        AND_WHEN("New graph is constructed, the old graph should be empty") {
          REQUIRE(g.GetNodes().size() == 0);
        }
      }
    }
  }
}

/*
 *  2. Test the templates.
 *  How to test: Initialise graph of various data types, including int, double, string char
 *
 *  method: Constructors
 */
SCENARIO("Testing templates") {
  GIVEN("Graph of strings") {
    gdwg::Graph<std::string, std::string> g{"alpha", "beta", "charlie", "delta"};
    THEN("The dimension should be 4")
    REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "alpha (\n"
                          ")\n"
                          "beta (\n"
                          ")\n"
                          "charlie (\n"
                          ")\n"
                          "delta (\n"
                          ")\n");
    }
  }

  GIVEN("Graph of int") {
    gdwg::Graph<int, int> g{1, 3, 5, 7};
    THEN("The dimension should be 4")
    REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "1 (\n"
                          ")\n"
                          "3 (\n"
                          ")\n"
                          "5 (\n"
                          ")\n"
                          "7 (\n"
                          ")\n");
    }
  }

  GIVEN("Graph of double") {
    gdwg::Graph<double, double> g{1.1, 3.3, 5.5, 7.7};
    THEN("The dimension should be 4")
    REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "1.1 (\n"
                          ")\n"
                          "3.3 (\n"
                          ")\n"
                          "5.5 (\n"
                          ")\n"
                          "7.7 (\n"
                          ")\n");
    }
  }

  GIVEN("Graph of chars") {
    gdwg::Graph<char, char> g{'a', 'b', 'c', 'd'};
    THEN("The dimension should be 4")
    REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "a (\n"
                          ")\n"
                          "b (\n"
                          ")\n"
                          "c (\n"
                          ")\n"
                          "d (\n"
                          ")\n");
    }
  }
}

/*
 *  3. Test the property related methods of Graph.
 *  How to test: Retrieve information via getter method then
 *               check if the order and value and exception match
 *               1. Isnode then GetNode
 *               2. Getnode then GetConnected then GetWeights
 *               3. IsConnected
 *
 *  method: GetNodes(), GetConnected(const N&), GetWeights(const N&, const N&)
 *          IsNode(const N&)  IsConnected(const N&, const N&)
 */
SCENARIO("Getting graph info from provided functions") {
  GIVEN("1. A non empty graph") {
    gdwg::Graph<double, double> g{1.1, 5.5, 3.3, 7.7};
    THEN("the size should be 4") REQUIRE(g.GetNodes().size() == 4);

    WHEN("check nodes that is not part of graph") {
      bool predicate = g.IsNode(100);
      THEN("it should return false") { REQUIRE(predicate == false); }
    }
    AND_WHEN("check nodes that is part of graph") {
      THEN("it should return true") { REQUIRE(g.IsNode(1.1) == true); }
    }

    WHEN("We try to retrieve the nodes in the graph") {
      std::vector node = g.GetNodes();
      THEN("the size should be 4") REQUIRE(node.size() == 4);
      AND_THEN("The node value and oder matches") {
        REQUIRE(node.at(0) == 1.1);
        REQUIRE(node.at(1) == 3.3);
        REQUIRE(node.at(2) == 5.5);
        REQUIRE(node.at(3) == 7.7);
      }
    }
  }

  GIVEN("2. A non empty graph with edges") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    std::tuple e1 = std::make_tuple(s1, s2, 5.4);
    std::tuple e2 = std::make_tuple(s2, s3, 7.6);
    std::vector e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    THEN("Get the vertex from the graph") {
      std::vector node = g.GetNodes();
      AND_THEN("the size should be 3") REQUIRE(node.size() == 3);

      AND_THEN("The node value and order matches") {
        REQUIRE(node.at(0) == "Hello");
        REQUIRE(node.at(1) == "are");
        REQUIRE(node.at(2) == "how");
      }

      THEN("The output matches") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "Hello (\n"
                            "  how | 5.4\n"
                            ")\n"
                            "are (\n"
                            ")\n"
                            "how (\n"
                            "  are | 7.6\n"
                            ")\n");
      }
    }

    WHEN("Find the edges that doesn't exist") {
      std::string excp = "Cannot call Graph::GetConnected if src doesn't exist in the graph";
      REQUIRE_THROWS_AS(g.GetConnected("doesn't exist"), std::out_of_range);
      REQUIRE_THROWS_WITH(g.GetConnected("doesn't exist"), excp);
    }

    WHEN("Find the weights that doesn't exist") {
      std::string excp =
          "Cannot call Graph::GetWeights if src or dst node don't exist in the graph";
      WHEN("src doesn't exist") {
        REQUIRE_THROWS_AS(g.GetWeights("doesn't exist", "are"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("doesn't exist", "are"), excp);
      }
      WHEN("dest doesn't exist") {
        REQUIRE_THROWS_AS(g.GetWeights("are", "doesn't exist"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("are", "doesn't exist"), excp);
      }
    }

    WHEN("Find the outgoing edges from how") {
      g.InsertEdge("how", "are", 10);
      std::vector edges = g.GetConnected("how");
      AND_THEN("Only 1 edge") {
        REQUIRE(edges.size() == 1);
        THEN("The returned edges should match the graph") { REQUIRE(edges.at(0) == "are"); }
        WHEN("We try to find the weight between two vertex") {
          std::vector weights = g.GetWeights("how", "are");
          THEN("Only one weight and should match") {
            REQUIRE(weights.size() == 2);
            REQUIRE(weights.at(0) == 7.6);
          }

          std::string excp =
              "Cannot call Graph::IsConnected if src or dst node don't exist in the graph";
          WHEN("NODES that doesn't exist") {
            REQUIRE_THROWS_AS(g.IsConnected("doesn't exist", "are"), std::runtime_error);
            REQUIRE_THROWS_WITH(g.IsConnected("doesn't exist", "are"), excp);
          }

          WHEN("NODES that doesn't exist") {
            REQUIRE_THROWS_AS(g.IsConnected("are", "doesn't exist"), std::runtime_error);
            REQUIRE_THROWS_WITH(g.IsConnected("are", "doesn't exist"), excp);
          }

          AND_THEN("the two nodes should be connected") {
            REQUIRE(g.IsConnected("how", "are") == true);
          }
        }
      }
    }
  }

  GIVEN("3. A non empty graph that has node with multiple edges") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    std::tuple e1 = std::make_tuple(s1, s2, 5.4);
    std::tuple e2 = std::make_tuple(s2, s3, 7.6);
    std::tuple e3 = std::make_tuple(s1, s3, 10);
    std::vector e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    THEN("The output matches") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "Hello (\n"
                          "  are | 10\n"
                          "  how | 5.4\n"
                          ")\n"
                          "are (\n"
                          ")\n"
                          "how (\n"
                          "  are | 7.6\n"
                          ")\n");
    }

    WHEN("Find the outgoing edges from Hello") {
      std::vector edges = g.GetConnected("Hello");
      AND_THEN("2 outgoing edge with weight 7.6 and 10") {
        REQUIRE(edges.size() == 2);
        THEN("The returned edges should have sorted and match the graph") {
          REQUIRE(edges.at(0) == "are");
          REQUIRE(edges.at(1) == "how");
        }

        WHEN("We try to find the weight between two vertex") {
          std::vector w1 = g.GetWeights("Hello", "are");
          std::vector w2 = g.GetWeights("Hello", "how");
          THEN("Only one weight and should match") {
            REQUIRE(w1.size() == 1);
            REQUIRE(w1.at(0) == 10);
            REQUIRE(w2.size() == 1);
            REQUIRE(w2.at(0) == 5.4);
          }
          AND_THEN("the two nodes should be connected") {
            REQUIRE(g.IsConnected("Hello", "are") == true);
            REQUIRE(g.IsConnected("Hello", "how") == true);
          }
        }
      }
    }
  }
}

/*
 *  4. Test graph modifications.
 *  How to test:
 *              Perform insertion and deletion operations of node and edges
 *              Check order
 *              1. Insert Node
 *              2. Insert Edge
 *              3. Delete Node
 *              4. erase edge
 *              5. Comprehensive tests
 *
 *  method tested: InsertNode(const N& val) InsertEdge(const N& src, const N& dst, const E& w)
 *          DeleteNode(const N&)
 *
 *  getting graph info from provided function
 */
SCENARIO("Modify graph from provided functions") {
  GIVEN("1. A empty graph") {
    gdwg::Graph<std::string, double> g{};
    WHEN("Insert nodes") {
      g.InsertNode("a");
      g.InsertNode("b");
      THEN("the graph should be updated") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "a (\n"
                            ")\n"
                            "b (\n"
                            ")\n");
        REQUIRE(g.GetNodes().size() == 2);
      }
      WHEN("Try to insert the same node") {
        bool inserted = g.InsertNode("a");
        THEN("The insertion should fail") { REQUIRE(inserted == false); }
      }
    }

    WHEN("Two nodes are inserted") {
      bool inserted = g.InsertNode("z");
      THEN("First one is inerted") {
        REQUIRE(g.GetNodes().size() == 1);
        REQUIRE(inserted == true);
      }

      inserted = g.InsertNode("a");
      THEN("Second one is inerted") {
        REQUIRE(inserted == true);
        REQUIRE(g.GetNodes().size() == 2);
      }

      THEN("The nodes are sorted") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "a (\n"
                            ")\n"
                            "z (\n"
                            ")\n");
      }
    }
  }

  GIVEN("2. A graph with vertex no linkage between them") {
    gdwg::Graph<double, double> g{1, 2, 3};
    REQUIRE(g.GetNodes().size() == 3);

    WHEN("Insert edges") {
      g.InsertEdge(1, 2, 10);
      g.InsertEdge(1, 3, 11);
      g.InsertEdge(2, 1, 12);
      THEN("the graph should be updated") {
        REQUIRE(g.GetConnected(1).size() == 2);
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "1 (\n"
                            "  2 | 10\n"
                            "  3 | 11\n"
                            ")\n"
                            "2 (\n"
                            "  1 | 12\n"
                            ")\n"
                            "3 (\n"
                            ")\n");
      }

      WHEN("Insert edge that has unknown vertex") {
        std::string excp =
            "Cannot call Graph::InsertEdge when either src or dst node does not exist";
        THEN("Exception should be thrown") {
          REQUIRE_THROWS_AS(g.InsertEdge(9999, 2, 10), std::runtime_error);
          REQUIRE_THROWS_WITH(g.InsertEdge(9999, 2, 10), excp);
        }
        THEN("") {
          REQUIRE_THROWS_AS(g.InsertEdge(1, 9999, 10), std::runtime_error);
          REQUIRE_THROWS_WITH(g.InsertEdge(1, 9999, 10), excp);
        }
      }
    }

    WHEN("Insert edge multiple times") {
      bool inserted = g.InsertEdge(1, 2, 10);
      THEN("First one is inserted") {
        REQUIRE(g.GetConnected(1).size() == 1);
        REQUIRE(inserted == true);
      }
      inserted = g.InsertEdge(1, 2, 10);
      THEN("duplicated edge cannot be inserted") {
        REQUIRE(inserted == false);
        REQUIRE(g.GetConnected(1).size() == 1);
      }
    }

    WHEN("Insert edge with different wegiht") {
      bool inserted = g.InsertEdge(1, 2, 10);
      THEN("First one is inerted") {
        REQUIRE(g.GetConnected(1).size() == 1);
        REQUIRE(inserted == true);
      }
      inserted = g.InsertEdge(1, 2, 9);
      THEN("Vertex with different weight is inserted") {
        REQUIRE(inserted == true);
        REQUIRE(g.GetConnected(1).size() == 1);
        REQUIRE(g.GetWeights(1, 2).size() == 2);
        THEN("The order of insertion is checked") {
          std::ostringstream os;
          os << g;
          REQUIRE(os.str() == "1 (\n"
                              "  2 | 9\n"
                              "  2 | 10\n"
                              ")\n"
                              "2 (\n"
                              ")\n"
                              "3 (\n"
                              ")\n");
        }
      }
    }
  }

  GIVEN("3. A graph with nodes and edges") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e4 = std::make_tuple(s2, s1, 4);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    g.InsertNode("d");

    THEN("The graph info") {
      REQUIRE(g.GetNodes().size() == 4);
      REQUIRE(g.GetConnected("b").size() == 2);
      REQUIRE(g.GetConnected("a").size() == 1);
      REQUIRE(g.GetConnected("c").size() == 1);
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "a (\n"
                          "  b | 1\n"
                          ")\n"
                          "b (\n"
                          "  a | 4\n"
                          "  c | 2\n"
                          ")\n"
                          "c (\n"
                          "  a | 3\n"
                          ")\n"
                          "d (\n"
                          ")\n");
    }

    WHEN("delete nodes with no edges") {
      bool deleted = g.DeleteNode("d");
      THEN("The deletion succeeded") {
        REQUIRE(deleted == true);
        REQUIRE(g.GetNodes().size() == 3);
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "a (\n"
                            "  b | 1\n"
                            ")\n"
                            "b (\n"
                            "  a | 4\n"
                            "  c | 2\n"
                            ")\n"
                            "c (\n"
                            "  a | 3\n"
                            ")\n");
      }

      AND_WHEN("delete nodes that is not in the graph") {
        deleted = g.DeleteNode("z");
        REQUIRE(deleted == false);
      }
    }

    WHEN("delete nodes with related edges") {
      bool deleted = g.DeleteNode("a");
      THEN("The deletion should succeed and all related edges are deleted") {
        REQUIRE(deleted == true);
        REQUIRE(g.GetNodes().size() == 3);
        std::string excp =
            "Cannot call Graph::GetWeights if src or dst node don't exist in the graph";
        REQUIRE_THROWS_AS(g.GetWeights("c", "a"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("c", "a"), excp);

        THEN("the graph output shoud update") {
          std::ostringstream os;
          os << g;
          REQUIRE(os.str() == "b (\n"
                              "  c | 2\n"
                              ")\n"
                              "c (\n"
                              ")\n"
                              "d (\n"
                              ")\n");
        }
      }
    }
  }

  GIVEN("4 test earse edges using given graph") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e4 = std::make_tuple(s2, s1, 4);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("erase edge that with node not in the graph") {
      bool erased = g.erase("x", "z", 1);
      REQUIRE(erased == false);
      erased = g.erase("a", "z", 1);
      REQUIRE(erased == false);
    }

    WHEN("erase edge that is in the graph") {
      bool erased = g.erase("a", "b", 1);
      REQUIRE(erased == true);
      REQUIRE(g.IsConnected("a", "b") == false);
      THEN("remove the edge again") {
        erased = g.erase("a", "b", 1);
        REQUIRE(erased == false);
      }
    }
  }

  GIVEN("5. Comprehensive operations to a given graph") {
    auto e3 = std::make_tuple("A", "B", 5);
    auto e4 = std::make_tuple("A", "C", 6);
    auto e5 = std::make_tuple("A", "D", 7);
    auto e6 = std::make_tuple("E", "C", 8);
    auto e7 = std::make_tuple("Z", "E", 8);
    auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e3, e4, e5, e6, e7};
    gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};
    std::string output = "A (\n"
                         "  B | 5\n"
                         "  C | 6\n"
                         "  D | 7\n"
                         ")\n"
                         "B (\n"
                         ")\n"
                         "C (\n"
                         ")\n"
                         "D (\n"
                         ")\n"
                         "E (\n"
                         "  C | 8\n"
                         ")\n"
                         "Z (\n"
                         "  E | 8\n"
                         ")\n";

    REQUIRE(g.GetNodes().size() == 6);
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == output);
    WHEN("We remove the vertex with most edges") {
      bool deleted = g.DeleteNode("A");
      THEN("the node can be deleted") {
        REQUIRE(deleted == true);
        std::string excp =
            "Cannot call Graph::GetWeights if src or dst node don't exist in the graph";
        REQUIRE_THROWS_AS(g.GetWeights("A", "C"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("A", "C"), excp);

        REQUIRE_THROWS_AS(g.GetWeights("Z", "A"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("Z", "A"), excp);

        os.str("");
        os << g;
        REQUIRE(os.str() == "B (\n"
                            ")\n"
                            "C (\n"
                            ")\n"
                            "D (\n"
                            ")\n"
                            "E (\n"
                            "  C | 8\n"
                            ")\n"
                            "Z (\n"
                            "  E | 8\n"
                            ")\n");
      }
    }

    THEN("We insert it back") {
      g.DeleteNode("A");
      bool inserted = g.InsertNode("A");
      REQUIRE(inserted == true);
      AND_WHEN("We insert edges") {
        g.InsertEdge("A", "B", 5);
        g.InsertEdge("A", "C", 6);
        g.InsertEdge("A", "D", 7);
        THEN("the output should match previous graph") {
          os.str("");
          os << g;
          REQUIRE(os.str() == output);
        }
      }
    }
  }
}

/*
 *  5. Test extended modifications.
 *  How to test:
 *              1. Replace
 *                1.1 Basic (no other ingoing edge) with exceptions
 *                1.2 Comprehensive(multiple incoming and outgoing edges)
 *              2.MergeRepalce
 *                2.1 Basic (no other incoming edge)
 *                2.2 Duplicate edge removed
 *                2.3 Comprehensive MerReplace nodes with incoming/outgoing nodes
 *  method: Replace(const N&, const N&)
 *          MergeReplace(const N&, const N&)
 */
SCENARIO("Replace and MergeReplace nodes in graph") {
  GIVEN("1.1 reaplce node with no incoming ") {
    auto e1 = std::make_tuple("A", "B", 5);
    auto e2 = std::make_tuple("A", "C", 6);
    auto e3 = std::make_tuple("B", "C", 5);
    auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "A (\n"
                        "  B | 5\n"
                        "  C | 6\n"
                        ")\n"
                        "B (\n"
                        "  C | 5\n"
                        ")\n"
                        "C (\n"
                        ")\n");

    WHEN("We replace node that is already in the graph") {
      bool replaced = g.Replace("A", "C");
      THEN("This action would fail") { REQUIRE(replaced == false); }
    }

    WHEN("We replace node that is not in the graph") {
      THEN("This action would fail") {
        std::string excp = "Cannot call Graph::Replace on a node that doesn't exist";
        REQUIRE_THROWS_AS(g.Replace("Z", "E"), std::runtime_error);
        REQUIRE_THROWS_WITH(g.Replace("Z", "E"), excp);
      }
    }

    AND_WHEN("We replace node A by Z") {
      bool replaced = g.Replace("A", "Z");

      REQUIRE(replaced == true);
      REQUIRE(g.GetNodes().size() == 3);
      REQUIRE(g.IsNode("A") == false);
      REQUIRE(g.IsNode("Z") == true);

      THEN("The edge from A should be repalced by Z") {
        REQUIRE(g.IsConnected("Z", "B") == true);
        REQUIRE(g.IsConnected("Z", "C") == true);
        os.str("");
        os << g;
        REQUIRE(os.str() == "B (\n"
                            "  C | 5\n"
                            ")\n"
                            "C (\n"
                            ")\n"
                            "Z (\n"
                            "  B | 5\n"
                            "  C | 6\n"
                            ")\n");
      }
    }
  }

  GIVEN("1.2 A graph with edges and nodes") {
    auto e3 = std::make_tuple("A", "B", 5);
    auto e4 = std::make_tuple("A", "C", 6);
    auto e5 = std::make_tuple("A", "D", 7);
    auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e3, e4, e5};
    gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};
    g.InsertEdge("C", "B", 10);
    g.InsertEdge("B", "D", 1);
    g.InsertEdge("D", "A", 10);
    g.InsertEdge("A", "A", 10);

    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "A (\n"
                        "  A | 10\n"
                        "  B | 5\n"
                        "  C | 6\n"
                        "  D | 7\n"
                        ")\n"
                        "B (\n"
                        "  D | 1\n"
                        ")\n"
                        "C (\n"
                        "  B | 10\n"
                        ")\n"
                        "D (\n"
                        "  A | 10\n"
                        ")\n");

    WHEN("Replace node by Q") {
      g.Replace("A", "Q");
      REQUIRE(g.IsNode("A") == false);
      REQUIRE(g.IsNode("Q") == true);

      THEN("All the outgoing and incoming edges should be updated") {
        REQUIRE(g.IsConnected("Q", "Q") == true);
        REQUIRE(g.IsConnected("Q", "B") == true);
        REQUIRE(g.IsConnected("Q", "C") == true);
        REQUIRE(g.IsConnected("Q", "D") == true);
        REQUIRE(g.IsConnected("D", "Q") == true);
      }

      THEN("The final graph output") {
        os.str("");
        os << g;
        REQUIRE(os.str() == "B (\n"
                            "  D | 1\n"
                            ")\n"
                            "C (\n"
                            "  B | 10\n"
                            ")\n"
                            "D (\n"
                            "  Q | 10\n"
                            ")\n"
                            "Q (\n"
                            "  B | 5\n"
                            "  C | 6\n"
                            "  D | 7\n"
                            "  Q | 10\n"
                            ")\n");
      }
    }
  }

  GIVEN("2.1 MergeReplace of a node with no incoming edge") {
    std::tuple e1 = std::make_tuple("A", "B", 5);
    std::tuple e2 = std::make_tuple("A", "C", 6);
    std::tuple e3 = std::make_tuple("B", "C", 5);
    std::vector v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};

    WHEN("We mergereaplce node that is not in the graph") {
      THEN("This action would fail") {
        std::string excp =
            "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph";
        REQUIRE_THROWS_AS(g.MergeReplace("Z", "A"), std::runtime_error);
        REQUIRE_THROWS_WITH(g.MergeReplace("Z", "A"), excp);
        REQUIRE_THROWS_AS(g.MergeReplace("A", "Z"), std::runtime_error);
        REQUIRE_THROWS_WITH(g.MergeReplace("A", "Z"), excp);
      }
    }

    WHEN("We mergereaplce node") {
      g.MergeReplace("A", "B");
      THEN("The graph should have two nodes now") {
        REQUIRE(g.GetNodes().size() == 2);
        REQUIRE(g.IsNode("A") == false);

        THEN("The edges that were in A should append to B now") {
          REQUIRE(g.IsConnected("B", "B") == true);
          REQUIRE(g.IsConnected("B", "C") == true);

          THEN("B to C has two edges now") {
            std::vector weights = g.GetWeights("B", "C");
            REQUIRE(weights.size() == 2);
            REQUIRE(weights[0] == 5);
            REQUIRE(weights[1] == 6);
          }
        }
      }

      AND_THEN("The final graph") {
        std::ostringstream os;
        os.str("");
        os << g;
        REQUIRE(os.str() == "B (\n"
                            "  B | 5\n"
                            "  C | 5\n"
                            "  C | 6\n"
                            ")\n"
                            "C (\n"
                            ")\n");
      }
    }
  }

  GIVEN("2.2 MergeReplace of a node with duplicate edges") {
    std::tuple e1 = std::make_tuple("A", "B", 5);
    std::tuple e2 = std::make_tuple("A", "C", 6);
    std::tuple e3 = std::make_tuple("B", "B", 5);
    std::vector v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};

    WHEN("MergeReplace") {
      g.MergeReplace("A", "B");
      THEN("The graph should have two nodes now") {
        REQUIRE(g.GetNodes().size() == 2);
        REQUIRE(g.IsNode("A") == false);

        THEN("The edges that were in A should append to B now") {
          REQUIRE(g.IsConnected("B", "B") == true);
          REQUIRE(g.IsConnected("B", "C") == true);

          THEN("The duplicate edges B-B is removed") {
            std::vector weights = g.GetWeights("B", "B");
            REQUIRE(weights.size() == 1);
            REQUIRE(weights[0] == 5);
          }
        }
      }

      AND_THEN("The final graph") {
        std::ostringstream os;
        os.str("");
        os << g;
        REQUIRE(os.str() == "B (\n"
                            "  B | 5\n"
                            "  C | 6\n"
                            ")\n"
                            "C (\n"
                            ")\n");
      }
    }
  }

  GIVEN("2.3 Comprehensive MergeReplace nodes with incoming/outgoing nodes") {
    auto e3 = std::make_tuple("A", "B", 5);
    auto e4 = std::make_tuple("A", "C", 6);
    auto e5 = std::make_tuple("A", "D", 7);
    auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e3, e4, e5};
    gdwg::Graph<std::string, double> g{v_tmp.begin(), v_tmp.end()};
    g.InsertEdge("C", "B", 10);
    g.InsertEdge("B", "D", 1);
    g.InsertEdge("D", "A", 10);
    g.InsertEdge("A", "A", 10);

    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "A (\n"
                        "  A | 10\n"
                        "  B | 5\n"
                        "  C | 6\n"
                        "  D | 7\n"
                        ")\n"
                        "B (\n"
                        "  D | 1\n"
                        ")\n"
                        "C (\n"
                        "  B | 10\n"
                        ")\n"
                        "D (\n"
                        "  A | 10\n"
                        ")\n");

    WHEN("MergeReplace node by B") {
      g.MergeReplace("A", "B");
      REQUIRE(g.IsNode("A") == false);

      THEN("All the outgoing and incoming edges should be updated") {
        REQUIRE(g.IsConnected("B", "B") == true);
        REQUIRE(g.IsConnected("B", "C") == true);
        REQUIRE(g.IsConnected("B", "D") == true);
        THEN("The edges B-D are merged") {
          auto weights = g.GetWeights("B", "D");
          REQUIRE(weights.size() == 2);
          REQUIRE(weights[0] == 1);
          REQUIRE(weights[1] == 7);
        }

        THEN("The incoming edges should update") {
          REQUIRE(g.IsConnected("C", "B") == true);
          REQUIRE(g.IsConnected("D", "B") == true);
          auto weights = g.GetWeights("D", "B");
          REQUIRE(weights.size() == 1);
          REQUIRE(weights[0] == 10);
        }
      }
      THEN("The final graph output") {
        os.str("");
        os << g;
        REQUIRE(os.str() == "B (\n"
                            "  B | 5\n"
                            "  B | 10\n"
                            "  C | 6\n"
                            "  D | 1\n"
                            "  D | 7\n"
                            ")\n"
                            "C (\n"
                            "  B | 10\n"
                            ")\n"
                            "D (\n"
                            "  B | 10\n"
                            ")\n");
      }
    }
  }
}

/*
 *  6. Test friend.
 *  How to test: since == and != use same interpretations, we can test simultaneously
 *              1. == and !=
 *
 *  method: == !=
 */
SCENARIO("Testing friend funciton") {
  GIVEN("A graph with nodes and edges") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    auto e1 = std::make_tuple(s1, s2, 5.4);
    auto e2 = std::make_tuple(s2, s3, 7.6);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    THEN("We compare the copied graph") {
      gdwg::Graph<std::string, double> g_copy{g};
      THEN("These two graphs should be equal") {
        REQUIRE(g == g_copy);
        REQUIRE(!(g != g_copy));
      }
    }

    THEN("compare a empty graph") {
      gdwg::Graph<std::string, double> g_empty;
      THEN("These two graphs should not be equal") {
        REQUIRE(g != g_empty);
        REQUIRE(!(g == g_empty));
      }
    }
    //
    THEN("compare graph with same nodes but no edges") {
      gdwg::Graph<std::string, double> g_1{"A", "B", "C"};
      THEN("These two graphs should not be equal") {
        REQUIRE(g != g_1);
        REQUIRE(!(g == g_1));
      }
    }

    THEN("compare graph with same nodes but different edges") {
      GIVEN("A same graph with one weight difference") {
        auto e3 = std::make_tuple("A", "B", 4.5);
        auto e4 = std::make_tuple("B", "C", 7.6);
        auto v = std::vector<std::tuple<std::string, std::string, double>>{e3, e4};
        gdwg::Graph<std::string, double> g_1{v.begin(), v.end()};
        THEN("These two graphs should not be equal") {
          REQUIRE(g != g_1);
          REQUIRE(!(g == g_1));
        }

        AND_WHEN("We remove to one of the edges") {
          REQUIRE(g_1.erase("A", "B", 4.5) == true);
          THEN("These two graphs should be equal") {
            REQUIRE(g != g_1);
            REQUIRE(!(g == g_1));
          }
        }

        AND_WHEN("We modify these edge to match the graph") {
          REQUIRE(g_1.erase("A", "B", 4.5) == true);
          REQUIRE(g_1.InsertEdge("A", "B", 5.4) == true);
          THEN("These two graphs should be equal") {
            REQUIRE(g == g_1);
            REQUIRE(!(g != g_1));
          }
        }

        AND_WHEN("We add one more edge to match the graph") {
          REQUIRE(g_1.erase("A", "B", 4.5) == true);
          REQUIRE(g_1.InsertEdge("A", "B", 5.4) == true);
          REQUIRE(g_1.InsertEdge("A", "B", 10) == true);
          THEN("These two graphs should not be equal") {
            REQUIRE(g != g_1);
            REQUIRE(!(g == g_1));
          }
        }
      }
    }

    THEN("compare graph with differnet nodes") {
      GIVEN("A same graph with one weight difference") {
        auto e3 = std::make_tuple("A", "B", 5.4);
        auto v = std::vector<std::tuple<std::string, std::string, double>>{e3};
        gdwg::Graph<std::string, double> g_1{v.begin(), v.end()};
        THEN("These two graphs should not be equal") {
          REQUIRE(g != g_1);
          REQUIRE(!(g == g_1));
        }

        THEN("WE insert C") {
          REQUIRE(g_1.InsertNode("C") == true);
          THEN("still not equal") {
            REQUIRE(g != g_1);
            REQUIRE(!(g == g_1));
          }
        }
      }
    }
  }
}

/*
 *  7. Test Const graph.
 *  How to test: Test all const method to check the const correctness
 *  method: 1.GetNodes, IsNode
 *          2.GetConnected, IsConnected,
 *          3.GetWeights
 */
SCENARIO("Check const correctness") {
  GIVEN("A graph with initialised edges and nodes") {
    std::string s1{"A"};
    std::string s2{"B"};
    std::string s3{"C"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s1, s3, 3);
    auto e4 = std::make_tuple(s1, s3, 10);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "A (\n"
                        "  B | 1\n"
                        "  C | 3\n"
                        "  C | 10\n"
                        ")\n"
                        "B (\n"
                        "  C | 2\n"
                        ")\n"
                        "C (\n"
                        ")\n");

    WHEN("7.1 GetNodes and test from the graph") {
      auto nodes = g.GetNodes();
      REQUIRE(nodes.size() == 3);
      REQUIRE(nodes[0] == "A");
      REQUIRE(nodes[1] == "B");
      REQUIRE(nodes[2] == "C");
      THEN("Check the existence of node") {
        REQUIRE(g.IsNode("A"));
        REQUIRE(g.IsNode("B"));
        REQUIRE(g.IsNode("C"));
        REQUIRE(g.IsNode("Z") == false);
      }
    }

    WHEN("7.2 GetConnected edges between nodes and check if they are connected") {
      auto edges = g.GetConnected("A");
      REQUIRE(edges.size() == 2);
      REQUIRE(edges[0] == "B");
      REQUIRE(edges[1] == "C");
      THEN("Check those nodes are connected") {
        REQUIRE(g.IsConnected("A", "A") == false);
        REQUIRE(g.IsConnected("A", "B"));
        REQUIRE(g.IsConnected("A", "C"));
      }
    }

    WHEN("7.3 GetWeights from an edge") {
      auto edges = g.GetConnected("A");
      REQUIRE(edges.size() == 2);
      REQUIRE(edges[0] == "B");
      REQUIRE(edges[1] == "C");
      THEN("Retrieve the edge betwee A and B") {
        auto weight = g.GetWeights("A", "B");
        REQUIRE(weight.size() == 1);
        REQUIRE(weight[0] == 1);
      }
      THEN("Retrieve the edge betwee A and B") {
        auto weight = g.GetWeights("A", "C");
        REQUIRE(weight.size() == 2);
        REQUIRE(weight[0] == 3);
        REQUIRE(weight[1] == 10);
      }
    }
  }
}

/*
 * 20. Test cbegin() function, How:
 * 1. test the value of begin iterator for a normal graph
 * 2. test the value of begin iterator after remove a node from a graph
 * 3. test the value of begin iterator for a empty graph
 */
SCENARIO("Testing cbegin()") {
  GIVEN("Given a  graph with structure:a->b(1), b->c(2), c->a(3)") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using cbegin() for a normal graph") {
      auto it = g.cbegin();
      THEN("we should get the expected value by this iterator") {
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == 1);
      }
    }

    WHEN("using cbegin() after a node in graph be removed, remove 'b'; begin is in next level of "
         "outer_iterator") {
      g.DeleteNode("b");  // now graph is a->null, c->a(3)

      THEN("we should get c->a(3)") {
        auto it = g.cbegin();
        REQUIRE(std::get<0>(*it) == "c");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 3);
      }
    }

    WHEN("given a new graph with structure: a->b(1), a->c(2), b:{} , c:{}") {
      std::string str1{"a"};
      std::string str2{"b"};
      std::string str3{"c"};
      auto e10 = std::make_tuple(str1, str2, 1);
      auto e20 = std::make_tuple(str1, str3, 2);
      auto es = std::vector<std::tuple<std::string, std::string, double>>{e10, e20};
      gdwg::Graph<std::string, double> temp_graph{es.begin(), es.end()};
      THEN("remove 'b' -> a->null, a->c(2), c:{} ") {
        temp_graph.DeleteNode("b");

        AND_THEN("cbegin() should be a->c(2)") {
          auto it = temp_graph.cbegin();
          REQUIRE(std::get<0>(*it) == "a");
          REQUIRE(std::get<1>(*it) == "c");
          REQUIRE(std::get<2>(*it) == 2);
        }
      }
    }

    WHEN("empty graph") {
      decltype(g) empty;
      THEN("cbegin() == cend()") { REQUIRE(empty.cbegin() == empty.cend()); }
    }
  }
}

/*
 * 21. Test cend() function, How:
 * 1. by testing the distance between cend() and cbegin() == correct size
 * 2. empty
 * 3. non-empty
 * 4. after remove
 */
SCENARIO("Testing cend()") {
  GIVEN("given a graph") {
    gdwg::Graph<std::string, double> g;

    WHEN("graph is empty") {
      THEN("distance of begin() and end() should be 0") {
        REQUIRE(std::distance(g.cbegin(), g.cend()) == 0);
      }
    }
    AND_GIVEN("inser 3 edge into the graph") {
      g.InsertNode("a");
      g.InsertNode("b");
      g.InsertNode("c");
      g.InsertEdge("a", "b", 1);
      g.InsertEdge("b", "c", 2);
      g.InsertEdge("c", "a", 3);

      WHEN("After insert 3 edge in to the graph") {
        THEN("distance should be 3") { REQUIRE(std::distance(g.cbegin(), g.cend()) == 3); }
      }

      WHEN("After remove a edge in graph") {
        g.erase("a", "b", 1);
        THEN("distance should be 2") { REQUIRE(std::distance(g.cbegin(), g.cend()) == 2); }
      }
    }
  }
}

/*
 * 22. Test crbegin() function, How:
 * 1. test the value of rbegin iterator for a normal graph
 * 2. test the value of rbegin iterator after remove a node from a graph
 * 3. test the value of rbegin iterator for a empty graph
 */
SCENARIO("Testing crbegin()") {
  GIVEN("Given a  graph with structure:a->b(1), b->c(2), c->a(3)") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using crbegin() for a normal graph") {
      auto it = g.crbegin();
      THEN("we should get c->a(3)") {
        REQUIRE(std::get<0>(*it) == "c");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 3);
      }
    }

    WHEN("using crbegin() after a node in graph be removed, remove 'c'; begin is in next level of "
         "outer_iterator") {
      g.DeleteNode("c");  // now graph is a->b(1), b->null

      THEN("we should get a->b(1)") {
        auto it = g.cbegin();
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == 1);
      }
    }

    WHEN("given a new graph with structure: a:{}, b:{} , c->a(1), c->b(2)") {
      std::string str1{"a"};
      std::string str2{"b"};
      std::string str3{"c"};
      auto e10 = std::make_tuple(str3, str1, 1);
      auto e20 = std::make_tuple(str3, str2, 2);
      auto es = std::vector<std::tuple<std::string, std::string, double>>{e10, e20};
      gdwg::Graph<std::string, double> temp_graph{es.begin(), es.end()};
      THEN("remove 'b' -> a:{}, c->a(1), c->null(2) ") {
        temp_graph.DeleteNode("b");

        AND_THEN("crbegin() should be c->a(1)") {
          auto it = temp_graph.crbegin();
          REQUIRE(std::get<0>(*it) == "c");
          REQUIRE(std::get<1>(*it) == "a");
          REQUIRE(std::get<2>(*it) == 1);
        }
      }
    }

    WHEN("empty graph") {
      decltype(g) empty;
      THEN("crbegin() == crend()") { REQUIRE(empty.crbegin() == empty.crend()); }
    }
  }
}

/*
 * 23. Test crend() function, How:
 * 1. by testing the distance between cend() and cbegin() == correct size
 * 2. empty
 * 3. non-empty
 * 4. after remove
 */
SCENARIO("Testing crend()") {
  GIVEN("given a graph") {
    gdwg::Graph<std::string, double> g;

    WHEN("graph is empty") {
      THEN("distance of crbegin() and crend() should be 0") {
        REQUIRE(std::distance(g.crbegin(), g.crend()) == 0);
      }
    }

    AND_GIVEN("insert 3 edge into the graph") {
      g.InsertNode("a");
      g.InsertNode("b");
      g.InsertNode("c");
      g.InsertEdge("a", "b", 1);
      g.InsertEdge("b", "c", 2);
      g.InsertEdge("c", "a", 3);

      WHEN("After insert 3 edge in to the graph") {
        THEN("distance should be 3") { REQUIRE(std::distance(g.crbegin(), g.crend()) == 3); }
      }

      WHEN("After remove a edge in graph") {
        g.erase("a", "b", 1);
        THEN("distance should be 2") { REQUIRE(std::distance(g.crbegin(), g.crend()) == 2); }
      }
    }
  }
}

/*
 * 24.Test: const_iterator ++operator()
 *  1. loop through all to compare the src and edge value
 *  2. test postfix operator++ working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test ++end() still == end()

 */
SCENARIO("Test: const_iterator -> ++operator for const_iterator") {
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph") {
      THEN("the result should be the same") {
        auto edge = e.begin();
        for (auto it = g.cbegin(); it != g.cend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("testing postfix ++ operator") {
      auto it = g.begin();
      auto old = it++;
      THEN("it now is b->c(2), and old should be a->b(1)") {
        // check it
        REQUIRE("b" == std::get<0>(*it));
        REQUIRE("c" == std::get<1>(*it));
        REQUIRE(2 == std::get<2>(*it));

        // check old
        REQUIRE("a" == std::get<0>(*old));
        REQUIRE("b" == std::get<1>(*old));
        REQUIRE(1 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b") {
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)") {
        auto edge = edges.begin();
        for (auto it = g.cbegin(); it != g.cend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("++end() is still end()") {
      auto it = g.cend();
      ++it;
      THEN("++it == end()") { REQUIRE(it == g.cend()); }
    }
  }
}

/*
 * 25.Test: const_iterator --operator()
 *  1. loop through all , then compare the src and edge value
 *  2. test postfix operator-- working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test --begin() still == begin()

 */
SCENARIO("Test: const_iterator -> --operator") {
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph") {
      THEN("the result should be the same") {
        auto edge = e.end();
        auto it = g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.cbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("testing postfix -- operator") {
      auto it = g.begin();
      ++it;  // second position
      auto old = it--;
      THEN("it now is a->b(1), and old should be b->c(2)") {
        REQUIRE("a" == std::get<0>(*it));
        REQUIRE("b" == std::get<1>(*it));
        REQUIRE(1 == std::get<2>(*it));

        // check old
        REQUIRE("b" == std::get<0>(*old));
        REQUIRE("c" == std::get<1>(*old));
        REQUIRE(2 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b") {
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)") {
        auto edge = edges.end();
        auto it = g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.cbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("--begin() is still begin()") {
      auto it = g.cbegin();
      --it;
      THEN("--it == cbegin()") { REQUIRE(it == g.cbegin()); }
    }
  }
}

/*
 * 26. test ++ and -- operator work properly
 * 1. ++ and -- randomly
 * 2. test with erase edge
 * 3. test with erase node
 */
SCENARIO("Test ++ and -- randomly, and ensure they work properly") {
  GIVEN("given a normal graph with mutiple edges. check comment for structure") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("end--, then ++") {
      auto it = g.cend();
      --it;
      THEN("it == c->b(8)") {
        REQUIRE("c" == std::get<0>(*it));
        REQUIRE("b" == std::get<1>(*it));
        REQUIRE(8 == std::get<2>(*it));
      }

      AND_WHEN("++it") {
        ++it;
        THEN("it == cend()") { REQUIRE(it == g.cend()); }
      }
    }

    WHEN("loop through--") {
      THEN("check expected value") {
        auto edge = e.cend();
        auto it = g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.cbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("we want to loop through the whole graph by ++") {
      THEN("the result should be the same") {
        auto edge = e.begin();
        for (auto it = g.cbegin(); it != g.cend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    AND_WHEN("remove 'c', now graph is a->b(1), b->a(5)") {
      g.DeleteNode("c");
      auto new_edges = std::vector<std::tuple<std::string, std::string, double>>{e1, e5};
      THEN("loop through the whole graph by ++") {
        auto edge = new_edges.begin();
        for (auto it = g.cbegin(); it != g.cend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }

      THEN("-- loop through") {
        auto edge = new_edges.cend();
        auto it = g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.cbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }
  }
}

/*
 * 27.Test: const_reverse_iterator ++operator()
 *  1. loop through all to compare the src and edge value
 *  2. test postfix operator++ working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test ++end() still == end()

 */
SCENARIO("Test: const_reverse_iterator -> ++operator for const_reverse_iterator") {
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph") {
      THEN("the result should be the same") {
        auto edge = e.crbegin();
        for (auto it = g.crbegin(); it != g.crend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("testing postfix ++ operator") {
      auto it = g.crbegin();
      auto old = it++;
      THEN("it now is b->c(2), and old should be c->a(3)") {
        // check it
        REQUIRE("b" == std::get<0>(*it));
        REQUIRE("c" == std::get<1>(*it));
        REQUIRE(2 == std::get<2>(*it));

        // check old
        REQUIRE("c" == std::get<0>(*old));
        REQUIRE("a" == std::get<1>(*old));
        REQUIRE(3 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b") {
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)") {
        auto edge = edges.crbegin();
        for (auto it = g.crbegin(); it != g.crend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("++crend() is still end()") {
      auto it = g.crend();
      ++it;
      THEN("++it == end()") { REQUIRE(it == g.crend()); }
    }
  }
}

/*
 * 28.Test: const_reverse_iterator --operator()
 *  1. loop through all , then compare the src and edge value
 *  2. test postfix operator-- working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test --crbegin() still == crbegin()

 */
SCENARIO("Test: const_reverse_iterator -> --operator") {
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)") {
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph") {
      THEN("the result should be the same") {
        auto edge = e.crend();
        auto it = g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.crbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("testing postfix -- operator") {
      auto it = g.crbegin();
      ++it;  // second position
      auto old = it--;
      THEN("it now is c->a(3), and old should be b->c(2)") {
        REQUIRE("c" == std::get<0>(*it));
        REQUIRE("a" == std::get<1>(*it));
        REQUIRE(3 == std::get<2>(*it));

        // check old
        REQUIRE("b" == std::get<0>(*old));
        REQUIRE("c" == std::get<1>(*old));
        REQUIRE(2 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b") {
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)") {
        auto edge = edges.crend();
        auto it = g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.crbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("--cbregin() is still crbegin()") {
      auto it = g.crbegin();
      --it;
      THEN("--it == cbegin()") { REQUIRE(it == g.crbegin()); }
    }
  }
}

/*
 * 29. test ++ and -- operator work properly for const_reverse_iterator
 * 1. ++ and -- randomly
 * 2. test with erase edge
 * 3. test with erase node
 */
SCENARIO("Test ++ and -- randomly, and ensure they work properly for const_reverse_iterator") {
  GIVEN("given a normal graph with mutiple edges. check comment for structure") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("end--, then ++") {
      auto it = g.crend();
      --it;
      THEN("it == a->b(1)") {
        REQUIRE("a" == std::get<0>(*it));
        REQUIRE("b" == std::get<1>(*it));
        REQUIRE(1 == std::get<2>(*it));
      }

      AND_WHEN("++it") {
        ++it;
        THEN("it == crend()") { REQUIRE(it == g.crend()); }
      }
    }

    WHEN("loop through--") {
      THEN("check expected value") {
        auto edge = e.crend();
        auto it = g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.crbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("we want to loop through the whole graph by ++") {
      THEN("the result should be the same") {
        auto edge = e.crbegin();
        for (auto it = g.crbegin(); it != g.crend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    AND_WHEN("remove 'c', now graph is a->b(1), b->a(5)") {
      g.DeleteNode("c");
      auto new_edges = std::vector<std::tuple<std::string, std::string, double>>{e1, e5};
      THEN("loop through the whole graph by ++") {
        auto edge = new_edges.crbegin();
        for (auto it = g.crbegin(); it != g.crend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }

      THEN("-- loop through") {
        auto edge = new_edges.crend();
        auto it = g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.crbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }
  }
}

/*
 * 30. Testing == operator
 * 1. for const_iterator
 * 2. for const_reverse_iterator
 */
SCENARIO("Testing == operator") {
  GIVEN("given a graph with structure(check comments)") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using const_iterator and loop through to compare with begin()") {
      auto begin = g.cbegin();
      int i = 0;
      THEN("only the first one == begin(), others all !(it == begin())")
      for (auto it = g.cbegin(); it != g.cend(); ++it) {
        if (i == 0) {
          REQUIRE(begin == it);
        } else {
          REQUIRE(!(begin == it));
        }
        ++i;
      }
    }

    WHEN("using const_reverse_iterator and loop through to compare with rbegin()") {
      auto rbegin = g.crbegin();
      int i = 0;
      THEN("only the first one == rbegin(), others all !(it == rbegin())")
      for (auto it = g.crbegin(); it != g.crend(); ++it) {
        if (i == 0) {
          REQUIRE(rbegin == it);
        } else {
          REQUIRE(!(rbegin == it));
        }
        ++i;
      }
    }
  }
}

/*
 * 31. Testing != operator
 * 1. for const_iterator
 * 2. for const_reverse_iterator
 */
SCENARIO("Testing != operator") {
  GIVEN("given a graph with structure(check comments)") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using const_iterator and loop through to compare with begin()") {
      auto begin = g.cbegin();
      int i = 0;
      THEN("only !(first one != begin()), others all (it != begin())")
      for (auto it = g.cbegin(); it != g.cend(); ++it) {
        if (i == 0) {
          REQUIRE(!(begin != it));
        } else {
          REQUIRE(begin != it);
        }
        ++i;
      }
    }

    WHEN("using const_reverse_iterator and loop through to compare with rbegin()") {
      auto rbegin = g.crbegin();
      int i = 0;
      THEN("only  !(first one != begin()), others all (it != begin())")
      for (auto it = g.crbegin(); it != g.crend(); ++it) {
        if (i == 0) {
          REQUIRE(!(rbegin != it));
        } else {
          REQUIRE(rbegin != it);
        }
        ++i;
      }
    }
  }
}

/*
 * 32. test const_iterator find()
 * with a complex graph structure
 * 1. find the element at very first
 * 2. find the element at middle of first level edgeSet
 * 3. find the element at the last of first level edgeSet
 * 4. find the element at the begin of second level edgeSet
 * 5. find the element at the end of second level edge set
 * 6. find the element at the begin of last level of edgeSet
 * 7. find the element at the very very last
 * 8. cannot find the element will return cend()
 */
SCENARIO("Testing find()") {
  GIVEN("give a complex graph with structure(check comments)") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("1. find a->b(1) ") {
      auto found = g.find(a, b, 1);
      THEN("check the value of found iterator") {
        REQUIRE("a" == std::get<0>(*found));
        REQUIRE("b" == std::get<1>(*found));
        REQUIRE(1 == std::get<2>(*found));
      }
    }

    WHEN("2. find a->c(2) ") {
      auto found = g.find(a, c, 2);
      THEN("check the value of found iterator") {
        REQUIRE("a" == std::get<0>(*found));
        REQUIRE("c" == std::get<1>(*found));
        REQUIRE(2 == std::get<2>(*found));
      }
    }

    WHEN("3. find a->c(4) ") {
      auto found = g.find(a, c, 4);
      THEN("check the value of found iterator") {
        REQUIRE("a" == std::get<0>(*found));
        REQUIRE("c" == std::get<1>(*found));
        REQUIRE(4 == std::get<2>(*found));
      }
    }
    WHEN("4. find b->a(5) ") {
      auto found = g.find(b, a, 5);
      THEN("check the value of found iterator") {
        REQUIRE("b" == std::get<0>(*found));
        REQUIRE("a" == std::get<1>(*found));
        REQUIRE(5 == std::get<2>(*found));
      }
    }
    WHEN("5. find b->c(6) ") {
      auto found = g.find(b, c, 6);
      THEN("check the value of found iterator") {
        REQUIRE("b" == std::get<0>(*found));
        REQUIRE("c" == std::get<1>(*found));
        REQUIRE(6 == std::get<2>(*found));
      }
    }

    WHEN("6. find c->b(7) ") {
      auto found = g.find(c, b, 7);
      THEN("check the value of found iterator") {
        REQUIRE("c" == std::get<0>(*found));
        REQUIRE("b" == std::get<1>(*found));
        REQUIRE(7 == std::get<2>(*found));
      }
    }
    WHEN("7. find c->b(8) ") {
      auto found = g.find(c, b, 8);
      THEN("check the value of found iterator") {
        REQUIRE("c" == std::get<0>(*found));
        REQUIRE("b" == std::get<1>(*found));
        REQUIRE(8 == std::get<2>(*found));
      }
    }

    WHEN("8. cannot find a edge ") {
      auto found = g.find(b, c, 100);
      THEN("return cend()") { REQUIRE(found == g.cend()); }
    }
  }
}

/*
 * 33. Test: const_iterator erase() -> all check its next element
 *  1. erase the element at very first
 * 2. erase the element at middle of first level edgeSet
 * 3. erase the element at the last of first level edgeSet
 * 4. erase the element at the begin of second level edgeSet
 * 5. erase the element at the end of second level edge set
 * 6. erase the element at the begin of last level of edgeSet
 * 7. erase the element at the very very last
 * 8. the element that cannot find to erase ->  will return cend()
 * 9. check after erase, -- and ++ run through that iterator_pos -> work properly
 */
SCENARIO("Testing erase()") {
  GIVEN("give a complex graph with structure(check comments) for each test case") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("1. erase a->b(1) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, b, 1);
      auto next = copy_g.erase(found);
      THEN("then we cannot find a->b(1) anymore, and erase return a->c(2)") {
        // check next element
        REQUIRE("a" == std::get<0>(*next));
        REQUIRE("c" == std::get<1>(*next));
        REQUIRE(2 == std::get<2>(*next));

        REQUIRE(copy_g.find(a, b, 1) == copy_g.cend());
      }
    }

    WHEN("2. erase a->c(2) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, c, 2);
      auto next = copy_g.erase(found);
      THEN("then we cannot find a->c(2) anymore, and erase return a->c(3)") {
        // check next element
        REQUIRE("a" == std::get<0>(*next));
        REQUIRE("c" == std::get<1>(*next));
        REQUIRE(3 == std::get<2>(*next));
        REQUIRE(copy_g.find(a, c, 2) == copy_g.cend());
      }
    }

    WHEN("3. erase a->c(4) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, c, 4);
      auto next = copy_g.erase(found);
      THEN("then we cannot find a->c(4) anymore, and erase return b->a(5)") {
        // check next element
        REQUIRE("b" == std::get<0>(*next));
        REQUIRE("a" == std::get<1>(*next));
        REQUIRE(5 == std::get<2>(*next));
        REQUIRE(copy_g.find(a, c, 4) == copy_g.cend());
      }
    }

    WHEN("4. erase b->a(5) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(b, a, 5);
      auto next = copy_g.erase(found);
      THEN("then we cannot find b->a(5) anymore,and erase return b->c(6) ") {
        // check next element
        REQUIRE("b" == std::get<0>(*next));
        REQUIRE("c" == std::get<1>(*next));
        REQUIRE(6 == std::get<2>(*next));
        REQUIRE(copy_g.find(b, a, 5) == copy_g.cend());
      }
    }

    WHEN("5. erase b->c(6) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(b, c, 6);
      auto next = copy_g.erase(found);
      THEN("then we cannot find b->c(6) anymore,and erase return c->b(7) ") {
        // check next element
        REQUIRE("c" == std::get<0>(*next));
        REQUIRE("b" == std::get<1>(*next));
        REQUIRE(7 == std::get<2>(*next));
        REQUIRE(copy_g.find(b, c, 6) == copy_g.cend());
      }
    }

    WHEN("6. erase c->b(7) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(c, b, 7);
      auto next = copy_g.erase(found);
      THEN("then we cannot find c->b(7) anymore, and erase return c->b(8)") {
        // check next element
        REQUIRE("c" == std::get<0>(*next));
        REQUIRE("b" == std::get<1>(*next));
        REQUIRE(8 == std::get<2>(*next));
        REQUIRE(copy_g.find(c, b, 7) == copy_g.cend());
      }
    }

    WHEN("7. erase c->b(8) ") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(c, b, 8);
      auto next = copy_g.erase(found);
      THEN("then we cannot find c->b(8) anymore, and erase return cend()") {
        REQUIRE(next == copy_g.cend());
        REQUIRE(copy_g.find(c, b, 8) == copy_g.cend());
      }
    }
    WHEN("8. cannot find one to erase ") {
      decltype(g) copy_g{g};
      auto found = copy_g.cend();
      auto result = copy_g.erase(found);
      THEN("we will return cend()") { REQUIRE(result == copy_g.cend()); }
    }

    WHEN("check after erase with -- and ++ through that position") {
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, c, 2);
      auto result = copy_g.erase(found);
      THEN("--result should be a->b(1)") {
        --result;
        REQUIRE("a" == std::get<0>(*result));
        REQUIRE("b" == std::get<1>(*result));
        REQUIRE(1 == std::get<2>(*result));

        AND_THEN("++result will be a->c(3)") {
          ++result;
          REQUIRE("a" == std::get<0>(*result));
          REQUIRE("c" == std::get<1>(*result));
          REQUIRE(3 == std::get<2>(*result));
        }
      }
    }
  }
}

/*
 *  34. Test: const object with iterator
 *  --- 9 to 10 will do const_iterator and const_reverse_iterator together
 *  9. ++ look through whole graph
 *  10. -- look through whole graph
 *  11. find
 *  12. ==
 *  13. !=
 *  -----
 *  1.have cbegin() to call
 *  2.have cend()
 *  3. have begin()
 *  4. have end()
 *  5.have crbegin()
 *  6.have crend()
 *  7. have rbegin()
 *  8. have rend()
 *
 */
SCENARIO("Test const graph with iterator") {
  GIVEN("given a const graph ") {
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e =
        std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3, e4, e5, e6, e7, e8};
    const gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("test case from 1-8. ensure const graph have these iterator function to call") {
      THEN("they should all work properly") {
        REQUIRE_NOTHROW(g.cbegin());
        REQUIRE_NOTHROW(g.cend());
        REQUIRE_NOTHROW(g.begin());
        REQUIRE_NOTHROW(g.end());
        REQUIRE_NOTHROW(g.crbegin());
        REQUIRE_NOTHROW(g.crend());
        REQUIRE_NOTHROW(g.rbegin());
        REQUIRE_NOTHROW(g.rend());
      }
    }

    WHEN("9. use ++ to look through for const_iterator") {
      THEN("we should get whatever the value we expected") {
        auto edge = e.cbegin();
        for (auto it = g.cbegin(); it != g.cend(); ++it) {
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }

      AND_WHEN("++ look through by const_reverse_iterator") {
        THEN("we still get the expected value") {
          auto edge = e.crbegin();
          for (auto it = g.crbegin(); it != g.crend(); ++it) {
            REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
            REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
            REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
            ++edge;
          }
        }
      }
    }

    WHEN("10. loop through-- by const_iterator") {
      THEN("check expected value") {
        auto edge = e.cend();
        auto it = g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for (; it != g.cbegin(); --it) {  // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        // compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }

      AND_WHEN("loop through-- by const_reverse_iterator") {
        THEN("check expected value") {
          auto edge = e.crend();
          auto it = g.crend();
          std::advance(it, -1);
          std::advance(edge, -1);
          for (; it != g.crbegin(); --it) {  // compare from last element to begin-1
            REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
            REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
            REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
            --edge;
          }
          // compare begin element
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
        }
      }
    }

    WHEN("11. const obeject call find()") {
      THEN("work properly") { REQUIRE_NOTHROW(g.find(a, b, 1)); }
    }

    WHEN("12. const obeject call == operator for const_iterator and const_reverse_iterator") {
      THEN("work properly") {
        REQUIRE_NOTHROW(g.cbegin() == g.cbegin());
        REQUIRE_NOTHROW(g.crbegin() == g.crbegin());
        REQUIRE_NOTHROW(g.cend() == g.cend());
        REQUIRE_NOTHROW(g.crend() == g.crend());
      }
    }

    WHEN("13. const obeject call != operator for const_iterator and const_reverse_iterator") {
      THEN("work properly") {
        REQUIRE_NOTHROW(g.cend() != g.cbegin());
        REQUIRE_NOTHROW(g.crend() != g.crbegin());
        REQUIRE_NOTHROW(g.cbegin() != g.cend());
        REQUIRE_NOTHROW(g.crbegin() != g.crend());
      }
    }
  }
}
