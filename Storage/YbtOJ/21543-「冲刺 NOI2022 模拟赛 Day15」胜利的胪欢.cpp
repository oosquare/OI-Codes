#include <iostream>
#include <vector>

constexpr int MAX_N = 200000 + 10;
constexpr long long INFINITY = 100000000000;

int n;
std::vector<std::pair<int, int>> tree[MAX_N];
long long c[MAX_N], d[MAX_N];
long long dis[MAX_N];
long long lv[MAX_N], rv[MAX_N], mv[MAX_N];
long long ans, sol[MAX_N];

void link(int x, int y, int c) {
    tree[x].push_back({ y, c });
}

namespace SegmentTree {
    struct Node {
        int ls, rs;
        long long sum;
    };

    Node tree[MAX_N * 40];
    int root[MAX_N], tot;

    void add(int &x, long long l, long long r, long long p, long long v) {
        if (!x)
            x = ++tot;

        tree[x].sum += v;
        
        if (l == r)
            return;

        long long mid = (l + r) / 2;

        if (p <= mid)
            add(tree[x].ls, l, mid, p, v);
        else
            add(tree[x].rs, mid + 1, r, p, v);
    }

    int merge(int x, int y) {
        if (!x || !y)
            return x ^ y;

        tree[x].sum += tree[y].sum;
        tree[x].ls = merge(tree[x].ls, tree[y].ls);
        tree[x].rs = merge(tree[x].rs, tree[y].rs);
        return x;
    }

    long long findLeft(int x, long long l, long long r, long long val) {
        if (l == r)
            return l;

        long long mid = (l + r) / 2;
        tree[x].sum -= val;

        if (val <= tree[tree[x].ls].sum) {
            return findLeft(tree[x].ls, l, mid, val);
        } else {
            val -= tree[tree[x].ls].sum;
            tree[x].ls = 0;
            return findLeft(tree[x].rs, mid + 1, r, val);
        }
    }

    long long findRight(int x, long long l, long long r, long long val) {
        if (l == r)
            return l;

        long long mid = (l + r) / 2;
        tree[x].sum -= val;

        if (val <= tree[tree[x].rs].sum) {
            return findRight(tree[x].rs, mid + 1, r, val);
        } else {
            val -= tree[tree[x].rs].sum;
            tree[x].rs = 0;
            return findRight(tree[x].ls, l, mid, val);
        }
    }
}

void dfs(int x) {
    for (auto [y, c] : tree[x]) {
        dis[y] = dis[x] + c;
        dfs(y);
    }

    if (tree[x].empty()) {
        lv[x] = rv[x] = dis[x];
        mv[x] = d[x];
        SegmentTree::add(SegmentTree::root[x], 0, INFINITY, dis[x], d[x] * 2);
        return;
    }

    for (auto [y, c] : tree[x]) {
        mv[x] += mv[y];
        SegmentTree::root[x] = SegmentTree::merge(SegmentTree::root[x], SegmentTree::root[y]);
    }

    lv[x] = rv[x] = -1;

    if (x == 1)
        return;

    if (mv[x] > d[x]) {
        lv[x] = SegmentTree::findLeft(SegmentTree::root[x], 0, INFINITY, mv[x] - d[x]);
        rv[x] = SegmentTree::findRight(SegmentTree::root[x], 0, INFINITY, mv[x] - d[x]);
        mv[x] = d[x];
    }
}

void dfs(int x, long long val) {
    for (auto [y, c] : tree[x]) {
        sol[y] = c;
        long long res = val;

        if (lv[y] != -1) {
            if (res < lv[y]) {
                sol[y] -= lv[y] - res;
                res = lv[y];
            } else if (res > rv[y]) {
                sol[y] += res - rv[y];
                res = rv[y];
            }
        }

        dfs(y, res);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("tree.in", "r", stdin);
    std::freopen("tree.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n;

    for (int i = 2; i <= n; ++i) {
        int fa;
        std::cin >> fa >> c[i] >> d[i];
        link(fa, i, c[i]);
    }

    dfs(1);
    dfs(1, SegmentTree::findLeft(SegmentTree::root[1], 0, INFINITY, mv[1]));

    for (int i = 2; i <= n; ++i)
        ans += std::abs(c[i] - sol[i]) * d[i];

    std::cout << ans << std::endl;
    
    for (int i = 2; i <= n; ++i)
        std::cout << sol[i] << std::endl;

    return 0;
}
