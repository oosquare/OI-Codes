#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const int N = 501;
const int M = 10001;
const double EPS = 1e-3;
const double INF = 1e10;

struct edge {
    int v, nxt, w;
};

int dis[N] = { 0 };
int vis[N] = { 0 };
int head[N];
edge e[M];
int tot = 1;
bool pc;
int n, m, w;
bool found;

inline void add(int u, int v, int w) {
    e[tot].v = v;
    e[tot].nxt = head[u];
    e[tot].w = w;
    head[u] = tot++;
}

inline void spfadfs(int u) {
    vis[u] = true;
    for (register int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (dis[u] + e[i].w < dis[v]) {
            dis[v] = dis[u] + e[i].w;
            if (!vis[v]) {
                spfadfs(v);
            } else {
                if (dis[v] < 0) {
                    found = true;
                    return;
                }
            }
        }
    }
    vis[u] = false;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        found = false;
        tot = 1;
        memset(vis, 0, sizeof(vis));
        memset(dis, 0, sizeof(dis));
        memset(head, 0, sizeof(head));
        memset(e, 0, sizeof(e));
        scanf("%d%d%d", &n, &m, &w);
        for (register int i = 0; i < m; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
            add(b, a, c);
        }
        for (register int i = 0; i < w; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, -c);
        }
        for (register int i = 1; i <= n && !found; i++) {
            spfadfs(i);
        }
        if (found) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}