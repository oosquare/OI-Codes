#include <iostream>
using namespace std;

constexpr int MOD = 1e9 + 7;
constexpr int MAX_M = 1e5 + 10;

int t, m;
int prime[MAX_M], miu[MAX_M], tot;
bool notPrime[MAX_M];
int inv[MAX_M];

void preprocess(int n) {
    notPrime[1] = true;
    miu[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            miu[i] = -1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                miu[i * prime[j]] = -miu[i];
            } else {
                miu[i * prime[j]] = 0;
                break;
            }
        }
    }

    for (int i = 1; i <= n; ++i) miu[i] = ((miu[i] + miu[i - 1]) % MOD + MOD) % MOD;

    inv[1] = 1;

    for (int i = 2; i <= n; ++i) inv[i] = 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD;
}

int calc(int m) {
    int res = 0;

    for (int l = 2, r; l <= m; l = r + 1) {
        r = m / (m / l);
        int sum = 1ll * (m / l) * inv[m - (m / l)] % MOD;
        res = (res + 1ll * (miu[r] - miu[l - 1] + MOD) % MOD * sum) % MOD;
    }

    return (1 - res + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    preprocess(MAX_M - 1);

    cin >> m;
    cout << calc(m) << endl;

    return 0;
}