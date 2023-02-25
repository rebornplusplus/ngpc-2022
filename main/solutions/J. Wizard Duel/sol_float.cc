#include <bits/stdc++.h>

using namespace std;

typedef int Ti;
typedef double Tf;

struct Edge {
	Ti from, to;
	Tf cost;
};

const Tf EPS = 1e-4;

const int N = 40;

vector<Edge> g[N];
Tf d[N];

Tf bfs(Ti u, Ti v) {
	queue<Ti> q;
	q.push(u);

	fill(d, d + N, -1);
	d[u] = 1;

	while(!q.empty()) {
		Ti a = q.front();
		q.pop();

		if(a == v) {
			return d[a];
		}

		for(auto& e : g[a]) {
			auto b = e.to;
			auto cost = e.cost;
			if(d[b] < 0) {
				d[b] = d[a] * cost;
				q.push(b);
			}
		}
	}

	return -1;
}

int main() {
	Ti t;
	cin >> t;

	while(t--) {
		Ti n, m, q; 
		cin >> n >> m >> q;

		for(int i=1; i<=n; ++i) {
			g[i].clear();
		}

		while(m--) {
			Ti u, v, x, y;
			cin >> u >> v >> x >> y;
			g[u].push_back(Edge({ u, v, Tf(x) / Tf(y) }));
			g[v].push_back(Edge({ v, u, Tf(y) / Tf(x) }));
		}

		while(q--) {
			Ti u, v;
			cin >> u >> v;

			auto ratio = bfs(u, v);
			if(ratio < 0) {
				cout << "unknown\n";
			}
			else if(fabs(1 - ratio) < EPS) {
				cout << "draw\n";
			}
			else if(ratio > 1) {
				cout << "win\n";
			}
			else {
				cout << "lose\n";
			}
		}
	}

	return 0;
}
