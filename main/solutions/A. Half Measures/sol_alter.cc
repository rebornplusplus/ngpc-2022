/**
 * Author: reborn++
 * Rationale:
 * 	 For a sequence 1, 2, .. n/2-1, n/2, n/2+1, .. n,
 * 	 halve each element of the last half n/2+1, .. n
 * 	 the sequence will be 1, 2, .. n/4-1, n/4, n/4+1, .. n/2-1, n/2
 * 	 with the frequency of 1, 2, .. n/4-1 equalling 1,
 * 	      the frequency of n/4 being some value x,
 * 	      the frequency of n/4+1, .. n/2-1 being the same value y
 * 	      the frequency of n/2 being some value z
 * 	 keep breaking it in half until the number of operations max out
 * 	 binary search on the value whose all occurances cannot be halved
 * 	 do some manual labour and some adjustments carefully
 **/

#include <bits/stdc++.h>

using namespace std;

typedef long long Ti;

struct Test {
	Ti n, k;

	map<Ti, Ti> sp_cnt;

	Ti count(Ti v, Ti back) {
		if(v > back) {
			return 0;
		}

		Ti half = back / 2;
		if(v < half) {
			return 1;
		}

		auto it = sp_cnt.find(v);
		if(it != sp_cnt.end()) {
			return it->second;
		}

		Ti aggr_cnt = n - (half - 1) - sp_cnt[back] - sp_cnt[half];
		assert(aggr_cnt > 0);
		assert(back - half - 1 > 0);
		
		Ti cnt = aggr_cnt / (back - half - 1);
		return cnt;
	}

	// sum of count(v, backs) for v \in [l, r]
	Ti count_range(Ti l, Ti r, Ti back) {
		if(l > r) {
			return 0;
		}
		if(l == r) {
			return count(l, back);
		}

		Ti res = count(l, back) + count(r, back);
		if(l + 1 < r) {
			res += (r - l - 1) * count(l + 1, back);
		}
		return res;
	}

	Ti count_operations(Ti back) {
		Ti half = back / 2;

		Ti res = count(back, back);
		if(back - half > 1) {
			res += count(back - 1, back) * (back - half - 1);
		}
		return res;
	}

	void break_half(Ti back) {
		Ti half = back / 2;
		set<Ti> interesting({ back, back - 1, half + 1, half + 2 });

		for(auto x : interesting) {
			Ti hx = x / 2;
			auto it = sp_cnt.find(hx);
			if(it == sp_cnt.end()) {
				continue;
			}
			sp_cnt[hx] += count(x, back);
		}
	}

	// sum of the values [l, r]
	Ti sum(Ti l, Ti r) const {
		if(l > r) {
			return 0;
		}
		return r * (r + 1) / 2 - l * (l - 1) / 2;
	}

	// sum of the values with count [ 1 .. back ]
	Ti sum_values(Ti back) {
		Ti half = back / 2;

		Ti res = 0;
		if(half > 1) {
			res += sum(1, half - 1);
		}
		res += count(half, back) * half;
		if(half + 1 < back) {
			res += count(half + 1, back) * sum(half + 1, back - 1);
		}
		res += count(back, back) * back;

		return res;
	}

	Ti sum_full(Ti l, Ti r, Ti back) {
		Ti res = count(l, back) * l;
		if(r > l) {
			res += count(r, back) * r;
		}
		if(r - l > 1) {
			Ti sum_val = sum(l + 1, r - 1);
			Ti cnt = count(l + 1, back);
			res += sum_val * cnt;
		}
		return res;
	}

	// sum_half calculates the sum if values in [l, r] were halved.
	Ti sum_half(Ti l, Ti r, Ti back) {
		Ti res = count(l, back) * (l / 2);
		if(r > l) {
			res += count(r, back) * (r / 2);
		}
		if(r - l > 1) {
			l++, r--;
			Ti ev_l, od_l, ev_r, od_r;
			if(l % 2) {
				od_l = l, ev_l = l + 1;
			}
			else {
				od_l = l + 1, ev_l = l;
			}
			if(r % 2) {
				od_r = r, ev_r = r - 1;
			}
			else {
				od_r = r - 1, ev_r = r;
			}
			Ti val_sum = sum(od_l / 2, od_r / 2) + sum(ev_l / 2, ev_r / 2);
			Ti cnt = count(l, back);
			res += val_sum * cnt;
		}

		return res;
	}

	Ti solve() {
		// fill specials
		for(int i=n; i>0; i/=2) {
			sp_cnt[i] = 1;
		}
		sp_cnt[0] = 0;

		// remaining ops are k
		Ti rem_ops = k;
		Ti back = n;

		while(back > 0) {
			Ti ops = count_operations(back);
			if(ops > rem_ops) {
				// cannot break [ back / 2 .. back ] fully
				break;
			}

			rem_ops -= ops;
			break_half(back);
			back /= 2;
		}

		// if all numbers are reduced to 0, sum is 0
		if(back == 0) {
			return 0;
		}
		// if all numbers are reduced to 1,
		// rem_ops cnt can be further reduced to 0
		if(back == 1) {
			Ti c = count(1, back);
			return max(c - rem_ops, Ti(0));
		}

		// find out the value that would be half-broken half-not
		Ti l = back / 2, r = back;
		while(l < r) {
			Ti mid = (l + r) / 2;
			Ti c = count_range(mid + 1, r, back);
			if(rem_ops >= c) {
				rem_ops -= c;
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}

		// sum of [ 1 .. back ]
		Ti res = sum_values(back);
		if(r < back) {
			// adjust the broken values in [ r+1 .. back ]
			res -= sum_full(r + 1, back, back);
			res += sum_half(r + 1, back, back);
		}

		// break some of the value r
		if(rem_ops > 0) {
			Ti r_cnt = count(r, back);
			assert(rem_ops < r_cnt);
			
			res -= rem_ops * r;
			res += rem_ops * (r / 2);
		}

		return res;
	}

	Ti brute_solve() const {
		map<Ti, Ti> cnt;

		for(int i=1; i<=n; i++) {
			cnt[i] = 1;
		}

		for(int i=n, j=k; j > 0; --j) {
			cnt[i / 2]++;
			cnt[i]--;
			if(cnt[i] == 0) {
				i--;
			}
		}

		Ti res = 0;
		for(int i=1; i<=n; i++) {
			res += cnt[i] * i;
		}
		return res;
	}
};

void input(Ti& t, vector<Test>& tests) {
	assert(cin >> t);
	assert(t >= 1 and t <= Ti(1e5));

	tests.resize(t);
	for(Test& test : tests) {
		assert(cin >> test.n >> test.k);
		assert(test.n >= 1 and test.n <= Ti(1e9));
		assert(test.k >= 1 and test.k <= Ti(1e9));
	}

	string token;
	assert(!(cin >> token));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	Ti t;
	vector<Test> tests;

	input(t, tests);

	for(Test& test : tests) {
		cout << test.solve() << "\n";
	}

	return 0;
}
