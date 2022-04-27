#include <iostream>

constexpr int MAX_N = 100000 + 10;
constexpr int MOD = 1000000007;

int n, k;
int fac[MAX_N], inv[MAX_N];
int pk[MAX_N], pk1[MAX_N];
int ans;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % MOD;

        x = 1ll * x * x % MOD;
    }

    return res;
}

void prepocess(int n) {
    fac[0] = 1;

    for (int i = 1; i <= n; ++i) {
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    }

    inv[n] = power(fac[n], MOD - 2);

    for (int i = n - 1; i >= 0; --i)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;

    pk[0] = 1;

    for (int i = 1; i <= n; ++i)
        pk[i] = 1ll * pk[i - 1] * k % MOD;

    pk1[0] = 1;

    for (int i = 1; i <= n; ++i)
        pk1[i] = 1ll * pk1[i - 1] * (k - 1) % MOD;
}

int comb(int n, int m) {
    return 1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k;
    prepocess(n);

    for (int i = 0; i <= n; ++i) {
        int sgn = (i % 2 ? -1 : 1);
        int sol = power((1ll * pk[n - i] * pk1[i] % MOD - pk1[n] + MOD) % MOD, n);
        ans = (ans + 1ll * sgn * comb(n, i) * sol % MOD + MOD) % MOD;
    }

    std::cout << ans << std::endl;
}
