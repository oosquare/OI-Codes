#include <bits/stdc++.h>
using namespace std;

struct SegmentNode {
    int sum, left, right;
};

struct TreeNode {
    int to, nxt;
};

const int maxn = 100005;
SegmentNode seg[(maxn << 5) + 10];
int root[maxn], total;
TreeNode tree[2 * maxn + 10];
int head[maxn], tot;
int dep[maxn], father[maxn], f[maxn][19];
int arr[maxn], mapping[maxn], len;
int n, m, lastans = 0;

inline void link(int x, int y) {
    tree[++tot] = (TreeNode){y, head[x]};
    head[x] = tot;
}

inline int toIndex(int x) {
    return lower_bound(mapping + 1, mapping + 1 + len, arr[x]) - mapping;
}

inline int toData(int x) { return mapping[x]; }

inline int &lc(int x) { return seg[x].left; }

inline int &rc(int x) { return seg[x].right; }

inline int getSum(int x) { return seg[lc(x)].sum; }

int build(int l, int r) {
    int newroot = ++total;
    if (l == r)
        return newroot;
    int mid = (l + r) >> 1;
    lc(newroot) = build(l, mid);
    rc(newroot) = build(mid + 1, r);
    return newroot;
}

int modify(int base, int l, int r, int pos) {
    int newroot = ++total;
    seg[newroot] = seg[base];
    seg[newroot].sum++;
    if (l == r)
        return newroot;
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        lc(newroot) = modify(lc(base), l, mid, pos);
    } else {
        rc(newroot) = modify(rc(base), mid + 1, r, pos);
    }
    return newroot;
}

int query(int r1, int r2, int r3, int r4, int l, int r, int k) {
    if (l == r)
        return l;
    int s = getSum(r1) + getSum(r2) - getSum(r3) - getSum(r4);
    int mid = (l + r) >> 1;
    if (k <= s) {
        return query(lc(r1), lc(r2), lc(r3), lc(r4), l, mid, k);
    } else {
        return query(rc(r1), rc(r2), rc(r3), rc(r4), mid + 1, r, k - s);
    }
}

void preprocess(int x, int fa) {
    root[x] = modify(root[fa], 1, len, toIndex(x));
    dep[x] = dep[fa] + 1;
    father[x] = fa;
    f[x][0] = fa;
    for (int i = 1; i <= 18; ++i) {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt) {
        if (y == fa)
            continue;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 18; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    }
    if (x == y)
        return x;
    for (int i = 18; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

inline int query(int x, int y, int k) {
    int l = lca(x, y);
    int id = query(root[x], root[y], root[l], root[father[l]], 1, len, k);
    return toData(id);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        mapping[i] = arr[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        link(x, y);
        link(y, x);
    }
    sort(mapping + 1, mapping + 1 + n);
    len = unique(mapping + 1, mapping + 1 + n) - mapping - 1;
    root[0] = build(1, len);
    preprocess(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        lastans = query(x, y, k);
        printf("%d\n", lastans);
    }
}