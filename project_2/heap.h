#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>

using namespace std;

class heap {
  public:
    heap(int size = 0);
    bool isEmpty() const;
    int findMin() const;

    int insert(const string &tmp, const int &key);
    int deleteMin(const string *tmp, const int *key);
    int setKey(const string &tmp, const int &key);
    int remove(const string &tmp, const int* key);

  private:

    class node { // An inner class within heap
    public:
      string id; // The id of this node
      int key; // The key of this node
      void *pData; // A pointer to the actual data
    };

    int capacity;
    int filled;

    vector<node> data;

    void buildHeap();
    void percolateDown(int hole);
};

#endif
