#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1e5 + 10;

int n;
ll a[maxn], b[maxn];

template <typename T> T multiply(T x, T y, T p) {
    T res = 0;
    while (y != 0) {
        if (y % 2 == 1) res = (res + x) % p;
        x = (x + x) % p;
        y /= 2;
    }
    return (res % p + p) % p;
    // return x * y;
}

template <typename T> T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template <typename T> T lcm(T a, T b) {
    T d = gcd(a, b);
    return a / d * b;
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
        y = t - (a / b) * y;
        return d;
    }
}

/** Solve the linear congruent equation [ax \equiv c (mod p)] */
template <typename T> pair<bool, T> equation(T a, T c, T p, T &g) {
    c = (c % p + p) % p;
    T x, y;
    T d = exgcd(a, p, x, y);
    g = d;
    if (c % d != 0) return make_pair(false, 0);
    x = multiply(x, c / d, p / d);
    x = (x % (p / d) + (p / d)) % (p / d);
    return make_pair(true, x);
}

template <typename T> pair<bool, T> exCrt(int n, T a[], T b[]) {
    if (n <= 0) return make_pair(false, 0);
    T g;
    auto res = equation(1LL, a[1], b[1], g);
    if (res.first == false) return make_pair(false, 0);
    T x = res.second, d = b[1];
    for (int i = 2; i <= n; ++i) {
        res = equation(d, a[i] - x, b[i], g);
        if (res.first == false) return make_pair(false, 0);
        x = x + res.second * d;
        d *= b[i] / g;
        x = (x % d + d) % d;
    }
    return make_pair(true, x);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i] >> a[i];
    auto res = exCrt(n, a, b);
    cout << res.second << endl;
    return 0;
}