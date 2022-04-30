#include <iostream>
#include <algorithm>

constexpr int MAX_N = 200000 + 10;
constexpr int INF = 0x3f3f3f3f;

class SegmentTree {
public:
    void init(int l, int r) {
        build(1, l, r);
    }

    void add(int l, int r, int v) {
        add(1, l, r, v);
    }

    long long query(int l, int r) {
        return query(1, l, r);
    }

private:
    struct Node {
        int left, right;
        long long sum, add;
    };

    Node tree[MAX_N * 4];

    void pushup(int x) {
        tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
    }

    void update(int x, long long v) {
        tree[x].sum += (tree[x].right - tree[x].left + 1) * v;
        tree[x].add += v;
    }

    void pushdown(int x) {
        if (tree[x].add == 0)
            return;

        update(x * 2, tree[x].add);
        update(x * 2 + 1, tree[x].add);
        tree[x].add = 0;
    }
    
    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r)
            return;

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void add(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            add(x * 2, l, r, v);

        if (mid < r)
            add(x * 2 + 1, l, r, v);

        pushup(x);
    }

    long long query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].sum;

        int mid = (tree[x].left + tree[x].right) / 2;
        long long res = 0;
        pushdown(x);

        if (l <= mid)
            res += query(x * 2, l, r);

        if (mid < r)
            res += query(x * 2 + 1, l, r);

        return res;
    }
};

struct Query {
    int l, r, id;
};

int n, m, p1, p2;
int k[MAX_N];
SegmentTree tree;
int st[MAX_N], top, l[MAX_N], r[MAX_N];
std::vector<int> c1[MAX_N];
std::vector<std::pair<int, int>> c2[MAX_N], c3[MAX_N];
std::vector<Query> qs[MAX_N];
long long ans[MAX_N * 2];

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("c.in", "r", stdin);
    std::freopen("c.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m >> p1 >> p2;

    for (int i = 1; i <= n; ++i)
        std::cin >> k[i];

    for (int i = 1; i <= m; ++i) {
        int l, r;
        std::cin >> l >> r;
        qs[l - 1].push_back({ l, r, i });
        qs[r].push_back({ l, r, i + m });
        ans[i + m] += 1ll * (r - l) * p1;
    }

    k[0] = k[n + 1] = INF;

    for (int i = 0; i <= n + 1; ++i) {
        while (top && k[st[top]] < k[i]) {
            r[st[top]] = i;
            --top;
        }

        l[i] = st[top];
        st[++top] = i;
    }

    for (int i = 1; i <= n; ++i) {
        if (0 < l[i] && r[i] < n + 1)
            c1[r[i]].push_back(l[i]);

        if (l[i] + 1 <= i - 1 && r[i] < n + 1)
            c2[r[i]].push_back({ l[i] + 1, i - 1 });

        if (0 < l[i] && i + 1 <= r[i] - 1)
            c3[l[i]].push_back({ i + 1, r[i] - 1 });
    }

    tree.init(0, n + 1);

    for (int i = 1; i <= n; ++i) {
        for (int p : c1[i])
            tree.add(p, p, p1);

        for (auto [l, r] : c2[i])
            tree.add(l, r, p2);

        for (auto [l, r] : c3[i])
            tree.add(l, r, p2);

        for (auto [l, r, id] : qs[i])
            ans[id] += tree.query(l, r);
    }

    for (int i = 1; i <= m; ++i)
        std::cout << ans[i + m] - ans[i] << std::endl;

    return 0;
}