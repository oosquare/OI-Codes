#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 5e5 + 10;

struct Edge {
    int x, y, l;

    bool operator<(const Edge &rhs) const {
        return l < rhs.l;
    } 
};

struct Query {
    int v, x, k, id;

    bool operator<(const Query &rhs) const {
        return x < rhs.x;
    }
};

struct Node {
    int ls, rs;
    int sum;
};

int n, m, q, h[maxn], mx;
Edge edges[maxm];
int fa[maxn];
Node tree[maxn * 50];
int uuid, root[maxn];
Query qs[maxm];
int ans[maxm];

void pushup(int x) {
    tree[x].sum = tree[tree[x].ls].sum + tree[tree[x].rs].sum;
}


void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        tree[x].sum += v;
        return;
    }

    int mid = (l + r) / 2;

    if (p <= mid)
        add(tree[x].ls, l, mid, p, v);
    else
        add(tree[x].rs, mid + 1, r, p, v);

    pushup(x);
}

int query(int x, int l, int r, int k) {
    if (l == r)
        return l;

    int mid = (l + r) / 2, sum = tree[tree[x].rs].sum;

    if (k > sum)
        return query(tree[x].ls, l, mid, k - sum);
    else
        return query(tree[x].rs, mid + 1, r, k);
}

int merge(int x, int y, int l, int r) {
    if (!x || !y)
        return x ^ y;

    if (l == r) {
        tree[x].sum += tree[y].sum;
        return x;
    }

    int mid = (l + r) / 2;
    tree[x].ls = merge(tree[x].ls, tree[y].ls, l, mid);
    tree[x].rs = merge(tree[x].rs, tree[y].rs, mid + 1, r);
    pushup(x);
    return x;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y) {
        fa[x] = y;
        root[y] = merge(root[y], root[x], 1, mx);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        mx = max(mx, h[i]);
    }

    for (int i = 1; i <= m; ++i) {
        auto &[x, y, l] = edges[i];
        cin >> x >> y >> l;
    }

    for (int i = 1; i <= q; ++i) {
        auto &[v, x, k, id] = qs[i];
        cin >> v >> x >> k;
        id = i;
    }

    sort(edges + 1, edges + 1 + m);
    sort(qs + 1, qs + 1 + q);

    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        add(root[i], 1, mx, h[i], 1);
    }

    for (int i = 1, j = 0; i <= q; ++i) {
        auto [v, x, k, id] = qs[i];

        while (j < m && edges[j + 1].l <= x) {
            ++j;
            merge(edges[j].x, edges[j].y);
        }

        int fv = find(v);

        if (tree[root[fv]].sum < k)
            ans[id] = -1;
        else
            ans[id] = query(root[fv], 1, mx, k);
    }

    for (int i = 1; i <= q; ++i)
        cout << ans[i] << endl;

    return 0;
}