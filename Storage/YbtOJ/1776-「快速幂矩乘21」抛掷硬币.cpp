#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int mod = 998244353;

ll p, k;

ll power(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
        y /= 2;
    }
    return res;
}

ll inv(ll x) {
    return power(x, mod - 2);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("coin.in", "r", stdin);
    freopen("coin.out", "w", stdout);
#endif
    cin >> p >> k;
    if (p == 1) {
        cout << k % mod << endl;
        return 0;
    }
    ll num = (1 - inv(power(p, k)) + mod) % mod;
    ll den = (p - 1 + mod) % mod;
    cout << 1LL * num * inv(den) % mod << endl;
    return 0;
}
