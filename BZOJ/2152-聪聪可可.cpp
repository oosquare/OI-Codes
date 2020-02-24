#include <bits/stdc++.h>
using namespace std;

const int maxn=20001;

struct Node
{
	int to,nxt,weight;
	Node() {}
	Node(int a,int b,int c) { to=a; nxt=b; weight=c; }
};

Node tree[2*maxn]; int head[maxn],tot;
int f[maxn],sze[maxn],vis[maxn],dis[maxn],t[maxn],root,sum,ans,n;

int gcd(int a,int b) { return !b?a:gcd(b,a%b); }

void link(int x,int y,int z) { tree[++tot]=Node(y,head[x],z); head[x]=tot; }

void getroot(int x,int fa) {
	sze[x]=1; f[x]=0;
	for(int i=head[x],y;y=tree[i].to;i=tree[i].nxt) {
		if(vis[y]||y==fa) continue;
		getroot(y,x);
		sze[x]+=sze[y];
		f[x]=max(f[x],sze[y]);
	}
	f[x]=max(f[x],sum-sze[x]);
	root=f[x]<f[root]?x:root;
}

void getdeep(int x,int fa) {
	++t[dis[x]];
	for(int i=head[x],y;y=tree[i].to,i;i=tree[i].nxt) {
		if(vis[y]||y==fa) continue;
		dis[y]=(dis[x]+tree[i].weight)%3;
		getdeep(y,x);
	}
}

int calc(int x,int len) {
	t[0]=t[1]=t[2]=0;
	dis[x]=len;
	getdeep(x,0);
	int a=2*t[1]*t[2]+t[0]*t[0];
	return a;
}

void solve(int x) {
	ans+=calc(x,0); vis[x]=true;
	for(int i=head[x],y;y=tree[i].to,i;i=tree[i].nxt) {
		if(vis[y]) continue;
		ans-=calc(y,tree[i].weight);
		sum=sze[y];
		root=0;
		getroot(y,x);
		solve(root);
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<n;++i) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z); z%=3;
		link(x,y,z); link(y,x,z);
	}
	sum=n;
	f[0]=0x7fffffff;
	getroot(1,0);
	solve(root);
	int anss=gcd(ans,n*n);
	printf("%d/%d\n",ans/anss,n*n/anss);
	return 0;
}