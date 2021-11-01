#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 100 + 10;
constexpr int maxt = 2000 + 10;

struct Cheese {
    int v, h;
};

int n, t, k;
Cheese cheese[maxn];
ll f[maxt], ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> t >> k;

    for (int i = 1; i <= n; ++i)
        cin >> cheese[i].v >> cheese[i].h;

    for (int i = 1; i <= n; ++i)
        for (int j = cheese[i].h; j <= t * 5 / 4; ++j)
            f[j] = max(f[j], f[j - cheese[i].h] + cheese[i].v);

    ans = f[t];

    for (int i = 1; i <= n; ++ i)
        if (cheese[i].h >= k)
            ans = max(ans, f[(t - cheese[i].h) * 5 / 4] + cheese[i].v);

    cout << ans << endl;
    return 0;
}