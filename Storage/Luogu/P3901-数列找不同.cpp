#include <bits/stdc++.h>
using namespace std;

inline char gc() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T> T read() {
    T x = 0, s = 1;
    char c = gc();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = gc();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = gc();
    }
    return x * s;
}

struct query {
    int l, r, id;
};

constexpr int maxn = 1e5 + 5;
query q[maxn];
int arr[maxn], cnt[maxn], ans[maxn], res, n, m, blocksize;

inline int blockid(int x) { return (x - 1) / blocksize + 1; }

inline void add(int x) { res += (++cnt[arr[x]]) == 1; }

inline void sub(int x) { res -= (--cnt[arr[x]]) == 0; }

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read<int>();
    blocksize = sqrt(n);
    m = read<int>();
    for (int i = 1; i <= n; ++i)
        arr[i] = read<int>();
    for (int i = 1; i <= m; ++i)
        q[i] = {read<int>(), read<int>(), i};
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
        ans[q[i].id] = res == r - l + 1 ? 1 : 0;
    }
    for (int i = 1; i <= m; ++i)
        printf("%s\n", ans[i] ? "Yes" : "No");
    return 0;
}