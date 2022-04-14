#include <iostream>
#include <vector>

constexpr int MOD = 998244353;
constexpr int MAX_N = 100000 + 10;

int n, q;
int a[MAX_N], k[MAX_N], b[MAX_N], d[MAX_N], p[MAX_N];
std::vector<int> tree[MAX_N];
int ans;

void add(int &x, int y) {
    x += y;

    if (x >= MOD)
        x -= MOD;
}

void sub(int &x, int y) {
    x -= y;

    if (x < 0)
        x += MOD;
}

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = (int)(1ll * res * x % MOD);

        x = (int)(1ll * x * x % MOD);
    }

    return res;
}

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x, int fa) {
    if (d[x] == 1) {
        k[x] = 0;
        b[x] = a[x];
        return;
    }

    int sum = d[x];

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs1(y, x);
        sub(sum, k[y]);
        add(b[x], b[y]);
    }

    add(b[x], (int)(1ll * d[x] * a[x] % MOD));
    k[x] = power(sum, MOD - 2);
    b[x] = (int)(1ll * b[x] * k[x] % MOD);
}

void dfs2(int x, int fa) {
    p[x] = (int)(1ll * (d[x] == 1 ? 1 : k[x]) * (fa == 0 ? 1 : p[fa]) % MOD);

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs2(y, x);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("walk.in", "r", stdin);
    std::freopen("walk.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; ++i) d[i] = (int)tree[i].size();

    dfs1(1, 0);
    dfs2(1, 0);

    ans = b[1];
    std::cout << ans << std::endl;

    std::cin >> q;

    for (int i = 1; i <= q; ++i) {
        int x, y;
        std::cin >> x >> y;
        sub(ans, (int)(1ll * d[x] * a[x] % MOD * p[x] % MOD));
        a[x] = y;
        add(ans, (int)(1ll * d[x] * a[x] % MOD * p[x] % MOD));
        std::cout << ans << std::endl;
    }

    return 0;
}
