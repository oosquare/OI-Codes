#include <bits/stdc++.h>
using namespace std;

const int maxn=3e5+10;
int n,s;
long long t[maxn],c[maxn],f[maxn];
deque<int> q;

int search(int k) {
    if(q.size()==1) return q[0];
    int l=0,r=q.size()-1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(f[q[mid+1]]-f[q[mid]]<=k*(c[q[mid+1]]-c[q[mid]])) l=mid+1;
        else r=mid-1;
    }
    return q[l];
}

int main() {
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;++i) { scanf("%lld%lld",&t[i],&c[i]); t[i]+=t[i-1]; c[i]+=c[i-1]; }
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    q.push_back(0);
    for(int i=1;i<=n;++i) {
        int j=search(s+t[i]);
        f[i]=f[j]-(s+t[i])*c[j]+t[i]*c[i]+s*c[n];
        int l=q.size()-1;
        while(q.size()>1&&(f[q[l]]-f[q[l-1]])*(c[i]-c[q[l]])>=(c[q[l]]-c[q[l-1]])*(f[i]-f[q[l]])) {
            q.pop_back(); --l;
        }
        q.push_back(i);
    }
    printf("%lld\n",f[n]);
    return 0;
}