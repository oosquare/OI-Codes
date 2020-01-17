#include <cstdio>
#include <iostream>
using namespace std;
typedef __int128 ll;
const int lim=100;
ll f[lim][lim],ans;
ll a[lim];
int n,m;

inline int read(){
    ll s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*f;
}

inline void write(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
}

int main() {
    //freopen("game.in","r",stdin);
    //freopen("game.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=m;i++) a[i]=read();
        for(int i=1;i<=m;i++) f[i][i]=a[i];
        for(int l=2;l<=m;l++)
            for(int i=1;i<=m-l+1;i++) {
                int j=i+l-1;
                f[i][j]= max(a[i]+2*f[i+1][j],a[j]+2*f[i][j-1]);
            }
        ans+=f[1][m];
    }
    ans*=2;
    write(ans);
    putchar('\n');
    return 0;
}