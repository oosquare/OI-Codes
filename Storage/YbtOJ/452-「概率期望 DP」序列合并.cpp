#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 1000 + 10;
constexpr int mod = 1e9 + 7;

int p[maxn][maxn * 2], q[maxn][maxn * 2], g[maxn][maxn * 2], f[maxn][maxn * 2];
int ans[maxn], n, m, maxv, inv;

int power(int x, int y) {
    int res = 1;
    while (y) {
        if (y % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
        y /= 2;
    }
    return res;
}

void DP() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= maxv; ++j) {
            p[i][j] = (1LL * p[i][j - 1] * p[i - 1][j - 1] + (j <= m ? inv : 0)) % mod;
            q[i][j] = (1 - (j < maxv ? p[i - 1][j] : 0) + mod) % mod;
        }
    }
    for (int j = 1; j <= maxv; ++j) {
        g[1][j] = f[1][j] = j;
        ans[1] = (1LL * p[1][j] * q[1][j] % mod * j + ans[1]) % mod;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= maxv; ++j) {
            int tmp = ans[i - 1] - (j < maxv ? 1LL * p[i - 1][j] * f[i - 1][j] % mod : 0) + mod;
            g[i][j] = (1LL * tmp * power(q[i][j], mod - 2) + j) % mod;
            ans[i] = (1LL * p[i][j] * q[i][j] % mod * g[i][j] + ans[i]) % mod;
        }
        for (int j = maxv; j >= 1; --j) {
            f[i][j] = (1LL * q[i][j] * g[i][j] + 1LL * (1 - q[i][j] + mod) * f[i][j + 1]) % mod;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    cin >> n >> m >> maxv;
    inv = power(m, mod - 2);
    maxv = min(maxv, n + m - 1);
    DP();
    cout << ans[n] << endl;
    return 0;
}
