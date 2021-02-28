#include <bits/stdc++.h>
using namespace std;

struct node {
    int sum, id;
};

struct e {
    int to, next;
};

constexpr int inf = 0x7fffffff;
constexpr int maxn = 100000 + 10;
node tree[maxn << 3];
e edge[maxn << 1];
int uuid, n, q, timer, head[maxn];
int sze[maxn], dep[maxn], father[maxn], son[maxn], top[maxn], dfn[maxn],
    rev[maxn];

inline void link(int x, int y) { edge[++uuid] = {y, head[x]}, head[x] = uuid; }

inline void pushup(int x) {
    tree[x].sum = tree[x << 1].sum + tree[x << 1 | 1].sum;
    tree[x].id = min(tree[x << 1].id, tree[x << 1 | 1].id);
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].sum = 0;
        tree[x].id = inf;
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    pushup(x);
}

void modify(int x, int l, int r, int p) {
    if (l == r && r == p) {
        tree[x].sum ^= 1;
        tree[x].id = (tree[x].sum ? l : inf);
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(x << 1, l, mid, p);
    else
        modify(x << 1 | 1, mid + 1, r, p);
    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x].id;
    int mid = (l + r) >> 1;
    int res = inf;
    if (ql <= mid)
        res = min(res, query(x << 1, l, mid, ql, qr));
    if (mid < qr)
        res = min(res, query(x << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

void DFS1(int x, int fa) {
    sze[x] = 1;
    dep[x] = dep[fa] + 1;
    father[x] = fa;
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
        rev[timer] = son[x];
        DFS2(son[x]);
    }
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (top[y])
            continue;
        dfn[y] = ++timer;
        top[y] = y;
        rev[timer] = y;
        DFS2(y);
    }
}

inline int read() {
    int x = 0, s = 1;
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

inline void treeModify() {
    int x = read();
    modify(1, 1, n, dfn[x]);
}

inline void myswap(int &x, int &y) { x ^= y ^= x ^= y; }

inline void treeQuery() {
    int x = read(), y = 1;
    int fx = top[x], fy = top[y];
    int res = inf;
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            myswap(fx, fy);
            myswap(x, y);
        }
        res = min(res, query(1, 1, n, dfn[fx], dfn[x]));
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        myswap(x, y);
    res = min(res, query(1, 1, n, dfn[x], dfn[y]));
    printf("%d\n", res == inf ? -1 : rev[res]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    q = read();
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(x, y);
        link(y, x);
    }
    DFS1(1, 0);
    top[1] = dfn[1] = rev[1] = timer = 1;
    DFS2(1);
    build(1, 1, n);
    while (q--) {
        int x = read();
        if (x == 0)
            treeModify();
        else
            treeQuery();
    }
    return 0;
}