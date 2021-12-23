#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int left, right;
    int sum;    
};

int n, m, t[maxn];
Node seg[maxn * 50];
int root[maxn], uuid;
vector<int> tree[maxn];
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int timer, dfn[maxn];

void pushup(int x) {
    seg[x].sum = seg[seg[x].left].sum + seg[seg[x].right].sum;
}

void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        seg[x].sum += v;
        return;
    }

    int mid = (l + r) / 2;

    if (p <= mid)
        add(seg[x].left, l, mid, p, v);
    else
        add(seg[x].right, mid + 1, r, p, v);

    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return 0;

    if (ql <= l && r <= qr)
        return seg[x].sum;

    int mid = (l + r) / 2, res = 0;

    if (ql <= mid)
        res += query(seg[x].left, l, mid, ql, qr);

    if (mid < qr)
        res += query(seg[x].right, mid + 1, r, ql, qr);

    return res;
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

    if (son[x])
        dfs(son[x], t);

    for (int y : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs(y, y);
    }
}

bool query(int x, int y, int c) {
    int fx = top[x], fy = top[y];
    int sum = 0;

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }

        sum += query(root[c], 1, n, dfn[fx], dfn[x]);
        x = fa[fx];
        fx = top[x];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    sum += query(root[c], 1, n, dfn[x], dfn[y]);
    return sum > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> t[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    dfs(1);
    dfs(1, 1);

    for (int i = 1; i <= n; ++i)
        add(root[t[i]], 1, n, dfn[i], 1);

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << query(a, b, c);
    }

    cout << endl;

    return 0;
}