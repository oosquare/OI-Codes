#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=1e6+10;
int n;
ll x[maxn],p[maxn],c[maxn],s[maxn];
ll f[maxn];
int q[maxn];

inline ll X(int i) { return p[i]; }

inline ll Y(int i) { return f[i]+s[i]; }

double slope(int i,int j) { return 1.0*(Y(j)-Y(i))/(X(j)-X(i)); }

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%lld%lld%lld",&x[i],&p[i],&c[i]);
		s[i]=s[i-1]+x[i]*p[i];
		p[i]+=p[i-1];
	}
	int l=1,r=1; q[l]=0;
	for(int i=1;i<=n;++i) {
		while(l<r&&slope(q[l],q[l+1])<x[i]) ++l;
		int j=q[l]; f[i]=f[j]+x[i]*(p[i]-p[j])-(s[i]-s[j])+c[i];
		while(l<r&&slope(q[r-1],q[r])>slope(q[r],i)) --r;
		q[++r]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}