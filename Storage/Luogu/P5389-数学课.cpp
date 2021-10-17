#include <bits/stdc++.h>
using namespace std;

constexpr long long mod = 998244353;

long long n;

long long inv(long long x) {
    long long y = mod - 2, res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    if (n == 0) {
        cout << inv(2) << endl;
        return 0;
    }

    n %= mod;
    long long p = 3ll * inv(n) % mod * inv(n + 2) % mod;
    cout << 1ll * (1 - p + mod) * inv(2) % mod << endl;
    return 0;
}