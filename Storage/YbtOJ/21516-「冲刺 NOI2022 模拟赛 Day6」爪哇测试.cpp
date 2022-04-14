#include <iostream>
using namespace std;

constexpr int INFINITY = 0x3f3f3f3f;
constexpr int MOD = 998244353;
constexpr int MAX_N = 24010000;
constexpr int MAX_M = 20 + 5;

int n, m, l = INFINITY, r = -INFINITY;
int pos[MAX_M];
int fac[MAX_N], inv[MAX_N];
int e[MAX_N], e2[MAX_N], sum[MAX_N];
int ans;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = (int) (1ll * res * x % MOD);
        
        x = (int) (1ll * x * x % MOD);
    }

    return res;
}

void preprocess(int n) {
    fac[0] = 1;

    for (int i = 1; i <= n; ++i)
        fac[i] = (int) (1ll * fac[i - 1] * i % MOD);

    inv[n] = power(fac[n], MOD - 2);

    for (int i = n - 1; i >= 0; --i)
        inv[i] = (int) (1ll * inv[i + 1] * (i + 1) % MOD);
}

int comb(int n, int m) {
    return (int) (1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD);
}

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);

    cin >> n >> m;
    
    preprocess(n);
    const int inv2n = power(power(2, n), MOD - 2);

    for (int i = 1; i <= m; ++i) {
        cin >> pos[i];
        l = min(l, pos[i] - n);
        r = max(r, pos[i] + n);
    }
        
    for (int i = 0; i <= n; ++i) {
        if (i % 2 != n % 2)
            continue;
        
        e[i] = (int) (1ll * inv2n * comb(n, (n + i) / 2) % MOD);
    }

    for (int i = n; i >= 0; --i) {
        sum[i] = (sum[i + 1] + e[i]) % MOD;
        e2[i] = ((e[i] + sum[i + 1]) % MOD + sum[i + 1] % MOD);
    }

    for (int i = l; i <= r; ++i) {
        int res = 1;

        for (int j = 1; j <= m; ++j) {
            int d = abs(i - pos[j]);
            
            if (d > n)
                continue;
            
            res = (int) (1ll * res * (1 - e2[d] + MOD) % MOD);
        }

        res = (1 - res + MOD) % MOD;
        ans = (ans + res) % MOD;
    }

    cout << ans << endl;
    return 0;
}
