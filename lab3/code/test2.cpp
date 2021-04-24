#include <iostream>
#include <vector>
#include <cassert>

#include "BinarySearchTree.h"

//#define TEST_PRED_SUCC

/* *********************************************
 * Test 2: find_pred_succ
 ********************************************* */

void test2() {
#ifdef TEST_PRED_SUCC

    /*********************************************/
    std::cout << "\nPHASE 0: find_pred_succ\n";
    /*********************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        auto p = t.find_pred_succ(12);
        assert(p.first == 10);   // pred
        assert(p.second == 14);  // suc

        p = t.find_pred_succ(13);
        assert(p.first == 12);   // pred
        assert(p.second == 14);  // suc

        p = t.find_pred_succ(15);
        assert(p.first == 14);   // pred
        assert(p.second == 20);  // suc

        p = t.find_pred_succ(28);
        assert(p.first == 25);   // pred
        assert(p.second == 30);  // suc

        p = t.find_pred_succ(35);  // largest value in the tree
        assert(p.first == 33);
        assert(p.second == 35);

        p = t.find_pred_succ(5);  // smallest value in the tree
        assert(p.first == 5);
        assert(p.second == 10);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /****************************************************/
    std::cout << "\nPHASE 1: remove & find_pred_succ\n";
    /****************************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        // Add values to the tree
        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        // Remove some values
        for (int i = 0; i < 35; i += 2) {
            t.remove(i);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 5);

        std::vector<int> V1{10, 12, 14, 20, 30};  // the removed values

        for (auto j : V1) {
            assert(t.contains(j) == false);
        }

        std::vector<int> V2{5, 15, 25, 33, 35};

        for (auto j : V2) {
            assert(t.contains(j));
        }

        auto p = t.find_pred_succ(12);
        assert(p.first == 5);    // pred
        assert(p.second == 15);  // suc

        p = t.find_pred_succ(13);
        assert(p.first == 5);    // pred
        assert(p.second == 15);  // suc

        p = t.find_pred_succ(15);
        assert(p.first == 5);    // pred
        assert(p.second == 25);  // suc

        p = t.find_pred_succ(28);
        assert(p.first == 25);   // pred
        assert(p.second == 33);  // suc

        p = t.find_pred_succ(35);
        assert(p.first == 33);   // pred
        assert(p.second == 35);  // suc

        p = t.find_pred_succ(5);
        assert(p.first == 5);    // pred
        assert(p.second == 15);  // suc

        p = t.find_pred_succ(100);  // find pred/suc of a value larger than any value in the tree
        assert(p.first == 35);      // pred
        assert(p.second == 100);    // suc

        p = t.find_pred_succ(1);  // find pred/suc of a value smaller than any value in the tree
        assert(p.first == 1);     // pred
        assert(p.second == 5);    // suc
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif
}
