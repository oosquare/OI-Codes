#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 5e4 + 10;

struct SegmentTree {
    struct Node {
        int left, right;
        long long min, max, det[2], add;

        Node() {
            min = 0x3f3f3f3f3f3f3f3f;
            max = -0x3f3f3f3f3f3f3f3f;
            det[0] = det[1] = 0;
        }
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
        tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
        tree[x].det[0] = max(max(tree[x * 2].det[0], tree[x * 2 + 1].det[0]), tree[x * 2 + 1].max - tree[x * 2].min);
        tree[x].det[1] = max(max(tree[x * 2].det[1], tree[x * 2 + 1].det[1]), tree[x * 2].max - tree[x * 2 + 1].min);
    }

    Node pushup(Node l, Node r) {
        Node res;
        res.min = min(l.min, r.min);
        res.max = max(l.max, r.max);
        res.det[0] = max(max(l.det[0], r.det[0]), r.max - l.min);
        res.det[1] = max(max(l.det[1], r.det[1]), l.max - r.min);
        return res;
    }

    void update(int x, int v) {
        tree[x].min += v;
        tree[x].max += v;
        tree[x].add += v;
    }

    void pushdown(int x) {
        if (tree[x].add) {
            update(x * 2, tree[x].add);
            update(x * 2 + 1, tree[x].add);
            tree[x].add = 0;
        }
    }

    void build(int x, int l, int r, int arr[], int rev[]) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            tree[x].min = tree[x].max = arr[rev[l]];
            tree[x].det[0] = tree[x].det[1] = 0;
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, arr, rev);
        build(x * 2 + 1, mid + 1, r, arr, rev);
        pushup(x);
    }

    void add(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            add(x * 2, l, r, v);

        if (mid < r)
            add(x * 2 + 1, l, r, v);

        pushup(x);
    }

    Node query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x];

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (r <= mid)
            return query(x * 2, l, r);
        else if (mid < l)
            return query(x * 2 + 1, l, r);
        else
            return pushup(query(x * 2, l, r), query(x * 2 + 1, l, r));
    }
};

int n, q, p[maxn];
vector<int> tree[maxn];
int sze[maxn], dep[maxn], fa[maxn], son[maxn];
int timer, dfn[maxn], rev[maxn], top[maxn];
SegmentTree seg;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x) {
    dep[x] = dep[fa[x]] + 1;
    sze[x] = 1;

    for (int y : tree[x]) {
        if (y == fa[x])
            continue;

        fa[y] = x;
        dfs1(y);
        sze[x] += sze[y];

        if (sze[son[x]] < sze[y])
            son[x] = y;
    }
}

void dfs2(int x, int t) {
    top[x] = t;
    dfn[x] = ++timer;
    rev[timer] = x;

    if (son[x])
        dfs2(son[x], t);

    for (int y : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs2(y, y);
    }
}

int query(int x, int y) {
    SegmentTree::Node res1, res2;
    int fx = top[x], fy = top[y];

    while (fx != fy) {
        if (dep[fx] > dep[fy]) {
            res1 = seg.pushup(seg.query(1, dfn[fx], dfn[x]), res1);
            x = fa[fx];
            fx = top[x];
        } else {
            res2 = seg.pushup(seg.query(1, dfn[fy], dfn[y]), res2);
            y = fa[fy];
            fy = top[y];
        }
    }

    if (dep[x] < dep[y]) {
        res2 = seg.pushup(seg.query(1, dfn[x], dfn[y]), res2);
    } else {
        res1 = seg.pushup(seg.query(1, dfn[y], dfn[x]), res1);
    }

    swap(res1.det[0], res1.det[1]);
    return seg.pushup(res1, res2).det[0];
}

void add(int x, int y, int v) {
    int fx = top[x], fy = top[y];

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }

        seg.add(1, dfn[fx], dfn[x], v);
        x = fa[fx];
        fx = top[x];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    seg.add(1, dfn[x], dfn[y], v);
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> p[i];

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        link(a, b);
    }

    dfs1(1);
    dfs2(1, 1);
    seg.build(1, 1, n, p, rev);

    cin >> q;

    while (q--) {
        int x, y, v;
        cin >> x >> y >> v;
        cout << query(x, y) << endl;
        add(x, y, v);
    }

    return 0;
}