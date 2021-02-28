#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 500 + 10;

struct e {
    int to, next, capacity;
};

e edge[maxn * maxn];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
int n, p, q, source, sink;

void link(int x, int y, int c) {
    edge[++uuid] = {y, head[x], c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    q.push(source);
    dis[source] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y])
                continue;
            dis[y] = dis[x] + 1;
            q.push(y);
        }
    }
    return dis[sink] != 0;
}

int DFS(int x, int a) {
    if (x == sink)
        return a;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (edge[i].capacity <= 0 || dis[y] != dis[x] + 1)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res));
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            if (res == a)
                break;
        }
    }
    if (res != a)
        dis[x] = 0;
    return res;
}

int Dinic() {
    int res = 0;
    while (BFS())
        res += DFS(source, 0x3f3f3f3f);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &p, &q);
    source = 2 * n + p + q + 1;
    sink = source + 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= p; ++j) {
            int x;
            scanf("%d", &x);
            if (x == 1)
                link(2 * n + j, i, 1);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= q; ++j) {
            int x;
            scanf("%d", &x);
            if (x == 1)
                link(i + n, 2 * n + p + j, 1);
        }
    }
    for (int i = 1; i <= n; ++i)
        link(i, i + n, 1);
    for (int i = 1; i <= p; ++i)
        link(source, 2 * n + i, 1);
    for (int i = 1; i <= q; ++i)
        link(2 * n + p + i, sink, 1);
    printf("%d\n", Dinic());
    return 0;
}