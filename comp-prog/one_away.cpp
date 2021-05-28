#include <iostream>
#include <string>
using namespace std;

bool one_away(string s1, string s2){

  int n=s1.length();
  int m=s2.length();
  if(abs(n-m)>1)return false;
  int i=0,j=0;
  int cnt=0;
  while(i<n && j<m){

    if(s1[i]!=s2[j]){
      if(cnt==1)return false;
      cnt++;
      if(n==m){i++;j++;} // replace
      else if(n<m) j++;   //insert in s1
      else i++; //insert in s2
    }
    else{
      i++;j++;
    }
  }
  return cnt<=1;
}

int main(){

  string s1,s2;
  cin>>s1>>s2;
  cout<<one_away(s1, s2)<<endl;
  return 0;
}
