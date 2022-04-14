#include <iostream>
#include <vector>
#include <cmath>

constexpr int MAX_N = 2e5 + 10;
constexpr int MOD = 998244353;

int n, v[MAX_N];
int f[MAX_N][2];
long double g[MAX_N][2];
std::vector<int> tree[MAX_N];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    f[x][0] = 1;
    f[x][1] = v[x];
    g[x][0] = 0;
    g[x][1] = std::log((long double)v[x]);

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
        // f[x][0] <- max(f[y][0], f[y][1])
        if (g[y][0] > g[y][1]) {
            f[x][0] = (int)(1ll * f[x][0] * f[y][0] % MOD);
            g[x][0] += g[y][0];
        } else {
            f[x][0] = (int)(1ll * f[x][0] * f[y][1] % MOD);
            g[x][0] += g[y][1];
        }
        // f[x][1] <- f[y][0]
        f[x][1] = (int)(1ll * f[x][1] * f[y][0] % MOD);
        g[x][1] += g[y][0];
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("doubt.in", "r", stdin);
    freopen("doubt.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n;

    for (int i = 1; i <= n; ++i) std::cin >> v[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        link(x, y);
    }

    dfs(1, 0);
    std::cout << (g[1][0] > g[1][1] ? f[1][0] : f[1][1]) << std::endl;
    return 0;
}
