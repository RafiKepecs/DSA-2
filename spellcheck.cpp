#include <iostream>
#include <fstream>
#include "hash.h"
using namespace std;

//implement file parse with !validCharacter as word separators

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
hashTable loadDictionary(string dictionary){
  string str1, str2;
  ifstream file1 (dictionary);
  int numberOfLines = 0;
  while(getline(file1,str1)){
    if (validWord(str1)){
      numberOfLines++;
    }
  }
  file1.close();
  ifstream file2 (dictionary);
  hashTable h(numberOfLines);
  while(getline(file2,str2)){
    for (int i = 0; i < str2.length(); i++){
      str2[i] = tolower(str2[i]);
    }
    if (validWord(str2)){
      h.insert(str2);
    }
  }
  //cout << numberOfLines << endl;
  //h.display();
  file2.close();
  return h;
}

void spellCheck(string document, string output, hashTable h){
  string str;
  ifstream file (document);
  ofstream file2 (output);
  string word = "";
  int line = 0;
  int digitFlag = 0;
  while(getline(file,str)){
    line++;
    //cout << str.length() << endl;
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
          //cout << str.length() << endl;
        }
        word = "";
      }
      //cout << "i: " << i << ", string length: " << str.length() << endl;
    }

  }

  file.close();
  file2.close();
}

int main(){
  //hashTable(int) *h = new hashTable(5);

  string dictionary, document, output;
  cout << "Enter name of dictionary file: ";
  cin >> dictionary;
  //dictionary = "wordlist_small.txt";
  //cout << dictionary << endl;
  time_t start1, end1;
  time(&start1);
  hashTable h = loadDictionary(dictionary);
  time(&end1);
  double time_taken1 = double(end1-start1);
  cout << "Time taken to load dictionary is: " << time_taken1 << endl;
  cout << "Enter name of document to be spell checked: ";
  cin >> document;
  document = "lyrics.txt";
  //cout << document << endl;
  cout << "Enter name of output file: ";
  cin >> output;
  //output = "output.txt";
  //cout << output << endl;
  time_t start2, end2;
  time(&start2);
  spellCheck(document, output, h);
  time(&end2);
  double time_taken2 = double(end2-start2);
  cout << "Time taken to load dictionary is: " << time_taken2 << endl;
  return 0;
}
