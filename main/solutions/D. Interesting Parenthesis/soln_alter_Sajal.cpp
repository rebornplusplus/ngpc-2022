#include<bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL)
#define LL long long
#define MAX (LL) 4e18
#define MOD 998244353
#define N 1005
#define endl "\n"
using namespace std;
namespace fs = std::filesystem;


int dpp[N][N];

int CountBrackets(int opening, int closing)
{
    if (closing - opening < -2 || opening < 0 || closing < 0) return 0;
    if (opening == 0 && closing == 0) return 1;
    if (dpp[opening][closing] != -1) return dpp[opening][closing];
    int ans = CountBrackets(opening - 1, closing) + CountBrackets(opening, closing - 1);
    if (ans >= MOD) ans -= MOD;
    return dpp[opening][closing] = ans;
}

void Solve()
{
    memset(dpp, -1, sizeof dpp);
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        cout<<CountBrackets(n, n)<<endl;
    }
}


int main()
{
    Solve();
}