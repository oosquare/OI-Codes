#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;

typedef long long ll;

int n;
ll f[maxn], suf[maxn], pos[maxn], cnt[maxn], cost[maxn], dis[maxn];
int que[maxn], l, r;

ll X(int i) {
    return cnt[i];
}

ll Y(int i) {
    return f[i] + suf[i + 1];
}

ll calc(int j, int i) {
    return (suf[j + 1] - suf[i + 1]) - (cnt[i] - cnt[j]) * dis[i];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> pos[i] >> cnt[i] >> cost[i], cnt[i] += cnt[i - 1];
    for (int i = 1; i <= n; ++i)
        dis[i] = pos[n] - pos[i];
    for (int i = n; i >= 1; --i)
        suf[i] = suf[i + 1] + (cnt[i] - cnt[i - 1]) * dis[i];
    
    que[l = r = 1] = 0;
    for (int i = 1; i <= n; ++i) {
        while (l < r && (Y(que[l + 1]) - Y(que[l])) <= (-dis[i]) * (X(que[l + 1]) - X(que[l])))
            ++l;
        f[i] = f[que[l]] + calc(que[l], i) + cost[i];
        while (l < r && (Y(que[r]) - Y(que[r - 1])) * (X(i) - X(que[r])) >= (X(que[r]) - X(que[r - 1])) * (Y(i) - Y(que[r])))
            --r;
        que[++r] = i;
    }
    cout << f[n] << endl;
    return 0;
}