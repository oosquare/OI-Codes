#include <bits/stdc++.h>
using namespace std;

const int maxn=5e5+10;
typedef long long ll;

int n,m;
ll c[maxn],f[maxn];
int q[maxn],l,r;

inline ll getX(int i) { return c[i]; }

inline ll getY(int i) { return f[i]+c[i]*c[i]; }

inline double slope(int i,int j) { return 1.0*(getY(j)-getY(i))/(getX(j)-getX(i)); }

int main() {
	while(scanf("%d%d",&n,&m)!=EOF) {
		for(int i=1;i<=n;i++) { scanf("%lld",&c[i]); c[i]+=c[i-1]; }
		q[l=r=1]=0; f[1]=0;
		for(int i=1;i<=n;++i) {
			while(l<r&&slope(q[l],q[l+1])<2*c[i]) ++l;
			int j=q[l]; f[i]=f[j]+(c[i]-c[j])*(c[i]-c[j])+m;
			while(l<r&&slope(q[r-1],q[r])>slope(q[r],i)) --r;
			q[++r]=i;
		}
		printf("%lld\n",f[n]);
	}
	return 0;
}