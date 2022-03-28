#include <iostream>
#include <algorithm>

constexpr int MAX_N = 200000 + 10;
constexpr int MOD = 1000000007;

class SegmentTree {
public:
    void init(int len) {
        build(1, 1, len);
    }

    void assign(int p, int v) {
        assign(1, p, v);
    }

    void multiply(int l, int r, int v) {
        multiply(1, l, r, v);
    }

    int query(int l, int r) {
        return query(1, l, r);
    }
private:
    struct Node {
        int left, right;
        int sum, mul;
    };

    Node tree[MAX_N * 4];
    
    void pushup(int x) {
        tree[x].sum = (tree[x * 2].sum + tree[x * 2 + 1].sum) % MOD;
    }

    void update(int x, int v) {
        tree[x].mul = (int) (1ll * tree[x].mul * v % MOD);
        tree[x].sum = (int) (1ll * tree[x].sum * v % MOD);
    }

    void pushdown(int x) {
        if (tree[x].mul == 1)
            return;

        update(x * 2, tree[x].mul);
        update(x * 2 + 1, tree[x].mul);
        tree[x].mul = 1;
    }

    void build(int x, int l, int r) {
        tree[x] = { l, r, 0, 1 };

        if (l == r)
            return;

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void assign(int x, int p, int v) {
        if (tree[x].left == tree[x].right) {
            tree[x].sum = v;
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (p <= mid)
            assign(x * 2, p, v);
        else
            assign(x * 2 + 1, p, v);

        pushup(x);
    }

    void multiply(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            multiply(x * 2, l, r, v);

        if (mid < r)
            multiply(x * 2 + 1, l, r, v);

        pushup(x);
    }

    int query(int x, int l, int r) {
        if (l > r)
            return 0;

        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].sum;

        int mid = (tree[x].left + tree[x].right) / 2, res = 0;
        pushdown(x);

        if (l <= mid)
            res = (res + query(x * 2, l, r)) % MOD;

        if (mid < r)
            res = (res + query(x * 2 + 1, l, r)) % MOD;

        return res;
    }
};

class BinaryIndexedTree {
public:
    void init(int n) {
        len = n;
    }

    void add(int x, int y) {
        for (; x <= len; x += lowbit(x))
            arr[x] += y;
    }

    int query(int x) {
        int res = 0;

        for (; x; x -= lowbit(x))
            res += arr[x];

        return res;
    }
private:
    int len, arr[MAX_N];
    
    int lowbit(int x) {
        return x & (-x);
    }
};

struct Number {
    int val, pos;
};

int n;
Number s[MAX_N];
int inv[MAX_N * 2];
SegmentTree tree;
BinaryIndexedTree bit;
int tot = 1, ans;

int main() {
    std::ios::sync_with_stdio(false);
   
    std::cin >> n;
    tree.init(n);
    bit.init(n);

    for (int i = 1; i <= n; ++i) {
        std::cin >> s[i].val;
        s[i].pos = i;
    }

    inv[1] = 1;

    for (int i = 2; i <= 2 * n; ++i)
        inv[i] = (int) (1ll * inv[MOD % i] * (MOD - MOD / i) % MOD);

    std::sort(s + 1, s + n + 1, [](const auto &lhs, const auto &rhs) {
        return lhs.val < rhs.val;
    });

    for (int i = 1; i <= n; ++i)
        tot = (int) (1ll * tot * (s[i].val - i + 1) % MOD);

    for (int i = 1; i <= n; ++i) {
        int res = 0;
        res = ((tree.query(1, s[i].pos - 1) - tree.query(s[i].pos + 1, n)) % MOD + MOD) % MOD;
        res = (int) (1ll * res * tot % MOD * inv[2 * (s[i].val - i + 1)] % MOD);
        res = (int) ((res + 1ll * (bit.query(n) - bit.query(s[i].pos)) * tot) % MOD);
        ans = (ans + res) % MOD;

        tree.multiply(1, n, (int) (1ll * (s[i].val - i) * inv[s[i].val - i + 1] % MOD));
        tree.assign(s[i].pos, s[i].val - i);
        bit.add(s[i].pos, 1);
    }

    std::cout << ans << std::endl;
    return 0;
}
