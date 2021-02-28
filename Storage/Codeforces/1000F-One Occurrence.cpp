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

constexpr int maxn = 5e5 + 5;
int arr[maxn], cnt[maxn], ans[maxn], n, m, blocksize;
query q[maxn];
int stk[maxn], pos[maxn], top;

#define blockid(x) (((x)-1) / blocksize + 1)

inline void merge(int x) {
    if (++cnt[arr[x]] == 1) {
        stk[++top] = arr[x];
        pos[arr[x]] = top;
    } else if (cnt[arr[x]] == 2) {
        stk[pos[arr[x]]] = stk[top];
        pos[stk[top]] = pos[arr[x]];
        stk[top--] = pos[arr[x]] = 0;
    }
}

inline void remove(int x) {
    if (--cnt[arr[x]] == 1) {
        stk[++top] = arr[x];
        pos[arr[x]] = top;
    } else if (cnt[arr[x]] == 0) {
        stk[pos[arr[x]]] = stk[top];
        pos[stk[top]] = pos[arr[x]];
        stk[top--] = pos[arr[x]] = 0;
    }
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
    m = read<int>();
    for (int i = 1; i <= m; ++i) {
        q[i].l = read<int>();
        q[i].r = read<int>();
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, [](const query &a, const query &b) {
        return (blockid(a.l) ^ blockid(b.l))
                   ? a.l < b.l
                   : ((a.r ^ b.r) ? (blockid(a.l) & 1) ^ (a.r < b.r) : 0);
    });
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (q[i].l < l)
            merge(--l);
        while (q[i].r > r)
            merge(++r);
        while (q[i].l > l)
            remove(l++);
        while (q[i].r < r)
            remove(r--);
        ans[q[i].id] = stk[top];
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}