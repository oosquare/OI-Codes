#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200000 + 10;
constexpr int mod = 19260817;

using ll = long long;

int n, m;
ll sum[maxn], rsum[maxn], dis[maxn], rdis[maxn], cnt[maxn], rcnt[maxn];

ll calcToLeft(int x, int l, int r) {
    return ((sum[r] - sum[l - 1] + 2 * mod) - dis[x] * (cnt[r] - cnt[l - 1]) % mod + mod) % mod;
}

ll calcToRight(int x, int l, int r) {
    return ((rsum[l] - rsum[r + 1] + 2 * mod) - rdis[x] * (rcnt[l] - rcnt[r + 1]) % mod + mod) % mod;
}

ll calc(int x, int l, int r) {
    if (x < l) {
        return calcToLeft(x, l, r);
    } else if (x > r) {
        return calcToRight(x, l, r);
    } else {
        ll res = 0;
        if (l <= x - 1)
            res += calcToRight(x, l, x - 1);
        if (x + 1 <= r)
            res += calcToLeft(x, x + 1, r);
        res %= mod;
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 2; i <= n; ++i) {
        cin >> dis[i];
        rdis[i - 1] = dis[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> cnt[i];
        rcnt[i] = cnt[i];
    }
    for (int i = 1; i <= n; ++i) {
        (dis[i] += dis[i - 1]) %= mod;
        sum[i] = (sum[i - 1] + dis[i] * cnt[i]) % mod;
        (cnt[i] += cnt[i - 1]) %= mod;
    }
    for (int i = n; i >= 1; --i) {
        (rdis[i] += rdis[i + 1]) %= mod;
        rsum[i] = (rsum[i + 1] + rdis[i] * rcnt[i]) % mod;
        (rcnt[i] += rcnt[i + 1]) %= mod;
    }
    for (int i = 1; i <= m; ++i) {
        int x, l, r;
        cin >> x >> l >> r;
        cout << calc(x, l, r) << endl;
    }
    return 0;
}