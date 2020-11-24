#include <string>
#include <iostream>

using namespace std;

int merge(string a, string b, string c){
  if ((a == "") && (b == "") && (c == "")){
    return true;
  }

  else if((c == "") && ((a != "") || (b != ""))){
    return false;
  }

  bool Merge = false;

  if(a[0] == c[0]){
    Merge = merge(a.substr(1), b, c.substr(1));
  }

  if(b[0] == c[0] && Merge == false){
    Merge =  merge(a, b.substr(1), c.substr(1));
  }

  return Merge;
}

int main(){
  string A = "aa";//"aa";//
  string B = "ab";//"ab";//
  string C = "abaa";//"abaa";//
  int res = merge(A, B, C);
  cout << res << endl;
  return 0;
}
