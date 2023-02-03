// @author: Shimul Sutradhar

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAX(1e4 + 7);

ll A[MAX], B[MAX];
int n, m, k;

int mark[MAX] [11] [11] [11], ind = 0;
ll dp[MAX] [11] [11] [11];

ll F(int atA, int atB, int niche, int badDiche) {
	if (atA == n + 1 && atB == m) {
		return 0;
	}
	if (mark[atA] [atB] [niche] [badDiche] == ind)
		return dp[atA] [atB] [niche] [badDiche];
	mark[atA] [atB] [niche] [badDiche] = ind;
	ll ans = -1e18;
	if (atA <= n) {
		ans = max(ans, F(atA + 1, atB, niche, badDiche) + A[atA] * (atA + niche - badDiche));
		if (badDiche < k)
			ans = max(ans, F(atA + 1, atB, niche, badDiche + 1));
	}
	if (atB < m) {
		ans = max(ans, F(atA, atB + 1, niche + 1, badDiche) + B[atB] * (atA + niche - badDiche));
		ans = max(ans, F(atA, atB + 1, niche, badDiche));
	}
	return dp[atA] [atB] [niche] [badDiche] = ans;
}

int main( ){
	int tc;
	cin >> tc;
	while (tc--) {
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i++) {
			cin >> A[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> B[i];
		}
		sort(B, B + m);
		++ind;
		cout << F(1, 0, 0, 0) << '\n';
	}
	return 0;
}
