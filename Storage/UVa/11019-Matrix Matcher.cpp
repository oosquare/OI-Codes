#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr int base1 = 5;
constexpr int base2 = 7;
constexpr int mod = 998244353;

using ll = long long;

int t, n, m, dx, dy;
char a[maxn][maxn], b[maxn][maxn];
ll ha[maxn][maxn], hb[maxn][maxn], power1[maxn], power2[maxn];

void init() {
    power1[0] = power2[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        power1[i] = power1[i - 1] * base1 % mod;
        power2[i] = power2[i - 1] * base2 % mod;
    }
}

void preprocess() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ha[i][j] = (ha[i][j - 1] * base1 + a[i][j] - 'a') % mod;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ha[i][j] = (ha[i - 1][j] * base2 + ha[i][j]) % mod;

    for (int i = 1; i <= dx; ++i)
        for (int j = 1; j <= dy; ++j)
            hb[i][j] = (hb[i][j - 1] * base1 + b[i][j] - 'a') % mod;
    for (int i = 1; i <= dx; ++i)
        for (int j = 1; j <= dy; ++j)
            hb[i][j] = (hb[i - 1][j] * base2 + hb[i][j]) % mod;
}

ll get(int x1, int y1) {
    int x2 = x1 + dx - 1, y2 = y1 + dy - 1;
    ll res = ha[x2][y2] -
             ha[x1 - 1][y2] * power2[dx] % mod -
             ha[x2][y1 - 1] * power1[dy] % mod +
             ha[x1 - 1][y1 - 1] * power2[dx] % mod * power1[dy] % mod;
    return (res % mod + mod) % mod;
}

void solve() {
    int ans = 0;
    for (int i = 1, ex = n - dx + 1; i <= ex; ++i)
        for (int j = 1, ey = m - dy + 1; j <= ey; ++j)
            if (get(i, j) == hb[dx][dy])
                ++ans;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> a[i][j];
        cin >> dx >> dy;
        for (int i = 1; i <= dx; ++i)
            for (int j = 1; j <= dy; ++j)
                cin >> b[i][j];
        preprocess();
        solve();
    }
    return 0;
}