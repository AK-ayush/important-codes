#include <iostream>
#include <string>
#include <vector>
using namespace std;
void swap(string &s, int i, int j){
  char t = s[i];
  s[i] = s[j];
  s[j] = t;
}

void permute(string s, int idx, vector<string>&result){
  if(idx>=s.length()){
    cout<<s<<"\n";
    result.push_back(s);
    return;
  }
  permute(s, idx+1, result);
  for(int j=idx;j<s.length();j++){
    if(s[idx-1]!=s[j]){
      swap(s, idx-1, j);
      permute(s, idx+1, result);
      swap(s, idx-1, j);
    }
  }
}

int main(){
  string s="abb";
  vector<string>result;
  permute(s, 1, result);
  return 0;
}
