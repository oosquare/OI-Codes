#include <bits/stdc++.h>
using namespace std;

const int maxn = 20000 + 10;
const int maxm = 200000 + 10;

struct e {
    int to, next, capacity;
};

e edge[maxm * 10];
int uuid = 1, head[maxn * 10], cur[maxn * 10], dis[maxn * 10];
int n, m, source, sink;

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
    cur[source] = head[source];
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y])
                continue;
            dis[y] = dis[x] + 1;
            cur[y] = head[y];
            q.push(y);
        }
    }
    return dis[sink];
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
    scanf("%d%d", &n, &m);
    source = n + 1;
    sink = n + 2;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        link(source, i, a);
        link(i, sink, b);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        link(a, b, w);
        link(b, a, w);
    }
    printf("%d\n", Dinic());
    return 0;
}