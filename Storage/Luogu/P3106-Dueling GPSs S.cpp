#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 10000 + 10;

struct Edge {
    int to, length[2];
};

int n, m;
vector<Edge> graph[maxn], rgraph[maxn];
int dis[maxn], vis[maxn], pre[2][maxn];

void link(int x, int y, int p, int q) {
    rgraph[x].push_back({y, {p, q}});
}

void link(int x, int y, int l) {
    graph[x].push_back({y, {l, 0}});
}

void dijkstra(int id, int start) {
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(dis));
    dis[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x] == true)
            continue;
        vis[x] = true;
        for (auto e : rgraph[x]) {
            int y = e.to, l = e.length[id];
            if (dis[y] <= dis[x] + l)
                continue;
            dis[y] = dis[x] + l;
            pre[id][y] = x;
            q.push({-dis[y], y});
        }
    }
}

void dijkstra(int start) {
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(dis));
    dis[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x] == true)
            continue;
        vis[x] = true;
        for (auto e : graph[x]) {
            int y = e.to, l = e.length[0];
            if (dis[y] <= dis[x] + l)
                continue;
            dis[y] = dis[x] + l;
            q.push({-dis[y], y});
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        link(y, x, p, q);
    }
    dijkstra(0, n);
    dijkstra(1, n);
    for (int x = 1; x <= n; ++x) {
        for (auto e : rgraph[x]) {
            int y = e.to;
            link(y, x, (pre[0][y] == x ? 0 : 1) + (pre[1][y] == x ? 0 : 1));
        }
    }
    dijkstra(1);
    cout << dis[n] << endl;
    return 0;
}