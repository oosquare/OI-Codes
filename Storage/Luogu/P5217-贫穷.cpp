#include <bits/stdc++.h>
using namespace std;

struct node {
	int key,value,count,rev,father,l,r,size,priority;
};

constexpr int maxn=1e5+10;
node tree[maxn<<4]; int total,root,seed;
int mapping[maxn];
char tmp[maxn];
int n,m;

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline int &fa(int x) { return tree[x].father; }

inline int myrandom() { return seed=((seed+3)*312731LL%0x7fffffff); }

inline void pushup(int x){ 
	tree[x].count=tree[ls(x)].count|tree[rs(x)].count|(1<<(tree[x].key));
	tree[x].size=tree[ls(x)].size+tree[rs(x)].size+1;
	if(ls(x)) fa(ls(x))=x;
	if(rs(x)) fa(rs(x))=x;
}

inline void pushdown(int x){
	if(tree[x].rev==0) return;
	tree[x].rev=0;
	tree[ls(x)].rev^=1;
	tree[rs(x)].rev^=1;
	swap(ls(x),rs(x));
}

inline int create(int key,int val=-1){
	tree[++total]={key,val,(1<<(key)),0,0,0,0,1,myrandom()}; return total;
}

void split(int root,int sze,int &x,int &y){
	if(!root){
		x=y=0;
		return;
	}
	pushdown(root);
	if(tree[ls(root)].size<sze){
		x=root; split(rs(x),sze-tree[ls(x)].size-1,rs(x),y); pushup(x); fa(y)=0;
	}else{
		y=root; split(ls(y),sze,x,ls(y)); pushup(y); fa(x)=0;
	}
}

int merge(int x,int y){
	if(!x||!y) return x^y;
	pushdown(x); pushdown(y);
	if(tree[x].priority<tree[y].priority){
		rs(x)=merge(rs(x),y); pushup(x); return x;
	}else{
		ls(y)=merge(x,ls(y)); pushup(y); return y;
	}
}

void insert(){
	int pos; char c[5]; scanf("%d%s",&pos,c);
	int x,y;
	split(root,pos,x,y);
	root=merge(merge(x,create(c[0]-'a')),y);
}

void remove(){
	int pos; scanf("%d",&pos);
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,1,y,z);
	if(tree[y].value!=-1){
		mapping[tree[y].value]=-1;
	}
	root=merge(x,z);
}

void reserve(){
	int l,r;
	scanf("%d%d",&l,&r);
	int x,y,z;
	split(root,l-1,x,y);
	split(y,r-l+1,y,z);
	tree[y].rev^=1;
	root=merge(merge(x,y),z);
}

void update(int x){
	if(fa(x)) update(fa(x));
	pushdown(x);
}

void querypos(){
	int pos; scanf("%d",&pos);
	if(mapping[pos]!=-1){
		update(mapping[pos]);
		int x=mapping[pos];
		int ans=tree[ls(x)].size+1;
		while(fa(x)){
			if(rs(fa(x))==x){
				ans+=tree[ls(fa(x))].size+1;
			}
			x=fa(x);
		}
		printf("%d\n",ans);
	}else{
		printf("0\n");
	}
}

void at(){
	int pos; scanf("%d",&pos);
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,1,y,z);
	printf("%c\n",(char)(tree[y].key+'a'));
	root=merge(merge(x,y),z);
}

void count(){
	int l,r; scanf("%d%d",&l,&r);
	int x,y,z;
	split(root,l-1,x,y);
	split(y,r-l+1,y,z);
	int ans=0;
	for(int i=0;i<26;++i){
		if(tree[y].count&(1<<i))
			++ans;
	}
	printf("%d\n",ans);
	root=merge(merge(x,y),z);
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",tmp+1);
	for(int i=1;i<=n;++i){
		root=merge(root,create(tmp[i]-'a',i));
		mapping[i]=total;
	}
	while(m--){
		scanf("%s",tmp);
		switch(tmp[0]){
			case 'I': insert(); break;
			case 'D': remove(); break;
			case 'R': reserve(); break;
			case 'P': querypos(); break;
			case 'T': at(); break;
			case 'Q': count(); break;
		}
	}
	return 0;
}
