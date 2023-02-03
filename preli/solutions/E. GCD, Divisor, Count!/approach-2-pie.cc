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

vector<pair<ll, int>> get_primes(ll x){
	vector<pair<ll, int>> ret;
	for(ll i = 2; i*i <= x; i++){
		if(x % i == 0){
			ret.emplace_back(i, 0);
			while(x % i == 0){
				x /= i;
				ret.back().second++;
			}
		}
	}

	if(x > 1)
		ret.emplace_back(x, 1);

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

		b/=a;

		vector<pair<ll, int>> primes = get_primes(b);

		ll ans = 0;

		for(int mask = 0; mask<(1<<primes.size()); mask++){
			int sign = 1;
			for(int j = 0; j<(int)primes.size(); j++){
				if(mask & (1<<j)){
					sign *= -1;
					primes[j].second--;
				}
			}

			int c = 1;
			for(int j = 0; j<(int)primes.size(); j++){
				if(primes[j].second > 0){
					c *= primes[j].second+1;
				}
			}

			ans += sign * modexpo(c, n);
			ans %= mod;
			if(ans < 0)
				ans += mod;

			for(int j = 0; j<(int)primes.size(); j++){
				if(mask & (1<<j)){
					sign *= -1;
					primes[j].second++;
				}
			}
		}


		cout<<ans<<"\n";
	}

	return 0;
}
