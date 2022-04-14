#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 1000 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

struct Fish {
    int a, p, t;

    bool operator<(Fish rhs) {
        return a < rhs.a;
    }
};

int c, n, k;
ll f[2 * maxn];
Fish fishes[maxn];

void solve() {
    cin >> n >> k;
    int maxp = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> fishes[i].a >> fishes[i].p >> fishes[i].t;
        maxp = max(maxp, fishes[i].p);
    }
    sort(fishes + 1, fishes + 1 + n);
    if (k == 1) {
        int ans = oo;
        for (int i = 1; i <= n; ++i)
            if (fishes[i].a == 0 && fishes[i].p >= 1)
                ans = min(ans, fishes[i].t);
        cout << ans << endl;
        return; 
    }

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = fishes[i].p + fishes[i].a; j <= 2 * k - 1 && j - maxp <= k; ++j)
            f[j] = min(f[j], f[j - fishes[i].p] + fishes[i].t);
    ll ans = oo;
    for (int i = k; i <= 2 * k - 1; ++i)
        ans = min(ans, f[i]);
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("frenzy.in", "r", stdin);
    freopen("frenzy.out", "w", stdout);
#endif
    cin >> c;
    while (c--)
        solve();
    return 0;
}
