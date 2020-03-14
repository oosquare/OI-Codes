#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, lmax, rmax, max, sum, l, r, size;
    unsigned priority;
};

constexpr int maxn = 500000 + 10;
constexpr int inf = 0x3f3f3f3f;
node tree[maxn];
int uuid, root, n, m;
unsigned seed;

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)
#define myrandom() (seed *= 75713)

inline int create(int key) {
    tree[++uuid] = {key, key, key, key, key, 0, 0, 1, myrandom()};
    return uuid;
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].sum = tree[ls(x)].sum + tree[x].key + tree[rs(x)].sum;
    tree[x].lmax = max(max(tree[ls(x)].lmax, tree[ls(x)].sum + tree[x].key),
                       tree[ls(x)].sum + tree[x].key + tree[rs(x)].lmax);
    tree[x].rmax = max(max(tree[rs(x)].rmax, tree[rs(x)].sum + tree[x].key),
                       tree[rs(x)].sum + tree[x].key + tree[ls(x)].rmax);
    tree[x].max =
        max(max(tree[ls(x)].max, tree[rs(x)].max),
            max(tree[ls(x)].rmax, 0) + tree[x].key + max(tree[rs(x)].lmax, 0));
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[ls(root)].size < sze) {
        x = root;
        split(rs(x), sze - tree[ls(x)].size - 1, rs(x), y);
        pushup(x);
    } else {
        y = root;
        split(ls(y), sze, x, ls(y));
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if (tree[x].priority < tree[y].priority) {
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else {
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

int read() {
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

void modify() {
    int pos = read(), val = read(), x, y, z;
    split(root, pos - 1, x, y);
    split(y, 1, y, z);
    unsigned tmp = tree[y].priority;
    tree[y] = {val, val, val, val, val, 0, 0, 1, tmp};
    root = merge(merge(x, y), z);
}

void query() {
    int l = read(), r = read(), x, y, z;
    if (l > r)
        swap(l, r);
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    printf("%d\n", tree[y].max);
    root = merge(merge(x, y), z);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    seed = time(NULL);
    tree[0] = {0, -inf, -inf, -inf, 0, 0, 0, 0, 0};
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i)
        root = merge(root, create(read()));
    while (m--) {
        int opt = read();
        if (opt == 1)
            query();
        else
            modify();
    }
    return 0;
}