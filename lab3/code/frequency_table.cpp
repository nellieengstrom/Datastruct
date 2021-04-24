#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

//#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
    // ADD CODE: exercise 3
};


// Add other stuff, if needed

#endif

void exercise3() {
#ifdef TEST_EXERCISE3
    {
        std::ifstream file("../code/text.txt");  // contains 56 unique words
        // std::ifstream file("../code/text_long.txt"); // contains 497 unique words

        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
            // std::cout << "Couldn't open file text_long.txt\n";
            return;
        }

        // ADD CODE: exercise 3

    }
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}