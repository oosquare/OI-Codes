#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template <typename T> using triple = tuple<T, T, T>;

ll k, m;

template <typename T> T multiply(T x, T y, T p) {
    T res = 0;
    for (; y != 0; y /= 2) {
        if (y % 2 == 1)
            res = (res + x) % p;
        x = (x + x) % p;
    }
    return res;
}

template <typename T> T power(T x, T y, T p) {
    T res = 1;
    for (; y != 0; y /= 2) {
        if (y % 2 == 1)
            res = multiply(res, x, p);
        x = multiply(x, x, p);
    }
    return res;
}

template <typename T> triple<T> exgcd(T a, T b) {
    if (b == 0) {
        return {a, 1, 0};
    } else {
        auto [d, x, y] = exgcd(b, a % b);
        return {d, y, x - a / b * y};
    }
}

template <typename T> T inverse(T a, T p) {
    return (get<1>(exgcd(a % p, p)) % p + p) % p;
}

template <typename T> optional<T> bsgs(T a, T b, T p) {
    a %= p;
    b %= p;
    T sqrtp = ceil(sqrt(p)), prod = b, base = power(a, sqrtp, p);
    unordered_map<T, T> mp;
    for (T i = 0; i <= sqrtp; ++i) {
        mp[prod] = i;
        prod = multiply(prod, a, p);
    }
    prod = 1;
    for (T i = 0; i <= sqrtp; ++i) {
        auto it = mp.find(prod);
        if (it != mp.end() && i * sqrtp - it->second > 0)
            return i * sqrtp - it->second;
        prod = multiply(prod, base, p);
    }
    return nullopt;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> m;
    auto res = bsgs(10LL, (k * 9 + 1) % m, m);
    cout << res.value() << endl;
    return 0;
}