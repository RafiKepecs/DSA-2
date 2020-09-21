#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

using namespace std;

class heap {
  public:
    heap(int capacity = 0);
    //int findMin() const;

    int insert(const string &id, const int &key, void *pv = nullptr);
    int deleteMin(const string *id, const int *key);
    int setKey(const string &id, const int &key);
    int remove(const string &id, const int* key);

  private:

    class node { // An inner class within heap
    public:
      string id; // The id of this node
      int key; // The key of this node
      void *pData; // A pointer to the actual data
    };

    int capacity;
    int currentSize;

    vector<node> data;
    hashTable mapping;

    void percolateUp(int posCur);
    void percolateDown(int posCur);
    int getPos(node *pn);

};

#endif
