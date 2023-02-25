#include<bits/stdc++.h>
#define pb push_back
#define ll long long
using namespace std;

const int mod = 998244353;
int dp[2005][2005];

int solve(int i,int j){
    if(i==0) return j==0;
    int &ret = dp[i][j+2];
    if(ret!=-1) return ret;
    ret=0;
    ret=(ret+solve(i-1,j+1))%mod;
    if(j-1>=-2) ret=(ret+solve(i-1,j-1))%mod;
    return ret;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    memset(dp,-1,sizeof dp);

    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        cout<<solve(n*2,0)<<'\n';
    }
    return 0;
}