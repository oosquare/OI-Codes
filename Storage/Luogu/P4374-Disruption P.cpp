#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 50000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    int left, right;
    int min;
};

int n, m;
vector<pair<int, int>> tree[maxn];
int timer, dep[maxn], sze[maxn], dfn[maxn];
Node seg[maxn * 50];
int uuid, root[maxn];
int ans[maxn];

void pushup(int x) {
    seg[x].min = min(seg[seg[x].left].min, seg[seg[x].right].min);
}

void update(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        seg[x].min = (seg[x].min == 0 ? v : min(seg[x].min, p));
        return;
    }

    int mid = (l + r) / 2;

    if (p <= mid)
        update(seg[x].left, l, mid, p, v);
    else
        update(seg[x].right, mid + 1, r, p, v);
    
    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return oo;

    if (ql <= l && r <= qr)
        return seg[x].min;

    int mid = (l + r) / 2, res = oo;

    if (ql <= mid)
        res = min(res, query(seg[x].left, l, mid, ql, qr));

    if (mid < qr)
        res = min(res, query(seg[x].right, mid + 1, r, ql, qr));

    return res;
}

int merge(int x, int y, int l, int r) {
    if (!x || !y)
        return x ^ y;

    if (l == r) {
        seg[x].min = min(seg[x].min, seg[y].min);
        return x;
    }

    int mid = (l + r) / 2;
    seg[x].left = merge(seg[x].left, seg[y].left, l, mid);
    seg[x].right = merge(seg[x].right, seg[y].right, mid + 1, r);
    pushup(x);
    return x;
}

void link(int x, int y, int id) {
    tree[x].push_back({y, id});
    tree[y].push_back({x, id});
}

void preprocess(int x, int fa) {
    sze[x] = 1;
    dfn[x] = ++timer;

    for (auto [y, id] : tree[x]) {
        if (y == fa)
            continue;

        preprocess(y, x);
        sze[x] += sze[y];
    }
}

void dfs(int x, int fa) {
    for (auto [y, id] : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
        ans[id] = min(query(root[y], 1, n, 1, dfn[y] - 1), query(root[y], 1, n, dfn[y] + sze[y], n));
        root[x] = merge(root[x], root[y], 1, n);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y, i);
    }

    preprocess(1, 0);
    seg[0].min = oo;

    for (int i = 1; i <= m; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        update(root[x], 1, n, dfn[y], l);
        update(root[y], 1, n, dfn[x], l);
    }

    dfs(1, 0);

    for (int i = 1; i < n; ++i)
        cout << (ans[i] == oo ? -1 : ans[i]) << endl;

    return 0;
}