#include <bits/stdc++.h>
using namespace std;

struct e {
    int to, next, weight;
};

constexpr int maxn = 5e6 + 10;
constexpr int maxm = 5e6 + 10;
e edge[maxn];
int uuid, n, m, head[maxn], in[maxn], dis[maxn], vis[maxn];

bool SPFA() {
    memset(dis, -0x3f, sizeof(dis));
    queue<int> q;
    q.push(n + 1);
    vis[n + 1] = 1;
    dis[n + 1] = 0;
    in[n + 1] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (dis[y] < dis[x] + edge[i].weight) {
                dis[y] = dis[x] + edge[i].weight;
                if (vis[y])
                    continue;
                q.push(y);
                vis[y] = 1;
                ++in[y];
                if (in[y] > n + 1)
                    return false;
            }
        }
    }
    return true;
}

inline void link(int x, int y, int w) {
    edge[++uuid] = {y, head[x], w};
    head[x] = uuid;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        link(n + 1, i, 0);
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        link(y, x, w);
    }
    bool res = SPFA();
    if (res) {
        for (int i = 1; i <= n; ++i)
            printf("%d ",dis[i]);
        printf("\n");
    } else {
        printf("NO\n");
    }
    return 0;
}