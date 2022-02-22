#include <iostream>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int MOD = 1e9 + 7;

int t, n, m, i1, i2, j1, j2;
int prime[MAX_N], phi[MAX_N], tot;
bool notPrime[MAX_N];

void preprocess(int n) {
    notPrime[1] = 1;
    phi[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        phi[i] = phi[i - 1] + phi[i];

        if (phi[i] >= MOD)
            phi[i] -= MOD;
    }
}

int calc(int n, int m) {
    int res = 0;

    for (int l = 1, r, e = min(n, m), val; l <= e; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        val = 1ll * (n / l) * (m / l) % MOD;
        res = (res + 1ll * (phi[r] - phi[l - 1] + MOD) * val) % MOD;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    cin >> n >> m;
    preprocess(min(n, m));

    while (t--) {
        cin >> i1 >> j1 >> i2 >> j2;
        long long ans = calc(i2, j2);
        ans -= calc(i1 - 1, j2);
        ans -= calc(i2, j1 - 1);
        ans += calc(i1 - 1, j1 - 1);
        cout << (ans % MOD + MOD) % MOD << endl;
    }

    return 0;
}