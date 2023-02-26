#include<bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL)
#define LL long long
#define MAX (LL) 4e18
#define MOD 998244353
#define N 5005
#define endl "\n"
using namespace std;
namespace fs = std::filesystem;

bool Walk(vector < pair < int , int > > &updates, LL health)
{
    if (health <= 0) return false;
    LL healthUpdate = 0;
    int lastUpdate = 0;
    for (auto update : updates)
    {
        int point = update.first;
        int power = update.second;
        health += healthUpdate * (point - lastUpdate);
        if (health <= 0) return false;
        lastUpdate = point;
        healthUpdate += power;
    }
    return true;
}

void Solve()
{
    int t;
    cin>>t;
    while (t--)
    {
        int nodes, queries;
        cin>>nodes>>queries;
        
        vector < pair < int , int > > updates;
        while (queries--)
        {
            int type, s, x, D;
            cin>>type>>s>>x>>D;
            
            if (type == 2) D = -D;
            updates.push_back({s, D});
            updates.push_back({x+1, -D});
        }

        sort(updates.begin(), updates.end());

        LL low = 1, high = 4e18;
        while (low < high)
        {
            LL mid = (low + high) / 2;
            if (Walk(updates, mid))
            {
                high = mid;
            }
            else low = mid + 1;
        }
        cout<<low<<endl;
    }
}


int main()
{
    Solve();
}