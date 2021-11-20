#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxm = 50 + 10;
constexpr int mod = 1e9 + 7;

int t, m;
ll n, a[maxm];
int x[maxm], y[maxm];

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

int lagrange(ll x0, int n) {
    int ans = 0;

    for (int i = 0; i <= n; ++i) {
        int num = 1, den = 1;

        for (int j = 0; j <= n; ++j) {
            if (i == j)
                continue;

            num = 1ll * num * (x0 - x[j]) % mod;
            den = 1ll * den * (x[i] - x[j]) % mod;
        }

        ans = (1ll * ans + 1ll * y[i] * num % mod * power(den, mod - 2) % mod) % mod;
    }

    return (ans + mod) % mod;
}

int calc(ll x0) {
    if (x0 <= m + 2)
        return y[x0];

    return lagrange(x0, m + 2);
}

int solve() {
    int ans = 0;

    for (int i = 1; i <= m + 2; ++i) {
        x[i] = i;
        y[i] = (y[i - 1] + power(i, m + 1)) % mod;
    }

    for (int i = 1; i <= m; ++i) {
        ans = (ans + calc(n)) % mod;

        for (int j = i; j <= m; ++j)
            ans = (ans - power(a[j], m + 1) + mod) % mod;

        for (int j = i + 1; j <= m; ++j)
            a[j] -= a[i];

        n -= a[i];
    }

    if (n != 0)
        ans = (ans + calc(n)) % mod;

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;

    while (t--) {
        cin >> n >> m;

        for (int i = 1; i <= m; ++i)
            cin >> a[i];

        sort(a + 1, a + 1 + m);
        cout << solve() << endl;
    }

    return 0;
}