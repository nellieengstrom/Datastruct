/*********************************************
 * file:	~\lab4a\list.cpp                  *
 * remark: implementation of adjacency lists  *
 **********************************************/

#include <iostream>
#include <iomanip>

// using namespace std;

#include "list.h"

// -- CONSTRUCTOR
List::List() : header{new Node{}}, current{header->next} {
    // The list has a dummy node at the head
}

// -- DESTRUCTOR
List::~List() {
    while (header != nullptr) {
        Node *temp = header;
        header = temp->next;
        delete temp;
    }
    header = current = nullptr;
}

// -- Copy constructor
List::List(const List &L) : List() {
    Node *sourcePtr = L.header->next;
    Node *newNode = header;

    while (sourcePtr != nullptr) {
        newNode->next = new Node(sourcePtr->vertex, sourcePtr->weight, nullptr);

        if (L.current == sourcePtr) {
            current = newNode;
        }

        newNode = newNode->next;
        sourcePtr = sourcePtr->next;
    }
}

// -- Assignment operator
List &List::operator=(List L) {
    std::swap(header, L.header);
    std::swap(current, L.current);

    return *this;
}

// -- MEMBER FUNCTIONS

// return pointer to first node (or nullptr)
Node *List::getFirst() const {
    current = header->next;
    return current;
}

// return pointer to next node (or nullptr)
Node *List::getNext() const {
    if (current != nullptr) {
        current = current->next;
    }
    return current;
}

// insert vertex v in sorted order
// update weight w if v is present
void List::insert(int v, int w) {
    Node *p = header;

    while (p->next != nullptr && p->next->vertex < v) {
        p = p->next;
    }

    if (p->next == nullptr || p->next->vertex > v) {
        p->next = new Node{v, w, p->next};
    } else {
        p->next->weight = w;
    }
    current = header->next;
}

// remove vertex v
void List::remove(int v) {
    Node *p = header;

    while (p->next != nullptr && p->next->vertex < v) {
        p = p->next;
    }

    if (p->next != nullptr && p->next->vertex == v) {
        Node *temp = p->next;
        p->next = temp->next;
        delete temp;
    }
    current = header->next;
}

// print list
void List::print() const {
    Node *p = header->next;

    while (p != nullptr) {
        std::cout << " (" << std::setw(2) << p->vertex << ", " << std::setw(2) << p->weight << ") ";
        p = p->next;
    }
    std::cout << '\n';
}
