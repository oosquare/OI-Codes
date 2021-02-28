#include <bits/stdc++.h>
using namespace std;

inline char gc() {
    static char ff[1000000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 1000000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T>
T read() {
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

struct node {
    int val, l, r;
};

constexpr int maxn = 1e6 + 10;
node tree[maxn << 5];
int root[maxn], arr[maxn], uuid, n, m;

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)

void build(int &x, int l, int r) {
    x = ++uuid;
    if (l == r) {
        tree[x].val = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}

void modify(int &x, int &y, int l, int r, int p, int v) {
    tree[x = ++uuid] = tree[y];
    if (l == r && r == p) {
        tree[x].val = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(ls(x), ls(y), l, mid, p, v);
    else
        modify(rs(x), rs(y), mid + 1, r, p, v);
}

int query(int &x, int l, int r, int p) {
    if (l == r && r == p)
        return tree[x].val;
    int mid = (l + r) >> 1;
    if (p <= mid)
        return query(ls(x), l, mid, p);
    else
        return query(rs(x), mid + 1, r, p);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read<int>();
    m = read<int>();
    for (int i = 1; i <= n; ++i)
        arr[i] = read<int>();
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int v = read<int>(), o = read<int>(), x = read<int>();
        if (o == 1) {
            int y = read<int>();
            modify(root[i], root[v], 1, n, x, y);
        } else {
            printf("%d\n", query(root[i] = root[v], 1, n, x));
        }
    }
    return 0;
}