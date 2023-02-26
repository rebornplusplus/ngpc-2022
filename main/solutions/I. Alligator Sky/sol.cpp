#include<bits/stdc++.h>
using namespace std;

void solve()
{
    int n,k;
    cin>>n>>k;
    if(k==1)
    {
        cout<<n<<'\n';
    }
    else
    {
        cout<<(n/k)*2+((n%k)>0)<<'\n';
    }
}
main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}
