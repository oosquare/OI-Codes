#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 400000 + 10;
constexpr int maxm = 800000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Edge {
    int to, next, weight;
};

struct Edge2 {
    int x, y, l, a;

    bool operator<(Edge2 rhs) { return a > rhs.a; }
};

Edge graph[maxm * 2], tree[maxm * 2];
Edge2 edges[maxm], redge[maxm];
int uuid, tuuid, head[maxn], thead[maxn * 2], vis[maxn], dis[maxn];
int t, n, m, q, k, s, lastans, fa[maxn * 2], dep[maxn * 2], step[maxn * 2][18];

void link(int x, int y, int w) {
    graph[++uuid] = { y, head[x], w };
    head[x] = uuid;
}

void linkt(int x, int y) {
    tree[++tuuid] = { y, thead[x], 0 };
    thead[x] = tuuid;
}

void Dijkstra(int source) {
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, source));
    memset(dis, 0x3f, sizeof(dis));
    dis[source] = 0;
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (dis[y] <= dis[x] + graph[i].weight)
                continue;
            dis[y] = dis[x] + graph[i].weight;
            q.push(make_pair(-dis[y], y));
        }
    }
    for (int i = 1; i <= n; ++i) redge[i].l = dis[i];
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void DFS(int x, int fa) {
    dep[x] = dep[fa] + 1;
    step[x][0] = fa;
    for (int i = 1; i <= 17; ++i) step[x][i] = step[step[x][i - 1]][i - 1];
    for (int i = thead[x], y; y = tree[i].to, i; i = tree[i].next) {
        DFS(y, x);
        redge[x].l = min(redge[x].l, redge[y].l);
    }
}

int query(int x, int y) {
    for (int i = 17; i >= 0; --i)
        if (dep[x] - (1 << i) > 0 && redge[step[x][i]].a > y)
            x = step[x][i];
    return redge[x].l;
}

void build() {
    int tot = 0, newid = n;
    for (int i = 1; i <= n * 2; ++i) fa[i] = i;
    sort(edges + 1, edges + 1 + m);
    for (int i = 1; i <= m; ++i) {
        int x = edges[i].x, y = edges[i].y;
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            ++newid;
            linkt(newid, fx);
            linkt(newid, fy);
            fa[fx] = newid;
            fa[fy] = newid;
            redge[newid].a = edges[i].a;
            ++tot;
            if (tot == n - 1)
                break;
        }
    }
    DFS(newid, 0);
}

void answer() {
    while (q--) {
        int a1, a2;
        scanf("%d%d", &a1, &a2);
        int x = (k * lastans + a1 - 1) % n + 1, y = (k * lastans + a2) % (s + 1);
        printf("%d\n", lastans = query(x, y));
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("return.in", "r", stdin);
    freopen("return.out", "w", stdout);
#endif
    scanf("%d", &t);
    while (t--) {
        lastans = 0;
        uuid = 0;
        tuuid = 0;
        memset(edges, 0, sizeof(edges));
        memset(redge, 0, sizeof(redge));
        memset(head, 0, sizeof(head));
        memset(thead, 0, sizeof(thead));
        memset(step, 0, sizeof(step));
        memset(vis, 0, sizeof(vis));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d%d", &edges[i].x, &edges[i].y, &edges[i].l, &edges[i].a);
            link(edges[i].x, edges[i].y, edges[i].l);
            link(edges[i].y, edges[i].x, edges[i].l);
        }
        scanf("%d%d%d", &q, &k, &s);
        for (int i = n + 1; i <= n * 2; ++i) redge[i].l = oo;
        Dijkstra(1);
        build();
        answer();
    }
}
