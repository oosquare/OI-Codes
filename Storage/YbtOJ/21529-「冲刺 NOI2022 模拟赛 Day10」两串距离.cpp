#include <iostream>
#include <cstring>

constexpr int MAX_N = 5000 + 10;
constexpr int MOD = 998244353;

int n, m;
char s[MAX_N], t[MAX_N];
int f[MAX_N][2 * MAX_N][2], g[MAX_N][2 * MAX_N][2];
int ans;

using Array = decltype(f);

void add(int &x, int y) {
    x += y;

    if (x >= MOD)
        x -= MOD;
}

void dp(char s[], Array f, int n) {
    f[n + 1][MAX_N][1] = 1;

    for (int i = n + 1; i >= 2; --i) {
        for (int j = -n; j <= n; ++j) {
            if (s[i - 1] == 'V' || s[i - 1] == '?') {
                add(f[i - 1][MAX_N + j + 1][0], f[i][MAX_N + j][0]);
                add(f[i - 1][MAX_N + j + 1][1], f[i][MAX_N + j][1]);
            }

            if (s[i - 1] == 'P' || s[i - 1] == '?') {
                add(f[i - 1][MAX_N + std::min(-1, j - 1)][0], f[i][MAX_N + j][0]);
                add(f[i - 1][MAX_N + std::min(-1, j - 1)][j <= 0 ? 1 : 0], f[i][MAX_N + j][1]);
            }
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("distance.in", "r", stdin);
    std::freopen("distance.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif 
    std::ios::sync_with_stdio(false);
    
    std::cin >> (s + 1);
    std::cin >> (t + 1);
    n = (int) std::strlen(s + 1);
    m = (int) std::strlen(t + 1);

    dp(s, f, n);
    dp(t, g, m);

    for (int i = -n; i <= n; ++i) {
        for (int j = -m; j <= m; ++j) {
            if (i + j >= -1)
                add(ans, 1ll * f[1][MAX_N + i][0] * g[1][MAX_N + j][0] % MOD);

            if (i + j >= 0) {
                add(ans, 1ll * f[1][MAX_N + i][1] * g[1][MAX_N + j][0] % MOD);
                add(ans, 1ll * f[1][MAX_N + i][0] * g[1][MAX_N + j][1] % MOD);
                add(ans, 1ll * f[1][MAX_N + i][1] * g[1][MAX_N + j][1] % MOD);
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}
