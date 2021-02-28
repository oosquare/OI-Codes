#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 400 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3fLL;

struct e {
    int to, next;
    ll capacity;
};

e edge[maxn * maxn * 10];
int uuid = 1, head[maxn], vis[maxn], cur[maxn];
ll s[maxn], p[maxn], eg[maxn][3], dis[maxn][maxn];
int n, m, source, sink;
ll sum, rleft, rright, ans = -1;

void link(int x, int y, ll c) {
    edge[++uuid] = {y, head[x], c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    vis[source] = 1;
    q.push(source);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || vis[y])
                continue;
            vis[y] = vis[x] + 1;
            q.push(y);
        }
    }
    return vis[sink] != 0;
}

ll DFS(int x, ll a) {
    if (x == sink)
        return a;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (edge[i].capacity <= 0 || vis[y] != vis[x] + 1)
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
        vis[x] = 0;
    return res;
}

ll Dinic() {
    ll res = 0;
    while (BFS())
        res += DFS(source, oo);
    return res;
}

void Floyd() {
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

void build(ll x) {
    memset(head, 0, sizeof(head));
    uuid = 1;
    for (int i = 1; i <= n; ++i) {
        link(source, i, s[i]);
        link(i + n, sink, p[i]);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (dis[i][j] <= x)
                link(i, j + n, oo);
}

bool check(ll x) {
    build(x);
    return Dinic() == sum;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    source = 2 * n + 1, sink = 2 * n + 2;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &s[i], &p[i]);
        sum += s[i];
    }
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 0; i <= n; ++i)
        dis[i][i] = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        ll z;
        scanf("%d%d%lld", &x, &y, &z);
        dis[x][y] = dis[y][x] = min(dis[x][y], z);
    }
    Floyd();
    rleft = oo, rright = -oo;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dis[i][j] >= oo)
                continue;
            rleft = min(rleft, dis[i][j]);
            rright = max(rright, dis[i][j]);
        }
    }
    while (rleft <= rright) {
        ll mid = (rleft + rright) / 2;
        if (check(mid)) {
            ans = mid;
            rright = mid - 1;
        } else {
            rleft = mid + 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}