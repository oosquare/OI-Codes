#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, l, r, sze, pri;
};

constexpr int maxn = 7e5 + 10;

node tree[maxn << 2];
int tot, root, seed = 233;
int n, r[maxn];

int myrandom() { return seed = (int)(seed * 123421LL % 0x7fffffff); }

void pushup(int x) {
    tree[x].sze = tree[tree[x].l].sze + tree[tree[x].r].sze + 1;
}

int create(int key) {
    tree[++tot] = (node){key, 0, 0, 1, myrandom()};
    return tot;
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[tree[root].l].sze < sze) {
        x = root;
        split(tree[x].r, sze - tree[tree[x].l].sze - 1, tree[x].r, y);
        pushup(x);
    } else {
        y = root;
        split(tree[y].l, sze, x, tree[y].l);
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if (tree[x].pri < tree[y].pri) {
        tree[x].r = merge(tree[x].r, y);
        pushup(x);
        return x;
    } else {
        tree[y].l = merge(x, tree[y].l);
        pushup(y);
        return y;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &r[i]);
        root = merge(root, create(i));
    }
    for (int i = 1; i <= n; ++i) {
        int x, y, z;
        r[i] %= tree[root].sze;
        split(root, r[i], x, y);
        split(y, 1, y, z);
        printf("%d\n", tree[y].key);
        root = merge(z, x);
    }
    return 0;
}