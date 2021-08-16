#include <bits/stdc++.h>
using namespace std;

template <typename T = int> inline T read() {
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

typedef long long ll;

struct node {
    ll key, sum, add, mul;
    int rev, child[2], father, size;
    int &operator[](int x) { return child[x]; }
};

constexpr int maxn = 1001000;
constexpr int mod = 51061;
node tree[maxn];
int uuid, n, q;
int stk[maxn], top;

inline int &ls(int x) { return tree[x].child[0]; }

inline int &rs(int x) { return tree[x].child[1]; }

inline int &fa(int x) { return tree[x].father; }

inline int create(unsigned key) {
    tree[++uuid] = {key, key, 0, 1, 0, {0, 0}, 0, 1};
    return uuid;
}

inline bool notroot(int x) { return ls(fa(x)) == x || rs(fa(x)) == x; }

inline bool which(int x) { return x == rs(fa(x)); }

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].sum = (tree[ls(x)].sum + tree[x].key + tree[rs(x)].sum) % mod;
}

inline void updateReserve(int x) {
    swap(ls(x), rs(x));
    tree[x].rev ^= 1;
}

inline void updateAdd(int x, ll d) {
    tree[x].add = (tree[x].add + d) % mod;
    tree[x].key = (tree[x].key + d) % mod;
    tree[x].sum = (tree[x].sum + (d * tree[x].size) % mod) % mod;
}

inline void updateMul(int x, ll d) {
    tree[x].mul = tree[x].mul * d % mod;
    tree[x].add = tree[x].add * d % mod;
    tree[x].key = tree[x].key * d % mod;
    tree[x].sum = tree[x].sum * d % mod;
}

void pushdown(int x) {
    if (tree[x].rev) {
        if (ls(x))
            updateReserve(ls(x));
        if (rs(x))
            updateReserve(rs(x));
        tree[x].rev = 0;
    }
    if (tree[x].mul != 1) {
        if (ls(x))
            updateMul(ls(x), tree[x].mul);
        if (rs(x))
            updateMul(rs(x), tree[x].mul);
        tree[x].mul = 1;
    }
    if (tree[x].add) {
        if (ls(x))
            updateAdd(ls(x), tree[x].add);
        if (rs(x))
            updateAdd(rs(x), tree[x].add);
        tree[x].add = 0;
    }
}

void rotate(int x) {
    int y = fa(x), z = fa(y), k = which(x), w = tree[x][k ^ 1];
    if (notroot(y))
        tree[z][y == rs(z)] = x;
    tree[x][k ^ 1] = y;
    tree[y][k] = w;
    if (w)
        fa(w) = y;
    fa(y) = x;
    fa(x) = z;
    pushup(y);
    pushup(x);
}

inline void splay(int x) {
    int y = x;
    stk[++top] = y;
    while (notroot(y))
        stk[++top] = y = fa(y);
    while (top)
        pushdown(stk[top--]);
    while (notroot(x)) {
        y = fa(x);
        if (notroot(y))
            which(x) ^ which(y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x) {
    for (int y = 0; x; x = fa(y = x)) {
        splay(x);
        rs(x) = y;
        pushup(x);
    }
}

inline void makeroot(int x) {
    access(x);
    splay(x);
    updateReserve(x);
}

inline int findroot(int x) {
    access(x);
    splay(x);
    while (ls(x)) {
        pushdown(x);
        x = ls(x);
    }
    splay(x);
    return x;
}

inline int extract(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
    return y;
}

inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x)
        fa(x) = y;
}

inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa(y) == x && !ls(y)) {
        fa(y) = rs(x) = 0;
        pushup(x);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    q = read();
    for (int i = 1; i <= n; ++i)
        create(1);
    for (int i = 1; i < n; ++i)
        link(read(), read());
    for (int i = 1; i <= q; ++i) {
        char op[5];
        scanf("%s", op);
        switch (op[0]) {
        case '+': {
            int a = read(), b = read();
            ll c = read<ll>();
            updateAdd(extract(a, b), c);
            break;
        }
        case '-': {
            int a = read(), b = read(), c = read(), d = read();
            cut(a, b);
            link(c, d);
            break;
        }
        case '*': {
            int a = read(), b = read();
            ll c = read<ll>();
            updateMul(extract(a, b), c);
            break;
        }
        case '/': {
            int a = read(), b = read();
            printf("%lld\n", tree[extract(a, b)].sum % mod);
            break;
        }
        }
    }
}