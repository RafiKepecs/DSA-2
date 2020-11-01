#include <iostream>
#include "graph.h"
using namespace std;

Graph::Graph(int size):mapping(size*2){
  // vertices.resize(size+1);
  capacity = size;
  currentSize = 0;
}

int Graph::insert(string vs, string ve){
  if(!mapping.contains(vs)){ // using hashTable to check whether vertex ID has been encountered
    Vertex* v = new Vertex;
    v->vert = vs;
    vertices.push_back(v);
    mapping.insert(vs);
  }
  if (!mapping.contains(ve)){
    Vertex* v = new Vertex;
    v->vert = ve;
    vertices.push_back(v);
    mapping.insert(ve);
  }
  else{
  }
  return 0;
}

void Graph::display(){
  for(auto it : vertices){
    cout << it->vert << endl;
  }
  return;
}

// int graph::dijkstra(){
//   return 0;
// }
