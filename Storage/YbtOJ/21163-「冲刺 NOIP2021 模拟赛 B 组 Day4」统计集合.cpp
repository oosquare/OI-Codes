#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr int mod = 1e9 + 7;

int n, a[maxn], s[maxn], power[maxn], ans;

inline int sum(int l, int r) {
    return (s[r] - s[l - 1] + mod) % mod;
}

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    sort(a + 1, a + 1 + n);

    for (int i = 1; i <= n; ++i)
        s[i] = (s[i - 1] + a[i]) % mod;

    power[0] = 1;

    for (int i = 1; i <= n; ++i)
        power[i] = power[i - 1] * 2 % mod;

    for (int d = 0; d <= n - 2; ++d)
        ans = (ans + 1ll * (sum(d + 2, n) - sum(1, n - d - 1) + mod) % mod * power[d] % mod) % mod;

    cout << ans << endl;
    return 0;
}
