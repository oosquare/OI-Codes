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
constexpr int mod = 10007;

int t, n, m;
ll fac[mod + 1], inv[mod + 1];

ll C(ll n, ll m) {
    if (n < m)
        return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

ll lucas(ll n, ll m) {
    if (m == 0)
        return 1;
    return C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    fac[0] = fac[1] = 1;
    inv[0] = inv[1] = 1;
    for (ll i = 2; i <= mod; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    for (ll i = 2; i <= mod; ++i) {
        inv[i] = inv[i - 1] * inv[i] % mod;
    }
    t = read();
    while (t--) {
        n = read();
        m = read();
        printf("%lld\n", lucas(n, m));
    }
    return 0;
}