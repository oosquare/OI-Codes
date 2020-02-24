#include <bits/stdc++.h>
using namespace std;

struct node
{
    int key,max,add,rev,lc,rc,size,pri;
};

constexpr int maxn=500000+10;
node tree[maxn]; int total,root,seed;
int n,m;

inline int myrand(){ return seed=(int)((seed+3)*321837LL%0x7fffffff); }

inline int &ls(int root) { return tree[root].lc; }

inline int &rs(int root) { return tree[root].rc; }

inline int getmax(int root){
    return root?tree[root].max:-0x7fffffff;
}

inline void pushup(int root){
    if(root){
        tree[root].size=tree[ls(root)].size+tree[rs(root)].size+1;
        tree[root].max=max(tree[root].key,max(getmax(ls(root)),getmax(rs(root))));
    }
}

void pushdown(int root){
    if(tree[root].rev){
        tree[root].rev=0;
        swap(ls(root),rs(root));
        tree[ls(root)].rev^=1;
        tree[rs(root)].rev^=1;
    }
    if(tree[root].add){
        if(ls(root)){
            tree[ls(root)].add+=tree[root].add;
            tree[ls(root)].key+=tree[root].add;
            tree[ls(root)].max+=tree[root].add;
        }
        if(rs(root)){
            tree[rs(root)].add+=tree[root].add;
            tree[rs(root)].key+=tree[root].add;
            tree[rs(root)].max+=tree[root].add;
        }
        tree[root].add=0;
    }
}

inline int create(int key){
    tree[++total]=(node){ key,key,0,0,0,0,1,myrand() }; return total;
}

void split(int root,int sze,int &x,int &y){
    if(!root){
        x=y=0;
        return;
    }
    pushdown(root);
    if(tree[ls(root)].size<sze){
        x=root;
        split(rs(x),sze-tree[ls(x)].size-1,rs(x),y);
        pushup(x);
    }else{
        y=root;
        split(ls(y),sze,x,ls(y));
        pushup(y);
    }
}

int merge(int x,int y){
    if(!x||!y) return x^y;
    if(tree[x].pri<tree[y].pri){
        pushdown(x);
        rs(x)=merge(rs(x),y);
        pushup(x);
        return x;
    }else{
        pushdown(y);
        ls(y)=merge(x,ls(y));
        pushup(y);
        return y;
    }
}

void modify(int l,int r,int v){
    int x,y,z;
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    tree[y].add+=v;
    tree[y].key+=v;
    tree[y].max+=v;
    root=merge(merge(x,y),z);
}

void reserve(int l,int r){
    int x,y,z;
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    tree[y].rev^=1;
    root=merge(merge(x,y),z);
}

int query(int l,int r){
    int x,y,z,ans;
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    ans=tree[y].max;
    root=merge(merge(x,y),z);
    return ans;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        root=merge(root,create(0)); 
    }
    for(int i=1;i<=m;++i){
        int k,l,r,v;
        scanf("%d%d%d",&k,&l,&r);
        if(k==1){
            scanf("%d",&v);
            modify(l,r,v);
        }else if(k==2){
            reserve(l,r);
        }else{
            printf("%d\n",query(l,r));
        }
    }
    return 0;
}