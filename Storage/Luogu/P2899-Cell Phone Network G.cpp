#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 10000 + 10;

int n;
vector<int> tree[maxn];
int f[maxn][3];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    int d = 0x3f3f3f3f;
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x);
        d = min(d, f[y][1] - min(f[y][0], f[y][1]));
        f[x][0] += min(f[y][0], f[y][1]);
        f[x][1] += min(min(f[y][0], f[y][1]), f[y][2]);
        f[x][2] += min(f[y][0], f[y][1]);
    }
    f[x][0] += d;
    f[x][1] += 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }
    dfs(1, 0);
    cout << min(f[1][0], f[1][1]) << endl;
    return 0;
}