#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 20000 + 10;

int n, s, mx;
vector<pair<int, int>> tree[maxn];
int dis[maxn], f[maxn];

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
}

void dfs(int x, int fa) {
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        if (dis[y] + l > s) {
            f[x] += f[y] + 1;
            dis[x] = max(dis[x], l);    
        } else {
            f[x] += f[y];
            dis[x] = max(dis[x], dis[y] + l);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        int k, a, b;
        cin >> k;

        for (int j = 1; j <= k; ++j) {
            cin >> a >> b;
            link(i, a, b);
            mx = max(mx, b);
        }
    }

    cin >> s;

    if (mx >= s) {
        cout << "No solution." << endl;
        return 0;
    }

    dfs(1, 0);
    cout << f[1] << endl;

    return 0;
}