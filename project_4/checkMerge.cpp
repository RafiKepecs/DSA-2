#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

unordered_map<string, string> memory;

string checkMerge(string a, string b, string c){
  if ( (a == "") && (b == "") && (c == "")){
    return "";
  }

  else if ( (a == "") + (b == "") + (c == "") == 2) {
    return "*** NOT A MERGE ***";
  }

  else if (memory.find(a+"\n"+b+"\n"+c) != memory.end()) {
    return memory[a+"\n"+b+"\n"+c];
  }

  string merge = "*** NOT A MERGE ***";

  if ( (a != "") && (a[0] == c[0])){
    merge = checkMerge(a.substr(1), b, c.substr(1));
    if (merge != "*** NOT A MERGE ***") {
      merge.insert(0, string(1,toupper(c[0])));
    }
  }

  if ( (b != "") && (b[0] == c[0]) && (merge == "*** NOT A MERGE ***") ){
    merge = checkMerge(a, b.substr(1), c.substr(1));
    if (merge != "*** NOT A MERGE ***") {
      merge.insert(0, string(1,c[0]));
  }
}

  memory.insert(make_pair(a+"\n"+b+"\n"+c, merge));

  return merge;
}


int main()
{
string infile, outfile, a, b, c;

// Get the input file
cout << "Enter name of input file: ";
  cin >> infile;
ifstream input(infile);

// Get the output file
  cout << "Enter name of output file: ";
  cin >> outfile;
ofstream output(outfile);

// Read lines three at a time, and print checkMerge results to output file
while (getline(input, a) && getline(input, b) && getline(input, c)) {
  output << checkMerge(a,b,c) << endl;
}

}
