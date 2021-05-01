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
    int counter = 1; 
    //We need operator< so BST knows if its going traverse left or right
    bool operator<(const Row &rhs) const {
        if (key < rhs.key) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator>=(const Row& rhs) const {
        if (key >= rhs.key) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator==(const Row& rhs) const {
        if (key == rhs.key && counter == rhs.counter) {
            return true;
        }
        else {
            return false;
        }
    }

    void increment() {
        ++counter;
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
        BinarySearchTree<Row>::Iterator it;

        std::string word;
        while (file >> word) {
            Row result;
            std::transform(word.begin(), word.end(), word.begin(), [](char& c) {return c = std::tolower(c); }); // to lower case
            std::copy_if(word.begin(), word.end(), back_inserter(result.key), allowed_char); // remove punctuations
            //Insert the corrected string in the tree
            it = freqtable.find(result);
            if (it != freqtable.end()){
                it->increment();
            }
            else {
                freqtable.insert(result);
            }
        }
        //freqtable.printTree();

         

        std::vector<Row> vector_table;
        std::copy(freqtable.begin(), freqtable.end(), back_inserter(vector_table));
        
        //print vector
        //std::copy(vector_table.begin(), vector_table.end(), std::ostream_iterator<Row>(std::cout, "\n"));

        //Read the solution and insert to vector
        std::ifstream fileTest("../code/frequency_table.txt");

        std::vector<Row> vector_test;
        std::string a;
        int b;

        // load expected frequency table sorted alphabetically
        while (fileTest >> a >> b) {
            Row testResult;
            testResult.key = a;
            testResult.counter = b;
            vector_test.push_back(testResult);
        }

        //print vector
        //std::copy(vector_test.begin(), vector_test.end(), std::ostream_iterator<Row>(std::cout, "\n"));

        assert(vector_table == vector_test);
    }

	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}

std::ostream& operator<<(std::ostream& os, const Row& R) {
    os << R.key << "    " << R.counter;
    return os;
}