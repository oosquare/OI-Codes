#include <bits/stdc++.h>
using namespace std;

constexpr int maxv = 2e3 + 10;
constexpr int mod = 1e5 + 3;

int a, b, c, d, k, ans;
int fact[maxv], inv[maxv];

int power(int x, int y) {
    int res = 1;
    for (; y; y /= 2) {
        if (y % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
    }
    return res;
}

void preprocess() {
    fact[0] = 1;
    for (int i = 1; i <= 2000; ++i)
        fact[i] = 1LL * fact[i - 1] * i % mod;
    inv[2000] = power(fact[2000], mod - 2);
    for (int i = 2000 - 1; i >= 0; --i)
        inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}

int comb(int n, int m) {
    if (n < m)
        return 0;
    return 1LL * fact[n] * inv[m] % mod * inv[n - m] % mod;
}

int perm(int n, int m) {
    if (n < m)
        return 0;
    return 1LL * fact[n] * inv[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    preprocess();
    cin >> a >> b >> c >> d >> k;
    for (int i = 0; i <= k; ++i) {
        if (i > min(a, b) || k - i > min(d, a + c - i))
            continue;
        ans += 1LL * comb(b, i) * perm(a, i) % mod * comb(d, k - i) % mod * perm(a + c - i, k - i) % mod;
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}