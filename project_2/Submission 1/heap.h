#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

using namespace std;

class heap {
  public:
    heap(int capacity);
    //int findMin() const;

    int insert(const string &id, int key, void *pv = nullptr);
    int deleteMin(string *pId = nullptr, int *pkey = nullptr, void *ppData = nullptr);
    int setKey(const string &id, int key);
    int remove(const string &id, int *pkey = nullptr, void *ppData = nullptr);
    void display();

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
