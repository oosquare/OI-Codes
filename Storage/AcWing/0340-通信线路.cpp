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

constexpr int maxn = 1000000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, weight;
};

e edge[maxn * 4];
int uuid = 1, head[maxn], dis[maxn], vis[maxn];
int n, p, k;

void link(int x, int y, int z) {
    edge[++uuid] = {y, head[x], z};
    head[x] = uuid;
}

void Dijkstra() {
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    q.push(make_pair(dis[1], 1));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = false;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (dis[y] <= max(dis[x], edge[i].weight))
                continue;
            dis[y] = max(dis[x], edge[i].weight);
            q.push(make_pair(-dis[y], y));
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), p = read(), k = read();
    for (int i = 1; i <= p; ++i) {
        int x = read(), y = read(), z = read();
        link(x, y, z);
        link(y, x, z);
        for (int j = 1; j <= k; ++j) {
            link(x + j * n, y + j * n, z);
            link(y + j * n, x + j * n, z);
            link(x + (j - 1) * n, y + j * n, 0);
            link(y + (j - 1) * n, x + j * n, 0);
        }
    }
    Dijkstra();
    int ans = oo;
    for (int i = 0; i <= k; ++i)
        ans = min(ans, dis[n + i * n]);
    writeln(ans != oo ? ans : -1);
    return 0;
}