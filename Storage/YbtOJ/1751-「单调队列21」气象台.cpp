#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, ans = 1, x[maxn], y[maxn];
int l, r, q[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("tem.in", "r", stdin);
    freopen("tem.out", "w", stdout);
#endif
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) {
        while (l <= r && y[i] < x[q[l]])
            ++l;
        while (l <= r && x[i] >= x[q[r]])
            --r;
        q[++r] = i;
        ans = max(ans, i - q[l - 1]);
    }
    cout << ans << endl;
    return 0;
}
