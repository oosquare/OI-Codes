#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int mod = 1e9 + 7;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int n, k, colored[maxn];
int f[maxn][4];

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DP(int x, int fa) {
    if (colored[x]) {
        f[x][colored[x]] = 1;
    } else {
        f[x][1] = f[x][2] = f[x][3] = 1;
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa) continue;
        DP(y, x);
        for (int j = 1; j <= 3; ++j) {
            if (colored[x] != 0 && colored[x] != j) continue;
            f[x][j] = 1LL * f[x][j] * (f[y][j % 3 + 1] + f[y][(j + 1) % 3 + 1]) % mod;
        }
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
    for (int i = 1; i <= k; ++i) {
        int x, y;
        cin >> x >> y;
        colored[x] = y;
    }
    DP(1, 0);
    if (colored[1]) {
        cout << f[1][colored[1]] << endl;
    } else {
        cout << ((f[1][1] + f[1][2]) % mod + f[1][3]) % mod << endl;
    }
    // for (int i = 1; i <= n; ++i) {
    //     cout << f[i][1] << " " << f[i][2] << " " << f[i][3] << endl;
    // }
    return 0;
}