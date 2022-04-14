#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 1000 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

struct edge {
    int to, next;
    ll capacity, weight;
};

edge graph[maxn * maxn];
int uuid = 1, head[maxn], cur[maxn], vis[maxn];
ll sum, dis[maxn];
int n, k, ss, ee, s[maxn], e[maxn], source, sink;

void link(int x, int y, int c, int w) {
    graph[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    graph[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

bool SPFA() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    dis[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        cur[x] = head[x];
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (graph[i].capacity <= 0 || dis[y] <= dis[x] + graph[i].weight)
                continue;
            dis[y] = dis[x] + graph[i].weight;
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != oo;
}

ll DFS(int x, int a, ll &c) {
    if (x == sink)
        return a;
    ll res = 0;
    vis[x] = true;
    for (int &i = cur[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (vis[y] || graph[i].capacity <= 0 || dis[y] != dis[x] + graph[i].weight)
            continue;
        ll f = DFS(y, min(a - res, 1LL * graph[i].capacity), c);
        if (f > 0) {
            c += f * graph[i].weight;
            res += f;
            graph[i].capacity -= f;
            graph[i ^ 1].capacity += f;
            if (res == a)
                break;
        }
        
    }
    if (res == a)
        vis[x] = false;
    return res;
}

pair<ll, ll> Dinic() {
    ll flow = 0, cost = 0;
    while (SPFA())
        DFS(source, 0x3f3f3f3f, cost);
    return make_pair(flow, cost);
}

int main() { 
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("delight.in", "r", stdin);
    freopen("delight.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> k >> ss >> ee;
    for (int i = 1; i <= n; ++i)
        cin >> s[i], sum += s[i];
    for (int i = 1; i <= n; ++i)
        cin >> e[i];
    source = n + 1, sink = n + 3;
    link(n + 1, n + 2, k - ss, 0);
    for (int i = 1; i <= k; ++i)
        link(n + 2, i, 1, s[i] - e[i]);
    link(n + 2, 1, k - ss - ee, 0);
    for (int i = 1; i < n; ++i)
        link(i, i + 1, k - ss - ee, 0);
    for (int i = 1; i <= n - k; ++i)
        link(i, i + k, 1, s[i + k] - e[i + k]);
    for (int i = n - k + 1; i <= n; ++i)
        link(i, n + 3, oo, 0);
    cout << sum - Dinic().second << endl;
    return 0;
}
