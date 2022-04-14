#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 2e5 + 10;
constexpr ll mod = 1004535809;

struct movie {
    ll l, x, y;

    bool operator<(movie rhs) {
        return x * (rhs.y - rhs.x) * l > rhs.x * (y - x) * rhs.l;
    }
};

ll power(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y % 2)
            res = res * x % mod;
        x = x * x % mod;
        y /= 2;
    }
    return res;
}

ll inv(ll x) {
    return power(x, mod - 2);
}

movie mo[maxn];
int n;
ll ans, len;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> mo[i].l >> mo[i].x >> mo[i].y;
    sort(mo + 1, mo + 1 + n);
    for (int i = 1; i <= n; ++i) {
        ll a1 = (2 * mo[i].x - mo[i].y + mod) * mo[i].l % mod;
        ll a2 = (mo[i].y - mo[i].x) * len % mod;
        ans = (ans + (a1 + a2) % mod * inv(mo[i].y) % mod) % mod;
        len = (len + mo[i].x * inv(mo[i].y) % mod * mo[i].l % mod) % mod;
    }
    cout << ans << endl;
    return 0;
}
