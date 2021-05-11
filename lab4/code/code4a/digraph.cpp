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
        dist[i] = -1;
        path[i] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s);

    while (!Q.isEmpty()) {

        int v = Q.getFront();
        Q.dequeue();

        Node* u = table[v].getFirst(); //get pointer to first element of list (adjancent)
        while (u != nullptr) {
            if (dist[u->vertex] == -1) { // Not already marked
                dist[u->vertex] = dist[v] + 1; //distance is former nodes distance + 1
                path[u->vertex] = v; //the path is the former node
                Q.enqueue(u->vertex);
            }
            u = table[v].getNext();
        }

    }
}

// positive weighted single source shortest paths
// Dijktra’s algorithm
void Digraph::pwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }

    for (int i = 1; i < table.size(); i++) {
        dist[i] = std::numeric_limits<int>::max();
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;

    int v = s;

    while (true) {
        Node* u = table[v].getFirst(); //get pointer to first element of list (adjancent)
        while (u != nullptr) {
            if (!(done[u->vertex]) && (dist[u->vertex] > dist[v] + u->weight)) {
                dist[u->vertex] = dist[v] + u->weight;
                path[u->vertex] = v;
            } 
            u = table[v].getNext();
        }
        v = find_smallest_undone_distance_vertex();
        if (v == 0) {
            break;
        }
        done[v] = true;
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
    while (path[t] =! 0)
    {
        std::cout << path[t] << "  ";
        t = path[t];
    }
    std::cout << "(" << distance << ")" << std::endl;
}

int Digraph::find_smallest_undone_distance_vertex() const
{
    int smallest = 0;
    int index = 0;
    int i = 1;
    while (i < dist.size()) {
        if (((!done[i]) && smallest == 0) || ((!done[i]) && dist[i] < smallest)) {
            index = i;
            smallest = dist[i];
        }
        ++i;
    }
    return index;
}
