// @author: Apurba Saha

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const int N = 2e5 +5;
const int K = 100 +5;
const int mod = 998244353;
typedef pair<int,int> pii;

inline int add(int x, int y)
{
	return (x+y>=mod ? x+y-mod : x+y);
}

int n,m,k;
int s,t;
vector<pii>adj[N];
ll dist[N];
int dp[N][K];

void dijkstra()
{
	vector<bool>visited(n,false);
	priority_queue <pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > pq;
	dist[s]=0;
	pq.push({0,s});
	while(!pq.empty())
	{
		int a = pq.top().second;
		pq.pop();
		if (visited[a])
			continue;
		visited[a] = true;
		for (pair<int,int> i : adj[a])
		{
			if(dist[i.first]> dist[a]+i.second)
			{
				dist[i.first] = dist[a]+i.second;
				pq.push({dist[i.first],i.first});
			}
		}
	}
}

int solve(int cur, int delta)
{
	assert(delta>=0 && delta<=k);
	int &ret = dp[cur][delta];
	if(ret!=-1)
		return ret;
	int ans = 0;
	if(cur==t)
	{
		ans = 1;
	}
	for(auto [v,w]:adj[cur])
	{
		ll d = dist[cur] + delta + w;
		if(d-dist[v]<=k)
			ans = add(ans , solve(v,d-dist[v]));
	}
	return ret = ans;
}

void TEST_CASES()
{
	cin>>n>>m>>k;
	cin>>s>>t;
	s--;
	t--;
	for(int i=0;i<n;i++)
	{
		adj[i].clear();
		dist[i] = 1e18;
		memset(dp[i],-1,sizeof dp[i]);
	}
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		u--;
		v--;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	dijkstra();
	int ans = solve(s,0);
	cout<<ans<<"\n";
}

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin>>t;
	while(t--)
	{
		TEST_CASES();
	}
	return 0;
}
