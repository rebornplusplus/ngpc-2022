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

int gauss(int n, int m, vector< vector<int> >ar, vector<int>& res){
    res.assign(m, 0);
    vector <int> pos(m, -1);
    int i, j, k, l, p, d, free_var = 0;
    const long long MODSQ = (long long) mod * mod;
    for (j = 0, i = 0; j < m && i < n; j++){
        for (k = i, p = i; k < n; k++){
            if (ar[k][j] > ar[p][j]) p = k;
        }
        if (ar[p][j]){
            pos[j] = i;
            for (l = j; l <= m; l++) swap(ar[p][l], ar[i][l]);
            d = modinv(ar[i][j]);
            for (k = 0; k < n && d; k++){
                if (k != i && ar[k][j]){
                    int x = ((long long)ar[k][j] * d) % mod;
                    for (l = j; l <= m && x; l++){
                        if (ar[i][l]) ar[k][l] = (MODSQ + ar[k][l] - ((long long)ar[i][l] * x)) % mod;
                    }
                }
            }
            i++;
        }
    }
    for (i = 0; i < m; i++){
        if (pos[i] == -1) free_var++;
        else res[i] = (long long) ar[pos[i]][m] * modinv(ar[pos[i]][i]) % mod;
    }
    for (i = 0; i < n; i++) {
        long long val = 0;
        for (j = 0; j < m; j++) val = (val + (long long)res[j] * ar[i][j]) % mod;
        if (val != ar[i][m]) return -1;
    }
    return free_var;
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

    vector< vector<int> >Mat(n, vector<int>(n+1));
    for(int i=0, j=1; i<n; i++, j=(j+1)%n){
        Mat[i][j] = Y[i];
        Mat[i][i] = mod - 1;
        Mat[i].back() = (mod-X[i])%mod;
    }

    vector<int>res;
    gauss(n, n, Mat, res);
    ll ans = (res[0]+mod) % mod;

    cout<<ans<<"\n";
}


