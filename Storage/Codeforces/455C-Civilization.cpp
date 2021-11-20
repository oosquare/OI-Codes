#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 3e5 + 10;

int n, m, q;
vector<int> tree[maxn];
int vis[maxn], f[maxn][2], len[maxn], fa[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
        return;

    fa[y] = x;
}

void dfs(int x, int fa) {
    vis[x] = true;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        if (f[x][0] <= f[y][0] + 1)
            f[x][1] = exchange(f[x][0], f[y][0] + 1);
        else if (f[x][1] < f[y][0] + 1)
            f[x][1] = f[y][0] + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    iota(fa + 1, fa + 1 + n, 1);

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
        merge(x, y);
    }

    for (int i = 1; i <= n; ++i) {
        if (!vis[i])
            dfs(i, 0);

        len[find(i)] = max(len[find(i)], f[i][0] + f[i][1]);
    }

    for (int i = 1; i <= q; ++i) {
        int op, x, y;
        cin >> op;

        if (op == 1) {
            cin >> x;
            cout << len[find(x)] << endl;
        } else {
            cin >> x >> y;
            x = find(x);
            y = find(y);

            if (x == y)
                continue;

            int lx = len[x], ly = len[y];
            fa[y] = x;
            len[x] = max(max(len[x], len[y]), (lx + 1) / 2 + (ly + 1) / 2 + 1);
        }
    }

    return 0;
}