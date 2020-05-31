#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

struct node {
    int sum, assign;
};

constexpr int maxn = 100000 + 10;
node tree[maxn * 4];
int n, t, m;

void pushup(int x) {
    tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
}

void update(int x, int l, int r, int v) {
    tree[x].assign = v;
    tree[x].sum = (r - l + 1) * v;
}

void pushdown(int x, int l, int r) {
    if (tree[x].assign) {
        int mid = (l + r) / 2;
        update(x * 2, l, mid, tree[x].assign);
        update(x * 2 + 1, mid + 1, r, tree[x].assign);
        tree[x].assign = 0;
    }
}

void modify(int x, int l, int r, int ml, int mr, int v) {
    if (ml <= l && r <= mr) {
        update(x, l, r, v);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x, l, r);
    if (ml <= mid)
        modify(x * 2, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x * 2 + 1, mid + 1, r, ml, mr, v);
    pushup(x);
}

void build(int x, int l, int r) {
    tree[x].sum = 1;
    tree[x].assign = 0;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    t = read();
    for (int i = 1; i <= t; ++i) {
        n = read();
        build(1, 1, n);
        m = read();
        while (m--) {
            int l = read(), r = read(), v = read();
            modify(1, 1, n, l, r, v);
        }
        printf("Case %d: The total value of the hook is %d.\n", i, tree[1].sum);
    }
    return 0;
}