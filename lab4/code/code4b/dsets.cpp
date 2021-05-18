/*********************************************
 * file:	~\lab4b\dsets.cpp                 *
 * remark: implementation of disjoint sets    *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>

#include "dsets.h"

// -- CONSTRUCTORS

DSets::DSets(int theSize) {
    assert(theSize > 0);
    size = theSize;
    array = new int[size + 1];
    init();
}

// -- DESTRUCTOR

DSets::~DSets() {
    delete[] array;
    array = nullptr;
    size = 0;
}

// -- MEMBER FUNCTIONS

// create initial sets
void DSets::init() {
    for (int i = 1; i <= size; i++) {
        array[i] = -1;  // every disjoint set has one node -- singleton
    }
}

// join sets named r and s where r != s
// i.e. join trees with roots r and s
void DSets::join(int r, int s) {
    assert(r != s);
    assert(r >= 1 && r <= size);
    assert(s >= 1 && s <= size);
    assert(array[r] < 0);
    assert(array[s] < 0);

    // simple union
    //array[r] = s;

    // *** TODO ***
    // Do Union by Size
    if(array[r] < array[s]){ //r is deeper
        array[s] = r; //Make r new root
    }
    else {

        if (array[s] == array[r]) {
            --array[s]; //Update height if same
        }
        array[r] = s; //Make s new root
    }
}

// return name of current set for x
// i.e. return root of tree for x
int DSets::find(int x) {
    assert(x >= 1 && x <= size);

    // simple find
    /*if (array[x] < 0) {
        return x;
    } else {
        return find(array[x]);
    }*/

    // *** TODO ***
    // find with path compression
    if (array[x] < 0) {
        return x;
    }

    else {
        return array[x] = find(array[x]);
    }


}

// just in case ...
void DSets::print() const {
    std::cout << "\n";

    for (int i = 1; i <= size; i++) {
        std::cout << std::setw(4) << i;
    }

    std::cout << "\n";

    for (int i = 1; i <= size; i++) {
        std::cout << std::setw(4) << array[i];
    }

    std::cout << "\n";
}
