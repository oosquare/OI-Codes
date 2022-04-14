#pragma GCC optimize(3)
#include <iostream>
#include <algorithm>
#include <cmath>
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

} // namespace IO

constexpr int MAXT = 2e5 + 10;
constexpr int MOD = 998244353;

struct Query {
    int n, x, id;
};

int t;
int unit;
Query qs[MAXT * 2];
int fac[MAXT], inv[MAXT], inv2;
int sum = 1, nn, nx;
int ans[MAXT * 2];

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % MOD;

        x = 1ll * x * x % MOD;
    }

    return res;
}

void preprocess() {
    fac[0] = 1;

    for (int i = 1; i < MAXT; ++i) fac[i] = 1ll * fac[i - 1] * i % MOD;

    inv[MAXT - 1] = power(fac[MAXT - 1], MOD - 2);

    for (int i = MAXT - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;

    inv2 = power(2, MOD - 2);
}

int comb(int n, int m) {
    if (n < m)
        return 0;

    return 1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int calc(int n, int x) {
    while (n < nn) {
        sum = (sum - comb(nx, nn) + MOD) % MOD;
        --nn;
    }

    while (nx < x) {
        ++nx;
        sum = (2ll * sum % MOD - comb(nx - 1, nn) + MOD) % MOD;
    }

    while (nn < n) {
        ++nn;
        sum = (sum + comb(nx, nn)) % MOD;
    }

    while (x < nx) {
        sum = (1ll * (sum + comb(nx - 1, nn)) * inv2) % MOD;
        --nx;
    }

    return sum;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    using namespace IO;
    preprocess();
    t = read();
    unit = 258 * 1.85 - log2(114514) - log2(1919810);

    for (int i = 1; i <= t; ++i) {
        int l = read(), r = read(), x = read();
        qs[i] = { l - 1, x, i };
        qs[i + t] = { r, x, i + t };
    }

    sort(qs + 1, qs + 1 + 2 * t, [](const auto& lhs, const auto& rhs) {
        if (lhs.n / unit != rhs.n / unit)
            return lhs.n < rhs.n;

        if ((lhs.n / unit) & 1)
            return lhs.x < rhs.x;

        return lhs.x > rhs.x;
    });

    for (int i = 1; i <= 2 * t; ++i) ans[qs[i].id] = calc(qs[i].n, qs[i].x);

    for (int i = 1; i <= t; ++i) writeln((ans[i + t] - ans[i] + MOD) % MOD);

    return 0;
}
