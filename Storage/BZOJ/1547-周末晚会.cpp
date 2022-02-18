#include <iostream>
using namespace std;

constexpr int MAX_N = 2000 + 10;
constexpr int MAX_K = 2000 + 10;
constexpr int MOD = 1e8 + 7;

int t, n, k;
int f[MAX_N][2], sum[MAX_N], g[MAX_N];

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % MOD;

        x = 1ll * x * x % MOD;
    }

    return res;
}

int phi(int x) {
    int res = x;

    for (int i = 2; i * i <= x; ++i) {
        if (x % i)
            continue;

        res = res / i * (i - 1);

        while (x % i == 0)
            x /= i;
    }

    if (x > 1)
        res = res / x * (x - 1);

    return res;
}

void dp() {
    for (int i = 1; i <= n; ++i)
        g[i] = 0;

    for (int t = 0; t <= k; ++t) {
        for (int i = 0; i <= n; ++i) {
            f[i][0] = f[i][1] = 0;
            sum[i] = 0;
        }

        f[t][1] = 1;

        if (k >= n)
            g[t] = (g[t] + f[t][1]) % MOD;

        for (int i = t + 1; i <= n; ++i) {
            f[i][0] = (f[i - 1][0] + f[i - 1][1]) % MOD;
            f[i][1] = (sum[i - 1] - sum[max(i - k - 1, 0)] + MOD) % MOD;
            sum[i] = (sum[i - 1] + f[i][0]) % MOD;
            g[i] = ((g[i] + f[i][0]) % MOD + (sum[i - 1] - sum[max(i - (k - t) - 1, 0)] + MOD)) % MOD;
        }
    }
}

int solve() {
    int ans = 0;
    dp();

    for (int i = 1; i * i <= n; ++i) {
        if (n % i)
            continue;

        if (i * i == n) {
            ans = (ans + 1ll * g[i] * phi(n / i)) % MOD;
        } else {
            ans = (ans + 1ll * g[i] * phi(n / i)) % MOD;
            ans = (ans + 1ll * g[n / i] * phi(i)) % MOD;
        }
    }

    ans = 1ll * ans * power(n, MOD - 2) % MOD;
    return ans;
}

int main() {
    cin >> t;

    for (int i = 1; i <= t; ++i) {
        cin >> n >> k;
        cout << solve() << endl;
    }

    return 0;
}