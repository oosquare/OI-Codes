#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int maxm = 20000 + 10;

int s, n, m, f[maxm];
pair<int, int> info[maxn][maxn];

int &v(int i, int j) { return info[i][j].first; }

int &w(int i, int j) { return info[i][j].second; }

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> s >> n >> m;
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= n; ++j) {
            int a;
            cin >> a;
            v(j, i) = 2 * a + 1;
            w(j, i) = j;
        }
    }
    for (int i = 1; i <= n; ++i)
        sort(info[i] + 1, info[i] + 1 + s);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= s; ++j)
            w(i, j) += w(i, j - 1);
    for (int i = 1; i <= n; ++i)
        for (int k = m; k >= 0; --k)
            for (int j = 1; j <= s; ++j)
                if (k >= v(i, j))
                    f[k] = max(f[k], f[k - v(i, j)] + w(i, j));
    int ans = 0;
    for (int i = 0; i <= m; ++i)
        ans = max(ans, f[i]);
    cout << ans << endl;
    return 0;
}