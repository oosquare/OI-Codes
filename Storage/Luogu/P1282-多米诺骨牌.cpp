#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr int maxd = 10000 + 10;
constexpr int base = 5000;
constexpr int oo = 0x3f3f3f3f;

int n, a[maxn], b[maxn], f[maxn][maxd], delta = oo, ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];

    memset(f, 0x3f, sizeof(f));
    f[0][base] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 2 * base; ++j) {
            f[i][j] = min(f[i][j], f[i - 1][j + a[i] - b[i]]);
            f[i][j] = min(f[i][j], f[i - 1][j + b[i] - a[i]] + 1);
            if (f[i][j] > oo) f[i][j] = oo;
        }
    }
    for (int i = 0; i <= 2 * base; ++i) {
        if (f[n][i] != oo && delta > abs(i - base)) {
            ans = f[n][i];
            delta = abs(i - base);
        }
    }
    cout << ans << endl;
    return 0;
}