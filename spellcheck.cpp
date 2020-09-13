#include <iostream>
#include "hash.h"
using namespace std;

int main(){
  //hashTable(int) *h = new hashTable(5);
  hashTable h(50000);
  h.insert("One");

  h.contains("One");
  h.insert("Two");
  h.display();
  //h.insert("Three");

  cout << "success" << endl;
  return 0;
}
