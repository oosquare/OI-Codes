#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, l, r, sze, pri, rev;
} tree[200000];
int tot, root;
int seed = 233, n, m;

int rad() { return seed = int(seed * 482711ll % 2147483647); }

int create(int key) {
    ++tot;
    tree[tot].key = key;
    tree[tot].l = tree[tot].r = 0;
    tree[tot].sze = 1;
    tree[tot].pri = rad();
    return tot;
}

void pushup(int rt) {
    tree[rt].sze = tree[tree[rt].l].sze + tree[tree[rt].r].sze + 1;
}

void pushdown(int rt) {
    if (tree[rt].rev == 0)
        return;
    swap(tree[rt].l, tree[rt].r);
    tree[tree[rt].l].rev ^= 1;
    tree[tree[rt].r].rev ^= 1;
    tree[rt].rev = 0;
}

void split(int rt, int sze, int &x, int &y) {
    if (rt == 0) {
        x = y = 0;
        return;
    }
    pushdown(rt);
    if (tree[tree[rt].l].sze + 1 <= sze) {
        x = rt;
        split(tree[rt].r, sze - tree[tree[rt].l].sze - 1, tree[rt].r, y);
    } else {
        y = rt;
        split(tree[rt].l, sze, x, tree[rt].l);
    }
    pushup(rt);
}

int merge(int x, int y) {
    if (x == 0 || y == 0)
        return x + y;
    if (tree[x].pri > tree[y].pri) {
        pushdown(x);
        tree[x].r = merge(tree[x].r, y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        tree[y].l = merge(x, tree[y].l);
        pushup(y);
        return y;
    }
}

void reverse(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    tree[y].rev ^= 1;
    root = merge(merge(x, y), z);
}

void output(int x) {
    if (x == 0)
        return;
    pushdown(x);
    output(tree[x].l);
    printf("%d ", tree[x].key);
    output(tree[x].r);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        root = merge(root, create(i));
    }
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        reverse(l, r);
    }
    output(root);
    return 0;
}
