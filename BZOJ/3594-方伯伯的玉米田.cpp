#include <bits/stdc++.h>
using namespace std;

const int maxn=10000,maxk=500;

int n,k,maxx,ans,h[maxn+2],b[maxn+2][maxk+2];

inline int lowbit(int x) { return x&-x; }

inline void modify(int x,int y,int v) {
    for(;x<=maxx+k;x+=lowbit(x)) 
        for(int i=y;i<=k+1;i+=lowbit(i)) 
            b[x][i]=max(b[x][i],v);
}

inline int query(int x,int y) {
    int ans=0; 
    for(;x;x-=lowbit(x)) 
        for(int i=y;i;i-=lowbit(i)) 
            ans=max(ans,b[x][i]); 
    return ans;
}

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) { scanf("%d",&h[i]); maxx=max(maxx,h[i]); }
    for(int i=1;i<=n;++i) {
        for(int j=k;j>=0;--j) {
            int x=query(h[i]+j,j+1)+1;
            ans=max(ans,x);
            modify(h[i]+j,j+1,x);
        }
    }
    printf("%d\n",ans);
}