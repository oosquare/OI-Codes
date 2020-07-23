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

constexpr int maxn = 100 + 10;

typedef long long ll;
ll graph[maxn][maxn], cnt[maxn][maxn];
int n, m;

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    memset(graph, 0x3f, sizeof(graph));
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        graph[x][y] = graph[y][x] = read<ll>();
        cnt[x][y] = cnt[y][x] = 1;
    }
    
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    cnt[i][j] = cnt[i][k] * cnt[k][j];
                } else if (graph[i][j] == graph[i][k] + graph[k][j]) {
                    cnt[i][j] = cnt[i][j] + cnt[i][k] * cnt[k][j];
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        graph[i][i] = 0;
        cnt[i][i] = 1;
    }
    for (int v = 1; v <= n; ++v) {
        double ans = 0;
        for (int s = 1; s <= n; ++s) {
            if (s == v)
                continue;
            for (int t = 1; t <= n; ++t) {
                if (t == v || s == t)
                    continue;
                if (graph[s][v] + graph[v][t] == graph[s][t])
                    ans += 1.0 * cnt[s][v] * cnt[v][t] / cnt[s][t];
            }
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}