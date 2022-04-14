#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

constexpr int MAX_N = 1e5 + 10;
constexpr long long INFINITY = 0x3f3f3f3f3f3f3f3f;

class SegmentTree {
public:
    void init(int n) { build(1, 1, n); }
    void assign(int l, int r, long long v) { assign(1, l, r, v); }
    long long query(int p) const { return query(1, p); }

private:
    struct Node {
        int left, right;
        long long min = INFINITY, assign = INFINITY;
    } tree[MAX_N * 4];

    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;
        if (l == r)
            return;
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void assign(int x, int l, int r, long long v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            tree[x].min = min(tree[x].min, v);
            tree[x].assign = min(tree[x].assign, v);
            return;
        }
        int mid = (tree[x].left + tree[x].right) / 2;
        if (l <= mid)
            assign(x * 2, l, r, v);
        if (mid < r)
            assign(x * 2 + 1, l, r, v);
        tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
    }

    long long query(int x, int p) const {
        if (tree[x].left == tree[x].right)
            return min(tree[x].assign, tree[x].min);
        int mid = (tree[x].left + tree[x].right) / 2;
        long long res = tree[x].assign;
        if (p <= mid)
            res = min(res, query(x * 2, p));
        else
            res = min(res, query(x * 2 + 1, p));
        return res;
    }
};

class Tree {
public:
    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess(int root) {
        dfs(root);
        dfs(root, root);
        seg.init(timer);
    }

    int lca(int x, int y) const {
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

    int below(int x, int to) const {
        if (x == to)
            return 0;
        int fx = top[x];
        while (fx != top[to]) {
            if (fa[fx] == to)
                return fx;
            x = fa[fx];
            fx = top[x];
        }
        return son[to];
    }

    void assign(int x, int y, long long v) {
        int fx = top[x], fy = top[y];
        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(fx, fy);
                swap(x, y);
            }
            seg.assign(dfn[fx], dfn[x], v);
            x = fa[fx];
            fx = top[x];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        seg.assign(dfn[x], dfn[y], v);
    }

    long long query(int x) const { return seg.query(dfn[x]); }

private:
    vector<int> tree[MAX_N];
    int size[MAX_N], fa[MAX_N], son[MAX_N], dep[MAX_N], top[MAX_N];
    int timer, dfn[MAX_N], rev[MAX_N];
    SegmentTree seg;

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
        rev[timer] = x;
        if (son[x])
            dfs(son[x], t);
        for (int y : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;
            dfs(y, y);
        }
    }
};

int n, m, s, t;
vector<pair<int, int>> graph[MAX_N];
long long f[MAX_N], dis[MAX_N];
int pre[MAX_N];
bool vis[MAX_N];
Tree tree;

void link(int x, int y, int l) {
    graph[x].push_back({ y, l });
    graph[y].push_back({ x, l });
}

void dijkstra(int start, bool type) {
    for (int i = 1; i <= n; ++i) {
        vis[i] = false;
        dis[i] = INFINITY;
    }
    priority_queue<pair<long long, int>> q;
    q.push({ 0, start });
    dis[start] = 0;
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (auto [y, l] : graph[x]) {
            long long val = dis[x] + l;
            if (type)
                val = max(val, f[y]);
            if (dis[y] <= val)
                continue;
            dis[y] = val;
            pre[y] = x;
            q.push({ -dis[y], y });
        }
    }
}

void build() {
    for (int x = 1; x <= n; ++x) {
        if (!pre[x])
            continue;
        tree.link(pre[x], x);
    }
    tree.preprocess(t);
}

void calc() {
    for (int x = 1; x <= n; ++x) {
        for (auto [y, l] : graph[x]) {
            if (pre[y] == x || pre[x] == y)
                continue;
            int top = tree.below(x, tree.lca(x, y));
            if (top)
                tree.assign(x, top, dis[x] + l + dis[y]);
        }
    }
    for (int x = 1; x <= n; ++x) {
        f[x] = tree.query(x);
        if (f[x] != INFINITY)
            f[x] -= dis[x];
    }
    f[t] = 0;
}

int main() {
    std::freopen("path.in", "r", stdin);
    std::freopen("path.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }
    dijkstra(t, false);
    build();
    calc();
    dijkstra(t, true);
    cout << (dis[s] >= INFINITY / 2 ? -1 : dis[s]) << endl;

    return 0;
}
