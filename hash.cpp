#include <iostream>
#include "hash.h"
using namespace std;

//for now, not implementing pointer member functions
//will need a hard-coded list of prime numbers for the size of the hash array
//start dictionary at around 100,000


///*
hashTable::hashTable(int size) : data(getPrime(size)){
  makeEmpty();
  /*
  hashItem test;
  for(int i=0 ; i < primeSize ; i++){
    data.push_back(test);
  }
  */
}

//i don't know if this is necessary yet
void hashTable::makeEmpty(){
  capacity = 0;
  for (auto & entry : data){
    entry.key = "0";
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

unsigned int hashTable::getPrime(int size){
  int primes[6] = {98317, 196613, 393241, 786433, 1572869, 3145739};
  int prime = 0;
  for (int i = 0; i < 6; i++){
    if ((primes[i]/2) < size){
    }
    else{
      prime = primes[i];
      cout << "Table size = " << prime << endl;
      return prime;
    }
  }
  return 0;
}
//*/
