#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll power(ll a, ll p) {
  ll ans = 1;
  while (p) {
    if (p & 1) ans = (1LL*ans*a)%mod;
    a = (1LL*a*a)%mod; p >>= 1;
  } return ans;
}

ll modinv(ll a){
    return power(a, mod-2);
}

const int n = 11;
const ll inv100 = modinv(100);

int main(){
    ios::sync_with_stdio(false), cin.tie(0);

    deque<ll>a(n), b(n);
    for(auto &x : a){
        cin>>x;
        assert(x>=1 and x<100);
    }
    for(auto &x : b){
        cin>>x;
        assert(x>=1 and x<100);
    }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    for(int i=0; i<5; i++){
        a.push_back(a.front()), b.push_back(b.front());
        a.pop_front(), b.pop_front();
    }

    vector<ll>X(n), Y(n);
    for(int i=0; i<n; i++){
        a[i] = a[i] * inv100 % mod;
        b[i] = b[i] * inv100 % mod;

        X[i] = a[i] * (1 - b[i]) % mod;
        if(X[i]<0) X[i] += mod;

        Y[i] = (a[i] * b[i] + (1 - a[i]) * (1 - b[i]) ) % mod;
        if(Y[i]<0) Y[i] += mod;
    }

    ll ans = 0;
    for(int i=0; i<n; i++){
        ll gun = 1;
        for(int j=0; j<i; j++){
            gun = gun * Y[j] % mod;
        }
        ans = (ans + X[i] * gun) % mod;
    }
    ll yall = 1;
    for(int j=0; j<n; j++)
        yall = yall * Y[j] % mod;

    ll bhag = (1 - yall + mod) % mod;
	assert(bhag);
    ans = ans * modinv(bhag) % mod;
    cout<<ans<<"\n";
}

