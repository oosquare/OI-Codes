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

constexpr int maxn = 2e3 + 10;
constexpr int mod = 998244353;

int n;
int k, x[maxn], y[maxn];

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

int inv(int x) {
    return power(x, mod - 2);
}

int lagrange(int k) {
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        int num = 1, den = 1;
        for (int j = 0; j <= n; ++j) {
            if (i == j)
                continue;
            num = 1LL * num * (k - x[j]) % mod;
            den = 1LL * den * (x[i] - x[j]) % mod;
        }
        ans = (1LL * ans + 1LL * y[i] * num % mod * inv(den) % mod) % mod;
    }
    return (ans + mod) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read() - 1, k = read();
    for (int i = 0; i <= n; ++i)
        x[i] = read(), y[i] = read();
    writeln(lagrange(k));
    return 0;
}