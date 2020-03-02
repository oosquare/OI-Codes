#include <bits/stdc++.h>
using namespace std;

struct node {
    int key, sum, rev, child[2], father;
    int &operator[](int x) { return child[x]; }
};

constexpr int maxn = 1e5 + 5;
node tree[maxn];
int uuid, n, m, opt, x, y;

#define ls(x) (tree[(x)].child[0])
#define rs(x) (tree[(x)].child[1])
#define fa(x) (tree[(x)].father)
#define create(k) ((tree[++uuid] = {k, k, 0, {0, 0}, 0}), uuid)
#define notroot(x) (ls(fa(x)) == (x) || rs(fa(x)) == (x))
#define pushup(x)                                                              \
    (tree[x].sum = tree[ls(x)].sum ^ tree[x].key ^ tree[rs(x)].sum)
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
#define update(x) (swap(ls(x), rs(x)), tree[x].rev ^= 1)
#define which(x) (x == rs(fa(x)))

inline void pushdown(int x) {
    if (tree[x].rev) {
        if (ls(x))
            update(ls(x));
        if (rs(x))
            update(rs(x));
        tree[x].rev = 0;
    }
}

inline void rotate(int x) {
    int y = fa(x), z = fa(y), k = which(x), w = tree[x][!k];
    if (notroot(y))
        tree[z][y == rs(z)] = x;
    tree[x][!k] = y;
    tree[y][k] = w;
    if (w)
        fa(w) = y;
    fa(y) = x;
    fa(x) = z;
    pushup(y);
    //  pushup(x);
}

inline void splay(int x) {
    int y = x;
    stack<int> stk;
    stk.push(y);
    while (notroot(y))
        stk.push(y = fa(y));
    while (!stk.empty())
        pushdown(stk.top()), stk.pop();
    while (notroot(x)) {
        y = fa(x);
        if (notroot(y))
            which(x) == which(y) ? rotate(y) : rotate(x);
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        create(x);
    }
    while (m--) {
        scanf("%d%d%d", &opt, &x, &y);
        switch (opt) {
        case 0:
            printf("%d\n", tree[extract(x, y)].sum);
            break;
        case 1:
            link(x, y);
            break;
        case 2:
            cut(x, y);
            break;
        case 3:
            splay(x);
            tree[x].key = y;
            break;
        }
    }
    return 0;
}
