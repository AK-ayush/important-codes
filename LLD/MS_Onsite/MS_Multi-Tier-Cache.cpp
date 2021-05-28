#include <exception>
#include <iostream>
#include <string>
#include <map>

using namespace std;
/*
class t1 -> class t2


*/

class Cache {
    string name;
    Cache* Parent;
    void updateValue(int , int); 
protected:
    int getUsingKeyCore(int); //return the value, concrete classes imp
    int setUsingKeyCore(int, int); //
public:
    int getUsingKey(int);
};

class T1 : public Cache {
    map<int, int> storage;
public:
    T1(Cache*); // nullptr
    int getUsingKey(int);
};

class T2 : public Cache { // redis based
    map<int, int> storage;  
public:
    T2(Cache*); // // parent = T1
    int getUsingKey(int);
};

class T3 : public Cache { //memory cache
    map<int, int> storage;
public:
    T3(Cache*); // // parent = T2
    int getUsingKey(int);
};

int Cache::getUsingKey(int key ){
    int val = getUsingKeyCore(key); // check the expection 
    if(/*no exception*/)   return val;
    
    if(Parent == nullptr){
        cout<<"Key not found!\n";
    }
    int val = Parent->getUsingKey(key);  // check for the exception if not found 
    setUsingKeyCore(key, val);
    return val;
}


int T3::getUsingKeyCore(int key){
    if(storage.count(key)){
        return storage[key];
    }
    throw std::exception("key not found");
}

void T3::setUsingKeyCore(int key, int val){
    /* eviction mechanism*/
    storage[key] = val;
}

int main() {
    // you can write to stdout for debugging purposes, e.g.
    std::cout << "This is a debug message" << std::endl;

    
    T1 tier1(nullptr); // DB cache

    T2 tier2(&tier1); // Redis cache
    T3 tier3(&tier2); // mem cache

    tier3.getUsingKey(2); 
     
    return 0;
}
