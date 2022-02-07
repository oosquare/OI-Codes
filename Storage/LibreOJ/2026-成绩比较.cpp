#include <iostream>
using namespace std;

constexpr int MAXN = 100 + 10;
constexpr int MOD = 1e9 + 7;

int n, m, k;
int u[MAXN], r[MAXN];
int c[MAXN][MAXN], d[MAXN], f[MAXN][MAXN];

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % MOD;

        x = 1ll * x * x % MOD;
    }

    return res;
}

int lagrange(int deg, int k, int x[], int y[]) {
    int res = 0;

    for (int i = 1; i <= deg + 1; ++i) {
        int num = y[i], den = 1;

        for (int j = 1; j <= deg + 1; ++j) {
            if (i == j)
                continue;

            num = 1ll * num * (k - x[j] + MOD) % MOD;
            den = 1ll * den * (x[i] - x[j] + MOD) % MOD;
        }

        res = (res + 1ll * num * power(den, MOD - 2)) % MOD;
    }

    return res;
}

int calc(int i) {
    int x[MAXN] = { 0 }, y[MAXN] = { 0 };

    for (int j = 1; j <= min(u[i], n + 1); ++j) {
        x[j] = j;
        y[j] = (y[j - 1] + 1ll * power(j, n - r[i]) * power(u[i] - j, r[i] - 1)) % MOD;
    }

    if (u[i] <= n + 1)
        return y[u[i]];

    return lagrange(n, u[i], x, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 1; i <= m; ++i)
        cin >> u[i];

    for (int i = 1; i <= m; ++i)
        cin >> r[i];

    for (int i = 0; i <= n; ++i)
        c[i][0] = c[i][i] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
            
    for (int i = 1; i <= m; ++i)
        d[i] = calc(i);

    f[0][n - 1] = 1;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j < n; ++j) {
            for (int k = j; k < n; ++k) {
                if (k - j > r[i] - 1)
                    continue;

                int pre = 1ll * f[i - 1][k] * c[k][j] % MOD * c[n - k - 1][r[i] - 1 - (k - j)] % MOD * d[i] % MOD;
                f[i][j] = (f[i][j] + pre) % MOD;
            }
        }
    }

    cout << f[m][k] << endl;
    return 0;
}
