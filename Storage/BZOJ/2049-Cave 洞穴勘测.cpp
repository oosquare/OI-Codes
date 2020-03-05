#include <bits/stdc++.h>
using namespace std;

struct node {
    int rev, child[2], father;
    int &operator[](int x) { return child[x]; }
};

constexpr int maxn = 10000 + 10;
node tree[maxn];
int uuid, n, m, stk[maxn];

#define ls(x) (tree[(x)].child[0])
#define rs(x) (tree[(x)].child[1])
#define fa(x) (tree[(x)].father)
#define which(x) ((x) == rs(fa(x)))
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
#define update(x) (swap(ls(x), rs(x)), tree[(x)].rev ^= 1)
#define notroot(x) (ls(fa(x)) == (x) || rs(fa(x)) == (x))

inline void pushdown(int x) {
    if (tree[x].rev) {
        tree[x].rev = 0;
        if (ls(x))
            update(ls(x));
        if (rs(x))
            update(rs(x));
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
}

void splay(int x) {
    int y = x, top = 1;
    stk[top] = y;
    while (notroot(y))
        stk[++top] = y = fa(y);
    while (top) {
        pushdown(stk[top--]);
    }
    while (notroot(x)) {
        y = fa(x);
        if (notroot(y))
            which(x) == which(y) ? rotate(y) : rotate(x);
        rotate(x);
    }
}

inline void access(int x) {
    for (int y = 0; x; x = fa(y = x)) {
        splay(x);
        rs(x) = y;
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

inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x)
        fa(x) = y;
}

inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa(y) == x && !ls(y))
        fa(y) = rs(x) = 0;
}

#define check(x, y) (findroot(x) == findroot(y))

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    while (m--) {
        char cmd[10];
        int x, y;
        scanf("%s%d%d", cmd, &x, &y);
        switch (cmd[0]) {
        case 'Q':
            if (check(x, y))
                printf("Yes\n");
            else
                printf("No\n");
            break;
        case 'C':
            link(x, y);
            break;
        case 'D':
            cut(x, y);
            break;
        }
    }
    return 0;
}