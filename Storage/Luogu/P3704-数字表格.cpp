#include <iostream>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int MOD = 1e9 + 7;
constexpr int MOD2 = 1e9 + 6;

int t, n, m;
int prime[MAX_N], mu[MAX_N], tot;
bool notPrime[MAX_N];
int fib[MAX_N], ifib[MAX_N], tmp[MAX_N];

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
    notPrime[1] = true;
    mu[1] = 1;

    for (int i = 1; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            mu[i] = -1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                mu[i * prime[j]] = -mu[i];
            } else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        mu[i] = ((mu[i - 1] + mu[i]) % MOD2 + MOD2) % MOD2;
}

void preprocessFib(int n) {
    tmp[1] = 1;

    for (int i = 2; i <= n; ++i)
        tmp[i] = (tmp[i - 1] + tmp[i - 2]) % MOD;
    
    fib[0] = 1;
    
    for (int i = 1; i <= n; ++i)
        fib[i] = 1ll * fib[i - 1] * tmp[i] % MOD;
    
    ifib[n] = power(fib[n], MOD - 2);

    for (int i = n - 1; i >= 0; --i)
        ifib[i] = 1ll * ifib[i + 1] * tmp[i + 1] % MOD;
}

int calc(int n, int m) {
    int res = 0;
    
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        res = (res + 1ll * (mu[r] - mu[l - 1] + MOD2) * (n / l) % MOD2 * (m / l)) % MOD2;
    }

    return res;
}

void solve() {
    cin >> n >> m;
    int res = 1;

    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        res = 1ll * res * power(1ll * fib[r] * ifib[l - 1] % MOD, calc(n / l, m / l)) % MOD;    
    }

    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    preprocessMu(MAX_N - 10);
    preprocessFib(MAX_N - 10);

    cin >> t;

    while (t--)
        solve();

    return 0;
}