#pragma Clang optimize(3)
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar()) x = x * 10 + c - '0';

    return x * s;
}

constexpr int MAX_N = 1e5 + 10;
constexpr int MOD = 1e9 + 7;
constexpr int INFINITY = 0x3f3f3f3f;

class SegmentTree {
public:
    void init(int l, int r) {
        this->l = l;
        this->r = r;
        tot = 0;
        root = 0;
    }

    void modify(int p, int v) { modify(root, l, r, p, v); }

    void multiply(int v) { update(root, v); }

    int query(int l, int r) { return query(root, this->l, this->r, l, r); }

private:
    struct Node {
        int ls, rs;
        int sum = 0, mul = 1;
    };

    Node tree[MAX_N * 40];
    int tot, root, l, r;

    int create() {
        ++tot;
        tree[tot] = { 0, 0, 0, 1 };
        return tot;
    }

    void pushup(int x) { tree[x].sum = (tree[tree[x].ls].sum + tree[tree[x].rs].sum) % MOD; }

    void update(int x, int v) {
        if (!x)
            return;

        tree[x].sum = (int)(1ll * tree[x].sum * v % MOD);
        tree[x].mul = (int)(1ll * tree[x].mul * v % MOD);
    }

    void pushdown(int x) {
        if (tree[x].mul == 1)
            return;

        update(tree[x].ls, tree[x].mul);
        update(tree[x].rs, tree[x].mul);

        tree[x].mul = 1;
    }

    void modify(int& x, int l, int r, int p, int v) {
        if (!x)
            x = create();

        if (l == r) {
            tree[x].sum = (tree[x].sum + v) % MOD;
            return;
        }

        int mid = (l + r) >> 1;
        pushdown(x);

        if (p <= mid)
            modify(tree[x].ls, l, mid, p, v);
        else
            modify(tree[x].rs, mid + 1, r, p, v);

        pushup(x);
    }

    int query(int x, int l, int r, int ql, int qr) {
        if (!x)
            return 0;

        if (ql <= l && r <= qr)
            return tree[x].sum;

        pushdown(x);
        int mid = (l + r) >> 1, res = 0;

        if (ql <= mid)
            res = (res + query(tree[x].ls, l, mid, ql, qr)) % MOD;

        if (mid < qr)
            res = (res + query(tree[x].rs, mid + 1, r, ql, qr)) % MOD;

        return res;
    }
};

int n, a[MAX_N];
std::vector<int> tree[MAX_N];
int timer, l[MAX_N], r[MAX_N], son[MAX_N * 3], sze[MAX_N];
int sum[MAX_N], pre[MAX_N * 3], suf[MAX_N * 3];
int seq[MAX_N][2], tot;
SegmentTree seg;
int f[MAX_N];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void preprocess(int x, int fa) {
    sum[x] = sum[fa] + a[x];
    sze[x] = 1;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        preprocess(y, x);
        sze[x] += sze[y];
    }

    l[x] = r[x] = timer + 1;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        son[++r[x]] = y;
    }

    ++r[x];
    timer = r[x];

    std::sort(son + l[x] + 1, son + r[x], [](int lhs, int rhs) { return sze[lhs] > sze[rhs]; });
}

void calc(int x, int s) {
    ++tot;
    seq[tot][0] = sum[x];
    seq[tot][1] = (int)(1ll * s * pre[r[x] - 1] % MOD);

    for (int i = l[x] + 1; i < r[x]; ++i) calc(son[i], (int)(1ll * s * pre[i - 1] % MOD * suf[i + 1] % MOD));
}

void dfs(int x, int fa) {
    for (int i = l[x] + 2; i < r[x]; ++i) {
        dfs(son[i], x);
        seg.init(-INFINITY, INFINITY);
    }

    if (l[x] + 1 < r[x])
        dfs(son[l[x] + 1], x);

    pre[l[x]] = suf[r[x]] = 1;

    for (int i = l[x] + 1; i < r[x]; ++i) pre[i] = (int)(1ll * pre[i - 1] * f[son[i]] % MOD);

    for (int i = r[x] - 1; i > l[x]; --i) suf[i] = (int)(1ll * suf[i + 1] * f[son[i]] % MOD);

    if (sum[x] - sum[fa] >= 0)
        f[x] = (f[x] + pre[r[x] - 1]) % MOD;

    f[x] = (int)((f[x] + 1ll * suf[l[x] + 2] * seg.query(sum[fa], INFINITY)) % MOD);

    for (int i = l[x] + 2; i < r[x]; ++i) {
        tot = 0;
        calc(son[i], 1);

        for (int j = 1; j <= tot; ++j) {
            if (seq[j][0] >= sum[fa])
                f[x] = (int)((f[x] + 1ll * seq[j][1] * pre[i - 1] % MOD * suf[i + 1]) % MOD);

            f[x] = (int)((f[x] + 1ll * seq[j][1] * suf[i + 1] % MOD *
                                     seg.query(sum[x] + sum[fa] - seq[j][0], INFINITY)) %
                         MOD);
        }

        seg.multiply(f[son[i]]);

        for (int j = 1; j <= tot; ++j) seg.modify(seq[j][0], (int)(1ll * seq[j][1] * pre[i - 1] % MOD));
    }

    seg.modify(sum[x], pre[r[x] - 1]);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("run.in", "r", stdin);
    freopen("run.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();

    for (int i = 1; i <= n; ++i) a[i] = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(x, y);
    }

    preprocess(1, 0);
    seg.init(-INFINITY, INFINITY);
    dfs(1, 0);

    std::cout << f[1] << std::endl;

    return 0;
}
