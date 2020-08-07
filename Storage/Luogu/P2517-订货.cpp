#include <bits/stdc++.h>
using namespace std;

namespace IO {
    
inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
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

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 60;

struct e {
    int to, next, capacity, weight;
};

e edge[maxn * maxn];
int uuid = 1, head[maxn], dis[maxn], vis[maxn], cur[maxn];
int n, m, s, source, sink;

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

bool SPFA() {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    queue<int> q;
    dis[source] = 0;
    vis[source] = true;
    cur[source] = head[source];
    q.push(source);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y] <= dis[x] + edge[i].weight)
                continue;
            dis[y] = dis[x] + edge[i].weight;
            cur[y] = head[y];
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != 0x3f3f3f3f;
}

int DFS(int x, int a, int &c) {
    if (x == sink)
        return a;
    vis[x] = true;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y] || edge[i].capacity <= 0 || dis[y] != dis[x] + edge[i].weight)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res), c);
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            c += edge[i].weight * f;
            if (res == a)
                break;
        }
    }
    if (res == a)
        vis[x] = false;
    return res;
}

pair<int, int> Dinic() {
    int flow = 0, cost = 0;
    while (SPFA())
        flow += DFS(source, 0x3f3f3f3f, cost);
    return make_pair(flow, cost);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    s = read();
    source = n + 1, sink = n + 2;
    for (int i = 1; i <= n; ++i) {
        int u = read();
        link(i, sink, u, 0);
    }
    for (int i = 1; i <= n; ++i) {
        int d = read();
        link(source, i, 0x3f3f3f3f, d);
    }
    for (int i = 1; i < n; ++i) {
        link(i, i + 1, s, m);
    }
    auto res = Dinic();
    writeln(res.second);
    return 0;
}