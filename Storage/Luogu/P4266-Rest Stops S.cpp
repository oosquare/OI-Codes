#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

using ll = long long;

struct Station {
    int x, c;

    bool operator<(const Station &rhs) const {
        return c > rhs.c;
    }
};

Station st[maxn];
int n, l, rf, rb, now;
ll ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> l >> n >> rf >> rb;    
    for (int i = 1; i <= n; ++i)
        cin >> st[i].x >> st[i].c;
    sort(st + 1, st + 1 + n);
    for (int i = 1; i <= n; ++i) {
        if (now < st[i].x) {
            ans += 1LL * (rf - rb) * (st[i].x - now) * st[i].c;
            now = st[i].x;
        }
    }
    cout << ans << endl;
    return 0;
}