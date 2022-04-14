#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxn = 3000 + 10;

int n, p, q;
vector<int> tree[maxn];
ll f[2][maxn][maxn], g[2][2][maxn], ans1, ans2, ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x, int fa) {
    f[0][x][0] = 1;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs1(y, x);

        for (int i = 0; i <= p - 1; ++i)
            g[0][0][x] += f[0][x][p - i - 1] * f[0][y][i];

        for (int i = 0; i <= q - 1; ++i)
            g[0][1][x] += f[0][x][q - i - 1] * f[0][y][i];
        
        for (int i = 1; i <= n; ++i)
            f[0][x][i] += f[0][y][i - 1];
    }
}

void dfs2(int x, int fa) {
    for (int i = 0; i <= p; ++i)
        g[1][0][x] += f[0][x][i] * f[1][x][p - i];

    for (int i = 0; i <= q; ++i)
        g[1][1][x] += f[0][x][i] * f[1][x][q - i];

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        f[1][y][1] = 1;

        for (int i = 2; i <= n; ++i)
            f[1][y][i] += f[1][x][i - 1] + f[0][x][i - 1] - f[0][y][i - 2];

        dfs2(y, x);
    }
}

int main() {
    freopen("intersection.in", "r", stdin);
    freopen("intersection.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> p >> q;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for (int i = 1; i <= n; ++i)
        ans1 += g[0][0][i];

    for (int i = 1; i <= n; ++i)
        ans2 += g[0][1][i];

    ans = ans1 * ans2;

    for (int i = 1; i <= n; ++i)
        ans -= g[0][0][i] * g[0][1][i] + g[1][0][i] * g[0][1][i] + g[0][0][i] * g[1][1][i];

    cout << ans * 4 << endl;
    return 0;
}
