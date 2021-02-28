#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

int read() {
    int x = 0, s = 1;
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
    int father, depth, l, r;
};

const int maxn = 2e5 + 5;
node tree[(maxn << 5) + 5];
int uuid, root[maxn], n, m, lastans;

inline int decode(int x) { return x ^ lastans; }

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

void build(int &x, int l, int r) {
    x = ++uuid;
    if (l == r) {
        tree[x].father = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}

void modify(int &x, int y, int l, int r, int p, int v) {
    tree[x = ++uuid] = tree[y];
    if (l == r) {
        tree[x].father = v;
        tree[x].depth = tree[y].depth;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(ls(x), ls(y), l, mid, p, v);
    else
        modify(rs(x), rs(y), mid + 1, r, p, v);
}

int query(int x, int l, int r, int p) {
    if (l == r)
        return x;
    int mid = (l + r) >> 1;
    if (p <= mid)
        return query(ls(x), l, mid, p);
    else
        return query(rs(x), mid + 1, r, p);
}

void add(int x, int l, int r, int p) {
    if (l == r) {
        ++tree[x].depth;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        add(ls(x), l, mid, p);
    else
        add(rs(x), mid + 1, r, p);
}

int find(int x, int ver) {
    while (1) {
        int y = query(root[ver], 1, n, x);
        if (x == tree[y].father)
            return y;
        x = tree[y].father;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    m = read();
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int o = read(), x = decode(read()), y = ((o ^ 2) ? decode(read()) : 0);
        if (o == 1) {
            root[i] = root[i - 1];
            int fx = find(x, i), fy = find(y, i);
            if (tree[fx].father == tree[fy].father)
                continue;
            if (tree[fx].depth > tree[fy].depth)
                swap(fx, fy);
            modify(root[i], root[i - 1], 1, n, tree[fx].father, tree[fy].father);
            if (tree[fx].depth == tree[fy].depth)
                add(root[i], 1, n, tree[fy].father);
        } else if (o == 2) {
            root[i] = root[x];
        } else {
            root[i] = root[i - 1];
            int fx = find(x, i), fy = find(y, i);
            printf("%d\n", lastans = (tree[fx].father == tree[fy].father ? 1 : 0));
        }
    }
    return 0;
}