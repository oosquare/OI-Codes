#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 5e5 + 10;

int n, k;
vector<pair<int, int>> tree[maxn];
bool key[maxn];
int sze[maxn], idx[maxn];
long long f[maxn][2], g[maxn][3];

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void dfs1(int x, int fa) {
    sze[x] = key[x];

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        dfs1(y, x);
        sze[x] += sze[y];
        f[x][0] += (sze[y] ? l + f[y][0] : 0);

        if (sze[y]) {
            if (g[x][0] <= g[y][0] + l) {
                g[x][1] = g[x][0];
                g[x][0] = g[y][0] + l;
                idx[x] = y;
            } else if (g[x][1] < g[y][0] + l) {
                g[x][1] = g[y][0] + l;
            }

        }
    }
}

void dfs2(int x, int fa) {
    if (fa == 0)
        f[x][1] = f[x][0];

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        f[y][1] = f[y][0] + f[x][1] - (sze[y] ? l + f[y][0] : 0) + (k - sze[y] ? l : 0);

        if (k - sze[y]) {
            if (idx[x] != y)
                g[y][2] = max(g[x][0], g[x][2]) + l;
            else
                g[y][2] = max(g[x][1], g[x][2]) + l;
        }
        
        dfs2(y, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i < n; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }

    for (int i = 1; i <= k; ++i) {
        int x;
        cin >> x;
        key[x] = true;
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for (int i = 1; i <= n; ++i)
        cout << 2 * f[i][1] - max(g[i][0], g[i][2]) << endl;

    return 0;
}