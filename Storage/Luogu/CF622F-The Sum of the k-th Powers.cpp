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

constexpr int maxk = 1e6 + 10;
constexpr int mod = 1e9 + 7;

int n, k, x[maxk], y[maxk], pre[maxk], suf[maxk], inv[maxk];

int power(int x, int k) {
    int res = 1;
    while (k) {
        if (k % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
        k /= 2;
    }
    return res % mod;
}

int lagrange(int n, int k) {
    int ans = 0;
    pre[0] = (k - x[0]) % mod;
    suf[n + 1] = 1;
    inv[0] = inv[1] = 1;
    for (int i = 1; i <= n; ++i)
        pre[i] = 1LL * pre[i - 1] * (k - x[i]) % mod;
    for (int i = n; i >= 0; --i)
        suf[i] = 1LL * suf[i + 1] * (k - x[i]) % mod;
    for (int i = 2; i <= n; ++i)
        inv[i] = -1LL * mod / i * inv[mod % i] % mod;
    for (int i = 2; i <= n; ++i)
        inv[i] = 1LL * inv[i] * inv[i - 1] % mod;
    for (int i = 0; i <= n; ++i) {
        int num = 1LL * y[i] * (i == 0 ? 1 : pre[i - 1]) % mod * suf[i + 1] % mod;
        int iden = 1LL * inv[i] * (((n - i) & 1) ? -1 : 1) * inv[n - i] % mod;
        ans = (ans + 1LL * num * iden % mod) % mod;
    }
    return (ans + mod) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), k = read();
    x[0] = 1, y[0] = 1;
    for (int i = 2; i <= k + 2; ++i) {
        x[i - 1] = i;
        y[i - 1] = (1LL * y[i - 2] + power(i, k)) % mod;
    }
    writeln(lagrange(k + 1, n));
    return 0;
}