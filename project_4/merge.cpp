#include <string>
#include <iostream>

using namespace std;

//Change the array size!
int db[10][10] = {0};

string merge(string a, string b, string c){
  int n = a.length();
  int m = b.length();
  string Merge = "*** NOT A MERGE ***";
  for(int i = 0; i < n+1; i++){
    for(int j = 0; j < m+1; j++){
      if((i == 0) && (j == 0)){
      }
      else{
        if(b[j-1] == c[i+j-1]){
          //cout << "i, j = " << i << ", " << j << ", " << c[i+j-1] << endl;
          db[i][j] = 1;
        }
        else if(a[i-1] == c[i+j-1]){
          //cout << "i, j = " << i << ", " << j << ", " << c[i+j-1] << endl;
          db[i][j] = 1;
        }
      }
    }
    for(int i = 0; i < n+1; i++){
      for(int j = 0; j < m+1; j++){

      }
    }
  }
  return Merge;
}

int main(){
  string A = "aa";//"aa";//
  string B = "ab";//"ab";//
  string C = "abaa";//"abaa";//
  string res = merge(A, B, C);
  cout << res << endl;
  for(int i = 0; i < A.length()+1; i++){
    for (int j = 0; j < B.length()+1; j++){
      cout << db[i][j];
    }
    cout << endl;
  }
  return 0;
}
