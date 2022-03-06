#include <iostream>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int ls, rs, fa, size, vsize;
    bool rev;

    int &operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

int n, q;
Node tree[maxn];
int st[maxn];

void pushup(int x) {
    tree[x].size = tree[tree[x].ls].size + tree[tree[x].rs].size + 1 + tree[x].vsize;
}

void update(int x) {
    tree[x].rev ^= 1;
    swap(tree[x].ls, tree[x].rs);
}

void pushdown(int x) {
    if (tree[x].rev) {
        if (tree[x].ls)
            update(tree[x].ls);

        if (tree[x].rs)
            update(tree[x].rs);

        tree[x].rev = false;
    }
}

int which(int x) {
    return tree[tree[x].fa].rs == x;
}

bool isRoot(int x) {
    return tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x;
}

void rotate(int x) {
    int y = tree[x].fa, z = tree[y].fa, k = which(x), w = tree[x][k ^ 1];

    if (!isRoot(y))
        tree[z][which(y)] = x;

    tree[x][k ^ 1] = y;
    tree[y][k] = w;
    tree[x].fa = z;
    tree[y].fa = x;

    if (w)
        tree[w].fa = y;

    pushup(y);
    pushup(x);
}

void splay(int x) {
    int top = 0;
    st[++top] = x;

    for (int y = x; !isRoot(y); y = tree[y].fa)
        st[++top] = tree[y].fa;

    while (top)
        pushdown(st[top--]);

    for (int y; y = tree[x].fa, !isRoot(x); rotate(x))
        if (!isRoot(y))
            rotate(which(x) == which(y) ? y : x);
}

void access(int x) {
    for (int y = 0; x; y = x, x = tree[x].fa) {
        splay(x);
        tree[x].vsize += tree[tree[x].rs].size - tree[y].size;
        tree[x].rs = y;
        pushup(x);
    }
}

void makeRoot(int x) {
    access(x);
    splay(x);
    update(x);
}

int findRoot(int x) {
    access(x);
    splay(x);
    pushdown(x);

    if (tree[x].ls) {
        x = tree[x].ls;
        pushdown(x);
    }

    splay(x);
    return x;
}

void link(int x, int y) {
    makeRoot(x);

    if (findRoot(y) != x) {
        makeRoot(y);
        tree[x].fa = y;
        tree[y].vsize += tree[x].size;
        tree[y].size += tree[x].size;
    }
}

void cut(int x, int y) {
    makeRoot(x);

    if (findRoot(y) == x && tree[y].fa == x && !tree[y].ls) {
        tree[x].rs = tree[y].fa = 0;
        pushup(x);
    }
}

long long query(int x, int y) {
    cut(x, y);

    makeRoot(x);
    splay(x);
    int sx = tree[x].size;

    makeRoot(y);
    splay(y);
    int sy = tree[y].size;

    link(x, y);
    
    return 1ll * sx * sy;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        tree[i].size = 1;

    for (int i = 1; i <= q; ++i) {
        char op;
        int x, y;
        cin >> op >> x >> y;

        if (op == 'A')
            link(x, y);
        else
            cout << query(x, y) << endl;
    }

    return 0;
}