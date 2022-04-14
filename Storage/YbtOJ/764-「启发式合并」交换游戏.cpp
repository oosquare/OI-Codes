#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_N = 2e5 + 10;

int n;

namespace Tree2 {

struct Data {
    int l, r, cnt = -1;

    static Data merge(const Data & lhs, const Data & rhs) {
        if (lhs.cnt == -1)
            return rhs;
        
        if (rhs.cnt == -1)
            return lhs;

        return { lhs.l, rhs.r, lhs.cnt + rhs.cnt + (lhs.r != rhs.l) };
    }
};

struct Node {
    int left, right;
    Data data;
};

Node seg[MAX_N * 4];

vector<int> tree[MAX_N];
int fa[MAX_N], son[MAX_N], dep[MAX_N], size[MAX_N], top[MAX_N];
int timer, dfn[MAX_N];

void pushup(int x) {
    seg[x].data = Data::merge(seg[x * 2].data, seg[x * 2 + 1].data);
}

void build(int x, int l, int r) {
    seg[x].left = l;
    seg[x].right = r;
    seg[x].data = {0, 0, 0};

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void modify(int x, int p, int v) {
    if (seg[x].left == seg[x].right) {
        seg[x].data = {v, v, 0};
        return;
    }

    int mid = (seg[x].left + seg[x].right) / 2;

    if (p <= mid)
        modify(x * 2, p, v);
    else
        modify(x * 2 + 1, p, v);
    
    pushup(x);
}

Data query(int x, int l, int r) {
    if (l <= seg[x].left && seg[x].right <= r)
        return seg[x].data;
    
    int mid = (seg[x].left + seg[x].right) / 2;

    if (r <= mid)
        return query(x * 2, l, r);
    else if (mid < l)
        return query(x * 2 + 1, l, r);
    else
        return Data::merge(query(x * 2, l, r), query(x * 2 + 1, l, r));
}

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x) {
    size[x] = 1;
    dep[x] = dep[fa[x]] + 1;

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

    if (son[x])
        dfs(son[x], t);

    for (int y : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs(y, y);
    }
}

void preprocess() {
    dfs(1);
    dfs(1, 1);
    build(1, 1, n);
}

void modify(int x, int v) {
    modify(1, dfn[x], v);
}

int query(int x, int y) {
    int fx = top[x], fy = top[y];
    Data l, r;

    while (fx != fy) {
        if (dep[fx] > dep[fy]) {
            l = Data::merge(query(1, dfn[fx], dfn[x]), l);
            x = fa[fx];
            fx = top[x];
        } else {
            r = Data::merge(query(1, dfn[fy], dfn[y]), r);
            y = fa[fy];
            fy = top[y];
        }
    }

    if (dep[x] < dep[y])
        r = Data::merge(query(1, dfn[x], dfn[y]), r);
    else
        l = Data::merge(query(1, dfn[y], dfn[x]), l);

    swap(l.l, l.r);
    return Data::merge(l, r).cnt;
}

} // namespace Tree2

namespace Tree1 {

vector<pair<int, int>> edges;
vector<int> tree[MAX_N];
int fa[MAX_N], size[MAX_N], son[MAX_N];
int timer, dfn[MAX_N], rev[MAX_N];
int ans[MAX_N];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
    edges.push_back({x, y});
}

void dfs(int x) {
    size[x] = 1;
    dfn[x] = ++timer;
    rev[timer] = x;

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

void solve(int x, bool keep) {
    for (int y : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;
        
        solve(y, false);
    }

    if (son[x])
        solve(son[x], true);
    
    for (int y : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;
        
        for (int i = dfn[y]; i < dfn[y] + size[y]; ++i)
            Tree2::modify(rev[i], 1);
    }

    Tree2::modify(x, 1);

    if (fa[x])
        ans[x] = Tree2::query(x, fa[x]);

    if (!keep)
        for (int i = dfn[x]; i < dfn[x] + size[x]; ++i)
            Tree2::modify(rev[i], 0);
}

void solve() {
    dfs(1);
    solve(1, true);
    
    for (int i = 1; i < n; ++i) {
        auto [x, y] = edges[i - 1];

        if (fa[y] == x)
            swap(x, y);
        
        cout << ans[x] << " ";
    }
}

} // namespace Tree2

int main() {
#ifdef ONLINE_JUDGE
    freopen("exchange.in", "r", stdin);
    freopen("exchange.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        Tree1::link(x, y);
    }

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        Tree2::link(x, y);
    }

    Tree2::preprocess();
    Tree1::solve();
    return 0;
}
