#include <bits/stdc++.h>

using namespace std;

struct node {
    int key, sum, rev, child[2], father;
    int &operator[](int i) { return child[i]; }
};

constexpr int maxn = 3e4;
node tree[maxn << 2];
int n, q, stk[maxn];
char cmd[20];
int faset[maxn];

#define ls(x) (tree[(x)].child[0])
#define rs(x) (tree[(x)].child[1])
#define fa(x) (tree[(x)].father)
#define notroot(x) (ls(fa(x)) == (x) || rs(fa(x)) == (x))
#define pushup(x)                                                              \
    (tree[x].sum = tree[ls(x)].sum + tree[x].key + tree[rs(x)].sum)
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
#define update(x) (swap(ls(x), rs(x)), tree[x].rev ^= 1)
#define which(x) (x == rs(fa(x)))

int find(int x) { return x == faset[x] ? x : faset[x] = find(faset[x]); }

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

inline int read() {
    int x = 0, s = 1;
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

inline void link() {
    int x = read(), y = read();
    makeroot(x);
    if (find(x) == find(y)) {
        printf("no\n");
    } else {
        printf("yes\n");
        fa(x) = y;
        faset[find(x)] = faset[find(y)];
    }
}

inline void modify() {
    int x = read(), y = read();
    makeroot(x);
    tree[x].key = y;
    pushup(x);
}

inline void query() {
    int x = read(), y = read();
    makeroot(x);
    if (find(x) != find(y)) {
        printf("impossible\n");
    } else {
        access(y);
        splay(y);
        printf("%d\n", tree[y].sum);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i) {
        tree[i].key = tree[i].sum = read();
        faset[i] = i;
    }
    q = read();
    while (q--) {
        scanf("%s", cmd);
        switch (cmd[0]) {
        case 'b':
            link();
            break;
        case 'p':
            modify();
            break;
        case 'e':
            query();
            break;
        }
    }
    return 0;
}