#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 210;
constexpr int maxm = 1e4 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

int t, n, m, a, b;
ll avg, g[maxm], x[maxm], s[maxm], f[maxn][maxm], c[maxn][maxm];
int que[maxm], front, back;

template <typename T>
inline T square(T x) {
    return x * x;
}

inline ll calc(int k, int j) {
    return f[k - 1][j] - g[k] * s[j];
}

void solve() {
    cin >> m >> n >> a >> b;
    avg = 0;
    for (int i = 1; i <= m; ++i)
        cin >> x[i], avg += x[i];
    avg /= m;
    for (int i = 1; i <= n; ++i)
        cin >> g[i];
    for (int i = 1; i <= m; ++i)
        s[i] = s[i - 1] + square(x[i] - avg);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            f[i][j] = oo;
    f[0][0] = 0;
    for (int k = 1; k <= n; ++k) {
        front = 1, back = 0;
        f[k][0] = 0;
        for (int i = k; i <= m; ++i) {
            while (front <= back && que[front] < i - b)
                ++front;
            if (i - a >= k - 1 && f[k - 1][i - a] < oo) {
                while (front <= back && calc(k, que[back]) >= calc(k, i - a))
                    --back;
                que[++back] = i - a;
            }
            if (front <= back) {
                int j = que[front];
                f[k][i] = f[k - 1][j] + g[k] * (s[i] - s[j]);
                c[k][i] = i - j;
            }
        }
    }
    ll sigma = oo, cnt = oo;
    for (int i = 1; i <= n; ++i)
        sigma = min(sigma, f[i][m]);
    for (int i = n; i >= 1; --i)
        if (f[i][m] == sigma)
            cnt = i;
    cout << sigma << " " << cnt << " " << c[cnt][m] << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
        solve();
    return 0;
}
