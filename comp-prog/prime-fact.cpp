#include <iostream>
#include <unordered_map>
#include <vector>

#define mod (int)(1e9 + 7)
using namespace std;
const int N = 100000;

int* lpf = new int[N+1];

int least_prime_fact(){
  for(int i=1; i<=N; i++)
    lpf[i]=i;
  for(int i=2; i<=N; i++)
    if(lpf[i]==i)
      for (int j=i*2; j<=N; j+=i)
        if(lpf[j]==j)lpf[j]=i;

  return 0;
}

int power(int a, int p){
  if (p==0)return 1;
  if (p==1)return a;
  if (p==2)return (1LL * a * a)%mod;
  if (p&1)
    return (1LL * a * power(power(a, p/2)%mod, 2)%mod)%mod;
  else
    return (1LL * power(power(a, p/2)%mod, 2))%mod;
}


int main(){
  int n, temp;
  least_prime_fact();
  cout<<"enter n:"<<endl;
  cin>>n;
  int* a = new int[n];
  for(int i=0;i<n;i++)cin>>a[i];
  unordered_map<int, int>prime_fact;

  for(int i=0;i<n;i++){
    temp = a[i];
    unordered_map<int, int>single_num;
    while(temp>1){
      int x = lpf[temp];
      single_num[x]++;
      temp /=x;
    }
    if(i!=0){
      for(auto x:single_num){
        prime_fact[x.first] = max(prime_fact[x.first], x.second);
      }
    }
    else prime_fact = single_num;
  }
  long long sum=0, lcm=1;

  //lcm of the array
  for(auto x:prime_fact){
      lcm = (lcm * power(x.first, x.second))%mod;
  }
  //sum of the array B
  for (int i=0;i<n;i++){
    sum = (sum + lcm/a[i])%mod;
  }

  cout<<"factors of array"<<endl;
  for(auto x:prime_fact){
    cout<<x.first<<"->"<<x.second<<endl;
  }
  cout<<"lcm and sum of the array "<<lcm<<"--"<<sum<<endl;
  return 0;
}
