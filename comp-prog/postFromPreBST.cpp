#include <iostream>
using namespace std;

int find_next_greater(int pre[], int l, int r, int val){
  for(int i=l;i<=r;i++){
    if(pre[i]>= val)return i;
  }
  return -1;
}

int find_next_smaller(int post[], int l, int r, int val){
  for(int i=r;i>=l;i--){
    if(post[i]<= val)return i;
  }
  return -1;
}

void postFromPre(int pre[], int l, int r, int min_val, int max_val){
  if(l>r)return;
  if (pre[l]<min_val || pre[l]>max_val)return;
  int idx = find_next_greater(pre, l+1, r, pre[l]);
  // left
  postFromPre(pre, l+1, idx-1, min_val, pre[l]);
  // right
  postFromPre(pre, idx, r, pre[l], max_val);
}

void preFromPost(int post[], int l, int r, int min_val, int max_val){
  if(l>r)return;
  if(post[r]<min_val || post[r]>max_val)return;
  cout<<post[r]<<" ";
  int idx = find_next_smaller(post, l, r-1, post[r]);
  //left
  preFromPost(post, l, idx, min_val, post[r]);
  //right
  preFromPost(post, idx+1, r-1, post[r], max_val);
}

int main(){
  int min_val,max_val;
  min_val = INT_MIN;
  max_val = INT_MAX;
  int pre[] = { 40, 30, 35, 80, 100 };
  int post[] = { 35, 30, 100, 80, 40 };
  int n = sizeof(pre) / sizeof(pre[0]);

  postFromPre(pre, 0, n-1, min_val, max_val);
  preFromPost(post, 0, n-1, min_val, max_val);
  return 0;
}
