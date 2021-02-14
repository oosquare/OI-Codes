#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000000 + 10;

int n, arr[maxn], f[maxn], ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    for (int i = 1; i <= n; ++i) {
        int m = 0;
        for (int j = 0; j <= 31; ++j)
            if (arr[i] & (1 << j))
                m = max(m, f[j] + 1);
        for (int j = 0; j <= 31; ++j)
            if (arr[i] & (1 << j))
                f[j] = m;
    }
    for (int i = 0; i <= 31; ++i)
        ans = max(ans, f[i]);
    cout << ans << endl;
    return 0;
}