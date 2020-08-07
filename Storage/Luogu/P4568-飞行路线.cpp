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

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 1e6 + 10;
constexpr int maxk = 15;

struct e {
    int to, next, weight;
};

e edge[maxm * maxk];
int head[maxn * maxk], uuid;
int dis[maxn * maxk], vis[maxn * maxk];
int n, m, k, s, t, ans = 0x3f3f3f3f;

void link(int x, int y, int w) {
    edge[++uuid] = {y, head[x], w};
    head[x] = uuid;
}

void Dijkstra(int s) {
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(-dis[s], s));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x], y, z; y = edge[i].to, z = edge[i].weight, i; i = edge[i].next) {
            if (dis[y] > dis[x] + z) {
                dis[y] = dis[x] + z;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    k = read();
    s = read();
    t = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), z = read();
        link(x, y, z);
        link(y, x, z);
        for (int j = 1; j <= k; ++j) {
            link(n * j + x, n * j + y, z);
            link(n * j + y, n * j + x, z);
            link(n * (j - 1) + x, n * j + y, 0);
            link(n * (j - 1) + y, n * j + x, 0);
        }
    }
    Dijkstra(s);
    for (int i = 0; i <= k; ++i)
        ans = min(ans, dis[n * i + t]);
    writeln(ans);
    return 0;
}