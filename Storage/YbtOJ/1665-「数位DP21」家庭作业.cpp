#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 50 + 10;
constexpr int mod = 1e9 + 3;

int n;
ll k, m[maxn], f[maxn][maxn][2], power[maxn];

bool get(int x, int p) {
    return 1 & (x >> p);
}

ll DP(int id, int val, int len) {
    val &= (~((1 << len) - 1));
    if (id == n + 1)
        return val == 0;
    int x = get(val, len);
    if (f[id][len][x] != -1)
        return f[id][len][x];
    ll ans = 0;
    int res = 0;
    for (int i = 31; i >= 0; --i) {
        if (get(m[id], i) == 1) {
            ans = (ans + DP(id + 1, val ^ res, max(len, i)) * power[min(len, i)] % mod) % mod;
            res |= (1 << i);
        }
    }
    f[id][len][x] = ans;
    return ans;
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        cin >> m[i];
        ++m[i];
    }
    memset(f, -1, sizeof(f));
    cout << DP(1, k, 0) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("hom.in", "r", stdin);
    freopen("hom.out", "w", stdout);
#endif
    power[0] = 1;
    for (int i = 1; i < maxn; ++i)
        power[i] = power[i - 1] * 2 % mod;
    while (cin >> n >> k && (n != 0 || k != 0))
        solve();
    return 0;
}
