#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int mod = 9999973;

int n, m, ans;
int f[maxn][maxn][maxn];

int comb(int n, int m) {
    if (n < m)
        return 0;

    if (m == 1)
        return n;
    
    return 1ll * n * (n - 1) / 2 % mod; // m = 2
}

void add(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    f[0][0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k + j <= m; ++k) {
                int blank = m - j - k;
                f[i][j][k] = f[i - 1][j][k];

                if (j > 0)
                    add(f[i][j][k], 1ll * f[i - 1][j - 1][k] * (blank + 1) % mod);

                if (k > 0 && j < m)
                    add(f[i][j][k], 1ll * f[i - 1][j + 1][k - 1] * (j + 1) % mod);
                
                if (j > 1)
                    add(f[i][j][k], 1ll * f[i - 1][j - 2][k] * comb(blank + 2, 2) % mod);

                if (j > 0 && k > 0)
                    add(f[i][j][k], 1ll * f[i - 1][j][k - 1] * comb(blank + 1, 1) % mod * j % mod);

                if (k > 1 && j < m - 1)
                    add(f[i][j][k], 1ll * f[i - 1][j + 2][k - 2] * comb(j + 2, 2) % mod);

                if (i == n)
                    add(ans, f[i][j][k]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}