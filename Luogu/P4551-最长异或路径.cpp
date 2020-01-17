#include <bits/stdc++.h>
using namespace std;

struct edge
{
	int to,nxt,weight;
};

struct node
{
	int ch[2];
};

int tot1,tot2=1,head[1000001];
edge tree[2000001];
int trie[2000001][2];
int sum[2000001];
int bo[2000001];
int n;

void link(int x,int y,int w){
	tree[++tot1].to=y; tree[tot1].weight=w; tree[tot1].nxt=head[x]; head[x]=tot1;
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=tree[i].nxt){
		int v=tree[i].to,w=tree[i].weight;
		if(v==fa)continue;
		sum[v]=sum[u]^w;
		dfs(v,u);
	}
}

void insert(int v){
	int u=1;
	for(int i=1<<30;i;i>>=1){
		bool c=v&i;
		if(!trie[u][c]) trie[u][c]=++tot2;
		u=trie[u][c];
	}
	bo[u]=1;	
}

int query(int v){
	int u=1,ans=0;
	for(int i=1<<30;i;i>>=1){
		bool c=v&i;
		if(trie[u][c^1]){
			ans+=i;
			u=trie[u][c^1];
		}else{
			u=trie[u][c];
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		link(u,v,w);
		link(v,u,w);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		insert(sum[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,query(sum[i]));
	}
	printf("%d\n",ans);
}