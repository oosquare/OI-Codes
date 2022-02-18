#include <iostream>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int MOD = 19260817;

int t, n;
int prime[MAX_N], mu[MAX_N], notPrime[MAX_N], tot;
int inv[MAX_N];
int prod[MAX_N], invProd[MAX_N], tmp[MAX_N];
int num = 1, den = 1;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % MOD;

        x = 1ll * x * x % MOD;
    }

    return res;
}

void preprocessMu(int n) {
    mu[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            mu[i] = -1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}

void preprocessInv(int n) {
    inv[1] = 1;

    for (int i = 2; i <= n; ++i)
        inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
}

void preprocessProd(int n) {
    for (int d = 1; d <= n; ++d)
        prod[d] = 1;

    for (int d = 1; d <= n; ++d) {
        for (int p = d, k = 1; p <= n; p += d, ++k) {
            if (mu[k] == 1)
                prod[p] = 1ll * prod[p] * d % MOD;
            else if (mu[k] == -1)
                prod[p] = 1ll * prod[p] * inv[d] % MOD;
        }
    }

    prod[0] = 1;

    for (int i = 1; i <= n; ++i) {
        tmp[i] = prod[i];
        prod[i] = 1ll * prod[i] * prod[i - 1] % MOD;
    }

    invProd[n] = power(prod[n], MOD - 2);

    for (int i = n - 1; i >= 0; --i)
        invProd[i] = 1ll * invProd[i + 1] * tmp[i + 1] % MOD;
}

int main() {
    preprocessMu(MAX_N - 10);
    preprocessInv(MAX_N - 10);
    preprocessProd(MAX_N - 10);

    cin >> t;

    while (t--) {
        cin >> n;
        num = den = 1;

        for (int i = 1; i <= n; ++i)
            num = 1ll * num * i % MOD;

        num = power(num, 2 * n);

        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            int base = 1ll * prod[r] * invProd[l - 1] % MOD;
            den = 1ll * den * power(base, 1ll * (n / l) * (n / l) % (MOD - 1)) % MOD;
        }

        den = 1ll * den * den % MOD;

        cout << 1ll * num * power(den, MOD - 2) % MOD << endl;
    }

    return 0;
}