#include <bits/stdc++.h>
using namespace std;

struct node {
    int sum, assign, l, r;
};

constexpr int maxsize = 1e7 + 5e6;
node tree[maxsize];
int uuid, root;
int n, q;

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline void pushup(int x) { tree[x].sum = tree[ls(x)].sum + tree[rs(x)].sum; }

inline int create() {
    return tree[++uuid].assign = 2, uuid;
}

inline void update(int &x, int l, int r, int v) {
    if (!x)
        x = create();
    if (v) {        
        tree[x].assign = 1;
        tree[x].sum = r - l + 1;
    } else {
        tree[x].assign = 0;
        tree[x].sum = 0;
    }
}

void pushdown(int &x, int l, int r) {
    if (tree[x].assign != 2) {
        int mid = (l + r) >> 1;
        update(ls(x), l, mid, tree[x].assign);
        update(rs(x), mid + 1, r, tree[x].assign);
        tree[x].assign = 2;
    }
}

void modify(int &x, int l, int r, int ml, int mr, int v) {
    if (!x)
        x = create();
    if (ml <= l && r <= mr) {
        update(x, l, r, v);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(x, l, r);
    if (ml <= mid)
        modify(ls(x), l, mid, ml, mr, v);
    if (mid < mr)
        modify(rs(x), mid + 1, r, ml, mr, v);
    pushup(x);
}

int read() {
    int x = 0, s = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    q = read();
    update(root, 1, n, 1);
    while (q--) {
        int l = read(), r = read(), k = read();
        modify(root, 1, n, l, r, k - 1);
        pushdown(root, 1, n);
        printf("%d\n", tree[root].sum);
    }
    return 0;
}