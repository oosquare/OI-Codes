#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200 + 10;
constexpr int maxv = 2000 + 10;
constexpr int mod = 1e9 + 7;

long long f[2][maxn][maxv];
int n, k, s[maxn], ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("group.in", "r", stdin);
    freopen("group.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> s[i];
    sort(s + 1, s + 1 + n);
    f[0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
        int now = (i + 1)  % 2, last = i % 2;
        for (int j = 0; j <= n; ++j)
            for (int l = 0; l <= k; ++l)
                f[now][j][l] = 0;
        for (int j = 0; j <= i; ++j) {
            for (int l = 0; l <= k; ++l) {
                if (f[last][j][l] == 0)
                    continue;
                int l2 = l + (s[i + 1] - s[i]) * j;
                if (l2 > k)
                    break;
                //åç¬ä½ä¸ºä¸ä¸ªç»ææå¥ä¸ä¸ªå·²æçç»ï¼ä¸ä¸ä½ä¸ºæå¤§å¼ï¼éè¦å¡«æ°çç»ä¸å
                (f[now][j][l2] += 1LL * f[last][j][l] * (j + 1)) %= mod;
                //æ°å»ºä¸ä¸ªç»å¹¶å¡«å¥èªå·±ï¼éè¦å¡«æ°çç»å¢å 1
                (f[now][j + 1][l2] += f[last][j][l]) %= mod;
                //æå¥ä¸ä¸ªç»å¹¶ä½ä¸ºæå¤§å¼ï¼éè¦å¡«æ°çç»åå°1
                if (j > 0)
                    (f[now][j - 1][l2] += 1LL * f[last][j][l] * j) %= mod;
            }
        }
    }
    for (int i = 0; i <= k; ++i)
        ans = (ans + f[n % 2][0][i]) % mod;
    cout << ans << endl;
    return 0;
}
