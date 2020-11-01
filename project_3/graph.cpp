#include <iostream>
#include <limits.h>
#include "graph.h"
using namespace std;

Graph::Graph(int size):mapping(size*2){
  // vertices.resize(size+1);
  capacity = size;
  currentSize = 0;
}

int Graph::insert(string vs, string ve, int cost){
  if(!mapping.contains(vs)){ // using hashTable to check whether vertex ID has been encountered
    Vertex* v = new Vertex;
    v->vert = vs;
    vertices.push_back(v);
    mapping.insert(vs, vertices.back());
  }
  if (!mapping.contains(ve)){
    Vertex* v = new Vertex;
    v->vert = ve;
    vertices.push_back(v);
    mapping.insert(ve, vertices.back());
  }
  if(mapping.contains(vs)){
    Edge* e = new Edge;
    e->dest = ve;
    Vertex *pn = static_cast<Vertex *> (mapping.getPointer(vs));
    pn->adj_list.push_back(e);
    // cout << pn->vert << endl;
  }
  return 0;
}

int Graph::dijkstra(string vs){
  Vertex *s = static_cast<Vertex *> (mapping.getPointer(vs));
  for(auto v : vertices){
    v->dist = INT_MAX;
    v->known = false;
  }
  s->dist = 0;
  s->path = nullptr;
  heap h(capacity); // look at sizes...
  // while(){

  // }
  return 0;
}

void Graph::display(){
  for(auto verts : vertices){
    cout << verts->vert << ": " << "[";
    for(auto edges : verts->adj_list){
      cout << edges->dest;
      if(edges != *verts->adj_list.end()){
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
  return;
}
