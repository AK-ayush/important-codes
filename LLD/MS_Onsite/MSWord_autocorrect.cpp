
/*
Input: "Copyright (c) Microsoft Corporation --> Test"
       "Copyright O"
        idx = 9 -> ++idx
        i = 13  
idx = 0

(i,j)
 mapping = {"(c)" : O}

Input[i..j] is maching in mapping

Input[i] = mapping[Input[i..j]]
*/

#include <vector>
using namespace std;

class Trie{
    bool isEncoding;
    char newEncoding;
    vector<Trie*> children;
};



// Input: "Copyright (c) Microsoft Corporation --> Test"
void solve(char s[], int n){
    int idx = -1;
    int i = 0, j = 0;
    Trie* curr = dict, root;

    while(i < n){
        j = i;
        curr = dict;
        root = dict;
        while(j < n ){
            if(curr->children[s[j]] != nullptr){
                curr = curr->children[s[j]];
                j++;
            }
            else
                break;
        }

        if(curr->isEncoding){
            s[++idx] = curr->newEncoding;
        }
        else{
            
        }

        if(j < n){
            s[++idx] = s[j];
        }
        i = j+1;
    }
    
}



