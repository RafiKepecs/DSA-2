#include <iostream>
#include "heap.h"
#include "hash.h"
using namespace std;

heap::heap(int capacity):mapping(capacity*2){
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
    currentSize = 0;

}
/*
int heap::findMin() const{
  return 0;
}
*/

int heap::insert(const string &tmp, const int &key, void *pv){
  //skipping resizing for know
  //percolateUp
  // currentSize++;

  //currently in progress
  // percolateUp(currentSize);
  // for(auto it : data){
  //   cout << "Key: " << it.key << ", String: " << it.id << endl;
  // }
  // return 0;
  int hole = ++currentSize;
  data[0].key = key;
  data[0].id = tmp;
  data[hole] = data[0];
  for( ; data[0].key < data[hole/2].key; hole /= 2){
    data[hole] = data[hole/2];
  }
  data[hole] = data[0];
  data[0] = node();
  for(auto it : data){
    cout << "Key: " << it.key << ", String: " << it.id << endl;
  }
  return 0;
}

//currently in progress
void heap::percolateUp(int posCur){

}

int heap::deleteMin(const string *tmp, const int *key){
  return 0;
}

int heap::setKey(const string &tmp, const int &key){
  return 0;
}

int heap::remove(const string &tmp, const int* key){
  return 0;
}

//percolateDown implementation based on textbook, still unfinished
void heap::percolateDown(int posCur){
  int child;
  for( ; posCur * 2 <= currentSize; posCur = child){
    child = posCur * 2;
    if (child != currentSize && data[child+1].key < data[child].key){
      ++child;
    }
    // continue here!
  }
  return;
}

int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}
