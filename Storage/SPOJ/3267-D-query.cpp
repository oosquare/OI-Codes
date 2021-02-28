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

constexpr int maxn = 30000 + 5;
constexpr int maxv = 1e6 + 5;
constexpr int maxq = 200000 + 5;
query qs[maxq];
int arr[maxn], cnt[maxv], ans[maxq], n, q, res, blocksize;

inline int blockid(int x) { return (x - 1) / blocksize + 1; }

inline void add(int x) {
    ++cnt[arr[x]];
    if (cnt[arr[x]] == 1)
        ++res;
}

inline void sub(int x) {
    --cnt[arr[x]];
    if (!cnt[arr[x]])
        --res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read<int>();
    blocksize = sqrt(n);
    for (int i = 1; i <= n; ++i)
        arr[i] = read<int>();
    q = read<int>();
    for (int i = 1; i <= q; ++i) {
        qs[i].l = read<int>();
        qs[i].r = read<int>();
        qs[i].id = i;
    }
    sort(qs + 1, qs + 1 + q, [](const query &a, const query &b) {
        return blockid(a.l) == blockid(b.l)
                   ? (a.r == b.r ? 0 : (blockid(a.l) & 1) ^ (a.r < b.r))
                   : a.l < b.l;
    });
    int l = 1, r = 0;
    for (int i = 1; i <= q; ++i) {
        while (qs[i].l < l)
            add(--l);
        while (qs[i].r > r)
            add(++r);
        while (qs[i].l > l)
            sub(l++);
        while (qs[i].r < r)
            sub(r--);
        ans[qs[i].id] = res;
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}