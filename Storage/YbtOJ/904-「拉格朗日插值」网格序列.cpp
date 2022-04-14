#include <iostream>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int MOD = 998244353;

int n, m, k;
int fac[2 * MAX_N], ifac[2 * MAX_N], pre[2 * MAX_N], suf[2 * MAX_N];
int sum[2 * MAX_N];

int power(int x, int y) {
    int res = 1;

    for (; y; y >>= 1) {
        if (y & 1)
            res = 1ll * res * x % MOD;
        
        x = 1ll * x * x % MOD;
    }

    return res;
}

inline int sgnInv(int x) {
    static int inv[2] = { power(1, MOD - 2), power(MOD - 1, MOD - 2) };
    return inv[x & 1];
}

void preprocess(int deg) {
    fac[0] = 1;

    for (int i = 1; i <= deg + 1; ++i)
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    
    ifac[deg + 1] = power(fac[deg + 1], MOD - 2);

    for (int i = deg; i >= 0; --i)
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
}

int interpolation(int deg, int k, int y[]) {
    pre[0] = suf[deg + 2] = 1;

    for (int i = 1; i <= deg + 1; ++i)
        pre[i] = 1ll * pre[i - 1] * (k - i + MOD) % MOD;
    
    for (int i = deg + 1; i >= 1; --i)
        suf[i] = 1ll * suf[i + 1] * (k - i + MOD) % MOD;
    
    int ans = 0;

    for (int i = 1; i <= deg + 1; ++i) {
        int num = 1ll * y[i] * pre[i - 1] % MOD * suf[i + 1] % MOD;
        int den = 1ll * ifac[i - 1] * ifac[deg - i + 1] % MOD * sgnInv(deg - i + 1) % MOD;
        ans = (ans + 1ll * num * den) % MOD;
    }

    return ans;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 1; i <= min(n + m + 2, k); ++i) {
        int res = 1ll * (power(i, n) - power(i - 1, n) + MOD) * (power(i, m) - power(i - 1, m) + MOD) % MOD;
        sum[i] = (sum[i - 1] + res) % MOD;
    }

    if (k <= n + m + 2) {
        cout << sum[k] << endl;
    } else {
        preprocess(n + m + 1);
        cout << interpolation(n + m + 1, k, sum) << endl;
    }

    return 0;
}
