#include <bits/stdc++.h>
using namespace std;

struct node
{
    int key,lmax,rmax,max,sum,rev,same;
    int lc,rc,size,pri;
};

constexpr int maxn=4001000+10;
constexpr int inf=0x3f3f3f3f;
node tree[maxn]; int root,total,seed;
int n,m;
char cmd[20];

inline void debug(int p){ printf("<<< Debug Message at %d >>>\n",p); }

inline int myrand(){ return seed=(int)((seed+3)*175423LL%0x7fffffff); }

inline int &ls(int x) { return tree[x].lc; }

inline int &rs(int x) { return tree[x].rc; }

inline void pushup(int x){
	if(x){
		tree[x].size=tree[ls(x)].size+tree[rs(x)].size+1;
		tree[x].sum=tree[ls(x)].sum+tree[rs(x)].sum+tree[x].key;
		tree[x].lmax=max(max(
							tree[ls(x)].lmax,
							tree[ls(x)].sum+tree[x].key),
							tree[ls(x)].sum+tree[x].key+tree[rs(x)].lmax);
		tree[x].rmax=max(max(
							tree[rs(x)].rmax,
							tree[rs(x)].sum+tree[x].key),
							tree[rs(x)].sum+tree[x].key+tree[ls(x)].rmax);
		tree[x].max=max(max(
							max(tree[ls(x)].rmax,0)+tree[x].key+max(tree[rs(x)].lmax,0),
							tree[ls(x)].max),
							tree[rs(x)].max);
	}
}

inline bool exist(int s) { return s!=inf; }

inline void pushdown(int x){
	if(exist(tree[x].same)){
		int s=tree[x].same;
		if(ls(x)){
			tree[ls(x)].key=s;
			tree[ls(x)].same=s;
			tree[ls(x)].sum=tree[ls(x)].size*s;
			tree[ls(x)].lmax=tree[ls(x)].rmax=tree[ls(x)].max=(s>=0?tree[ls(x)].sum:s);
			//tree[ls(x)].rev=0;
		}
		if(rs(x)){
			tree[rs(x)].key=s;
			tree[rs(x)].same=s;
			tree[rs(x)].sum=tree[rs(x)].size*s;
			tree[rs(x)].lmax=tree[rs(x)].rmax=tree[rs(x)].max=(s>=0?tree[rs(x)].sum:s);
			//tree[rs(x)].rev=0;
		}
		tree[x].same=inf;
	}
	if(tree[x].rev){
		
		if(ls(x)){
			swap(ls(ls(x)),rs(ls(x)));
			swap(tree[ls(x)].lmax,tree[ls(x)].rmax);
			tree[ls(x)].rev^=1;
		}
		if(rs(x)){
			swap(ls(rs(x)),rs(rs(x)));
			swap(tree[rs(x)].lmax,tree[rs(x)].rmax);
			tree[rs(x)].rev^=1;
		}
		tree[x].rev=0;
	}
}

inline int create(int key){
	tree[++total]=(node){ key,key,key,key,key,0,inf,0,0,1,myrand() };
	return total;
}

void split(int root,int sze,int &x,int &y){
	if(root==0){
		x=y=0;
		return;
	}
	pushdown(root);
	if(tree[ls(root)].size<sze){
		x=root;
		split(rs(root),sze-tree[ls(root)].size-1,rs(x),y);
	}else{
		y=root;
		split(ls(root),sze,x,ls(root));
	}
	pushup(root);
}

int merge(int x,int y){
	if(x==0||y==0) return x^y;
	pushdown(x); pushdown(y);
	if(tree[x].pri<tree[y].pri){
		rs(x)=merge(rs(x),y);
		pushup(x);
		return x;
	}else{
		ls(y)=merge(x,ls(y));
		pushup(y);
		return y;
	}
}

inline void insert(){
	int pos,len; scanf("%d%d",&pos,&len);
	int x,y;
	split(root,pos,x,y);
	while(len--){
		int num; scanf("%d",&num);
		x=merge(x,create(num));
	}
	root=merge(x,y);
}

inline void remove(){
	int pos,len; scanf("%d%d",&pos,&len);
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,len,y,z);
	root=merge(x,z);
}

inline void reserve(){
	int pos,len; scanf("%d%d",&pos,&len);
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,len,y,z);
	tree[y].rev^=1;
	swap(ls(y),rs(y));
	swap(tree[y].lmax,tree[y].rmax);
	root=merge(merge(x,y),z);
}

inline void makesame(){
	int pos,len,val; scanf("%d%d%d",&pos,&len,&val);
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,len,y,z);
	tree[y].same=val;
	tree[y].key=val;
	tree[y].sum=tree[y].size*val;
	tree[y].lmax=tree[y].rmax=tree[y].max=(val>=0?tree[y].sum:val);
	root=merge(merge(x,y),z);
}

inline int querysum(){
	int pos,len; scanf("%d%d",&pos,&len);
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,len,y,z);
	int ans=tree[y].sum;
	root=merge(merge(x,y),z);
	return ans;
}

inline int queryone(){
	int pos; scanf("%d",&pos);
	int rt=root;
	while(1){
		if(tree[ls(rt)].size+1==pos){
			return tree[rt].key;
		}else if(tree[ls(rt)].size+1<pos){
			pos-=tree[ls(rt)].size+1;
			rt=rs(rt);
		}else{
			rt=ls(rt);
		}
	}
}

inline int querymax(){
	return tree[root].max;
}

int main(){
	tree[0].sum=0;
	tree[0].lmax=tree[0].rmax=tree[0].max=-inf;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		int x; scanf("%d",&x);
		root=merge(root,create(x));
	}
	while(m--){
		scanf("%s",cmd);
		if(cmd[0]=='I') insert();
		else if(cmd[0]=='D') remove();
		else if(cmd[0]=='R') reserve();
		else if(cmd[0]=='M'&&cmd[2]=='K') makesame();
		else if(cmd[0]=='G') printf("%d\n",querysum());
		else printf("%d\n",querymax());
	}
	return 0;
}