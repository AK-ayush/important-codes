#include <iostream>
#include <vector>
using namespace std;

int rotatedBS(const vector<int>inp, int l, int r, int val){
  cout<<l<<"---"<<r<<endl;
  if(l>r)return -1;
  if(l==r)return l;
  int mid = (l+r)/2;
  if(inp[mid]==val)return mid;
  if(inp[l]<inp[r]){ //not rotated
    if(inp[mid]<val)
      return rotatedBS(inp, mid+1, r, val); //right
    return rotatedBS(inp, l, mid, val);
  }
  
  if(inp[mid]<val){
    if(inp[l]>val)
      return rotatedBS(inp, mid+1, r, val); //right
    return rotatedBS(inp, l, mid, val); //left
  }
  if(inp[r]>val)
    return rotatedBS(inp, mid+1, r, val); //right
  return rotatedBS(inp, l, mid, val);// left
}

int main(){
  int n, val, t;
  cin>>n>>val;
  vector<int>inp(n);
  for(int i=0;i<n;i++){
    cin>>t;
    inp[i]=t;
  }
  cout<<rotatedBS(inp, 0, n-1, val)<<endl;
  return 0;
}
