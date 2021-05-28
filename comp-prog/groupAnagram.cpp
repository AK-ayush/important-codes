#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void groupAnagram(vector<string>&inp){
  unordered_map<string, vector<string>>umap;
  vector<string>::iterator v_it;
  string temp;
  for(v_it=inp.begin();v_it!=inp.end();v_it++){
    temp = *v_it;
    sort(temp.begin(), temp.end());
    umap[temp].push_back(*v_it);
  }
  int k=0;
  unordered_map<string, vector<string>>::iterator u_it;
  for(u_it=umap.begin();u_it!=umap.end();u_it++){
    // cout<<*u_it<<endl;
    vector<string> value=u_it->second;
    for (auto v:value)inp[k++]=v;
  }
}

int main(){
  vector<string>inp;
  string s;
  int n;
  cin>>n;
  while(n--){
    cin>>s;
    inp.push_back(s);
  }
  groupAnagram(inp);
  for(auto s:inp)cout<<s<<endl;
  return 0;
}
