#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, m, k, ans = oo;
vector<pair<int, int>> graph[maxn];
int key[maxn];
int dis[maxn];
bool vis[maxn];

void link(int x, int y, int z) {
    graph[x].push_back({y, z});
}

int dijkstra(int p, int t) {
    int res = oo;
    priority_queue<pair<int, int>> q;
    fill(vis + 1, vis + 1 + n, false);
    fill(dis + 1, dis + 1 + n, oo);

    for (int i = 0; i < k; ++i) {
        if (((i >> p) & 1) == t) {
            dis[key[i]] = 0;
            q.push({0, key[i]});
        }
    }

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x])
            continue;

        vis[x] = true;

        for (auto [y, l] : graph[x]) {
            if (dis[y] <= dis[x] + l)
                continue;

            dis[y] = dis[x] + l;
            q.push({-dis[y], y});
        }
    }

    for (int i = 0; i < k; ++i)
        if (((i >> p) & 1) != t)
            res = min(res, dis[key[i]]);

    return res;
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        link(x, y, z);
    }

    for (int i = 0; i < k; ++i)
        cin >> key[i];

    for (int i = 0; i < 17; ++i) {
        ans = min(ans, dijkstra(i, 0));
        ans = min(ans, dijkstra(i, 1));
    }

    cout << ans << endl;
    return 0;
}
