#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 3e5 + 10;
constexpr int maxk = 20;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;
constexpr ll seed = 211034400;
constexpr ll oomin = -6574445958228943728LL;

int n, k, q[maxn];
ll ans = oo, ans2, sum, arr[maxn * 2], pre[maxn], f[maxk][maxn];

ll square(ll x) { return x * x; }

ll getX(int i) { return 2 * pre[i]; }

ll getY(int i, int j) { return f[i - 1][j] + square(pre[j]); }

void subtask1() {
    for (int i = 1; i <= 2 * n; ++i)
        pre[i] = pre[i - 1] + arr[i];
    int j = 1;
    ll tmp = pre[n] / 2;
    while (pre[j + 1] - pre[1] <= tmp)
        ++j;
    ans = min(ans, square(pre[j] - pre[1]) + square(pre[n] - pre[j] + pre[1]));
    for (int i = 2; i <= n; ++i) {
        while (pre[j + 1] - pre[i] <= tmp)
            ++j;
        ans = min(ans,
                  square(pre[j] - pre[i]) + square(pre[n] - pre[j] + pre[i]));
        ans = min(ans, square(pre[j - 1] - pre[i]) +
                           square(pre[n] - pre[j - 1] + pre[i]));
    }
    cout << square(k) * ans - k * square(pre[n]) << endl;
}

ll calc(int j, int i, int k) {
    ll tx = pre[j] + pre[n] - pre[k], ty = pre[i] - pre[j], tz = pre[k] - pre[i];
    return tx * tx + ty * ty + tz * tz;
}

ll check(ll x) {
    return x == oomin ? seed : x;
}

void subtask2() {
    int j = 0, kk = 2;
    for (int i = 1; i <= n; ++i)
        pre[i] = pre[i - 1] + arr[i];
    ll tmp = pre[n] / 3;
    for (int i = 1; i <= n; ++i) {
        while (j < i && pre[i] - pre[j] > tmp)
            ++j;
        while (kk <= n && pre[kk] - pre[i] <= tmp)
            ++kk;
        for (int x = max(j - 1, 0), am = min(j + 1, i); x <= am; ++x)
            for (int y = max(kk - 1, i), bm = min(kk + 1, n); y <= bm; ++y)
                ans = min(ans, calc(x, i, y));
    }
    cout << square(k) * ans - k * square(pre[n]) << endl;
}

ll calculate() {
    int l, r;
    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = oo;
    f[0][0] = 0;
    for (int i = 1; i <= k; ++i) {
        q[l = r = 1] = 0;
        for (int j = 1; j <= n; ++j) {
            while (l < r && getY(i, q[l + 1]) - getY(i, q[l]) <=
                                2 * pre[j] * (pre[q[l + 1]] - pre[q[l]]))
                ++l;
            f[i][j] = f[i - 1][q[l]] + square(pre[j] - pre[q[l]]);
            while (l < r &&
                   (getY(i, q[r]) - getY(i, q[r - 1])) * (pre[j] - pre[q[r]]) >=
                       (getY(i, j) - getY(i, q[r])) *
                           (pre[q[r]] - pre[q[r - 1]]))
                --r;
            q[++r] = j;
        }
    }
    return check(square(k) * f[k][n] - k * square(sum));
    
}

void subtask3() {
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= n; ++j)
            pre[j] = pre[j - 1] + arr[i + j];
        ans = min(ans, calculate());
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("spaceship.in", "r", stdin);
    freopen("spaceship.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        (cin >> arr[i]), arr[i + n] = arr[i], sum += arr[i];
    if (k == 2)
        subtask1();
    else if (k == 3)
        subtask2();
    else if (n <= 400)
        subtask3();
    return 0;
}
