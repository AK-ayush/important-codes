#include <iostream>
#include <string>
using namespace std;

string compress(string s){
  string ret = "";
  int i=0, count=0;
  int n = s.length();
  while(i<n){
    ret = ret+s[i]; count=1;
    while(i+1<n && s[i]==s[i+1]){i++;count++;}
    ret = ret+to_string(count);
    i++;
  }

  return (n>ret.length())?ret:s;

}

int main(){
  string s = "aabcccccaaa";
  // output = "a2b1c5a3"
  string out = compress(s);
  cout<<out<<endl;
 return 0;
}
