#include <iostream>
#include <limits.h>
#include <string>
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
    e->source = vs;
    e->dest = ve;
    e->cost = cost;
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
  s = static_cast<Vertex *> (mapping.getPointer(vs));
  s->dist = 0;
  s->path = s;
  s->known = true;
  s->vert = vs;

  // cout << s->vert << ": " << s->dist << " [" << s->path->vert << "]" << endl;

  /*
  initiale the HEAP
  set all the vertices to have infinite length and known bool to false
  set source vertex equal to input vertex
  frontier:
    add every adjacent vertex to the frontier
  while !deleteMin(pId, pkey)
    v = new "known" Vertex
    v->cost = pkey
    (check if leads to known vertex)
    for every unknown vertex in v's adj_list
        add each vertex to the frontier (check if it's already in the frontier and if it is, check if the new pathlength is shorter than the old, in which case use setKey to update the new shortest_path)
  */

  for(auto it : s->adj_list){
    w = static_cast<Vertex *> (mapping.getPointer(it->dest));
    w->dist = it->cost;
    w->vert = it->dest;
    w->path = s;
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
      w = static_cast<Vertex *> (mapping.getPointer(it->dest));
      if((v->dist + it->cost) < w->dist){
        w->dist = v->dist + it->cost;
        w->path = v;
        w->vert = it->dest;
        // cout << "w: " << w->vert << ", dist:" << v->dist << ", cost" << it->cost << endl;
        h.insert(w->vert, w->dist);
      }
    }
  }
  return 0;
}

void Graph::printGraph(string vs){
  Vertex* test = *vertices.begin();
  string path;
  for(auto verts : vertices){
    path = "";
    if(verts->dist >= INT_MAX){
      cout << verts->vert << ": NO PATH" << endl;
    }
    else{
      cout << verts->vert << ": " << verts->dist << " [" << vs;
      test = verts;
      while(test->vert != vs){
        path = ", " + test->vert + path;
        test = test->path;
      }
      cout << path << "]" << endl;
    }
  }
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
