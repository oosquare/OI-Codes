#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;

constexpr int maxp = 100000 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

int c, p, pb, pa1, pa2;
vector<pair<int, ll>> graph[maxp];
ll dis[3][maxp];
bool vis[maxp];

void link(int x, int y, ll l) {
    graph[x].push_back({y, l});
    graph[y].push_back({x, l});
} 

void dijkstra(int start, ll dis[]) {
    priority_queue<pair<ll, int>> q;
    fill(dis + 1, dis + 1 + p, oo);
    fill(vis + 1, vis + 1 + p, false);
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
    ios::sync_with_stdio(false);
    cin >> c >> p >> pb >> pa1 >> pa2;

    for (int i = 1; i <= c; ++i) {
        int x, y;
        ll l;
        cin >> x >> y >> l;
        link(x, y, l);
    }

    dijkstra(pb, dis[0]);
    dijkstra(pa1, dis[1]);
    dijkstra(pa2, dis[2]);
    cout << min(dis[0][pa1] + dis[1][pa2], dis[0][pa2] + dis[2][pa1]) << endl;
    return 0;
}