#include <iostream>
#include <bitset>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int MOD = 104857601;

int n;
int prime[MAX_N], phi[MAX_N], tot;
bitset<MAX_N> notPrime;
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

void preprocess(int n) {
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

    for (int i = 1; i <= n; ++i)
        phi[i] = (phi[i - 1] + phi[i]) % (MOD - 1);
}

int main() {
    cin >> n;
    preprocess(n);

    for (int i = 1; i <= n; ++i)
        num = 1ll * num * i % MOD;
    
    num = power(num, 2 * n);

    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        int base = 1;

        for (int i = l; i <= r; ++i)
            base = 1ll * base * i % MOD;

        den = 1ll * den * power(base, 2 * phi[n / l] - 1) % MOD;
    }

    den = 1ll * den * den % MOD;

    cout << 1ll * num * power(den, MOD - 2) % MOD << endl;

    return 0;
}