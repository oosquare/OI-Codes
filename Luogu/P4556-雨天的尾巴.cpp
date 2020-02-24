#include <bits/stdc++.h>
using namespace std;

namespace IO
{
    char buf[1<<15],*fs,*ft;
    char out[1<<28],*fe=out;
    inline char getc(){
        return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++;
    }
    
    template <typename T>
    inline void read(T &x){
        x=0;
        bool f=false;
        char ch=getchar();
        while (!isdigit(ch) && ch^'-') ch=getchar();
        if (ch=='-') f=true, ch=getchar();
        while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
        if(f)
            x=-x;
        return;
    }

    
    inline void flush(){
        fwrite(out,1,fe-out,stdout);
        fe=out;
    }

    template <typename T>
    inline void writeln(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++='\n';
    }

    template <typename T>
    inline void writesp(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++=' ';
    }
}

struct node {
    int l,r,max,id;
};

struct e {
    int to,next;
};

constexpr int maxn=1e5+10;
constexpr int maxz=1e5;

e edge[maxn<<1]; int edgetotal,head[maxn];
node tree[maxn<<6]; int total,root[maxn];
int dep[maxn],f[maxn][21];
int ans[maxn],n,m;

inline void link(int x,int y){
    edge[++edgetotal]=(e){y,head[x]}; head[x]=edgetotal;
    edge[++edgetotal]=(e){x,head[y]}; head[y]=edgetotal;
}

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline void pushup(int x){
    if(tree[ls(x)].max>=tree[rs(x)].max){
        tree[x].id=tree[ls(x)].id;
        tree[x].max=tree[ls(x)].max;    
    } else {
        tree[x].id=tree[rs(x)].id;
        tree[x].max=tree[rs(x)].max;
    }
}

void modify(int &x,int l,int r,int p,int v){
    if(!x) x=++total;
    if(l==r&&r==p){
        tree[x].max+=v;
        tree[x].id=tree[x].max?l:0;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) modify(ls(x),l,mid,p,v);
    else modify(rs(x),mid+1,r,p,v);
    pushup(x);
}

inline int rankat(int x){
    return tree[x].id;
}

int merge(int x,int y,int l,int r){
    if(!x||!y) return x^y;
    if(l==r){
        tree[x].max+=tree[y].max;
        tree[x].id=tree[x].max?l:0;
        return x;
    }
    int mid=(l+r)>>1;
    tree[x].l=merge(tree[x].l,tree[y].l,l,mid);
    tree[x].r=merge(tree[x].r,tree[y].r,mid+1,r);
    pushup(x);
    return x;
}

void preprocess(int x){
    dep[x]=dep[f[x][0]]+1;
    for(int i=1;(1<<i)<=dep[x];++i) f[x][i]=f[f[x][i-1]][i-1];
    for(int i=head[x],y;y=edge[i].to,i;i=edge[i].next){
        if(y==f[x][0]) continue;
        f[y][0]=x;
        preprocess(y);
    }
}

int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;--i){
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
        if(x==y) return x;
    }
    for(int i=20;i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}

void send(int x,int y,int z){
    int lca=LCA(x,y);
    modify(root[x],1,maxz,z,1);
    modify(root[y],1,maxz,z,1);
    modify(root[lca],1,maxz,z,-1);
    modify(root[f[lca][0]],1,maxz,z,-1);
}

void DFS(int x){
    for(int i=head[x],y;y=edge[i].to,i;i=edge[i].next){
        if(y==f[x][0]) continue;
        DFS(y);
        root[x]=merge(root[x],root[y],1,maxz);
    }
    ans[x]=rankat(root[x]);
    
}

int main(){
    using namespace IO;
    read(n); read(m);
    for(int i=1;i<n;++i){
        int x,y; read(x); read(y); link(x,y);
    }
    preprocess(1);
    for(int i=1;i<=m;++i){
        int x,y,z; read(x); read(y); read(z); send(x,y,z);
    }
    DFS(1);
    for(int i=1;i<=n;++i){
        writeln(ans[i]);
    }
    flush();
    return 0;
}