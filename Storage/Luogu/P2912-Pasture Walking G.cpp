#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;

int n, q;
vector<pair<int, int>> tree[maxn];
int dep[maxn], step[maxn][11], dis[maxn];

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void preprocess(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 1; i <= 10; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;
        step[y][0] = x;
        dis[y] = dis[x] + l;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 10; i >= 0; --i) {
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];
        if (x == y)
            return x;
    }
    for (int i = 10; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }
    return step[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }
    preprocess(1, 0);
    for (int i = 1; i <= q; ++i) {
        int x, y;
        cin >> x >> y;
        int l = lca(x, y);
        cout << dis[x] + dis[y] - 2 * dis[l] << endl;
    }
    return 0;
}