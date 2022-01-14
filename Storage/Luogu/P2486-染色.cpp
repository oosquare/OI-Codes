#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Data {
    int pre = 0, suf = 0, cnt = 0;

    static Data merge(Data lhs, Data rhs) {
        return {lhs.pre, rhs.suf, lhs.cnt + rhs.cnt - (lhs.suf == rhs.pre)};
    }

    static Data reverse(Data a) {
        return {a.suf, a.pre, a.cnt};
    }
};

struct SegmentTree {
public:
    void build(int n, int c[], int rev[]) {
        build(1, 1, n, c, rev);
    }

    void assign(int l, int r, int c) {
        assign(1, l, r, c);
    }

    Data query(int l, int r) {
        return query(1, l, r);
    }

private:
    struct Node {
        int left, right;
        Data data;
        int assign;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].data = Data::merge(tree[x * 2].data, tree[x * 2 + 1].data);
    }

    void update(int x, int c) {
        tree[x].data.cnt = 1;
        tree[x].data.pre = tree[x].data.suf = c;
        tree[x].assign = c;
    }

    void pushdown(int x) {
        if (tree[x].assign) {
            update(x * 2, tree[x].assign);
            update(x * 2 + 1, tree[x].assign);
            tree[x].assign = 0;
        }
    }

    void build(int x, int l, int r, int c[], int rev[]) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            tree[x].data.pre = tree[x].data.suf = c[rev[l]];
            tree[x].data.cnt = 1;
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, c, rev);
        build(x * 2 + 1, mid + 1, r, c, rev);
        pushup(x);
    }

    void assign(int x, int l, int r, int c) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, c);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            assign(x * 2, l, r, c);

        if (mid < r)
            assign(x * 2 + 1, l, r, c);

        pushup(x);
    }

    Data query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].data;

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (r <= mid)
            return query(x * 2, l, r);
        else if (mid < l)
            return query(x * 2 + 1, l, r);
        else
            return Data::merge(query(x * 2, l, r), query(x * 2 + 1, l, r));
    }
};

class Tree {
public:
    void init(int c[], int n) {
        for (int i = 1; i <= n; ++i)
            col[i] = c[i];
    }

    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess() {
        dfs(1);
        dfs(1, 1);
        seg.build(timer, col, rev);
    }

    int order(int x) {
        return dfn[x];
    }

    int depth(int x) {
        return dep[x];
    }

    vector<int> &operator[](int x) {
        return tree[x];
    }

    int lca(int x, int y) {
        int fx = top[x], fy = top[y];

        while (fx != fy) {
            if (dep[fx] > dep[fy]) {
                x = fa[fx];
                fx = top[x];
            } else {
                y = fa[fy];
                fy = top[y];
            }
        }

        return (dep[x] < dep[y] ? x : y);
    }

    void assign(int x, int y, int c) {
        int fx = top[x], fy = top[y];

        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(x, y);
                swap(fx, fy);
            }

            seg.assign(dfn[fx], dfn[x], c);
            x = fa[fx];
            fx = top[x];
        }

        if (dep[x] > dep[y])
            swap(x, y);

        seg.assign(dfn[x], dfn[y], c);
    }

    Data query(int x, int y) {
        int fx = top[x], fy = top[y];
        Data l, r;

        while (fx != fy) {
            if (dep[fx] > dep[fy]) {
                l = Data::merge(seg.query(dfn[fx], dfn[x]), l);
                x = fa[fx];
                fx = top[x];
            } else {
                r = Data::merge(seg.query(dfn[fy], dfn[y]), r);
                y = fa[fy];
                fy = top[y];
            }
        }

        if (dep[x] < dep[y])
            r = Data::merge(seg.query(dfn[x], dfn[y]), r);
        else
            l = Data::merge(seg.query(dfn[y], dfn[x]), l);

        return Data::merge(Data::reverse(l), r);
    }

private:
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    int timer, dfn[maxn], rev[maxn], col[maxn];
    SegmentTree seg;

    void dfs(int x) {
        dep[x] = dep[fa[x]] + 1;
        size[x] = 1;

        for (int y : tree[x]) {
            if (y == fa[x])
                continue;

            fa[y] = x;
            dfs(y);
            size[x] += size[y];

            if (size[y] > size[son[x]])
                son[x] = y;
        }
    }

    void dfs(int x, int t) {
        top[x] = t;
        dfn[x] = ++timer;
        rev[timer] = x;

        if (son[x])
            dfs(son[x], t);

        for (int y : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;

            dfs(y, y);
        }
    }
};

int n, m, col[maxn];
Tree tree;

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++)
            cin >> col[i];

        tree.init(col, n);
        
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            tree.link(x, y);
        }

        tree.preprocess();

        while (m--) {
            char op;
            int x, y, c;
            cin >> op;

            if (op == 'C') {
                cin >> x >> y >> c;
                tree.assign(x, y, c);
            } else {
                cin >> x >> y;
                cout << tree.query(x, y).cnt << endl;
            }
        }
    }

    return 0;
}