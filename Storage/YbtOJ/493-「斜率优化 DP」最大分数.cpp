#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 3e5 + 10;

int n, m, t[maxn], p[maxn], v[maxn], st[maxn], top;
ll f[maxn], g[maxn], h[maxn], ml[maxn], mr[maxn], sum[maxn];
ll x[maxn], y[maxn];

bool sless(int i, int j, int k) {
    return (y[j] - y[i]) * (x[k] - x[i]) <= (y[k] - y[i]) * (x[j] - x[i]);
}

ll calc(int tid, int i) {
    return y[tid] - x[tid] * 2 * i;
}

void DP(ll f[]) {
    f[0] = x[0] = y[0] = 0;
    st[top = 1] = 0;
    for (int i = 1; i <= n; ++i) {
        while (top >= 2 && calc(st[top], i) <= calc(st[top - 1], i))
            --top;
        f[i] = max(f[i - 1], calc(st[top], i) - sum[i] + 1LL * i * (i + 1));
        x[i] = i;
        y[i] = f[i] + 1LL * i * (i - 1) + sum[i];
        while (top >= 2 && sless(st[top - 1], st[top], i))
            --top;
        st[++top] = i;
    }
}

void divide(int l, int r) {
    if (l == r) {
        h[l] = max(h[l], f[l - 1] + g[l + 1] + 2 - t[l]);
        return;
    }
    int mid = (l + r) / 2;
    x[l - 1] = l - 1;
    y[l - 1] = f[l - 1] + 1LL * (l - 1) * (l - 2) + sum[l - 1];
    st[top = 1] = l - 1;
    for (int i = l; i <= mid - 1; ++i) {
        x[i] = i;
        y[i] = f[i] + 1LL * i * (i - 1) + sum[i];
        while (top >= 2 && sless(st[top - 1], st[top], i))
            --top;
        st[++top] = i;
    }
    for (int i = mid + 1; i <= r; ++i) {
        while (top >= 2 && calc(st[top], i) <= calc(st[top - 1], i))
            --top;
        mr[i] = calc(st[top], i) - sum[i] + 1LL * i * (i + 1);
    }
    for (int i = l; i <= mid; ++i)
        if (i != l + r - i)
            swap(t[i], t[l + r - i]);
    if ((r - l) % 2 == 0)
        --mid;
    for (int i = l; i <= r; ++i)
        sum[i] = sum[i - 1] + t[i];
    
    x[l - 1] = l - 1;
    y[l - 1] = g[r + 1] + 1LL * (l - 1) * (l - 2) + sum[l - 1];
    st[top = 1] = l - 1;
    for (int i = l; i <= mid - 1; ++i) {
        x[i] = i;
        y[i] = g[l + r - i] + 1LL * i * (i - 1) + sum[i];
        while (top >= 2 && sless(st[top - 1], st[top], i))
            --top;
        st[++top] = i;
    }
    for (int i = mid + 1; i <= r; ++i) {
        while (top >= 2 && calc(st[top], i) <= calc(st[top - 1], i))
            --top;
        ml[l + r - i] = calc(st[top], i) - sum[i] + 1LL * i * (i + 1);
    }
    for (int i = l; i <= mid; ++i)
        if (i != l + r - i)
            swap(t[i], t[l + r - i]);

    mid = (l + r) / 2;
    for (int i = l; i <= mid; ++i)
        ml[i] += f[i - 1];
    for (int i = mid + 1; i <= r; ++i)
        mr[i] += g[i + 1];
    for (int i = l; i <= r; ++i)
        sum[i] = sum[i - 1] + t[i];
    for (int i = l + 1; i <= mid; ++i)
        ml[i] = max(ml[i], ml[i - 1]);
    for (int i = r - 1; i >= mid + 1; --i)
        mr[i] = max(mr[i], mr[i + 1]);
    for (int i = l; i <= mid; ++i)
        h[i] = max(h[i], ml[i]);
    for (int i = mid + 1; i <= r; ++i)
        h[i] = max(h[i], mr[i]);

    divide(l, mid), divide(mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("score.in", "r", stdin);
    freopen("score.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> t[i], t[i] *= 2;
    cin >> m;
    for (int i = 1; i <= m; ++i)
        cin >> p[i] >> v[i], v[i] *= 2;
    
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + t[i];
    DP(f);
    for (int i = 1; i <= n / 2; ++i)
        swap(t[i], t[n - i + 1]);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + t[i];
    DP(g);
    for (int i = 1; i <= n / 2; ++i)
        swap(t[i], t[n - i + 1]);
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + t[i];
    for (int i = 1; i <= n / 2; ++i)
        swap(g[i], g[n - i + 1]);

    memset(h, ~0x3f, sizeof(h));
    divide(1, n);

    for (int i = 1; i <= m; ++i)
        cout << (max(f[p[i] - 1] + g[p[i] + 1], h[p[i]] + t[p[i]] - v[i]) / 2) << endl;
        
    return 0;
}
