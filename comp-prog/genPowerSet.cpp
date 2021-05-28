#include <iostream>
#include <vector>
using namespace std;

void genPowerSet(vector<int>s, vector<int>temp, vector<vector<int>>&result, int i){
  if(i==s.size()){
    result.push_back(temp);
    if(temp.size()==0)cout<<"empty set";
    for(int i=0;i<temp.size();i++)cout<<temp[i];
    cout<<endl;
    return;
  }
  genPowerSet(s, temp, result, i+1);
  temp.push_back(s[i]);
  genPowerSet(s, temp, result, i+1);
}

int main(){
  vector<int> s ={1,2,3,4};
  vector<int>temp;
  vector<vector<int>>result;
  genPowerSet(s, temp, result, 0);
  return 0;
}
