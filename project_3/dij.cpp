#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

graph loadGraph(string graph){
  string str;
  ifstream file(graph);
  while(getline(file,str)){

  }

  int capacity = 100;
  graph g(capacity);
  return g;
}

int main(){
  string graph, start_ver, output;
  cout << "Enter name of graph file: ";
  graph = "graph.txt";// cin >> graph;
  cout << graph << endl;
  cout << "Enter a valid vertex id for the starting vertex: ";
  start_ver = "v1"; // cin >> start;
  cout << start_ver << endl;
  clock_t start, end;
  start = clock();
  // graph g = loadGraph(graph);
  end = clock();
  double time_taken = double(end-start) / double(CLOCKS_PER_SEC);
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_taken << endl;
  cout << "Enter name of output file: ";
  output = "output.txt";
  cout << output << endl; // cin >> output;
  return 1;
}
