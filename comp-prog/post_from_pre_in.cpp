#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// int find_idx(int in[], int n, int key)
// {
//   for(int i=0;i<n;i++){
//     if(in[i]==key)return i;
//   }
// }

void printPost(int in[], int pre[], unordered_map<int, int> umap, int *preIdx, int l, int r, int n)
{
   if(l>r)return;
   //int root_idx = find_idx(in, n, pre[*preIdx]);
   int root_idx = umap[pre[*preIdx]];
   (*preIdx)++;
   printPost(in, pre, umap, preIdx, l, root_idx-1, 6);
   printPost(in, pre, umap, preIdx, root_idx+1, r, 6);
   cout<<in[root_idx]<<" ";
}

int main(){
  int in[] = {4, 2, 5, 1, 3, 6};
  int pre[] = {1, 2, 4, 5, 3, 6};
  int preIdx = 0;
  int n=6;
  unordered_map<int, int> umap;
  for(int i=0;i<n;i++)umap[in[i]]=i;

  printPost(in, pre, umap, &preIdx, 0, n-1, n);
  return 0;
}
