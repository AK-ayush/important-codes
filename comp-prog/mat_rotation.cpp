#include <iostream>
#include <vector>
using namespace std;

void rotate_matrix(vector<vector<int>>&mat){
  int temp, n=mat.size(), ct=0;
  int l,r, i;
  while(ct<n/2){
    l = ct; r = n-1-ct;
    i=l;
    while(i<r){
      temp = mat[l][l+i];
      mat[l][l+i] = mat[l+i][r];
      mat[l+i][r] = mat[r][r-i];
      mat[r][r-i] = mat[r-i][l];
      mat[r-i][l] = temp;
      i++;
    }
    ct++;
  }
}

int main(){
  vector<vector<int>> mat;
  mat.push_back(vector<int>{1,2,3, 11});
  mat.push_back(vector<int>{4,5,6, 12});
  mat.push_back(vector<int>{7,8,9, 13});
  mat.push_back(vector<int>{10,20,30, 40});
  for(int i=0;i<mat.size();i++){
    for(int j=0;j<mat[0].size(); j++)cout<<mat[i][j]<<" ";
    cout<<endl;
  }
  cout<<"------\n";
  rotate_matrix(mat);
  for(int i=0;i<mat.size();i++){
    for(int j=0;j<mat[0].size(); j++)cout<<mat[i][j]<<" ";
    cout<<endl;
  }
  return 0;
}
