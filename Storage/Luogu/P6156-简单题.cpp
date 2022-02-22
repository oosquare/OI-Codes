#include <iostream>
using namespace std;

constexpr int MAX_N = 5e6 + 10;
constexpr int MAX_SIZE = 1e7 + 10;
constexpr int MOD = 998244353;

int n;
long long k;
int prime[MAX_SIZE], tot;
bool notPrime[MAX_SIZE];
int prod[MAX_SIZE], f[MAX_N], g[MAX_SIZE], sum[MAX_N];
int fPre[MAX_SIZE], fSuf[MAX_SIZE], fSum[MAX_SIZE];
int ans;

int power(int x, long long y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % MOD;

        x = 1ll * x * x % MOD;
    }

    return res;
}

void sieve(int n) {
    n *= 2;
    prod[1] = 1;
    g[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            prod[i] = power(i, k);
            g[i] = i - 1;
        }

        for (int j = 1; j <= tot && 1ll * i * prime[j] <= n; ++j) {
            const int next = i * prime[j];
            notPrime[next] = true;
            prod[next] = 1ll * prod[i] * prod[prime[j]] % MOD;

            if (i % prime[j]) {
                g[next] = g[i] * (prime[j] - 1);
            } else if ((i / prime[j]) % prime[j]) {
                g[next] = -g[i / prime[j]] * prime[j];
                break;
            } else {
                g[next] = 0;
                break;
            }
        }
    }

    n /= 2;

    for (int i = 1; i <= n; ++i) {
        sum[i] = (sum[i - 1] + 1ll * prod[i] * g[i]) % MOD;
        sum[i] = (sum[i] + MOD) % MOD;
    }
}

void preprocess(int n) {
    for (int i = 1; i <= 2 * n; ++i) {
        fPre[i] = (fPre[i - 1] + 1ll * prod[i] * (i - 1)) % MOD;
        fSum[i] = (fSum[i - 1] + prod[i]) % MOD;
    }

    for (int i = 2 * n; i >= 1; --i)
        fSuf[i] = (fSuf[i + 1] + 1ll * prod[i] * (2 * n - i + 1)) % MOD;

    for (int i = 1; i <= n; ++i) {
        int mid = i + 1, res = 0;
        res = ((fPre[mid] + fSuf[mid + 1]) % MOD - fSuf[2 * i + 1]) % MOD;
        res = (res - 1ll * (2 * n - 2 * i) * (fSum[2 * i] - fSum[mid])) % MOD;
        res = (res + MOD) % MOD;
        f[i] = res;
    }
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> k;

    sieve(n);
    preprocess(n);

    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans = (ans + 1ll * (sum[r] - sum[l - 1] + MOD) * f[n / l]) % MOD;
    }

    cout << ans << endl;
    return 0;
}