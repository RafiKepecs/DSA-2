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
  // cout << ".0" << endl;
  s = static_cast<Vertex *> (mapping.getPointer(vs));
  s->dist = 0;
  s->path = s;
  s->known = true;
  s->vert = vs;

  cout << s->vert << ": " << s->dist << " [" << s->path->vert << "]" << endl;

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
    // cout << it->cost << endl;
  }
  string pId = "";
  int shortest_path = 0;
  int net_dist = 0;
  while(!h.deleteMin(&pId, &shortest_path)){
    // cout << "0.2" << endl;
    // s->vert = v->vert;
    // s->path = v->path;
    // cout << "0.3" << endl;
    v = static_cast<Vertex *> (mapping.getPointer(pId));
    v->dist = shortest_path;
    // cout << pId << endl;
    v->vert = pId;
    v->known = true;
    // cout << "0.4" << endl;
    // v->path = s;
    // cout << "0.5" << endl;
    cout << v->vert << ": " << v->dist << " [" << vs << ", ";
    Vertex* test = v;
    // cout << "0.6" << endl;
    while(test->path->vert != vs){
      cout << test->path->vert << ", ";
      test = test->path;
    }
    cout << "]" << endl;
    for(auto it : v->adj_list){
      // if(!h.mapping.contains(it->dest)){
      //   h.insert(it->dest, (v->dist + it->cost));
      // }

      w = static_cast<Vertex *> (mapping.getPointer(it->dest));
      // w->dist = it->cost;
      // w->vert = it->dest;

      // if(h.insert(it->dest, it->cost) == 2){
      //
      //   if()
      // }
      // cout << it->cost << ", " << w->dist << endl;

      if((v->dist + it->cost) < w->dist){
        w->dist = v->dist + it->cost;
        // cout << it->cost << endl;
        w->path = v;
        w->vert = it->dest;
        h.insert(w->vert, w->dist);
      }
      // cout << "0.1" << endl;
    }
  }
  cout << "print" << endl;
  // for(auto verts : vertices){
  //   for(auto it : verts->path){
  //     cout << it->vert << endl;
  //   }
  // }
  return 0;
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
