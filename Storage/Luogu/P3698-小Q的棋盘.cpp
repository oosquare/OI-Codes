#include <bits/stdc++.h>
using namespace std;

constexpr int maxv = 100 + 10;
constexpr int maxn = 100 + 10;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int v, n, f[maxv][maxn][2];

void update(int &x, int y) {
    if (x < y) x = y;
}

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void Dp(int x, int fa) {
    f[x][0][0] = f[x][0][1] = 1;
    for (int e = head[x], y; y = tree[e].to, e; e = tree[e].next) {
        if (y == fa) continue;
        Dp(y, x);
        for (int i = n; i >= 1; --i) {
            for (int j = i - 1; j >= 0; --j) {
                update(f[x][i][1], f[x][i - 1 - j][0] + f[y][j][1]);
                if (i - 2 - j >= 0) {
                    update(f[x][i][1], f[x][i - 2 - j][1] + f[y][j][0]);
                    update(f[x][i][0], f[x][i - 2 - j][0] + f[y][j][0]);
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        update(f[x][i][0], f[x][i - 1][0]);
        update(f[x][i][1], f[x][i - 1][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> v >> n;
    for (int i = 1; i < v; ++i) {
        int a, b;
        cin >> a >> b;
        ++a;
        ++b;
        link(a, b);
        link(b, a);
    }
    Dp(1, 0);
    cout << max(f[1][n][0], f[1][n][1]) << endl;
    // for (int i = 1; i <= v; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= n; ++j) {
    //         cout << "(" << f[i][j][0] << " " << f[i][j][1] << ") ";
    //     }
    //     cout << endl;
    // }
    return 0;
}