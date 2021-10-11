#include <bits/stdc++.h>

constexpr int maxn = 100000 + 10;
constexpr int mod = 1e9 + 7;

int n, ans, f[maxn];
std::vector<int> tree[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    f[x] = 1;
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x);
        f[x] = 1LL * f[x] * (f[y] + 1) % mod;
    }
    ans = (ans + f[x]) % mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        link(x, y);
    }
    dfs(1, 0);
    std::cout << ans << std::endl;
    return 0;
}