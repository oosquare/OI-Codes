#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

typedef long long ll;

int n, n0;
ll a[maxn], b[maxn], m;
ll maxa[maxn], minb[maxn][20], s[maxn];
int loglv[maxn];
int q[maxn];
ll f[maxn];
multiset<ll> ss;

ll query(int l, int r) {
    int k = loglv[r - l + 1];
    return min(minb[l][k], minb[r - (1 << k) + 1][k]);
}

bool check(ll mid) {
    ss.clear();
    memset(f, 0x3f, sizeof(f));

    int front, back;
    q[front = back = 1] = 0;
    f[0] = 0;

    int last = 0;

    for (int i = 1; i <= n; ++i) {
        while (front <= back && s[i] - s[q[front]] > mid) {
            if (front < back)
                ss.erase(ss.find(f[q[front]] + a[q[front + 1]]));
            ++front;
        }
        while (front <= back && a[q[back]] < a[i]) {
            if (front < back)
                ss.erase(ss.find(f[q[back - 1]] + a[q[back]]));
            --back;
        }
        if (front <= back)
            ss.insert(f[q[back]] + a[i]);
        q[++back] = i;

        while (last < i && s[i] - s[last] > mid)
            ++last;
        if (last == q[front])
            f[i] = f[last] + a[q[front + 1]];
        else
            f[i] = f[last] + a[q[front]];
        if (front < back)
            f[i] = min(f[i], *ss.begin());
    }
    return f[n] <= m;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n0 >> m;
    for (int i = 1; i <= n0; ++i) {
        cin >> a[i] >> b[i];
        minb[i][0] = b[i];
    }
    maxa[n0] = n0;
    for (int i = n0 - 1; i >= 1; --i)
        maxa[i] = a[i] > a[maxa[i + 1]] ? i : maxa[i + 1];
    loglv[0] = -1;
    for (int i = 1; i <= n0; ++i)
        loglv[i] = loglv[i / 2] + 1;
    for (int j = 1; j <= 18; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n0; ++i)
            minb[i][j] = min(minb[i][j - 1], minb[i + (1 << (j - 1))][j - 1]);
    int tmp = 0;
    for (int i = 1; i <= n0;) {
        int j;
        for (j = i; j < n0 && a[maxa[j + 1]] >= query(i, j); j = maxa[j + 1])
            ;
        a[++tmp] = a[i];
        b[tmp] = b[i];
        for (i = i + 1; i <= j; ++i) {
            a[tmp] = max(a[tmp], a[i]);
            b[tmp] += b[i];
        }
    }
    n = tmp;
    ll l = 0, r = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        l = max(l, b[i]);
        r += b[i];
        s[i] = s[i - 1] + b[i];
    }
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
