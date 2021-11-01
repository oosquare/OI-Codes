#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2000 + 10;

int n, m, ans1, ans2;
int a[maxn][maxn], h[maxn][maxn], l[maxn][maxn], r[maxn][maxn], f[maxn][maxn];
int st[maxn], top;

void calc(int line) {
    top = 0;

    for (int i = 1; i <= m; ++i) {
        while (top > 0 && h[line][st[top]] >= h[line][i]) {
            f[line][st[top]] += min((i - 1) - st[top], r[line][st[top]] - 1);
            --top;
        }

        f[line][i] += min(i - st[top], l[line][i]);
        st[++top] = i;
    }
}

void preprocess() {
    for (int i = 1; i <= m; ++i)
        h[1][i] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] != a[i - 1][j])
                h[i][j] = h[i - 1][j] + 1;
            else
                h[i][j] = 1;
        }
    }

    for (int i = 1; i <= n; ++i)
        l[i][1] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            if (a[i][j] != a[i][j - 1])
                l[i][j] = l[i][j - 1] + 1;
            else
                l[i][j] = 1;
        }
    }

    for (int i = 1; i <= n; ++i)
        r[i][m] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j >= 1; --j) {
            if (a[i][j] != a[i][j + 1])
                r[i][j] = r[i][j + 1] + 1;
            else
                r[i][j] = 1;
        }
    }
}

int square(int x) {
    return x * x;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];

    preprocess();

    for (int i = 1; i <= n; ++i)
        calc(i);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ans1 = max(ans1, square(min(h[i][j], f[i][j])));
            ans2 = max(ans, h[i][j] * f[i][j]);
        }
    }

    cout << ans1 << endl;
    cout << ans2 << endl;
    return 0;
}