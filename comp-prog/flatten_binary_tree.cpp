/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    pair<TreeNode*,TreeNode*> convert(TreeNode* root){
        if(!root)return make_pair(nullptr, nullptr);
        if(!root->left && !root->right)return make_pair(root, root);
        pair<TreeNode*,TreeNode*> left(nullptr, nullptr);
        pair<TreeNode*,TreeNode*> right(nullptr, nullptr);

        left = convert(root->left);
        right = convert(root->right);

        if(!root->left){
            root->right=right.first;
            return make_pair(root, right.second);
        }
        if(!root->right){
            root->right=left.first;
            root->left=nullptr;
        }
        root->right=left.first;
        root->left=nullptr;
        left.second->right=right.first;
        return make_pair(root, right.second);
    }

    void flatten(TreeNode* root) {
        if(!root)return root;
        pair<TreeNode*, TreeNode*> head_tail = convert(root);
        root=head_tail.first;
    }
};
