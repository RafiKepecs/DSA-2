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
  ++currentSize;
  for(auto it : data){
    if(it.id == tmp){
      //error
      return 2;
    }
  }
  data[0].key = key;
  data[0].id = tmp;
  percolateUp(currentSize);
  mapping.insert(tmp);
  display();
  mapping.display();
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
  cout << posCur << ", " << currentSize << ", " << data[0].key << endl;;
  mapping.setPointer(data[posCur].id, &data[posCur]);
  data[0] = node();
}

int heap::deleteMin(string *tmp, int *pkey, void *ppData){
  if(currentSize == 0){
    //error
    return 1;
  }
  mapping.remove(data[1].id);
  data[1] = data[currentSize--];
  percolateDown(1);
  display();
  mapping.display();
  return 0;
}

int heap::setKey(const string &tmp, int key){
  node *pn = static_cast<node *> (mapping.getPointer(tmp));
  int posCur = getPos(pn);
  // cout << posCur << endl;
  if(data[posCur].key < key){
    data[posCur].key = key;
    percolateDown(posCur);
  }
  else if (data[posCur].key > key){
    data[0].key = key;
    data[0].id = tmp;
    // cout << ".2" << endl;
    percolateUp(posCur);
  }
  display();
  mapping.display();
  return 0;
}

//wasn't able to use static_casting, regular casting seems to be working...
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
  //cout << ".4" << endl;
  //cout << posCur << ", ";
  //cout << data[currentSize-1].key << endl;
  mapping.remove(data[posCur].id);
  data[posCur] = data[currentSize--];
  //cout << ".5" << endl;
  percolateDown(posCur);
  display();
  mapping.display();
  return 0;
}

//percolateDown implementation based on textbook, still unfinished
void heap::percolateDown(int posCur){
  int child;
  data[currentSize+1] = data[posCur];
  for( ; posCur * 2 <= currentSize; posCur = child){
    child = posCur * 2;
    if (child != currentSize && data[child+1].key < data[child].key){
      ++child;
    }
    if (data[child].key < data[currentSize+1].key){
      data[posCur] = data[child];
      mapping.setPointer(data[posCur].id, &data[posCur]);
    }
    else{
      break;
    }
  }
  data[posCur] = data[currentSize+1];
  mapping.setPointer(data[posCur].id, &data[posCur]);
  data[currentSize+1] = node();
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
  cout << endl;
}
