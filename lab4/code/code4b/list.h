/*********************************************
 * file:	~\lab4b\list.h                    *
 * remark: interface for adjacency lists      *
 **********************************************/
#pragma once

class Node {
public:
    // -- CONSTRUCTORS
    Node(int v = 0, int w = 0, Node *n = nullptr) : vertex{v}, weight{w}, next{n} {
    }

    // -- DATA MEMBERS
    int vertex;
    int weight;
    Node *next;
};

class List {
public:
    // -- CONSTRUCTORS
    List();

    // -- DESTRUCTOR
    ~List();

    // -- Copy constructor
    List(const List &);

    // -- Assignment operator
    List &operator=(List L);

    // -- MEMBER FUNCTIONS

    // return pointer to first node (or nullptr)
    Node *getFirst() const;

    // return pointer to next node (or nullptr)
    Node *getNext() const;

    // insert vertex v in sorted order
    // update weight w if v is present
    void insert(int v, int w);

    // remove vertex v
    void remove(int v);

    // print list
    void print() const;

private:
    // -- DATA MEMBERS
    Node *header;
    mutable Node *current;
};
