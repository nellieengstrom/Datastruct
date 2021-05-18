/*********************************************
 * file:	~\lab4a\digraph.cpp               *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>


#include "digraph.h"
#include "queue.h"

// NOTE: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

Digraph::Digraph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
    dist.resize(size + 1);
    path.resize(size + 1);
    done.resize(size + 1);
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<std::tuple<int, int, int>> &V, int n) : Digraph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);

    n_edges += 1;
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v); //table[u] is a list with all edges of node u

    n_edges -= 1;
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }
    Queue<int> Q; 

    for (int i = 1; i < table.size(); i++) {
        dist[i] = -1; //intial value for all vertexes
        path[i] = 0;
    }

    dist[s] = 0; //choose starting point
    Q.enqueue(s); //puts the starting point at the back of the Queue
 
    //while there is still vertexes not visited
    while (!Q.isEmpty()) {
        int v = Q.getFront(); //Takes the front element and store in v
        Q.dequeue(); //Removes that element from the Queue

        Node* u = table[v].getFirst(); //get pointer to first element of list (adjancent)

        //Goes through the adjacent vertexes of the first element
        while (u != nullptr) {
            if (dist[u->vertex] == -1) { // Not already marked
                dist[u->vertex] = dist[v] + 1; //distance is former nodes distance + 1 (unweighted)
                path[u->vertex] = v; //the path is the former node
                Q.enqueue(u->vertex); //puts the adjancent vertex in the back of the Queue
            }
            u = table[v].getNext(); //next adjancent vertex
        }

    }
}

// positive weighted single source shortest paths
// Dijktra�s algorithm, here done[] vector is used to mark. Do not use a Queue
// So we have no cycles
void Digraph::pwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }

    for (int i = 1; i < table.size(); i++) {
        dist[i] = std::numeric_limits<int>::max(); //inital values
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0; //set the starting point
    done[s] = true; //its visited

    int v = s;

    while (true) {
        Node* u = table[v].getFirst(); //get pointer to first element of list (adjancent)
        while (u != nullptr) {
            //Whats the cost of reaching node u coming from v, compared to the cost we already have
            if (!(done[u->vertex]) && (dist[u->vertex] > dist[v] + u->weight)) {
                dist[u->vertex] = dist[v] + u->weight; //if smaller, then replace it
                path[u->vertex] = v; //best path is now reaching u coming from v
            } 
            u = table[v].getNext();
        }

        //The ones not already visited, find the smallest distance.
        v = find_smallest_undone_distance_vertex();
        if (v == 0) { //if there is no unvisited, then exit
            break;
        }
        done[v] = true; //the v is set to visited
    }
}

// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                  \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " :" << std::setw(8)
                  << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                  << path[v] << "\n";
    }

    std::cout << "----------------------\n";
}

// print shortest path from s to t
void Digraph::printPath(int t) const {
    if (t < 1 || t > size) {
        std::cout << "\nERROR: expected target t in range 1.." << size << " !\n";
        return;
    }
    int distance = dist[t];
    std::vector<int> V;
    V.reserve(5); //reserve memory in vector

    while (!(path[t] == 0)) //while path is not 0
    {
        V.push_back(t); //saves t into the vector
        t = path[t]; //moves t to the next vertex, next index
    }
    V.push_back(t); //extra push_back because the start vertex has path 0

    for (int i = V.size()-1; i >= 0; i--) { //then just cout the vector, backwards
        std::cout << " " << V[i] << " ";
    }
    std::cout << "(" << distance << ")" << std::endl;
}

int Digraph::find_smallest_undone_distance_vertex() const
{
    int smallest = 0;
    int index = 0;
    int i = 1;
    while (i < dist.size()) {
        //Checks that the vertex is unvisited and smallest = 0, its the first time
        //or its unvisited and the distance is smaller than the latest smallest
        if (((!done[i]) && smallest == 0) || ((!done[i]) && dist[i] < smallest)) {
            index = i; //want to return its index
            smallest = dist[i];
        }
        ++i;
    }
    return index;
}
