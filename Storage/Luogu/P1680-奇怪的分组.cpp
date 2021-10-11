#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int n, m;

int power(int x, int y) {
    int res = 1;
    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
    }
    return res;
}

int comb(int n, int m) {
    if (n < m)
        return 0;
    int num = 1, den = 1;
    for (int i = n - m + 1; i <= n; ++i)
        num = 1ll * num * i % mod;
    for (int i = 1; i <= m; ++i)
        den = 1ll * den  * i % mod;
    return 1ll * num * power(den, mod - 2) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int c;
        cin >> c;
        n -= c;
    }
    cout << comb(n - 1, m - 1) << endl;
    return 0;
}