#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int oo = 0x7fffffff;

struct SegmentTree {
    struct Node {
        int left, right;
        int min, assign;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
    }

    void update(int x, int v) {
        tree[x].assign = v;
        tree[x].min = v;
    }

    void pushdown(int x) {
        if (tree[x].assign) {
            update(x * 2, tree[x].assign);
            update(x * 2 + 1, tree[x].assign);
            tree[x].assign = 0;
        }
    }

    void build(int x, int l, int r, int a[], int rev[]) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            tree[x].min = a[rev[l]];
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, a, rev);
        build(x * 2 + 1, mid + 1, r, a, rev);
        pushup(x);
    }

    void assign(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            assign(x * 2, l, r, v);

        if (mid < r)
            assign(x * 2 + 1, l, r, v);

        pushup(x);
    }

    int query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].min;

        int mid = (tree[x].left + tree[x].right) / 2, res = oo;
        pushdown(x);

        if (l <= mid)
            res = min(res, query(x * 2, l, r));

        if (mid < r)
            res = min(res, query(x * 2 + 1, l, r));

        return res;
    }
};

int n, m;
vector<int> tree[maxn];
int val[maxn], root;
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], step[maxn][18];
int timer, dfn[maxn], rev[maxn];
SegmentTree seg;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x) {
    dep[x] = dep[fa[x]] + 1;
    sze[x] = 1;
    step[x][0] = fa[x];

    for (int i = 1; i <= 17; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (int y : tree[x]) {
        if (y == fa[x])
            continue;

        fa[y] = x;
        dfs(y);
        sze[x] += sze[y];

        if (sze[y] > sze[son[x]])
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

void assign(int x, int y, int v) {
    int fx = top[x], fy = top[y];

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(x, y);
            swap(fx, fy);
        }

        seg.assign(1, dfn[fx], dfn[x], v);
        x = fa[fx];
        fx = top[x];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    seg.assign(1, dfn[x], dfn[y], v);
}

int lca(int x, int y) {
    int fx = top[x], fy = top[y];

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(x, y);
            swap(fx, fy);
        }

        x = fa[fx];
        fx = top[x];
    }

    return dep[x] < dep[y] ? x : y;
}

int jump(int x, int to) {
    for (int i = 17; i >= 0; --i)
        if (dep[step[x][i]] > dep[to])
            x = step[x][i];

    return x;
}

int query(int x) {
    if (lca(x, root) != x) {
        return seg.query(1, dfn[x], dfn[x] + sze[x] - 1);
    } else if (x == root) {
        return seg.query(1, 1, n);
    } else {
        int y = jump(root, x);
        return min(seg.query(1, 1, dfn[y] - 1), seg.query(1, dfn[y] + sze[y], n));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; ++i)
        cin >> val[i];

    cin >> root;

    dfs(1);
    dfs(1, 1);
    seg.build(1, 1, n, val, rev);

    for (int i = 1; i <= m; ++i) {
        int opt, x, y, v;
        cin >> opt >> x;

        if (opt == 1) {
            root = x;
        } else if (opt == 2) {
            cin >> y >> v;
            assign(x, y, v);
        } else {
            cout << query(x) << endl;
        }
    }

    return 0;
}