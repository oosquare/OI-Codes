#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

int read() {
    int x = 0, s = 1;
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

struct e {
    int to, weight, next;
};

e edge[4000];
int head[1005], uuid;
int dis[1005], vis[1005];
int t, n;

void link(int x, int y, int w) {
    edge[++uuid] = {y, w, head[x]};
    head[x] = uuid;
    edge[++uuid] = {x, w, head[y]};
    head[y] = uuid;
}

int dijkstra(int s, int e) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x], y, w; y = edge[i].to, w = edge[i].weight, i; i = edge[i].next) {
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
                if (vis[y])
                    continue;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
    return dis[e];
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    t = read();
    n = read();
    for (int i = 1; i <= t; ++i) {
        int x = read(), y = read(), w = read();
        link(x, y, w);
    }
    printf("%d\n", dijkstra(n, 1));
    return 0;
}