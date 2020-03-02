#include <bits/stdc++.h>
using namespace std;

const int maxm=200010,maxn=100010;

struct Edge
{
    int to,nxt,weight;
    Edge() {}
    Edge(int a,int b,int c) { to=a; nxt=b; weight=c; }
};

Edge graph[maxm]; 
int head[maxn],total,n,m,order[maxn],in[maxn],out[maxn],ordert;
double f[maxn];

void link(int x,int y,int w) {
    graph[++total]=Edge(y,head[x],w);
    head[x]=total;
    ++in[y]; ++out[x];
}

void solve() {
    queue<int> q;
    for(int i=1;i<=n;++i) {
        if(in[i]==0) q.push(i);
    }
    while(!q.empty()) {
        int x=q.front(); q.pop(); order[++ordert]=x;
        for(int i=head[x],y;y=graph[i].to,i;i=graph[i].nxt) {
            if(--in[y]==0) q.push(y);
        }
    }
    f[n]=0;
    for(int i=n-1;i;--i) {
        int x=order[i];
        f[x]=0;
        for(int j=head[x],y,w;y=graph[j].to,w=graph[j].weight,j;j=graph[j].nxt) {
            f[x]+=1.0*(f[y]+w)/out[x];
        }
    }
    printf("%.2lf\n",f[1]);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        link(a,b,c);
    }
    solve();
    return 0;
}