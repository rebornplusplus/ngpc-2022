// @author: Rafid Bin Mostofa

#include <bits/stdc++.h>

using namespace std;

typedef long double Tf;

struct Cube {
	Tf l, w, h;

	bool check_limits() {
		return min({l, w, h}) > 0 and max({l, w, h}) <= Tf(1e9);
	}

	bool fits(const Cube& c) const {
		return l >= c.l and w >= c.w and h >= c.h;
	}

	void fold_l() {
		l /= 2;
		h *= 2;
	}

	void fold_w() {
		w /= 2;
		h *= 2;
	}

	vector<Cube> permuatations() {
		vector<Cube> p;

		vector<Tf> perm = { l, w, h };
		sort(perm.begin(), perm.end());
		do {
			p.emplace_back(Cube({ perm[0], perm[1], perm[2] }));
		} while(next_permutation(perm.begin(), perm.end()));

		return p;
	}

	friend istream& operator >> (istream& is, Cube& c) {
		return is >> c.l >> c.w >> c.h;
	}
};

struct TestData {
	Cube suitcase;
	Cube blanket;

	bool check_limits() {
		return suitcase.check_limits() and blanket.check_limits();
	}

	int solve() {
		int folds = INT_MAX;
		auto perms = suitcase.permuatations();

		for(const auto& sc : perms) {
			int cur = 0;
			auto c = blanket;
			while(c.l > sc.l) {
				c.fold_l();
				++cur;
			}
			while(c.w > sc.w) {
				c.fold_w();
				++cur;
			}
			if(sc.fits(c)) {
				folds = min(folds, cur);
			}
		}

		return folds == INT_MAX ? -1 : folds;
	}

	friend istream& operator >> (istream& is, TestData& t) {
		return is >> t.suitcase >> t.blanket;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	assert(cin >> t);
	assert(t >= 1 and t <= int(1e5));

	while(t--) {
		TestData test;
		assert(cin >> test);
		assert(test.check_limits());

		cout << test.solve() << "\n";
	}

	string temp;
	assert(!(cin >> temp));

	return 0;
}
