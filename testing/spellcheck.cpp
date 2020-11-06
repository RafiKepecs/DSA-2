#include <iostream>
#include <fstream>
#include "hash.h"
using namespace std;


//function to determine if a character is valid
bool validCharacter(char &c){
  int A_bound = 65;
  int Z_bound = 90;
  int a_bound = 97;
  int z_bound = 122;
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

//Determins if word is valid
bool validWord(string &key){
  int validLetters = 0;
  for(int i = 0; i < key.length(); i++){
    if(validCharacter(key[i])){
      validLetters++;
    }
  }
  if (validLetters == key.length()){
    return true;
  }
  else{
    return false;
  }
}

//Loads dictionary into hashTable
hashTable loadDictionary(string dictionary){
  string str;
  ifstream file (dictionary);
  int numberOfLines = 0;
  hashTable h(49000);
  while(getline(file,str)){
    for (int i = 0; i < str.length(); i++){
      str[i] = tolower(str[i]);
    }
    if (validWord(str)){
      h.insert(str);
    }
  }
  file.close();
  return h;
}

//Spellchecks a file based on loaded dictionary and outputs to output file
void spellCheck(string document, string output, hashTable h){
  string str;
  ifstream file (document);
  ofstream file2 (output);
  string word = "";
  int line = 0;
  int digitFlag = 0;
  while(getline(file,str)){
    line++;
    for (int i = 0; i < str.length(); i++){
      if(48 <= int(str[i]) && int(str[i]) <= 57){
        word = "";
        digitFlag = 1;
      }
      else if(validCharacter(str[i])){
        word += tolower(str[i]);
      }
      if(!validCharacter(str[i]) || (i+1) == str.length()){
        if(digitFlag == 1){
          digitFlag = 0;
          word = "";
        }
        else if (word.length() > 20){
          word = word.substr(0,20);
          file2 << "Long word at line " << line << ", starts: " << word << "\n";
          word = "";
        }
        else if(!h.contains(word) && word != ""){
          file2 << "Unknown word at line " << line << ": " << word << "\n";
        }
        word = "";
      }
    }

  }

  file.close();
  file2.close();
}

int main(){
  string dictionary, document, output;
  cout << "Enter name of dictionary file: ";
  cin >> dictionary;
  clock_t start1, end1;
  start1 = clock();
  hashTable h = loadDictionary(dictionary);
  end1 = clock();
  double time_taken1 = double(end1-start1) / double(CLOCKS_PER_SEC);
  cout << "Time taken to load dictionary is: " << time_taken1 << " secs" << endl;
  h.display();
  cout << "Enter name of document to be spell checked: ";
  cin >> document;
  cout << "Enter name of output file: ";
  cin >> output;
  clock_t start2, end2;
  start2 = clock();
  spellCheck(document, output, h);
  end2 = clock();
  double time_taken2 = double(end2-start2) / double(CLOCKS_PER_SEC);
  cout << "Time taken to spellcheck file is: " << time_taken2 << " secs" << endl;
  return 0;
}
