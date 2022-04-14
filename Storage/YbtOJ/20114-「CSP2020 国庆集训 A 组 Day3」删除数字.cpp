#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
long long n, x, y, ans;

int power(long long a, long long b) {
    long long r = 1;
    while (b) {
        if (b & 1)
            r = (r * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return r;
}

int main() {
    freopen("nbc.in", "r", stdin);
    freopen("nbc.out", "w", stdout);
    cin >> n;
    x = power(2, n - 1);
    x = (x * (n - 1) + 1) % mod;
    y = power(2, n - 1);
    ans = x * power(y, mod - 2) % mod;
    cout << ans;
    return 0;
}
