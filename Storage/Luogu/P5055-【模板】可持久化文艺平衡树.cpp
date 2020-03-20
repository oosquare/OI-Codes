#include <bits/stdc++.h>
using namespace std;

inline char gc() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T> T read() {
    T x = 0, s = 1;
    char c = gc();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = gc();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = gc();
    }
    return x * s;
}

typedef long long ll;

struct node {
    ll key, sum;
    int rev, l, r, size;
    unsigned priority;
};

constexpr int maxn = 2e5 + 5;
node tree[maxn << 7];
int uuid, root[maxn], now, n, last, opt;
ll ans;
unsigned seed;

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline unsigned myrandom() { return seed *= 194283U; }

inline int create(ll key) {
    int newroot = ++uuid;
    tree[newroot] = {key, key, 0, 0, 0, 1, myrandom()};
    return newroot;
}

inline int copy(int x) {
    int newroot = ++uuid;
    tree[newroot] = tree[x];
    tree[newroot].priority = myrandom();
    return newroot;
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].sum = tree[ls(x)].sum + tree[x].key + tree[rs(x)].sum;
}

inline void pushdown(int x) {
    if (tree[x].rev) {
        if (ls(x))
            ls(x) = copy(ls(x));
        if (rs(x))
            rs(x) = copy(rs(x));
        swap(ls(x), rs(x));
        if (ls(x))
            tree[ls(x)].rev ^= 1;
        if (rs(x))
            tree[rs(x)].rev ^= 1;
        tree[x].rev = 0;
    }
}

void split(int root, int sze, int &x, int &y) {
    if (root == 0) {
        x = y = 0;
        return;
    }
    pushdown(root);
    if (tree[ls(root)].size < sze) {
        x = copy(root);
        split(rs(x), sze - tree[ls(x)].size - 1, rs(x), y);
        pushup(x);
    } else {
        y = copy(root);
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

void insert() {
    int pos = read<int>() ^ ans;
    ll val = read<ll>() ^ ans;
    int x, y;
    split(root[last], pos, x, y);
    root[++now] = merge(merge(x, create(val)), y);
}

void remove() {
    int pos = read<int>() ^ ans;
    int x, y, z;
    split(root[last], pos - 1, x, y);
    split(y, 1, y, z);
    root[++now] = merge(x, z);
}

void reserve() {
    int l = read<int>() ^ ans, r = read<int>() ^ ans;
    int x, y, z;
    split(root[last], l - 1, x, y);
    split(y, r - l + 1, y, z);
    tree[y].rev ^= 1;
    root[++now] = merge(merge(x, y), z);
}

void query() {
    int l = read<int>() ^ ans, r = read<int>() ^ ans;
    int x, y, z;
    split(root[last], l - 1, x, y);
    split(y, r - l + 1, y, z);
    printf("%lld\n", ans = tree[y].sum);
    root[++now] = merge(merge(x, y), z);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    seed = time(nullptr);
    n = read<int>();
    while (n--) {
        last = read<int>();
        opt = read<int>();
        switch (opt) {
        case 1:
            insert();
            break;
        case 2:
            remove();
            break;
        case 3:
            reserve();
            break;
        case 4:
            query();
            break;
        }
    }
    return 0;
}