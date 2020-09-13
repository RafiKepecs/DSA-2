#include <iostream>
#include <fstream>
#include "hash.h"
using namespace std;

int main(){
  //hashTable(int) *h = new hashTable(5);
  string input, str;
  cout << "Enter name of input file: ";
  cin >> input;

  //parse the dictionary
  ifstream file (input);
  int numberOfLines = 0;
  while(getline(file,str)){
    numberOfLines++;
  }
  hashTable h(numberOfLines);
  while(getline(file,str)){
    h.insert(str);
  }
  return 0;
}
