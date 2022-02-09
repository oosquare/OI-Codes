#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxm = 50 + 10;
constexpr int mod = 1e9 + 7;

int t, m;
ll n, a[maxm];
int x[maxm], y[maxm];
int fac[maxm], inv[maxm], pre[maxm], suf[maxm];

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

inline int sgnInv(int n) {
    static int inv[2] = {power(1, mod - 2), power(mod - 1, mod - 2)};
    return inv[n % 2];
}

void preprocess() {
    fac[0] = 1;

    for (int i = 1; i <= maxm - 1; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    
    inv[maxm - 1] = power(fac[maxm - 1], mod - 2);

    for (int i = maxm - 2; i >= 0; --i)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
}

int lagrange(ll x0, int n) {
    int ans = 0;

    pre[0] = suf[n + 2] = 1;

    for (int i = 1; i <= n + 1; ++i)
        pre[i] = 1ll * pre[i - 1] * (x0 - i + mod) % mod;
    
    for (int i = n + 1; i >= 1; --i)
        suf[i] = 1ll * suf[i + 1] * (x0 - i + mod) % mod;

    for (int i = 1; i <= n + 1; ++i) {
        int num = 1ll * y[i] * pre[i - 1] % mod * suf[i + 1] % mod;
        int den = 1ll * inv[i - 1] * inv[n - i + 1] % mod * sgnInv(n - i + 1) % mod % mod;
        ans = (1ll * ans + 1ll * num * den % mod) % mod;
    }

    return (ans + mod) % mod;
}

int calc(ll x0) {
    if (x0 <= m + 3)
        return y[x0];

    return lagrange(x0, m + 2);
}

int solve() {
    int ans = 0;

    for (int i = 1; i <= m + 3; ++i) {
        x[i] = i;
        y[i] = (y[i - 1] + power(i, m + 1)) % mod;
    }

    for (int i = 1; i <= m; ++i) {
        ans = (ans + calc(n)) % mod;

        for (int j = i; j <= m; ++j)
            ans = (ans - power(a[j], m + 1) + mod) % mod;

        for (int j = i + 1; j <= m; ++j)
            a[j] -= a[i];

        n -= a[i];
    }

    if (n != 0)
        ans = (ans + calc(n)) % mod;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    preprocess();
    cin >> t;

    while (t--) {
        cin >> n >> m;

        for (int i = 1; i <= m; ++i)
            cin >> a[i];

        sort(a + 1, a + 1 + m);
        cout << solve() << endl;
    }

    return 0;
}