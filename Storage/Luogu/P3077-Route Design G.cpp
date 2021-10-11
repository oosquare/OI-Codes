#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 40000 + 10;
constexpr int maxr = 100000 + 10;

struct Edge {
    int x, y;

    bool operator<(const Edge &rhs) {
        if (x != rhs.x)
            return x < rhs.x;
        return y < rhs.y;
    }
};

int n, m, r, ans;
Edge graph[maxr];
int w[maxn][2], f[maxn][2];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> r;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i][0];
        f[i][0] = w[i][0];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> w[i][1];
        f[i][1] = w[i][1];
    }
    for (int i = 1; i <= r; ++i)
        cin >> graph[i].x >> graph[i].y;
    sort(graph + 1, graph + 1 + r);
    for (int i = 1; i <= r; ++i) {
        auto [x, y] = graph[i];
        int tmp = f[x][0];
        f[x][0] = max(f[x][0], f[y][1] + w[x][0]);
        f[y][1] = max(f[y][1], tmp + w[y][1]);
    }
    for (int i = 1; i <= max(n, m); ++i)
        ans = max(ans, max(f[i][0], f[i][1]));
    cout << ans << endl;
    return 0;
}