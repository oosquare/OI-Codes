#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn=80001;

struct Node
{
	int to,nxt,len;
};

Node tree[maxn]; int head[maxn],tot;
int n,k,father[maxn],sze[maxn],son[maxn];
ll dis[maxn];

ll ans;
bool vis[maxn];

void link(int x,int y,int w) { 
	tree[++tot].to=y; tree[tot].nxt=head[x]; tree[tot].len=w; head[x]=tot; 
}

void clear() {
	ans=tot=0;
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
}

int getGravity(int sv) {
	int q[maxn],r=1;
	int l=1;
	int maxx=n,ans;
	q[r]=sv; father[sv]=0;
	while(l<=r) {
		int x;
		sze[x=q[l]]=1; son[x]=0;
		for(int i=head[x],y;y=tree[i].to,i;i=tree[i].nxt) {
			if(vis[y]||y==father[x]) continue;
			father[y]=x; q[++r]=y;
		}
		++l;
	}
	for(l=r;l>=1;--l) {
		int x=q[l],y=father[x];
		son[x]=max(son[x],r-sze[x]);
		if(son[x]<maxx) { ans=x; maxx=son[x]; }
		if(!y) break;
		sze[y]+=sze[x];
		if(sze[x]>son[y]) son[y]=sze[x];
	}
	return ans;
}

ll calc(int sv,int le) {
	int q[maxn],d[maxn],r=1; int l,t=0,left,right;
	q[l=1]=sv; dis[sv]=le; father[sv]=0;
	while(l<=r) {
		int x;
		d[++t]=dis[x=q[l]];
		for(int i=head[x],y;y=tree[i].to,i;i=tree[i].nxt) {
			if(vis[y]||y==father[x]) continue;
			father[y]=x; dis[y]=dis[x]+tree[i].len; q[++r]=y;
		}
		++l;
	}
	ll cnt=0;
	sort(d+1,d+1+t);
	left=1; right=t;
	while(left<right) {
		if(d[left]+d[right]<=k) { cnt+=right-left; ++left; } else --right;
	}
	return cnt;
}

void solve(int x) {
	int g=getGravity(x);
	vis[g]=true;
	ans+=calc(g,0);
	for(int i=head[g],y;y=tree[i].to,i;i=tree[i].nxt) {
		if(!vis[y]) ans-=calc(y,tree[i].len);
	}
	for(int i=head[g],y;y=tree[i].to,i;i=tree[i].nxt) {
		if(!vis[y]) solve(y);
	}
}

int main() {
	scanf("%d",&n);
	clear();
	for(int i=1;i<n;++i) {
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		link(x,y,w); link(y,x,w);
	}
	scanf("%d",&k);
	solve(1);
	printf("%lld\n",ans);
	
	return 0;
}