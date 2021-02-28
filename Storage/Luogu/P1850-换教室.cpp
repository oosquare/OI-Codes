#include <bits/stdc++.h>
using namespace std;

namespace IO {

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
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

constexpr int maxv = 305;
constexpr int maxn = 2005;
constexpr int maxm = 3005;

int w[maxn][maxn], c[maxn], d[maxn];
double f[maxn][maxm][2], p[maxn];
int n, m, v, e;
double ans = 1e18;

void init() {
    for (int k = 1; k <= v; ++k)
        for (int i = 1; i <= v; ++i)
            for (int j = 1; j <= v; ++j)
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
    for (int i = 0; i <= v; ++i)
        w[i][i] = w[0][i] = w[i][0] = 0;
        
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            f[i][j][0] = f[i][j][1] = 1e18;
    f[1][0][0] = 0;
    f[1][1][1] = 0;
}

void DP() {
    for (int i = 2; i <= n; ++i) {
        f[i][0][0] = f[i - 1][0][0] + w[c[i - 1]][c[i]];
        for (int j = 1; j <= min(i, m); ++j) {
            f[i][j][0] = f[i - 1][j][0] + w[c[i - 1]][c[i]];
            f[i][j][0] = min(f[i][j][0], f[i - 1][j][1] + p[i - 1] * w[d[i - 1]][c[i]] + (1 - p[i - 1]) * w[c[i - 1]][c[i]]);
            f[i][j][1] = f[i - 1][j - 1][0] + p[i] * w[c[i - 1]][d[i]] + (1 - p[i]) * w[c[i - 1]][c[i]];
            double dcc = (1 - p[i - 1]) * (1 - p[i]) * w[c[i - 1]][c[i]];
            double dcd = (1 - p[i - 1]) * p[i] * w[c[i - 1]][d[i]];
            double ddc = p[i - 1] * (1 - p[i]) * w[d[i - 1]][c[i]];
            double ddd = p[i - 1] * p[i] * w[d[i - 1]][d[i]];
            f[i][j][1] = min(f[i][j][1], f[i - 1][j - 1][1] + dcc + dcd + ddc + ddd);
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    memset(w, 0x3f, sizeof(w));
    n = read();
    m = read();
    v = read();
    e = read();
    for (int i = 1; i <= n; ++i)
        c[i] = read();
    for (int i = 1; i <= n; ++i)
        d[i] = read();
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &p[i]);
    for (int i = 1; i <= e; ++i) {
        int x = read(), y = read(), z = read();
        w[x][y] = w[y][x] = min(w[x][y], z);
    }
    init();
    DP();
    for (int i = 0; i <= m; ++i)
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    printf("%.2lf\n", ans);
    return 0;
}