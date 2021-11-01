#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e4 + 10;
constexpr int maxm = 500 + 10;

int n, m;
int k[maxn], p[maxn], x[maxn], sum[maxn * 2], mx;
int f[maxn][maxm][2], ans;
vector<int> val;

template <typename T> void update(T &x, T y) {
    if (x < y)
        x = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> k[i] >> p[i];

    for (int i = 1; i <= n; ++i)
        cin >> x[i];

    for (int i = 1; i <= n; ++i) {
        val.push_back(k[i]);
        val.push_back(x[i]);
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n; ++i) {
        k[i] = lower_bound(val.begin(), val.end(), k[i]) - val.begin() + 1;
        x[i] = lower_bound(val.begin(), val.end(), x[i]) - val.begin() + 1;
    }

    memset(f, ~0x3f, sizeof(f));
    sum[k[1]] += p[1];
    mx = p[1];
    f[1][0][0] = max(sum[x[1]], mx);
    f[1][1][1] = 0;

    for (int i = 2; i <= n; ++i) {
        int now = i, pre = i ^ 1;
        sum[k[i]] += p[i];
        mx = max(mx, p[i]);
        for (int j = 0; j <= m; ++j) {
            update(f[i][j][0], f[i - 1][j][0] + max(sum[x[i]], mx));
            update(f[i][j][0], f[i - 1][j][1] + 2 * max(sum[x[i]], mx));

            if (j > 0)
                update(f[i][j][1], f[i - 1][j - 1][0]);
        }
    }

    for (int i = 0; i <= m; ++i) {
        update(ans, f[n][i][0]);
        update(ans, f[n][i][1]);
    }

    cout << ans << endl;
    return 0;
}