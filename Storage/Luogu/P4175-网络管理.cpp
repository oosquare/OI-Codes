#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 80000 + 10;

int n, q, mx = 1e8, t[maxn];

namespace SegmentTree {

struct Node {
    int left, right;
    int sum;
};

Node tree[maxn * 200];
int uuid, root[maxn];

void pushup(int x) {
    tree[x].sum = tree[tree[x].left].sum + tree[tree[x].right].sum;
}

void modify(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        tree[x].sum += v;
        return;
    }

    int mid = (l + r) / 2;

    if (p <= mid)
        modify(tree[x].left, l, mid, p, v);
    else
        modify(tree[x].right, mid + 1, r, p, v);

    pushup(x);
}

int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v, int d) {
    for (; p <= n; p += lowbit(p))
        modify(root[p], 1, mx, v, d);
}

void query(int p, vector<int> &rt) {
    for (; p; p -= lowbit(p))
        rt.push_back(root[p]);
}

int query(vector<int> &add, vector<int> &del, int l, int r, int k) {
    if (l == r)
        return l;

    int mid = (l + r) / 2, sum = 0;

    for (int x : add)
        sum += tree[tree[x].right].sum;

    for (int x : del)
        sum -= tree[tree[x].right].sum;

    if (k <= sum) {
        for (int &x : add)
            x = tree[x].right;

        for (int &x : del)
            x = tree[x].right;

        return query(add, del, mid + 1, r, k);
    } else {
        for (int &x : add)
            x = tree[x].left;

        for (int &x : del)
            x = tree[x].left;

        return query(add, del, l, mid, k - sum);
    }
}

} // namespace SegmentTree

namespace Tree {

vector<int> tree[maxn];
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int timer, dfn[maxn], rev[maxn];

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

void preprocess() {
    dfs(1);
    dfs(1, 1);
}

void modify(int x, int v) {
    SegmentTree::add(dfn[x], t[x], -1);
    SegmentTree::add(dfn[x], v, 1);
    t[x] = v;
}

int query(int x, int y, int k) {
    int fx = top[x], fy = top[y], cnt = 0;
    vector<int> add, del;

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(x, y);
            swap(fx, fy);
        }

        SegmentTree::query(dfn[x], add);
        SegmentTree::query(dfn[fx] - 1, del);
        cnt += dep[x] - dep[fx] + 1;
        x = fa[fx];
        fx = top[x];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    SegmentTree::query(dfn[y], add);
    SegmentTree::query(dfn[x] - 1, del);
    cnt += dep[y] - dep[x] + 1;

    if (k > cnt)
        return -1;

    return SegmentTree::query(add, del, 1, mx, k);
}

} // namespace Tree

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        cin >> t[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        Tree::link(x, y);
    }

    Tree::preprocess();

    for (int i = 1; i <= n; ++i)
        SegmentTree::add(Tree::dfn[i], t[i], 1);

    for (int i = 1; i <= q; ++i) {
        int k, x, y;
        cin >> k >> x >> y;

        if (k == 0) {
            Tree::modify(x, y);
        } else {
            int res = Tree::query(x, y, k);

            if (res == -1)
                cout << "invalid request!" << endl;
            else
                cout << res << endl;
        }
    }
    
    return 0;
}