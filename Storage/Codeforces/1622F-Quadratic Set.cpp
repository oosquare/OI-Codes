#include <iostream>
#include <random>
#include <unordered_map>
using namespace std;

constexpr int MAX_N = 1e6 + 10;

int n;
int prime[MAX_N], pt;
bool notPrime[MAX_N];
long long f[MAX_N], p;
unordered_map<long long, int> mp;

void sieve(int n) {
    mt19937 gen((random_device())());
    uniform_int_distribution<long long> dist(0x3f3f3f3f, 0x3f3f3f3f3f3f3f3f);

    notPrime[1] = true;
    f[1] = 0;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++pt] = i;
            f[i] = dist(gen);
        }

        for (int j = 1; j <= pt && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;
            f[i * prime[j]] = (f[i] ^ f[prime[j]]);

            if (i % prime[j] == 0)
                break;
        }
    }

    for (int i = 2; i <= n; ++i)
        f[i] ^= f[i - 1];
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n;
    sieve(n);

    for (int i = 1; i <= n; ++i)
        p ^= f[i];

    if (p == 0) {
        cout << n << endl;

        for (int i = 1; i <= n; ++i)
            cout << i << " ";

        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        if (p ^ f[i])
            continue;

        cout << n - 1 << endl;

        for (int j = 1; j <= n; ++j) {
            if (j == i)
                continue;

            cout << j << " ";
        }

        return 0;
    }

    if (n % 4 == 0) {
        cout << n - 1 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }

    for (int i = 1; i <= n; ++i)
        mp[f[i]] = i;
    
    for (int i = 1; i <= n; ++i) {
        if (!mp.count(p ^ f[i]))
            continue;
        
        int t = mp[p ^ f[i]];

        cout << n - 2 << endl;

        for (int j = 1; j <= n; ++j) {
            if (j == i || j == t)
                continue;
            
            cout << j << " ";
        }

        return 0;
    }

    if (n % 4 == 2) {
        cout << n - 2 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == 2 || i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }

    --n;

    if (n % 4 == 0) {
        cout << n - 1 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }

    if (n % 4 == 2) {
        cout << n - 2 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == 2 || i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }
    
    return 0;
}