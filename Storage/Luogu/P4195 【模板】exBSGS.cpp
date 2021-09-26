#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> T gcd(T x, T y) {
    return y == 0 ? x : gcd(y, x % y);
}

template <typename T> T power(T x, T y, T p) {
    T res = 1;
    for (; y != 0; y /= 2) {
        if (y % 2 == 1)
            res = 1LL * res * x % p;
        x = 1LL * x * x % p;
    }
    return res;
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

template <typename T> T inverse(T a, T p) {
    T x, y;
    exgcd(a, p, x, y);
    x = (x % p + p) % p;
    return x;
}

template <typename T> optional<T> bsgs(T a, T b, T p) {
    a %= p;
    b %= p;
    T sqrtp = ceil(sqrt(p)), prod = b, base = power(a, sqrtp, p);
    map<T, T> mp;
    for (T i = 0; i <= sqrtp; ++i) {
        mp[prod] = i;
        prod = prod * a % p;
    }
    prod = 1;
    for (T i = 0; i <= sqrtp; ++i) {
        auto it = mp.find(prod);
        if (it != mp.end() && i * sqrtp - it->second >= 0) {
            return i * sqrtp - it->second;
        }
        prod = prod * base % p;
    }
    return nullopt;
}

template <typename T> optional<T> exBsgs(T a, T b, T p) {
    if (p == 1) return 0;
    a %= p;
    b %= p;
    if (b == 1) return 0;
    T x = 0, t, y = 1;
    while ((t = gcd(a, p)) != 1) {
        if (b % t != 0) return nullopt;
        b /= t;
        ++x;
        p /= t;
        y = y * (a / t) % p;
        if (b == y) return x;
    }
    auto res = bsgs(a, b * inverse(y, p) % p, p);
    if (res.has_value() == false) return nullopt;
    return res.value() + x;
}

int main() {
    ios::sync_with_stdio(false);
    ll a, p, b;
    while (cin >> a >> p >> b, a != 0 && b != 0 && p != 0) {
        auto res = exBsgs(a, b, p);
        if (res.has_value())
            cout << res.value() << endl;
        else
            cout << "No Solution" << endl;
    }
    return 0;
}