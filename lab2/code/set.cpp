#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes
// Return number of existing nodes  -- static member function
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{ 0 }, head{ new Node }, tail{ new Node } {
    head->next = tail;
    tail->prev = head;
}

// Conversion constructor
Set::Set(int n)
    : Set{} {  // create an empty list
    _insert(head, n);
}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v)
    : Set{} {  // create an empty list
    Node* temp = head; 
    for (int i = 0; i < size(v); i++ ){
        _insert(temp, v[i]);
        temp = temp->next;
    }
}

// Make the set empty
void Set::make_empty() {
    Node* temp = head;

    while (!is_empty()) {
        _remove(temp->next);
    }
}

Set::~Set() {
    // Member function make_empty() can be used to implement the destructor
    if (!is_empty()) {
        make_empty();
    }
    //Måste man ha head->next = nullptr och tail->next = nullptr?
    delete head;
    delete tail;
}

// Copy constructor
Set::Set(const Set& source)
    : Set{}  // create an empty list
{
    Node* p_new = head;
    Node* p_source = source.head->next;

    while (p_source != source.tail) {
        _insert(p_new, p_source->value);
        p_new = p_new->next;
        p_source = p_source->next;
    }
}


// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {
    //swap: constant if non-array but linear if array
    std::swap(counter, source.counter);
    std::swap(head, source.head);
    std::swap(tail, source.tail);

    return *this;
}

// Test set membership
bool Set::is_member(int val) const {
    if (is_empty()) {
        return false;
    }

    Node* temp = head->next;
    while (temp->next != tail && temp->value < val) {
        temp = temp->next;
    }

    if (temp->value == val) {
        return true;
    }
    else {
        return false;
    }
}

// Test whether a set is empty
bool Set::is_empty() const {
    return (counter == 0);
}


// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}


// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    Node* lhs_p = head->next;
    Node* rhs_p = S.head->next;

    while (rhs_p != S.tail) {
        if (lhs_p == tail) { // at the end of lhs, insert remaining nodes of rhs into lhs
            _insert(lhs_p->prev, rhs_p->value);
            rhs_p = rhs_p->next;
        }
        else if (lhs_p->value == rhs_p->value) { //value are in both sets, move pointers forward
            lhs_p = lhs_p->next;
            rhs_p = rhs_p->next;
        }
        else if (rhs_p->value < lhs_p->value) { //rhs_p points to value that is smallers, insert it and move both forward
            _insert(lhs_p->prev, rhs_p->value);
            rhs_p = rhs_p->next;    
        }
        else { //Rhs_p points to value that is higher, move lhs_p forward
            lhs_p = lhs_p->next;
        }
    }
    return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
    Node* lhs_p = head->next;
    Node* rhs_p = S.head->next;

    while (lhs_p != tail) {
        if (rhs_p == S.tail) { //if we have reached the end of rhs, remove the last remaining nodes in lhs
            lhs_p = lhs_p->next;
            _remove(lhs_p->prev);
        }
        else if (lhs_p->value == rhs_p->value) { //value are in both sets, move pointers forward
            lhs_p = lhs_p->next;
            rhs_p = rhs_p->next;
        }
        else if (rhs_p->value < lhs_p->value) { //rhs_p points to value that is smallers, move rhs_p forward
            rhs_p = rhs_p->next;
        }
        else { //Rhs_p points to value that is bigger, move lhs_p forward and remove the node behind it
            lhs_p = lhs_p->next;
            _remove(lhs_p->prev);
        }
    }
    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
    Node* lhs_p = head->next;
    Node* rhs_p = S.head->next;

    while (lhs_p != tail && rhs_p != S.tail) {
        if (lhs_p->value == rhs_p->value) { //value are in both sets, move both pointer forward and remove node behind lhs_p
            lhs_p = lhs_p->next;
            rhs_p = rhs_p->next;
            _remove(lhs_p->prev);
        }
        else if (rhs_p->value < lhs_p->value) { //rhs_p points to value that is smallers, move rhs_p forward
            rhs_p = rhs_p->next;
        }
        else { //Rhs_p points to value that is bigger, move lhs_p forward because its unique
            lhs_p = lhs_p->next;
        }
    }
    return *this;
}

// Overloaded stream insertion operator<<
std::ostream& operator<<(std::ostream& os, const Set& b) {
    if (b.is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{b.head->next};

        os << "{ ";
        while (temp != b.tail) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

// Overloaded subset operator<=
// True if S1 s a subset of S2, all nodes in S1 are in S2
bool operator<=(const Set& S1, const Set& S2) {
    Set::Node* lhs_p = S1.head;
    Set::Node* rhs_p = S2.head;

    while (lhs_p != S1.tail) {
        if (rhs_p == S2.tail) {
            return false;
        }
        else if (lhs_p->value == rhs_p->value) {
            lhs_p = lhs_p->next;
            rhs_p = rhs_p->next;

        }
        else if (lhs_p->value > rhs_p->value) {
            rhs_p = rhs_p->next;
        }
        else {
            return false;
        }
    }
    return true;
}

// Overloaded proper subset operator<
// True if S1 s a subset of S2, but also contains atleast one additional element 
bool operator<(const Set& S1, const Set& S2) {
    if (S1 <= S2) {
        if (S2.cardinality() > S1.cardinality()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

// Overloaded Subset of each other operator==
// True if S1 is S2 
bool operator==(const Set& S1, const Set& S2) {
    if (S1 <= S2) {
        if (S2.cardinality() == S1.cardinality()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

// Overloaded not equal operator!=
// True if S1 is different from S2
bool operator!=(const Set& S1, const Set& S2) {
    if (S1 == S2) {
        return false;
    }
    else {
        return true;
    }
}
/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

//If you add any private member functions to class Set then write the implementation here

// Insert a new Node storing val after the Node pointed by p
void Set::_insert(Node* p, int val) {
    Node* newNode = new Node(val, p->next, p);
    p->next = p->next->prev = newNode;
    counter++;
}


// Remove the Node pointed by p
void Set::_remove(Node* p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->prev = p->next = nullptr;
    delete p;
    counter--;
}


