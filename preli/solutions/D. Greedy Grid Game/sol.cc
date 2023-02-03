// @author: Abu Saleh

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<typename U> using ordered_set=tree<U, null_type,less<U>,rb_tree_tag,tree_order_statistics_node_update>;

#define ll long long
#define all(we) we.begin(),we.end()
#define test int tt; cin>>tt; for(int cs=1;cs<=tt;cs++)
#define nl '\n'

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	test
	{
		ll n,m,i,j,k,l,s=0,ans=-1e18;

		cin>>n>>m;

		ll a[n+4][m+4];

		for(i=0; i<n; i++)
		{
			for(j=0; j<m; j++)
			{
				cin>>a[i][j];
				s+=a[i][j];
			}
		}

		if(n==1 || m==1)
		{
			ans=s;
		}
		else if(n==2 && m==2)
		{
			ans=max({a[0][0]+a[n-1][m-1], a[0][0]+a[1][0]+a[n-1][m-1],a[0][0]+a[0][1]+a[n-1][m-1],s});
		}
		else if(n==2 || m==2)
		{
			if(n==2)
			{
				///1
				s=0;
				for(i=0; i<m; i++) s+=a[0][i];
				s+=a[1][m-2];
				s+=a[1][m-1];
				ans=max(ans,s);

				///2
				s=0;
				s+=a[0][0];
				s+=a[1][0];
				for(i=1; i<m; i++) s+=a[0][i];
				s+=a[1][m-1];
				ans=max(ans,s);

				///3
				s=0;
				s+=a[0][0];
				for(i=1;i<m;i++) s+=a[1][i];
				ans=max(ans,s);

				///4
				s=0;
				for(i=0;i<m;i++) s+=a[0][i];
				s+=a[1][m-1];
				ans=max(ans,s);

				///5
				s=0;
				for(i=0;i<m;i++) s+=a[1][i];
				s+=a[0][0];
				ans=max(ans,s);

				///6
				s=0;
				for(i=0;i<m;i++) s+=a[1][i];
				s+=a[0][0];
				s+=a[0][1];
				ans=max(ans,s);
			}
			else
			{
				///1
				s=0;
				for(i=0; i<n; i++) s+=a[i][0];
				s+=a[n-2][1];
				s+=a[n-1][1];
				ans=max(ans,s);

				///2
				s=0;
				s+=a[0][0];
				s+=a[0][1];
				for(i=1; i<n; i++) s+=a[i][0];
				s+=a[n-1][1];
				ans=max(ans,s);

				///3
				s=0;
				s+=a[0][0];
				for(i=1;i<n;i++) s+=a[i][1];
				ans=max(ans,s);

				///4
				s=0;
				for(i=0;i<n;i++) s+=a[i][0];
				s+=a[n-1][1];
				ans=max(ans,s);

				///5
				s=0;
				for(i=0;i<n;i++) s+=a[i][1];
				s+=a[0][0];
				ans=max(ans,s);

				///6
				s=0;
				for(i=0;i<n;i++) s+=a[i][1];
				s+=a[0][0];
				s+=a[1][0];
				ans=max(ans,s);
			}
		}
		else
		{
			///1
			s=0;
			for(i=0; i<m; i++) s+=a[0][i];
			for(i=1; i<n; i++) s+=a[i][m-1];
			ans=max(ans,s);

			///2
			s=0;
			for(i=0; i<n; i++) s+=a[i][0];
			for(i=1; i<m; i++) s+=a[n-1][i];
			ans=max(ans,s);

			///3
			s=0;
			for(i=0; i<n; i++) s+=a[i][0];
			for(i=1; i<m; i++) s+=a[n-1][i];
			s+=a[n-2][1];
			ans=max(ans,s);

			///4
			s=0;
			for(i=0; i<n; i++) s+=a[i][0];
			for(i=1; i<m; i++) s+=a[n-2][i];
			s+=a[n-1][m-1];
			ans=max(ans,s);

			///5
			s=0;
			s+=a[0][0];
			for(i=1; i<m; i++) s+=a[1][i];
			for(i=2; i<n; i++) s+=a[i][m-1];
			ans=max(ans,s);

			///6
			s=0;
			s+=a[0][0];
			for(i=1; i<n; i++) s+=a[i][1];
			for(i=2; i<m; i++) s+=a[n-1][i];
			ans=max(ans,s);

			///7
			s=0;
			for(i=0; i<m; i++) s+=a[0][i];
			for(i=1; i<n; i++) s+=a[i][m-2];
			s+=a[n-1][m-1];
			ans=max(ans,s);

			///8
			s=0;
			for(i=0; i<m; i++) s+=a[0][i];
			s+=a[1][m-2];
			for(i=1; i<n; i++) s+=a[i][m-1];
			ans=max(ans,s);
		}

		cout<<ans<<nl;
	}
	return 0;
}


