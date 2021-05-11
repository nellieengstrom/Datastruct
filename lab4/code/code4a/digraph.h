/*********************************************
 * file:    ~\lab4a\digraph.h                 *
 * remark: interface for directed graphs      *
 **********************************************/

#pragma once

#include <tuple>
#include <vector>
#include "list.h"

class Digraph {
public:
    // -- CONSTRUCTORS
    explicit Digraph(int n);

    Digraph(const std::vector<std::tuple<int, int, int>>& V,
            int n);  // Create a digraph with n vertices and the edges in V

    // -- DESTRUCTOR
    ~Digraph() = default;

    // Disallow copying
    Digraph(const Digraph&) = delete;
    Digraph& operator=(const Digraph&) = delete;

    // -- MEMBER FUNCTIONS

    // insert directed edge (u, v) with weight w
    // update weight w if edge (u, v) is present
    void insertEdge(int u, int v, int w);

    // remove directed edge (u, v)
    void removeEdge(int u, int v);

    // unweighted single source shortest paths
    void uwsssp(int s) const;

    // positive weighted single source shortest paths
    // Dijktra's algorithm
    void pwsssp(int s) const;

    // print graph
    void printGraph() const;

    // print shortest path tree for s
    void printTree() const;

    // print shortest path from s to t
    void printPath(int t) const;

private:
    // -- DATA MEMBERS
    std::vector<List> table;  // table of adjacency lists
    int size;                 // number of vertices
    int n_edges;              // number of edges

    mutable std::vector<int> dist;
    mutable std::vector<int> path;
    mutable std::vector<int> done;

    int find_smallest_undone_distance_vertex() const;
};