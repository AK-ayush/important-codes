#include <iostream>
#include <vector>
using namespace std;


pair<int, int>search(const vector<vector<int>>&mat, int row, int col, int val){

  int r = 0;
  int c = col-1;
  // cout<<r<<" "<<c<<endl;
  while(r<row && c>=0){
    // cout<<r<<" "<<c<<endl;
    if(mat[r][c]>val) c--; //move left in columns
    else if (mat[r][c]<val) r++; //move down in rows
    else return make_pair(r,c);
  }
  return make_pair(-1,-1);
}


int main(){
  int r,c,val, t;
  cin>>r>>c>>val;

  vector<vector<int>>mat;
  vector<int>temp(c);

  for(int i=0;i<r;i++){
    for(int j=0;j<c;j++){
      cin>>t;
      temp[j]=t;
    }
    mat.push_back(temp);
  }
  // for(int i=0;i<r;i++){
  //   for(int j=0;j<c;j++){
  //     cout<<mat[i][j]<<" ";
  //   }
  //   cout<<"\n";
  // }
  pair<int, int> pos = search(mat, r, c, val);
  cout<<pos.first<<" "<<pos.second<<"\n";
  return 0;
}
