#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 40000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity;
};

e edge[maxn * 20];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
int n1, n2, n3, m1, source, sink;

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
            q.push(y);
            dis[y] = dis[x] + 1;
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
            if (a == res)
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

int id(int t, int x) {
    if (t == 1)
        return x;
    if (t == 2)
        return x + n2;
    if (t == 3)
        return x + n2 + n1;
    if (t == 4)
        return x + n2 + 2 * n1;
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d%d", &n1, &n2, &n3);
    int m;
    for (scanf("%d", &m); m--;) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(id(1, v), id(2, u), 1);
    }
    for (scanf("%d", &m); m--;) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(id(3, u), id(4, v), 1);
    }
    for (int i = 1; i <= n1; ++i)
        link(id(2, i), id(3, i), 1);
    source = 0, sink = n2 + n1 + n1 + n3 + 1;
    for (int i = 1; i <= n2; ++i)
        link(source, id(1, i), 1);
    for (int i = 1; i <= n3; ++i)
        link(id(4, i), sink, 1);
    printf("%d\n", Dinic());
    return 0;
}