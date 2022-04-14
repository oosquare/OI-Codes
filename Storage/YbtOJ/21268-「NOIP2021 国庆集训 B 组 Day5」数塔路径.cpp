#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;

int tower[maxn][maxn];
int f[maxn][maxn], g[maxn][maxn];
int ans[maxn][2], pos[maxn];
int n, m;

int calc(int i, int j) {
    return f[i][j] + g[i][j] - tower[i][j];
}

int main() {
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> tower[i][j];
            f[i][j] = g[i][j] = tower[i][j];
        }
    }
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] += max(f[i + 1][j], f[i + 1][j + 1]);
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            g[i][j] += max((j != 1 ? g[i - 1][j - 1] : 0), (j != i ? g[i - 1][j] : 0));
        }
    }
    // ans[1][0] = g[1][1], ans[1][1] = 0, pos[1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (calc(i, j) >= ans[i][0]) {
                ans[i][1] = ans[i][0];
                ans[i][0] = calc(i, j);
                pos[i] = j;
            } else if (calc(i, j) >= ans[i][1]) {
                ans[i][1] = calc(i, j);
            }
        }
    }
    while (m--) {
        int x, y;
        cin >> x >> y;
        if (x == 1) {
            cout << -1 << endl;
        } else {
            cout << (pos[x] != y ? ans[x][0] : ans[x][1]) << endl;
        }
    }
    return 0;
}
