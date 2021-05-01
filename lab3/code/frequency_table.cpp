#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
    std::string key;
    int counter = 0; 
    //We need operator< so BST knows if its going traverse left or right
    bool operator<(const Row& rhs) {
        if (this->key < rhs.key) {
            return true;
        }
        else {
            if (this->key == rhs.key) {
                ++counter;
            }
            return false;
        }
    }
};

const std::string punc_sign(".,!?:\"();");

bool allowed_char(const char& c){
    if (std::find(punc_sign.begin(), punc_sign.end(), c) != punc_sign.end()) {
        return false;
    }
    else {
        return true;
    }
}

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

        BinarySearchTree<Row> freqtable;
        int counter = 0;

        std::string word;
        while (file >> word) {
            Row result;
            std::transform(word.begin(), word.end(), word.begin(), [](unsigned char& c) {return c = std::tolower(c); }); // to lower case
            std::copy_if(word.begin(), word.end(), back_inserter(result.key), allowed_char); // remove punctuations
            //Insert the corrected string in the tree
            freqtable.insert(result);
            ++counter;
        }


    }
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}