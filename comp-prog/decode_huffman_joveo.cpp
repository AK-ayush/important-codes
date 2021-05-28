#include <bits/stdc++.h>
using namespace std;

struct Node{
    Node * left,*right;
    char val;
    Node(char c) : left(NULL), right(NULL),val(c){}
};

struct data{
    char ch;
    int len;
    string repr;
    data(char ch, int len, string repr) : ch(ch), len(len), repr(repr) {}
};

Node* buildTree(int& idx, string s){
    if(idx == s.length()) return nullptr;
    Node* root = new Node(s[idx]);
    if(s[idx] == '*'){
        idx++;
        root->left = buildTree(idx, s);
        root->right = buildTree(idx, s);
    }
    else{
        idx++; // created the external node
    }
    return root;
}

Node* constructTree(string preorder) {
    // part 1
    int n = preorder.length();
    // cout<<"in here :"<<preorder<<preorder.length()<<endl;
    if(n == 0) return nullptr;
    // if(n == 1)
    // {
    //     Node* root = new Node('*');
    //     Node* left = new Node(preorder[0]);
    //     root->left = left;
    //     cout<<root->val<<endl;
    //     return root;
    // }
    int idx = 0;
    return buildTree(idx, preorder);
}

char decodeChar(Node* root, string s, int &idx){
    Node* curr = root;
    while(curr && curr->val == '*'){
        if(s[idx++] == '0')
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr->val;
}

string decodeMessage(Node *root, string encodedMessage) {
    // part 2
    string output = "";
    int idx = 0;
    while(idx  < encodedMessage.length()){
        output += decodeChar(root, encodedMessage, idx);
    }
    return output;
}

void stats(string encodedMessage, string decodedMessage) {
    // part 3
    int numBits = encodedMessage.length();
    int charBits = decodedMessage.length();
    float ratio = (float)numBits/(charBits*8);
    cout<<"Number of bits       = "<< numBits<<endl;
    cout<<"Number of characters = "<< charBits<<endl;
    ratio *= 100;
    printf("Compression ratio    = %.2f%%",ratio);
}

void getPreorder(Node* root, vector<data>& result, string curr){
    if(!root) return;
    if(root->val == '*'){
        getPreorder(root->left, result, curr+"0");
        getPreorder(root->right, result, curr+"1");
    }
    else{
        // cout<<curr<<endl;
        result.push_back({root->val, curr.length(), curr});
    }
}

void printPreorder(Node *root) {
    // part 4
    cout<<"character bits encoding\n";
    cout<<"-----------------------\n";
    vector<data> result;
    getPreorder(root, result, "");
    for(int i = 0; i < result.size(); i++){
        cout<<result[i].ch<<" "<<result[i].len<<" "<<result[i].repr<<"\n";
    }
}

int main() {
    string s;
	vector<string> lines;
	while(getline(cin,s)){
	   lines.push_back(s);
	}
    string preorder = "";
    for (int i = 0; i < lines.size() - 1; i++) {
        preorder += lines[i]+"\n";
    }
    string encodedMessage = lines.back();
    // cout<<preorder.length()<<endl;
    Node *root = constructTree(preorder);
    string decodedMessage = decodeMessage(root, encodedMessage);
    printPreorder(root);
    cout<<endl;
    cout<<decodedMessage<<endl;
    stats(encodedMessage, decodedMessage);
    return 0;
}
