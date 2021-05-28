#include<iostream>
#include<vector>

using namespace std;

struct TreeNode{
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


void print_tree(TreeNode* root){
  if(!root)return;

  print_tree(root->left);
  cout<<root->val<<" ";
  print_tree(root->right);
}



pair<int, int> find_child(vector<int>vec, int val){
  int left,right;
  left=right=-2;
  for(int i=0;i<vec.size();i++){
    if(vec[i]==val){
      if(left==-2)left=i;
      else if(right==-2)right=i;
    }
  }
  return make_pair(left, right);

}

TreeNode* constructTree(vector<int>vec, int root_val){
  if(root_val==-2)return NULL;

  TreeNode* root = new TreeNode(root_val);
  pair<int, int>idx_pair = find_child(vec, root_val);

  root->left = constructTree(vec, idx_pair.first);
  root->right = constructTree(vec, idx_pair.second);
  return root;
}

int main(){
  vector<int>vec{2,2,5,4,5,-1,1};
  int root_val;
  for(root_val=0;root_val<vec.size();root_val++)
    if(vec[root_val]==-1)break;
  TreeNode* root = constructTree(vec, root_val);
  print_tree(root);
  return 0;
}
