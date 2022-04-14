#include <iostream>
#include <iterator>
#include <vector>
#include <ext/pb_ds/priority_queue.hpp>
#include <algorithm>

constexpr int MAX_N = 3000 + 5;

int n, m, k;
std::vector<std::pair<int, int>> graph[MAX_N];
long long dis[MAX_N];
bool vis[MAX_N];
int len[MAX_N];
long long ans[MAX_N];

void link(int x, int y, int w) {
    graph[x].push_back({ y, w });
    graph[y].push_back({ x, w });
}

long long dijkstra(int delta) {
    __gnu_pbds::priority_queue<std::pair<long long, int>> q;

    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        dis[i] = 0x3f3f3f3f3f3f3f3f;
    }

    dis[1] = 0;
    q.push({ 0, 1 });

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x])
            continue;

        vis[x] = true;
        
        for (auto [y, w] : graph[x]) {
            if (dis[y] <= dis[x] + std::max(0, w - delta))
                continue;

            dis[y] = dis[x] + std::max(0, w - delta);
            q.push({ -dis[y], y });
        }
    }

    return dis[n];
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("journey.in", "r", stdin);
    std::freopen("journey.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        len[i] = w;
        link(x, y, w);
    }

    std::sort(len + 1, len + 1 + m);
    m = (int) (std::unique(len + 1, len + 1 + m) - len - 1);
    dijkstra(0);

    for (int i = 1; i <= n; ++i)
        ans[i] = dis[n];

    for (int i = 1; i <= m; ++i) {
        auto res = dijkstra(len[i]);

        for (int j = 1; j <= n; ++j)
            ans[j] = std::min(ans[j], res + 1ll * len[i] * j);
    }

    for (int i = n; i >= 1; --i)
        std::cout << ans[i] << std::endl;

    return 0;
}
