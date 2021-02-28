#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
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

typedef long long ll;

int t;
ll n, m, p;

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

inline ll inv(ll x, ll p) {
    return power(x, p - 2, p);
}

ll C(ll n, ll m, ll p) {
    if (n < m)
        return 0;
    ll a = 1, b = 1;
    for (int i = n - m + 1; i <= n; ++i)
        a = a * i % p;
    for (int i = 2; i <= m; ++i)
        b = b * i % p;
    return a * inv(b, p) % p;
}

ll lucas(ll n, ll m, ll p) {
    if (m == 0)
        return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    t = read();
    while (t--) {
        n = read<ll>();
        m = read<ll>();
        p = read<ll>();
        printf("%lld\n", lucas(n, m, p));
    }
    return 0;
}