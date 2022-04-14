#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int mod = 998244353;

int h[maxn], inv[maxn], n, ans = 1, len;
char str[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif
    inv[1] = 1;
    for (int i = 2; i < maxn; ++i)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    h[0] = 1;
    for (int i = 1; i < maxn; ++i)
        h[i] = 1LL * h[i - 1] * (4 * i - 2) % mod * inv[i + 1] % mod;
    cin >> n >> (str + 1);
    len = 1;
    for (int i = 2; i <= n; ++i) {
        if (str[i] == str[i - 1]) {
            ++len;
        } else {
            ans  = 1LL * ans * h[len] % mod;
            len = 1;
        }
    }
    ans = 1LL * ans * h[len] % mod;
    cout << ans << endl;
    return 0;
}
