#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3 + 10;

int n, ans, a[maxn], f[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            f[i][j] = f[i - 1][j] + (a[i] == i - j);
            if (j > 0)
                f[i][j] = max(f[i][j], f[i - 1][j - 1]);
        }
    }
    for (int i = 0; i <= n; ++i)
        ans = max(ans, f[n][i]);
    cout << ans << endl;
    return 0;
}