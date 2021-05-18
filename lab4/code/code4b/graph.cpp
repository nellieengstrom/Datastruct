/*********************************************
 * file:	~\tnd004\lab\lab4b\graph.h        *
 * remark:implementation of undirected graphs *
 **********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert
#include <limits>   //std::numeric_limits

// using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

// Create an empty graph with n vertices
Graph::Graph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
}

Graph::Graph(const std::vector<std::tuple<int, int, int>> &V, int n) : Graph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);
    table[v].insert(u, w);

    n_edges += 2;
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);
    table[v].remove(u);

    n_edges -= 2;
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {
    std::vector<int> dist; //creates new vectors
    std::vector<int> path;
    std::vector<bool> done;
    int weight = 0;

    dist.resize(size + 1); //changes the size so it will fit, and do not need to reallocate
    path.resize(size + 1);
    done.resize(size + 1);

    for (int i = 1; i < table.size(); i++) {
        dist[i] = std::numeric_limits<int>::max(); //set initial values
        path[i] = 0;
        done[i] = false;
    }
    dist[1] = 0; //Set the starting point
    done[1] = true;
    int v = 1;

    while (true) {
        Node* u = table[v].getFirst(); //get pointer to first element of list (adjancent)

        while(u != nullptr){
         //Checks if the node is not visited and the weight of the new distance is smaller than the already existing
            if (!(done[u->vertex]) && dist[u->vertex] >= u->weight ) {
                path[u->vertex] = v; //Then update to that edge
                dist[u->vertex] = u->weight; //and weight
            }
            u = table[v].getNext();
        }

        //The ones not already visited, find the smallest distance.
        v = find_smallest_undone_distance_vertex(dist, done);
        if (v == 0) break;

        //Then print the edges of the minimum spanning tree
        std::cout << "( " << path[v] << ",  " << v << ",  " << dist[v] << ")" << std::endl;
        weight = weight + dist[v];
        done[v] = true;
    }
    //and the total weight
    std::cout << std::endl << "Total weight = " << weight << std::endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {
    Heap H = Heap<Edge>::Heap(size-1); //minHeap, root is always edge that is not
    //in the tree and with the lowest weight
    DSets D(size); //n disjoint trees with one node in each
    
    //Adds the edges to the minHeap
    for (int i = 1; i < table.size(); i++) {
        Node* u = table[i].getFirst();
        while (u != nullptr) {
            H.insert(Edge(i, u->vertex, u->weight));
            u = table[i].getNext(); 
        }
    }

    int counter = 0;
    int weight = 0;
    Edge theEdge;

    while (counter < (size - 1)) {
        //return the root = the edge with the smallest weight, and delete it
        theEdge = H.deleteMin();

        //Does this edge connect two different trees? Checks the head and tail pointers
        if (D.find(theEdge.head) != D.find(theEdge.tail)) { 
            
            //Prints the vertexes the edge connects and the weight of the edge
            std::cout << "( " << theEdge.tail << ",  "
            << theEdge.head << ",  "
            << theEdge.weight << ")" << std::endl;
            weight = weight + theEdge.weight;

            D.join(D.find(theEdge.head), D.find(theEdge.tail)); //Added to the same set
            counter++;
        }
    }
    std::cout << std::endl << "Total weight = " << weight << std::endl;
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}

//Same as before but send in the dist and done instead
int Graph::find_smallest_undone_distance_vertex(std::vector<int> dist, std::vector<bool> done) const{
    int index = 0;
    int smallest = 0;
    
    for(int i = 1; i < dist.size(); i++){
        //Checks that the vertex is unvisited and smallest = 0, its the first time
        //or its unvisited and the distance is smaller than the latest smallest
        if (((!done[i]) && smallest == 0) || ((!done[i]) && dist[i] < smallest)) {
            index = i; //want to return its index
            smallest = dist[i];
        }
    }
    return index;
}