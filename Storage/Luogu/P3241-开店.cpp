#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 1.5e5 + 10;

struct Tree {
    vector<pair<int, int>> tree[maxn];
    int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    long long dis[maxn];

    void link(int x, int y, int l) {
        tree[x].push_back({y, l});
        tree[y].push_back({x, l});
    }

    vector<pair<int, int>> &operator[](int x) {
        return tree[x];
    }

    void preprocess() {
        dfs(1);
        dfs(1, 1);
    }

    void dfs(int x) {
        dep[x] = dep[fa[x]] + 1;
        sze[x] = 1;

        for (auto [y, l] : tree[x]) {
            if (y == fa[x])
                continue;

            fa[y] = x;
            dis[y] = dis[x] + l;
            dfs(y);
            sze[x] += sze[y];

            if (sze[y] > sze[son[x]])
                son[x] = y;
        }
    }

    void dfs(int x, int t) {
        top[x] = t;

        if (son[x])
            dfs(son[x], t);

        for (auto [y, l] : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;

            dfs(y, y);
        }
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

    long long distance(int x, int y) {
        return dis[x] + dis[y] - 2 * dis[lca(x, y)];
    }
};

bool cmp(const pair<long long, int> &lhs, const pair<long long, int> &rhs) {
    return lhs.second < rhs.second;
}

struct DynamicArray {
    vector<pair<long long, int>> arr;
    vector<long long> sum;

    DynamicArray() {
        arr.push_back({0, -1});
    }

    void reserve(int n) {
        arr.reserve(n + 3);
        sum.reserve(n + 3);
    }

    void pushBack(int val, int col) {
        arr.push_back({val, col});
    }

    void preprocess() {
        sort(arr.begin(), arr.end(), cmp);

        long long last = 0;

        for (auto [v, c] : arr) {
            sum.push_back(last + v);
            last += v;
        }
    }

    pair<long long, int> query(int l, int r) {
        if (arr.empty())
            return {0, 0};

        auto il = lower_bound(arr.begin(), arr.end(), make_pair(0ll, l), cmp) - arr.begin();
        auto ir = upper_bound(arr.begin(), arr.end(), make_pair(0ll, r), cmp) - arr.begin() - 1;
        return {sum[ir] - (il > 0 ? sum[il - 1] : 0), ir - il + 1};
    }
};

int n, q, a, col[maxn];
Tree tree;
int uuid;
int sze[maxn], sze2[maxn], fa[maxn], root, tot;
bool vis[maxn];
long long ans;
int mx;
vector<int> val;
DynamicArray f1[maxn], f2[maxn];

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (auto [y, l] : tree[x]) {
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

    for (auto [y, l] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getSize(y, x);
        sze[x] += sze[y];
    }
}

void build(int x) {
    vis[x] = true;
    getSize(x, 0);
    f1[x].reserve(sze[x]);
    f2[x].reserve(sze[x]);

    for (auto [y, l] : tree[x]) {
        if (vis[y])
            continue;

        tot = sze[y];
        root = 0;
        getRoot(y, 0);
        fa[root] = x;
        build(root);
    }
}

void modify(int x0, int t) {
    for (int x = x0; x; x = fa[x]) {
        f1[x].pushBack(tree.distance(x0, x), t);

        if (fa[x])
            f2[x].pushBack(tree.distance(x0, fa[x]), t);
    }
}

long long query(int x0, int l, int r) {
    auto res = f1[x0].query(l, r);
    long long sum = res.first;

    for (int x = x0; fa[x]; x = fa[x]) {
        auto res1 = f1[fa[x]].query(l, r);
        auto res2 = f2[x].query(l, r);
        sum += (res1.first - res2.first) + tree.distance(fa[x], x0) * (res1.second - res2.second);
    }

    return sum;
}

int id(int x) {
    return lower_bound(val.begin(), val.end(), x) - val.begin() + 1;
}

void discretize() {
    for (int i = 1; i <= n; ++i)
        val.push_back(col[i]);

    sort(val.begin(), val.end());
    auto it = unique(val.begin(), val.end());
    val.erase(it, val.end());
    mx = val.size();

    for (int i = 1; i <= n; ++i)
        col[i] = id(col[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q >> a;

    for (int i = 1; i <= n; ++i)
        cin >> col[i];

    for (int i = 1; i < n; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        tree.link(x, y, l);
    }

    discretize();
    tree.preprocess();
    tot = n;
    getRoot(1, 0);
    build(root);

    for (int i = 1; i <= n; ++i)
        modify(i, col[i]);

    for (int i = 1; i <= n; ++i) {
        f1[i].preprocess();
        f2[i].preprocess();
    }

    for (int i = 1; i <= q; ++i) {
        int x, aa, bb;
        cin >> x >> aa >> bb;
        int l = min((aa + ans) % a, (bb + ans) % a);
        int r = max((aa + ans) % a, (bb + ans) % a);
        l = id(l);
        r = id(r + 1) - 1;
        ans = query(x, l, r);
        cout << ans << endl;
    }

    return 0;
}