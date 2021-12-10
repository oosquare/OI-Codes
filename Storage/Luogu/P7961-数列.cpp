#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 30 + 2;
constexpr int maxm = 100 + 5;
constexpr int mod = 998244353;

int n, m, s;
int f[2][maxn][maxn][maxn];
int power[maxm][maxn], comb[maxn][maxn];
int ans;

inline void add(int &x, int y) {
    x += y;

    if (x >= mod)
        x -= mod;
}

inline int popcount(int x) {
    int res = 0;

    while (x) {
        res += (x & 1);
        x >>= 1;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> s;
    ++m;

    for (int i = 1; i <= m; ++i) {
        power[i][0] = 1;
        cin >> power[i][1];

        for (int j = 2; j <= n; ++j)
            power[i][j] = 1ll * power[i][j - 1] * power[i][1] % mod;
    }

    for (int i = 0; i <= n; ++i) {
        comb[i][0] = comb[i][i] = 1;

        for (int j = 1; j < i; ++j)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    f[0][0][0][0] = 1;

    for (int i = 0, now, suf; now = (i & 1), suf = (now ^ 1), i < m; ++i) {
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= s; ++k)
                for (int l = 0; l <= n; ++l)
                    f[suf][j][k][l] = 0;

        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= s; ++k) {
                for (int l = 0; l <= n; ++l) {
                    for (int t = 0; j + t <= n; ++t) {
                        if (k + ((t + l) & 1) > s)
                            continue;

                        add(
                            f[suf][j + t][k + ((t + l) & 1)][(t + l) >> 1],
                            1ll * f[now][j][k][l] * power[i + 1][t] % mod * comb[j + t][t] % mod
                        );
                    }
                }
            }
        }
    }

    for (int i = 0; i <= s; ++i)
        for (int j = 0; j <= n; ++j)
            if (i + popcount(j) <= s)
                add(ans, f[m & 1][n][i][j]);

    cout << ans << endl;
    return 0;
}