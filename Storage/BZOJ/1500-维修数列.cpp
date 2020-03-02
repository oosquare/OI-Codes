#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, lmax, rmax, max, sum, rev, same;
    int l, r, size, pri;
};

const int maxn = 1000000 + 1000;
const int inf = 0x3f3f3f3f;
node tree[maxn];
int root, total, seed;
int trash[maxn], top;
int stk[maxn];
int n, m;
char cmd[20];

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)
#define myrand() (seed = (int)(seed * 312372LL % 0x7fffffff))
#define swap(x, y) (x ^= y ^= x ^= y)

inline int create(int key) {
    int rt;
    tree[rt = (top ? trash[top--] : ++total)] =
        (node){key, key, key, key, key, 0, inf, 0, 0, 1, myrand()};
    return rt;
}

void gc(int x) {
    if (!x)
        return;
    trash[++top] = x;
    gc(ls(x));
    gc(rs(x));
}

inline void pushup(int x) {
    if (x) {
        tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
        tree[x].sum = tree[ls(x)].sum + tree[rs(x)].sum + tree[x].key;
        tree[x].lmax = max(max(tree[ls(x)].lmax, tree[ls(x)].sum + tree[x].key),
                           tree[ls(x)].sum + tree[x].key + tree[rs(x)].lmax);
        tree[x].rmax = max(max(tree[rs(x)].rmax, tree[rs(x)].sum + tree[x].key),
                           tree[rs(x)].sum + tree[x].key + tree[ls(x)].rmax);
        tree[x].max = max(max(max(tree[ls(x)].rmax, 0) + tree[x].key +
                                  max(tree[rs(x)].lmax, 0),
                              tree[ls(x)].max),
                          tree[rs(x)].max);
    }
}

inline void pushdown(int x) {
    if (tree[x].same != inf) {
        int s = tree[x].same;
        if (ls(x)) {
            tree[ls(x)].key = s;
            tree[ls(x)].same = s;
            tree[ls(x)].sum = tree[ls(x)].size * s;
            tree[ls(x)].lmax = tree[ls(x)].rmax = tree[ls(x)].max =
                (s >= 0 ? tree[ls(x)].sum : s);
            // tree[ls(x)].rev=0;
        }
        if (rs(x)) {
            tree[rs(x)].key = s;
            tree[rs(x)].same = s;
            tree[rs(x)].sum = tree[rs(x)].size * s;
            tree[rs(x)].lmax = tree[rs(x)].rmax = tree[rs(x)].max =
                (s >= 0 ? tree[rs(x)].sum : s);
            // tree[rs(x)].rev=0;
        }
        tree[x].same = inf;
    }
    if (tree[x].rev) {
        if (ls(x)) {
            swap(ls(ls(x)), rs(ls(x)));
            swap(tree[ls(x)].lmax, tree[ls(x)].rmax);
            tree[ls(x)].rev ^= 1;
        }
        if (rs(x)) {
            swap(ls(rs(x)), rs(rs(x)));
            swap(tree[rs(x)].lmax, tree[rs(x)].rmax);
            tree[rs(x)].rev ^= 1;
        }
        tree[x].rev = 0;
    }
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    pushdown(root);
    if (tree[ls(root)].size < sze) {
        x = root;
        split(rs(root), sze - tree[ls(root)].size - 1, rs(x), y);
    } else {
        y = root;
        split(ls(root), sze, x, ls(root));
    }
    pushup(root);
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if (tree[x].pri < tree[y].pri) {
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

template <typename T> inline T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

int build(int len) {
    int p = 0, x, last;
    for (register int i = 1; i <= len; ++i) {
        int val = read<int>();
        x = create(val);
        last = 0;
        while (p && tree[stk[p]].key > tree[x].key) {
            pushup(stk[p]);
            last = stk[p];
            stk[p--] = 0;
        }
        if (p)
            rs(stk[p]) = x;
        ls(x) = last;
        stk[++p] = x;
    }
    while (p)
        pushup(stk[p--]);
    return stk[1];
}

inline void insert() {
    int pos = read<int>(), len = read<int>();
    int x, y;
    split(root, pos, x, y);
    root = merge(merge(x, build(len)), y);
}

inline void remove() {
    int pos = read<int>(), len = read<int>();
    int x, y, z;
    split(root, pos - 1, x, y);
    split(y, len, y, z);
    root = merge(x, z);
    gc(y);
}

inline void reserve() {
    int pos = read<int>(), len = read<int>();
    int x, y, z;
    split(root, pos - 1, x, y);
    split(y, len, y, z);
    tree[y].rev ^= 1;
    swap(ls(y), rs(y));
    swap(tree[y].lmax, tree[y].rmax);
    root = merge(merge(x, y), z);
}

inline void makesame() {
    int pos = read<int>(), len = read<int>(), val = read<int>();
    int x, y, z;
    split(root, pos - 1, x, y);
    split(y, len, y, z);
    tree[y].same = val;
    tree[y].key = val;
    tree[y].sum = tree[y].size * val;
    tree[y].lmax = tree[y].rmax = tree[y].max = (val >= 0 ? tree[y].sum : val);
    root = merge(merge(x, y), z);
}

inline void querysum() {
    int pos = read<int>(), len = read<int>();
    int x, y, z;
    split(root, pos - 1, x, y);
    split(y, len, y, z);
    printf("%d\n", tree[y].sum);
    root = merge(merge(x, y), z);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    seed = time(NULL);
    tree[0].sum = 0;
    tree[0].lmax = tree[0].rmax = tree[0].max = -inf;
    n = read<int>();
    m = read<int>();
    root = build(n);
    while (m--) {
        scanf("%s", cmd);
        if (cmd[0] == 'I')
            insert();
        else if (cmd[0] == 'D')
            remove();
        else if (cmd[0] == 'R')
            reserve();
        else if (cmd[0] == 'M' && cmd[2] == 'K')
            makesame();
        else if (cmd[0] == 'G')
            querysum();
        else
            printf("%d\n", tree[root].max);
    }
    return 0;
}
