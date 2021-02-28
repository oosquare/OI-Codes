#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 6000 + 10;
constexpr int maxc = 100000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity;
};

e edge[maxc];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
bool notdes[maxn] = {true};
int p, n, c, source, sink;

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
        res += DFS(source, oo);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d%d", &p, &c, &n);
    source = 2 * p + 1, sink = 1;
    for (int i = 1; i <= c; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        link(x + p, y, oo);
        link(y + p, x, oo);
    }
    memset(notdes, true, sizeof(notdes));
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        notdes[x] = false;
    }
    for (int i = 1; i <= p; ++i) {
        link(i, i + p, notdes[i] ? 1 : oo);
        if (!notdes[i])
            link(source, i, oo);
    }
    printf("%d\n", Dinic());
    return 0;
}