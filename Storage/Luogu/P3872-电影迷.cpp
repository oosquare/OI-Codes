#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity;
};

e graph[maxn * maxn * 10];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
int n, m, source, sink, sum;

void link(int x, int y, int c) {
    graph[++uuid] = {y, head[x], c};
    head[x] = uuid;
    graph[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    dis[source] = 1;
    q.push(source);
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

int DFS(int x, int a) {
    if (x == sink)
        return a;
    int res = 0;
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

int Dinic() {
    int flow = 0;
    while (BFS())
        flow += DFS(source, oo);
    return flow;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);

    cin >> n >> m;
    source = n + 1, sink = n + 2;
    for (int i = 1; i <= n; ++i) {
        int score;
        cin >> score;
        if (score >= 0) {
            sum += score;
            link(source, i, score);
        } else {
            link(i, sink, -score);
        }
    }
    for (int i = 1; i <= m; ++i) {
        int x, y, d;
        cin >> x >> y >> d;
        link(x, y, d);
    }
    int res = sum - Dinic();
    cout << max(res, 0) << endl;
    return 0;
}