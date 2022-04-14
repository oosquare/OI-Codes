#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

using ll = long long;

constexpr int maxn = 50000 + 10;
constexpr int maxk = 12;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int x, y, l;
};

int n, m, k;
vector<pair<int, ll>> graph[maxn];
Edge edges[maxk + 10];
ll dis[maxk * 2 + 10][maxn], f[maxk * 2 + 10][1 << (maxk + 2)], ans = oo;
bool vis[maxn];
unordered_map<int, int> id;
int tot, rev[2 * maxk + 10];

void link(int x, int y, int l) {
    graph[x].push_back({y, l});
    graph[y].push_back({x, l});
}

void dijkstra(int start, ll dis[]) {
    priority_queue<pair<ll, int>> q;
    fill(dis + 1, dis + 1 + n, oo);
    fill(vis + 1, vis + 1 + n, false);
    dis[start] = 0;
    q.push({0, start});

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
}

int main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    id[1] = ++tot;
    rev[tot] = 1;

    for (int i = 1; i <= k; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
        edges[i] = {x, y, l};

        if (id[x] == 0) {
            id[x] = ++tot;
            rev[tot] = x;
        }

        if (id[y] == 0) {
            id[y] = ++tot;
            rev[tot] = y;
        }
    }

    for (int i = k + 1; i <= m; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l); 
    }

    for (int i = 1; i <= tot; ++i)
        dijkstra(rev[i], dis[i]);

    for (int i = 1; i <= tot; ++i)
        for (int s = 0; s < (1 << k); ++s)
            f[i][s] = oo;

    for (int i = 1; i <= k; ++i) {
        auto [x, y, l] = edges[i];
        f[id[x]][1 << (i - 1)] = dis[id[1]][y] + l;
        f[id[y]][1 << (i - 1)] = dis[id[1]][x] + l;
    }

    for (int s = 0; s < (1 << k); ++s) {
        for (int i = 1; i <= k; ++i) {
            if (!((s >> (i - 1)) & 1))
                continue;

            auto [x, y, l] = edges[i];

            for (int j = 1; j <= k; ++j) {
                if (!((s >> (j - 1)) & 1) || i == j)
                    continue;

                int z = edges[j].x;
                f[id[x]][s] = min(f[id[x]][s], f[id[z]][s ^ (1 << (i - 1))] + dis[id[z]][y] + l);
                f[id[y]][s] = min(f[id[y]][s], f[id[z]][s ^ (1 << (i - 1))] + dis[id[z]][x] + l);
                z = edges[j].y;
                f[id[x]][s] = min(f[id[x]][s], f[id[z]][s ^ (1 << (i - 1))] + dis[id[z]][y] + l);
                f[id[y]][s] = min(f[id[y]][s], f[id[z]][s ^ (1 << (i - 1))] + dis[id[z]][x] + l);
            }
        }
    }

    for (int i = 2; i <= tot; ++i)
        ans = min(ans, f[i][(1 << k) - 1] + dis[i][1]);

    cout << ans << endl;
    return 0;
}
