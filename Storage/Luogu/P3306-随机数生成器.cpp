#include <bits/stdc++.h>
using namespace std;

template <typename T> using triple = tuple<T, T, T>;
using ll = long long;

int n;
ll p, a, b, xx1, t;

template <typename T> T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template <typename T> triple<T> exgcd(T a, T b) {
    if (b == 0) {
        return make_tuple(a, T(1), T(0));
    } else {
        auto [d, x, y] = exgcd(b, a % b);
        return make_tuple(d, y, x - a / b * y);
    }
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

template <typename T> T inverse(T a, T p) {
    auto [d, x, y] = exgcd(a % p, p);
    return (x % p + p) % p;
}

template <typename T> optional<T> bsgs(T a, T b, T p) {
    a %= p;
    b %= p;
    T sqrtp = ceil(sqrt(p)), prod = b, base = power(a, sqrtp, p);
    unordered_map<T, T> mp;
    for (T i = 0; i <= sqrtp; ++i) {
        mp[prod] = i;
        prod = prod * a % p;
    }
    prod = 1;
    for (T i = 0; i <= sqrtp; ++i) {
        auto it = mp.find(prod);
        if (it != mp.end() && i * sqrtp - it->second > 0)
            return i * sqrtp - it->second;
        prod = prod * base % p;
    }
    return nullopt;
}

optional<ll> solve() {
    if (xx1 == t) {
        return 1;
    } else if (a == 0) {
        if (b % p == t)
            return 2;
        else
            return nullopt;
    } else if (a == 1) {
        auto [d, x, y] = exgcd(b, p);
        if ((b - xx1 + t) % d != 0)
            return nullopt;
        x *= (b - xx1 + t) / d;
        x = (x % (p / d) + (p / d)) % (p / d);
        if (x == 0)
            x += p / d;
        return x;
    } else {
        ll tmp = b * inverse((a - 1 + p) % p, p) % p;
        return bsgs(a, a * (tmp + t) % p * inverse(tmp + xx1, p) % p, p);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    while (n--) {
        cin >> p >> a >> b >> xx1 >> t;
        cout << solve().value_or(-1) << endl;
    }
    return 0;
}