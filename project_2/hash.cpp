#include <iostream>
#include "hash.h"
using namespace std;

//for now, not implementing pointer member functions
//will need a hard-coded list of prime numbers for the size of the hash array
//start dictionary at around 100,000


///*
hashTable::hashTable(int size) : data(getPrime(size)){
  capacity = getPrime(size);
  //cout << "constructor called" << endl;
  /*
  capacity = getPrime(size);
  filled = 0;
  hash("s", capacity); // i think this goes into the insert function
  */

  /*
  hashItem test;
  for(int i=0 ; i < primeSize ; i++){
    data.push_back(test);
  }
  */
}

//i don't know if this is necessary yet
/*
void hashTable::makeEmpty(){
  capacity = 0;
  for (auto & entry : data){
    entry.key = "0";
  }
}
*/

int hashTable::insert(const string &key, void *pv){
  int currentPos = findPos(key);

  if(contains(key)){
    //cout << "insert failed" << endl;
    return 1;
  }
  data[currentPos].key = key;
  data[currentPos].isOccupied = true;
  //rehash

  if(++filled > data.size()/2){
    rehash();
    if(filled > data.size()/2){ //rehash failure
      return 2;
    }
  }
  //cout << "insert successful" << endl;
  return 0;
  /*
  hashItem *temp = new hashItem();
  int index = hash(key);
  while((data[index].key != key) && (data[index].key != "0")){
    index++;
  }
  filled++;
  //having trouble inserting the element into the data vector
  vector<int>::iterator it = find(data.begin(), data.end, index)
  data.insert(it,temp);
  return 0;
  */
}
///*
bool hashTable::contains(const string &key){
  //cout << "contains called" << endl;
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
  //cout << "hash called" << endl;
  return hashVal % capacity;

    /*
    int sum = 0;

    for (int k = 0; k < key.length(); k++){
        sum = sum + int(key[k]);
        //cout << sum << endl;
    }
    cout << sum % capacity << endl;
    //cout << capacity << endl;
    //cout << sum % capacity << endl;
    return (sum % capacity);
    //return 0;
    */
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
  //cout << "findPos called" << endl;
  return currentPos;
}

bool hashTable::rehash(){
  vector<hashItem> oldData = data;
  data.resize(getPrime(2*oldData.size()));
  for(auto & entry : data){
    entry.key = "";
    entry.isOccupied = false;
  }
  filled = 0;
  for(auto & entry : oldData){
    if(entry.isOccupied){
      insert(std::move(entry.key));
    }
  }
  //cout << "reshash called" << endl;
  return true;
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
  int primes[7] = {49157, 98317, 196613, 393241, 786433, 1572869, 3145739};
  int prime = 0;
  for (int i = 0; i < 7; i++){
    if ((primes[i]/2) < size){
    }
    else{
      prime = primes[i];
      //cout << "Table size = " << prime << endl;
      return prime;
    }
  }
  return 0;
}
//*/

void hashTable::display()
    {
        //cout << capacity << endl;
        for(int i = 0 ; i < capacity ; i++)
        {
            //cout << "test" << endl;
            if(data[i].isOccupied){
                cout << "key = " << data[i].key <<
                " is in position " << i << endl;
            }
            else{
              //cout << "error" << endl;
            }
        }
    }
