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
  //cout << "insert called" << endl;
  int currentPos = findPos(key);
  /*
  if(contains(key)){
    return 1;
  }
  else{
  }
  */
  data[currentPos].key = key;
  data[currentPos].isOccupied = true;
  //rehash
  //cout << data.size() << endl;
/*
  if(data.size() >= 196613 && filled > 50000){
    //cout << filled << endl;
    if (filled > 98000){
      cout << filled << endl;
    }
    else{
      //cout << "error" << endl;
    }
  }
  else{
  }
  /*
  if (filled == 98306){
    cout << filled << endl;
  }
  */
  //cout << "Filled: " << filled << ", data.size: " << data.size() << endl;
  if(++filled > data.size()/2){
    //cout << "Filled: " << filled << endl;
    //cout << "reshash called" << endl;
    rehash();
    if(filled > data.size()/2){ //rehash failure
      cout << "Rehash error" << endl;
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
  /*
  long sum = 0, mul = 1;
	for (int i = 0; i < key.length(); i++) {
		mul = (i % 8 == 0) ? 1 : mul * 256;
		sum += tolower(key[i]) * mul; // Note: conversion to lowercase
	}
	return (int)(abs(sum) % data.size());
  */
  ///*
  unsigned int hashVal = 0;
  for (char ch : key){
    hashVal = 37*hashVal + ch;
  }
  return hashVal % data.size();
  //*/
}

//for linear probing, offset is always 1
//implementation based on textbook
int hashTable::findPos(const string &key){
  int currentPos = hash(key);
  int collisions = 0;
  //int offset = 1;
  while(data[currentPos].isOccupied == true &&
        data[currentPos].key != key){
    currentPos += 1; // current probe
    collisions++;
    //offset += 2;
    if(currentPos >= data.size()){
      currentPos -= data.size();
    }
  }
  if(collisions > 8){
    //cout << "Collisions: " << collisions << endl;
  }
  return currentPos;
}

bool hashTable::rehash(){
  //cout << "rehash called" << endl;
  //cout << data.size() << endl;
  vector<hashItem> oldData = data;
  data.clear();
  data.resize(getPrime(2*oldData.size()));
  //cout << getPrime(2*oldData.size()) << endl;
  //cout << ".1" << endl;
  if(data.size() <= oldData.size()){
    cout << "Rehash failed" << endl;
    return false;
  }
  //cout << ".2" << endl;
  // for(auto entry : data){
  //   entry.key = "";
  //   entry.isOccupied = false;
  // }
  //cout << ".3" << endl;
  filled = 0;
  for(auto entry : oldData){
    if(entry.isOccupied){
      insert(entry.key);
    }
  }
  oldData.clear();
  oldData.shrink_to_fit();
  //cout << ".4" << endl;
  //cout << data.size() << endl;
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
void hashTable::display()
    {
        string str;
        ofstream file ("test.txt");
        for(int i = 0 ; i < capacity ; i++)
        {
            if(data[i].isOccupied){
                file <<  data[i].key << endl;
            }
            else{
            }
        }
    }
