#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


vector<int> max_array(vector<int> &A){
  int gi=-1,ci=-1;
  int gn=0,cn=0;
  long long gsum=0,csum=0;
  for(int i=0;i<A.size();i++){
    if(A[i]>=0){
      ci = (-1==ci)?i:ci;
      csum +=A[i];
      cn++;
    }
    else if((gsum<csum) || (gsum==csum && cn>gn)){
      gi=ci;ci=-1;
      gsum=csum;csum=0;
      gn=cn;cn=0;
    }
  }
  cout<<gi<<"=="<<gn<<"=="<<gsum<<endl;
  return vector<int>(A.begin()+gi, A.begin()+gi+gn);
/*
//To test it from main()
vector<int> v = {-1, -2, -3 ,-1, -1};
vector<int> ret = max_array(v);
for(int i=0;i<ret.size();i++)
cout<<ret[i]<<endl;
*/
}

struct p{
  int i;
  int j;
};

struct p subarray_sum(vector<int>&A, long long sum){
  int i=0,j=1;
  long long csum = A[0];
  int n = A.size();
  while(j<=n && i<j){
    if(csum<sum && j<n)
      csum +=A[j++];
    else if(csum>sum)
      csum -=A[i++];
    else
      break;
    //cout<<i<<"in while"<<j<< "sum"<<csum<<endl;
  }
  struct p ret;
  ret.i=i;
  ret.j=j-1;
  return ret;
}

// int count_triplet(vector<int>&A){
//   sort(A.begin(), A.end());
//   int i=0,j=1,k=2;
//   int count = 0;
//   while(k<n && j<k && i<j){
//     if(A[i]+A[j]>A[k]){
//       k++;
//     }
//     else if (A[i]+A[j]<A[k]){
//
//     }
//   }
// }

//kadane algorithm
vector <int> max_sum_subarray(vector<int> &A){
  int meh = A[0];
  int msf = A[0];
  int st=0;int n=1;
  for(int i=1;i<A.size();i++){
    if(A[i]>(meh+A[i])){
      meh = A[i];st=i;n=1;
    }
    else{
      meh +=A[i]; n++;
    }
  }
  msf = (msf>meh)?msf:meh;
  ret = vector<int>(A.begin()+st, A.begin()+st+n);
  return ret;
}


/*-------------------------------*/
int main(){
  vector<int> v = {2, 1, 3 ,7, 5};
  struct p ret = subarray_sum(v, 9);
  cout<<ret.i<<"--"<<ret.j<<endl;

  return 0;
}
