#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

//#define TEST_ITERATOR

/* *********************************************
 * Test 3: Iterator
 ********************************************* */

void test3() {
#ifdef TEST_ITERATOR
    {
        std::ifstream file{"../code/words.txt"};

        if (!file) {
            std::cout << "Couldn't open file words.txt\n";
            return;
        }

        // Read all words in the file into a vector
        std::vector<std::string> V{std::istream_iterator<std::string>{file},
                                   std::istream_iterator<std::string>{}};
        file.close();

        // Create a tree
        BinarySearchTree<std::string> t;
        assert(BinarySearchTree<std::string>::get_count_nodes() == 0);

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<std::string>::get_count_nodes() == 35);

        // Display the tree
        /*std::cout << "Tree: \n";
        t.printTree();
        std::cout << '\n';*/

        // Load the expected inorder traversal of the tree
        file.open("../code/inorder_traversal.txt");

        if (!file) {
            std::cout << "Couldn't open file inorder_traversal.txt\n";
            return;
        }

        std::vector<std::string> inorder{std::istream_iterator<std::string>{file},
                                         std::istream_iterator<std::string>{}};
        file.close();

        /**************************************/
        std::cout << "\nPHASE 0: find\n";
        /**************************************/
        {
            // some words in the tree
            std::vector<std::string> V1{"airborne", "yelp", "obligations", "unbridled"};

            for (auto w : V1) {
                assert(*t.find(w) == w);
            }

            std::vector<std::string> V2{"stop", "Sweden"};

            // some words not in the tree
            for (auto w : V2) {
                assert(t.find(w) == t.end());
            }
        }

        /****************************************************/
        std::cout << "\nPHASE 1: operator++, operator*\n";
        /****************************************************/
        {
            std::vector<std::string> V1{};

            // Inorder traversal
            /* for (BinarySearchTree<string>::Iterator it = t.begin(); it != t.end(); ++it) {
                 V1.push_back(*it);
             }*/

            // Inorder traversal
            for (auto w : t) {
                V1.push_back(w);
            }

            assert(V1 == inorder);
        }

        /****************************************************/
        std::cout << "\nPHASE 2: operator--, operator*\n";
        /*****************************************************/
        {
            std::string largest{t.findMax()};

            assert(largest == "yelp");

            std::vector<std::string> V1{};

            // Backwards inorder traversal
            for (auto it = t.find(largest); it != t.end(); --it) {
                V1.push_back(*it);
            }

            std::sort(V1.begin(), V1.end());
            assert(V1 == inorder);
        }

        /*****************************************************************/
        std::cout << "\nPHASE 3: test iterators with STL algorithms\n";
        /*****************************************************************/

        std::vector<std::string> V1{};

        // Copy the tree in inorder into a vector
        std::copy(t.begin(), t.end(), std::back_inserter(V1));

        assert(V1 == inorder);

        auto f = [](const std::string& s) {
            return std::find(s.begin(), s.end(), '\'') != s.end();
        };

        // Check if there are three words in BST t with char '\''
        assert(std::count_if(t.begin(), t.end(), f) == 3);
    }

    assert(BinarySearchTree<std::string>::get_count_nodes() == 0);

    std::cout << "\nSuccess!!\n";
#endif
}
