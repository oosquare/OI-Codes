#include <bits/stdc++.h>
using namespace std;

inline char gc() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
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
    int key, assign;
};

struct e {
    int to, next;
};

constexpr int maxn = 500000 << 2;
e edge[maxn];
int edgeuuid, head[maxn];
node tree[maxn];
int sze[maxn], dep[maxn], father[maxn], son[maxn], dfn[maxn], top[maxn];
int n, q, timer;

void build(int x, int l, int r) {
    tree[x] = {0, 2};
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
}

inline void update(int x, int v) { tree[x].key = tree[x].assign = v; }

inline void pushdown(int x) {
    if (tree[x].assign != 2) {
        update(x << 1, tree[x].assign);
        update(x << 1 | 1, tree[x].assign);
        tree[x].assign = 2;
    }
}

void modify(int x, int l, int r, int ml, int mr, int v) {
    if (ml <= l && r <= mr) {
        update(x, v);
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ml <= mid)
        modify(x << 1, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x << 1 | 1, mid + 1, r, ml, mr, v);
}

int query(int x, int l, int r, int p) {
    if (l == r && r == p)
        return tree[x].key;
    pushdown(x);
    int mid = (l + r) >> 1;
    if (p <= mid)
        return query(x << 1, l, mid, p);
    else
        return query(x << 1 | 1, mid + 1, r, p);
}

inline void link(int x, int y) {
    edge[++edgeuuid] = {y, head[x]};
    head[x] = edgeuuid;
}

void DFS1(int x, int fa) {
    dep[x] = dep[fa] + 1;
    father[x] = fa;
    sze[x] = 1;
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (y == fa)
            continue;
        DFS1(y, x);
        sze[x] += sze[y];
        if (sze[y] > sze[son[x]])
            son[x] = y;
    }
}

void DFS2(int x) {
    if (son[x]) {
        dfn[son[x]] = ++timer;
        top[son[x]] = top[x];
        DFS2(son[x]);
    }
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (top[y])
            continue;
        dfn[y] = ++timer;
        top[y] = y;
        DFS2(y);
    }
}

void modifyPath(int x) {
    int y = 1, fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy])
            swap(fx, fy), swap(x, y);
        modify(1, 1, n, dfn[fx], dfn[x], 0);
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    modify(1, 1, n, dfn[x], dfn[y], 0);
}

inline void modifyTree(int x) { modify(1, 1, n, dfn[x], dfn[x] + sze[x] - 1, 1); }

inline int queryNode(int x) { return query(1, 1, n, dfn[x]); }

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read<int>();
    for (int i = 1; i < n; ++i) {
        int x = read<int>(), y = read<int>();
        link(x, y);
        link(y, x);
    }
    DFS1(1, 0);
    top[1] = dfn[1] = timer = 1;
    DFS2(1);
    build(1, 1, n);
    q = read<int>();
    while (q--) {
        int o = read<int>(), x = read<int>();
        if (o == 1)
            modifyTree(x);
        else if (o == 2)
            modifyPath(x);
        else
            printf("%d\n", queryNode(x));
    }
    return 0;
}