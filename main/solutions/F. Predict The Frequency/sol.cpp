#include<bits/stdc++.h>
#define N 202
#define fast ios_base::sync_with_stdio(0);cin.tie(0);
#define ll long long
using namespace std;


int M;
int bigmod(ll a,ll b)
{
    a %= M;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

int f[N];
int inv[N];

void init()
{
    f[0]=inv[0]=1;
    for(int i=1;i<N;i++)
    {
        f[i]=(1LL*f[i-1]*i)%M;
    }
    inv[N-1]=bigmod(f[N-1],M-2);
    for(int i=N-2;i>=0;i--)
    {
        inv[i]=1LL*inv[i+1]*(i+1)%M;
    }
    return;
}
int C(int n,int r)
{
    if(n<r)
        return 0;
    return 1LL*f[n]*inv[r]%M*inv[n-r]%M;
}

int dp[N][N][N];

int run(int n,int m,int x)
{
    if(n==0)
    {
        return 1;
    }
    if(x==0) return 0;
    if(dp[n][m][x]!=-1)
        return dp[n][m][x];
    int ans=0;
    int pw=1;
    for(int k=0;k<=min(m,n/x);k++)
    {
        int temp=1LL*C(m,k)*pw%M*run(n-k*x,m-k,x-1)%M;
        ans+=temp;
        if(ans>=M)
            ans-=M;
        pw=1LL*pw*inv[x]%M;
    }
    return dp[n][m][x]=ans;
}

void solve()
{
    int n,m,x;
    cin>>n>>m>>x;

    int sum=0,cnt=0;

    for(int mx=x;mx>=1;mx--)
    {
        int temp=run(n,m,mx)-run(n,m,mx-1);
        if(temp<0) temp+=M;
        sum=(sum+1LL*temp*mx)%M;
    }
    int ans=sum;
    ans=(1LL*ans*f[n])%M;
    cout<<ans<<'\n';
}

main()
{
    fast;
    memset(dp,-1,sizeof dp);

    int t;
    cin>>t;
    cin>>M;
    init();

    while(t--)
    {
        solve();
    }
}

