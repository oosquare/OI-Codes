#include <bits/stdc++.h>
using namespace std;

const int maxn = 100001;

int n;
double p[maxn], f[maxn], l[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf", &p[i]);
    }
    for (int i = 1; i <= n; ++i) {
        l[i] = (l[i - 1] + 1) * p[i];
        f[i] = f[i - 1] + (2 * l[i - 1] + 1) * p[i];
    }
    printf("%.15lf\n", f[n]);
    return 0;
}