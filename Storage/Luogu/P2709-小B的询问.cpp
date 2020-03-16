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

constexpr int maxn = 5e4 + 5;
typedef long long ll;

query q[maxn];
int arr[maxn], cnt[maxn], n, m, k, blocksize;
ll res, ans[maxn];

template <typename T> inline T square(T x) { return x * x; }

inline int blockid(int x) { return (x - 1) / blocksize + 1; }

inline void add(int x) {
    ++cnt[arr[x]];
    res += square(cnt[arr[x]]) - square(cnt[arr[x]] - 1);
}

inline void sub(int x) {
    --cnt[arr[x]];
    res += square(cnt[arr[x]]) - square(cnt[arr[x]] + 1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read<int>();
    m = read<int>();
    k = read<int>();
    blocksize = sqrt(n);
    for (int i = 1; i <= n; ++i)
        arr[i] = read<int>();
    for (int i = 1; i <= m; ++i) {
        q[i].l = read<int>();
        q[i].r = read<int>();
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, [](const query &a, const query &b) {
        return blockid(a.l) == blockid(b.l)
                   ? (a.r == b.r ? 0 : (blockid(a.l) & 1) ^ (a.r < b.r))
                   : a.l < b.l;
    });
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (q[i].l < l)
            add(--l);
        while (q[i].r > r)
            add(++r);
        while (q[i].l > l)
            sub(l++);
        while (q[i].r < r)
            sub(r--);
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}