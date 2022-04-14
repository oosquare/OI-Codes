#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity;
};

e edge[maxn * maxn];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
int n, m, source, sink, sum;

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
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    source = 2 * n + 1, sink = 2 * n + 2;
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        if (a >= 0) {
            link(source, i, a);
            link(i, i + n, 0);
            link(i + n, sink, a);
            sum += a;
        } else {
            link(source, i, 0);
            link(i, i + n, -a);
            link(i + n, sink, 0);
        }
    }
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y, oo);
        link(x + n, y + n, oo);
    }
    cout << sum - Dinic() << endl;
    return 0;
}
