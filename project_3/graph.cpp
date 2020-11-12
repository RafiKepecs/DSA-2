#include <iostream>
#include <fstream>
#include <limits.h>
#include <string>
#include "graph.h"
using namespace std;

Graph::Graph(int size):mapping(size*2){
  capacity = size;
  currentSize = 0;
}

int Graph::insert(string vs, string ve, int cost){
  if(!mapping.contains(vs)){ // using hashTable to check whether vertex ID has been encountered
    Vertex* v = new Vertex;
    v->vert = vs;
    vertices.push_back(v);
    mapping.insert(vs, vertices.back());
    currentSize++;
  }
  if (!mapping.contains(ve)){
    Vertex* v = new Vertex;
    v->vert = ve;
    vertices.push_back(v);
    mapping.insert(ve, vertices.back());
    currentSize++;
  }
  if(mapping.contains(vs)){
    Edge* e = new Edge;
    e->source = vs;
    e->dest = ve;
    e->cost = cost;
    Vertex *pn = static_cast<Vertex *> (mapping.getPointer(vs));
    pn->adj_list.push_back(e);
  }
  return 0;
}

bool Graph::containsVertex(string vs){
  if(mapping.contains(vs)){
    return true;
  }
  else{
    return false;
  }
}

int Graph::dijkstra(string vs){
  Vertex *s, *v, *w;
  heap h(currentSize); // look at sizes...
  for(auto v1 : vertices){
    v1->dist = INT_MAX;
    v1->known = false;
  }
  s = static_cast<Vertex *> (mapping.getPointer(vs));
  s->dist = 0;
  s->path = nullptr;
  h.insert(s->vert, s->dist);
  string pId = "";
  int shortest_path = 0;
  Vertex* ppData;
  while(!h.deleteMin(&pId, &shortest_path)){
    v = static_cast<Vertex *> (mapping.getPointer(pId));
    v->dist = shortest_path;
    v->vert = pId;
    v->known = true;
    for(auto it : v->adj_list){
      w = static_cast<Vertex *> (mapping.getPointer(it->dest));
      if((v->dist + it->cost) < w->dist){
        w->dist = v->dist + it->cost;
        w->path = v;
        if(h.insert(w->vert, w->dist) == 2){
          h.setKey(w->vert, w->dist);
        }
      }
    }
  }
  return 0;
}

void Graph::printGraph(string vs, string output){
  ofstream file(output);
  Vertex* test = *vertices.begin();
  string path;
  for(auto verts : vertices){
    path = "";
    if(verts->dist >= INT_MAX){
      file << verts->vert << ": NO PATH" << endl;
    }
    else{
      file << verts->vert << ": " << verts->dist << " [" << vs;
      test = verts;
      while(test->vert != vs){
        path = ", " + test->vert + path;
        test = test->path;
      }
      file << path << "]" << endl;
    }
  }
  file.close();
}

void Graph::display(){
  for(auto verts : vertices){
    cout << verts->vert << ": " << "[";
    for(auto edges : verts->adj_list){
      cout << edges->dest << ": " << edges->cost;
      if(edges != *verts->adj_list.end()){
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
  return;
}
