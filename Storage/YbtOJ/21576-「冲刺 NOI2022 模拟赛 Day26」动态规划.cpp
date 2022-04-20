#include <iostream>

constexpr int MAX_N = 10 + 1;
constexpr int MAX_M = 100000 + 10;

struct DisjointSet {
    int fa[2 * MAX_N];

    int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            fa[x] = y;
            return true;
        } else {
            return false;
        }
    }
};

struct Data {
    int col[MAX_N];
    int id[MAX_N];
};

struct Node {
    int left, right;
    Data ld, rd;
    int sum;
};

int n, m, q;
Node tree[MAX_M * 4];
int grid[MAX_N][MAX_M];

int calc(const Data &lhs, const Data &rhs) {
    DisjointSet ds;
    int res = 0;

    for (int i = 1; i <= n; ++i)
        ds.fa[i] = lhs.id[i];

    for (int i = 1; i <= n; ++i)
        ds.fa[i + n] = rhs.id[i] + n;

    for (int i = 1; i <= n; ++i) 
        if (lhs.col[i] == rhs.col[i] && ds.merge(i, i + n))
            ++res;

    return res;
}

void pushup(int x) {
    tree[x].ld = tree[x * 2].ld;
    tree[x].rd = tree[x * 2 + 1].rd;
    tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum - calc(tree[x * 2].rd, tree[x * 2 + 1].ld);
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r) {
        Data res;
        DisjointSet ds;
        tree[x].sum = n;

        for (int i = 1; i <= n; ++i) {
            res.col[i] = grid[i][l];
            ds.fa[i] = i;
        }

        for (int i = 1; i < n; ++i) {
            if (res.col[i] == res.col[i + 1]) {
                --tree[x].sum;
                ds.merge(i, i + 1);
            }
        }

        for (int i = 1; i <= n; ++i)
            res.id[i] = ds.find(i);

        tree[x].ld = tree[x].rd = res;
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

Node query(int x, int l, int r) {
    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x];

    int mid = (tree[x].left + tree[x].right) / 2;

    if (r <= mid) {
        return query(x * 2, l, r);
    } else if (mid < l) {
        return query(x * 2 + 1, l, r);
    } else {
        Node lhs = query(x * 2, l, r), rhs = query(x * 2 + 1, l, r);
        return { 0, 0, lhs.ld, rhs.rd, lhs.sum + rhs.sum - calc(lhs.rd, rhs.ld) };
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("B.in", "r", stdin);
    std::freopen("B.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> q;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            std::cin >> grid[i][j];

    build(1, 1, m);

    for (int i = 1; i <= q; ++i) {
        int l, r;
        std::cin >> l >> r;
        std::cout << query(1, l, r).sum << std::endl;
    }

    return 0;
}