/*********************************************
 * file:	~\tnd004\lab\lab4b\graph.h           *
 * remark: interface for undirected graphs    *
 **********************************************/

#pragma once

#include <vector>
#include <tuple>

#include "list.h"
#include "edge.h"

class Graph {
public:
    // -- CONSTRUCTORS
    explicit Graph(int n);  // Create an empty graph with n vertices

    // Create a graph with n vertices and the edges in V
    Graph(const std::vector<std::tuple<int, int, int>> &V, int n);

    // -- DESTRUCTOR
    ~Graph() = default;

    // Disallow copying
    Graph(const Graph &) = delete;
    Graph &operator=(const Graph &) = delete;

    // -- MEMBER FUNCTIONS

    // insert undirected edge (u, v) with weight w
    // update weight w if edge (u, v) is present
    void insertEdge(int u, int v, int w);

    // remove undirected edge (u, v)
    void removeEdge(int u, int v);

    // Prim's minimum spanning tree algorithm
    void mstPrim() const;

    // Kruskal's minimum spanning tree algorithm
    void mstKruskal() const;

    // print graph
    void printGraph() const;

private:
    // -- DATA MEMBERS
    std::vector<List> table;  // table of adjacency lists
    int size;                 // number of vertices
    int n_edges;              // number of edges
};
