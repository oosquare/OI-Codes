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

namespace exLucas {

ll a[100001], b[100001], total;

ll power(ll x, ll k, ll p) {
    ll res = 1;
    while (k) {
        if (k % 2)
            res = res * x % p;
        x = x * x % p;
        k /= 2;
    }
    return res % p;
}

ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int d = exGCD(b, a % b, x, y);
        int t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}

ll inverse(ll x, ll p) {
    ll x0, y0;
    exGCD(x, p, x0, y0);
    return (x0 + p) % p;
}

ll factor(ll n, ll p, ll pk) {
    if (n == 0)
        return 1;
    ll a = 1, b = 1;
    for (ll i = 1; i <= pk; ++i)
        if (i % p)
            a = a * i % pk;
    a = power(a, n / pk, pk);
    for (ll i = (n / pk) * pk; i <= n; ++i)
        if (i % p)
            b = b * (i % pk) % pk;
    return factor(n / p, p, pk) * a % pk * b % pk;
}

ll exponent(ll n, ll p) {
    if (n < p)
        return 0;
    return exponent(n / p, p) + n / p;
}

ll C(ll n, ll m, ll p, ll pk) {
    if (n < m)
        return 0;
    if (m == 0)
        return 1;
    ll fn = factor(n, p, pk), fm = factor(m, p, pk), fnm = factor(n - m, p, pk);
    ll ex = power(p, exponent(n, p) - exponent(m, p) - exponent(n - m, p), pk);
    return fn * inverse(fm, pk) % pk * inverse(fnm, pk) % pk * ex % pk;
}

ll CRT(ll prod) {
    ll ans = 0;
    for (int i = 1; i <= total; ++i) {
        ll m = prod / a[i];
        ll v = inverse(m, a[i]);
        ans = (ans + b[i] * m % prod * v % prod) % prod;
    }
    return ans;
}

ll calculate(ll n, ll m, ll p) {
    ll p2 = p;
    total = 0;
    for (ll i = 2; i * i <= p; ++i) {
        if (p2 % i == 0) {
            ll pk = 1;
            while (p2 % i == 0) {
                pk *= i;
                p2 /= i;
            }
            a[++total] = pk;
            b[total] = C(n, m, i, pk);
        }
    }
    if (p2 != 1) {
        a[++total] = p2;
        b[total] = C(n, m, p2, p2);
    }
    return CRT(p);
}

} // namespace exLucas

ll p, n, m, sum, ans = 1, w[10];

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    p = IO::read<ll>();
    n = IO::read<ll>();
    m = IO::read<ll>();
    for (int i = 1; i <= m; ++i) {
        w[i] = IO::read<ll>();
        sum += w[i];
    }
    if (sum > n) {
        printf("Impossible\n");
        return 0;
    }
    for (int i = 1; i <= m; ++i) {
        ans = ans * exLucas::calculate(n, w[i], p) % p;
        n -= w[i];
    }
    IO::writeln(ans);
    return 0;
}