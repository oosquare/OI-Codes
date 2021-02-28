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

typedef __int128 __int258;
typedef __int258 ll;

constexpr int maxn = 5000;

ll f[maxn][maxn], f2[maxn][maxn], r, g, b, t, n, ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read<ll>();
    r = read<ll>();
    g = read<ll>();
    b = read<ll>();
    t = read<ll>();
    for (int i = 1; i <= n; ++i)
        f[i][0] = (i - 1) * g * t + f[i - 1][0];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            f[i][j] = max(f[i - 1][j] + g * (i - j - 1) * (j * b + t),
                          f[i - 1][j - 1] + g * (i - j) * ((j - 1) * b + t));
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            ans = max(ans, f[i][j] + (n - i) * (j * b + t) * r +
                               (n - i) * (j * b + t) * (i - j) * g);
    writeln(ans);
    return 0;
}

