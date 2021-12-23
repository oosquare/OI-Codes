#include <iostream>
#include <vector>

using namespace std;

constexpr int maxn = 2e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    int left, right;
    int sum, max, min;
    bool rev;

    Node() : left(0), right(0), sum(0), max(-oo), min(oo), rev(false) {}
};

int n, m;
vector<pair<int, int>> tree[maxn];
int edges[maxn][2];
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int timer, dfn[maxn], rev[maxn], val[maxn];
Node seg[maxn * 4];

void pushup(int x) {
    seg[x].sum = seg[x * 2].sum + seg[x * 2 + 1].sum;
    seg[x].max = max(seg[x * 2].max, seg[x * 2 + 1].max);
    seg[x].min = min(seg[x * 2].min, seg[x * 2 + 1].min);
}

Node pushup(Node lhs, Node rhs) {
    Node res;
    res.sum = lhs.sum + rhs.sum;
    res.max = max(lhs.max, rhs.max);
    res.min = min(lhs.min, rhs.min);
    return res;
}

void update(int x) {
    seg[x].rev ^= 1;
    seg[x].sum *= -1;
    swap(seg[x].min, seg[x].max);
    seg[x].max *= -1;
    seg[x].min *= -1;
}

void pushdown(int x) {
    if (seg[x].rev) {
        update(x * 2);
        update(x * 2 + 1);
        seg[x].rev = false;
    }
}

void build(int x, int l, int r) {
    seg[x].left = l;
    seg[x].right = r;

    if (l == r) {
        seg[x].sum = seg[x].max = seg[x].min = val[rev[l]];
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void assign(int x, int p, int v) {
    if (seg[x].left == seg[x].right) {
        seg[x].sum = seg[x].max = seg[x].min = v;
        return;
    }

    int mid = (seg[x].left + seg[x].right) / 2;
    pushdown(x);

    if (p <= mid)
        assign(x * 2, p, v);
    else
        assign(x * 2 + 1, p, v);

    pushup(x);
}

void reverse(int x, int l, int r) {
    if (l <= seg[x].left && seg[x].right <= r) {
        update(x);
        return;
    }

    int mid = (seg[x].left + seg[x].right) / 2;
    pushdown(x);

    if (l <= mid)
        reverse(x * 2, l, r);

    if (mid < r)
        reverse(x * 2 + 1, l, r);

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

void link(int x, int y, int w) {
    tree[x].push_back({y, w});
    tree[y].push_back({x, w});
}

void dfs(int x) {
    dep[x] = dep[fa[x]] + 1;
    sze[x] = 1;

    for (auto [y, l] : tree[x]) {
        if (y == fa[x])
            continue;

        fa[y] = x;
        val[y] = l;
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

    for (auto [y, l] : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs(y, y);
    }
}

void assign(int id, int v) {
    auto [x, y] = edges[id];

    if (dep[x] < dep[y])
        swap(x, y);

    assign(1, dfn[x], v);
}

void reverse(int x, int y) {
    int fx = top[x], fy = top[y];

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }

        reverse(1, dfn[fx], dfn[x]);
        x = fa[fx];
        fx = top[x];
    }

    if (x == y)
        return;

    if (dep[x] > dep[y])
        swap(x, y);

    reverse(1, dfn[x] + 1, dfn[y]);
}

Node query(int x, int y) {
    int fx = top[x], fy = top[y];
    Node res;

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }

        res = pushup(res, query(1, dfn[fx], dfn[x]));
        x = fa[fx];
        fx = top[x];
    }

    if (x == y)
        return res;

    if (dep[x] > dep[y])
        swap(x, y);

    res = pushup(res, query(1, dfn[x] + 1, dfn[y]));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        ++x;
        ++y;
        edges[i][0] = x;
        edges[i][1] = y;
        link(x, y, w);
    }

    dfs(1);
    dfs(1, 1);
    build(1, 1, n);

    cin >> m;

    while (m--) {
        char op[4];
        int x, y;
        cin >> op >> x >> y;

        if (op[0] == 'C')
            assign(x, y);
        else if (op[0] == 'N')
            reverse(x + 1, y + 1);
        else if (op[0] == 'S')
            cout << query(x + 1, y + 1).sum << endl;
        else if (op[1] == 'A')
            cout << query(x + 1, y + 1).max << endl;
        else
            cout << query(x + 1, y + 1).min << endl;
    }

    return 0;
}