#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 55;
constexpr int maxs = 1 << 14;

int n, cnt;
ll a[maxn], f[maxn][maxs], ans;
ll vaild[maxn]; 

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("orandxor.in", "r", stdin);
    freopen("orandxor.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int k = 1; k < maxs; ++k) {
        cnt = 0;
        for (int i = 1; i <= n; ++i)
            if ((k | a[i]) == k)
                vaild[++cnt] = a[i];
        f[0][0] = 1;
        for (int i = 1; i <= cnt; ++i)
            for (int j = 0; j <= k; ++j)
                f[i][j] = f[i - 1][j] + f[i - 1][j ^ vaild[i]];
        ans += f[cnt][k];
    }
    cout << ans << endl;
    return 0;
}
