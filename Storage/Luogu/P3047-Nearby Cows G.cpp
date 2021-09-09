#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxk = 20 + 5;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int n, k, c[maxn], f[2][maxn][maxk];

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DP1(int x, int fa) {
    for (int i = 0; i <= k; ++i)
        f[0][x][i] = c[x];
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa) continue;
        DP1(y, x);
        for (int j = 1; j <= k; ++j) f[0][x][j] += f[0][y][j - 1];
    }
}

void DP2(int x, int fa) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa) continue;
        for (int j = 1; j <= k; ++j) {
            f[1][y][j] += f[1][x][j - 1] + f[0][x][j - 1];
            if (j >= 2) f[1][y][j] -= f[0][y][j - 2];
        }
        DP2(y, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
        link(y, x);
    }
    for (int i = 1; i <= n; ++i) cin >> c[i];
    DP1(1, 0);
    DP2(1, 0);
    for (int i = 1; i <= n; ++i) cout << f[0][i][k] + f[1][i][k] << endl;
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= k; ++j) {
    //         cout << f[0][i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}