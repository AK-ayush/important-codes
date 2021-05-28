#include <iostream>
#include <string>
#include <vector>
using namespace std;



void genParens(string s, int open, int close){
  // cout<<s<<"\n";
  if(open==0 && close==0){
    cout<<s<<"\n";
    return;
  }
  if(open > 0)
    genParens(s+'(', open-1, close);
  if(close > 0 && close > open)
    genParens(s+')', open, close-1);
}


int main(){
  int n;
  cin>>n;
  string s="";
  genParens(s, n, n);
  return 0;
}
