#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr int maxm = 1300 + 10;
constexpr int maxk = 480 + 10;

struct Edge {
    int to, next, t;
};

Edge graph[maxm * 2];
int uuid, head[maxn];
double f[2][maxn][maxk], ans[2];
int n, m, k, c[maxn], h[2][maxn];

void link(int x, int y, int t) {
    graph[++uuid] = {y, head[x], t};
    head[x] = uuid;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("park.in", "r", stdin);
    freopen("park.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i] >> h[0][i] >> h[1][i];
    }
    for (int i = 1; i <= m; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        link(x, y, t);
        link(y, x, t);
    }

    for (int i = k; i >= 0; --i) {
        for (int x = 1; x <= n; ++x) {
            int cnt = 0;
            for (int e = head[x], y; y = graph[e].to, e; e = graph[e].next) {
                if (i + graph[e].t + c[x] + c[y] > k)
                    continue;
                f[0][x][i] += f[0][y][i + graph[e].t + c[x]];
                f[1][x][i] += f[1][y][i + graph[e].t + c[x]];
                ++cnt;
            }
            f[0][x][i] = (cnt != 0 ? f[0][x][i] / cnt : 0) + (i + c[x] <= k) * h[0][x];
            f[1][x][i] = (cnt != 0 ? f[1][x][i] / cnt : 0) + (i + c[x] <= k) * h[1][x];
        }
    }
    for (int i = 1; i <= n; ++i) {
        ans[0] += f[0][i][0] / n;
        ans[1] += f[1][i][0] / n;
    }
    cout << fixed << setprecision(5);
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}
