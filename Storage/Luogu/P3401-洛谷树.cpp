#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 3e4 + 10;

struct SegmentTree {
    struct Data {
        int sum, cnt[2], lcnt[2], rcnt[2];

        Data() {
            sum = 0;
            cnt[0] = cnt[1] = 0;
            lcnt[0] = lcnt[1] = 0;
            rcnt[0] = rcnt[1] = 0;
        }

        void set(int x) {
            sum = x;
            cnt[x] = lcnt[x] = rcnt[x] = 1;
            cnt[x ^ 1] = lcnt[x ^ 1] = rcnt[x ^ 1] = 0;
        }

        static Data merge(Data lhs, Data rhs) {
            Data res;
            res.sum = lhs.sum + rhs.sum;
            res.cnt[0] = lhs.cnt[0] + rhs.cnt[0] + lhs.rcnt[0] * rhs.lcnt[0] + lhs.rcnt[1] * rhs.lcnt[1];
            res.cnt[1] = lhs.cnt[1] + rhs.cnt[1] + lhs.rcnt[0] * rhs.lcnt[1] + lhs.rcnt[1] * rhs.lcnt[0];
            res.lcnt[0] = lhs.lcnt[0] + rhs.lcnt[lhs.sum & 1];
            res.lcnt[1] = lhs.lcnt[1] + rhs.lcnt[(lhs.sum & 1) ^ 1];
            res.rcnt[0] = rhs.rcnt[0] + lhs.rcnt[rhs.sum & 1];
            res.rcnt[1] = rhs.rcnt[1] + lhs.rcnt[(rhs.sum & 1) ^ 1];
            return res;
        }
    };
    
    struct Node {
        int left, right;
        Data data;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].data = Data::merge(tree[x * 2].data, tree[x * 2 + 1].data);
    }

    void build(int x, int l, int r, int a[],int rev[]) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            tree[x].data.set(a[rev[l]]);
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, a, rev);
        build(x * 2 + 1, mid + 1, r, a, rev);
        pushup(x);
    }

    void modify(int x, int p, int v) {
        if (tree[x].left == tree[x].right) {
            tree[x].data.set(v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;

        if (p <= mid)
            modify(x * 2, p, v);
        else
            modify(x * 2 + 1, p, v);

        pushup(x);
    }

    Data query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].data;

        int mid = (tree[x].left + tree[x].right) / 2;

        if (r <= mid)
            return query(x * 2, l, r);
        else if (mid < l)
            return query(x * 2 + 1, l, r);
        else
            return Data::merge(query(x * 2, l, r), query(x * 2 + 1, l, r));
    }
};

int n, q;
vector<pair<int, int>> tree[maxn];
SegmentTree seg[10];
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int timer, dfn[maxn], rev[maxn];
int arr[10][maxn];

void link(int x, int y, int w) {
    tree[x].push_back({y, w});
    tree[y].push_back({x, w});
}

void dfs1(int x) {
    dep[x] = dep[fa[x]] + 1;
    sze[x] = 1;

    for (auto [y, l] : tree[x]) {
        if (y == fa[x])
            continue;

        for (int i = 0; i < 10; ++i)
            arr[i][y] = ((l >> i) & 1);

        fa[y] = x;
        dfs1(y);
        sze[x] += sze[y];

        if (sze[y] > sze[son[x]])
            son[x] = y;
    }
}

void dfs2(int x, int t) {
    top[x] = t;
    dfn[x] = ++timer;
    rev[timer] = x;

    if (son[x])
        dfs2(son[x], t);

    for (auto [y, l] : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs2(y, y);
    }
}

void modify(int x, int y, int w) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 0; i < 10; ++i)
        seg[i].modify(1, dfn[x], ((w >> i) & 1));
}

long long query(int x, int y, int id) {
    int fx = top[x], fy = top[y];
    SegmentTree::Data l, r;

    while (fx != fy) {
        if (dep[fx] > dep[fy]) {
            SegmentTree::Data res = seg[id].query(1, dfn[fx], dfn[x]);
            l = SegmentTree::Data::merge(res, l);
            x = fa[fx];
            fx = top[x];
        } else {
            SegmentTree::Data res = seg[id].query(1, dfn[fy], dfn[y]);
            r = SegmentTree::Data::merge(res, r);
            y = fa[fy];
            fy = top[y];
        }
    }

    if (x != y) {
        if (dep[x] < dep[y]) {
            SegmentTree::Data res = seg[id].query(1, dfn[x] + 1, dfn[y]);
            r = SegmentTree::Data::merge(res, r);
        } else {
            SegmentTree::Data res = seg[id].query(1, dfn[y] + 1, dfn[x]);
            l = SegmentTree::Data::merge(res, l);
        }
    }

    swap(l.lcnt[0], l.rcnt[0]);
    swap(l.lcnt[1], l.rcnt[1]);
    SegmentTree::Data res = SegmentTree::Data::merge(l, r);
    return res.cnt[1];
}

long long query(int x, int y) {
    long long res = 0;

    for (int i = 0; i < 10; ++i)
        res += 1ll * (1ll << i) * query(x, y, i);

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        link(x, y, w);
    }

    dfs1(1);
    dfs2(1, 1);

    for (int i = 0; i < 10; ++i)
        seg[i].build(1, 1, n, arr[i], rev);

    while (q--) {
        int op, x, y, w;
        cin >> op >> x >> y;

        if (op == 1) {
            cout << query(x, y) << endl;
        } else {
            cin >> w;
            modify(x, y, w);
        }
    }

    return 0;
}