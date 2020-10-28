#include <iostream>
#include "heap.h"
#include "hash.h"
using namespace std;
//remove

heap::heap(int capacity):mapping(capacity*2){
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
    currentSize = 0;
    this->capacity = capacity;
}

int heap::insert(const string &tmp, int key, void *pv){
  if(currentSize == capacity){
    return 1;
  }

  else if(mapping.contains(tmp)){
    //error
    // display();
    return 2;
  }
  else {
    int posCur = currentSize+1;
    data[0].key = key;
    data[0].id = tmp;
    mapping.insert(tmp, &data[posCur]);
    percolateUp(++currentSize);
    // display();
  }
  return 0;
}

int heap::deleteMin(string *tmp, int *pkey, void *ppData){
  if(currentSize <= 0){
    //error
    // display();
    return 1;
  }
  *tmp = data[1].id;
  *pkey = data[1].key;
  mapping.remove(data[1].id);
  data[1] = data[currentSize--];
  percolateDown(1);
  data[currentSize+1] = node();
  // display();
  return 0;
}

int heap::setKey(const string &tmp, int key){
  if(!mapping.contains(tmp)){
    // display();
    return 1;
  }
  node *pn = static_cast<node *> (mapping.getPointer(tmp));
  int posCur = getPos(pn);
  if(data[posCur].key < key){
    data[posCur].key = key;
    percolateDown(posCur);
  }
  else if (data[posCur].key > key){
    data[0].key = key;
    data[0].id = tmp;
    percolateUp(posCur);
  }
  // display();
  return 0;
}

int heap::remove(const string &tmp, int *pkey, void *ppData){
  if(!mapping.contains(tmp) || currentSize <= 0){
    //error
    // display();
    return 1;
  }
  // cout << "0.3" << endl;
  node *pn = static_cast<node *> (mapping.getPointer(tmp));
  // cout << "0.4" << endl;
  int posCur = getPos(pn);
  int oldKey = data[posCur].key;
  // if(pkey != nullptr){
    *pkey = data[posCur].key;
  // }
  mapping.remove(data[posCur].id);
  data[posCur] = data[currentSize--];
  data[currentSize+1] = node();

//test if new key is bigger or smaller than old key - may need to use percolateUp!!
  if(posCur <= currentSize && data[posCur].key <= oldKey){
    data[0] = data[posCur];
    percolateUp(posCur);
  }
  else{
    percolateDown(posCur);
  }
  // cout << "posCur: " << posCur << endl;
  // display();
  return 0;
}

void heap::percolateUp(int posCur){
  data[posCur] = data[0];
  for( ; data[0].key < data[posCur/2].key; posCur /= 2){
    data[posCur] = data[posCur/2];
    mapping.setPointer(data[posCur].id, &data[posCur]);
  }
  data[posCur] = data[0];
  mapping.setPointer(data[posCur].id, &data[posCur]);
  data[0] = node();
}

void heap::percolateDown(int posCur){
  int child;
  data[0] = data[posCur];
  for( ; posCur * 2 <= currentSize; posCur = child){
    child = posCur * 2;
    if (child != currentSize && data[child+1].key < data[child].key){
      ++child;
    }
    if (data[child].key < data[0].key){
      data[posCur] = data[child];
      mapping.setPointer(data[posCur].id, &data[posCur]);
    }
    else{
      break;
    }
  }
  data[posCur] = data[0];
  mapping.setPointer(data[posCur].id, &data[posCur]);
  data[0] = node();
  return;
}

int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}

void heap::display(){
  cout << "Current Size: " << currentSize << endl;
  cout << "*** HEAP ***" << endl;
  for(auto it : data){
    if(mapping.contains(it.id)){
      cout << "Key: " << it.key << ", String: " << it.id << endl;
    }
  }
  mapping.display();
  cout << endl;
}
