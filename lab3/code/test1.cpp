#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

#include "BinarySearchTree.h"

#define TEST_PARENT

/* *********************************************
 * Test 1: get_parent
 ********************************************* */

void test1() {
    /*************************************************/
    std::cout << "PHASE 0: insert, printTree, ";
    std::cout << "findMin, FindMax\n\n";
    /*************************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        // Display the tree
        std::cout << "Tree: \n";
        t.printTree();
        std::cout << '\n';

        assert(t.findMin() == 5);
        assert(t.findMax() == 35);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nPHASE 1: contains\n";
    /**************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        std::vector<int> V1{2, 4, 6, 8, 16, 18, 22, 24, 26, 28, 52};

        for (auto j : V1) {
            assert(t.contains(j) == false);
        }

        std::vector<int> V2{10, 12, 14, 20, 30, 33, 35};

        for (auto j : V2) {
            assert(t.contains(j));
        }
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /***********************************************/
    std::cout << "\nPHASE 2: copy constructor\n";
    /***********************************************/
    {
        BinarySearchTree<int> t1;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t1.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        BinarySearchTree<int> t2{t1};

        assert(BinarySearchTree<int>::get_count_nodes() == 20);

        // Compare trees t1 and t2 -- should be equal
        std::ostringstream os1;
        t1.printTree(os1);

        std::ostringstream os2;
        t2.printTree(os2);

        assert(os1.str() == os2.str());
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nPHASE 3: makeEmpty\n";
    /**************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        t.makeEmpty();
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::ostringstream os;
        t.printTree(os);
        assert(os.str() == "Empty tree");
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nPHASE 4: operator=\n";
    /**************************************/
    {
        BinarySearchTree<int> t1;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V1{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V1) {
            t1.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        std::ostringstream os1;
        t1.printTree(os1);

        t1 = t1;  // self-assignment

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        std::ostringstream os2;
        t1.printTree(os2);
        assert(os1.str() == os2.str());

        /* ********************* */

        BinarySearchTree<int> t2;
        std::vector<int> V2{33, -6, 8};

        for (auto j : V2) {
            t2.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 13);

        t2 = t1;

        assert(BinarySearchTree<int>::get_count_nodes() == 20);

        // Compare trees t1 and t2 -- should be equal
        std::ostringstream os3;

        t2.printTree(os3);
        assert(os1.str() == os3.str());
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

#ifdef TEST_PARENT

    /**************************************/
    std::cout << "\nPHASE 5: get_parent\n";
    /**************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        assert(t.get_parent(14) == 12);
        assert(t.get_parent(10) == 20);
        assert(t.get_parent(33) == 35);
        assert(t.get_parent(20) == 0);
        assert(t.get_parent(28) == 0);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

#endif

    /**************************************/
    std::cout << "\nPHASE 6: remove\n";
    /**************************************/
    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        for (int i = 0; i < 35; i += 2) {
            t.remove(i);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 5);

        std::vector<int> V1{10, 12, 14, 20, 30};

        for (auto j : V1) {
            assert(t.contains(j) == false);
        }

        std::vector<int> V2{5, 15, 25, 33, 35};

        for (auto j : V2) {
            assert(t.contains(j));
        }
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

#ifdef TEST_PARENT

    /**********************************************************/
    std::cout << "\nPHASE 7: get_parent & clone & remove \n";
    /**********************************************************/
    // To test that after cloning the parent pointer is not pointing
    // to the nodes in the original tree
    {
        BinarySearchTree<int> t1;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30};

        for (auto j : V) {
            t1.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 3);

        BinarySearchTree<int> t2{t1};

        assert(BinarySearchTree<int>::get_count_nodes() == 6);

        t1.remove(20);
        t1.remove(10);
        t1.remove(30);

        assert(BinarySearchTree<int>::get_count_nodes() == 3);

        assert(t2.get_parent(10) == 20);
        assert(t2.get_parent(30) == 20);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

    /*****************************************************/
    std::cout << "\nPHASE 8: get_parent after remove\n";
    /*****************************************************/
    /* Test pointers to the parent node after the remove */

    {
        BinarySearchTree<int> t;
        assert(BinarySearchTree<int>::get_count_nodes() == 0);

        std::vector<int> V{20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : V) {
            t.insert(j);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 10);

        // Remove some nodes
        for (int i = 0; i < 35; i += 2) {
            t.remove(i);
        }

        assert(BinarySearchTree<int>::get_count_nodes() == 5);

        assert(t.get_parent(5) == 15);
        assert(t.get_parent(15) == 25);
        assert(t.get_parent(25) == 0);
        assert(t.get_parent(33) == 35);
        assert(t.get_parent(35) == 25);
    }

    assert(BinarySearchTree<int>::get_count_nodes() == 0);

#endif

    std::cout << "Success!!\n";
}
