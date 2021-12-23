#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int null = 10001;

struct Node {
    int left, right;
    int sum, assign;
    int max, lmax, rmax;

    Node() : left(0), right(0), sum(0), assign(null), max(0), lmax(0), rmax(9) {}
};

int n, q, val[maxn];
vector<int> tree[maxn];
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int timer, dfn[maxn], rev[maxn];
Node seg[maxn * 4];

void pushup(int x) {
    seg[x].sum = seg[x * 2].sum + seg[x * 2 + 1].sum;
    seg[x].max = max(max(seg[x * 2].max, seg[x * 2 + 1].max), max(seg[x * 2].rmax + seg[x * 2 + 1].lmax, 0));
    seg[x].lmax = max(max(seg[x * 2].lmax, seg[x * 2].sum + seg[x * 2 + 1].lmax), 0);
    seg[x].rmax = max(max(seg[x * 2 + 1].rmax, seg[x * 2 + 1].sum + seg[x * 2].rmax), 0);
}

Node pushup(Node lhs, Node rhs) {
    Node res;
    res.sum = lhs.sum + rhs.sum;
    res.max = max(max(lhs.max, rhs.max), max(lhs.rmax + rhs.lmax, 0));
    res.lmax = max(max(lhs.lmax, lhs.sum + rhs.lmax), 0);
    res.rmax = max(max(rhs.rmax, rhs.sum + lhs.rmax), 0);
    return res;
}

void update(int x, int v) {
    seg[x].sum = v * (seg[x].right - seg[x].left + 1);
    seg[x].assign = v;
    seg[x].max = seg[x].lmax = seg[x].rmax = max(seg[x].sum, 0);
}

void pushdown(int x) {
    if (seg[x].assign != null) {
        update(x * 2, seg[x].assign);
        update(x * 2 + 1, seg[x].assign);
        seg[x].assign = null;
    }
}

void build(int x, int l, int r) {
    seg[x].left = l;
    seg[x].right = r;

    if (l == r) {
        seg[x].sum = val[rev[l]];
        seg[x].max = seg[x].lmax = seg[x].rmax = max(val[rev[l]], 0);
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void assign(int x, int l, int r, int v) {
    if (l <= seg[x].left && seg[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (seg[x].left + seg[x].right) / 2;
    pushdown(x);

    if (l <= mid)
        assign(x * 2, l, r, v);

    if (mid < r)
        assign(x * 2 + 1, l, r, v);

    pushup(x);
}

Node query(int x, int l, int r) {
    if (l <= seg[x].left && seg[x].right <= r)
        return seg[x];

    int mid = (seg[x].left + seg[x].right) / 2;
    pushdown(x);

    if (r <= mid)
        return query(x * 2, l, r);
    else if (mid < l)
        return query(x * 2 + 1, l, r);
    else
        return pushup(query(x * 2, l, r), query(x * 2 + 1, l, r));
}

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x) {
    dep[x] = dep[fa[x]] + 1;
    sze[x] = 1;

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
            swap(fx, fy);
            swap(x, y);
        }

        assign(1, dfn[fx], dfn[x], v);
        x = fa[fx];
        fx = top[x];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    assign(1, dfn[x], dfn[y], v);
}

int query(int x, int y) {
    int fx = top[x], fy = top[y];
    Node l, r;

    while (fx != fy) {
        if (dep[fx] > dep[fy]) {
            l = pushup(query(1, dfn[fx], dfn[x]), l);
            x = fa[fx];
            fx = top[x];
        } else {
            r = pushup(query(1, dfn[fy], dfn[y]), r);
            y = fa[fy];
            fy = top[y];
        }
    }

    if (dep[x] < dep[y])
        r = pushup(query(1, dfn[x], dfn[y]), r);
    else
        l = pushup(query(1, dfn[y], dfn[x]), l);

    swap(l.lmax, l.rmax);
    return pushup(l, r).max;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> val[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    dfs(1);
    dfs(1, 1);
    build(1, 1, n);

    cin >> q;

    while (q--) {
        int op, x, y, v;
        cin >> op >> x >> y;

        if (op == 1) {
            cout << query(x, y) << endl;
        } else {
            cin >> v;
            assign(x, y, v);
        }
    }

    return 0;
}
