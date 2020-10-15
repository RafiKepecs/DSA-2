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
  // display();
  // mapping.display();
  //mapping.setPointer(data[posCur].id, &data[posCur]);
  return 0;
}

void heap::percolateUp(int posCur){
  data[posCur] = data[0];
  for( ; data[0].key < data[posCur/2].key; posCur /= 2){
    data[posCur] = data[posCur/2];
    mapping.setPointer(data[posCur].id, &data[posCur]);
    //getPos(&data[posCur]);
  }
  data[posCur] = data[0];
  // cout << posCur << ", " << currentSize << ", " << data[0].key << endl;;
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
  // cout << data[currentSize].key << endl;
  data[1] = data[currentSize--];
  percolateDown(1);
  // display();
  // mapping.display();
  return 0;
}

int heap::setKey(const string &tmp, int key){
  if(!mapping.contains(tmp)){
    return 1;
  }
  node *pn = static_cast<node *> (mapping.getPointer(tmp));
  int posCur = getPos(pn);
  // cout << posCur << endl;
  if(data[posCur].key < key){
    data[posCur].key = key;
    // data[posCur].id = tmp;
    // cout << posCur << endl;
    percolateDown(posCur);
  }
  else if (data[posCur].key > key){
    data[0].key = key;
    data[0].id = tmp;
    // cout << ".2" << endl;
    percolateUp(posCur);
  }
  // display();
  // mapping.display();
  return 0;
}

int heap::remove(const string &tmp, int *pkey, void *ppData){
  if(!mapping.contains(tmp)){
    //error
    return 1;
  }

  //cout << ".1" << endl;
  //bool *pt = (bool *) ppData;
  //cout << ".2" << endl;
  // node *pn = (node *) (mapping.getPointer(tmp, pt));
  node *pn = static_cast<node *> (mapping.getPointer(tmp));
  //cout << ".3" << endl;
  int posCur = getPos(pn);
  // tmp = data[posCur].id;
  int oldKey = data[posCur].key;
  *pkey = data[posCur].key;
  //cout << ".4" << endl;
  //cout << posCur << ", ";
  //cout << data[currentSize-1].key << endl;
  mapping.remove(data[posCur].id);
  data[posCur] = data[currentSize--];
  //cout << ".5" << endl;

//test if new key is bigger or smaller than old key - may need to use percolateUp!!
  if(data[posCur].key < oldKey){
    percolateUp(posCur);
  }
  else{
    percolateDown(posCur);
  }
  // display();
  // mapping.display();
  return 0;
}

//percolateDown implementation based on textbook, still unfinished
void heap::percolateDown(int posCur){
  int child;
  // data[currentSize+1] = data[posCur];
  data[0] = data[posCur];
  for( ; posCur * 2 <= currentSize; posCur = child){
    child = posCur * 2;
    if (child != currentSize && data[child+1].key < data[child].key){
      // cout << "test" << endl;
      ++child;
    }
    if (data[child].key < data[0].key){
      data[posCur] = data[child];
      mapping.setPointer(data[posCur].id, &data[posCur]);
      // cout << ".1" << endl;
    }
    else{
      // cout << ".2" << endl;
      break;
    }
  }
  // cout << ".3" << endl;
  // data[posCur] = data[currentSize+1];
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
  cout << "*** HEAP ***" << endl;
  for(auto it : data){
    if(it.id != ""){
      cout << "Key: " << it.key << ", String: " << it.id << endl;
    }
  }
  mapping.display();
  cout << endl;
}
