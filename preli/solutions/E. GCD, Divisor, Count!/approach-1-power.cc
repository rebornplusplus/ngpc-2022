// @author: Sabbir Rahman Abir

#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

const int mod = 1e9+7;

ll modexpo(ll x, ll n){
	ll ret = 1;
	while(n){
		if(n & 1)
			ret = (ret * x) % mod;
		x = (x * x) % mod;
		n >>= 1;
	}
	return ret;
}

vector<ll> get_primes(ll x){
	vector<ll> ret;
	for(ll i = 2; i*i <= x; i++){
		if(x % i == 0){
			ret.push_back(i);
			while(x % i == 0)
				x /= i;
		}
	}

	if(x > 1)
		ret.push_back(x);

	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int tc;
	cin>>tc;

	for(int cs = 1; cs <= tc; cs++){
		int n;
		ll a, b;
		cin>>n>>a>>b;

		if(b % a != 0){
			cout<<0<<"\n";
			continue;
		}

		vector<ll> primes = get_primes(b);

		ll ans = 1;

		for(ll p : primes){
			int e1 = 0, e2 = 0;
			while(a % p == 0){
				e1++;
				a /= p;
			}

			while(b % p == 0){
				e2++;
				b /= p;
			}

			int c = e2-e1+1;

			ans *= (modexpo(c, n) - modexpo(c-1, n) + mod);
			ans %= mod;
		}

		cout<<ans<<"\n";
	}

	return 0;
}
