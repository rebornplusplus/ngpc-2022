#include <bits/stdc++.h>

using namespace std;

typedef long long Ti;

const Ti MOD = 998244353;

struct Test {
	Ti n, p;
	Ti orval, andval;

	bool is_set(Ti val, Ti idx) {
		return (val & (Ti(1) << idx)) > 0;
	}

	Ti solve() {
		if((andval & orval) != andval) {
			return 0;
		}

		Ti res = 1;

		for(Ti i=0; i<p; i++) {
			bool orbit = is_set(orval, i);
			bool andbit = is_set(andval, i);

			if(orbit and !andbit) {
				Ti cur = ((Ti(1) << n) - 2) % MOD;	// if n = 1, cur = 0
				res = (res * cur) % MOD;
			}
		}

		return res;
	}

	bool is_valid() {
		return n >= 1 and n <= 50
			and p >= 1 and p <= 30
			and orval >= 0 and orval < (Ti(1) << p)
			and andval >= 0 and andval < (Ti(1) << p);
	}

	friend istream& operator >> (istream& is, Test& t) {
		return is >> t.n >> t.p >> t.orval >> t.andval;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	Ti t;
	assert(cin >> t);
	assert(t >= 1 and t <= 1500);

	while(t--) {
		Test test;
		assert(cin >> test);
		assert(test.is_valid());

		Ti res = test.solve();
		cout << res << "\n";
	}

	string token;
	assert(!(cin >> token));

	return 0;
}

