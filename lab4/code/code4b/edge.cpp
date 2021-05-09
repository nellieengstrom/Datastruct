/*********************************************
 * file:	~\lab4b\edge.cpp                  *
 * remark: implementation of (explicit) edges *
 **********************************************/

#include <iostream>
#include <iomanip>

#include "edge.h"

// -- RELATIONAL OPERATORS

bool Edge::operator<(const Edge &e) const {
    return weight < e.weight;
}

bool Edge::operator==(const Edge &e) const {
    return weight == e.weight;
}

// -- FRIENDS

std::ostream &operator<<(std::ostream &os, const Edge &e) {
    os << "(" << std::setw(2) << e.head << ", " << std::setw(2) << e.tail << ", " << std::setw(2)
       << e.weight << ") ";

    return os;
}
