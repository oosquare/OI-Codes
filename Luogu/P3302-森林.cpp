#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

template <typename T>
void read(T &number) {
    number = 0; int symbol = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') symbol *= -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        number = (number << 3) + (number << 1) + (c ^ '0');
        c = getchar();
    }
    number *= symbol;
}

struct node {
    int l,r,sum;
};

struct e {
    int to,nxt;
};

constexpr int maxn=8e4+10;
node tree[maxn<<7]; int treeuuid,root[maxn];
e edge[maxn<<2]; int edgeuuid,head[maxn];
int dep[maxn],sze[maxn],f[maxn][18];
vector<int> data; int mapping[maxn];
int fa[maxn];
bool vis[maxn];
int n,m,t;

int find(int x) { return x==fa[x]?x:fa[x]=find(fa[x]); }

inline void link(int x,int y){
    edge[++edgeuuid]=(e){y,head[x]}; head[x]=edgeuuid;
    edge[++edgeuuid]=(e){x,head[y]}; head[y]=edgeuuid;
}

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)

void insert(int &x,int y,int l,int r,int v){
    tree[x=++treeuuid]=tree[y];
    tree[x].sum+=1;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(v<=mid)
        insert(ls(x),ls(y),l,mid,v);
    else
        insert(rs(x),rs(y),mid+1,r,v);
}

int query(int x,int y,int lca,int fa,int l,int r,int rk){
    if(l==r) return l;
    int tmp=tree[ls(x)].sum+tree[ls(y)].sum-tree[ls(lca)].sum-tree[ls(fa)].sum;
    int mid=(l+r)>>1;
    if(rk<=tmp)
        return query(ls(x),ls(y),ls(lca),ls(fa),l,mid,rk);
    else
        return query(rs(x),rs(y),rs(lca),rs(fa),mid+1,r,rk-tmp);
}

void DFS(int x,int father,int rt){
    f[x][0]=father;
    for(int i=1;i<=17;++i)
        f[x][i]=f[f[x][i-1]][i-1];
    sze[rt]+=1;
    dep[x]=dep[father]+1;
    insert(root[x],root[father],1,n,mapping[x]);
    vis[x]=1;
    fa[x]=father;
    for(int i=head[x],y;y=edge[i].to,i;i=edge[i].nxt){
        if(y==father) continue;
        DFS(y,x,rt);
    }
}

int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=17;i>=0;--i){
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
        if(x==y) return x;
    }
    for(int i=17;i>=0;--i){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}

void solve(){
    read(n); read(m); read(t);
    for(int i=1;i<=n;++i){
        read(mapping[i]); data.push_back(mapping[i]);
        fa[i]=i;
    }
    for(int i=1;i<=m;++i){
        int x,y; read(x); read(y);
        link(x,y);
    }
    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()),data.end());
    for(int i=1;i<=n;++i)
        mapping[i]=lower_bound(data.begin(), data.end(),mapping[i])-data.begin()+1;
    for(int i=1;i<=n;++i){
        if(!vis[i]){
            DFS(i,0,i);
            fa[i]=i;
        }
    }
    int lastans=0,x,y,k;
    char cmd[5];
    while(t--){
        scanf("%s",cmd);
        read(x); read(y);
        if(cmd[0]=='Q'){
            read(k); x^=lastans; y^=lastans; k^=lastans;
            int lca=LCA(x,y);
            lastans=data[query(root[x],root[y],root[lca],root[f[lca][0]],1,n,k)-1];
            printf("%d\n",lastans);
        }else{
            x^=lastans; y^=lastans;
            link(x,y);
            int fx=find(x),fy=find(y);
            if(sze[fx]<sze[fy]){
                swap(fx,fy);
                swap(x,y);
            }
            DFS(y,x,fx);
        }
    }
}

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////
    
    int id; read(id);
    solve();

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", (int)(etime - stime));
    if (etime - stime >= TIME_LIMIT) {
        printf("<<< Warning >>> Time Limited Exceeded\n");
    }
#endif
    return 0;
}

//
//        ^ y
//       1|                            y = sin x (0 < x < 2π)
//  - - - | - - - + - - - - - - - - - - - - - -
//        |  +         +
// -------+---------------+---------------+----------> x
//       O|               π  +         +  2π
//  - - - | - - - - - - - - - - - + - - - - - -
//      -1|
//        |
//
