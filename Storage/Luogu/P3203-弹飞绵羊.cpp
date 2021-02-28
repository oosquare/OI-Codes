#include <bits/stdc++.h>
#define FILEIO true
using namespace std;

struct node {
    int child[2], father, rev, size;
    int &operator[](int x) { return child[x]; }
};

constexpr int maxn = 2e5 + 5;
node tree[maxn];
int num[maxn];
int uuid, n, m, stk[maxn];

#define ls(x) (tree[(x)].child[0])
#define rs(x) (tree[(x)].child[1])
#define fa(x) (tree[(x)].father)
#define which(x) ((x) == rs(fa(x)))
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
#define update(x) (swap(ls(x), rs(x)), tree[(x)].rev ^= 1)
#define notroot(x) ((x) == ls(fa(x)) || (x) == rs(fa(x)))
#define pushup(x) (tree[(x)].size = tree[ls(x)].size + tree[rs(x)].size + 1)

inline void pushdown(int x) {
    if (tree[x].rev) {
        tree[x].rev = 0;
        if (ls(x))
            update(ls(x));
        if (rs(x))
            update(rs(x));
    }
}

inline void rotate(int x) {
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
}

inline void splay(int x) {
    int y = x, top;
    stk[top = 1] = y;
    while (notroot(y))
        stk[++top] = y = fa(y);
    while (top)
        pushdown(stk[top--]);
    while (notroot(x)) {
        y = fa(x);
        if (notroot(y))
            which(x) ^ which(y) ? rotate(x) : rotate(x);
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
    update(x);
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
    return tree[ls(y)].size;
}

inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x)
        fa(x) = y;
}

inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa(y) == x && !ls(x)) {
        fa(y) = rs(x) = 0;
        pushup(x);
    }
}

int main() {
#if !defined(ONLINE_JUDGE) && FILEIO
    freopen("project.in", "r", stdout);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; ++i)
        tree[i].size = 1;
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        num[i] = x;
        if (x + i > n)
            link(i, n + 1);
        else
            link(i, x + i);
    }
    scanf("%d", &m);
    while (m--) {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        ++x;
        if (opt == 1) {
            printf("%d\n", extract(x, n + 1));
        } else {
            scanf("%d", &y);
            cut(x, (x + num[x] <= n ? x + num[x] : n + 1));
            link(x, (x + y <= n ? x + y : n + 1));
            num[x] = y;
        }
    }
    return 0;
}