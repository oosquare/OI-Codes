#include <iostream>
using namespace std;

constexpr int MAX_N = 1e7 + 10;
constexpr int MAX_SIZE = 2e7 + 10;

int t;
unsigned n, k;
int prime[MAX_SIZE], factor[MAX_SIZE], tot;
unsigned f[MAX_SIZE], g[MAX_SIZE];
unsigned ans;

unsigned power(unsigned x, unsigned y) {
    unsigned res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = res * x;

        x = x * x;
    }

    return res;
}

void sieve(int n) {
    n *= 2;
    f[1] = 1;
    g[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!factor[i]) {
            prime[++tot] = i;
            f[i] = power(i, k);
            g[i] = i - 1;

            if (1ll * i * i <= n)
                g[i * i] = -i;

            for (long long prod = i, exp = 1; prod <= n; prod *= i, ++exp)
                factor[prod] = prod;
        }

        for (int j = 1; j <= tot && 1ll * i * prime[j] <= n; ++j) {
            const int next = i * prime[j];

            if (i % prime[j]) {
                factor[next] = prime[j];
                f[next] = f[i] * f[prime[j]];
                g[next] = g[i] * g[prime[j]];
            } else {
                factor[next] = factor[i] * prime[j];
                f[next] = f[i] * f[prime[j]];
                g[next] = g[next / factor[next]] * g[factor[next]];
                break;
            }
        }
    }

    n /= 2;

    for (int i = 1; i <= n; ++i)
        g[i] = g[i - 1] + f[i] * g[i];
}

void preprocess(int n) {
    for (int t = 1; t <= 2; ++t)
        for (int i = 1; i <= 2 * n; ++i)
            f[i] += f[i - 1];
}

unsigned calc(int i) {
    return f[i * 2] - f[i] * 2;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> t >> n >> k;

    sieve(n);
    preprocess(n);

    while (t--) {
        int m;
        cin >> m;
        ans = 0;

        for (int l = 1, r; l <= m; l = r + 1) {
            r = m / (m / l);
            ans = ans + (g[r] - g[l - 1]) * calc(m / l);
        }

        cout << ans << endl;
    }

    return 0;
}