#include <bits/stdc++.h>
using namespace std;

template <typename T> T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

struct query {
    int l, r, id;
};

constexpr int maxn = 50000 + 5;
query qs[maxn];
int arr[maxn], cnt[maxn], n, m, blocksize;
long long ans[maxn][2], res;

inline int blockid(int x) { return (x - 1) / blocksize + 1; }

inline void add(int x) {
    res += cnt[arr[x]]++;
}

inline void sub(int x) {
    res -= --cnt[arr[x]];
}

long long GCD(long long x, long long y) { return y == 0 ? x : GCD(y, x % y); }

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read<int>();
    m = read<int>();
    blocksize = sqrt(n);
    for (int i = 1; i <= n; ++i)
        arr[i] = read<int>();
    for (int i = 1; i <= m; ++i) {
        qs[i].l = read<int>();
        qs[i].r = read<int>();
        qs[i].id = i;
    }
    sort(qs + 1, qs + 1 + m, [](const query &a, const query &b) {
        return blockid(a.l) == blockid(b.l)
                   ? (a.r == b.r ? 0 : (blockid(a.l) & 1) ^ (a.r < b.r))
                   : a.l < b.l;
    });
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        if (qs[i].l == qs[i].r) {
            ans[qs[i].id][0] = 0;
            ans[qs[i].id][1] = 1;
            continue;
        }
        while (qs[i].l < l)
            add(--l);
        while (qs[i].r > r)
            add(++r);
        while (qs[i].l > l)
            sub(l++);
        while (qs[i].r < r)
            sub(r--);
        ans[qs[i].id][0] = res;
        ans[qs[i].id][1] = (1LL * (r - l) * (r - l + 1)) >> 1;
    }
    for (int i = 1; i <= m; ++i) {
        long long g = GCD(ans[i][0], ans[i][1]);
        printf("%lld/%lld\n", ans[i][0] / g, ans[i][1] / g);
    }
    return 0;
}