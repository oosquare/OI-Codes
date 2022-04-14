#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 5e4 + 10;
constexpr int maxk = 22;

int n, k, a[maxn], l[maxn];
ll c[maxn], d[maxn], s[maxn];
ll f[maxk][maxn], g[maxk][maxn], x[maxn], y[maxn];
int q[maxn], front, back;

bool less1(int i, int j, ll k) {
    return 1LL * (y[j] - y[i]) <= 1LL * k * (x[j] - x[i]);
}

bool less2(int i, int j, int k) {
    return 1LL * (y[j] - y[i]) * (x[k] - x[j]) >= 1LL * (y[k] - y[j]) * (x[j] - x[i]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("bike.in", "r", stdin);
    freopen("bike.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i < n; ++i)
        cin >> l[i];
    for (int i = 1; i <= n; ++i)
        c[i] = c[i - 1] + a[i];
    for (int i = 2; i <= n; ++i)
        d[i] = d[i - 1] + l[i - 1];
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + 1LL * a[i] * d[i];
    for (int i = 1; i <= n; ++i)
        f[1][i] = c[i] * d[i] - s[i];
    for (int i = 1; i <= k; ++i) {
        if (i != 1) {
            front = 1, back = 0;
            for (int j = 1; j <= n; ++j) {
                x[j] = c[j];
                y[j] = g[i - 1][j] + s[j];
                while (front < back && less2(q[back - 1], q[back], j))
                    --back;
                q[++back] = j;
                while (front < back && less1(q[front], q[front + 1], d[j]))
                    ++front;
                f[i][j] = g[i - 1][q[front]] + 1LL * (c[j] - c[q[front]]) * d[j] - s[j] + s[q[front]];
            }
        }
        front = 1, back = 0;
        for (int j = 1; j <= n; ++j) {
            x[j] = d[j];
            y[j] = f[i][j] - s[j] + 1LL * c[j] * d[j];
            while (front < back && less2(q[back - 1], q[back], j))
                --back;
            q[++back] = j;
            while (front < back && less1(q[front], q[front + 1], c[j]))
                ++front;
            g[i][j] = f[i][q[front]] - 1LL * (c[j] - c[q[front]]) * d[q[front]] + s[j] - s[q[front]];
        }
    }
    cout << g[k][n] << endl;
    return 0;
}
