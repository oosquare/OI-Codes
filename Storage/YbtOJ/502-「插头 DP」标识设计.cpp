#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 30 + 2;
constexpr int maxs = 4500;

typedef long long ll;

map<int, int> mp;
char a[maxn][maxn];
int n, m, num[maxs], cnt = 0;
ll f[maxn][maxn][4][maxs][2];

ll DP(int x, int y, int re, int s, bool r) {
    ll &res = f[x][y][re][s][r];
    if (~res) return res;
    int status = num[s];
    if (x == n) {
        if (!re && !status) return res = 1;
        return res = 0;
    }
    if (y == m) {
        if (r) return res = 0;
        return res = DP(x + 1, 0, re, s, 0);
    }
    if (status & (1 << y)) {
        if (a[x][y] == '#' || r) return res = 0;
        return res = DP(x, y + 1, re, s, 0) +
                     DP(x, y + 1, re, mp[status ^ (1 << y)], 1);
    }
    if (r) {
        if (a[x][y] == '#') return res = 0;
        return res = DP(x, y + 1, re, s, 1) + DP(x, y + 1, re, s, 0);
    }
    res = DP(x, y + 1, re, s, r);
    if (a[x][y] == '.' && re > 0 && y < m - 1)
        res += DP(x, y + 1, re - 1, mp[status | (1 << y)], r);
    return res;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("logo.in", "r", stdin);
    freopen("logo.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    mp[0] = ++cnt, num[cnt] = 0;
    for (int i = 0, s1, s2, s3; i < m - 1; ++i) {
        s1 = 1 << i, mp[s1] = ++cnt, num[cnt] = s1;
        for (int j = i + 1; j < m - 1; ++j) {
            s2 = s1 | (1 << j), mp[s2] = ++cnt, num[cnt] = s2;
            for (int k = j + 1; k < m - 1; ++k)
                s3 = s2 | (1 << k), mp[s3] = ++cnt, num[cnt] = s3;
        }
    }
    memset(f, -1, sizeof(f));
    cout << DP(0, 0, 3, 1, 0) << endl;
    return 0;
}
