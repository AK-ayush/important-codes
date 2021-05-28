#include <iostream>
using namespace std;

int binary_search1(int arr[], int l, int r, int val)
{
  if(l>r)return -1;
  if(l==r)return (arr[l]==val)?l:-1;
  int mid = (l+r)/2;
  if(arr[mid]<val)
    return binary_search1(arr, mid+1, r, val);
  return binary_search1(arr, l, mid, val);
}

int binary_search2(int arr[], int l, int r, int val)
{
  if(l>r)return -1;
  if(l==r)return (arr[l]==val)?l:-1;
  int mid = (l+r)/2;
  if(arr[mid]>val)
    return binary_search2(arr, l, mid-1, val);
  return binary_search2(arr, mid, r, val);
}

int main(){
  int arr[] = {1,3,4,5,5,5,8,9};
  int val;
  cin>>val;
  int idx1 = binary_search1(arr, 0, 7, val);
  int idx2 = binary_search2(arr, 0, 7, val);
  cout<<idx1<<"---"<<idx2<<endl;
  return 0;
}
