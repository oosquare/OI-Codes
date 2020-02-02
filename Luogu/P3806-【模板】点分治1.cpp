#include <bits/stdc++.h>
using namespace std;

struct node
{
	int to,nxt,weight;
	node() {}
	node(int a,int b,int c) { to=a; nxt=b; weight=c; }
};

const int maxn=1e7+10;
node tree[2*maxn]; int head[maxn],tot;
int f[maxn],sze[maxn],vis[maxn],dis[maxn],ans[maxn],root,sum,n,m,timer;
int d[maxn];

void link(int x,int y,int z) { tree[++tot]=node(y,head[x],z); head[x]=tot; }

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

void getdis(int x,int len,int fa) {
	dis[++timer]=d[x];
	for(int i=head[x],y;y=tree[i].to,i;i=tree[i].nxt) {
		if(vis[y]||y==fa) continue;
		d[y]=d[x]+tree[i].weight;
		getdis(y,d[y],x);
	}
}

void calc(int x,int len,int w) {
	timer=0;
	d[x]=len;
	getdis(x,len,0);
	for(int i=1;i<=timer;i++) {
		for(int j=1;j<=timer;j++) {
			if(i!=j) {
				ans[dis[i]+dis[j]]+=w;
			}
		}
	}
}

void solve(int x) {
	calc(x,0,1);
	vis[x]=true;
	for(int i=head[x],y;y=tree[i].to,i;i=tree[i].nxt) {
		if(vis[y]) continue;
		calc(y,tree[i].weight,-1);
		sum=sze[x]; root=0;
		getroot(y,x);
		solve(y);
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i) {
		int x,y,w; scanf("%d%d%d",&x,&y,&w);
		link(x,y,w); link(y,x,w);
	}
	sum=n;
	root=0;
	f[0]=0x3f3f3f3f;
	getroot(1,0);
	solve(root);
	for(int i=1;i<=m;++i) {
		int k; scanf("%d\n",&k);
		printf("%s\n",(ans[k]?"AYE":"NAY"));
	}
	return 0;
}