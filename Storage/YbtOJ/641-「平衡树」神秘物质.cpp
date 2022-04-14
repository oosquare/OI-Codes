#include <bits/stdc++.h>
using namespace std;

void read(int &x) {
    x = 0;
    char c = getchar();
    while (c < '0' || '9' < c) {
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
}

void writeln(int x) {
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

constexpr int maxn = 1e5 + 10;

struct node {
    int key, raw, max, min, ls, rs, size;
    unsigned priority;
};

node tree[maxn * 100];
int uuid, root1, root2;
unsigned seed;
int n, m, e[maxn];

inline unsigned myrandom() {
    return seed = ((seed + 5) * 12839 + 13427);
}

inline int &ls(int x) {
    return tree[x].ls;
}

inline int &rs(int x) {
    return tree[x].rs;
}

void pushup(int x) {
    tree[x].min = tree[x].max = tree[x].key;
    tree[x].size = 1;
    if (ls(x)) {
        tree[x].size += tree[ls(x)].size;
        tree[x].max = max(tree[x].max, tree[ls(x)].max);
        tree[x].min = min(tree[x].min, tree[ls(x)].min);
    }
    if (rs(x)) {
        tree[x].size += tree[rs(x)].size;
        tree[x].max = max(tree[x].max, tree[rs(x)].max);
        tree[x].min = min(tree[x].min, tree[rs(x)].min);
    }
}

inline int create(int key, int raw) {
    tree[++uuid] = {key, raw, key, key, 0, 0, 1, myrandom()};
    return uuid;
}

void split(int rt, int sze, int &x, int &y) {
    if (!rt) {
        x = y = 0;
        return;
    }
    if (tree[ls(rt)].size + 1 <= sze) {
        x = rt;
        split(rs(x), sze - tree[ls(x)].size - 1, rs(x), y);
        pushup(x);
    } else {
        y = rt;
        split(ls(y), sze, x, ls(y));
        pushup(y);
    }
}

int merge(int x, int y) {
    if (x == 0 || y == 0)
        return x + y;
    if (tree[x].priority > tree[y].priority) {
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else {
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

void qmax(int l, int r) {
    int x, y, z;
    split(root1, l - 1, x, y);
    split(y, r - l + 1, y, z);
    writeln(tree[y].max - tree[y].min);
    root1 = merge(merge(x, y), z);
}

void qmin(int l, int r) {
    ++l;
    int x, y, z;
    split(root2, l - 1, x, y);
    split(y, r - l + 1, y, z);
    writeln(tree[y].min);
    root2 = merge(merge(x, y), z);
}

void mmerge(int p, int e) {
    {
        int x, y, z;
        split(root1, p - 1, x, y);
        split(y, 2, y, z);
        root1 = merge(merge(x, create(e, e)), z);
    }
    {
        int x, y, z, w, k;
        split(root2, p - 2, x, y); // x [1, p - 2]
        split(y, 1, y, z); // y [p - 1, p - 1]
        split(z, 2, z, w); // z [p, p + 1]
        split(w, 1, w, k); // w [p + 2, p + 2] k [p + 3, ...]
        int nd1 = create(abs(e - tree[y].raw), e);
        int nd2 = create(abs(tree[w].raw - e), tree[w].raw);
        root2 = merge(merge(x, y), merge(nd1, merge(nd2, k)));
    }
}

void minsert(int p, int e) {
    {
        int x, y;
        split(root1, p, x, y);
        root1 = merge(merge(x, create(e, e)), y);
    }
    {
        int x, y, z, w;
        split(root2, p - 1, x, y); // x [1, p - 1]
        split(y, 1, y, z); // y [p, p]
        split(z, 1, z, w); // z [p + 1, p + 1] w [p + 2, ...]
        int nd1 = create(abs(e - tree[y].raw), e);
        int nd2 = create(abs(tree[z].raw - e), tree[z].raw);
        root2 = merge(merge(x, y), merge(nd1, merge(nd2, w)));
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("atom.in", "r", stdin);
    freopen("atom.out", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        read(e[i]);
        root1 = merge(root1, create(e[i], e[i]));
        root2 = merge(root2, create(abs(e[i] - e[i - 1]), e[i]));
    }
    for (int i = 1; i <= m; ++i) {
        char op[10];
        int x, y;
        scanf("%s", op);
        read(x), read(y);
        if (op[1] == 'e')
            mmerge(x, y);
        if (op[1] == 'n')
            minsert(x, y);
        if (op[1] == 'a')
            qmax(x, y);
        if (op[1] == 'i')
            qmin(x, y);
    }
    return 0;
}
