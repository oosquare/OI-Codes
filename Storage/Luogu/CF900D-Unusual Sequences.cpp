#include <iostream>
#include <unordered_map>
using namespace std;

constexpr int mod = 1e9 + 7;

unordered_map<int, int> f;
int x, y;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

int solve(int x) {
    if (f.find(x) != f.end())
        return f[x];

    int res = power(2, x - 1);

    for (int d = 2; d * d <= x; ++d) {
        if (x % d)
            continue;

        res = (res - solve(x / d) + mod) % mod;

        if (d * d != x)
            res = (res - solve(d) + mod) % mod;
    }

    res = (res - solve(1) + mod) % mod;
    f[x] = res;
    return res;
}

int main() {
    f[1] = 1;
    cin >> x >> y;

    if (y % x) {
        cout << 0 << endl;
        return 0;
    }

    cout << solve(y / x) << endl;
    return 0;
}