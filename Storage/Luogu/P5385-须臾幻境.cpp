#include <iostream>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 2e5 + 10;
constexpr int oo = 0x3f3f3f3f;

class LinkCutTree {
public:
    void init(int x, int key) {
        tree[x].left = tree[x].right = tree[x].father = 0;
        tree[x].rev = false;
        tree[x].key = tree[x].min = key;
        tree[x].pos = x;
    }

    void link(int x, int y) {
        makeRoot(x);

        if (findRoot(y) != x)
            tree[x].father = y;
    }

    void cut(int x, int y) {
        makeRoot(x);

        if (findRoot(y) == x && tree[y].father == x && !tree[y].left) {
            tree[x].right = tree[y].father = 0;
            pushup(x);
        }
    }

    int findRoot(int x) {
        access(x);
        splay(x);
        pushdown(x);

        while (tree[x].left) {
            x = tree[x].left;
            pushdown(x);
        }

        splay(x);
        return x;
    }

    pair<int, int> split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return {tree[y].min, tree[y].pos};
    }

private:
    struct Node {
        int left, right, father;
        bool rev;
        int key, min, pos;

        int &operator[](int x) {
            return (x == 0 ? left : right);
        }
    };

    Node tree[maxn + maxm];
    int st[maxn + maxm];

    void pushup(int x) {
        tree[x].min = tree[x].key;
        tree[x].pos = x;

        if (tree[x].left && tree[tree[x].left].min < tree[x].min) {
            tree[x].min = tree[tree[x].left].min;
            tree[x].pos = tree[tree[x].left].pos;
        }

        if (tree[x].right && tree[tree[x].right].min < tree[x].min) {
            tree[x].min = tree[tree[x].right].min;
            tree[x].pos = tree[tree[x].right].pos;
        }
    }

    void update(int x) {
        tree[x].rev ^= 1;
        swap(tree[x].left, tree[x].right);
    }

    void pushdown(int x) {
        if (tree[x].rev) {
            if (tree[x].left)
                update(tree[x].left);

            if (tree[x].right)
                update(tree[x].right);

            tree[x].rev = false;
        }
    }

    int which(int x) {
        return (tree[tree[x].father].right == x ? 1 : 0);
    }

    bool isRoot(int x) {
        return (tree[tree[x].father].left != x && tree[tree[x].father].right != x);
    }

    void rotate(int x) {
        int y = tree[x].father, z = tree[y].father, k = which(x), w = tree[x][k ^ 1];

        if (!isRoot(y))
            tree[z][which(y)] = x;

        tree[x][k ^ 1] = y;
        tree[y][k] = w;
        tree[x].father = z;
        tree[y].father = x;

        if (w)
            tree[w].father = y;

        pushup(y);
        pushup(x);
    }

    void splay(int x) {
        int top = 0;
        st[++top] = x;

        for (int y = x; !isRoot(y); y = tree[y].father)
            st[++top] = tree[y].father;

        while (top)
            pushdown(st[top--]);

        for (int y; y = tree[x].father, !isRoot(x); rotate(x))
            if (!isRoot(y))
                rotate(which(x) == which(y) ? y : x);
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = tree[x].father) {
            splay(x);
            tree[x].right = y;
            pushup(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        update(x);
    }
};

class PersistentSegmentTree {
public:
    void init(int len) {
        this->len = len;
    }

    void add(int now, int pre, int p, int v) {
        add(root[now], root[pre], 1, len, p, v);
    }

    int query(int now, int l, int r) {
        return query(root[now], 1, len, l, r);
    }

    void copy(int x, int y) {
        root[x] = root[y];
    }

private:
    struct Node {
        int left, right;
        int sum;
    };

    Node tree[maxn * 100];
    int len, uuid, root[maxm];

    void add(int &x, int y, int l, int r, int p, int v) {
        x = ++uuid;
        tree[x] = tree[y];
        tree[x].sum += v;

        if (l == r)
            return;

        int mid = (l + r) / 2;

        if (p <= mid)
            add(tree[x].left, tree[y].left, l, mid, p, v);
        else
            add(tree[x].right, tree[y].right, mid + 1, r, p, v);
    }

    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[x].sum;

        int mid = (l + r) / 2, res = 0;

        if (ql <= mid)
            res += query(tree[x].left, l, mid, ql, qr);

        if (mid < qr)
            res += query(tree[x].right, mid + 1, r, ql, qr);

        return res;
    }
};

struct Edge {
    int x, y, weight;
};

int n, m, q, t;
Edge edges[maxm];
LinkCutTree lct;
PersistentSegmentTree seg;
int ans;

void decode(int &l, int &r) {
    if (t > 0) {
        l = (l + ans) % m + 1;
        r = (r + ans) % m + 1;
    }

    if (l > r)
        swap(l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q >> t;
    seg.init(m);

    for (int i = 1; i <= n; ++i)
        lct.init(i, oo);

    for (int i = 1; i <= m; ++i) {
        auto &[x, y, w] = edges[i];
        cin >> x >> y;
        w = i;
        lct.init(n + i, w);
    }

    for (int i = 1; i <= m; ++i) {
        auto [x, y, w] = edges[i];

        if (x == y) {
            seg.copy(i, i - 1);
            continue;
        }

        if (lct.findRoot(x) == lct.findRoot(y)) {
            auto [v, p] = lct.split(x, y);
            p -= n;

            lct.cut(n + p, edges[p].x);
            lct.cut(n + p, edges[p].y);
            seg.add(i, i - 1, p, -1);
            
            lct.link(n + i, edges[i].x);
            lct.link(n + i, edges[i].y);
            seg.add(i, i, i, 1);
        } else {
            lct.link(n + i, edges[i].x);
            lct.link(n + i, edges[i].y);
            seg.add(i, i - 1, i, 1);
        }
    }

    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        decode(l, r);
        ans = n - seg.query(r, l, r);
        cout << ans << endl;
    }
    
    return 0;
}