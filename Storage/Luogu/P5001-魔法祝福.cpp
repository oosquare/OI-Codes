#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 1e6 + 10;

struct e {
    int to, next, limit;
    ll weight;
};

e edge[maxn * 2];
int head[maxn], uuid;
int n, m, p, q;
ll dis[maxn], step[maxn];
bool vis[maxn];
priority_queue<pair<int, int>> que;

void link(int x, int y, int w, int l) {
    edge[++uuid] = {y, head[x], l, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], l, w};
    head[y] = uuid;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &p, &q);
    for (int i = 1; i <= m; ++i) {
        int x, y, t, k;
        scanf("%d%d%d%d", &x, &y, &t, &k);
        link(x, y, t, k);
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[p] = 0;
    vis[p] = true;
    que.push(make_pair(0, p));
    while (!que.empty()) {
        int x = que.top().second;
        que.pop();
        vis[x] = 0;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (step[x] >= edge[i].limit)
                continue;
            if (dis[y] > dis[x] + edge[i].weight || (dis[y] == dis[x] + edge[i].weight && step[x] + 1 < step[y])) {
                if (dis[y] > dis[x] + edge[i].weight) {
                    dis[y] = dis[x] + edge[i].weight;
                    step[y] = step[x] + 1;
                }
                if (vis[y])
                    continue;
                vis[y] = true;
                que.push(make_pair(-dis[y], y));
            }
        }
    }
    if (dis[q] == 0x3f3f3f3f3f3f3f3fLL)
        printf("bao 0\n");
    else
        printf("%lld\n", dis[q]);
    return 0;
}