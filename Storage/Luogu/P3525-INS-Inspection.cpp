#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000000 + 10;

int n;
vector<int> tree[maxn];
int sze[maxn][2], sum[maxn][2], dis[maxn][4], idx[maxn], son[maxn], f[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x, int fa) {
    f[x] = fa;
    sze[x][0] = 1;
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        dfs1(y, x);
        sze[x][0] += sze[y][0];
        if (sze[x][1] < sze[y][0]) {
            sze[x][1] = sze[y][0];
            son[x] = y;
        }
        sze[x][1] = max(sze[x][1], sze[y][0]);
        sum[x][0] += sum[y][0] + 2 * sze[y][0];
        if (dis[x][0] < dis[y][0] + 1) {
            dis[x][1] = exchange(dis[x][0], dis[y][0] + 1);
            idx[x] = y;
        } else if (dis[x][1] < dis[y][0] + 1) {
            dis[x][1] = dis[y][0] + 1;
        }
    }
}

void dfs2(int x, int fa) {
    if (fa == 0) {
        sum[x][1] = sum[x][0];
        dis[x][2] = 0;
    }
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        if (sze[y][1] < n - sze[y][0]) {
            sze[y][1] = n - sze[y][0];
            son[y] = x;
        }
        sum[y][1] = sum[y][0] + (sum[x][1] - sum[y][0] - 2 * sze[y][0]) + 2 * (n - sze[y][0]);
        if (idx[x] == y)
            dis[y][2] = max(dis[x][1] + 1, dis[x][2] + 1);
        else
            dis[y][2] = max(dis[x][0] + 1, dis[x][2] + 1);
        dfs2(y, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int x = 1; x <= n; ++x) {
        int y = son[x], s = sze[x][1];
        if (s > n / 2) {
            cout << -1 << endl;
            continue;
        }
        int d;
        if (s * 2 == n) {
            if (f[y] == x)
                d = dis[y][0] + 1;
            else
                d = dis[x][2];
        } else {
            d = max(dis[x][0], dis[x][2]);
        }
        cout << sum[x][1] - d << endl;
    }
    return 0;
}