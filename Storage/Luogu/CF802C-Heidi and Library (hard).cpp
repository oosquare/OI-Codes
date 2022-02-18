#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

constexpr int MAXN = 5000 + 10;

struct Edge {
    int to, next, capacity, weight;
};

int n, k, a[MAXN], c[MAXN], pos[MAXN], pre[MAXN];
Edge graph[MAXN * 10];
int tot = 1, head[MAXN], dis[MAXN], vis[MAXN], cur[MAXN], source, sink;

void link(int x, int y, int c, int w) {
    graph[++tot] = { y, head[x], c, w };
    head[x] = tot;
    graph[++tot] = { x, head[y], 0, -w };
    head[y] = tot;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    vis[source] = true;
    cur[source] = head[source];
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (graph[i].capacity <= 0 || dis[y] <= dis[x] + graph[i].weight)
                continue;
            dis[y] = dis[x] + graph[i].weight;
            cur[y] = head[y];
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != 0x3f3f3f3f;
}

int dfs(int x, int a, int & c) {
    if (x == sink)
        return a;
    int res = 0;
    vis[x] = true;
    for (int & i = cur[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (vis[y] || graph[i].capacity <= 0 || dis[y] != dis[x] + graph[i].weight)
            continue;
        int f = dfs(y, min(graph[i].capacity, a - res), c);
        if (f > 0) {
            c += graph[i].weight * f;
            graph[i].capacity -= f;
            graph[i ^ 1].capacity += f;
            res += f;
        }
    }
    if (res == a)
        vis[x] = false;
    return res;
}

pair<int, int> mcmf() {
    int flow = 0, cost = 0;
    while (spfa()) {
        while (true) {
            int t = dfs(source, 0x3f3f3f3f, cost);
            if (t == 0)
                break;
            flow += t;
        }
    }
    return { flow, cost };
}

int main() {
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    
    source = 2 * n + 1;
    sink = 2 * n + 2;

    for (int i = 1; i <= n; ++i) {
        link(source, i, 1, c[a[i]]);
        link(i + n, sink, 1, 0);
        link(i, i + n, 1, 0);
        link(i, i + 1, k - 1, 0);
        
        if (pre[i])
            link(i - 1, pre[i] + n, 1, -c[a[i]]);
    }

    int cost = mcmf().second;
    cout << cost << endl;
    return 0;
}