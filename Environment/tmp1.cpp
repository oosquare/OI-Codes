#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, sum, max, min, rev, plus, l, r, size, priority;
};

struct e {
    int to, next;
};

constexpr int maxn = 50000 + 10;
node tree[maxn << 1];
int root, treeuuid;
unsigned seed;
e edge[maxn << 1];
int head[maxn], edgeuuid;
int sze[maxn], dep[maxn], father[maxn], son[maxn], dfn[maxn], top[maxn], timer;
int n, m, r;

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)
#define myrandom() (seed = seed * 391397 ^ 123893)
#define create(key)                                                            \
    ((tree[++treeuuid] = {key, key, key, key, 0, 0, 0, 0, 1, myrand()}), uuid)
#define swap(x, y) (x ^= y ^= x ^= y)

void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].sum = tree[ls(x)].sum + tree[x].key + tree[rs(x)].sum;
    tree[x].max = max(max(tree[ls(x)].max, tree[x].key), tree[rs(x)].max);
    tree[x].min = min(min(tree[ls(x)].min, tree[x].key), tree[rs(x)].min);
}

inline void updatePlus(int x, int p) {
    tree[x].plus += p;
    tree[x].key += p;
    tree[x].sum += p * tree[x].size;
    tree[x].max += p;
    tree[x].min += p;
}

inline void updateReserve(int x) {
    swap(ls(x), rs(x));
    tree[x].rev ^= 1;
}

void pushdown(int x) {
    if (tree[x].plus) {
        int p = tree[x].plus;
        if (ls(x))
            updatePlus(ls(x), p);
        if (rs(x))
            updatePlus(rs(x), p);
        tree[x].plus = 0;
    }
    if (tree[x].rev) {
        if (ls(x))
            updateReserve(ls(x));
        if (rs(x))
            updateReserve(rs(x));
        tree[x].rev = 0;
    }
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[ls(root)].size < sze) {
        x = root;
        split(rs(x), sze - tree[ls(x)].size - 1, rs(x), y);
    } else {
        y = root;
        split(ls(y), sze, x, ls(y));
    }
    pushup(root);
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if (tree[x].priority < tree[y].priority) {
        pushdown(x);
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

inline void treapPlus(int l, int r, int v) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    updatePlus(y, v);
    root = merge(merge(x, y), z);
}

inline void treapRserve(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    updateReserve(y);
    root = merge(merge(x, y), z);
}

inline int querySum(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    int ans = tree[y].sum;
    root = merge(merge(x, y), z);
    return ans;
}

inline int queryMax(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    int ans = tree[y].max;
    root = merge(merge(x, y), z);
    return ans;
}

inline int queryMin(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    int ans = tree[y].min;
    root = merge(merge(x, y), z);
    return ans;
}

void DFS1(int x, int fa) {
    father[x] = fa;
    dep[x] = dep[fa] + 1;
    sze[x] = 1;
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (y == fa)
            continue;
        DFS1(y, x);
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
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].to) {
        if (top[y])
            continue;
        dfn[y] = ++timer;
        top[y] = y;
        DFS2(y);
    }
}

void treePlus(int x, int y, int v) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        treapPlus(dfn[fx], dfn[x], v);
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    treapPlus(dfn[x], dfn[y], v);
}

void treeReserve(int x, int y) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        treapRserve(dfn[fx], dfn[x]);
        x = father[fx];
        fx = top[x];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    treapRserve(dfn[x], dfn[y]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
}