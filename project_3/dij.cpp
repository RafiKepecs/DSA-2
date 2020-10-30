#include <iostream>
#include <fstream>
#include "graph.h"
// #include "heap.h"
// #include "hash.h"
using namespace std;

Graph loadGraph(string graph, string output){
  string str;
  ifstream file(graph);
  ofstream file2(output);
  int capacity = 100;
  Graph g(capacity);
  bool vs_flag, ve_flag;
  string vs, ve, word;
  int cost;
  while(getline(file,str)){
    vs_flag = false;
    ve_flag = false;
    word = "";
    vs = "";
    ve = "";
    cost = 0;
    for(auto it : str){
      if(it == ' ' || it == *(str.end()-1)){
        if(!vs_flag){
          vs_flag = true;
          vs = word;
        }
        else if(!ve_flag){
          ve_flag = true;
          ve = word;
        }
        else{
          cost = stoi(word);
        }
        word = "";
      }
      else{
        word += it;
      }
    }
    file2 << vs << " " << ve << " " << cost << "\n";
    // g.insert();
  }
  file.close();
  file2.close();
  // cout << "loadGraph" << endl;
  return g;
}

int main(){
  string graph, start_ver, output, output_temp;
  output_temp = "output.txt";
  cout << "Enter name of graph file: ";
  graph = "graph.txt";// cin >> graph;
  cout << graph << endl;
  cout << "Enter a valid vertex id for the starting vertex: ";
  start_ver = "v1"; // cin >> start;
  cout << start_ver << endl;
  clock_t start, end;
  start = clock();
  Graph g = loadGraph(graph, output_temp);
  end = clock();
  double time_taken = double(end-start) / double(CLOCKS_PER_SEC);
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_taken << endl;
  cout << "Enter name of output file: ";
  output = "output.txt";
  cout << output << endl; // cin >> output;
  return 1;
}
