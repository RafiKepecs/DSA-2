#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <list>
#include "hash.h"
#include "heap.h"

using namespace std;

class graph {
  public:
    graph(int capacity);
    int insert();
    void display();

  private:
    class edge {
    public:
      int dest;
      int cost;
    };
    list<edge> test;
    int dijkstra();

};


#endif
