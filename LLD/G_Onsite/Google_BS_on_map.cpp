/*
Implement two functions:

receive: one that takes in timestamp and number pair (not necessarily chronological)

cumsum: one that give timestamp, calculates cumulative sum

i.e.

receive((10, 100))
receive((5, 10))
receive((40, 30))
cumsum(20) -> print 110 (10 at timestamp 5, 100 at timestamp 10 added)
receive((10, 40))
receive((50, -30))
cumsum(10) -> print 140 (100 at timestamp 10, 40 at timestamp 10 added)
cumsum(60) -> print 150 (10 at timestamp 5, 100 at timestamp 10, 30 at timestamp 40, 40 at timestamp 10, -30 at timestamp 50 added)
cumsum(2) -> print 0 (nothing added at that time)
*/




#include <iostream>
#include <map>
using namespace std;


class Solution {
    map<int, int> timeToVal;
public:
    void cumsum(int );
    void recieve(int, int);
};

void Solution::recieve(int t, int val){
    this->timeToVal[t] += val;
}

void Solution::cumsum(int t){
    map<int, int>::iterator it;
    int sum = 0;
    for(it = timeToVal.begin(); it != timeToVal.end(); ++it){
        if(it->first > t) break;
        sum += it->second;
    }
    cout<<sum<<endl;
}

int main(){
    Solution solve;
    solve.recieve(10, 100);
    solve.recieve(5, 10);
    solve.recieve(40, 30);
    solve.cumsum(20);
    solve.recieve(10, 40);
    solve.recieve(50, -30);
    solve.cumsum(10);
    solve.cumsum(60);
    solve.cumsum(2);
    return 0;
}