#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

constexpr int maxn = 5000 + 10;
constexpr int mod = 1e9 + 7;
constexpr int oo = 0x3f3f3f3f;

int n, m, ans[maxn];
int from[maxn], to[maxn], len[maxn];
vector<pair<int, int>> graph[maxn];
vector<int> graph2[maxn];
int dis[maxn], vis[maxn], cnt[2][maxn], in[maxn], ins[maxn], timer;

void link(int x, int y, int z) {
    graph[x].push_back({y, z});
}

void link(int x, int y) {
    graph2[x].push_back(y);
    ++in[y];
}

void dijkstra(int start) {
    priority_queue<pair<int, int>> q;

    for (int i = 1; i <= n; ++i)
        dis[i] = oo;

    dis[start] = 0;
    q.push({0, start});

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x] == timer)
            continue;

        vis[x] = timer;

        for (auto [y, l] : graph[x]) {
            if (dis[y] <= dis[x] + l)
                continue;

            dis[y] = dis[x] + l;
            q.push({-dis[y], y});
        }
    }
}

void topo(int start) {
    queue<int> q;
    stack<int> s;

    for (int x = 1; x <= n; ++x) {
        graph2[x].clear();
        in[x] = 0;
        cnt[0][x] = cnt[1][x] = 0;
    }

    cnt[0][start] = 1;

    for (int i = 1; i <= m; ++i) {
        int x = from[i], y = to[i], z = len[i];

        if (dis[x] + z == dis[y]) {
            link(x, y);
            ins[i] = timer;
        }
    }

    for (int x = 1; x <= n; ++x)
        if (!in[x])
            q.push(x);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        s.push(x);

        for (int y : graph2[x]) {
            cnt[0][y] = (cnt[0][y] + cnt[0][x]) % mod;
            --in[y];

            if (!in[y])
                q.push(y);
        }
    }

    while (!s.empty()) {
        int x = s.top();
        s.pop();
        cnt[1][x] = 1;

        for (int y : graph2[x])
            cnt[1][x] = (cnt[1][x] + cnt[1][y]) % mod;
    }
}

void calc(int start) {
    ++timer;
    dijkstra(start);
    topo(start);

    for (int i = 1; i <= m; ++i)
        if (ins[i] == timer)
            ans[i] = (ans[i] + 1ll * cnt[0][from[i]] * cnt[1][to[i]] % mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        from[i] = x;
        to[i] = y;
        len[i] = z;
        link(x, y, z);
    }

    for (int i = 1; i <= n; ++i)
        calc(i);

    for (int i = 1; i <= m; ++i)
        cout << ans[i] << endl;

    return 0;
}