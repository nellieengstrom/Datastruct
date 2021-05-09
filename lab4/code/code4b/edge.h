/*********************************************
* file:	~\lab4b\edge.h                       *
* remark: interface for (explicit) edges     *
**********************************************/

#pragma once

#include <utility>

using namespace std::rel_ops; //deprecated in C++20

class Edge
{
public:
    // -- CONSTRUCTORS
    Edge(int u = 0, int v = 0, int w = 0)
		: head{ u }, tail{ v }, weight{ w } { }

    // -- RELATIONAL OPERATORS
    bool operator< (const Edge &e) const;
    bool operator==(const Edge &e) const;

    // -- FRIENDS
    friend std::ostream & operator<< (std::ostream &os, const Edge &e);

    // -- DATA MEMBERS
    int head;
    int tail;
    int weight;
};
