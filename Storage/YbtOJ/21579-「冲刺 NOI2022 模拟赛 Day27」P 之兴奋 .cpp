#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 3e5 + 10;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
long long t[MAX_N], s[MAX_N];
long long buf[2][MAX_N], *f = buf[0], *g = buf[1], h[MAX_N];
long long p[MAX_N], q[MAX_N];
int que[MAX_N], fr, bk;
long long ans[MAX_N];

inline long long getY(int i) {
    return f[i] + (1ll * i * i - i) / 2 + s[i];
}

inline double slope(int i, int j) {
    return 1.0 * (getY(j) - getY(i)) / (j - i);
}

inline long long getY1(int i) {
    return g[i + 1] + (1ll * i * i + i) / 2 - s[i];
}

inline double slope1(int i, int j) {
    return 1.0 * (getY1(j) - getY1(i)) / (j - i);
}

inline long long getY2(int i) {
    return f[i] + (1ll * i * i - i) / 2 + s[i];
}

inline double slope2(int i, int j) {
    return 1.0 * (getY2(j) - getY2(i)) / (j - i);
}
// 求 f, g
void dp() {
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + t[i];

    fr = bk = 1;
    que[1] = 0;

    for (int i = 1; i <= n; ++i) {
        while (fr < bk && slope(que[bk - 1], que[bk]) <= i)
            --bk;

        int j = que[bk];
        f[i] = max(f[i - 1], f[j] + 1ll * (i - j) * (i - j + 1) / 2 - s[i] + s[j]);

        while (fr < bk && slope(que[bk - 1], que[bk]) <= slope(que[bk], i))
            --bk;

        que[++bk] = i;     
    }
}
// 分治
void divide(int l, int r) {
    if (l == r) {
        h[l] = 1 - t[l];
        return;
    }

    int mid = (l + r) / 2;
    divide(l, mid);
    divide(mid + 1, r);
    
    fr = 1;
    bk = 0;
    long long mx = -INF;
    // 求 p
    for (int i = mid + 1; i <= r; ++i) {
        while (fr < bk && slope1(que[bk - 1], que[bk]) <= slope1(que[bk], i))
            --bk;

        que[++bk] = i;
    }
    // 求 q
    for (int i = l - 1; i < mid; ++i) {
        while (fr < bk && slope1(que[bk - 1], que[bk]) <= i)
            --bk;

        int j = que[bk];
        p[i + 1] = f[i] + g[j + 1] + 1ll * (j - i) * (j - i + 1) / 2 - s[j] + s[i];
        mx = max(mx, p[i + 1]);
        h[i + 1] = max(h[i + 1], mx);
    }

    fr = 1;
    bk = 0;
    mx = -INF;

    for (int i = l - 1; i < mid; ++i) {
        while (fr < bk && slope2(que[bk - 1], que[bk]) <= slope2(que[bk], i))
            --bk;

        que[++bk] = i;
    }

    for (int i = r; i >= mid + 1; --i) {
        while (fr < bk && slope2(que[fr], que[fr + 1]) >= i)
            ++fr;

        int j = que[fr];
        q[i] = g[i + 1] + f[j] + 1ll * (i - j) * (i - j + 1) / 2 - s[i] + s[j]; 
        mx = max(mx, q[i]);
        h[i] = max(h[i], mx);
    }
}

int main() {
    std::freopen("excitement.in", "r", stdin);
    std::freopen("excitement.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> t[i];

    dp();
    swap(f, g);
    reverse(t + 1, t + 1 + n);
    dp();
    reverse(t + 1, t + 1 + n);
    swap(f, g);
    reverse(g + 1, g + 1 + n);

    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + t[i];

    divide(1, n);

    cin >> m;

    for (int i = 1; i <= m; ++i) {
        int p, x;
        cin >> p >> x;
        ans[i] = max(f[p - 1] + g[p + 1], h[p] + t[p] - x);
    }

    long long v;
    std::cin >> v;

    for (int i = 1; i <= m; ++i)
        std::cout << (ans[i] ^ v) << std::endl;

    return 0;
}
