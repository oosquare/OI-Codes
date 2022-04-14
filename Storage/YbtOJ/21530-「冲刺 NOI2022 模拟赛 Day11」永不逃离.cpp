#include <iostream>

constexpr int MAX_N = 2000 + 10;

int n, k, mod;
int co[MAX_N][MAX_N], f[MAX_N], g[MAX_N], w[MAX_N][MAX_N];
int ans;

void add(int &x, int y) {
    x += y;

    if (x >= mod)
        x -= mod;
}

void sub(int &x, int y) {
    x -= y;

    if (x < 0)
        x += mod;
}

void preprocess(int n) {
    for (int i = 0; i <= n; ++i) {
        co[i][0] = co[i][i] = 1;

        for (int j = 1; j < i; ++j)
            co[i][j] = (co[i - 1][j] + co[i - 1][j - 1]) % mod;
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("runaround.in", "r", stdin);
    std::freopen("runaround.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k >> mod;
    preprocess(n);

    g[0] = 1;

    for (int i = 1; i <= n; ++i)
        g[i] = (int) (2ll * k * g[i - 1] % mod);
        
    for (int i = 0; 2 * i <= n; ++i)
        w[1][i] = co[2 * i][i] % mod;

    for (int i = 2; i <= k; ++i)
        for (int j = 0; 2 * j <= n; ++j)
            for (int k = 0; k <= j; ++k)
                add(w[i][j], (int) (1ll * w[i - 1][j - k] * w[1][k] % mod * co[2 * j][2 * k] % mod));

    for (int i = 0; i <= n; ++i) {
        f[i] = g[i];

        for (int j = i % 2; j < i; j += 2)
            sub(f[i], (int) (1ll * f[j] * w[k][(i - j) / 2] % mod));
    }

    for (int i = 0; i <= n; ++i) 
        add(ans, (int) (1ll * f[i] * g[n - i] % mod));

    std::cout << ans << std::endl;

    return 0;
}
