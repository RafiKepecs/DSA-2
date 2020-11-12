#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <list>
#include "hash.h"
#include "heap.h"

using namespace std;

class Graph {
  public:
    Graph(int size = 0);
    // Insert item into Graph based on starting and ending vertices, and edge cost
    int insert(string vs, string ve, int cost);
    //testing function to display the graph
    void display();
    //print out the minimum path length file
    void printGraph(string vs, string output);
    //compute the minimum path length from starting vertex vs
    int dijkstra(string vs);
    //function to check if a vertex is in the graph
    bool containsVertex(string vs);
  private:
    //nested edge class to store graph edges
    class Edge {
    public:
      string source;
      string dest;
      int cost;
    };
    //nested vertex class to store graph nodes
    class Vertex{
    public:
      string vert;
      bool known;
      int dist;
      Vertex* path;
      list<Edge*> adj_list;
    };

    list<Vertex*> vertices;
    hashTable mapping;
    int capacity;
    int currentSize;

};

#endif
