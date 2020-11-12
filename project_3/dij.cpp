#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"

using namespace std;

//loads the graph based on input file
Graph loadGraph(string graph){
  string str;
  ifstream file(graph);
  Graph g;
  bool vs_flag, ve_flag;
  string vs, ve, word;
  int cost;
  while(getline(file,str)){
    stringstream ss(str);
    ss >> vs >> ve >> cost;
    g.insert(vs, ve, cost);
  }
  file.close();
  return g;
}

//main function
int main(){
  string graph, start_ver, output, output_temp;
  cout << "Enter name of graph file: ";
  cin >> graph;
  Graph g = loadGraph(graph);
  do{
    cout << "Enter a valid vertex id for the starting vertex: ";
    cin >> start_ver;
  } while (!g.containsVertex(start_ver));
  clock_t start, end;
  start = clock();
  g.dijkstra(start_ver);
  end = clock();
  double time_taken = double(end-start) / double(CLOCKS_PER_SEC);
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_taken << endl;
  cout << "Enter name of output file: ";
  cin >> output;
  g.printGraph(start_ver, output);
  return 1;
}
