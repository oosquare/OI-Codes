#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, l, r, father, size, priortiy;
};

const int maxn = 80000 + 10;
node tree[maxn];
int root, uuid, seed, mapping[maxn], n, m;
char cmd[10];

inline int myrandom() { return seed = (int)(seed * 993147LL ^ 0x7fffffff); }

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline int &fa(int x) { return tree[x].father; }

inline int create(int key) {
    tree[++uuid] = {key, 0, 0, 0, 1, myrandom()};
    mapping[key] = uuid;
    return uuid;
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    if (ls(x))
        fa(ls(x)) = x;
    if (rs(x))
        fa(rs(x)) = x;
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
        fa(y) = 0;
    } else {
        y = root;
        split(ls(y), sze, x, ls(y));
        pushup(y);
        fa(x) = 0;
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if (tree[x].priortiy < tree[y].priortiy) {
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else {
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

template <typename T> T read() {
    T x = 0, s = 1;
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

int ask(int s) {
    int x = mapping[s];
    int ans = tree[ls(x)].size + 1;
    while (fa(x)) {
        if (rs(fa(x)) == x)
            ans += tree[ls(fa(x))].size + 1;
        x = fa(x);
    }
    return ans - 1;
}

void top() {
    int p = ask(read<int>()), x, y, z;
    split(root, p, x, y);
    split(y, 1, y, z);
    root = merge(merge(y, x), z);
}

void bottom() {
    int p = ask(read<int>()), x, y, z;
    split(root, p, x, y);
    split(y, 1, y, z);
    root = merge(merge(x, z), y);
}

void insert() {
    int s = read<int>(), t = read<int>(), x, y, z, w;
    if (!t)
        return;
    int p = ask(s);
    if (t == 1) {
        split(root, p, x, y);
        split(y, 1, y, z);
        split(z, 1, z, w);
        root = merge(merge(x, z), merge(y, w));
    } else {
        split(root, p - 1, x, y);
        split(y, 1, y, z);
        split(z, 1, z, w);
        root = merge(merge(x, z), merge(y, w));
    }
}

inline void ask() { printf("%d\n", ask(read<int>())); }

inline void query() {
    int x, y, z;
    split(root, read<int>() - 1, x, y);
    split(y, 1, y, z);
    printf("%d\n", tree[y].key);
    root = merge(merge(x, y), z);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    seed = (int)(time(NULL) * 439911LL % 0x7fffffff);
    n = read<int>();
    m = read<int>();
    for (int i = 1; i <= n; ++i) {
        int x = read<int>();
        root = merge(root, create(x));
    }
    while (m--) {
        scanf("%s", cmd);
        switch (cmd[0]) {
        case 'T':
            top();
            break;
        case 'B':
            bottom();
            break;
        case 'I':
            insert();
            break;
        case 'A':
            ask();
            break;
        case 'Q':
            query();
            break;
        }
    }
    return 0;
}
