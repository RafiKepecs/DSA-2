#include <iostream>
#include "hash.h"
#include <fstream>
using namespace std;

//for now, not implementing pointer member functions

hashTable::hashTable(int size) : data(getPrime(size)){
  capacity = getPrime(size);//data.size();
  //cout << "constructor called" << endl;
}

int hashTable::insert(const string &key, void *pv){
  int currentPos = findPos(key);
  if(contains(key)){
    return 1;
  }
  data[currentPos].key = key;
  data[currentPos].isOccupied = true;
  data[currentPos].isDeleted = false;
  data[currentPos].pv = pv;
  //rehash
  if(++filled > data.size()/2){

    rehash();
    if(filled > data.size()/2){ //rehash failure
      return 2;
    }
  }
  return 0;
}

bool hashTable::contains(const string &key){
  if(data[findPos(key)].isOccupied == true){
    return true;
  }
  else{
    return false;
  }
}

//Hash function taken from the textbook
int hashTable::hash(const string &key){
  unsigned int hashVal = 0;
  for (char ch : key){
    hashVal = 37*hashVal + ch;
  }
  return hashVal % data.size();
}

//for linear probing, offset is always 1
//implementation based on textbook
int hashTable::findPos(const string &key){
  int currentPos = hash(key);
  while(data[currentPos].isOccupied == true &&
        data[currentPos].key != key){
    currentPos += 1; // current probe
    if(currentPos >= data.size()){
      currentPos -= data.size();
    }
  }
  if(currentPos > data.size()){
    return -1;
  }
  return currentPos;
}

bool hashTable::rehash(){
  vector<hashItem> oldData = data;
  data.clear();
  data.resize(getPrime(2*oldData.size()));
  if(data.size() <= oldData.size()){
    //cout << "Rehash failed" << endl;
    return false;
  }
  filled = 0;
  for(auto entry : oldData){
    if(entry.isOccupied && !entry.isDeleted){
      insert(entry.key);
    }
  }
  oldData.clear();
  oldData.shrink_to_fit();
  return true;
}

void* hashTable::getPointer(const std::string &key, bool *b){
  int currentPos = hash(key);
  // cout << "getPointer of: " << data[currentPos].key << endl;
  // //bool *pt = (bool *) data[currentPos].pv;
  // if(data[currentPos].pv == nullptr){
  //   cout << "error" << endl;
  // }
  return data[currentPos].pv;
  // return pt;
}

int hashTable::setPointer(const std::string &key, void *pv){
  int currentPos = hash(key); //look up position of input Key
  // cout << "setPointer of: " << data[currentPos].key << endl;
  data[currentPos].pv = pv; //set pointer member of item in hashtable equal to location of item in heap
  return 0;
}

bool hashTable::remove(const std::string &key){
  int currentPos = hash(key);
  data[currentPos] = hashItem();
  data[currentPos].isDeleted = true;
  return false;
}

unsigned int hashTable::getPrime(int size){
  int primes[7] = {49157, 98317, 196613, 393241, 786433, 1572869, 3145739};
  int prime = 0;
  for (int i = 0; i < 7; i++){
    if ((primes[i]) < size-100){
    }
    else{
      prime = primes[i];
      return prime;
    }
  }
  return 0;
}

//function mostly used for testing purposes
void hashTable::display(){
  cout << "*** HASH TABLE ***" << endl;
  for(auto it : data){
      if(it.isOccupied){
        cout << "hash key: " << it.key << endl;
      }
  }
  cout << endl;

        // string str;
        // ofstream file ("test.txt");
        // for(int i = 0 ; i < capacity ; i++)
        // {
        //     if(data[i].isOccupied){
        //         file <<  data[i].key << endl;
        //     }
        //     else{
        //     }
        // }
    }
