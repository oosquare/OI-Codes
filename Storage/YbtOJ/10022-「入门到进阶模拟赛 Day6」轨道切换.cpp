#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B) ? EOF : *A++;
}

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

struct edge {
    int to, next, weight;
} graph[5000000];
int head[10005], uuid;
int dis[10005], vis[10005];
int n, a, b;

void link(int x, int y, int w) {
    graph[++uuid] = { y, head[x], w };
    head[x] = uuid;
}

bool dijkstra(int s, int e) {
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x]; i; i = graph[i].next) {
            int y = graph[i].to, z = graph[i].weight;
            if (dis[y] > dis[x] + z) {
                dis[y] = dis[x] + z;
                if (vis[y])
                    continue;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
    return dis[e] != 0x3f3f3f3f;
}

int main() {
    freopen("tram.in", "r", stdin);
    freopen("tram.out", "w", stdout);
    n = read();
    a = read();
    b = read();
    for (int i = 1; i <= n; ++i) {
        int k = read();
        for (int j = 1; j <= k; ++j) {
            int x = read();
            link(i, x, j == 1 ? 0 : 1);
        }
    }
    bool res = dijkstra(a, b);
    printf("%d\n", res ? dis[b] : -1);
    return 0;
}
