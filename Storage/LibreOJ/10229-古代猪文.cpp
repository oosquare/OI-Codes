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

constexpr int maxn = 1e6 + 10;

ll n, g, z, total, p[5] = {0, 2, 3, 4679, 35617}, q[5], factor[maxn];
constexpr ll mod = 999911658;

ll power(ll x, ll k, ll p) {
    ll res = 1;
    while (k != 0) {
        if (k % 2 == 1)
            res = res * x % p;
        x = x * x % p;
        k /= 2;
    }
    return res % p;
}

inline ll inverse(ll x, ll p) { return power(x, p - 2, p); }

ll C(ll n, ll m, ll p) {
    ll a = 1, b = 1;
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    for (int i = n - m + 1; i <= n; ++i)
        a = a * i % p;
    for (int i = 1; i <= m; ++i)
        b = b * i % p;
    return a * inverse(b, p) % p;
}

ll lucas(ll n, ll m, ll p) {
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p);
}

ll calculate() {
    ll prod = mod, ans = 0;
    for (int i = 1; i <= 4; ++i) {
        ll m = prod / p[i];
        ll v = inverse(m, p[i]);
        ans = (ans + q[i] * m * v) % prod;
    }
    return ans;
}

void divide(ll n) {
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            for (int j = 1; j <= 4; ++j)
                q[j] = (q[j] + lucas(n, i, p[j])) % p[j];
            if (i * i != n)
                for (int j = 1; j <= 4; ++j)
                    q[j] = (q[j] + lucas(n, n / i, p[j])) % p[j];
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
    g = read();
    g %= mod + 1;
    if (g == 0) {
        writeln(0);
        return 0;
    }
    divide(n);
    ll z = (calculate() + mod) % mod;
    writeln(power(g, z, mod + 1));

    return 0;
}