#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 4e5 + 10;

int n, m, q;
int dep[maxn], f[maxn];
int father[maxn], sze[maxn];
bool added[maxn], vis[maxn];
vector<int> tree[maxn];
vector<pair<int, int>> e;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    f[x] = fa;
    vis[x] = true;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
    }
}

void init(int n) {
    iota(father + 1, father + 1 + n, 1);
    fill(sze + 1, sze + 1 + n, 1);
}

int find(int x) {
    return x == father[x] ? x : father[x] = find(father[x]);
}

int merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (dep[x] < dep[y])
        swap(x, y);

    if (x == y)
        return x;
    
    father[x] = merge(f[x], y);
    sze[father[x]] += sze[x];
    sze[x] = 0;
    return father[x];
}

int query(int x) {
    return sze[find(x)];
}

int main() {
    freopen("alliance.in", "r", stdin);
    freopen("alliance.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    init(n);

    for (int i = 1; i <= m + q; ++i) {
        int x, y;
        cin >> x >> y;
        e.push_back({x, y});
        x = find(x);
        y = find(y);

        if (x != y) {
            link(e[i - 1].first, e[i - 1].second);
            added[i] = true;
            father[x] = y;
        }
    }

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i, 0);

    iota(father + 1, father + 1 + n, 1);

    for (int i = 1; i <= m; ++i) {
        if (added[i])
            continue;

        auto [x, y] = e[i - 1];
        merge(x, y);
    }

    for (int i = m + 1; i <= m + q; ++i) {
        if (added[i]) {
            cout << "No" << endl;
        } else {
            auto [x, y] = e[i - 1];
            merge(x, y);
            cout << query(x) << endl;
        }
    }

    return 0;
}
