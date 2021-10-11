#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Edge {
    int to, value;
};

int n, m, k;
vector<Edge> tree[maxn];
int f[maxn][maxn][2], tmp[maxn][2];

void link(int x, int y, int v) {
    tree[x].push_back({y, v});
    tree[y].push_back({x, v});
}

void update(int &x, int y) {
    if (x > y)
        x = y;
}

string myToString(int x) {
    if (x == oo)
        return "oo";
    else
        return to_string(x);
}

void dfs(int x, int fa) {
    f[x][0][0] = 0;
    f[x][1][1] = 0;
    for (auto [y, v] : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x);
        for (int i = 0; i <= k; ++i) {
            tmp[i][0] = f[x][i][0];
            tmp[i][1] = f[x][i][1];
            f[x][i][0] = oo;
            f[x][i][1] = oo;
        }
        if (m == 2) {
            for (int i = k; i >= 0; --i) {
                for (int j = 0; j <= i; ++j) {
                    update(f[x][i][0], tmp[i - j][0] + f[y][j][0] + v);
                    if (j >= 1)
                        update(f[x][i][0], tmp[i - j][0] + f[y][j][1]);

                    if (i - j >= 1)
                        update(f[x][i][1], tmp[i - j][1] + f[y][j][0]);
                    if (i - j >= 1 && j >= 1)
                        update(f[x][i][1], tmp[i - j][1] + f[y][j][1] + v);
                }
            }
        } else {
            for (int i = k; i >= 0; --i) {
                for (int j = 0; j <= i; ++j) {
                    update(f[x][i][0], tmp[i - j][0] + f[y][j][0]);
                    if (j >= 1)
                        update(f[x][i][0], tmp[i - j][0] + f[y][j][1]);

                    if (i - j >= 1)
                        update(f[x][i][1], tmp[i - j][1] + f[y][j][0]);
                    if (i - j >= 1 && j >= 1)
                        update(f[x][i][1], tmp[i - j][1] + f[y][j][1] + v);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        link(a, b, c);
    }
    if (k + m > n) {
        cout << -1 << endl;
        return 0;
    }
    memset(f, 0x3f, sizeof(f));
    dfs(1, 0);
    cout << f[1][k][1] << endl;
    return 0;
}