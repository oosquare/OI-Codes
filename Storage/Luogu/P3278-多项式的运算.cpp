#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, add, mul, l, r, size, priority;
};

constexpr int maxn = 1e5 + 10;
constexpr int mod = 20130426;
node tree[maxn << 4];
int total, root, seed;
int n, tmp, ans;
char cmd[10];

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline int myrandom() {
    return seed = (int)((seed + 3) * 341241LL % 0x7fffffff);
}

inline int create(int v) {
    tree[++total] = {v, 0, 1, 0, 0, 1, myrandom()};
    return total;
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
}

inline void addmod(int &x, int y) { x = (1LL * x + 1LL * y) % mod; }

inline void mulmod(int &x, int y) { x = (1LL * x * y) % mod; }

inline void pushdown(int x) {
    if (tree[x].mul != 1) {
        int xm = tree[x].mul;
        tree[x].mul = 1;
        if (ls(x)) {
            mulmod(tree[ls(x)].mul, xm);
            mulmod(tree[ls(x)].add, xm);
            mulmod(tree[ls(x)].key, xm);
        }
        if (rs(x)) {
            mulmod(tree[rs(x)].mul, xm);
            mulmod(tree[rs(x)].add, xm);
            mulmod(tree[rs(x)].key, xm);
        }
    }
    if (tree[x].add) {
        int am = tree[x].add;
        tree[x].add = 0;
        if (ls(x)) {
            addmod(tree[ls(x)].add, am);
            addmod(tree[ls(x)].key, am);
        }
        if (rs(x)) {
            addmod(tree[rs(x)].add, am);
            addmod(tree[rs(x)].key, am);
        }
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
    pushdown(x);
    pushdown(y);
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

int power(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1)
            ans = 1LL * ans * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}

inline int merge(int x, int y, int z) { return merge(merge(x, y), z); }

inline void add() {
    int l, r, v, x, y, z;
    scanf("%d%d%d", &l, &r, &v);
    ++l;
    ++r;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    addmod(tree[y].add, v);
    addmod(tree[y].key, v);
    root = merge(x, y, z);
}

inline void mul() {
    int l, r, v, x, y, z;
    scanf("%d%d%d", &l, &r, &v);
    ++l;
    ++r;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    mulmod(tree[y].mul, v);
    mulmod(tree[y].add, v);
    mulmod(tree[y].key, v);
    root = merge(x, y, z);
}

inline void mulx() {
    int n1, n2, n3, n4, n5, n6, n7, n8, nn = create(0), l, r;
    scanf("%d%d", &l, &r);
    ++l;
    ++r;
    split(root, l - 1, n1, n2);
    split(n2, r - l + 1, n3, n4);
    split(n3, tree[n3].size - 1, n5, n6);
    split(n4, 1, n7, n8);
    tree[n7].key += tree[n6].key;
    root = merge(n1, merge(nn, merge(n5, merge(n7, n8))));
}

void dfs(int x, int v) {
    if (!x)
        return;
    pushdown(x);
    dfs(ls(x), v);
    (ans += 1LL * tmp * tree[x].key % mod) %= mod;
    (tmp = 1LL * tmp * v % mod) %= mod;
    dfs(rs(x), v);
}

inline void query() {
    int x;
    scanf("%d", &x);
    tmp = 1;
    ans = 0;
    dfs(root, x);
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < maxn; ++i) {
        root = merge(root, create(0));
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%s", cmd);
        if (cmd[0] == 'a')
            add();
        else if (cmd[0] == 'm' && cmd[3] != 'x')
            mul();
        else if (cmd[0] == 'm' && cmd[3] == 'x')
            mulx();
        else
            query();
    }
    return 0;
}
