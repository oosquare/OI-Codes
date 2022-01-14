#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 300 + 10;
constexpr int mod = 1e9 + 7;

class BinaryIndexedTree {
public:
    void init(int n) {
        size = n;
    }

    void add(int p, int v) {
        for (; p <= size; p += lowbit(p))
            arr[p] += v;
    }

    int query(int p) {
        int res = 0;

        for (; p; p -= lowbit(p))
            res += arr[p];

        return res;
    }
private:
    int arr[maxn], size;

    int lowbit(int x) {
        return x & (-x);
    }
};

class Tree {
public:
    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess() {
        dfs(1);
        dfs(1, 1);
        arr.init(timer);
    }

    void add(int x, int v) {
        arr.add(dfn[x], v);
    }

    int query(int x, int y) {
        int fx = top[x], fy = top[y], res = 0;

        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(x, y);
                swap(fx, fy);
            }

            res += arr.query(dfn[x]) - arr.query(dfn[fx] - 1);
            x = fa[fx];
            fx = top[x];
        }

        if (dep[x] > dep[y])
            swap(x, y);

        res += arr.query(dfn[y]) - arr.query(dfn[x] - 1);

        return res;
    }
private:
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    int timer, dfn[maxn];
    BinaryIndexedTree arr;

    void dfs(int x) {
        dep[x] = dep[fa[x]] + 1;
        size[x] = 1;

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
};

int n, q, k, m, r, seq[maxn];
Tree tree;
int h[maxn], f[maxn][maxm], ans;

void solve() {
    cin >> k >> m >> r;

    for (int i = 1; i <= k; ++i) {
        cin >> seq[i];
        tree.add(seq[i], 1);
    }

    for (int i = 1; i <= k; ++i)
        h[seq[i]] = tree.query(seq[i], r) - 1;

    for (int i = 1; i <= k; ++i)
        tree.add(seq[i], -1);

    sort(seq + 1, seq + 1 + k, [](int l, int r) {
        return h[l] < h[r];
    });

    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= m; ++j)
            f[i][j] = 0;

    f[1][1] = 1;

    for (int i = 2; i <= k; ++i)
        for (int j = 1; j <= min(i, m); ++j)
            f[i][j] = (1ll * max(j - h[seq[i]], 0) * f[i - 1][j] % mod + f[i - 1][j - 1]) % mod;

    ans = 0;

    for (int i = 1; i <= m; ++i)
        ans = (ans + f[k][i]) % mod;

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree.link(x, y);
    }

    tree.preprocess();

    for (int i = 1; i <= q; ++i)
        solve();

    return 0;
}