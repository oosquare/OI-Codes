#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

using ll = long long;

int n, m, t;
ll a[maxn], p[maxn], atk0[maxn], atk1[maxn], atk[maxn], mx;
multiset<ll> tmp;

template <typename T> T multiply(T x, T y, T p) {
    T res = 0;
    for (; y != 0; y /= 2) {
        if (y % 2 == 1) res = (res + x) % p;
        x = (x + x) % p;
    }
    return (res % p + p) % p;
}

template <typename T> T exgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        T d = exgcd(b, a % b, x, y);
        T t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}

template <typename T> optional<T> exCrt(int n, T k[], T a[], T p[]) {
    T ans = 0, plcm = 1;
    for (int i = 1; i <= n; ++i) {
        T va = multiply(k[i], plcm, p[i]);
        T vb = p[i];
        T vc = (a[i] - multiply(k[i], ans, p[i]) + p[i]) % p[i];
        T x, y, d;
        d = exgcd(va, vb, x, y);
        x = (x % vb + vb) % vb;
        if (vc % d != 0) return nullopt;
        x = multiply(x, vc / d, vb / d * plcm);
        ans += multiply(x, plcm, vb / d * plcm);
        plcm *= vb / d;
        ans %= plcm;
    }
    if (ans < mx) ans += ((mx - ans - 1) / plcm + 1) * plcm;
    return ans;
}

void solve() {
    mx = 0;
    tmp.clear();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i) cin >> atk1[i];
    for (int i = 1; i <= m; ++i) {
        cin >> atk0[i];
        tmp.insert(atk0[i]);
    }
    for (int i = 1; i <= n; ++i) {
        auto it = tmp.upper_bound(a[i]);
        if (it != tmp.begin()) --it;
        atk[i] = *it;
        tmp.erase(it);
        tmp.insert(atk1[i]);
        mx = max(mx, (a[i] - 1) / atk[i] + 1);
    }

    auto res = exCrt(n, atk, a, p);
    cout << res.value_or(-1) << endl;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("dragon.in", "r", stdin);
    freopen("dragon.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) solve();
    return 0;
}