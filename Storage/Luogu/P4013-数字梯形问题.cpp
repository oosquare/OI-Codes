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

constexpr int maxn = 2000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity, weight;
};

e edge[maxn * 100];
int uuid = 1, head[maxn], dis[maxn], vis[maxn], cur[maxn];
int n, m, num, source, sink, matrix[maxn][maxn], ec[3] = {1, 1, oo}, vc[3] = {1, oo, oo};

int id(int x, int y) {
    return (x - 1) * (n + m - 1) + y;
}

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

bool SPFA() {
    for (int i = 1; i <= sink; ++i)
        dis[i] = -oo, vis[i] = false;
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        cur[x] = head[x];
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y] >= dis[x] + edge[i].weight)
                continue;
            dis[y] = dis[x] + edge[i].weight;
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != -oo;
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

int Dinic() {
    int res = 0;
    while (SPFA())
        DFS(source, oo, res);
    return res;
}

void build(int type) {
    memset(head, 0, sizeof(head));
    uuid = 1;
    for (int i = 1; i <= m; ++i)
        link(source, id(1, i), 1, 0);
    for (int i = 1; i <= m + n - 1; ++i)
        link(id(n, i) + num, sink, oo, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + m - 1; ++j)
            link(id(i, j), id(i, j) + num, vc[type], matrix[i][j]);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m + i - 1; ++j) {
            link(id(i, j) + num, id(i + 1, j), ec[type], 0);
            link(id(i, j) + num, id(i + 1, j + 1), ec[type], 0);
        }
    }
}

int main() {
    using namespace IO;
    m = read(), n = read();
    num = n * (n + m - 1);
    source = num * 2 + 1, sink = num * 2 + 2;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i + m - 1; ++j)
            matrix[i][j] = read();
    for (int i = 0; i < 3; ++i) {
        build(i);
        writeln(Dinic());
    }
    return 0;
}