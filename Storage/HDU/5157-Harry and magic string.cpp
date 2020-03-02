#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn=100005;
char s[2*maxn],s0[2*maxn];
int r[2*maxn];
ll suf[maxn],pre[maxn],sum[maxn];
int n,n0;

void manacher() {
    int p=0,maxx=0; r[0]=1;
    for(int i=1;i<=n;++i) {
        if(maxx>i) r[i]=min(maxx-i,r[2*p-i]); else r[i]=1;
        while(s[i-r[i]]==s[i+r[i]]) ++r[i];
        if(i+r[i]>maxx) { maxx=i+r[i]; p=i; }
    }
}

void calc() {
    for(int i=2;i<=2*n0;++i) {
        int x=(i+1)/2;
        ++suf[x]; --suf[x+r[i]/2];
    }
    for(int i=2;i<=2*n0;++i) {
        int x=i/2;
        ++pre[x]; --pre[x-r[i]/2];
    }
    for(int i=1;i<=n0;++i) {
        suf[i]+=suf[i-1];
        sum[i]+=sum[i-1]+suf[i];
    }
    for(int i=n0;i>=1;--i) {
        pre[i]+=pre[i+1];
    }
    ll ans=0;
    for(int i=1;i<=n0;++i) {
        ans+=pre[i]*sum[i-1];
    }
    printf("%lld\n",ans);
}

int main() {
    while(scanf("%s",s0+1)!=EOF) {
        memset(r,0,sizeof(r));
        memset(sum,0,sizeof(sum));
        memset(suf,0,sizeof(suf));
        memset(pre,0,sizeof(pre));
        n0=strlen(s0+1);
        n=2; s[0]='$'; s[1]='#';
        for(int i=1;i<=n0;++i) {
            s[n++]=s0[i]; s[n++]='#';
        }
        s[n]='^';
        manacher();
        calc();
    }
    return 0;
}