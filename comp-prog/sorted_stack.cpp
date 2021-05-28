#include <stack>
#include <iostream>
using namespace std;

class SortedStack{
  stack<int> s1; // main stack
  stack<int> s2;  //aux stack
public:
  void pop(){
    if(!s1.empty())
      s1.pop();
    else cout<<"stack is empty()";
  }
  int peek(){
    if(!s1.empty())
      return s1.top();
    else cout<<"stack is empty!";
  }
  bool empty(){
    return s1.empty();
  }
  void push(int val){
    while(!s1.empty() && s1.top()<val){
      s2.push(s1.top());
      s1.pop();
    }
    s1.push(val);
    while(!s2.empty()){
      s1.push(s2.top());
      s2.pop();
    }
  }

};

int main(){
  SortedStack ss;
  ss.push(12);
  ss.push(22);
  ss.push(0);
  ss.push(11);
  cout<<ss.peek()<<endl;
  ss.pop();
  cout<<ss.peek()<<endl;
  ss.pop();
  cout<<ss.peek()<<endl;
  ss.pop();
  cout<<ss.peek()<<endl;
  ss.pop();
  cout<<ss.peek()<<endl;
  ss.pop();
  return 0;
}
