#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 16 + 10;
using ll = long long;

int n, k, s[maxn];
ll f[maxn][1 << 16], ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 0; i < n; ++i)
        cin >> s[i];

    for (int i = 0; i < n; ++i)
        f[i][1 << i] = 1;

    for (int st = 0; st < (1 << n); ++st) {
        for (int i = 0; i < n; ++i) {
            if (((st >> i) & 1) == 0)
                continue;

            for (int j = 0; j < n; ++j) {
                if (i == j || ((st >> j) & 1) == 0)
                    continue;

                if (abs(s[i] - s[j]) <= k)
                    continue;

                f[i][st] += f[j][st ^ (1 << i)];
            }
        }
    }

    for (int i = 0; i < n; ++i)
        ans += f[i][(1 << n) - 1];

    cout << ans << endl;
    return 0;
}