#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int maxk = 100 + 10;
constexpr double oo = 1e18;
constexpr double eps = 1e-3;

int n, k, v[maxn], w[maxn];
vector<int> tree[maxn];
double a[maxn], f[maxn][maxk], tmp[maxk], sum, res;
int sze[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

template <typename T> void update(T &x, T y) {
    if (x < y)
        x = y;
}

void dfs(int x, int fa) {
    f[x][0] = 0;
    f[x][1] = a[x];
    sze[x] = 1;
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x);
        sze[x] += sze[y];
        for (int i = 1; i <= min(sze[x], n); ++i)
            tmp[i] = exchange(f[x][i], -oo);
        for (int i = 1; i <= min(sze[x], n); ++i)
            for (int j = 0; j <= min(sze[y], i - 1); ++j)
                update(f[x][i], tmp[i - j] + f[y][j]);
    }
}

bool check(double x) {
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = -oo;
    for (int i = 1; i <= n; ++i)
        a[i] = v[i] - x * w[i];
    dfs(1, 0);
    double res = -oo;
    for (int i = 1; i <= n; ++i)
        for (int j = k; j <= n; ++j)
            res = max(res, f[i][j]);
    return res >= -eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        sum += v[i];
    }
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    double l = 0, r = sum, ans = -oo;
    while (abs(r - l) > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}