#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxn = 500000 + 10;

int n, k, val[maxn];
bool vis[maxn];
ll ans, c[maxn], tmp[maxn];

void calc(int start) {
    int m = 0, x = start;
    ll avg = 0;

    while (!vis[x]) {
        tmp[++m] = val[x];
        avg += val[x];
        vis[x] = true;
        x = (x + k) % n + 1;
    }

    avg /= m;

    for (int i = 2; i <= m; ++i)
        c[i] = c[i - 1] + avg - tmp[i];

    sort(c + 1, c + 1 + m);
    ll t = -c[(m + 1) / 2];

    for (int i = 1; i <= m; ++i)
        ans += abs(c[i] + t);
}

int main() {
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> val[i];

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            calc(i);

    cout << ans << endl;
    return 0;
}
