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
    int insert(string vs, string ve, int cost);
    void display();
    void printGraph(string vs, string output);
    int dijkstra(string vs);
    bool containsVertex(string vs);
  private:
    class Edge {
    public:
      string source;
      string dest;
      int cost;
    };
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
