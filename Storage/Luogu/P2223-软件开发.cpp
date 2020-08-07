#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity, weight;
};

e edge[maxn * maxn];
int uuid = 1, head[maxn * 4], dis[maxn * 4], vis[maxn * 4], cur[maxn * 4];
int n, a, b, fa, fb, f, source, sink;

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

bool SPFA() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        cur[x] = head[x];
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y] <= dis[x] + edge[i].weight)
                continue;
            dis[y] = dis[x] + edge[i].weight;
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != oo;
}

int DFS(int x, int a, int &c) {
    if (x == sink)
        return a;
    vis[x] = true;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y] || edge[i].capacity <= 0 || dis[y] != dis[x] + edge[i].weight)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res), c);
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            c += f * edge[i].weight;
            if (res == a)
                break;
        }
    }
    if (res == a)
        vis[x] = false;
    return res; 
}

int Dinic() {
    int cost = 0;
    while (SPFA())
        DFS(source, oo, cost);
    return cost;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d%d%d%d%d", &n, &a, &b, &f, &fa, &fb);
    source = n * 2 + 1;
    sink = n * 2 + 2;
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        link(source, i + n, x, 0);
        link(i, sink, x, 0);
        link(source, i, oo, f);
        // link(i, i + n, x, 0);
        if (i + a + 1 <= n)
            link(i + n, i + a + 1, oo, fa);
        if (i + b + 1 <= n)
            link(i + n, i + b + 1, oo, fb);
        if (i + 1 <= n)
            link(i, i + 1, oo, 0);
    }
    printf("%d\n", Dinic());
    return 0;
}