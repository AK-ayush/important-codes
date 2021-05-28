#include <iostream>
using namespace std;

void merge(int a[], int idx[], int count[], int p, int q, int r){
  int n,m;
  n = q-p+1;
  m = r-q;
  int S[m+n];
  int Si[m+n];
  int cnt=0,i,j,k=0;
  i = p;j=q+1;
  while(i<=q && j<=r){
    if(a[i]<a[j]){
      S[k]=a[i];
      Si[k]=idx[i];
      count[idx[i]]+=cnt;
      k++;i++;
    }//if
    else{
      S[k]=a[j];
      Si[k]=idx[j];
      cnt++;
      k++;j++;
    }//else
  }//while

  while(i<=q){
      S[k]=a[i];
      Si[k]=idx[i];
      count[idx[i]]+=cnt;
      k++;i++;
    }//i-while
  while(j<=r){
      S[k]=a[j];
      Si[k] = idx[j];
      k++;j++;
    }//j-while


//copy back the temp arrays to original arrays
for (i=0;i<k;i++){
  a[p+i]=S[i];
  idx[p+i]=Si[i];
 }//for
}//merge







void mergeSort(int a[], int idx[], int count[], int p, int r){
if (p<r){
    int q = (p+r)/2;
    mergeSort(a, idx, count, p, q);
    mergeSort(a, idx, count, q+1, r);
    merge(a,idx,count,p,q,r);
  }//if
}// end mergeSort


int main(){
int a [] = {12, 3, 4, 2, 5, 1};
int idx[] = {0, 1, 2, 3, 4, 5};
int cnt[] = {0, 0, 0, 0, 0, 0};
int n=6;
mergeSort(a,idx,cnt,0,n-1);
for(int i=0;i<n;i++)
  cout<<cnt[i]<<"  ";
cout<<endl;
for(int i=0;i<n;i++)
  cout<<a[i]<<"  ";
cout<<endl;
for(int i=0;i<n;i++)
  cout<<idx[i]<<"  ";
cout<<endl;
return 0;
}
