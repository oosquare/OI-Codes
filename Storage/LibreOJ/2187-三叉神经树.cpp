#include <iostream>
using namespace std;

constexpr int maxn = 5e5 + 10;

struct Node {
    int ls, rs, fa, size;
    bool rev;
    int key, cnt[4], add;

    int &operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

int n, q;
Node tree[maxn];
int st[maxn];
int mp[maxn * 3], val[maxn * 3];

void pushup(int x) {
    tree[x].size = tree[tree[x].ls].size + 1 + tree[tree[x].rs].size;

    for (int i = 0; i < 4; ++i)
        tree[x].cnt[i] = tree[tree[x].ls].cnt[i] + (tree[x].key == i) + tree[tree[x].rs].cnt[i];
}

void updateReverse(int x) {
    tree[x].rev ^= 1;
    swap(tree[x].ls, tree[x].rs);
}

void updateAdd(int x, int v) {
    tree[x].cnt[tree[x].key + v] += tree[x].cnt[tree[x].key];
    tree[x].cnt[tree[x].key] = 0;
    tree[x].key += v;
    tree[x].add += v;
}

void pushdown(int x) {
    if (tree[x].rev) {
        if (tree[x].ls)
            updateReverse(tree[x].ls);

        if (tree[x].rs)
            updateReverse(tree[x].rs);

        tree[x].rev = false;
    }

    if (tree[x].add) {
        if (tree[x].ls)
            updateAdd(tree[x].ls, tree[x].add);

        if (tree[x].rs)
            updateAdd(tree[x].rs, tree[x].add);

        tree[x].add = 0;
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
    for (int s = 0; x; s = x, x = tree[x].fa) {
        splay(x);
        tree[x].rs = s;
        pushup(x);
    }
}

void makeRoot(int x) {
    access(x);
    splay(x);
    updateReverse(x);
}

int findRoot(int x) {
    access(x);
    splay(x);
    pushdown(x);

    while (tree[x].ls) {
        x = tree[x].ls;
        pushdown(x);
    }

    splay(x);
    return x;
}

void link(int x, int y) {
    makeRoot(x);

    if (findRoot(y) != x)
        tree[x].fa = y;
}

int find(int x, int v) {
    while (x) {
        pushdown(x);

        if (tree[tree[x].rs].cnt[v] == tree[tree[x].rs].size && tree[x].key != v)
            return x;
        else if (tree[tree[x].rs].cnt[v] < tree[tree[x].rs].size)
            x = tree[x].rs;
        else
            x = tree[x].ls;
    }

    return 0;
}

void modify(int x, int v) {
    makeRoot(1);
    access(x);
    splay(x);

    int delta = (v == 1 ? 1 : -1);
    int y = find(x, (v == 1 ? 1 : 2));

    if (!y) {
        updateAdd(x, delta);
    } else {
        splay(y);

        if (tree[y].rs)
            updateAdd(tree[y].rs, delta);

        if (0 <= tree[y].key + delta && tree[y].key + delta <= 3)
            tree[y].key += delta;
        
        pushup(y);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        tree[i].size = 1;
        tree[i].cnt[0] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        int x[3];
        cin >> x[0] >> x[1] >> x[2];

        for (int j = 0; j < 3; ++j) {
            if (x[j] <= n)
                link(i, x[j]);
            else
                mp[x[j]] = i;
        }
    }

    for (int i = n + 1; i <= 3 * n + 1; ++i) {
        int v;
        cin >> v;
        val[i] = v;

        if (v)
            modify(mp[i], v);
    }

    cin >> q;

    for (int i = 1; i <= q; ++i) {
        int x;
        cin >> x;
        val[x] ^= 1;
        modify(mp[x], val[x]);
        makeRoot(1);
        splay(1);
        cout << (tree[1].key >= 2) << endl;
    }

    return 0;
}