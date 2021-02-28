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

typedef long long ll;

constexpr int maxn = 100000 + 10;
constexpr int maxm = 500000 + 10;
constexpr int maxk = 20 + 10;

struct e {
    int to, next, weight;
};

e edge[maxm * maxk * 2];
int uuid, head[maxn * maxk];
int n, m, k, ans = 0x3f3f3f3f;
int dis[maxn * maxk * 2], vis[maxn * maxk];
priority_queue<pair<int, int>> q;

void link(int x, int y, int w) {
    edge[++uuid] = {y, head[x], w};
    head[x] = uuid;
}

void Dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    q.push(make_pair(0, 1));
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
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    k = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), z = read();
        link(x, y, z);
        link(y, x, z);
        for (int j = 1; j <= k; ++j) {
            link(j * n + x, j * n + y, z);
            link(j * n + y, j * n + x, z);
            link((j - 1) * n + x, j * n + y, 0);
            link((j - 1) * n + y, j * n + x, 0);
        }
    }
    Dijkstra();
    ans = dis[n];
    for (int i = 1; i <= k; ++i)
        ans = min(ans, dis[i * n + n]);
    writeln(ans);
    return 0;
}
