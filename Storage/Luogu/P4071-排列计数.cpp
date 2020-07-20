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

constexpr ll mod = 1e9 + 7;
constexpr int maxn = 1e6;
int t, n, m;
ll d[maxn + 10], factor[maxn + 10];

ll power(ll x, ll k) {
    ll res = 1;
    while (k) {
        if (k % 2)
            res = res * x % mod;
        x = x * x % mod;
        k /= 2;
    }
    return res % mod;
}

ll inv(ll x) {
    return power(x, mod - 2);
}

ll C(int n, int m) {
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    return factor[n] * inv(factor[m]) % mod * inv(factor[n - m]) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    d[1] = 0;
    d[2] = factor[1] = 1;
    for (int i = 3; i <= maxn; ++i)
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % mod;
    for (int i = 2; i <= maxn; ++i)
        factor[i] = factor[i - 1] * i % mod;
    t = read();
    while (t--) {
        n = read();
        m = read();
        writeln(n == m ? 1 : C(n, m) * d[n - m] % mod);
    }
    return 0;
}