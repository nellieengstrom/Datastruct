#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>

class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&
    /* ****************************************************************** */
 
    //Constuctor
    Iterator() : current{nullptr} {}

    Comparable& operator*() const {
        return current->element;
    }

    Comparable* operator->() const { //Gives a reference to the value
        return &(current->element); 
    }

    bool operator==(const Iterator& it) const {
        if (current == it.current) { //Compares the pointers to the nodes
            return true;
        }
        else { return false; }
    }

    bool operator!=(const Iterator& it) const {
        if (*this == it) {
            return false;
        }
        else {
            return true;
        }
    }
    
    Iterator& operator++() { //pre-increment, returns a reference after the 
        current = BST->find_successor(current);
        return *this;
    }
    
    Iterator operator++(int) { //post-increment, returns a copy to the old value. Changes the value but uses the original value.
        Iterator oldIt = *this; //stores the old value
        current = BST->find_successor(current); //moves this->current
        return oldIt; //returns the old value
    }    
       
    Iterator& operator--() { //pre-decrement, returns a reference ...
        current = BST->find_predecesor(current);
        return *this;
    }
    Iterator operator--(int) { //post-increment, returns a copy to the old value. Changes the value but uses the original value.
        Iterator oldIt = *this; //stores the old value
        current = BST->find_predecesor(current); //moves this->current
        return oldIt; //returns the old value
    }
        
private:
    Node* current;
    BinarySearchTree* BST = nullptr; 

    Iterator(Node* t, BinarySearchTree* tree) : current{ t }, BST{tree} {}


    template <typename Comparable>
    friend class BinarySearchTree;
};