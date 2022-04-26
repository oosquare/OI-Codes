#include <iostream>
#include <vector>

constexpr int MAX_N = 500000 + 10;
constexpr int MAX_D = 20 + 2;
constexpr int INF = 0x3f3f3f3f;

int n, m, d;
int w[MAX_N];
bool cover[MAX_N];
std::vector<int> tree[MAX_N];
long long f[MAX_N][MAX_D], g[MAX_N][MAX_D];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    for (int i = 1; i <= d; ++i)
        f[x][i] = w[x];

    f[x][d + 1] = INF;

    if (cover[x])
        f[x][0] = g[x][0] = w[x];

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        for (int i = 0; i <= d; ++i)
            f[x][i] = std::min(f[x][i] + g[y][i], g[x][i + 1] + f[y][i + 1]);

        for (int i = d - 1; i >= 0; --i)
            f[x][i] = std::min(f[x][i], f[x][i + 1]);

        g[x][0] = f[x][0];

        for (int i = 1; i <= d; ++i)
            g[x][i] += g[y][i - 1];

        for (int i = 1; i <= d; ++i)
            g[x][i] = std::min(g[x][i], g[x][i - 1]);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("data.in", "r", stdin);
    std::freopen("data.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> d;

    for (int i = 1; i <= n; ++i)
        std::cin >> w[i];

    std::cin >> m;

    for (int i = 1; i <= m; ++i) {
        int x;
        std::cin >> x;
        cover[x] = true;
    }

    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        link(x, y);
    }

    dfs(1, 0);
    std::cout << f[1][0] << std::endl;
    return 0;
}
