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
        temp->next = temp->next;
    }
}

// Make the set empty
void Set::make_empty() {
    Node* temp = head;

    while (!is_empty()) {
        _remove(temp->next);
        temp->next = temp->next->next;
    }
}

Set::~Set() {
    // Member function make_empty() can be used to implement the destructor
    if (!is_empty()) {
        make_empty(); //är detta rätt?
    }

    //Måste man ha typ head->next = nullptr och tail->next = nullptr?
    delete head;
    delete tail;
}

// Copy constructor
Set::Set(const Set& source)
    : Set{}  // create an empty list
{
    Node* p_new = head;
    Node* p_source = source.head->next;

    while (p_source != nullptr) {
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

    Node* temp = head;
    while (temp->next != nullptr && temp->next->value != val) {
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
    

    return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
    // IMPLEMENT

    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
    // IMPLEMENT

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


