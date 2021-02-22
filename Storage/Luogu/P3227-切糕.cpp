#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxl = 40 + 5;
constexpr int maxn = 40 * 40 * 42 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

struct edge {
    int to, next;
    ll capacity;
};

edge graph[maxn * 100];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
int p, q, r, d, source, sink, tot;
int v[maxl][maxl][maxl], id[maxl][maxl][maxl];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool vaild(int x, int y) { return 1 <= x && x <= p && 1 <= y && y <= q; }

void link(int x, int y, ll c) {
    graph[++uuid] = {y, head[x], c};
    head[x] = uuid;
    graph[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
    queue<int> q;
    for (int i = 1; i <= tot; ++i)
        dis[i] = 0;
    q.push(source);
    dis[source] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (graph[i].capacity <= 0 || dis[y])
                continue;
            dis[y] = dis[x] + 1;
            q.push(y);
        }
    }
    return dis[sink] != 0;
}

ll DFS(int x, ll a) {
    if (x == sink)
        return a;
    ll res = 0;
    for (int &i = cur[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (graph[i].capacity <= 0 || dis[y] != dis[x] + 1)
            continue;
        int f = DFS(y, min(graph[i].capacity, a - res));
        if (f > 0) {
            graph[i].capacity -= f;
            graph[i ^ 1].capacity += f;
            res += f;
            if (res == a)
                break;
        }
    }
    if (res != a)
        dis[x] = 0;
    return res;
}

ll Dinic() {
    ll f = 0;
    while (BFS())
        f += DFS(source, oo);
    return f;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> p >> q >> r >> d;
    source = ++tot, sink = ++tot;
    for (int k = 1; k <= r; ++k)
        for (int i = 1; i <= p; ++i)
            for (int j = 1; j <= q; ++j)
                cin >> v[i][j][k], id[i][j][k] = ++tot;
    for (int i = 1; i <= p; ++i)
            for (int j = 1; j <= q; ++j)
                id[i][j][r + 1] = ++tot;
    for (int i = 1; i <= p; ++i) {
        for (int j = 1; j <= q; ++j) {
            link(source, id[i][j][1], oo);
            for (int k = 1; k <= r; ++k)
                link(id[i][j][k], id[i][j][k + 1], v[i][j][k]);
            for (int k = d + 1; k <= r + 1; ++k) {
                for (int l = 0; l < 4; ++l) {
                    int ni = i + dir[l][0], nj = j + dir[l][1];
                    if (!vaild(ni, nj))
                        continue;
                    link(id[i][j][k], id[ni][nj][k - d], oo);
                }
            }
            link(id[i][j][r + 1], sink, oo);
        }
    }
    cout << Dinic() << endl;
    return 0;
}