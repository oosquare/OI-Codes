#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300000 + 10;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn], deg[maxn];
bool vis[maxn];
int n, m, res, ans, f[maxn][2];

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
    ++deg[y];
}

void Dp(int x, int fa) {
    if (deg[x] == 1 && x != 1) {
        f[x][0] = 1;
        return;
    }
    vis[x] = true;
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa) continue;
        Dp(y, x);
        if (f[x][0] <= f[y][0] + max(deg[y], 2) - 1) {
            f[x][1] = f[x][0];
            f[x][0] = f[y][0] + max(deg[y], 2) - 1;
        } else if (f[x][1] < f[y][0] + max(deg[y], 2) - 1) {
            f[x][1] = f[y][0] + max(deg[y], 2) - 1;
        }
    }
    int res = f[x][0] + f[x][1] - 1 + deg[x] - 2;
    if (f[x][0] == 0) res += 2;
    if (f[x][1] == 0) res += 2;
    ans = max(ans, res);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        link(a, b);
        link(b, a);
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            Dp(i, 0);
        }
    }
    cout << ans << endl;
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : " << deg[i] << " " << f[i][0] << " " << f[i][1] << endl;
    // }
    return 0;
}