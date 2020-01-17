#include <bits/stdc++.h>
using namespace std;

const int mod=100007,maxn=100000,maxk=10;

struct Position
{
    int X,Y;
    friend bool operator<(Position a,Position b) { return a.X<b.X; }
};

struct BinaryIndexedTree
{
    int Array[maxn];
    
    inline void modify(int x,int y) {
        for(;x<=maxn;x+=(-x&x)) { Array[x]=((long long)Array[x]+y)%mod; }
    }

    inline int query(int x) {
        int ans=0; for(;x;x-=(-x&x)) { ans=((long long)ans+Array[x])%mod; } return ans;
    }

    inline int rquery(int l,int r) { return (query(r)-query(l-1)+mod)%mod; }
};

Position tmppos[maxn+2];
BinaryIndexedTree up[maxk+2],down[maxk+2];
int posy[maxn+2],n,k;
int f[maxn+2][maxk+2][2];

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) { scanf("%d%d",&tmppos[i].X,&tmppos[i].Y); }
    sort(tmppos+1,tmppos+1+n);
    for(int i=1;i<=n;++i) { posy[i]=tmppos[i].Y; }
    up[0].modify(posy[1],1); down[0].modify(posy[1],1);
    for(int i=2;i<=n;++i) {
        f[i][0][0]=f[i][0][1]=1;
        for(int j=1;j<=k;++j) {
            f[i][j][0]=(up[j].rquery(1,posy[i])+down[j-1].rquery(1,posy[i]))%mod;
            f[i][j][1]=(down[j].rquery(posy[i]+1,maxn)+up[j-1].rquery(posy[i]+1,maxn))%mod;
        }
        for(int j=0;j<=k;++j){
            up[j].modify(posy[i],f[i][j][0]);
            down[j].modify(posy[i],f[i][j][1]);
        }
    }
    printf("%d\n",(up[k].query(maxn)+down[k].query(maxn))%mod);
    return 0;
}