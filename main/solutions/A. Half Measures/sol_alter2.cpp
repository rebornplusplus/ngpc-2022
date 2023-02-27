/* 
Number of divisions that each initial integer will get can be proved to be non-decreasing.
Use binary search to find the first initial integer x that will get at least one division.
If it is x, it wiil be possible to turn integers [x+1,n] to less than x in at most k-1 operations.
Once you have found x, all of the integers [x,n] will be made less than x. After that, you can have few operations (say, k') left to do.
They will be used to floor down k' (x-1) values.
*/


#include<bits/stdc++.h>
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

#define int ll

ll get(int l,int r)
{
    int x=l-1;
    int cnt=1;
    ll need=0;
    while(l<=r)
    {
        int upto=min(x*2-1,r);
        need+=1LL*(upto-l+1)*cnt;
        l=upto+1;
        x*=2;
        cnt++;
    }
    return need;
}

ll fn(int n,int p)
{
    int cycle=(n+1)/(1<<p);
    ll sum=1LL*(1<<p)*(cycle*(cycle-1))/2;
    int ex=(n+1)%(1<<p);
    sum+=1LL*ex*cycle;
    return sum;
}

main()
{
    fast;
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        int low=1,high=n;
        int got=n;
        while(low<=high)
        {
            int mid=(low+high)/2;
            ll need=get(mid+1,n);
            if(need<k)
            {
                got=mid;
                high=mid-1;
            }
            else
                low=mid+1;
        }
        int x=got;
        vector<pair<int,int>>all;
        int l=x;
        int cnt=1;
        while(l<=n)
        {
            int upto=min(x*2-1,n);
            all.push_back({cnt,l});
            k-=1LL*cnt*(upto-l+1);
            l=upto+1;
            cnt++;
            x*=2;
        }
        ll sum=1LL*(all[0].second-1)*(all[0].second)/2;
        int extra=0;
        for(int i=0;i<all.size();i++)
        {
            auto u=all[i];
            int l=u.second;
            int r=n;
            if(i+1<all.size())
                r=all[i+1].second-1;
            sum+=fn(r,all[i].first)-fn(l-1,all[i].first);

            ll L=max((ll)l,1LL*(got-1)*(1<<all[i].first));
            ll R=min((ll)r,1LL*(got-1)*((1<<(all[i].first+1))-1));
            if(L<=R)
                extra+=R-L+1;

        }
        int kill=min(extra,k);
        sum-=1LL*(got-1)*kill;
        sum+=1LL*(got-1)/2*kill;
        cout<<sum<<'\n';
    }
}

