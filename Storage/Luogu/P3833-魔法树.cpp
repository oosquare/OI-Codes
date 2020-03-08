#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct e {
    int to, next;
};

struct node {
    ll sum, add;
};

constexpr int maxn = 100000 + 10;
e edge[maxn << 1];
node tree[maxn << 3];
int uuid, n, m, timer, head[maxn];
int sze[maxn], dep[maxn], father[maxn], son[maxn], top[maxn], dfn[maxn];

inline void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
}

inline void update(int x, int l, int r, ll v) {
    tree[x].add += v;
    tree[x].sum += v * (r - l + 1);
}

inline void pushup(int x) {
    tree[x].sum = tree[x << 1].sum + tree[x << 1 | 1].sum;
}

inline void pushdown(int x, int l, int r, int mid) {
    if (tree[x].add) {
        update(x << 1, l, mid, tree[x].add);
        update(x << 1 | 1, mid + 1, r, tree[x].add);
        tree[x].add = 0;
    }
}

void modify(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        update(x, l, r, v);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(x, l, r, mid);
    if (ml <= mid)
        modify(x << 1, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x << 1 | 1, mid + 1, r, ml, mr, v);
    pushup(x);
}

ll query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x].sum;
    int mid = (l + r) >> 1;
    pushdown(x, l, r, mid);
    ll res = 0;
    if (ql <= mid)
        res += query(x << 1, l, mid, ql, qr);
    if (mid < qr)
        res += query(x << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

void DFS1(int x, int fa) {
    father[x] = fa;
    dep[x] = dep[fa] + 1;
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

void treeAdd() {
    int x = read() + 1, y = read() + 1, v = read();
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        modify(1, 1, n, dfn[fx], dfn[x], v);
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    modify(1, 1, n, dfn[x], dfn[y], v);
}

void treeQuery() {
    int x = read() + 1;
    printf("%lld\n", query(1, 1, n, dfn[x], dfn[x] + sze[x] - 1));
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i < n; ++i) {
        int x = read() + 1, y = read() + 1;
        link(x, y);
        link(y, x);
    }
    DFS1(1, 0);
    top[1] = 1;
    dfn[1] = timer = 1;
    DFS2(1);
    m = read();
    while (m--) {
        char cmd[3];
        scanf("%s", cmd);
        if (cmd[0] == 'A')
            treeAdd();
        else
            treeQuery();
    }
    return 0;
}