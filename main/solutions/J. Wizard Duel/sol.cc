#include <bits/stdc++.h>

using namespace std;

typedef long long Ti;

const Ti N_MAX = 35;
const Ti V_MAX = 3;

template <typename T = Ti>
struct Frac {
	T up, dn;
	
	Frac() : up(0), dn(1) { }
	Frac(T a, T b) : up(a), dn(b) { normalize(); }
	Frac(const Frac &p) : up(p.up), dn(p.dn) { normalize(); }

	void normalize() {
		bool sign = 0;
		if(up < 0) up *= -1, sign ^= 1;
		if(dn < 0) dn *= -1, sign ^= 1;
		T g = __gcd(up, dn);
		up /= g, dn /= g;
		if(sign) up *= -1;
	}

	Frac operator + (const Frac &p) {
		T g = __gcd(dn, p.dn);
		return Frac(up * (p.dn / g) + p.up * (dn / g), dn * (p.dn / g));
	}
	Frac operator - (const Frac &p) {
		T g = __gcd(dn, p.dn);
		return Frac(up * (p.dn / g) - p.up * (dn / g), dn * (p.dn / g));
	}
	Frac operator * (const Frac &p) {
		T g1 = __gcd(up, p.dn);
		T g2 = __gcd(p.up, dn);
		return Frac((up / g1) * (p.up / g2), (dn / g2) * (p.dn / g1));
	}
	Frac operator / (const Frac &p) {
		Frac inv(p.dn, p.up);
		return *this * inv;
	}

	bool operator < (const Frac &p) const {
		return up * p.dn < p.up * dn;	// double division if overflow
	}
	bool operator == (const Frac &p) const {
		return !(*this < p) and !(p < *this);
	}

	double to_double() { return 1.0 * up / dn; }

	friend ostream &operator << (ostream &os, const Frac &f) {
		return os << f.up << "/" << f.dn;
	}
	friend istream &operator >> (istream &is, Frac &f) {
		is >> f.up >> f.dn;
		f.normalize();
		return is;
	}
};

struct Query {
	Ti a, b;

	friend istream& operator >> (istream& is, Query& q) {
		return is >> q.a >> q.b;
	}
};

struct Info {
	Ti a, b, x, y;

	friend istream& operator >> (istream& is, Info& info) {
		return is >> info.a >> info.b >> info.x >> info.y;
	}

	friend ostream& operator << (ostream& os, const Info& info) {
		return os << "(" << info.a << "->" << info.b << ": " << info.x << "/" << info.y << ")";
	}
};

struct Test {
	Ti n, m, q;
	vector<Info> info;
	vector<Query> queries;

	vector< vector< Info > > g;
	vector<bool> vis;

	Test() { }

	vector<string> solve() {
		build_graph();

		vector<string> res;
		for(auto& qq : queries) {
			auto qval = query(qq);
			res.push_back(qval);
		}
		return res;
	}

	void build_graph() {
		g.resize(n + 1);
		for(Info& i : info) {
			auto front = i;
			g[i.a].push_back(front);
			auto back = Info({ i.b, i.a, i.y, i.x });
			g[i.b].push_back(back);
		}
		vis.resize(n + 1);
	}

	string query(Query& qq) {
		bool found = false;
		fill(vis.begin(), vis.end(), false);

		auto ratio = dfs(qq.a, qq.b, found);

		if(!found) {
			return "unknown";
		}

		if(ratio.up == ratio.dn) {
			return "draw";
		}
		else if(ratio.up > ratio.dn) {
			return "win";
		}
		else {
			return "lose";
		}
	}

	Frac<> dfs(Ti u, const Ti des, bool& found) {
		if(u == des) {
			found = true;
			return Frac<>(1, 1);
		}

		vis[u] = true;

		for(auto& e : g[u]) {
			if(vis[e.b]) {
				continue;
			}
			auto cost = Frac<>(e.x, e.y);
			auto val = dfs(e.b, des, found);
			if(found) {
				auto res = val * cost;
				return res;
			}
		}

		return Frac<>(0, 1);
	}
	
	bool valid() {
		if(n < 2 or n > N_MAX) {
			return false;
		}
		if(min(m, q) < 1 or max(m, q) > (n * (n - 1)) / 2) {
			return false;
		}
		for(auto& i : info) {
			if(i.a == i.b or min(i.a, i.b) < 1 or max(i.a, i.b) > n) {
				return false;
			}
			if(min(i.x, i.y) < 1 or max(i.x, i.y) > 3 or __gcd(i.x, i.y) != 1) {
				return false;
			}
		}
		for(auto& qq : queries) {
			if(qq.a == qq.b or min(qq.a, qq.b) < 1 or max(qq.a, qq.b) > n) {
				return false;
			}
		}
		return true;
	}

	friend istream& operator >> (istream& is, Test& t) {
		is >> t.n >> t.m >> t.q;
		t.info.resize(t.m);
		for(auto& i : t.info) {
			is >> i;
		}
		t.queries.resize(t.q);
		for(auto& qq : t.queries) {
			is >> qq;
		}
		return is;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	Ti t;
	assert(cin >> t);
	assert(t >= 1 and t <= 100);

	for(Ti tc=1; tc<=t; tc++) {
		Test test;
		assert(cin >> test);
		assert(test.valid());
		
		auto res = test.solve();

		for(auto s : res) {
			cout << s << "\n";
		}
	}

	string token;
	assert(!(cin >> token));

	return 0;
}
