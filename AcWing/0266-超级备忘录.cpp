#include <bits/stdc++.h>
using namespace std;

struct node
{
    int key,add,rev,min,lc,rc,size,pri;
};

constexpr int maxn=100000+10;
node tree[maxn<<4]; int root,seed,total;
int n,m;

inline int myrand() { return seed=(int)((seed+3)*341281LL%0x7fffffff); }

inline int &ls(int x) { return tree[x].lc; }

inline int &rs(int x) { return tree[x].rc; }

inline void chkmin(int &x,int y) { x=min(x,y); }

inline void pushup(int x){
    if(x){
        tree[x].size=1;
        tree[x].min=tree[x].key;
        if(ls(x)){ tree[x].size+=tree[ls(x)].size; chkmin(tree[x].min,tree[ls(x)].min); }
        if(rs(x)){ tree[x].size+=tree[rs(x)].size; chkmin(tree[x].min,tree[rs(x)].min); }
    }
}

void pushdown(int x){
    if(tree[x].add){
        int ad=tree[x].add;
        if(ls(x)){
            tree[ls(x)].add+=ad; tree[ls(x)].min+=ad; tree[ls(x)].key+=ad;
        }
        if(rs(x)){
            tree[rs(x)].add+=ad; tree[rs(x)].min+=ad; tree[rs(x)].key+=ad;
        }
        tree[x].add=0;
    }
    if(tree[x].rev){
        swap(ls(x),rs(x));
        if(ls(x)){
            tree[ls(x)].rev^=1;
        }
        if(rs(x)){
            tree[rs(x)].rev^=1;
        }
        tree[x].rev=0;
    }
}

inline int create(int key){ tree[++total]={ key,0,0,key,0,0,1,myrand() }; return total; }

void split(int root,int sze,int &x,int &y){
    if(root==0) { x=y=0; return; }
    pushdown(root);
    if(tree[ls(root)].size<sze){
        x=root; split(rs(x),sze-tree[ls(x)].size-1,rs(x),y);
    }else{
        y=root; split(ls(y),sze,x,ls(y));
    }
    pushup(root);
}

int merge(int x,int y){
    if(!x||!y) return x^y;
    pushdown(x); pushdown(y);
    if(tree[x].pri<tree[y].pri){
        rs(x)=merge(rs(x),y); pushup(x); return x;
    }else{
        ls(y)=merge(x,ls(y)); pushup(y); return y;
    }
}

void add(){
    int l,r,d;
    int x,y,z;
    scanf("%d%d%d",&l,&r,&d);
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    tree[y].add+=d;
    tree[y].min+=d;
    tree[y].key+=d;
    root=merge(merge(x,y),z);
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

void revolve(){
    int l,r,t;
    scanf("%d%d%d",&l,&r,&t);
    int x,y,z,y1,y2;
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    t%=tree[y].size;
    split(y,tree[y].size-t,y1,y2);
    y=merge(y2,y1);
    root=merge(merge(x,y),z);
}

void insert(){
    int p,v,x,y;
    scanf("%d%d",&p,&v);
    split(root,p,x,y);
    root=merge(merge(x,create(v)),y);
}

void remove(){
    int p,x,y,z;
    scanf("%d",&p);
    split(root,p-1,x,y);
    split(y,1,y,z);
    root=merge(x,z);
}

void query(){
    int l,r;
    scanf("%d%d",&l,&r);
    int x,y,z;
    split(root,l-1,x,y);
    split(y,r-l+1,y,z);
    printf("%d\n",tree[y].min);
    root=merge(merge(x,y),z);
}

int main(){
//  freopen("project.in","r",stdin);
//  freopen("project.out","w",stdout);
    scanf("%d",&n);
    while(n--){
        int x; scanf("%d",&x);
        root=merge(root,create(x));
    }
    scanf("%d",&m);
    while(m--){
        char cmd[10];
        scanf("%s",cmd);
        if(cmd[0]=='A') add();
        if(cmd[0]=='R'&&cmd[3]=='E') reserve();
        if(cmd[0]=='R'&&cmd[3]!='E') revolve();
        if(cmd[0]=='I') insert();
        if(cmd[0]=='D') remove();
        if(cmd[0]=='M') query();
    }
    return 0;
}