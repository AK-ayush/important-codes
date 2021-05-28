#include <iostream>
#include <cmath>
using namespace std;

const int N = 100001;

int primes[N];

void fill_prime(){
	for(int i = 1; i < N; i++)
		primes[i] = i;

	int k = 2*2;
	while(k < N){
		primes[k] = 2;
		k += 2;
	}

	for(int i = 3; i*i < N; i+=2){
		if(primes[i] == i){
			for(int j = i*i; j < N; j += i)
				primes[j] = i;
		}
	}
}

int main() {
	fill_prime();
	int t;
	cin>>t;
	long long x, p, np, i , cnt;
	int ans;
	while(t--){
        ans = 0; cnt=0;
	    	cin>>x>>p;
	    	np = x;
				i = 2;
				while( x > 1 && x%2 == 0){
					cnt++;
					x /= 2;
				}
				for( i = 3; i <= x; i += 2){
					if(primes[i] == i){
						// x = np;
						while(x > 1 && x%i == 0){
							cnt++;
							x /= i;
						}
					}
				}
				ans = cnt >= p ? 1 : 0;
	    	cout<<ans<<"\n";
	}
	return 0;
}
