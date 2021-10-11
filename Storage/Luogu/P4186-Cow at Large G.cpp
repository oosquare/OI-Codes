#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

int n, k, f[maxn], dis[maxn];
vector<int> tree[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa, int dep) {
    if (tree[x].size() == 1) {
        f[x] = 1;
        return;
    } else {
        dis[x] = 0x3f3f3f3f;
    }
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x, dep + 1);
        dis[x] = min(dis[x], dis[y] + 1);
    }
    if (dep >= dis[x]) {
        f[x] = 1;
        return;
    }
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        if (dis[y] == dep) {
            f[x] += 1;
            continue;
        }
        f[x] += f[y];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }
    dfs(k, 0, 0);
    cout << f[k] << endl;
    return 0;
}