#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 3001;
const ll inf = 1e18;

ll sum[maxn], f[maxn][maxn];
int n, m;

ll power(ll x) { return x * x; }

void solve(int x, int l, int r, int sl, int sr) {
    int mid = (l + r) >> 1, smid = 0;
    f[x][mid] = inf;
    for (int i = sl; i <= sr; ++i) {
        ll res = f[x - 1][i] + power(sum[mid] - sum[i]);
        if (res < f[x][mid]) {
            f[x][mid] = res;
            smid = i;
        }
    }
    if (l < mid)
        solve(x, l, mid - 1, sl, smid);
    if (mid < r)
        solve(x, mid + 1, r, smid, sr);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &sum[i]);
        sum[i] += sum[i - 1];
    }
    for (int i = 1; i <= n; ++i) {
        f[1][i] = power(sum[i]);
    }
    for (int i = 2; i <= m; ++i) {
        solve(i, 1, n, 1, n);
    }
    printf("%lld\n", m * f[m][n] - power(sum[n]));
    return 0;
}