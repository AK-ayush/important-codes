#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

void urlify(char* s, int n, int m){

  int i,j;
  i=n-1; j=m-1;
  while(i>=0){
    while(i>=0 && s[i]!=' ')s[j--]=s[i--];

    while(i>=0 && s[i]==' '){
      i--;
      s[j--]='0';
      s[j--]='2';
      s[j--]='%';
    }
  }
}

int main(){
  string s = "Mr John Smith    ";
  int n = 13;
  int m = s.length();
  char *char_arr = new char [m];
  strcpy(char_arr, s.c_str());
  urlify(char_arr, n, m);
  string ss  = char_arr;
  cout<<s<<endl;
  cout<<ss<<endl;
  return 0;
}
