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
    int l, r, max, min, id;
};

constexpr int maxn = 100000 + 5;
int arr[maxn], cnt[2][maxn], ans[2][maxn], n, m, blocksize;
query q[maxn];

#define blockid(x) (((x) - 1) / blocksize + 1)

#define lowbit(x) ((x) & -(x))

inline void modify(int id, int pos, int val) {
    for (; pos <= 100000; pos += lowbit(pos))
        cnt[id][pos] += val;
}

inline int sum(int id, int pos) {
    int res = 0;
    for (; pos; pos -= lowbit(pos))
        res += cnt[id][pos];
    return res;
}

inline void add(int x) {
    modify(0, arr[x], 1);
    if (sum(0, arr[x]) - sum(0, arr[x] - 1) == 1)
        modify(1, arr[x], 1);
}

inline void sub(int x) {
    modify(0, arr[x], -1);
    if (sum(0, arr[x]) - sum(0, arr[x] - 1) == 0)
        modify(1, arr[x], -1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read<int>();
    blocksize = sqrt(n);
    m = read<int>();
    for (int i = 1; i <= n; ++i)
        arr[i] = read<int>();
    for (int i = 1; i <= m; ++i) {
        q[i].l = read<int>();
        q[i].r = read<int>();
        q[i].min = read<int>();
        q[i].max = read<int>();
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
            add(--l);
        while (q[i].r > r)
            add(++r);
        while (q[i].l > l)
            sub(l++);
        while (q[i].r < r)
            sub(r--);
        ans[0][q[i].id] = sum(0, q[i].max) - sum(0, q[i].min - 1);
        ans[1][q[i].id] = sum(1, q[i].max) - sum(1, q[i].min - 1);
    }
    for (int i = 1; i <= m; ++i)
        printf("%d %d\n", ans[0][i], ans[1][i]);
    return 0;
}