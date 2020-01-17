#include <bits/stdc++.h>
using namespace std;

const int maxn=100001;

int n;
double p[maxn],f[maxn],l1[maxn],l2[maxn];

inline double square(double x) {
    return x*x;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i) { scanf("%lf",&p[i]); }
    for(int i=1;i<=n;++i) {
        l1[i]=(l1[i-1]+1)*p[i];
        l2[i]=(l2[i-1]+2*l1[i-1]+1)*p[i];
        f[i]=f[i-1]+(3*l2[i-1]+3*l1[i-1]+1)*p[i];
    }
    printf("%.1lf\n",f[n]);
    return 0;
}