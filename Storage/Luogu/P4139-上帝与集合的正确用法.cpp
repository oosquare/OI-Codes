#include <iostream>
using namespace std;

constexpr int MAXP = 1e7 + 10;

int t, p;
int buc[MAXP];
int prime[MAXP], phi[MAXP], tot;
bool notPrime[MAXP];

int gcd(int x, int y) {
    int t;

    while (y) {
        t = x;
        x = y;
        y = t % y;
    }

    return x;
}

int power(int x, int y, int p) {
    int res = 1;
    
    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % p;
        
        x = 1ll * x * x % p;
    }

    return res;
}

void preprocess(int n) {
    notPrime[1] = true;

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
}

int calc(int p) {
    if (buc[p] != -1)
        return buc[p];

    int res;

    if (gcd(2, p) == 1)
        res = power(2, calc(phi[p]), p);
    else
        res = power(2, calc(phi[p]) + phi[p], p);
    
    buc[p] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    preprocess(MAXP - 1);

    for (int i = 0; i < MAXP; ++i)
        buc[i] = -1;
    
    buc[1] = buc[2] = 0;

    cin >> t;

    while (t--) {
        int x;
        cin >> x;
        cout << calc(x) << endl;
    }
    
    return 0;
}