#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Tree {
    vector<int> tree[maxn];
    int timer, dep[maxn], size[maxn], son[maxn], fa[maxn], top[maxn];

    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> &operator[](int x) {
        return tree[x];
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

    int lca(int x, int y) {
        int fx = top[x], fy = top[y];

        while (fx != fy) {
            if (dep[fx] > dep[fy]) {
                x = fa[fx];
                fx = top[x];
            } else {
                y = fa[fy];
                fy = top[y];
            }
        }

        return (dep[x] < dep[y] ? x : y);
    }

    int distance(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
};

struct BinaryIndexedTree {
    vector<int> arr;
    int size;

    void init(int s) {
        size = s;
        arr.clear();
        arr = vector<int>(size + 3);
    }

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int p, int v) {
        ++p;

        if (p > size + 1)
            return;

        for (; p <= size + 1; p += lowbit(p))
            arr[p] += v;
    }

    int query(int p) {
        p = min(p + 1, size + 1);
        int res = 0;

        for (; p; p -= lowbit(p))
            res += arr[p];

        return res;
    }
};

int n, m, val[maxn];
Tree tree;
BinaryIndexedTree f1[maxn], f2[maxn];
int fa[maxn];
int root, tot, sze[maxn], sze2[maxn];
bool vis[maxn];
int ans;

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[x] < sze2[root])
        root = x;
}

void getSize(int x, int fa) {
    sze[x] = 1;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getSize(y, x);
        sze[x] += sze[y];
    }
}

void build(int x) {
    vis[x] = true;
    getSize(x, 0);
    f1[x].init(sze[x]);
    f2[x].init(sze[x]);

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        root = 0;
        tot = sze[y];
        getRoot(y, 0);
        fa[root] = x;
        build(root);
    }
}

void modify(int x0, int v) {
    for (int x = x0; x; x = fa[x]) {
        f1[x].add(tree.distance(x, x0), v);

        if (fa[x])
            f2[x].add(tree.distance(fa[x], x0), v);
    }
}

int query(int x0, int k) {
    int res = f1[x0].query(k);

    for (int x = x0; fa[x]; x = fa[x]) {
        int d = tree.distance(x0, fa[x]);

        if (k < d)
            continue;

        res += f1[fa[x]].query(k - d);
        res -= f2[x].query(k - d);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> val[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree.link(x, y);
    }

    tree.preprocess();
    tot = n;
    getRoot(1, 0);
    build(root);

    for (int i = 1; i <= n; ++i)
        modify(i, val[i]);

    for (int i = 1; i <= m; ++i) {
        int op, x, y;
        cin >> op >> x >> y;
        x ^= ans;
        y ^= ans;

        if (op == 0) {
            ans = query(x, y);
            cout << ans << endl;
        } else {
            modify(x, y - val[x]);
            val[x] = y;
        }
    }

    return 0;
}