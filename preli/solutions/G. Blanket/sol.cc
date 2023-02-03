// @author: Kazi Md Irshad

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int tmax = 100000;
const int vmax = 1000000000;

void solv(){
	vector<ll>sut(3);
	for(auto &X : sut){
		cin>>X;
		assert(1<=X and X<=vmax);
	}
	sort(sut.begin(), sut.end());
	ll L,W,H;
	cin>>L>>W>>H;
	assert(1<=L and 1<=W and 1<=H and L<=vmax and W<=vmax and H<=vmax);

	int ans = INT_MAX;
	do{
		if(H > sut[0]) continue;

		int k1 = 0, k2 = 0;
		ll h = H, s1 = sut[1], s2 = sut[2];
		while(h*2 <= sut[0]) h *= 2, k1++;
		while(s1 < L) s1 *= 2, k2++;
		while(s2 < W) s2 *= 2, k2++;

		if(k1>=k2) ans = min(ans, k2);

	}while(next_permutation(sut.begin(), sut.end()));

	if(ans==INT_MAX) ans = -1;
	cout<< ans <<"\n";
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0);

	int tc;
	cin>>tc;
	assert(1<=tc and tc<=tmax);
	while(tc--){
		solv();
	}
}
