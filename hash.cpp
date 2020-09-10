#include <iostream>
#include "hash.h"
using namespace std;

//for now, not implementing pointer member functions
//will need a hard-coded list of prime numbers for the size of the hash array
//start dictionary at around 100,000


///*
hashTable::hashTable(int size){
  int primeSize = 101;
  hashItem test;
  for(int i=0 ; i < primeSize ; i++){
    data.push_back(test);
  }
}

int hashTable::insert(const string &key, void *pv){
  return 0;
}
///*
bool hashTable::contains(const string &key){
  return false;
}

int hashTable::hash(const string &key){
  return 0;
}

int hashTable::findPos(const string &key){
  return 0;
}

bool hashTable::rehash(){
  return false;
}
/*
void hashTable::*getPointer(const string &key, bool *b = nullptr){
  return 0;
}
*/
int hashTable::setPointer(const std::string &key, void *pv){
  return 0;
}

bool hashTable::remove(const std::string &key){
  return false;
}

static unsigned int getPrime(int size){
  int prime = 101;
  return prime;
}
//*/
