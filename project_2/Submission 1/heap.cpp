#include <iostream>
#include "heap.h"
#include "hash.h"
using namespace std;

heap::heap(int capacity):mapping(capacity*2){
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
    currentSize = 0;
}

int heap::insert(const string &tmp, int key, void *pv){
  if(mapping.contains(tmp)){
      //error
      return 2;
  }
  ++currentSize;
  data[0].key = key;
  data[0].id = tmp;
  mapping.insert(tmp);
  percolateUp(currentSize);
  display();
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

int heap::deleteMin(string *tmp, int *pkey, void *ppData){
  if(currentSize == 0){
    //error
    return 1;
  }
  *tmp = data[1].id;
  *pkey = data[1].key;
  mapping.remove(data[1].id);
  data[1] = data[currentSize--];
  percolateDown(1);
  display();
  return 0;
}

int heap::setKey(const string &tmp, int key){
  if(!mapping.contains(tmp)){
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
  display();
  return 0;
}

int heap::remove(const string &tmp, int *pkey, void *ppData){
  if(!mapping.contains(tmp)){
    //error
    return 1;
  }

  node *pn = static_cast<node *> (mapping.getPointer(tmp));
  int posCur = getPos(pn);
  int oldKey = data[posCur].key;
  *pkey = data[posCur].key;
  mapping.remove(data[posCur].id);
  data[posCur] = data[currentSize--];

//test if new key is bigger or smaller than old key - may need to use percolateUp!!
  if(data[posCur].key < oldKey){
    percolateUp(posCur);
  }
  else{
    percolateDown(posCur);
  }
  display();
  return 0;
}

//percolateDown implementation based on textbook, still unfinished
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
  data[currentSize+1] = node();
  data[0] = node();
  return;
}

int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}

void heap::display(){
  cout << "currentSize: " << currentSize << endl;
  cout << "*** HEAP ***" << endl;
  for(auto it : data){
    if(it.id != ""){
      cout << "Key: " << it.key << ", String: " << it.id << endl;
    }
  }
  mapping.display();
  cout << endl;
}
