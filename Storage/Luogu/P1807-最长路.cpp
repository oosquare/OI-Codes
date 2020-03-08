#include <bits/stdc++.h>
using namespace std;

struct e {
    int to, next, weight;
};

constexpr int maxn = 1500 + 5;
constexpr int maxm = 50000 + 5;
e edge[maxm];
int uuid, n, m, head[maxn], dis[maxn], vis[maxn];

void SPFA() {
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        dis[i] = -0x3f3f3f3f;
    q.push(1);
    vis[1] = 1;
    dis[1] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (dis[x] + edge[i].weight > dis[y]) {
                dis[y] = dis[x] + edge[i].weight;
                if (vis[y])
                    continue;
                vis[y] = 1;
                q.push(y);
            }
        }
    }
}

inline void link(int x, int y, int w) {
    edge[++uuid] = {y, head[x], w}; head[x] = uuid;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        link(x, y, w);
    }
    SPFA();
    printf("%d\n", dis[n] == -0x3f3f3f3f ? -1 : dis[n]);
    return 0;
}