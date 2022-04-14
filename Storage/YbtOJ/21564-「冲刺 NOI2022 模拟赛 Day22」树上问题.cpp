#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>

template <typename T = int>
inline T read() {
    register T x = 0;
    int c = std::getchar();

    for (; c < '0' || c > '9'; c = std::getchar())
        ;

    for (; '0' <= c && c <= '9'; c = std::getchar())
        x = (x << 1) + (x << 3) + c - '0';

    return x;
}

constexpr int MAX_N = 500000 + 10;
constexpr int MOD = 1000000007;

inline int add(int x, int y) {
    x += y;
    return (x >= MOD ? x - MOD : x);
}

inline int sub(int x, int y) {
    x -= y;
    return (x < 0 ? x + MOD : x);
}

class SegmentTree {
public:
    void init(int a[], int n) {
        for (register int i = 1; i <= n; ++i)
            arr[i] = add(arr[i - 1], a[i]);

        build(1, 1, n);
    }

    void modify(int l, int r, int v) {
        ll = l;
        rr = r;
        modify(1, v);
    }

    int query() { return tree[1].sum; }

private:
    struct Node {
        int left, right;
        int sum, cnt;
    };

    Node tree[MAX_N * 4];
    int arr[MAX_N], ll, rr;

    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;
        tree[x].sum = sub(arr[r], arr[l - 1]);

        if (l == r)
            return;

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void modify(int x, int v) {
        if (ll <= tree[x].left && tree[x].right <= rr) {
            tree[x].cnt += v;

            if (tree[x].cnt != 0)
                tree[x].sum = 0;
            else if (tree[x].left == tree[x].right)
                tree[x].sum = sub(arr[tree[x].right], arr[tree[x].left - 1]);
            else
                tree[x].sum = add(tree[x * 2].sum, tree[x * 2 + 1].sum);

            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;

        if (ll <= mid)
            modify(x * 2, v);

        if (mid < rr)
            modify(x * 2 + 1, v);

        if (tree[x].cnt != 0)
            tree[x].sum = 0;
        else if (tree[x].left == tree[x].right)
            tree[x].sum = sub(arr[tree[x].right], arr[tree[x].left - 1]);
        else
            tree[x].sum = add(tree[x * 2].sum, tree[x * 2 + 1].sum);
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
        seg.init(val, tot);
    }

    void modify(int x, int y, int v) {
        int fx = top[x], fy = top[y];

        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                std::swap(fx, fy);
                std::swap(x, y);
            }

            seg.modify(dfn[fx], dfn[x], v);
            x = fa[fx];
            fx = top[x];
        }

        if (x == y)
            return;

        if (dep[x] > dep[y])
            std::swap(x, y);

        seg.modify(dfn[x] + 1, dfn[y], v);
    }

    int query() { return seg.query(); }

private:
    std::vector<int> tree[MAX_N];
    int fa[MAX_N], dep[MAX_N], size[MAX_N], son[MAX_N], top[MAX_N];
    int tot, timer, dfn[MAX_N], rev[MAX_N], val[MAX_N];
    SegmentTree seg;

    void dfs(int x) {
        size[x] = 1;
        dep[x] = dep[fa[x]] + 1;
        ++tot;

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
        rev[timer] = x;
        val[timer] = (int) (1ll * size[x] * (tot - size[x]) % MOD);

        if (son[x])
            dfs(son[x], t);

        for (int y : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;

            dfs(y, y);
        }
    }
};

struct Query {
    int val, x, y;
};

int n, m, q;
Tree tree;
std::vector<Query> qs[MAX_N];
int ans;

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("rhapsody.in", "r", stdin);
    std::freopen("rhapsody.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read();
    m = read();
    q = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        tree.link(x, y);
    }

    tree.preprocess();

    for (int i = 1; i <= q; ++i) {
        int l = read(), r = read(), x = read(), y = read();
        qs[l].push_back({ 1, x, y });
        qs[r + 1].push_back({ -1, x, y });
    }

    for (register int i = 1, p = 12345678; i <= m; ++i, p = (int) (p * 12345678ll % MOD)) {
        for (auto [v, x, y] : qs[i])
            tree.modify(x, y, v);

        ans = add(ans, (int) (1ll * tree.query() * p % MOD));
    }

    std::cout << ans << std::endl;
    return 0;
}
