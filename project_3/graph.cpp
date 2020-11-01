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
  Vertex *s, *v, *w;
  heap h(capacity); // look at sizes...
  for(auto v1 : vertices){
    v1->dist = INT_MAX;
    v1->known = false;
  }
  // cout << ".0" << endl;
  s = static_cast<Vertex *> (mapping.getPointer(vs));
  s->dist = 0;
  s->path = s;
  s->known = true;
  s->vert = vs;
  for(auto it : s->adj_list){
    w = static_cast<Vertex *> (mapping.getPointer(it->dest));
    w->dist = it->cost;
    w->vert = it->dest;
    h.insert(it->dest, it->cost);
  }
  string pId = "";
  int shortest_path = 0;
  int net_dist = 0;
  while(!h.deleteMin(&pId, &shortest_path)){
    v = static_cast<Vertex *> (mapping.getPointer(pId));
    v->dist = shortest_path;
    v->vert = pId;
    v->known = true;
    for(auto it : v->adj_list){
      if((v->dist + it->cost) < w->dist){
        w->dist = v->dist + it->cost;
        w->path = v;
        w->vert = it->dest;
        h.insert(w->vert, w->dist);
      }
      cout << w->vert << endl;
    }
  }
  for(auto verts : vertices){
    cout << verts->path->vert << endl;
  }
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
