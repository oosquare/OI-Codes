#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3005;
constexpr int maxm = 305;

int n, m, pt[maxm];
double p[maxn][maxm], ft[maxm], now[maxm], f[maxm][maxn];
double tmp[maxm], fsum[maxm][2], ans;

void calculate(int x) {
    ft[x] += now[x];
    ++pt[x];
    if (pt[x] > n) {
        now[x] = -1;
        return;
    }
    for (int i = 0; i <= n; ++i)
        tmp[i] = f[x][i];
    f[x][pt[x] - 1] = 0;
    for (int i = pt[x]; i <= n; ++i)
        f[x][i] = f[x][i - 1] * (1.0 - p[i][x]) + tmp[i - 1] * p[i][x];
    fsum[x][0] += f[x][n];
    fsum[x][1] += f[x][n] * pt[x];
    now[x] = fsum[x][1] + (1.0 - fsum[x][0]) * pt[x] - ft[x];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("coin.in", "r", stdin);
    freopen("coin.out", "w", stdout);
#endif
    int x;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> x, p[i][j] = 1.0 * x / 1000;
    for (int i = 1; i <= m; ++i) {
        f[i][0] = 1;
        for (int j = 1; j <= n; ++j)
            f[i][j] = f[i][j - 1] * (1.0 - p[j][i]);
        fsum[i][0] = f[i][n];
        calculate(i);
    }
    for (int t = 1; t <= n; ++t) {
        int id = 1;
        for (int i = 1; i <= m; ++i)
            if (now[i] > now[id])
                id = i;
        ans += now[id];
        calculate(id);
    }
    printf("%.11lf\n", ans);
    return 0;
}
