#include <iostream>
#include "hash.h"
using namespace std;

//for now, not implementing pointer member functions


hashTable::hashTable(int size) : data(getPrime(size)){
  capacity = data.size();
}

int hashTable::insert(const string &key, void *pv){
  int currentPos = findPos(key);

  if(contains(key)){
    return 1;
  }
  data[currentPos].key = key;
  data[currentPos].isOccupied = true;
  //rehash
  if(++filled > data.size()/2){
    //cout << "reshash called" << endl;
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
  return hashVal % capacity;
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
  return currentPos;
}

bool hashTable::rehash(){
  vector<hashItem> oldData = data;
  data.resize(getPrime(2*oldData.size()));
  if(data.size() <= oldData.size()){
    //cout << "Rehash failed" << endl;
    return false;
  }
  for(auto & entry : data){
    entry.key = "";
    entry.isOccupied = false;
  }
  filled = 0;
  for(auto & entry : oldData){
    if(entry.isOccupied){
      insert(entry.key);
    }
  }
  return true;
}

bool hashTable::*getPointer(const string &key, bool *b){
  return 0;
}

int hashTable::setPointer(const std::string &key, void *pv){
  return 0;
}

bool hashTable::remove(const std::string &key){
  return false;
}

unsigned int hashTable::getPrime(int size){
  int primes[7] = {49157, 98317, 196613, 393241, 786433, 1572869, 3145739};
  int prime = 0;
  for (int i = 0; i < 7; i++){
    if ((primes[i]) < size){
    }
    else{
      prime = primes[i];
      return prime;
    }
  }
  return 0;
}

//function mostly used for testing purposes
void hashTable::display()
    {
        for(int i = 0 ; i < capacity ; i++)
        {
            if(data[i].isOccupied){
                cout << "key = " << data[i].key <<
                " is in position " << i << endl;
            }
            else{
            }
        }
    }
