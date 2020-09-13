#include <iostream>
#include <fstream>
#include "hash.h"
using namespace std;

bool validCharacter(char c){
  int A_bound = 65;
  int Z_bound = 90;
  int a_bound = 97;
  int z_bound = 122;
  //NOTE - check if the digit values are actually using ascii!!!
  int zero_bound = 48;
  int nine_bound = 57;
  int dash = 45;
  int apos = 39;

  if ( (A_bound <= int(c) && int(c) <= Z_bound) ||
       (a_bound <= int(c) && int(c) <= z_bound) ||
       (zero_bound <= int(c) && int(c) <= nine_bound) ||
       (int(c) == dash) ||
       (int(c) == apos) ){
         return true;
  }
  else{
    return false;
  }
}

bool validWord(string key){
  int validLetters = 0;
  for(int i = 0; i < key.length(); i++){
    if(validCharacter(key[i])){
      validLetters++;
    }
  }
  //cout << validLetters << endl;
  if (validLetters == key.length()){
    return true;
  }
  else{
    return false;
  }
}

//I don't know why it's forcing me to using 2 files to parse a second time
void loadDictionary(string input){
  string str1, str2;
  ifstream file1 (input);
  int numberOfLines = 0;
  while(getline(file1,str1)){
    if (validWord(str1)){
      numberOfLines++;
    }
  }
  file1.close();
  ifstream file2 (input);
  hashTable h(numberOfLines);
  while(getline(file2,str2)){
    if (validWord(str2)){
      h.insert(str2);
    }
  }
  cout << numberOfLines << endl;
  //h.display();
  file2.close();
}

void spellCheck(){

}

int main(){
  //hashTable(int) *h = new hashTable(5);

  string input;
  cout << "Enter name of input file: ";
  //cin >> input;
  input = "wordlist_small.txt";
  cout << input << endl;
  loadDictionary(input);
  /*
  string test = "antony";
  //cout << test << endl;
  if (validWord(test)){
    cout << "good" << endl;
  }
  if (validWord("&&7fdsf&&dfs")){
    cout << "error" << endl;
  }
  */
  //parse the dictionary

  return 0;
}
