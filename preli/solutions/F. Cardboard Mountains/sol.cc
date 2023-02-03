// @author: Md. Rahat Islam

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define db double

db mh(ll x1,ll y1,ll x2,ll y2){
	db a1=-y1;
	db b1=x1-x2;
	db c1=a1*x1+b1*y1;
	db a2=-y2;
	db b2=x2-x1;
	db c2=a2*x2+b2*y2;
	db d=a1*b2-a2*b1;
	return (a1*c2-a2*c1)/d;
}

int main(){
	ll t,tc=0,total=0;
	scanf("%lld",&t);
	while(t--){
		ll N;
		db MX;
		scanf("%lld %lf",&N,&MX);
		total+=N;
		map<db,db>M;
		M[0]=0;
		M[MX]=0;
		for(ll i=0;i<N;i++){
			db x,y;
			scanf("%lf %lf",&x,&y);
			M[x]=max(M[x],y);
		}
		vector<db>X,Y;
		for(auto [x,y]:M){
			X.push_back(x);
			Y.push_back(y);
		}
		db ans=0;
		for(ll i=1;i<M.size()-1;i++){
			ans+=0.5*Y[i]*(X[i+1]-X[i-1]);
			db h=mh(X[i],Y[i],X[i+1],Y[i+1]);
			ans-=0.5*h*(X[i+1]-X[i]);
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}
