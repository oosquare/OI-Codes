#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxn = 5e5 + 10;

struct Store {
    int id;
    ll c;
};

int n, nxt[maxn], top;
ll ans, s[maxn], now, t, d[maxn], p[maxn];
Store stores[maxn];

int main () {
    freopen("wayhome.in", "r", stdin);
    freopen("wayhome.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> t;

    for (int i = 1; i <= n; ++i) {
        cin >> d[i] >> p[i - 1];

        if (d[i] > t) {
            cout << -1 << endl;
            return 0;
        }
        
        s[i] = s[i - 1] + d[i];
    }
    
    stores[++top].c = 0;
    stores[top].id = n;
    
    for (int i = n - 1; i >= 0; --i) {
        while (top && stores[top].c > p[i])
            --top;

        if (!top || s[stores[top].id] - s[i] > t)
            nxt[i] = 0;

        else
            nxt[i] = stores[top].id;

        stores[++top].id = i;
        stores[top].c = p[i];
    }
    
    for (int i = 0; i < n;) {
        if (nxt[i]) {
            if (now < s[nxt[i]] - s[i]) {
                ans += 1LL * p[i] * (s[nxt[i]] - s[i] - now);
                now = 0;
            } else {
                now -= s[nxt[i]] - s[i];
            }
            
            i = nxt[i];
        } else {
            if (now < min(t, s[n] - s[i])) {
                ans += 1LL * p[i] * (min(t, s[n] - s[i]) - now);
                now = min(t, s[n] - s[i]) - d[i + 1];
            } else {
                now -= d[i + 1];
            }
            
            ++i;
        }
    }

    cout << ans << endl;
    return 0;
}
