#include <bits/stdc++.h>
using namespace std;

struct node
{
    int key[200],sum[200],l,r,size,pri;   
};

constexpr int maxn=50010;
node tree[maxn]; int root,seed,total;
int n,m,q;

inline int myrandom() { return seed=(int)((seed+3)*471921LL%0x7fffffff); }

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline void pushup(int x) {
    if(!root) return;
    tree[x].size=tree[ls(x)].size+tree[rs(x)].size+1;
    for(int i=0;i<m;++i)
        tree[x].sum[i]=tree[ls(x)].sum[i]+tree[rs(x)].sum[i]+tree[x].key[i];
}

inline int create(){
    total++;
    ls(total)=rs(total)=0;
    tree[total].size=1;
    tree[total].pri=myrandom();
    return total;
}

void split(int root,int sze,int &x,int &y){
    if(root==0){
        x=y=0;
        return;
    }
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
    if(x==0||y==0) return x^y;
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

void init(){
    root=create();
    tree[root].pri=-0x7fffffff;
}

void insert(int pos){
    int tot,p,v;
    scanf("%d",&tot);
    int nd=create();
    for(int i=0;i<tot;++i){
        scanf("%d%d",&p,&v);
        tree[nd].key[p]=tree[nd].sum[p]=v;
    }
    int x,y;
    split(root,pos,x,y);
    root=merge(merge(x,nd),y);
}

void remove(int pos){
    int x,y,z;
    split(root,pos-1,x,y);
    split(y,1,y,z);
    root=merge(x,z);
}

void qsize(){
    printf("%d\n",tree[root].size-1);
}

int query(int l,int r){
    int x,y,z;
    split(root,l,x,y);
    split(y,r-l+1,y,z);
    for(int i=0;i<m;++i){
        printf("%d ",tree[y].sum[i]);
    }
    printf("\n");
    root=merge(merge(x,y),z);
}

int main() {
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=n;++i){
        insert(i);
    }
    scanf("%d",&q);
    while(q--){
        char cmd[5];
        scanf("%s",cmd);
        if(cmd[0]=='I'){
            int x; scanf("%d",&x); insert(x+1);
        }else if(cmd[0]=='D'){
            int x; scanf("%d",&x); remove(x+1);
        }else if(cmd[1]=='A') {
            qsize();
        }else{
            int l,r; scanf("%d%d",&l,&r); query(l,r);
        }
    }
    printf("end\n");
    return 0;
}