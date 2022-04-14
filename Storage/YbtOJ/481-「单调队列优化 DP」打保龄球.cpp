#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e4 + 10;
constexpr int maxk = 510;

int pre[maxn], arr[maxn], f[maxn][maxk], que[maxn], back, front;
int n, k, w, t;

void solve() {
    int ans = -12345161;
    cin >> n >> k >> w;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    memset(f, -127 / 3, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n + w; i++)
        pre[i] = pre[i - 1] + arr[i];

    for (int i = 1; i <= k; i++) {
        front = 0, back = 1;
        f[0][i] = 0;
        que[1] = 0;
        int mx = -123245141;
        for (int j = 1; j <= n + w; j++) {
            if (j >= w)
                mx = max(f[j - w][i - 1], mx);
            while (front < back && j - que[front + 1] >= w)
                front++;
            f[j][i] =
                max(mx + pre[j] - pre[j - w],
                    f[que[front + 1]][i - 1] + pre[j] - pre[que[front + 1]]);
            while (front < back &&
                   f[j][i - 1] > f[que[back]][i - 1] + pre[j] - pre[que[back]])
                back--;
            que[++back] = j;
            ans = max(ans, f[j][i]);
        }
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("bowling.in", "r", stdin);
    freopen("bowling.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
        solve();
    return 0;
}
