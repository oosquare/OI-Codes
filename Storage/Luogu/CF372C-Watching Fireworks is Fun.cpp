#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 150000 + 2;
constexpr int maxm = 300 + 2;

typedef long long ll;

int n, m, a, b, t[2], d, q[maxn], id, l, r;
ll ans = 0x7fffffffffffffffLL, f[2][maxn], sum;

int main() {
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &a, &b, &t[id ^ 1]);
        sum += b;
        l = 1;
        r = 0;
        ll len = 1LL * (t[id ^ 1] - t[id]) * d;
        for (int j = 1; j <= n; ++j) {
            while (l <= r && q[l] < j - len)
                ++l;
            while (l <= r && f[id][q[r]] > f[id][j])
                --r;
            q[++r] = j;
            f[id ^ 1][j] = f[id][q[l]] + abs(a - j);
        }
        l = 1;
        r = 0;
        for (int j = n; j >= 1; --j) {
            while (l <= r && q[l] > j + len)
                ++l;
            while (l <= r && f[id][q[r]] > f[id][j])
                --r;
            q[++r] = j;
            f[id ^ 1][j] = min(f[id ^ 1][j], f[id][q[l]] + abs(a - j));
        }
        id ^= 1;
    }
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, f[id][i]);
    }
    printf("%lld\n", sum - ans);
    return 0;
}
